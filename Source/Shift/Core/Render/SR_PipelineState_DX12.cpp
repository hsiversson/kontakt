//ProjectFilter(DX12/Shader)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_PipelineState_DX12.h"
#include "SR_PipelineStateStreamStructs_DX12.h"
#include "SR_RenderDevice_DX12.h"
#include "SR_RootSignature_DX12.h"
#include "SR_VertexLayout.h"

#include "SR_DirectXShaderCompiler.h"

SR_PipelineState_DX12::SR_PipelineState_DX12()
{

}

SR_PipelineState_DX12::~SR_PipelineState_DX12()
{

}

bool SR_PipelineState_DX12::Init(const SR_PipelineStateProperties& aProperties)
{

	for (uint32 i = 0; i < SR_ShaderType_COUNT; ++i)
	{
		const SR_CreateShaderProperties& createShaderProps = aProperties.mCreateShaderProperties[i];
		mShaders[i] = SR_RenderDevice_DX12::gInstance->CreateShader(createShaderProps);
	}

	//for (uint32 i = 0; i < static_cast<uint32>(SR_ShaderType::COUNT); ++i)
	//	mShaderMetaDatas[i] = aProperties.mShaderMetaDatas[i];

//	if (aProperties.mCreateShaderProperties[static_cast<uint32>(SR_ShaderType::Compute)].mSize)
//		return InitAsComputeShader(aProperties);
//#if SR_ENABLE_RAYTRACING
//	else if (aProperties.ms[static_cast<uint32>(SR_ShaderType::Raytracing)].mSize)
//		return InitAsRaytracingShader(aProperties);
//#endif
//#if SR_ENABLE_MESH_SHADERS
//	else if (SR_RenderDevice::gInstance->GetSupportCaps().mEnableMeshShaders && aProperties.mShaderByteCodes[static_cast<uint32>(SR_ShaderType::Mesh)].mSize)
//		return InitAsMeshShader(aProperties);
//#endif
//	else
		return InitDefault(aProperties);
}

ID3D12PipelineState* SR_PipelineState_DX12::GetD3D12PipelineState() const
{
	return mD3D12PipelineState.Get();
}

#if SR_ENABLE_RAYTRACING
const D3D12_DISPATCH_RAYS_DESC& SR_PipelineState_DX12::GetDispatchRaysDesc() const
{
	return mDispatchRaysDesc;
}

ID3D12StateObject* SR_PipelineState_DX12::GetD3D12StateObject() const
{
	return mD3D12StateObject.Get();
}
#endif

static D3D12_INPUT_ELEMENT_DESC CreateElementDesc(DXGI_FORMAT aFormat, uint32 aSemanticIndex, const char* aSemanticName, bool aIsInstanceData = false)
{
	D3D12_INPUT_ELEMENT_DESC element = {};
	element.Format = aFormat;
	element.InputSlot = aIsInstanceData ? 1 : 0;
	element.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
	element.InputSlotClass = aIsInstanceData ? D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA : D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
	element.InstanceDataStepRate = aIsInstanceData ? 1 : 0;
	element.SemanticIndex = aSemanticIndex;
	element.SemanticName = aSemanticName;
	return element;
}

static const char* locGetVertexAttributeSemantic(const SR_VertexAttribute& aAttributeId)
{
	switch (aAttributeId)
	{
	case SR_VertexAttribute::Position: return "POSITION";
	case SR_VertexAttribute::Normal: return "NORMAL";
	case SR_VertexAttribute::Tangent: return "TANGENT";
	case SR_VertexAttribute::Bitangent: return "BITANGENT";
	case SR_VertexAttribute::UV: return "UV";
	case SR_VertexAttribute::Color: return "COLOR";
	case SR_VertexAttribute::BoneId: return "BONEID";
	case SR_VertexAttribute::BoneWeight: return "BONEWEIGHT";
	}

	SC_ASSERT(false, "Unknown attribute");
	return "<unknown>";
}

bool SR_PipelineState_DX12::InitDefault(const SR_PipelineStateProperties& aProperties)
{
	uint32 vsIndex = static_cast<uint32>(SR_ShaderType::Vertex);
	uint32 psIndex = static_cast<uint32>(SR_ShaderType::Pixel);

	SR_DefaultShaderPipelineStreamDesc streamDesc;
	streamDesc.mVS.mByteCode = { mShaders[vsIndex]->GetByteCode().mData, mShaders[vsIndex]->GetByteCode().mSize };
	streamDesc.mPS.mByteCode = { mShaders[psIndex]->GetByteCode().mData, mShaders[psIndex]->GetByteCode().mSize };

	SC_Array<D3D12_INPUT_ELEMENT_DESC> inputElements;

	for (const SR_VertexAttributeData& attribute : aProperties.mVertexLayout.mAttributes)
		inputElements.Add(CreateElementDesc(SR_ConvertFormat_DX12(attribute.mFormat), attribute.mAttributeIndex, locGetVertexAttributeSemantic(attribute.mAttributeId)));

	streamDesc.mVertexLayout.mDesc.NumElements = inputElements.Count();
	streamDesc.mVertexLayout.mDesc.pInputElementDescs = inputElements.GetBuffer();

	streamDesc.mRTVFormats.Init(aProperties.mRenderTargetFormats);
	streamDesc.mDSVFormat.Init(aProperties.mRenderTargetFormats.mDepthFormat);
	streamDesc.mRasterizerState.Init(aProperties.mRasterizerProperties);
	streamDesc.mBlendState.Init(aProperties.mBlendStateProperties);
	streamDesc.mDepthStencilState.Init(aProperties.mDepthStencilProperties);

	switch (aProperties.mPrimitiveTopology)
	{
	case SR_PrimitiveTopology::PointList:
		streamDesc.mPrimitiveTopology.mValue = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
		break;
	case SR_PrimitiveTopology::LineList:
	case SR_PrimitiveTopology::LineStrip:
		streamDesc.mPrimitiveTopology.mValue = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
		break;
	case SR_PrimitiveTopology::TriangleList:
	default:
		streamDesc.mPrimitiveTopology.mValue = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		break;
	}

	SR_RootSignature* rootSignature = (aProperties.mRootSignature) ? aProperties.mRootSignature.Get() : SR_RenderDevice::gInstance->GetRootSignature(SR_RootSignatureType::Graphics);
	SR_RootSignature_DX12* rootSignatureDX12 = static_cast<SR_RootSignature_DX12*>(rootSignature);
	streamDesc.mRootSignature.mPtr = rootSignatureDX12->GetD3D12RootSignature();
	mRootSignature = rootSignature;

	D3D12_PIPELINE_STATE_STREAM_DESC desc = {};
	desc.pPipelineStateSubobjectStream = &streamDesc;
	desc.SizeInBytes = sizeof(streamDesc);

	HRESULT result = E_FAIL;
	result = SR_RenderDevice_DX12::gInstance->GetD3D12Device5()->CreatePipelineState(&desc, IID_PPV_ARGS(&mD3D12PipelineState));

	return SR_VerifyHRESULT(result);
}

bool SR_PipelineState_DX12::InitAsMeshShader(const SR_PipelineStateProperties& aProperties)
{

}

bool SR_PipelineState_DX12::InitAsComputeShader(const SR_PipelineStateProperties& aProperties)
{
	uint32 csIndex = static_cast<uint32>(SR_ShaderType::Compute);
	SR_RootSignature* rootSignature = (aProperties.mRootSignature) ? aProperties.mRootSignature.Get() : SR_RenderDevice::gInstance->GetRootSignature(SR_RootSignatureType::Compute);
	SR_RootSignature_DX12* rootSignatureDX12 = static_cast<SR_RootSignature_DX12*>(rootSignature);

	SR_ComputeShaderPipelineStreamDesc streamDesc;
	streamDesc.mRootSignature.mPtr = rootSignatureDX12->GetD3D12RootSignature();
	streamDesc.mCS.mByteCode = { mShaders[csIndex]->GetByteCode().mData, mShaders[csIndex]->GetByteCode().mSize };

	D3D12_PIPELINE_STATE_STREAM_DESC desc = {};
	desc.pPipelineStateSubobjectStream = &streamDesc;
	desc.SizeInBytes = sizeof(streamDesc);

	HRESULT result = SR_RenderDevice_DX12::gInstance->GetD3D12Device5()->CreatePipelineState(&desc, IID_PPV_ARGS(&mD3D12PipelineState));
	mRootSignature = rootSignature;
	mIsComputeShader = true;
	return SR_VerifyHRESULT(result);
}

bool SR_PipelineState_DX12::InitAsRaytracingShader(const SR_PipelineStateProperties& aProperties)
{

}

void SR_PipelineState_DX12::CreateRaytracingShaderTable(const SR_PipelineStateProperties& aProperties)
{

}
#endif
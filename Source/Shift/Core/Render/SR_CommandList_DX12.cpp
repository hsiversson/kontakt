//ProjectFilter(DX12/CommandList)
#include "Render_Precompiled.h"

#if SR_ENABLE_DX12
#include "SR_CommandList_DX12.h"
#include "SR_RenderDevice_DX12.h"
#include "SR_PipelineState_DX12.h"
#include "SR_RootSignature_DX12.h"
#include "SR_Texture_DX12.h"
#include "SR_BufferResource.h"
#include "SR_TextureResource.h"
#include "SR_DescriptorHeap_DX12.h"

SR_CommandList_DX12::SR_CommandList_DX12(const SR_CommandListType& aType)
	: SR_CommandList(aType)
{

}

SR_CommandList_DX12::~SR_CommandList_DX12()
{

}

bool SR_CommandList_DX12::Init()
{
	D3D12_COMMAND_LIST_TYPE cmdListType = D3D12_COMMAND_LIST_TYPE_DIRECT;
	switch (mType)
	{
	case SR_CommandListType::Compute:
		cmdListType = D3D12_COMMAND_LIST_TYPE_COMPUTE;
		break;
	case SR_CommandListType::Copy:
		cmdListType = D3D12_COMMAND_LIST_TYPE_COPY;
		break;
	default:
		break;
	}

	HRESULT result = SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateCommandAllocator(cmdListType, IID_PPV_ARGS(&mD3D12CommandAllocator));
	if (!SR_VerifyHRESULT(result))
	{
		SC_ASSERT(false);
		return false;
	}

	result = SR_RenderDevice_DX12::gInstance->GetD3D12Device()->CreateCommandList(0, cmdListType, mD3D12CommandAllocator.Get(), nullptr, IID_PPV_ARGS(&mD3D12CommandList));
	if (!SR_VerifyHRESULT(result))
	{
		SC_ASSERT(false);
		return false;
	}

	//SetDebugName(aDebugName);

	mD3D12CommandList.As(&mD3D12CommandList6);

	mD3D12CommandList->Close();
	return true;
}

void SR_CommandList_DX12::DrawInstanced(uint32 aVertexCount, uint32 aInstanceCount, uint32 aStartVertex /*= 0*/, uint32 aStartInstance /*= 0*/)
{
    mD3D12CommandList->DrawInstanced(aVertexCount, aInstanceCount, aStartVertex, aStartInstance);
}

void SR_CommandList_DX12::DrawIndexedInstanced(uint32 aIndexCount, uint32 aInstanceCount, uint32 aStartIndex /*= 0*/, uint32 aStartVertex /*= 0*/, uint32 aStartInstance /*= 0*/)
{
	mD3D12CommandList->DrawIndexedInstanced(aIndexCount, aInstanceCount, aStartIndex, aStartVertex, aStartInstance);
}

void SR_CommandList_DX12::Dispatch(uint32 aGroupCountX, uint32 aGroupCountY /*= 1*/, uint32 aGroupCountZ /*= 1*/)
{
    mD3D12CommandList->Dispatch(aGroupCountX, aGroupCountY, aGroupCountZ);
}

void SR_CommandList_DX12::SetPipelineState(SR_PipelineState* aPipelineState)
{
    SR_PipelineState_DX12* pipelineState = static_cast<SR_PipelineState_DX12*>(aPipelineState);
    mD3D12CommandList->SetPipelineState(pipelineState->GetD3D12PipelineState());
}

void SR_CommandList_DX12::SetPrimitiveTopology(const SR_PrimitiveTopology& aPrimitiveTopology)
{
	switch (aPrimitiveTopology)
	{
	case SR_PrimitiveTopology::PointList:
		mD3D12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case SR_PrimitiveTopology::LineList:
		mD3D12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case SR_PrimitiveTopology::LineStrip:
		mD3D12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
		break;
	case SR_PrimitiveTopology::TriangleList:
	default:
		mD3D12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	}
}

void SR_CommandList_DX12::SetRootSignature(SR_RootSignature* aRootSignature)
{
	SR_RootSignature_DX12* rootSignature = static_cast<SR_RootSignature_DX12*>(aRootSignature);

	ID3D12DescriptorHeap* descriptorHeaps[2];
	descriptorHeaps[0] = static_cast<SR_DescriptorHeap_DX12*>(SR_RenderDevice_DX12::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::CBV_SRV_UAV))->GetD3D12DescriptorHeap();
	descriptorHeaps[1] = static_cast<SR_DescriptorHeap_DX12*>(SR_RenderDevice_DX12::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::SAMPLER))->GetD3D12DescriptorHeap();
	mD3D12CommandList->SetDescriptorHeaps(2, descriptorHeaps);

	if (rootSignature->IsCompute())
		mD3D12CommandList->SetComputeRootSignature(rootSignature->GetD3D12RootSignature());
	else
		mD3D12CommandList->SetGraphicsRootSignature(rootSignature->GetD3D12RootSignature());
}

void SR_CommandList_DX12::SetVertexBuffer(SR_BufferResource* aVertexBuffer)
{
	const SR_BufferResourceProperties& props = aVertexBuffer->GetProperties();

	D3D12_VERTEX_BUFFER_VIEW view = {};
	view.BufferLocation = aVertexBuffer->mD3D12Resource->GetGPUVirtualAddress();
	view.SizeInBytes = props.mElementCount * props.mElementSize;
	view.StrideInBytes = props.mElementSize;

	mD3D12CommandList->IASetVertexBuffers(0, 1, &view);
}

void SR_CommandList_DX12::SetIndexBuffer(SR_BufferResource* aIndexBuffer)
{
	const SR_BufferResourceProperties& props = aIndexBuffer->GetProperties();

	D3D12_INDEX_BUFFER_VIEW view = {};
	view.BufferLocation = aIndexBuffer->mD3D12Resource->GetGPUVirtualAddress();
	view.SizeInBytes = props.mElementCount * props.mElementSize;
	view.Format = SR_ConvertFormat_DX12(props.mFormat);

	mD3D12CommandList->IASetIndexBuffer(&view);
}

void SR_CommandList_DX12::SetRenderTargets(SR_Texture** aRenderTargets, uint32 aNumTargets, SR_Texture* aDepthStencil)
{
	SC_Array<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandles;
	rtvHandles.Reserve(SR_MAX_RENDER_TARGETS);
	for (uint32 i = 0; i < aNumTargets; ++i)
	{
		if (aRenderTargets[i])
		{
			SR_Texture_DX12* rtv = static_cast<SR_Texture_DX12*>(aRenderTargets[i]);
			rtvHandles.Add(rtv->GetCPUHandle(SR_TextureDescriptorType::RenderTarget));
		}
	}

	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = {};
	if (aDepthStencil)
	{
		SR_Texture_DX12* dsv = static_cast<SR_Texture_DX12*>(aDepthStencil);
		dsvHandle = dsv->GetCPUHandle(SR_TextureDescriptorType::DepthStencil);
	}

	mD3D12CommandList->OMSetRenderTargets(rtvHandles.Count(), rtvHandles.GetBuffer(), false, (aDepthStencil) ? &dsvHandle : nullptr);
}

void SR_CommandList_DX12::SetBlendFactor(const SC_Vector4& aBlendFactor)
{
	mD3D12CommandList->OMSetBlendFactor(&aBlendFactor.x);
}

void SR_CommandList_DX12::SetViewport(const SR_Rect& aRect, float aMinDepth /*= 0.0f*/, float aMaxDepth /*= 1.0f*/)
{
	D3D12_VIEWPORT viewport = {};
	viewport.TopLeftX = (float)aRect.mLeft;
	viewport.TopLeftY = (float)aRect.mTop;
	viewport.Width = (float)aRect.mRight - aRect.mLeft;
	viewport.Height = (float)aRect.mBottom - aRect.mTop;
	viewport.MinDepth = aMinDepth;
	viewport.MaxDepth = aMaxDepth;

	mD3D12CommandList->RSSetViewports(1, &viewport);
}

void SR_CommandList_DX12::SetScissorRect(const SR_Rect& aRect)
{
	D3D12_RECT scissorRect = {};
	scissorRect.left = aRect.mLeft;
	scissorRect.top = aRect.mTop;
	scissorRect.right = aRect.mRight;
	scissorRect.bottom = aRect.mBottom;

	mD3D12CommandList->RSSetScissorRects(1, &scissorRect);
}

void SR_CommandList_DX12::ClearRenderTarget(SR_Texture* aRenderTarget, const SC_Vector4& aClearColor)
{
	SR_Texture_DX12* rtv = static_cast<SR_Texture_DX12*>(aRenderTarget);
	if (rtv)
		mD3D12CommandList->ClearRenderTargetView(rtv->GetCPUHandle(SR_TextureDescriptorType::RenderTarget), &aClearColor.x, 0, nullptr);
}

void SR_CommandList_DX12::ClearDepthStencil(SR_Texture* aDepthStencil, float aClearValue /*= 0.0f*/, uint8 aStencilClearValue /*= 0*/, const SR_DepthClearFlags& aClearFlags /*= SR_DepthClearFlags::All*/)
{
	SR_Texture_DX12* dsv = static_cast<SR_Texture_DX12*>(aDepthStencil);
	if (dsv)
	{
		D3D12_CLEAR_FLAGS clearFlag = {};
		switch (aClearFlags)
		{
		case SR_DepthClearFlags::Depth:
			clearFlag = D3D12_CLEAR_FLAG_DEPTH;
			break;
		case SR_DepthClearFlags::Stencil:
			clearFlag = D3D12_CLEAR_FLAG_STENCIL;
			break;
		default:
			clearFlag = D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL;
			break;
		}
		mD3D12CommandList->ClearDepthStencilView(dsv->GetCPUHandle(SR_TextureDescriptorType::DepthStencil), clearFlag, aClearValue, aStencilClearValue, 0, nullptr);
	}
}

void SR_CommandList_DX12::BindRootConstantBuffer(SR_BufferResource* aBuffer, uint32 aBindingSlot, bool aIsCompute)
{
	ID3D12Resource* resource = aBuffer->mD3D12Resource;
	if (aIsCompute)
		mD3D12CommandList->SetComputeRootConstantBufferView(aBindingSlot, resource->GetGPUVirtualAddress());
	else
		mD3D12CommandList->SetGraphicsRootConstantBufferView(aBindingSlot, resource->GetGPUVirtualAddress());
}

void SR_CommandList_DX12::ResourceStateTransition(const SC_Array<SC_Pair<uint32, SR_TrackedResource*>>& aStateTransitions)
{
	SC_Array<D3D12_RESOURCE_BARRIER> barriers;

	for (uint32 i = 0; i < aStateTransitions.Count(); ++i)
	{
		const SC_Pair<uint32, SR_TrackedResource*>& currentResource = aStateTransitions[i];
		SR_ResourceTracking_DX12& tracking = currentResource.mSecond->mResourceTrackingDX12;

		D3D12_RESOURCE_STATES targetState = D3D12_RESOURCE_STATE_COMMON;
		switch (currentResource.mFirst)
		{
		case SR_ResourceState_GenericRead:
			if (mType == SR_CommandListType::Graphics)
				targetState = D3D12_RESOURCE_STATES(tracking.mD3D12ReadState);
			else
				targetState = D3D12_RESOURCE_STATE_COMMON;
			break;

		case SR_ResourceState_Present:
			targetState = D3D12_RESOURCE_STATE_PRESENT;
			break;

		case SR_ResourceState_RenderTarget:
			targetState = D3D12_RESOURCE_STATE_RENDER_TARGET;
			break;

		case SR_ResourceState_ShaderRead:
			targetState = (mType == SR_CommandListType::Compute) ? D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE : (D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);
			break;

		case SR_ResourceState_ShaderWrite:
			targetState = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
			break;

		case SR_ResourceState_Indirect:
			if (mType == SR_CommandListType::Graphics)
				targetState = D3D12_RESOURCE_STATES(D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT | tracking.mD3D12ReadState);
			else
				targetState = D3D12_RESOURCE_STATES(D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT | (tracking.mD3D12ReadState & D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE));
			break;

		case SR_ResourceState_Readback:
			// Add Fence
			break;

		case SR_ResourceState_CopyDst:
			targetState = D3D12_RESOURCE_STATE_COPY_DEST;
			break;

		case SR_ResourceState_CopySrc:
			targetState = D3D12_RESOURCE_STATE_COPY_SOURCE;
			break;

		default:
			SC_ASSERT(false, "Invalid Resource Transition.");
			continue;
		}

		D3D12_RESOURCE_STATES previousState = D3D12_RESOURCE_STATES(tracking.mD3D12CurrentState);

		D3D12_RESOURCE_BARRIER& barrier = barriers.Add();
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.StateBefore = previousState;
		barrier.Transition.StateAfter = targetState;
		barrier.Transition.pResource = currentResource.mSecond->mD3D12Resource;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		tracking.mD3D12CurrentState = targetState;
	}

	if (barriers.Count())
		mD3D12CommandList->ResourceBarrier(barriers.Count(), barriers.GetBuffer());
}

void SR_CommandList_DX12::ResourceWriteBarrier(SR_TrackedResource* aResource)
{
	D3D12_RESOURCE_BARRIER barrier = {};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.UAV.pResource = aResource->mD3D12Resource;

	mD3D12CommandList->ResourceBarrier(1, &barrier);
}

void SR_CommandList_DX12::ResourceAliasBarrier(SR_TrackedResource* /*aResource*/)
{

}

ID3D12CommandList* SR_CommandList_DX12::GetD3D12CommandList() const
{
    return mD3D12CommandList.Get();
}

#endif
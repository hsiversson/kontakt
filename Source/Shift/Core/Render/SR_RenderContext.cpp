//ProjectFilter(Interface)
#include "Render_Precompiled.h"
#include "SR_RenderContext.h"

#include "SR_RenderDevice.h"
#include "SR_CommandList.h"
#include "SR_PipelineState.h"

thread_local SR_RenderContext* SR_RenderContext::gCurrentContext = nullptr;

SR_RenderContext::SR_RenderContext()
{
}

SR_RenderContext::~SR_RenderContext()
{
}

void SR_RenderContext::BeginTask(SR_CommandList* aCmdList)
{
	mCurrentCmdList = aCmdList;
	mCurrentCmdList->Open();
}

void SR_RenderContext::EndTask(bool aSubmitCmdList)
{
	if (aSubmitCmdList)
		SubmitCommandList();

	mCurrentCmdList = nullptr;
}

void SR_RenderContext::SubmitCommandList()
{
	SR_CommandQueue* cmdQueue = SR_RenderDevice::gInstance->GetCommandQueue(mCurrentCmdList->GetType());
	mCurrentCmdList->Close();
	cmdQueue->SubmitCommandList(mCurrentCmdList);

	SR_Fence f = cmdQueue->GetNextFence();
	cmdQueue->SignalFence(f);
	cmdQueue->WaitForFence(f);
}

void SR_RenderContext::Draw(uint32 aVertexCount, uint32 aStartVertex)
{
	PreDraw();
	mCurrentCmdList->DrawInstanced(aVertexCount, 1, aStartVertex, 0);
}

void SR_RenderContext::DrawInstanced(uint32 aVertexCount, uint32 aInstanceCount, uint32 aStartVertex, uint32 aStartInstance)
{
	PreDraw();
	mCurrentCmdList->DrawInstanced(aVertexCount, aInstanceCount, aStartVertex, aStartInstance);
}

void SR_RenderContext::DrawIndexed(uint32 aIndexCount, uint32 aStartIndex, uint32 aStartVertex)
{
	PreDraw();
	mCurrentCmdList->DrawIndexedInstanced(aIndexCount, 1, aStartIndex, aStartVertex, 0);
}

void SR_RenderContext::DrawIndexedInstanced(uint32 aIndexCount, uint32 aInstanceCount, uint32 aStartIndex /*= 0*/, uint32 aStartVertex /*= 0*/, uint32 aStartInstance /*= 0*/)
{
	PreDraw();
	mCurrentCmdList->DrawIndexedInstanced(aIndexCount, aInstanceCount, aStartIndex, aStartVertex, aStartInstance);
}

void SR_RenderContext::Dispatch(uint32 aGroupCountX, uint32 aGroupCountY /*= 1*/, uint32 aGroupCountZ /*= 1*/)
{
	PreDispatch();
	mCurrentCmdList->Dispatch(aGroupCountX, aGroupCountY, aGroupCountZ);
}

void SR_RenderContext::Dispatch(const SC_Vector3ui& aGroupCounts)
{
	Dispatch(aGroupCounts.x, aGroupCounts.y, aGroupCounts.z);
}

void SR_RenderContext::Dispatch(SR_PipelineState* aPipelineState, const SC_Vector3i& aThreadCounts)
{
	Dispatch(aPipelineState, aThreadCounts.x, aThreadCounts.y, aThreadCounts.z);
}

void SR_RenderContext::Dispatch(SR_PipelineState* aPipelineState, uint32 aGroupCountX, uint32 aGroupCountY, uint32 aGroupCountZ)
{
	SC_Vector3ui threadGroups;
	const SC_Vector3ui& numThreads = aPipelineState->GetShaderMetaData(SR_ShaderType::Compute).mNumThreads;
	threadGroups.x = SC_Max((aGroupCountX + numThreads.x - 1) / numThreads.x, 1);
	threadGroups.y = SC_Max((aGroupCountY + numThreads.y - 1) / numThreads.y, 1);
	threadGroups.z = SC_Max((aGroupCountZ + numThreads.z - 1) / numThreads.z, 1);
	SetPipelineState(aPipelineState);
	Dispatch(threadGroups);
}

void SR_RenderContext::SetPipelineState(SR_PipelineState* aPipelineState)
{
	SetRootSignature(aPipelineState->GetRootSignature());
	mCurrentCmdList->SetPipelineState(aPipelineState);
	// cache current state
}

void SR_RenderContext::SetPrimitiveTopology(const SR_PrimitiveTopology& aPrimitiveTopology)
{
	mCurrentCmdList->SetPrimitiveTopology(aPrimitiveTopology);
}

void SR_RenderContext::SetRootSignature(SR_RootSignature* aRootSignature)
{
	mCurrentCmdList->SetRootSignature(aRootSignature);
}

void SR_RenderContext::SetVertexBuffer(SR_BufferResource* aVertexBuffer)
{
	mCurrentCmdList->SetVertexBuffer(aVertexBuffer);
}

void SR_RenderContext::SetIndexBuffer(SR_BufferResource* aIndexBuffer)
{
	mCurrentCmdList->SetIndexBuffer(aIndexBuffer);
}

void SR_RenderContext::SetRenderTarget(SR_Texture* aRenderTarget, SR_Texture* aDepthStencil)
{
	mCurrentCmdList->SetRenderTargets(&aRenderTarget, 1, aDepthStencil);
}

void SR_RenderContext::SetRenderTargets(SR_Texture** aRenderTargets, uint32 aNumTargets, SR_Texture* aDepthStencil)
{
	mCurrentCmdList->SetRenderTargets(aRenderTargets, aNumTargets, aDepthStencil);
}

void SR_RenderContext::SetBlendFactor(const SC_Vector4& aBlendFactor)
{
	mCurrentCmdList->SetBlendFactor(aBlendFactor);
}

void SR_RenderContext::SetViewport(const SR_Rect& aRect, float aMinDepth /*= 0.0f*/, float aMaxDepth /*= 1.0f*/)
{
	mCurrentCmdList->SetViewport(aRect, aMinDepth, aMaxDepth);
}

void SR_RenderContext::SetScissorRect(const SR_Rect& aRect)
{
	mCurrentCmdList->SetScissorRect(aRect);
}

void SR_RenderContext::ClearRenderTarget(SR_Texture* aRenderTarget, const SC_Vector4& aClearColor)
{
	mCurrentCmdList->ClearRenderTarget(aRenderTarget, aClearColor);
}

void SR_RenderContext::ClearRenderTargets(SR_Texture** aRenderTargets, uint32 aNumTargets, const SC_Vector4& aClearColor)
{
	for (uint32 i = 0; i < aNumTargets; ++i)
		mCurrentCmdList->ClearRenderTarget(aRenderTargets[i], aClearColor);
}

void SR_RenderContext::ClearDepthStencil(SR_Texture* aDepthStencil, float aClearValue /*= 0.0f*/, uint8 aStencilClearValue /*= 0*/, const SR_DepthClearFlags& aClearFlags /*= SR_DepthClearFlags::All*/)
{
	mCurrentCmdList->ClearDepthStencil(aDepthStencil, aClearValue, aStencilClearValue, aClearFlags);
}

void SR_RenderContext::BindConstantBuffer(const void* /*aData*/, uint32 /*aByteSize*/, uint32 /*aBindingSlot*/)
{
}

void SR_RenderContext::BindConstantBuffer(SR_BufferResource* aBuffer, uint32 aBindingSlot)
{
	if (mStateCache.mConstantBuffers[aBindingSlot] != aBuffer)
	{
		mStateCache.mConstantsDirty[aBindingSlot] = true;
		mStateCache.mConstantBuffers[aBindingSlot] = aBuffer;

		uint64 offset = 0;
		mStateCache.mConstantBufferOffsets[aBindingSlot] = offset;
	}
}

void SR_RenderContext::ResourceStateTransition(uint32 aTargetState, SR_TrackedResource* aResource)
{
	SC_Array<SC_Pair<uint32, SR_TrackedResource*>> transition;
	transition.Add(SC_Pair(aTargetState, aResource));
	mCurrentCmdList->ResourceStateTransition(transition);
}

void SR_RenderContext::ResourceStateTransition(const SC_Array<SC_Pair<uint32, SR_TrackedResource*>>& aStateTransitions)
{
	mCurrentCmdList->ResourceStateTransition(aStateTransitions);
}

void SR_RenderContext::ResourceWriteBarrier(SR_TrackedResource* aResource)
{
	mCurrentCmdList->ResourceWriteBarrier(aResource);
}

void SR_RenderContext::ResourceAliasBarrier(SR_TrackedResource* aResource)
{
	mCurrentCmdList->ResourceAliasBarrier(aResource);
}

SR_RenderContext* SR_RenderContext::GetCurrent()
{
	return gCurrentContext;
}

void SR_RenderContext::PreDraw()
{

	BindResources();
}

void SR_RenderContext::PreDispatch()
{

	BindResources();
}

void SR_RenderContext::BindResources()
{
	if (mStateCache.mRootSignature)
	{
		const SR_RootSignatureProperties& rootSignatureProperties = mStateCache.mRootSignature->GetProperties();

		for (uint32 paramIndex = 0; paramIndex < rootSignatureProperties.mRootParams.Count(); ++paramIndex)
		{
			const SR_RootParam& param = rootSignatureProperties.mRootParams[paramIndex];
			if (param.mType == SR_RootParamType::CBV /*&& constantsDirty*/)
			{
				SR_BufferResource* buf = mStateCache.mConstantBuffers[param.mDescriptor.mRegisterIndex];
				if (!mStateCache.mConstantsDirty[param.mDescriptor.mRegisterIndex] || !buf)
					continue;

				//uint64 bufferOffset = mStateCache.mConstantBufferOffsets[param.mDescriptor.mRegisterIndex];
				mCurrentCmdList->BindRootConstantBuffer(buf, paramIndex, rootSignatureProperties.mIsCompute);
			}
			else
				SC_ASSERT(false, "not implemented.");
		}
	}
}

//ProjectFilter(Interface)
#pragma once
#include "SR_RenderStates.h"
#include "SR_Texture.h"
#include "SR_Buffer.h"
#include "SR_PipelineState.h"

class SR_CommandList;

class SR_RenderContext
{
    friend class SR_RenderDevice;
private:
    struct StateCache
    {
        SR_RootSignature* mRootSignature;
        SR_PipelineState* mPipelineState;

        SC_StaticArray<SR_BufferResource*, 4> mConstantBuffers;
		SC_StaticArray<uint64, 4> mConstantBufferOffsets;
		SC_StaticArray<bool, 4> mConstantsDirty;
    };

public:
    SR_RenderContext();
    ~SR_RenderContext();

    void BeginTask(SR_CommandList* aCmdList);
    void EndTask(bool aSubmitCmdList = true);

    void SubmitCommandList();

    void Draw(uint32 aVertexCount, uint32 aStartVertex = 0);
    void DrawInstanced(uint32 aVertexCount, uint32 aInstanceCount, uint32 aStartVertex = 0, uint32 aStartInstance = 0);

    void DrawIndexed(uint32 aIndexCount, uint32 aStartIndex = 0, uint32 aStartVertex = 0);
    void DrawIndexedInstanced(uint32 aIndexCount, uint32 aInstanceCount, uint32 aStartIndex = 0, uint32 aStartVertex = 0, uint32 aStartInstance = 0);

    void Dispatch(uint32 aGroupCountX, uint32 aGroupCountY = 1, uint32 aGroupCountZ = 1);
    void Dispatch(const SC_Vector3ui& aGroupCounts);
    void Dispatch(SR_PipelineState* aPipelineState, const SC_Vector3i& aThreadCounts);
    void Dispatch(SR_PipelineState* aPipelineState, uint32 aGroupCountX, uint32 aGroupCountY = 1, uint32 aGroupCountZ = 1);

    void SetPipelineState(SR_PipelineState* aPipelineState);
    void SetPrimitiveTopology(const SR_PrimitiveTopology& aPrimitiveTopology);
    void SetRootSignature(SR_RootSignature* aRootSignature);

    void SetVertexBuffer(SR_BufferResource* aVertexBuffer);
    void SetIndexBuffer(SR_BufferResource* aIndexBuffer);
    
    void SetRenderTarget(SR_Texture* aRenderTarget, SR_Texture* aDepthStencil);
    void SetRenderTargets(SR_Texture** aRenderTargets, uint32 aNumTargets, SR_Texture* aDepthStencil);
    void SetBlendFactor(const SC_Vector4& aBlendFactor);

    void SetViewport(const SR_Rect& aRect, float aMinDepth = 0.0f, float aMaxDepth = 1.0f);
    void SetScissorRect(const SR_Rect& aRect);

	void ClearRenderTarget(SR_Texture* aRenderTarget, const SC_Vector4& aClearColor);
	void ClearRenderTargets(SR_Texture** aRenderTargets, uint32 aNumTargets, const SC_Vector4& aClearColor);
	void ClearDepthStencil(SR_Texture* aDepthStencil, float aClearValue = 0.0f, uint8 aStencilClearValue = 0, const SR_DepthClearFlags& aClearFlags = SR_DepthClearFlags::All);

    void BindConstantBuffer(const void* aData, uint32 aByteSize, uint32 aBindingSlot);
    void BindConstantBuffer(SR_BufferResource* aBuffer, uint32 aBindingSlot);

    void ResourceStateTransition(uint32 aTargetState, SR_TrackedResource* aResource);
    void ResourceStateTransition(const SC_Array<SC_Pair<uint32, SR_TrackedResource*>>& aStateTransitions);
    void ResourceWriteBarrier(SR_TrackedResource* aResource);
    void ResourceAliasBarrier(SR_TrackedResource* aResource);

    static SR_RenderContext* GetCurrent();

private:
    void PreDraw();
    void PreDispatch();
    void BindResources();

    StateCache mStateCache;
    SC_Ref<SR_CommandList> mCurrentCmdList;

    static thread_local SR_RenderContext* gCurrentContext;
};
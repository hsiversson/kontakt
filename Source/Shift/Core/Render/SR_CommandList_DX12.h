//ProjectFilter(DX12/CommandList)
#pragma once

#if SR_ENABLE_DX12
#include "SR_CommandList.h"

class SR_CommandList_DX12 final : public SR_CommandList
{
public:
	SR_CommandList_DX12(const SR_CommandListType& aType);
	~SR_CommandList_DX12();

	bool Init();

	void DrawInstanced(uint32 aVertexCount, uint32 aInstanceCount, uint32 aStartVertex = 0, uint32 aStartInstance = 0) override;
	void DrawIndexedInstanced(uint32 aIndexCount, uint32 aInstanceCount, uint32 aStartIndex = 0, uint32 aStartVertex = 0, uint32 aStartInstance = 0) override;

	void Dispatch(uint32 aGroupCountX, uint32 aGroupCountY = 1, uint32 aGroupCountZ = 1) override;

	void SetPipelineState(SR_PipelineState* aPipelineState) override;
	void SetPrimitiveTopology(const SR_PrimitiveTopology& aPrimitiveTopology) override;
	void SetRootSignature(SR_RootSignature* aRootSignature) override;

	void SetVertexBuffer(SR_BufferResource* aVertexBuffer) override;
	void SetIndexBuffer(SR_BufferResource* aIndexBuffer) override;

	void SetRenderTargets(SR_Texture** aRenderTargets, uint32 aNumTargets, SR_Texture* aDepthStencil) override;
	void SetBlendFactor(const SC_Vector4& aBlendFactor) override;

	void SetViewport(const SR_Rect& aRect, float aMinDepth = 0.0f, float aMaxDepth = 1.0f) override;
	void SetScissorRect(const SR_Rect& aRect) override;

	void ClearRenderTarget(SR_Texture* aRenderTarget, const SC_Vector4& aClearColor) override;
	void ClearDepthStencil(SR_Texture* aDepthStencil, float aClearValue = 0.0f, uint8 aStencilClearValue = 0, const SR_DepthClearFlags& aClearFlags = SR_DepthClearFlags::All) override;

	void BindRootConstantBuffer(SR_BufferResource* aBuffer, uint32 aBindingSlot, bool aIsCompute = false) override;

	void ResourceStateTransition(const SC_Array<SC_Pair<uint32, SR_TrackedResource*>>& aStateTransitions) override;
	void ResourceWriteBarrier(SR_TrackedResource* aResource) override;
	void ResourceAliasBarrier(SR_TrackedResource* aResource) override;

	ID3D12CommandList* GetD3D12CommandList() const;

private:
	SR_ComPtr<ID3D12CommandAllocator> mD3D12CommandAllocator;
	SR_ComPtr<ID3D12GraphicsCommandList> mD3D12CommandList;
	SR_ComPtr<ID3D12GraphicsCommandList6> mD3D12CommandList6;
};

#endif
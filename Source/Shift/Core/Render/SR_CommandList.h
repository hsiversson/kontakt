//ProjectFilter(Interface/CommandList)
#pragma once
#include "SR_Resource.h"
#include "SR_RenderStates.h"

class SR_PipelineState;
class SR_RootSignature;
class SR_BufferResource;
class SR_Texture;
class SR_TrackedResource;

class SR_CommandList : public SR_Resource
{
public:
	SR_CommandList(const SR_CommandListType& aType);
	virtual ~SR_CommandList();

	virtual void Open();
	virtual void Close();

	virtual void DrawInstanced(uint32 aVertexCount, uint32 aInstanceCount, uint32 aStartVertex = 0, uint32 aStartInstance = 0);
	virtual void DrawIndexedInstanced(uint32 aIndexCount, uint32 aInstanceCount, uint32 aStartIndex = 0, uint32 aStartVertex = 0, uint32 aStartInstance = 0);

	virtual void Dispatch(uint32 aGroupCountX, uint32 aGroupCountY = 1, uint32 aGroupCountZ = 1);

	virtual void SetPipelineState(SR_PipelineState* aPipelineState);
	virtual void SetPrimitiveTopology(const SR_PrimitiveTopology& aPrimitiveTopology);
	virtual void SetRootSignature(SR_RootSignature* aRootSignature);

	virtual void SetVertexBuffer(SR_BufferResource* aVertexBuffer);
	virtual void SetIndexBuffer(SR_BufferResource* aIndexBuffer);

	virtual void SetRenderTargets(SR_Texture** aRenderTargets, uint32 aNumTargets, SR_Texture* aDepthStencil);
	virtual void SetBlendFactor(const SC_Vector4& aBlendFactor);

	virtual void SetViewport(const SR_Rect& aRect, float aMinDepth = 0.0f, float aMaxDepth = 1.0f);
	virtual void SetScissorRect(const SR_Rect& aRect);

	virtual void ClearRenderTarget(SR_Texture* aRenderTarget, const SC_Vector4& aClearColor);
	virtual void ClearDepthStencil(SR_Texture* aDepthStencil, float aClearValue = 0.0f, uint8 aStencilClearValue = 0, const SR_DepthClearFlags& aClearFlags = SR_DepthClearFlags::All);

	virtual void BindRootConstantBuffer(SR_BufferResource* aBuffer, uint32 aBindingSlot, bool aIsCompute = false);

	virtual void ResourceStateTransition(const SC_Array<SC_Pair<uint32, SR_TrackedResource*>>& aStateTransitions);
	virtual void ResourceWriteBarrier(SR_TrackedResource* aResource);
	virtual void ResourceAliasBarrier(SR_TrackedResource* aResource);

	const SR_CommandListType& GetType() const;

protected:
	const SR_CommandListType mType;
};


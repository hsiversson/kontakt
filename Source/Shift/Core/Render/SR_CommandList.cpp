//ProjectFilter(Interface/CommandList)
#include "Render_Precompiled.h"
#include "SR_CommandList.h"

SR_CommandList::SR_CommandList(const SR_CommandListType& aType)
	: mType(aType)
{

}

SR_CommandList::~SR_CommandList()
{

}

void SR_CommandList::Open()
{
}

void SR_CommandList::Close()
{
}

void SR_CommandList::DrawInstanced(uint32 /*aVertexCount*/, uint32 /*aInstanceCount*/, uint32 /*aStartVertex*/ /*= 0*/, uint32 /*aStartInstance*/ /*= 0*/)
{

}

void SR_CommandList::DrawIndexedInstanced(uint32 /*aIndexCount*/, uint32 /*aInstanceCount*/, uint32 /*aStartIndex*/ /*= 0*/, uint32 /*aStartVertex*/ /*= 0*/, uint32 /*aStartInstance*/ /*= 0*/)
{

}

void SR_CommandList::Dispatch(uint32 /*aGroupCountX*/, uint32 /*aGroupCountY*/ /*= 1*/, uint32 /*aGroupCountZ*/ /*= 1*/)
{

}

void SR_CommandList::SetPipelineState(SR_PipelineState* /*aPipelineState*/)
{

}

void SR_CommandList::SetPrimitiveTopology(const SR_PrimitiveTopology& /*aPrimitiveTopology*/)
{

}

void SR_CommandList::SetRootSignature(SR_RootSignature* /*aRootSignature*/)
{

}

void SR_CommandList::SetVertexBuffer(SR_BufferResource* /*aVertexBuffer*/)
{

}

void SR_CommandList::SetIndexBuffer(SR_BufferResource* /*aIndexBuffer*/)
{

}

void SR_CommandList::SetRenderTargets(SR_Texture** /*aRenderTargets*/, uint32 /*aNumTargets*/, SR_Texture* /*aDepthStencil*/)
{

}

void SR_CommandList::SetBlendFactor(const SC_Vector4& /*aBlendFactor*/)
{

}

void SR_CommandList::SetViewport(const SR_Rect& /*aRect*/, float /*aMinDepth*/ /*= 0.0f*/, float /*aMaxDepth*/ /*= 1.0f*/)
{

}

void SR_CommandList::SetScissorRect(const SR_Rect& /*aRect*/)
{

}

void SR_CommandList::ClearRenderTarget(SR_Texture* /*aRenderTarget*/, const SC_Vector4& /*aClearColor*/)
{

}

void SR_CommandList::ClearDepthStencil(SR_Texture* /*aDepthStencil*/, float /*aClearValue*/ /*= 0.0f*/, uint8 /*aStencilClearValue*/ /*= 0*/, const SR_DepthClearFlags& /*aClearFlags*/ /*= SR_DepthClearFlags::All*/)
{

}

void SR_CommandList::BindRootConstantBuffer(SR_BufferResource* /*aBuffer*/, uint32 /*aBindingSlot*/, bool /*aIsCompute*/)
{
}

void SR_CommandList::ResourceStateTransition(const SC_Array<SC_Pair<uint32, SR_TrackedResource*>>& /*aStateTransitions*/)
{

}

void SR_CommandList::ResourceWriteBarrier(SR_TrackedResource* /*aResource*/)
{

}

void SR_CommandList::ResourceAliasBarrier(SR_TrackedResource* /*aResource*/)
{

}

const SR_CommandListType& SR_CommandList::GetType() const
{
	return mType;
}

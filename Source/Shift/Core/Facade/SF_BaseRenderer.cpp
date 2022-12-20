#include "Facade_Precompiled.h"
#include "SF_BaseRenderer.h"
#include "SR_RenderContext.h"

SF_BaseRenderer::SF_BaseRenderer()
{

}

SF_BaseRenderer::~SF_BaseRenderer()
{

}

bool SF_BaseRenderer::Init()
{

	return true;
}

void SF_BaseRenderer::Render()
{
	SR_RenderContext* ctx = SR_RenderContext::GetCurrent();

	ctx->SetVertexBuffer(mDefaultVertexBuffer);
	ctx->SetIndexBuffer(mDefaultIndexBuffer);

	ctx->SetPipelineState(mDefaultPipelineState);
	ctx->DrawIndexedInstanced(mDefaultIndexBuffer->GetProperties().mElementCount, 1);
}

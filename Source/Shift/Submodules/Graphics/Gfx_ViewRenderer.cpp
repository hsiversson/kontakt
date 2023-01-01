//ProjectFilter(View)
#include "Graphics_Precompiled.h"
#include "Gfx_ViewRenderer.h"
#include "Gfx_View.h"

Gfx_ViewRenderer::Gfx_ViewRenderer()
{

}

Gfx_ViewRenderer::~Gfx_ViewRenderer()
{

}

bool Gfx_ViewRenderer::Init()
{
	return true;
}

void Gfx_ViewRenderer::Prepare(Gfx_View* /*aView*/)
{
}

void Gfx_ViewRenderer::Render(Gfx_View* /*aView*/)
{
	SR_RenderContext* ctx = SR_RenderContext::GetCurrent();
	//const Gfx_ViewRenderData& renderData = aView->GetRenderData();


	SR_Texture* rtv = SR_RenderDevice::gInstance->GetCurrentSwapChain()->GetCurrentRenderTarget();
	ctx->ResourceStateTransition(SR_ResourceState_RenderTarget, rtv->GetResource());
	ctx->ClearRenderTarget(rtv, { 1.0f, 0.0f, 0.0f, 0.0f });
	ctx->ResourceStateTransition(SR_ResourceState_Present, rtv->GetResource());

	//RenderDepth();
	//RenderColor();
	//RenderPostEffects();

}

void Gfx_ViewRenderer::RenderDepth()
{
	//SR_RenderContext* ctx /*= SR_RenderContext::GetCurrent()*/;

	//ctx->BindConstantBuffer();

}

void Gfx_ViewRenderer::ComputeLightGrid()
{

}

void Gfx_ViewRenderer::ComputeIndirectLighting()
{

}

void Gfx_ViewRenderer::RenderColor()
{

}

void Gfx_ViewRenderer::RenderPostEffects()
{

}

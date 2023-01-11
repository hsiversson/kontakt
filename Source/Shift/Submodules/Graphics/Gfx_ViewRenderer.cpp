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

void Gfx_ViewRenderer::Render(Gfx_View* aView)
{
	SR_RenderDevice::gInstance->PostGraphicsTask(std::bind(&Gfx_ViewRenderer::RenderColor, this, aView));



	//const Gfx_ViewRenderData& renderData = aView->GetRenderData();

	//PostGraphicsTask();
	//PostComputeTask();
	//PostCopyTask();


	//SR_RenderContext* ctx = SR_RenderContext::GetCurrent();
	//SR_Texture* rtv = SR_RenderDevice::gInstance->GetCurrentSwapChain()->GetCurrentRenderTarget();
	//ctx->ResourceStateTransition(SR_ResourceState_RenderTarget, rtv->GetResource());
	//ctx->ClearRenderTarget(rtv, { 1.0f, 0.0f, 0.0f, 0.0f });
	//ctx->ResourceStateTransition(SR_ResourceState_Present, rtv->GetResource());

	//RenderDepth();
	//RenderColor();
	//RenderPostEffects();

}

void Gfx_ViewRenderer::RenderDepth(Gfx_View* /*aView*/)
{
	//SR_RenderContext* ctx /*= SR_RenderContext::GetCurrent()*/;

	//ctx->BindConstantBuffer();

}

void Gfx_ViewRenderer::ComputeLightGrid(Gfx_View* /*aView*/)
{

}

void Gfx_ViewRenderer::ComputeIndirectLighting(Gfx_View* /*aView*/)
{

}

void Gfx_ViewRenderer::RenderColor(Gfx_View* /*aView*/)
{
	//const Gfx_ViewRenderData& renderData = aView->GetRenderData();
	//const Gfx_ViewRenderQueues& renderQueues = renderData.mQueues;
	//
	//SR_Rect viewRect;
	//
	//SR_RenderContext* ctx = SR_RenderContext::GetCurrent();
	//
	//SR_Texture* colorTarget = nullptr;
	//SR_Texture* depthStencil = nullptr;
	//ctx->SetRenderTarget(colorTarget, depthStencil);
	//
	//ctx->SetViewport(viewRect);
	//ctx->SetScissorRect(viewRect);
	//
	//renderQueues.mOpaqueQueue.Render(ctx);

	SR_RenderContext* ctx = SR_RenderContext::GetCurrent();
	SR_Texture* rtv = SR_RenderDevice::gInstance->GetCurrentSwapChain()->GetCurrentRenderTarget();
	ctx->ResourceStateTransition(SR_ResourceState_RenderTarget, rtv->GetResource());
	ctx->ClearRenderTarget(rtv, { 1.0f, 0.0f, 0.0f, 0.0f });
	ctx->ResourceStateTransition(SR_ResourceState_Present, rtv->GetResource());
}

void Gfx_ViewRenderer::RenderPostEffects(Gfx_View* /*aView*/)
{

}

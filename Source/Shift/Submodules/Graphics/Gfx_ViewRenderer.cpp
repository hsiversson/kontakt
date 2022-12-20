//ProjectFilter(View)
#include "Graphics_Precompiled.h"
#include "Gfx_ViewRenderer.h"

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

	RenderDepth();
	RenderColor();
	RenderPostEffects();

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

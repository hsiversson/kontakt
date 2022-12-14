//ProjectFilter(View)
#include "Graphics_Precompiled.h"
#include "Gfx_View.h"

Gfx_View::Gfx_View(Gfx_World* aParentWorld)
	: mParentWorld(aParentWorld)
{

}

Gfx_View::~Gfx_View()
{

}

Gfx_ViewRenderData& Gfx_View::GetPrepareData()
{
	return mViewRenderData[0];
}

const Gfx_ViewRenderData& Gfx_View::GetRenderData() const
{
	return mViewRenderData[0];
}

void Gfx_View::StartPrepare()
{

}

void Gfx_View::FinishPrepare()
{

}

void Gfx_View::StartRender()
{

}

void Gfx_View::FinishRender()
{

}

void Gfx_View::SetCamera(const Gfx_Camera& aCamera)
{
	mCamera = aCamera;
}

const Gfx_Camera& Gfx_View::GetCamera() const
{
	return mCamera;
}

Gfx_World* Gfx_View::GetWorld() const
{
	return mParentWorld;
}

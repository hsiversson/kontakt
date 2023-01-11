//ProjectFilter(PostFx)
#include "Graphics_Precompiled.h"
#include "Gfx_PostFx.h"

Gfx_PostFx::Gfx_PostFx()
{

}

Gfx_PostFx::~Gfx_PostFx()
{

}

bool Gfx_PostFx::Init()
{
	if (!mTonemap.Init())
		return false;

	if (!mMotionBlur.Init())
		return false;

	return true;
}

void Gfx_PostFx::Prepare()
{

}

void Gfx_PostFx::Render()
{
	mTonemap.Render();
}

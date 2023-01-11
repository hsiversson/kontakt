//ProjectFilter(PostFx)
#pragma once
#include "Gfx_ViewRenderer.h"

#include "Gfx_Tonemap.h"
#include "Gfx_MotionBlur.h"

class Gfx_PostFx final : public Gfx_ViewRendererSubSystem
{
public:
	Gfx_PostFx();
	~Gfx_PostFx();

	bool Init();

	void Prepare() override;
	void Render() override;

private:

	Gfx_Tonemap mTonemap;
	Gfx_MotionBlur mMotionBlur;
};


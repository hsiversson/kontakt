//ProjectFilter(PostFx/Upscaling)
#pragma once
#include "Gfx_TemporalUpscaler.h"

#if GFX_ENABLE_FSR2

class Gfx_TemporalUpscaler_FSR2 final : public Gfx_TemporalUpscaler
{
public:
	Gfx_TemporalUpscaler_FSR2();
	~Gfx_TemporalUpscaler_FSR2();

	void Render() override;

private:
};

#endif
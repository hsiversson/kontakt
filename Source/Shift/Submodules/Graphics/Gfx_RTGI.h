//ProjectFilter(Lighting)
#pragma once
#include "Gfx_ViewRenderer.h"

class Gfx_RTGI : public Gfx_ViewRendererSubSystem
{
public:
	static constexpr uint32 gNumCascades = 4;
	//static uint32 

public:
	Gfx_RTGI();
	~Gfx_RTGI();

	bool Init();

	void Prepare() override;
	void Render() override;

private:
	bool CreateCascades();

	struct RTCascade
	{
		SC_Vector mOrigin;
		SC_Vector mCameraOrigin;
		SC_Vector mPhaseDirection;
		SC_Vector3i mPhaseOffset;
		float mDistanceBetweenProbes;
		bool mSkip;
	};

	RTCascade mCascades[gNumCascades];

	SC_Ref<SR_PipelineState> mTraceRaysShader;
	SC_Ref<SR_PipelineState> mUpdateProbesShader[2]; // Irradiance/Depth
	SC_Ref<SR_PipelineState> mUpdateProbesBorderShader[2]; // Irradiance/Depth

	SC_Ref<SR_Texture> mProbesIrradiance;
	SC_Ref<SR_Texture> mProbesDepth;
	SC_Ref<SR_Texture> mProbesTraceRadiance;
	SC_Ref<SR_Texture> mProbesTraceDirectionDepth;
};


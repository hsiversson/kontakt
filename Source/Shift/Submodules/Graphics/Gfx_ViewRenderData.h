//ProjectFilter(View)
#pragma once

#include "Gfx_RenderQueue.h"
#include "Gfx_Light.h"

struct Gfx_DirectionalLightRenderData
{
	//Gfx_RenderQueue_ByState mShadowCastersQueue;
	Gfx_DirectionalLightGpuData mGpuData;
	bool mCastShadow;
};

struct Gfx_LocalLightRenderData
{
	//Gfx_RenderQueue_ByState mShadowCastersQueue;
	Gfx_LocalLightGpuData mGpuData;
	bool mCastShadow;
};

struct Gfx_ViewRenderQueues
{
	void Clear()
	{
		mDepthQueue.Clear();
		mDepthQueue_MotionVectors.Clear();
		mOpaqueQueue.Clear();
		mTransparentQueue.Clear();
	}

	Gfx_RenderQueue_ByState mDepthQueue;
	Gfx_RenderQueue_ByState mDepthQueue_MotionVectors;
	Gfx_RenderQueue_ByState mOpaqueQueue;
	Gfx_RenderQueue_FarFirst mTransparentQueue;
};

struct Gfx_ViewRenderData
{
	Gfx_ViewRenderData()
	{
		SC_ZeroMemory(this, sizeof(Gfx_ViewRenderData));
	}

	void Clear()
	{
		mQueues.Clear();
		mDirectionalLights.RemoveAll();
		mVisibleLocalLights.RemoveAll();
	}

	Gfx_ViewRenderQueues mQueues;

	SC_Array<Gfx_DirectionalLightRenderData> mDirectionalLights;
	SC_Array<Gfx_LocalLightRenderData> mVisibleLocalLights;
};


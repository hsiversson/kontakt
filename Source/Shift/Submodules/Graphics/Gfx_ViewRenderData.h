//ProjectFilter(View)
#pragma once

#include "Gfx_RenderQueue.h"
#include "Gfx_Light.h"
#include "Gfx_Camera.h"

struct Gfx_DirectionalLightRenderData
{
	//Gfx_RenderQueue_ByState mShadowCastersQueue;
	Gfx_DirectionalLightGpuData mGpuData;
};

struct Gfx_LocalLightRenderData
{
	//Gfx_RenderQueue_ByState mShadowCastersQueue;
	Gfx_LocalLightGpuData mGpuData;
};

struct Gfx_ViewRenderQueues
{
	void Clear()
	{
		mDepthQueue.Clear();
		mDepthQueue_MotionVectors.Clear();
		mOpaqueQueue.Clear();
		mTranslucentQueue.Clear();
	}

	Gfx_RenderQueue_ByState mDepthQueue;
	Gfx_RenderQueue_ByState mDepthQueue_MotionVectors;
	Gfx_RenderQueue_ByState mOpaqueQueue;
	Gfx_RenderQueue_FarFirst mTranslucentQueue;
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

	SR_Rect mViewport;

	Gfx_ViewRenderQueues mQueues;

	SC_Array<Gfx_DirectionalLightRenderData> mDirectionalLights;
	SC_Array<Gfx_LocalLightRenderData> mVisibleLocalLights;
};


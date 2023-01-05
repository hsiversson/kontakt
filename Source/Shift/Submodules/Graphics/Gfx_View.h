//ProjectFilter(View)
#pragma once
#include "Gfx_ViewRenderData.h"
#include "Gfx_Camera.h"

class Gfx_World;
class Gfx_View : public SC_ReferenceCounted
{
	friend class Gfx_ViewRenderer;
public:
	Gfx_View(Gfx_World* aParentWorld);
	~Gfx_View();

	Gfx_ViewRenderData& GetPrepareData();
	const Gfx_ViewRenderData& GetRenderData() const;

	void StartPrepare();
	void FinishPrepare();

	void StartRender();
	void FinishRender();

	void SetCamera(const Gfx_Camera& aCamera);
	const Gfx_Camera& GetCamera() const;

	Gfx_World* GetWorld() const;

private:
	Gfx_ViewRenderData mViewRenderData[2];

	Gfx_Camera mCamera;
	Gfx_World* mParentWorld;
};
//ProjectFilter(View)
#pragma once
#include "Gfx_ViewRenderData.h"

class Gfx_View : public SC_ReferenceCounted
{
	friend class Gfx_ViewRenderer;
public:
	Gfx_View();
	~Gfx_View();

	Gfx_ViewRenderData& GetPrepareData();
	const Gfx_ViewRenderData& GetRenderData() const;

	void StartPrepare();
	void FinishPrepare();

	void StartRender();
	void FinishRender();

private:

	Gfx_ViewRenderData mViewRenderData[2];

};
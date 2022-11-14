//ProjectFilter(View)
#pragma once

class Gfx_View;
struct Gfx_ViewRenderData;
class Gfx_ViewRenderer
{
public:
	Gfx_ViewRenderer();
	~Gfx_ViewRenderer();

	bool Init();

	void Render(Gfx_ViewRenderData& aRenderData);

private:


	void RenderDepth();

	void ComputeLightGrid();

	void ComputeIndirectLighting();

	void RenderColor();

	void RenderPostEffects();
};


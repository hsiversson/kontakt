//ProjectFilter(View)
#pragma once

class Gfx_View;
struct Gfx_ViewRenderData;

class Gfx_ViewRendererSubSystem
{
public:
	Gfx_ViewRendererSubSystem() {}
	virtual ~Gfx_ViewRendererSubSystem() {}

	virtual void Prepare() {};
	virtual void Render() {};

protected:

};

class Gfx_ViewRenderer
{
public:
	Gfx_ViewRenderer();
	~Gfx_ViewRenderer();

	bool Init();

	void Prepare(Gfx_View* aView);
	void Render(Gfx_View* aView);

private:
	void RenderDepth();
	void ComputeLightGrid();
	void ComputeIndirectLighting();
	void RenderColor();
	void RenderPostEffects();
};


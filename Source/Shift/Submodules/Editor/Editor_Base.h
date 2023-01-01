#pragma once
#include "SAF_Application.h"

class Gfx_World;
class Gfx_View;
class Gfx_ViewRenderer;

class Editor_Base : public SAF_ApplicationInterface
{
public:
	Editor_Base();
	~Editor_Base();

	bool Init() override;

	void Update() override;
	void Render() override;

	void Exit() override;

private:
	SC_Ptr<Gfx_World> mGfxWorld;
	SC_Ref<Gfx_View> mGfxView;

	SC_Ptr<Gfx_ViewRenderer> mViewRenderer;
};


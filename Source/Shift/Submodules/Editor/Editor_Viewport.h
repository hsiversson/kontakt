#pragma once
#include "Editor_Dockable.h"

class Gfx_View;

class Editor_Viewport final : public Editor_Dockable
{
public:
	Editor_Viewport();
	~Editor_Viewport();

	void Update();

	void Render();

private:

	SC_Ref<Gfx_View> mView;
};


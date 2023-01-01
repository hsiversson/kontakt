//ProjectFilter(World)
#pragma once
#include "Gfx_View.h"

class Gfx_MeshInstance;

class Gfx_World
{
public:
	Gfx_World();
	~Gfx_World();

	SC_Ref<Gfx_View> CreateView();
	void DestroyView(Gfx_View* aView);

	void Update();

	void PrepareView(Gfx_View* aView);

private:

	SC_Array<SC_Ref<Gfx_View>> mViews;

	SC_Array<SC_Ref<Gfx_MeshInstance>> mMeshes;
};


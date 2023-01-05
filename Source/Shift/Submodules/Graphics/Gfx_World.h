//ProjectFilter(World)
#pragma once
#include "Gfx_View.h"

class Gfx_MeshInstance;
class Gfx_SceneGraph;

class Gfx_World
{
public:
	Gfx_World();
	~Gfx_World();

	bool Init();

	SC_Ref<Gfx_View> CreateView();
	void DestroyView(Gfx_View* aView);

	void Update();

	void PrepareView(Gfx_View* aView);

	void AddMeshInstance(Gfx_MeshInstance* aMeshInstance);
	void RemoveMeshInstance(Gfx_MeshInstance* aMeshInstance);

	void AddLight(Gfx_Light* aLight);
	void RemoveLight(Gfx_Light* aLight);
private:
	SC_Array<SC_Ref<Gfx_View>> mViews;
	SC_Ptr<Gfx_SceneGraph> mSceneGraph;
};


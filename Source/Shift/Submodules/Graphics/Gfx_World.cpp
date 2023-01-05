//ProjectFilter(World)
#include "Graphics_Precompiled.h"

#include "Gfx_World.h"
#include "Gfx_SceneGraph.h"

Gfx_World::Gfx_World()
{

}

Gfx_World::~Gfx_World()
{

}

bool Gfx_World::Init()
{
	mSceneGraph = new Gfx_SceneGraph(this);
	return true;
}

SC_Ref<Gfx_View> Gfx_World::CreateView()
{
	SC_Ref<Gfx_View> view = mViews.Add(new Gfx_View(this));
	return view;
}

void Gfx_World::DestroyView(Gfx_View* aView)
{
	SC_ASSERT(aView->GetWorld() == this, "This view does not belong to this world.");
	mViews.Remove(aView);
}

void Gfx_World::Update()
{
	mSceneGraph->Update();
}

void Gfx_World::PrepareView(Gfx_View* aView)
{

	mSceneGraph->PrepareView(aView);
}

void Gfx_World::AddMeshInstance(Gfx_MeshInstance* aMeshInstance)
{
	mSceneGraph->AddMeshInstance(aMeshInstance);
}

void Gfx_World::RemoveMeshInstance(Gfx_MeshInstance* aMeshInstance)
{
	mSceneGraph->RemoveMeshInstance(aMeshInstance);
}

void Gfx_World::AddLight(Gfx_Light* aLight)
{
	mSceneGraph->AddLight(aLight);
}

void Gfx_World::RemoveLight(Gfx_Light* aLight)
{
	mSceneGraph->RemoveLight(aLight);
}

//ProjectFilter(World)
#include "Graphics_Precompiled.h"
#include "Gfx_World.h"

Gfx_World::Gfx_World()
{

}

Gfx_World::~Gfx_World()
{

}

SC_Ref<Gfx_View> Gfx_World::CreateView()
{
	SC_Ref<Gfx_View> view = mViews.Add(new Gfx_View());
	return view;
}

void Gfx_World::DestroyView(Gfx_View* aView)
{
	mViews.Remove(aView);
}

void Gfx_World::Update()
{
}

void Gfx_World::PrepareView(Gfx_View* /*aView*/)
{


}
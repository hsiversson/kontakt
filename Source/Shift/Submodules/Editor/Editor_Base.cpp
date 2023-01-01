#include "Editor_Precompiled.h"
#include "Editor_Base.h"

#include "Editor_AssetImporter_Assimp.h"

#include "Gfx_World.h"
#include "Gfx_View.h"
#include "Gfx_ViewRenderer.h"

Editor_Base::Editor_Base()
{

}

Editor_Base::~Editor_Base()
{

}

bool Editor_Base::Init()
{

	mViewRenderer = new Gfx_ViewRenderer();
	mGfxWorld = new Gfx_World();
	mGfxView = mGfxWorld->CreateView();

	Editor_AssetImporter_Assimp importer;
	importer.ImportScene("E:/Programmering/kontakt/Data/Shift/Assets/CornellBox/CornellBox.obj");


	return true;
}

void Editor_Base::Update()
{
	mViewRenderer->Render(mGfxView);
}

void Editor_Base::Exit()
{

}

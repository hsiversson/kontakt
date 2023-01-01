#include "Facade_Precompiled.h"
#include "SF_Manager.h"
#include "SF_BaseRenderer.h"

SF_Manager* SF_Manager::gInstance = nullptr;

SF_Manager::SF_Manager()
{

}

SF_Manager::~SF_Manager()
{

}

bool SF_Manager::Init(void* /*aWindowHandle*/)
{
	return false;
}

void SF_Manager::Update()
{
	// Handle Input
	SF_InputManager


	// Other

}

void SF_Manager::Render()
{

}

bool SF_Manager::Create()
{
	if (!gInstance)
		gInstance = new SF_Manager;

	return true;
}

void SF_Manager::Destroy()
{
	delete gInstance;
	gInstance = nullptr;
}

SF_Manager* SF_Manager::Get()
{
	return gInstance;
}


#include "Facade_Precompiled.h"
#include "SF_Manager.h"

SF_Manager* SF_Manager::gInstance = nullptr;

SF_Manager::SF_Manager()
{

}

SF_Manager::~SF_Manager()
{

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


//ProjectFilter(Input)
#include "Common_Precompiled.h"
#include "SC_Input.h"

SC_Input* SC_Input::gInstance = nullptr;

bool SC_Input::Create(void* aNativeWindowHandle /*= nullptr*/, uint32 aFlags /*= 0*/, uint32 aMode /*= 0*/)
{
	SC_ASSERT(!gInstance);

	gInstance = new SC_Input();
	if (!gInstance->Init(aNativeWindowHandle, aFlags, aMode))
	{
		Destroy();
		return false;
	}

	return true;
}

void SC_Input::Destroy()
{
	delete gInstance;
	gInstance = nullptr;
}

SC_Input* SC_Input::Get()
{
	return gInstance;
}

void SC_Input::Update()
{

}

SC_Input::SC_Input()
{

}

SC_Input::~SC_Input()
{

}

bool SC_Input::Init(void* /*aNativeWindowHandle*/, uint32 /*aFlags*/, uint32 /*aMode*/)
{


	return true;
}

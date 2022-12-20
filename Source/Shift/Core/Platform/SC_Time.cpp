//ProjectFilter(Platform)
#include "Platform_Precompiled.h"
#include "SC_Time.h"

SC_Time* SC_Time::gInstance = nullptr;

void SC_Time::Create()
{
	if (!gInstance)
		gInstance = new SC_Time;
}

void SC_Time::Destroy()
{
	delete gInstance;
	gInstance = nullptr;
}

SC_Time* SC_Time::Get()
{
	return gInstance;
}

SC_Time::SC_Time()
{

}

SC_Time::~SC_Time()
{

}

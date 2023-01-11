#include "Common_Precompiled.h"
#include "SC_Console.h"

#if ENABLE_CONSOLE

SC_Console* SC_Console::gInstance = nullptr;

bool SC_Console::Create()
{
	SC_ASSERT(!gInstance);
	gInstance = new SC_Console();
	return true;
}

void SC_Console::Destroy()
{
	delete gInstance;
	gInstance = nullptr;
}

SC_Console* SC_Console::Get()
{
	return gInstance;
}

void SC_Console::Update()
{

}

SC_Console::SC_Console()
{

}

SC_Console::~SC_Console()
{

}


#endif //ENABLE_CONSOLE
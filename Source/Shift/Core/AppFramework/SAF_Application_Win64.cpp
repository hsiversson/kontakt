//ProjectFilter(Windows)
#include "AppFramework_Precompiled.h"
#include "SAF_Application_Win64.h"

#if IS_WINDOWS_PLATFORM
#include "SC_CommandLine.h"

SAF_Application_Win64::SAF_Application_Win64()
{

}

SAF_Application_Win64::~SAF_Application_Win64()
{

}

bool SAF_Application_Win64::Init()
{
	if (!SC_CommandLine::Init(__argv, __argc))
		return false;

	if (!mWindow.Init())
		return false;

	return true;
}

bool SAF_Application_Win64::Update(SAF_ReturnCode& aOutReturnCode)
{
	{
		MSG msg = {};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return false;

			DispatchMessage(&msg);
		}
	}

	return SAF_Application::Update(aOutReturnCode);
}

#endif

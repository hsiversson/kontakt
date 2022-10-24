#include "AppFramework_Precompiled.h"
#include "SAF_Application.h"

SAF_Application* SAF_Application::Create(const SAF_ApplicationPlatform& aPlatform)
{
    switch(aPlatform)
    {
#if IS_WINDOWS_PLATFORM
    case SAF_ApplicationPlatform::Windows:
        return new SAF_Application_Win64();
#endif
#if IS_LINUX_PLATFORM
    case SAF_ApplicationPlatform::Linux:
        return new SAF_Application_Linux();
#endif
    default:
        return nullptr;
    }
}
#include "AppFramework_Precompiled.h"
#include "SAF_Application.h"

#if IS_WINDOWS_PLATFORM
    #include "SAF_Application_Win64.h"
#endif
#if IS_LINUX_PLATFORM
    #include "SAF_Application_Linux.h"
#endif

#include "SF_Manager.h"

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

SAF_Application::SAF_Application()
{

}

SAF_Application::~SAF_Application()
{

}

bool SAF_Application::Init()
{
    SF_Manager::Create();

    return true;
}

SAF_ReturnCode SAF_Application::Run()
{
    SAF_ReturnCode result = SAF_ReturnCode::OK;
    while (Update(result)) {}

    return result;
}

bool SAF_Application::Update(SAF_ReturnCode& aOutReturnCode)
{
    SF_Manager* facadeManager = SF_Manager::Get();
    // Facade Update

    // Facade Render
    facadeManager->Render();

    aOutReturnCode = SAF_ReturnCode::OK;
    return true;
}

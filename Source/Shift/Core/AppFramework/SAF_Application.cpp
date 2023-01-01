#include "AppFramework_Precompiled.h"
#include "SAF_Application.h"

#if IS_WINDOWS_PLATFORM
    #include "SAF_Application_Win64.h"
#endif
#if IS_LINUX_PLATFORM
    #include "SAF_Application_Linux.h"
#endif

#include "SR_RenderDevice.h"

#include "SF_Manager.h"

SAF_Application* SAF_Application::Create(const SAF_ApplicationPlatform& aPlatform, SAF_ApplicationInterface* aApplicationInterface)
{
    SC_Thread::RegisterMainThread();

    SAF_Application* app = nullptr;
    switch(aPlatform)
    {
#if IS_WINDOWS_PLATFORM
    case SAF_ApplicationPlatform::Windows:
        app = new SAF_Application_Win64();
        break;
#endif
#if IS_LINUX_PLATFORM
    case SAF_ApplicationPlatform::Linux:
		app = new SAF_Application_Linux();
		break;
#endif
    default:
        return nullptr;
    }

    app->SetInterface(aApplicationInterface);

    SC_WorkerPool::Init();

    return app;
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

    if (mApplicationInterface && !mApplicationInterface->Init())
        return false;

    return true;
}

SAF_ReturnCode SAF_Application::Run()
{
	SC_Time mTime(true);

    SAF_ReturnCode returnCode = SAF_ReturnCode::OK;
    bool result = true;
    while (result)
    {
        mTime.Tick();
        result = Update(returnCode);
    }

    return returnCode;
}

void SAF_Application::SetInterface(SAF_ApplicationInterface* aApplicationInterface)
{
    mApplicationInterface = aApplicationInterface;
}

bool SAF_Application::Update(SAF_ReturnCode& aOutReturnCode)
{
    // Simulation

	SR_RenderDevice::gInstance->BeginFrame();
    if (mApplicationInterface)
		mApplicationInterface->Update();

    // Prepare Rendering

    // Schedule Rendering
    // Post Start Render Frame Task
   // SR_RenderDevice::gInstance->BeginFrame();

    SR_RenderDevice::gInstance->EndFrame();
    SR_RenderDevice::gInstance->Present();

    aOutReturnCode = SAF_ReturnCode::OK;
    return true;
}

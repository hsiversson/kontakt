#include "SC_Base.h"

#include "SAF_Application.h"

#if IS_WINDOWS_PLATFORM
int WINAPI WinMain(_In_ HINSTANCE /*hInst*/, _In_opt_ HINSTANCE /*hInstPrev*/, _In_ LPSTR /*aCmdline*/, _In_ int /*aCmdShow*/)
{
	SIO_Path argv0(__argv[0]);
#else
int main(int aArgC, char* aArgV[])
{
	SIO_Path argv0(aArgV[0]);
#endif

	int returnCode = 0;

    {
#if IS_WINDOWS_PLATFORM
        SAF_Application* app = SAF_Application::Create(SAF_ApplicationPlatform::Windows);
#elif IS_LINUX_PLATFORM
        SAF_Application* app = SAF_Application::Create(SAF_ApplicationPlatform::Linux);
#else
        SAF_Application* app = nullptr;
#endif

        if (!app->Init())
            return -1;

        app->Run();
        // Create engine params
        // Init engine
        // Run loop
    }

    return returnCode;
}
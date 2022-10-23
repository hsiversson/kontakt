#include "SC_Base.h"

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
        // Create engine params
        // Init engine
        // Run loop
    }

    return returnCode;
}
//ProjectFilter(Windows)
#include "AppFramework_Precompiled.h"
#include "SAF_Window_Win64.h"

#if IS_WINDOWS_PLATFORM

static LRESULT CALLBACK	SAF_WndProc(HWND aHwnd, UINT aMsg, WPARAM aWPARAM, LPARAM aLPARAM);

static constexpr const char* gWindowClassName = "ShiftEngineWindowClassId";
static bool RegisterWindowClass()
{
    static bool initialized = false;

    if (initialized)
        return true;

    WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = SAF_WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(nullptr);
	wcex.hIcon = nullptr;//reinterpret_cast<HICON>(aParams.myNativeAppIcon);
	wcex.hCursor = nullptr;//mCursor;
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = gWindowClassName;
	wcex.hIconSm = 0;	//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (!RegisterClassEx(&wcex))
	{
		SC_ERROR("Register Window Class Failed with code: %d", GetLastError());
		return false;
	}

    initialized = true;
    return true;
}


SAF_Window_Win64::SAF_Window_Win64()
{

}

SAF_Window_Win64::~SAF_Window_Win64()
{

}

bool SAF_Window_Win64::Init(void* aParentWindowHandle)
{
	if (!RegisterWindowClass())
		return false;
	
	RECT windowRect = { 100, 100, 2560, 1440 };

    mWindowHandle = ::CreateWindow(
		gWindowClassName,
		"Kontakt",
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW,
		windowRect.left,
		windowRect.top,
		(windowRect.right - windowRect.left),
		(windowRect.bottom - windowRect.top),
		(HWND)aParentWindowHandle,
		nullptr,
		::GetModuleHandle(nullptr),
		nullptr
	);

	if (!mWindowHandle)
		return false;

	if (::IsIconic(mWindowHandle))
		ShowWindow(mWindowHandle, SW_RESTORE);

	::UpdateWindow(mWindowHandle);

	::ShowWindow(mWindowHandle, SW_SHOW);
    return true;
}

//void SAF_Window_Win64::PostMessageToMainThread(uint32 aMsg, WPARAM aWPARAM, LPARAM aLPARAM)
//{
//	::PostThreadMessage(SC_Thread::GetMainThreadId(), aMsg, aWPARAM, aLPARAM);
//}

LRESULT CALLBACK SAF_WndProc(HWND aHwnd, UINT aMsg, WPARAM aWPARAM, LPARAM aLPARAM)
{
	switch(aMsg)
	{
	case WM_ENTERSIZEMOVE:
		return 0;
	case WM_EXITSIZEMOVE:
		return 0;
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(aHwnd, aMsg, aWPARAM, aLPARAM);
	}
}

#endif
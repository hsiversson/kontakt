//ProjectFilter(Windows)
#include "AppFramework_Precompiled.h"
#include "SAF_Window_Win64.h"

#if IS_WINDOWS_PLATFORM

static constexpr const wchar_t* gWindowClassName = L"ShiftEngineWindowClassId";

static LRESULT CALLBACK	SAF_WndProc(HWND aHwnd, UINT aMsg, WPARAM aWPARAM, LPARAM aLPARAM);

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
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = nullptr;//reinterpret_cast<HICON>(aParams.myNativeAppIcon);
	wcex.hCursor = mCursor;
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

bool SAF_Window_Win64::Init()
{
    // Register window class

    mWindowHandle = ::CreateWindow(
		SAF_WindowThread_Win64::Get()->GetWndClassName(),
		name.c_str(),
		windowStyle,
		windowRect.left,
		windowRect.top,
		(windowRect.right - windowRect.left),
		(windowRect.bottom - windowRect.top),
		(HWND)aParentWindowHandle,
		nullptr,
		::GetModuleHandle(NULL),
		nullptr
	);

    return true;
}

LRESULT CALLBACK SAF_WndProc(HWND aHwnd, UINT aMsg, WPARAM aWPARAM, LPARAM aLPARAM)
{
	switch(aMsg)
	{
	case WM_ENTERSIZEMOVE:
		return 0;
	case WM_EXITSIZEMOVE:
		return 0;
	default:
		return DefWindowProcW(aHwnd, aMsg, aWPARAM, aLPARAM);
	}
}

#endif
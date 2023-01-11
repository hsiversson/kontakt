//ProjectFilter(Windows)
#include "AppFramework_Precompiled.h"
#include "SAF_Window_Win64.h"
#include "SF_Manager.h"

#if IS_WINDOWS_PLATFORM

static LRESULT CALLBACK	SAF_WndProc(HWND aHwnd, UINT aMsg, WPARAM wParam, LPARAM lParam);

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

HWND SAF_Window_Win64::GetHandle() const
{
	return mWindowHandle;
}

//void SAF_Window_Win64::PostMessageToMainThread(uint32 aMsg, WPARAM aWPARAM, LPARAM aLPARAM)
//{
//	::PostThreadMessage(SC_Thread::GetMainThreadId(), aMsg, aWPARAM, aLPARAM);
//}

LRESULT CALLBACK SAF_WndProc(HWND aHwnd, UINT aMsg, WPARAM wParam, LPARAM lParam)
{
	switch(aMsg)
	{
	case WM_ENTERSIZEMOVE:
		// Start Move
		return 0;
	case WM_EXITSIZEMOVE:
		// End Move
		return 0;

	case WM_WINDOWPOSCHANGED:
		// HandlePositionChangedMessage
		return 0;

	case WM_WINDOWPOSCHANGING:
		//HandlePositionChangingMessage
		break;

	case WM_SETCURSOR:
		if (LOWORD(lParam) == HTCLIENT)
		{
			//::SetCursor(cursor);
			return 1;
		}
		break;

	case WM_CLOSE:

		//if (isMainWindow)
			PostQuitMessage(0);
		//else
			//destroy child window
		return 0;

	default:
		break;
	}

	if (SF_Manager* facadeManager = SF_Manager::Get())
		facadeManager->WindowProc(aHwnd, aMsg, wParam, lParam);

	return DefWindowProc(aHwnd, aMsg, wParam, lParam);
}

#endif
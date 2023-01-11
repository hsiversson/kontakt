//ProjectFilter(Windows)
#pragma once

#if IS_WINDOWS_PLATFORM

class SR_SwapChain;
class SAF_Window_Win64
{
    friend class SAF_Application_Win64;
public:
    SAF_Window_Win64();
    ~SAF_Window_Win64();

    bool Init(void* aParentWindowHandle = nullptr);

    HWND GetHandle() const;

private:
    void PostMessageToMainThread(uint32 aMsg, WPARAM wParam, LPARAM lParam);

	HWND mWindowHandle;
	SC_Ref<SR_SwapChain> mSwapChain;
};

#endif
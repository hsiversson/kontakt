//ProjectFilter(Windows)
#pragma once

#if IS_WINDOWS_PLATFORM

class SAF_Window_Win64
{
public:
    SAF_Window_Win64();
    ~SAF_Window_Win64();

    bool Init(void* aParentWindowHandle = nullptr);

private:
    void PostMessageToMainThread(uint32 aMsg, WPARAM aWPARAM, LPARAM aLPARAM);

	HWND mWindowHandle;
};

#endif
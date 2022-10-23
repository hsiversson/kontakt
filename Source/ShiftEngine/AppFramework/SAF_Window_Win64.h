#pragma once

#if IS_WINDOWS_PLATFORM

class SAF_Window_Win64
{
public:
    SAF_Window_Win64();
    ~SAF_Window_Win64();

    bool Init();

private:

	HWND mWindowHandle;
};

#endif
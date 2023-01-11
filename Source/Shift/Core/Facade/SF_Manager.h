#pragma once

class SF_BaseRenderer;
class SF_InputManager;

class SF_Manager
{
public:
	SF_Manager();
	~SF_Manager();

	bool Init(void* aWindowHandle);

	void Update();

	void Render();

	static bool Create();
	static void Destroy();
	static SF_Manager* Get();

#if IS_WINDOWS_PLATFORM
	void WindowProc(HWND aHwnd, UINT aMsg, WPARAM wParam, LPARAM lParam);
#endif //IS_WINDOWS_PLATFORM

private:
	SC_Ptr<SF_BaseRenderer> mRenderer;
	SC_Ptr<SF_InputManager> mInputManager;

	static SF_Manager* gInstance;
};


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

private:
	SC_Ptr<SF_BaseRenderer> mRenderer;
	SC_Ptr<SF_InputManager> mInputManager;

	static SF_Manager* gInstance;
};


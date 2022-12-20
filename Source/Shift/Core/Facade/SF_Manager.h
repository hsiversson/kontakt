#pragma once

class SF_BaseRenderer;

class SF_Manager
{
public:
	SF_Manager();
	~SF_Manager();

	bool Init(void* aWindowHandle);

	void Render();

	static bool Create();
	static void Destroy();
	static SF_Manager* Get();

private:
	SC_Ptr<SF_BaseRenderer> mRenderer;

	static SF_Manager* gInstance;
};


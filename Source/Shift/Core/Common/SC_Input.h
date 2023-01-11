//ProjectFilter(Input)
#pragma once

class SC_Input
{
public:
	static bool Create(void* aNativeWindowHandle = nullptr, uint32 aFlags = 0, uint32 aMode = 0);
	static void Destroy();
	static SC_Input* Get();

	void Update();

private:
	SC_Input();
	~SC_Input();

	bool Init(void* aNativeWindowHandle, uint32 aFlags, uint32 aMode);

	static SC_Input* gInstance;
};


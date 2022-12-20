//ProjectFilter(Platform)
#pragma once

class SC_Time
{
public:
	static void Create();
	static void Destroy();
	static SC_Time* Get();

private:
	SC_Time();
	~SC_Time();

	static SC_Time* gInstance;
};


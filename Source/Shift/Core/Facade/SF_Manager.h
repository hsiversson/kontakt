#pragma once

class SF_Manager
{
public:
	SF_Manager();
	~SF_Manager();

	void Render();

	static bool Create();
	static void Destroy();
	static SF_Manager* Get();
private:

	static SF_Manager* gInstance;
};


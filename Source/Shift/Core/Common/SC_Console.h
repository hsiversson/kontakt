#pragma once

#if ENABLE_CONSOLE

class SC_Console
{
public:
	enum class State
	{
		NotActive,
		Default,
		Half,
	};

public:
	static bool Create();
	static void Destroy();
	static SC_Console* Get();

	void Update();

private:
	SC_Console();
	~SC_Console();

	static SC_Console* gInstance;
};

#endif //SC_ENABLE_CONSOLE
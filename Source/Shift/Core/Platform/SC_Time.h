//ProjectFilter(Platform)
#pragma once
#include <chrono>

class SC_Time
{
public:
	SC_Time(bool aIsMainTimer = false);
	~SC_Time();

	void Tick();

	static float gTimeDelta; // Time elapsed since the last frame. (In seconds)
	static float gElapsedTime; // Time since the application started. (In seconds)
	static uint32 gFrameIndex;

private:
	std::chrono::high_resolution_clock::time_point mLastFrameTick;

	const bool mIsMain;
};

class SC_StopWatch
{
public:
	SC_StopWatch(const char* aTag);

	void Stop();
private:
	const char* mTag;
	std::chrono::high_resolution_clock::time_point mStart;
};
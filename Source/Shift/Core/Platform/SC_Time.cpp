//ProjectFilter(Platform)
#include "Platform_Precompiled.h"
#include "SC_Time.h"

using secf = std::chrono::duration<float>;
using millisecf = std::chrono::duration<float, std::milli>;
using millisecu = std::chrono::duration<uint32, std::milli>;

float SC_Time::gTimeDelta = 0.0f;
float SC_Time::gElapsedTime = 0.0f;
uint32 SC_Time::gFrameIndex = 0;

SC_Time::SC_Time(const bool aIsMainTimer)
	: mIsMain(aIsMainTimer)
{

}

SC_Time::~SC_Time()
{

}

void SC_Time::Tick()
{

	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration dur = (now - mLastFrameTick);
	float delta = std::chrono::duration_cast<secf>(dur).count();

	if (mIsMain)
	{
		gTimeDelta = delta;
		gElapsedTime += delta;
		++gFrameIndex;
	}

	mLastFrameTick = now;
}

SC_StopWatch::SC_StopWatch(const char* aTag)
	: mTag(aTag)
{
	mStart = std::chrono::high_resolution_clock::now();
}

void SC_StopWatch::Stop()
{
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::duration dur = (now - mStart);
	float deltaMS = std::chrono::duration_cast<millisecf>(dur).count();

	std::string msg(mTag);
	msg += ": ";
	msg += std::to_string(deltaMS);
	msg += " ms\n";
	OutputDebugString(msg.c_str());
}

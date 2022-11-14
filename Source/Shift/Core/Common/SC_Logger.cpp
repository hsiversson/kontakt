//ProjectFilter(Debugging)
#include "Common_Precompiled.h"
#include "SC_Logger.h"

#if ENABLE_LOGS

void SC_Logger::Create()
{
}

void SC_Logger::Destroy()
{
}

void SC_Logger::LogMessage(const SC_LogType& /*aType*/, const std::string& /*aMsg*/, const char* /*aFunc*/, bool /*aFlush*/)
{
}

SC_Logger::SC_Logger()
{
}

SC_Logger::~SC_Logger()
{
}

#endif
//ProjectFilter(Debug)
#include "Platform_Precompiled.h"
#include "SC_Assert.h"

bool SC_Assert(const char* /*aFile*/, int /*aLine*/, const char* /*aString*/)
{
    return true;
}

bool SC_Assert(const char* /*aFile*/, int /*aLine*/, const char* /*aString*/, const char* /*aFmtString*/, ...)
{
    return true;
}

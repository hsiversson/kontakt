//ProjectFilter(Async)
#pragma once
#include "SC_GlobalDefines.h"

#if IS_WINDOWS_PLATFORM
#include "SC_Atomics_Win64.h"
#else
#error PLATFORM NOT SUPPORTED!
#endif


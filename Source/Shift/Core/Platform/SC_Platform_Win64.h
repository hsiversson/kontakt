//ProjectFilter(Platform)
#pragma once

#ifndef __SC_PLATFORM_HEADER__
	#error Please include "SC_Platform.h" instead.
#endif

#if IS_WINDOWS_PLATFORM

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
	#define NOMINMAX
#endif

	#include <windows.h>
#endif
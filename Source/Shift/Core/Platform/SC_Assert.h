//ProjectFilter(Debug)
#pragma once

#include "SC_GlobalDefines.h"
#include <cassert>
#undef assert

#if IS_MSVC_COMPILER
	#define SC_DEBUG_BREAK()	__debugbreak()
#else
	#error Not supported on this platform yet
#endif

bool SC_Assert(const char* aFile, int aLine, const char* aString);
bool SC_Assert(const char* aFile, int aLine, const char* aString, const char* aFmtString, ...);

#define SC_FORCE_ASSERT(aCondition, ...)									\
	do																		\
	{																		\
		if(!aCondition)														\
		{																	\
			if(SC_Assert(__FILE__, __LINE__, (#aCondition), ##__VA_ARGS__)) \
				SC_DEBUG_BREAK();											\
		}																	\
	} while(0)
		

#define SC_ASSERT(aCondition, ...) SC_FORCE_ASSERT((aCondition), ##__VA_ARGS__)
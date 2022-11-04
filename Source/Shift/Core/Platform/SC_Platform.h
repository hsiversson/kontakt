//ProjectFilter(Platform)
#pragma once
#define __SC_PLATFORM_HEADER__

#include "SC_GlobalDefines.h"

#define SC_STRINGIFY2(aStr)					#aStr
#define SC_STRINGIFY(aStr)					SC_STRINGIFY2(aStr)
#define SC_UNUSED(aIdentifier)				(static_cast<void>(aIdentifier))
#define SC_CONCAT2(a, b)					a ## b
#define SC_CONCAT(a, b)						SC_CONCAT2(a, b)
#define SC_STATIC_ASSERT(aCond, aMsg)		static_assert( aCond, #aMsg )
#define SC_ARRAY_SIZE(aArray)				(sizeof(aArray) / sizeof(*aArray))

#if IS_MSVC_COMPILER

	#define SC_FORCEINLINE					__forceinline
	#define SC_NOINLINE						__declspec(noinline)
	#define SC_OPTIMIZE_OFF					__pragma(optimize("", off))
	#define SC_OPTIMIZE_ON					__pragma(optimize("", on))
	#define SC_DEPRECATED					__declspec(deprecated)
	#define SC_DEPRECATED_MSG(aMsg)			__declspec(deprecated(aMsg))
	#define SC_RESTRICT						__restrict
	#define SC_FASTCALL						__fastcall
	#define SC_ALIGN(aValue)				__declspec(align(aValue))
	#define SC_NOVTABLE						__declspec(novtable)

#elif IS_CLANG_COMPILER

	#define SC_FORCEINLINE					inline __attribute((always_inline))
	#define SC_NOINLINE						__attribute((noinline))
	#define SC_OPTIMIZE_OFF					_Pragma("clang optimize off")
	#define SC_OPTIMIZE_ON					_Pragma("clang optimize on")
	#define SC_DEPRECATED					__attribute__((deprecated))
	#define SC_DEPRECATED_MSG(aMsg)			__attribute__((deprecated(aMsg)))
	#define SC_RESTRICT						__restrict__
	#define SC_FASTCALL						
	#define SC_ALIGN(aValue)				__attribute__((__aligned__(aValue)))
	#define SC_NOVTABLE				

#elif IS_GCC_COMPILER

	#define SC_FORCEINLINE					inline __attribute((always_inline))
	#define SC_NOINLINE						__attribute((noinline))
	#define SC_OPTIMIZE_OFF					__attribute__((optimize("O0")))
	#define SC_OPTIMIZE_ON					__attribute__((optimize("O3")))
	#define SC_DEPRECATED					__attribute__((deprecated))
	#define SC_DEPRECATED_MSG(aMsg)			__attribute__((deprecated(aMsg)))
	#define SC_RESTRICT						__restrict__
	#define SC_FASTCALL						
	#define SC_ALIGN(aValue)				__attribute__((__aligned__(aValue)))
	#define SC_NOVTABLE

#else
	#error Compiler not supported!
#endif

#if IS_WINDOWS_PLATFORM
	#include "SC_Platform_Win64.h"
#elif IS_LINUX_PLATFORM
	#include "SC_Platform_Linux.h"
#endif

#include "SC_Assert.h"
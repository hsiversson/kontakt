#pragma once

#include "d3d12.h"
#include <dxgi1_6.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")

#if ENABLE_PIX
	#define USE_PIX (1)

	#if !IS_RETAIL_BUILD
		#define USE_PIX_RETAIL (1)
	#endif

	#pragma warning(push)
	#pragma warning(disable:6101)
	#include "WinPixEventRuntime/pix3.h"
	#pragma warning(pop)
#endif

// For COM interface (ComPtr)
#include <wrl.h>

template<class T>
using SR_ComPtr = Microsoft::WRL::ComPtr<T>; 
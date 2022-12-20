//ProjectFilter(DX12)
#pragma once

#if SR_ENABLE_DX12
#include "d3d12.h"
#include "d3d12shader.h"
#include <dxgi1_6.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")

#if SR_ENABLE_PIX
	#define USE_PIX (1)

	#if !IS_RETAIL_BUILD
		#define USE_PIX_RETAIL (1)
	#endif

	#pragma warning(push)
	#pragma warning(disable:6101)
	//#include "WinPixEventRuntime/pix3.h"
	#pragma warning(pop)
#endif

// For COM interface (ComPtr)
#include <wrl.h>

template<class T>
using SR_ComPtr = Microsoft::WRL::ComPtr<T>; 

inline const char* SR_GetRemovedReasonString(HRESULT aValue)
{
	switch (aValue)
	{
	case DXGI_ERROR_DEVICE_HUNG: return "Device Hung";
	case DXGI_ERROR_DEVICE_RESET: return "Device Reset";
	case DXGI_ERROR_DEVICE_REMOVED: return "Device Removed";
	case DXGI_ERROR_DRIVER_INTERNAL_ERROR: return "Internal Driver Error";
	case DXGI_ERROR_INVALID_CALL: return "Invalid Call";
	case S_OK: return "S_OK";
	}

	return "<unknown value>";
}

inline bool SR_VerifyHRESULT(const HRESULT& aHRESULT)
{
	//bool outputDebugData = false;

	switch (aHRESULT)
	{
	case E_INVALIDARG:
		SC_ERROR("[DX12 ERROR]: Invalid Args");
		return false;
	case E_OUTOFMEMORY:
		SC_ERROR("[DX12 ERROR]: Out Of Memory");
		return false;
	case DXGI_ERROR_INVALID_CALL:
		SC_ERROR("[DX12 ERROR]: Invalid Call");
		return false;
	case DXGI_ERROR_UNSUPPORTED:
		SC_ERROR("[DX12 ERROR]: Unsupported Feature Used");
		return false;
	case DXGI_ERROR_DEVICE_HUNG:
		SC_ERROR("[DXGI ERROR]: Device Hung");
		//outputDebugData = true;
		break;
	case DXGI_ERROR_DEVICE_REMOVED:
		SC_ERROR("[DXGI ERROR]: Device Removed");
		//SC_ERROR("Removed Reason: {}", SR_GetRemovedReasonString(SR_RenderDevice_DX12::gInstance->GetD3D12Device()->GetDeviceRemovedReason()));
		//outputDebugData = true;
		break;
	case S_OK:
	case S_FALSE:
		return true;
	default:
		SC_ERROR("[DX12 ERROR]: Unknown Reason ({:0x})", aHRESULT);
		return false;
	}

	//if (outputDebugData)
	//{
	//}

	SC_ASSERT(false);
	return false;
}

#include "SR_Convert_DX12.h"
#endif
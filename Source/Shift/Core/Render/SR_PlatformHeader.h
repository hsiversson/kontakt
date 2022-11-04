#pragma once
#include "SR_RenderDefines.h"

#if SR_ENABLE_DX12
	#include "SR_PlatformHeader_DX12.h"
#endif

#if SR_ENABLE_VULKAN
	#include "SR_PlatformHeader_Vk"
#endif
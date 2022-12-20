//ProjectFilter(Interface)
#pragma once
#include "SR_RenderEnums.h"

enum class SR_GpuVendor
{
	Unknown,
	Nvidia,
	AMD,
	Intel
};
enum class SR_GpuArchitecture
{
	Unknown,

	Nv_Kepler,
	Nv_Maxwell,
	Nv_Pascal,
	Nv_Turing,
	Nv_Volta = Nv_Turing,
	Nv_Ampere,
	Nv_Lovlace,
	Nv_Hopper = Nv_Lovlace,

	Amd_GCN1,
	Amd_GCN2,
	Amd_GCN3,
	Amd_GCN4,
	Amd_Vega,
	Amd_RDNA,
	Amd_RDNA2,
	Amd_RDNA3,

	Intel_Xe,
	Intel_Xe2,
	Intel_Xe3,
};

struct SR_DeviceInfo
{
	std::string mDeviceName;
	std::string mDriverVersionString;
	uint32 mDriverVersion;

	SR_GpuVendor mVendor;
	SR_GpuArchitecture mArchitecture;

	uint32 mDedicatedVRAM; // in Megabytes
	uint32 mNumShaderCores;
	float mTheoreticalMaxPerformance; // in TFLOPS
};

struct SR_DeviceCapabilities
{
	SR_DeviceInfo mDeviceInfo;
	SR_ShaderModel mHighestShaderModel;
	bool mAsyncCompute : 1;
	bool mAsyncCopy : 1;
	bool mMeshShaders : 1;
	bool mVariableRateShading : 1;
	bool mSamplerFeedback : 1;
	bool mConservativeRasterization : 1;
	bool mRaytracing : 1;
	bool mInlineRaytracing : 1;
};
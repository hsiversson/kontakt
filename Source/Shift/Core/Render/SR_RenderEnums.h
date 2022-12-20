//ProjectFilter(Interface)
#pragma once
#include "SR_RenderDefines.h"

enum class SR_API
{
	Unknown,
#if SR_ENABLE_DX12
	D3D12,
#endif
#if SR_ENABLE_VULKAN
	Vulkan,
#endif
};

enum class SR_ShaderModel
{
	Unknown,
	SM_5_1,
	SM_6_0,
	SM_6_1,
	SM_6_2,
	SM_6_3,
	SM_6_4,
	SM_6_5,
	SM_6_6,
	SM_6_7,
};

enum class SR_ShaderType
{
	Vertex,
#if SR_ENABLE_MESH_SHADERS
	Mesh,
	Amplification,
#endif
	Pixel,
	Compute,
#if SR_ENABLE_RAYTRACING
	Raytracing,
#endif
	COUNT,
	Unknown = COUNT
};
static constexpr uint32 SR_ShaderType_COUNT = static_cast<uint32>(SR_ShaderType::COUNT);

enum class SR_RootSignatureType
{
	Graphics,
	GraphicsMS,
	Compute,
#if SR_ENABLE_RAYTRACING
	Raytracing,
#endif
	COUNT
};
static constexpr uint32 SR_RootSignatureType_COUNT = static_cast<uint32>(SR_RootSignatureType::COUNT);

enum class SR_CommandListType
{
	Graphics,
	Compute,
	Copy,
	COUNT = 3,
	Unknown = COUNT,
};
static constexpr uint32 SR_CommandListType_COUNT = static_cast<uint32>(SR_CommandListType::COUNT);

enum class SR_DescriptorType
{
	SRV,
	CBV,
	UAV,
	RTV,
	DSV,
	Sampler
};

enum class SR_StencilOperator
{
	Keep,
	Zero,
	Replace,
	IncrementSaturate,
	DecrementSaturate,
	Invert,
	Increment,
	Decrement,
	COUNT,
};
static constexpr uint32 SR_StencilOperator_COUNT = static_cast<uint32>(SR_StencilOperator::COUNT);

enum class SR_ComparisonFunc
{
	Never,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always,
	COUNT,
};
static constexpr uint32 SR_ComparisonFunc_COUNT = static_cast<uint32>(SR_ComparisonFunc::COUNT);

enum class SR_CullMode
{
	None,
	Front,
	Back,
	COUNT,
};
static constexpr uint32 SR_CullMode_COUNT = static_cast<uint32>(SR_CullMode::COUNT);

enum class SR_BlendFunc
{
	Add,
	Subtract,
	ReverseSubtract,
	Min,
	Max,
	COUNT,
};
static constexpr uint32 SR_BlendFunc_COUNT = static_cast<uint32>(SR_BlendFunc::COUNT);

enum class SR_BlendMode
{
	Zero,
	One,
	SrcColor,
	OneMinusSrcColor,
	SrcAlpha,
	OneMinusSrcAlpha,
	DstColor,
	OneMinusDstColor,
	DstAlpha,
	OneMinusDstAlpha,
	SrcAlphaSaturate,
	BlendFactor,
	OneMinusBlendFactor,
	Src1Color,
	OneMinusSrc1Color,
	Src1Alpha,
	OneMinusSrc1Alpha,
	COUNT,
};
static constexpr uint32 SR_BlendMode_COUNT = static_cast<uint32>(SR_BlendMode::COUNT);

enum class SR_ColorWriteMask
{
	None = (0),
	Red = (1 << 0),
	Green = (1 << 1),
	Blue = (1 << 2),
	Alpha = (1 << 3),
	RGB = (Red | Green | Blue),
	RGBA = (Red | Green | Blue | Alpha),
};

enum class SR_PrimitiveTopology
{
	TriangleList,
	LineList,
	LineStrip,
	PointList,
};

enum class SR_WrapMode
{
	Wrap = 0,
	Clamp,
	Mirror,
	MirrorOnce,
	Border,
	COUNT
};
static constexpr uint32 SR_WrapMode_COUNT = static_cast<uint32>(SR_WrapMode::COUNT);

enum class SR_FilterMode
{
	Point = 0,
	Linear,
	Min,
	Max,
	COUNT
};
static constexpr uint32 SR_FilterMode_COUNT = static_cast<uint32>(SR_FilterMode::COUNT);

enum class SR_ResourceType
{
	Unknown,
	Texture1D,
	Texture2D,
	Texture3D,
	Buffer
};

enum class SR_ShadingRate
{
	VRS_1X1,
	VRS_1X2,
	VRS_2X1,
	VRS_2X2,
};

enum class SR_DepthClearFlags
{
	Depth,
	Stencil,
	All,
};

enum SR_ResourceStates : uint32
{
	SR_ResourceState_GenericRead,
	SR_ResourceState_Present,
	SR_ResourceState_RenderTarget,
	SR_ResourceState_ShaderRead,
	SR_ResourceState_ShaderWrite,
	SR_ResourceState_Indirect,
	SR_ResourceState_Readback,
	SR_ResourceState_CopyDst,
	SR_ResourceState_CopySrc,
};

enum SR_BufferBindFlag : uint32
{
	SR_BufferBindFlag_None = 0,
	SR_BufferBindFlag_Staging = 0x1,
	SR_BufferBindFlag_VertexBuffer = 0x2,
	SR_BufferBindFlag_IndexBuffer = 0x4,
	SR_BufferBindFlag_ConstantBuffer = 0x8,
	SR_BufferBindFlag_Buffer = 0x10,
	SR_BufferBindFlag_IndirectBuffer = 0x20,
	SR_BufferBindFlag_RaytracingBuffer = 0x40,
	SR_BufferBindFlag_Readback = 0x80,
	SR_BufferBindFlag_COUNT = 6,
};
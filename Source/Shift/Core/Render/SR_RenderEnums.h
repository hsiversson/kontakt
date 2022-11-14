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
	COUNT
};

enum class SR_CommandListType
{
	Graphics,
	Compute,
	Copy,
	COUNT = 3,
	Unknown = COUNT,
};

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

enum class SR_CullMode
{
	None,
	Front,
	Back,
	COUNT,
};

enum class SR_BlendFunc
{
	Add,
	Subtract,
	ReverseSubtract,
	Min,
	Max,
	COUNT,
};

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

enum class SR_FilterMode
{
	Point = 0,
	Linear,
	Min,
	Max,
	COUNT
};

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
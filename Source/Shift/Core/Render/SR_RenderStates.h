//ProjectFilter(Interface)
#pragma once
#include "SR_RenderEnums.h"
#include "SR_Format.h"

////////////////////////////////////////////////
// Rasterizer State
// 
struct SR_RasterizerStateProperties
{
	int32 mDepthBias;
	float mDepthBiasClamp;
	float mSlopedScaleDepthBias;

	SR_CullMode mCullMode;

	bool mEnableDepthClip;
	bool mConservativeRaster;
	bool mWireframe;
	bool mCounterClockWise;

	SR_RasterizerStateProperties()
		: mDepthBias(0)
		, mDepthBiasClamp(0.0f)
		, mSlopedScaleDepthBias(0.0f)
		, mCullMode(SR_CullMode::Back)
		, mEnableDepthClip(true)
		, mConservativeRaster(false)
		, mWireframe(false)
		, mCounterClockWise(false)
	{}
};

struct SR_RasterizerState
{
	const SR_RasterizerStateProperties mProperties;
	const uint32 mKey;

	SR_RasterizerState(const SR_RasterizerStateProperties& aProperties) : mProperties(aProperties), mKey(0) {}
};

////////////////////////////////////////////////
// Blend State
// 
struct SR_RenderTargetBlendProperties
{
	bool mEnableBlend;
	uint8 mWriteMask;

	SR_BlendMode mSrcBlend;
	SR_BlendMode mDstBlend;
	SR_BlendFunc mBlendFunc;

	SR_BlendMode mSrcBlendAlpha;
	SR_BlendMode mDstBlendAlpha;
	SR_BlendFunc mBlendFuncAlpha;

	SR_RenderTargetBlendProperties()
		: mEnableBlend(false)
		, mWriteMask((uint8)SR_ColorWriteMask::RGBA)
		, mSrcBlend(SR_BlendMode::SrcAlpha)
		, mDstBlend(SR_BlendMode::OneMinusSrcAlpha)
		, mBlendFunc(SR_BlendFunc::Add)
		, mSrcBlendAlpha(SR_BlendMode::Zero)
		, mDstBlendAlpha(SR_BlendMode::One)
		, mBlendFuncAlpha(SR_BlendFunc::Add)
	{
	}
};

struct SR_BlendStateProperties
{
	uint8 mNumRenderTargets;
	SR_RenderTargetBlendProperties mRenderTagetBlendProperties[SR_MAX_RENDER_TARGETS];
	bool mAlphaToCoverage;

	SR_BlendStateProperties()
		: mNumRenderTargets(0)
		, mAlphaToCoverage(false)
	{}

	static SR_RenderTargetBlendProperties AlphaBlendProperties()
	{
		SR_RenderTargetBlendProperties alphaBlendProps;
		alphaBlendProps.mEnableBlend = true;
		alphaBlendProps.mBlendFunc = SR_BlendFunc::Add;
		alphaBlendProps.mSrcBlend = SR_BlendMode::SrcAlpha;
		alphaBlendProps.mDstBlend = SR_BlendMode::OneMinusSrcAlpha;
		alphaBlendProps.mBlendFuncAlpha = SR_BlendFunc::Add;
		alphaBlendProps.mSrcBlendAlpha = SR_BlendMode::One;
		alphaBlendProps.mDstBlendAlpha = SR_BlendMode::OneMinusSrcAlpha;
		return alphaBlendProps;
	}

	static SR_RenderTargetBlendProperties PremultipliedAlphaBlendProperties()
	{
		SR_RenderTargetBlendProperties alphaBlendProps;
		alphaBlendProps.mEnableBlend = true;
		alphaBlendProps.mBlendFunc = SR_BlendFunc::Add;
		alphaBlendProps.mSrcBlend = SR_BlendMode::One;
		alphaBlendProps.mDstBlend = SR_BlendMode::OneMinusSrcAlpha;
		alphaBlendProps.mBlendFuncAlpha = SR_BlendFunc::Add;
		alphaBlendProps.mSrcBlendAlpha = SR_BlendMode::One;
		alphaBlendProps.mDstBlendAlpha = SR_BlendMode::One;
		return alphaBlendProps;
	}

	static SR_RenderTargetBlendProperties AdditiveProperties()
	{
		SR_RenderTargetBlendProperties additiveProps;
		additiveProps.mEnableBlend = true;
		additiveProps.mBlendFunc = SR_BlendFunc::Add;
		additiveProps.mSrcBlend = SR_BlendMode::SrcAlpha;
		additiveProps.mDstBlend = SR_BlendMode::One;
		additiveProps.mBlendFuncAlpha = SR_BlendFunc::Add;
		additiveProps.mSrcBlendAlpha = SR_BlendMode::Zero;
		additiveProps.mDstBlendAlpha = SR_BlendMode::One;
		return additiveProps;
	}
};

struct SR_BlendState
{
	const SR_BlendStateProperties mProperties;
	const uint32 mKey;

	SR_BlendState(const SR_BlendStateProperties& aProperties) : mProperties(aProperties), mKey(0) {}
};

////////////////////////////////////////////////
// Depth Stencil State
//
struct SR_StencilProperties
{
	SR_StencilOperator mFail;
	SR_StencilOperator mDepthFail;
	SR_StencilOperator mPass;
	SR_ComparisonFunc mComparisonFunc;

	SR_StencilProperties()
		: mFail(SR_StencilOperator::Keep)
		, mDepthFail(SR_StencilOperator::Keep)
		, mPass(SR_StencilOperator::Keep)
		, mComparisonFunc(SR_ComparisonFunc::Always)
	{}
};

struct SR_DepthStencilStateProperties
{
	bool mWriteDepth;
	SR_ComparisonFunc mDepthComparisonFunc;

	bool mEnableStencil;
	uint8 mStencilReadMask;
	uint8 mStencilWriteMask;
	SR_StencilProperties mFrontFace;
	SR_StencilProperties mBackFace;

	SR_DepthStencilStateProperties()
		: mWriteDepth(false)
		, mDepthComparisonFunc(SR_ComparisonFunc::Always)
		, mEnableStencil(false)
		, mStencilReadMask(0xff)
		, mStencilWriteMask(0xff)
	{}
};

struct SR_DepthStencilState
{
	const SR_DepthStencilStateProperties mProperties;
	const uint32 mKey;

	SR_DepthStencilState(const SR_DepthStencilStateProperties& aProperties) : mProperties(aProperties), mKey(0) {}
};

////////////////////////////////////////////////
// Render Target Formats
//
struct SR_RenderTargetFormats
{
	uint8 mNumColorFormats;
	SR_Format mColorFormats[SR_MAX_RENDER_TARGETS];
	SR_Format mDepthFormat;

	SR_RenderTargetFormats()
		: mNumColorFormats(0)
		, mDepthFormat(SR_Format::D32_FLOAT)
	{
		for (uint32 i = 0; i < SR_MAX_RENDER_TARGETS; ++i)
			mColorFormats[i] = SR_Format::UNKNOWN;
	}
};

////////////////////////////////////////////////
// Sampler
//
struct SR_SamplerProperties
{
	SR_SamplerProperties(SR_FilterMode aFilter = SR_FilterMode::Linear, SR_WrapMode aWrapMode = SR_WrapMode::Wrap)
		: mBorderColor(0), mLODBias(0)
		, mMinFilter(aFilter), mMagFilter(aFilter), mMipFilter(aFilter)
		, mWrapX(aWrapMode), mWrapY(aWrapMode), mWrapZ(aWrapMode)
		, mMaxAnisotropy(gDefaultAnisotropy), mComparison(SR_ComparisonFunc::Never)
	{}

	bool operator==(const SR_SamplerProperties& aOther) const
	{
		return mBorderColor == aOther.mBorderColor && mLODBias == aOther.mLODBias &&
			mMinFilter == aOther.mMinFilter && mMagFilter == aOther.mMagFilter && mMipFilter == aOther.mMipFilter &&
			mWrapX == aOther.mWrapX && mWrapY == aOther.mWrapY && mWrapZ == aOther.mWrapZ &&
			mMaxAnisotropy == aOther.mMaxAnisotropy && mComparison == aOther.mComparison;
	}

	bool operator!=(const SR_SamplerProperties& aOther) const
	{
		return !(*this == aOther);
	}

	SC_Vector4 mBorderColor;
	float mLODBias;

	SR_FilterMode mMinFilter;
	SR_FilterMode mMagFilter;
	SR_FilterMode mMipFilter;

	SR_WrapMode mWrapX;
	SR_WrapMode mWrapY;
	SR_WrapMode mWrapZ;

	uint8 mMaxAnisotropy;

	SR_ComparisonFunc mComparison;

	static constexpr uint8 gDefaultAnisotropy = 255;
};

////////////////////////////////////////////////
// Misc
//
struct SR_Rect
{
	SR_Rect() : mLeft(0), mTop(0), mRight(0), mBottom(0) {}
	SR_Rect(const std::initializer_list<uint32>& aList) : mLeft(0), mTop(0), mRight(0), mBottom(0) { SC_Memcpy(&mLeft, aList.begin(), sizeof(uint32) * aList.size()); }

	SC_Vector2ui TopLeft() const { return SC_Vector2ui(mLeft, mTop); }
	SC_Vector2ui BottomRight() const { return SC_Vector2ui(mRight, mBottom); }
	SC_Vector2ui Size() const { return SC_Vector2ui(mRight - mLeft, mBottom - mTop); }

	uint32 mLeft;
	uint32 mTop;
	uint32 mRight;
	uint32 mBottom;
};
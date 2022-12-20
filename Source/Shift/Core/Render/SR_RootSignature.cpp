//ProjectFilter(Interface/Shader)
#include "Render_Precompiled.h"
#include "SR_RootSignature.h"

SR_RootSignature::SR_RootSignature(const SR_RootSignatureProperties& aProperties)
	: mProperties(aProperties)
{

}

SR_RootSignature::~SR_RootSignature()
{

}

bool SR_RootSignature::IsCompute() const
{
	return mProperties.mIsCompute;
}

const SR_RootSignatureProperties& SR_RootSignature::GetProperties() const
{
	return mProperties;
}

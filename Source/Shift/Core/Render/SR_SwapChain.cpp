//ProjectFilter(Interface)
#include "Render_Precompiled.h"
#include "SR_SwapChain.h"

SR_SwapChain::SR_SwapChain()
	: mCurrentResource(nullptr)
	, mCurrentIndex(0)
	, mNumBackbuffers(3)
{

}

SR_SwapChain::~SR_SwapChain()
{

}

bool SR_SwapChain::UpdateProperties(const SR_SwapChainProperties& aProperties)
{
	mProperties = aProperties;
	return true;
}

const SR_SwapChainProperties& SR_SwapChain::GetProperties() const
{
	return mProperties;
}

SR_Texture* SR_SwapChain::GetCurrentRenderTarget() const
{
	return mCurrentResource->mTexture;
}

SR_Texture* SR_SwapChain::GetCurrentTexture() const
{
	return mCurrentResource->mTexture;
}

//ProjectFilter(Interface)
//ProjectFilter(Interface)
#pragma once
#include "SR_Resource.h"

class SR_TextureResource;
class SR_Texture;

struct SR_SwapChainProperties
{
	SC_Vector2i mSize;
	SR_Format mFormat;

	bool mFullscreen;
	bool mTripleBuffer;
};

class SR_SwapChain : public SR_Resource
{
public:
	SR_SwapChain();
	virtual ~SR_SwapChain();

	virtual bool UpdateProperties(const SR_SwapChainProperties& aProperties);

	virtual void Present() = 0;

	const SR_SwapChainProperties& GetProperties() const;
	SR_Texture* GetCurrentRenderTarget() const;
	SR_Texture* GetCurrentTexture() const;

protected:
	struct BackbufferResource
	{
		SC_Ref<SR_TextureResource> mResource;
		SC_Ref<SR_Texture> mTexture;
	};

	SR_SwapChainProperties mProperties;
	BackbufferResource mBackbufferResources[3];
	BackbufferResource* mCurrentResource;
	uint32 mNumBackbuffers;
	uint32 mCurrentIndex;
};


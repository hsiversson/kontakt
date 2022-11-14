//ProjectFilter(Interface/Resources)
#include "Render_Precompiled.h"
#include "SR_TextureResource.h"

SR_TextureResource::~SR_TextureResource()
{

}

const SR_TextureResourceProperties& SR_TextureResource::GetProperties() const
{
    return mProperties;
}

SR_TextureResource::SR_TextureResource(const SR_TextureResourceProperties& aProperties)
	: mProperties(aProperties)
{

}

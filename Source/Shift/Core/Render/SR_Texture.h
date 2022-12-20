//ProjectFilter(Interface/Resources)
#pragma once

#include "SR_TextureResource.h"

enum SR_TextureBindFlags
{
	SR_TextureBindFlag_Texture = 1 << 0,
	SR_TextureBindFlag_RWTexture = 1 << 1,
	SR_TextureBindFlag_RenderTarget = 1 << 2,
	SR_TextureBindFlag_DepthStencil = 1 << 3
};

enum class SR_TextureDescriptorType
{
	Texture,
	RWTexture,
	RenderTarget,
	DepthStencil,
	COUNT
};

enum class SR_TextureDimension : uint8
{
    Texture1D,
    Texture2D,
    Texture3D,
    TextureCube
};

struct SR_TextureProperties : public SR_TextureSection
{
    SR_TextureProperties(const SR_Format& aFormat) : mFormat(aFormat), mDimension(SR_TextureDimension::Texture2D), mBindFlags(0) {}
    SR_TextureProperties(const SR_Format& aFormat, uint32 aBindFlags) : mFormat(aFormat), mDimension(SR_TextureDimension::Texture2D), mBindFlags(aBindFlags) {}

    SR_Format mFormat;
    SR_TextureDimension mDimension;
    uint32 mBindFlags;
};

class SR_Texture : public SR_Resource
{
public:
	virtual ~SR_Texture();

    const SR_TextureProperties& GetProperties() const;
    const SR_TextureResourceProperties& GetResourceProperties() const;
    SR_TextureResource* GetResource() const;

    const SR_Descriptor& GetDescriptor(const SR_TextureDescriptorType& aDescriptorType) const;
    uint32 GetDescriptorHeapIndex(const SR_TextureDescriptorType& aDescriptorType) const;

protected:
	SR_Texture(const SR_TextureProperties& aProperties, const SC_Ref<SR_TextureResource>& aResource);

    SR_TextureProperties mProperties;
    SC_StaticArray<SR_Descriptor, static_cast<uint32>(SR_TextureDescriptorType::COUNT)> mDescriptors;
    SC_Ref<SR_TextureResource> mResource;
};
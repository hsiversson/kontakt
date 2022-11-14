//ProjectFilter(Interface/Resources)
#pragma once

#include "SR_TextureResource.h"

enum class SR_TextureBindType : uint8
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
    SR_TextureProperties(const SR_Format& aFormat) : mFormat(aFormat), mDimension(SR_TextureDimension::Texture2D) {}

    SR_Format mFormat;
    SR_TextureDimension mDimension;
    bool mBindTypes[static_cast<uint8>(SR_TextureBindType::COUNT)];
};

class SR_Texture : public SR_Resource
{
public:
	virtual ~SR_Texture();

    const SR_TextureProperties& GetProperties() const;
    const SR_TextureResourceProperties& GetResourceProperties() const;
    SR_TextureResource* GetResource() const;

    const SR_Descriptor& GetDescriptor(const SR_TextureBindType& aDescriptorType) const;
    uint32 GetDescriptorHeapIndex(const SR_TextureBindType& aDescriptorType) const;

protected:
	SR_Texture(const SR_TextureProperties& aProperties, const SC_Ref<SR_TextureResource>& aResource);

    SR_TextureProperties mProperties;
    SR_Descriptor mDescriptors[static_cast<uint8>(SR_TextureBindType::COUNT)];
    SC_Ref<SR_TextureResource> mResource;
};
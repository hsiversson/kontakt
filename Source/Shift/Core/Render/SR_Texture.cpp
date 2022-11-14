//ProjectFilter(Interface/Resources)
#include "Render_Precompiled.h"
#include "SR_Texture.h"

SR_Texture::~SR_Texture()
{
	for (uint32 i = 0; i < static_cast<uint32>(SR_TextureBindType::COUNT); ++i)
	{
		if (i == SR_TextureBindType::RenderTarget)
			SR_RenderDevice::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::RTV)->Free(mDescriptors[i]);
		else if (i == SR_TextureBindType::DepthStencil)
			SR_RenderDevice::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::DSV)->Free(mDescriptors[i]);
		else
			SR_RenderDevice::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::Default)->Free(mDescriptors[i]);

	}
}

const SR_TextureProperties& SR_Texture::GetProperties() const
{
	return mProperties;
}

const SR_TextureResourceProperties& SR_Texture::GetResourceProperties() const
{
	return mResource->GetProperties();
}

SR_TextureResource* SR_Texture::GetResource() const
{
	return mResource;
}

const SR_Descriptor& SR_Texture::GetDescriptor(const SR_TextureBindType& aDescriptorType) const
{
	return mDescriptors[static_cast<uint32>(aDescriptorType)];
}

uint32 SR_Texture::GetDescriptorHeapIndex(const SR_TextureBindType& aDescriptorType) const
{
	return mDescriptors[static_cast<uint32>(aDescriptorType)].mHeapIndex;
}

SR_Texture::SR_Texture(const SR_TextureProperties& aProperties, const SC_Ref<SR_TextureResource>& aResource)
	: mProperties(aProperties)
	, mResource(aResource)
{

}

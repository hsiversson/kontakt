//ProjectFilter(Interface/Resources)
#include "Render_Precompiled.h"
#include "SR_Buffer.h"

SR_Buffer::~SR_Buffer()
{
	for (const SR_Descriptor& descriptor : mDescriptors)
	{
		if (descriptor.mHeapIndex != SR_Descriptor::gInvalidIndex)
			SR_RenderDevice::gInstance->GetDescriptorHeap(SR_DescriptorHeapType::CBV_SRV_UAV)->Free(descriptor);
	}
}

const SR_BufferProperties& SR_Buffer::GetProperties() const
{
	return mProperties;
}

const SR_BufferResourceProperties& SR_Buffer::GetResourceProperties() const
{
	return mResource->GetProperties();
}

SR_BufferResource* SR_Buffer::GetResource() const
{
	return mResource;
}

const SR_Descriptor& SR_Buffer::GetDescriptor() const
{
	return mDescriptors[0];
}

uint32 SR_Buffer::GetDescriptorHeapIndex() const
{
	return mDescriptors[0].mHeapIndex;
}

const SR_Descriptor& SR_Buffer::GetRWDescriptor() const
{
	return mDescriptors[1];
}

uint32 SR_Buffer::GetRWDescriptorHeapIndex() const
{
	return mDescriptors[1].mHeapIndex;
}

SR_Buffer::SR_Buffer(const SR_BufferProperties& aProperties, const SC_Ref<SR_BufferResource>& aResource)
	: mProperties(aProperties)
	, mResource(aResource)
{
}
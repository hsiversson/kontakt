//ProjectFilter(Interface/Resources)
#include "Render_Precompiled.h"
#include "SR_VertexLayout.h"

bool SR_VertexLayout::operator==(const SR_VertexLayout& aOther) const
{
	if (mAttributes.Count() != aOther.mAttributes.Count())
		return false;

	for (uint32 i = 0; i < mAttributes.Count(); ++i)
	{
		if (mAttributes[i].mAttributeId != aOther.mAttributes[i].mAttributeId)
			return false;

		if (mAttributes[i].mAttributeIndex != aOther.mAttributes[i].mAttributeIndex)
			return false;
	}

	return true;
}

uint32 SR_VertexLayout::GetVertexStrideSize() const
{
	uint32 stride = 0;

	for (const SR_VertexAttributeData& attribute : mAttributes)
	{
		uint32 bytesPerAttribute = SR_GetFormatBitsPerPixel(attribute.mFormat) / 8;
		stride += bytesPerAttribute;
	}

	return stride;
}

void SR_VertexLayout::SetAttribute(const SR_VertexAttribute& aAttribute, const SR_Format aFormat /*= SR_Format::UNKNOWN*/, uint32 aIndex /*= 0*/)
{
	for (SR_VertexAttributeData& attrib : mAttributes)
	{
		if (attrib.mAttributeId == aAttribute && attrib.mAttributeIndex == aIndex)
		{
			attrib.mFormat = aFormat;
			return;
		}
	}

	mAttributes.Add(SR_VertexAttributeData(aAttribute, aFormat, aIndex));
}

bool SR_VertexLayout::HasAttribute(const SR_VertexAttribute& aAttribute, uint32 aIndex /*= 0*/) const
{
	for (const SR_VertexAttributeData& attrib : mAttributes)
	{
		if (attrib.mAttributeId == aAttribute && attrib.mAttributeIndex == aIndex)
			return true;
	}

	return false;
}

SR_Format SR_VertexLayout::GetAttributeFormat(const SR_VertexAttribute& aAttribute, uint32 aIndex /*= 0*/) const
{
	for (const SR_VertexAttributeData& attrib : mAttributes)
	{
		if (attrib.mAttributeId == aAttribute && attrib.mAttributeIndex == aIndex)
			return attrib.mFormat;
	}

	return SR_Format::UNKNOWN;
}

uint32 SR_VertexLayout::GetAttributeByteOffset(const SR_VertexAttribute& aAttribute, uint32 aIndex /*= 0*/) const
{
	uint32 offset = 0;
	for (const SR_VertexAttributeData& attrib : mAttributes)
	{
		if (attrib.mAttributeId == aAttribute && attrib.mAttributeIndex == aIndex)
			break;

		uint32 attributeBytes = SR_GetFormatBitsPerPixel(attrib.mFormat) / 8;
		offset += attributeBytes;
	}
	return offset;
}

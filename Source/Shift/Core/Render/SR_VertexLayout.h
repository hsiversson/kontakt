//ProjectFilter(Interface/Resources)
#pragma once

enum class SR_VertexAttribute
{
	Position,
	Normal,
	Tangent,
	Bitangent,
	UV,
	Color,
	BoneId,
	BoneWeight,
	COUNT
};

struct SR_VertexAttributeData
{
	SR_VertexAttributeData() : mAttributeId(SR_VertexAttribute::COUNT), mFormat(SR_Format::UNKNOWN), mAttributeIndex(0) {}
	SR_VertexAttributeData(const SR_VertexAttribute& aAttribute, const SR_Format& aFormat, uint32 aAttributeIndex = 0) : mAttributeId(aAttribute), mFormat(aFormat), mAttributeIndex(aAttributeIndex) {}

	SR_VertexAttribute mAttributeId;
	SR_Format mFormat;
	uint32 mAttributeIndex;
};

struct SR_VertexLayout
{
	SR_VertexLayout();

	uint32 GetVertexStrideSize() const;
	void SetAttribute(const SR_VertexAttribute& aAttribute, const SR_Format aFormat = SR_Format::UNKNOWN, uint32 aIndex = 0);
	bool HasAttribute(const SR_VertexAttribute& aAttribute, uint32 aIndex = 0) const;
	SR_Format GetAttributeFormat(const SR_VertexAttribute& aAttribute, uint32 aIndex = 0) const;
	uint32 GetAttributeByteOffset(const SR_VertexAttribute& aAttribute, uint32 aIndex = 0) const;
	bool operator==(const SR_VertexLayout& aOther) const;


	SC_Array<SR_VertexAttributeData> mAttributes;
};
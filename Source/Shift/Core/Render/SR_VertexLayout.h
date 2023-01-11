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
	bool operator==(const SR_VertexLayout& aOther) const;

	uint32 GetVertexStrideSize() const;
	void SetAttribute(const SR_VertexAttribute& aAttribute, const SR_Format aFormat = SR_Format::UNKNOWN, uint32 aIndex = 0);
	bool HasAttribute(const SR_VertexAttribute& aAttribute, uint32 aIndex = 0) const;
	SR_Format GetAttributeFormat(const SR_VertexAttribute& aAttribute, uint32 aIndex = 0) const;
	uint32 GetAttributeByteOffset(const SR_VertexAttribute& aAttribute, uint32 aIndex = 0) const;

	SC_Array<SR_VertexAttributeData> mAttributes;
};

namespace std
{
	template <>
	struct hash<SR_VertexLayout>
	{
		size_t operator()(const SR_VertexLayout& aOther) const
		{
			size_t res = 17;
			for (uint32 i = 0; i < aOther.mAttributes.Count(); ++i)
			{
				res = res * 31 + hash<uint32>()(static_cast<uint32>(aOther.mAttributes[i].mAttributeId));
				res += 9 * hash<uint32>()(static_cast<uint32>(aOther.mAttributes[i].mFormat));
				res += 24 * hash<uint32>()(static_cast<uint32>(aOther.mAttributes[i].mAttributeIndex));
			}
			return res;
		}
	};
}
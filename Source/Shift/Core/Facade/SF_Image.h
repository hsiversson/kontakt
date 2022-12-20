//ProjectFilter(Widgets)
#pragma once
#include "SF_Widget.h"

class SR_Texture;
class SF_Image : public SF_Widget
{
public:
	SF_Image();
	~SF_Image();

	void Update() override;
	void Render() override;

	void SetImage(SR_Texture* aImage);
	void SetSize(const SC_Vector2& aSize);
	void SetUV(const SC_Vector2& aMinUV, const SC_Vector2& aMaxUV);

private:
	SC_Ref<SR_Texture> mImage;
};


//ProjectFilter(Widgets)
#pragma once
#include "SF_Widget.h"

class SF_Button : public SF_Widget
{
public:
	SF_Button();
	~SF_Button();

	void Update() override;
	void Render() override;

private:
	void Init();

	void OnClick();
	void OnMouseEvent();
};


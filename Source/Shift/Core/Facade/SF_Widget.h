//ProjectFilter(Widgets)
#pragma once

class SF_Widget
{
public:
	SF_Widget();
	virtual ~SF_Widget();

	virtual void Update();
	virtual void Render();

protected:
	SC_Slot<void()> mOnMouseEvent;
	SC_Slot<void()> mOnKeyEvent;

	SC_Slot<void()> mOnDragEvent;
	SC_Slot<void()> mOnDropEvent;
};


//ProjectFilter(Widgets)
#pragma once

class SF_Widget
{
public:
	SF_Widget();
	virtual ~SF_Widget();

	virtual void Update();
	virtual void Render();

	void SetVisible(bool aValue);
	void Show();
	void Hide();

	void SetEnabled(bool aValue);
	void Enable();
	void Disable();

	bool IsVisible() const;
	bool IsEnabled() const;

protected:
	SC_Slot<void()> mOnMouseEvent;
	SC_Slot<void()> mOnKeyEvent;

	SC_Slot<void()> mOnDragEvent;
	SC_Slot<void()> mOnDropEvent;

private:
	bool mIsVisible : 1;
	bool mIsEnabled : 1;

	bool mAcceptsDrops : 1;
};


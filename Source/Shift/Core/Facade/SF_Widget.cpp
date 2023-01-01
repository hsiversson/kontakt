//ProjectFilter(Widgets)
#include "Facade_Precompiled.h"
#include "SF_Widget.h"

SF_Widget::SF_Widget()
{

}

SF_Widget::~SF_Widget()
{

}

void SF_Widget::Update()
{

}

void SF_Widget::Render()
{

}

void SF_Widget::SetVisible(bool aValue)
{
	mIsVisible = aValue;
}

void SF_Widget::Show()
{
	mIsVisible = true;
}

void SF_Widget::Hide()
{
	mIsVisible = false;
}

void SF_Widget::SetEnabled(bool aValue)
{
	mIsEnabled = aValue;
}

void SF_Widget::Enable()
{
	mIsEnabled = true;
}

void SF_Widget::Disable()
{
	mIsEnabled = false;
}

bool SF_Widget::IsVisible() const
{
	return mIsVisible;
}

bool SF_Widget::IsEnabled() const
{
	return mIsEnabled;
}

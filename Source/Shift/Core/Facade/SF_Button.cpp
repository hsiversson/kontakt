//ProjectFilter(Widgets)
#include "Facade_Precompiled.h"
#include "SF_Button.h"

SF_Button::SF_Button()
{

}

SF_Button::~SF_Button()
{

}

void SF_Button::Update()
{

}

void SF_Button::Render()
{

}

void SF_Button::Init()
{

	// SetIsMouseTarget(true);
	// SetIsKeyboardTarget(true);

	// Connect(SF_MessageType::MouseFocusLeave, this, &SF_Button::OnMouseFocusLeave);
	// Connect(SF_MessageType::KeyFocusLeave, this, &SF_Button::OnKeyFocusLeave);



}

void SF_Button::OnClick()
{
	// Call anything subscribed to this button
}

void SF_Button::OnMouseEvent()
{
	//bool isMouseHoveringButton = IsPointInside(aMessage.mScreenPos);
	//
	//if (!mIsHovered && isMouseHoveringButton)
	//	OnHoverEnter();
	//else if (mIsHovered)
	//	OnHoverExit();
}

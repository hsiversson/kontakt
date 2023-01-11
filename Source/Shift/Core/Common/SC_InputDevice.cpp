//ProjectFilter(Input)
#include "Common_Precompiled.h"
#include "SC_InputDevice.h"

SC_InputDevice::SC_InputDevice(const SC_InputDeviceType aType, uint32 aIndex /*= 0*/)
	: mType(aType)
	, mIndex(aIndex)
{

}

SC_InputDevice::~SC_InputDevice()
{

}

bool SC_InputDevice::IsConnected() const
{
	return false;
}

bool SC_InputDevice::IsDown(uint32 aControlIndex) const
{
	return GetControl(aControlIndex)->IsDown();
}

bool SC_InputDevice::IsPressed(uint32 aControlIndex) const
{
	return GetControl(aControlIndex)->IsPressed();
}

bool SC_InputDevice::IsReleased(uint32 aControlIndex) const
{
	return GetControl(aControlIndex)->IsReleased();
}

bool SC_InputDevice::IsClicked(uint32 aControlIndex) const
{
	return GetControl(aControlIndex)->IsClicked(1);
}

bool SC_InputDevice::IsDoubleClicked(uint32 aControlIndex) const
{
	return GetControl(aControlIndex)->IsClicked(2);
}

bool SC_InputDevice::IsTripleClicked(uint32 aControlIndex) const
{
	return GetControl(aControlIndex)->IsClicked(3);
}

SC_InputDeviceControl* SC_InputDevice::GetControl(uint32 aControlIndex)
{
	return mControls[aControlIndex];
}

const SC_InputDeviceControl* SC_InputDevice::GetControl(uint32 aControlIndex) const
{
	return mControls[aControlIndex];
}

SC_InputDevice_Mouse::SC_InputDevice_Mouse(uint32 aIndex /*= 0*/)
	: SC_InputDevice(SC_InputDeviceType::Mouse, aIndex)
{

}

SC_Vector2 SC_InputDevice_Mouse::GetAxis()
{
	return SC_Vector2();
}

SC_Vector2 SC_InputDevice_Mouse::GetPosition()
{
	return SC_Vector2();
}

void SC_InputDevice_Mouse::SetPosition(const SC_Vector2& /*aPosition*/)
{

}

SC_InputDevice_Keyboard::SC_InputDevice_Keyboard(uint32 aIndex /*= 0*/)
	: SC_InputDevice(SC_InputDeviceType::Keyboard, aIndex)
{

}

const char* SC_InputDeviceControl::GetName() const
{
	return nullptr;
}

bool SC_InputDeviceControl::IsDown() const
{
	return false;
}

bool SC_InputDeviceControl::IsPressed() const
{
	return false;
}

bool SC_InputDeviceControl::IsReleased() const
{
	return false;
}

bool SC_InputDeviceControl::IsClicked(uint32 /*aNumClicks*/ /*= 1*/) const
{
	return false;
}

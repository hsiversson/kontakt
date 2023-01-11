//ProjectFilter(Input)
#pragma once
#include "SC_InputEnums.h"

class SC_InputDeviceControl
{
public:
	const char* GetName() const;

	bool IsDown() const;
	bool IsPressed() const;
	bool IsReleased() const;
	bool IsClicked(uint32 aNumClicks = 1) const;
};

class SC_InputDevice
{
public:
	SC_InputDevice(const SC_InputDeviceType aType, uint32 aIndex = 0);
	virtual ~SC_InputDevice();

	bool IsConnected() const;

	bool IsDown(uint32 aControlIndex) const;
	bool IsPressed(uint32 aControlIndex) const;
	bool IsReleased(uint32 aControlIndex) const;
	bool IsClicked(uint32 aControlIndex) const;
	bool IsDoubleClicked(uint32 aControlIndex) const;
	bool IsTripleClicked(uint32 aControlIndex) const;

	SC_InputDeviceControl* GetControl(uint32 aControlIndex);
	const SC_InputDeviceControl* GetControl(uint32 aControlIndex) const;

protected:
	SC_Array<SC_InputDeviceControl*> mControls;

	const SC_InputDeviceType mType;
	uint32 mIndex;
};

class SC_InputDevice_Mouse final : public SC_InputDevice
{
public:
	SC_InputDevice_Mouse(uint32 aIndex = 0);

	SC_Vector2 GetAxis();
	SC_Vector2 GetPosition();
	void SetPosition(const SC_Vector2& aPosition);

private:

};

class SC_InputDevice_Keyboard final : public SC_InputDevice
{
public:
	SC_InputDevice_Keyboard(uint32 aIndex = 0);



private:
};

class SC_InputDevice_Gamepad final : public SC_InputDevice
{
public:
	SC_InputDevice_Gamepad(uint32 aIndex = 0);

private:
};
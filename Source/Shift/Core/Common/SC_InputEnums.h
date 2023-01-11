//ProjectFilter(Input)
#pragma once

enum class SC_InputDeviceType
{
	Mouse,
	Keyboard,
	Gamepad,
	COUNT
};

enum class SC_InputDeviceSubType
{
	Default,
	Wheel,
	FlightStick,
	ArcadeStick,
	DancePad,
	Guitar,
	Drums,
	BigButton,
	COUNT,
	Unknown = COUNT
};

enum class SC_InputBackendType
{
	Unknown,
	XInput,
	COUNT
};

enum class SC_InputGamepadControl
{
	DPad_Up,
	DPad_Left,
	DPad_Down,
	DPad_Right,
	Start,
	Select,
	A,
	B,
	X,
	Y,
	L1,
	L2,
	R1,
	R2,
	LeftStick_Click,
	LeftStick_X,
	LeftStick_Y,
	RightStick_Click,
	RightStick_X,
	RightStick_Y,

	COUNT,

	// Playstation touchpad
	PS_Touch_Button,
	PS_Touch1_Id,
	PS_Touch1_X,
	PS_Touch1_Y,
	PS_Touch2_Id,
	PS_Touch2_X,
	PS_Touch2_Y,

	// PS5 Haptics
	PS5_L2_State,
	PS5_R2_State,
	PS5_Orientation_X,
	PS5_Orientation_Y,
	PS5_Orientation_Z,
	PS5_Orientation_W,
	PS5_Acceleration_X,
	PS5_Acceleration_Y,
	PS5_Acceleration_Z,
	PS5_AngularVelocity_X,
	PS5_AngularVelocity_Y,
	PS5_AngularVelocity_Z,

	EXTENDED_COUNT
};

enum class SC_InputMouseControl
{
	Left,
	Right,
	Middle,
	ScrollWheel,
	DeltaX,
	DeltaY,
	PositionX,
	PositionY,
	Button1,
	Button2,
	Button3,
	Button4,
	Button5,
	Button6,
	Button7,
	Button8,
	COUNT
};

enum class SC_InputKeyboardControl
{
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,

	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	F17,
	F18,
	F19,
	F20,
	F21,
	F22,
	F23,
	F24,

	LeftArrow,
	UpArrow,
	RightArrow,
	DownArrow,

	Insert,

	Delete,
	Home,
	End,
	PageUp,
	PageDown,

	Escape,
	Tab,
	CapsLock,
	LeftShift,
	LeftControl,
	LeftAlt,

	Space,
	PrintScreen,
	ScrollLock,
	PauseBreak,

	Backspace,
	Enter,
	RightShift,
	RightContol,
	RightAlt,

	Shift,
	Control,

	NumPad0,
	NumPad1,
	NumPad2,
	NumPad3,
	NumPad4,
	NumPad5,
	NumPad6,
	NumPad7,
	NumPad8,
	NumPad9,
	NumLock,
	Multiply,
	Add,
	Seperator,
	Subtract,
	Decimal,
	Divide,

	Tilde,
	Grave = Tilde,

	COUNT,

};
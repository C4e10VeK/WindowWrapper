#ifndef WINDOWWRAPPER_ENUMEVENT_HPP
#define WINDOWWRAPPER_ENUMEVENT_HPP

#include "Types.hpp"
#include "Vector.hpp"

namespace winWrap
{
	enum class EventType : i32
	{
		Non = -1,
		KeyPressed = 0,
		KeyReleased,
		Closed,
		Resized,
		Moved,
		MouseMoved,
		MouseEntered,
		MouseLeaved,
		MouseButtonPressed,
		MouseButtonReleased
	};

	enum class Key : i32
	{
		Non = -1,
		Left = 0,
		Up,
		Right,
		Down,
		Insert,
		Home,
		Delete,
		End,
		PageUp,
		PageDown,
		Print,
		Scroll,
		Pause,
		Escape,
		Tab,
		Caps,
		LShift,
		RShift,
		LControl,
		RControl,
		LAlt,
		RAlt,
		LSuper,
		RSuper,
		Return,
		Backspace,
		Space,
		Menu,
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		NumLock,
		Divide,
		Multiply,
		Minus,
		Plus,
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
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Num0,
		LBracket,
		RBracket,
		Semicolon,
		Comma,
		Equal,
		Slash,
		Backslash,

		Count
	};

	struct InternalEvent
	{
		EventType type{EventType::Non};
		Key key{Key::Non};
		Size size;
		dvec2 mousePos;

		InternalEvent() = default;
	};
}

#endif // WINDOWWRAPPER_ENUMEVENT_HPP


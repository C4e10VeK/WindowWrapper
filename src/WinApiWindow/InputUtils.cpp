#include "../Common/InputUtils.hpp"

#include <bitset>

#include <windows.h>
#include <Common/InternalEvent.hpp>

namespace winWrap
{
	Key specificPlatformKeyToKey(KeyInfo info)
	{
		std::bitset<32> bits(info.lParam);

		UINT scancode = static_cast<UINT>((static_cast<LPARAM>(info.lParam) & (0xFF << 16)) >> 16);
		i32 extend = bits.test(24) != 0;

		switch (static_cast<WPARAM>(info.key))
		{
			case VK_LEFT:		return Key::Left;
			case VK_UP: 		return Key::Up;
			case VK_RIGHT:		return Key::Right;
			case VK_DOWN:		return Key::Down;
			case VK_INSERT: 	return Key::Insert;
			case VK_HOME: 		return Key::Home;
			case VK_DELETE:		return Key::Delete;
			case VK_END: 		return Key::End;
			case VK_PRIOR:		return Key::PageUp;
			case VK_NEXT:		return Key::PageDown;
			case VK_PRINT:		return Key::Print;
			case VK_SCROLL: 	return Key::Scroll;
			case VK_PAUSE:		return Key::Pause;
			case VK_ESCAPE: 	return Key::Escape;
			case VK_TAB:		return Key::Tab;
			case VK_CAPITAL:	return Key::Caps;
			case VK_SHIFT:		return scancode == MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC) ? Key::LShift : Key::RShift;
			case VK_CONTROL: 	return extend ? Key::RControl : Key::LControl;
			case VK_MENU: 		return extend ? Key::RAlt : Key::LAlt;
			case VK_LWIN:		return Key::LSuper;
			case VK_RWIN:		return Key::RSuper;
			case VK_RETURN:		return Key::Return;
			case VK_BACK:		return Key::Backspace;
			case VK_SPACE:		return Key::Space;
			case VK_APPS:		return Key::Menu;
			case VK_NUMPAD0:	return Key::Numpad0;
			case VK_NUMPAD1:	return Key::Numpad1;
			case VK_NUMPAD2:	return Key::Numpad2;
			case VK_NUMPAD3:	return Key::Numpad3;
			case VK_NUMPAD4:	return Key::Numpad4;
			case VK_NUMPAD5:	return Key::Numpad5;
			case VK_NUMPAD6:	return Key::Numpad6;
			case VK_NUMPAD7:	return Key::Numpad7;
			case VK_NUMPAD8:	return Key::Numpad8;
			case VK_NUMPAD9:	return Key::Numpad9;
			case VK_NUMLOCK:	return Key::NumLock;
			case VK_DIVIDE:		return Key::Divide;
			case VK_MULTIPLY:	return Key::Multiply;
			case VK_SUBTRACT:	return Key::Minus;
			case VK_ADD:		return Key::Plus;
			case VK_F1:			return Key::F1;
			case VK_F2:			return Key::F2;
			case VK_F3:			return Key::F3;
			case VK_F4:			return Key::F4;
			case VK_F5:			return Key::F5;
			case VK_F6:			return Key::F6;
			case VK_F7:			return Key::F7;
			case VK_F8:			return Key::F8;
			case VK_F9:			return Key::F9;
			case VK_F10:		return Key::F10;
			case VK_F11:		return Key::F11;
			case VK_F12:		return Key::F12;
			case 'A':			return Key::A;
			case 'B':			return Key::B;
			case 'C':			return Key::C;
			case 'D':			return Key::D;
			case 'E':			return Key::E;
			case 'F':			return Key::F;
			case 'G':			return Key::G;
			case 'H':			return Key::H;
			case 'I':			return Key::I;
			case 'J':			return Key::J;
			case 'K':			return Key::K;
			case 'L':			return Key::L;
			case 'M':			return Key::M;
			case 'N':			return Key::N;
			case 'O':			return Key::O;
			case 'P':			return Key::P;
			case 'Q':			return Key::Q;
			case 'R':			return Key::R;
			case 'S':			return Key::S;
			case 'T':			return Key::T;
			case 'U':			return Key::U;
			case 'V':			return Key::V;
			case 'W':			return Key::W;
			case 'X':			return Key::X;
			case 'Y':			return Key::Y;
			case 'Z':			return Key::Z;
			case '1':			return Key::Num1;
			case '2':			return Key::Num2;
			case '3':			return Key::Num3;
			case '4':			return Key::Num4;
			case '5':			return Key::Num5;
			case '6':			return Key::Num6;
			case '7':			return Key::Num7;
			case '8':			return Key::Num8;
			case '9':			return Key::Num9;
			case '0':			return Key::Num0;
			case VK_OEM_4:		return Key::LBracket;
			case VK_OEM_6:		return Key::RBracket;
			case VK_OEM_1:		return Key::Semicolon;
			case VK_OEM_COMMA:	return Key::Comma;
			case VK_OEM_PLUS:	return Key::Equal;
			case VK_OEM_2:		return Key::Slash;
			case VK_OEM_5:		return Key::Backslash;
			default: break;
		}

		return Key::Non;
	}

	i32 keyToSpecificPlatformKey(Key key)
	{
		return 0;
	}
}
#include "../Common/InputUtils.hpp"
#include <Common/InternalEvent.hpp>

#include <X11/keysym.h>

namespace winWrap
{
	Key specificPlatformKeyToKey(u32 key)
	{
		switch (key)
		{
			case XK_Left:		 return Key::Left;
			case XK_Up:			 return Key::Up;
			case XK_Right:		 return Key::Right;
			case XK_Down:		 return Key::Down;
			case XK_Insert: 	 return Key::Insert;
			case XK_Home: 	 	 return Key::Home;
			case XK_Delete:  	 return Key::Delete;
			case XK_End: 	 	 return Key::End;
			case XK_Page_Up:	 return Key::PageUp;
			case XK_Page_Down:	 return Key::PageDown;
			case XK_Print:		 return Key::Print;
			case XK_Scroll_Lock: return Key::Scroll;
			case XK_Pause:		 return Key::Pause;
			case XK_Escape:		 return Key::Escape;
			case XK_Tab:		 return Key::Tab;
			case XK_Caps_Lock:	 return Key::Caps;
			case XK_Shift_L:	 return Key::LShift;
			case XK_Shift_R:	 return Key::RShift;
			case XK_Control_L:	 return Key::LControl;
			case XK_Control_R:	 return Key::RControl;
			case XK_Alt_L:	 	 return Key::LAlt;
			case XK_Alt_R:	 	 return Key::RAlt;
			case XK_Super_L: 	 return Key::LSuper;
			case XK_Super_R: 	 return Key::RSuper;
			case XK_Return:	 	 return Key::Return;
			case XK_BackSpace:	 return Key::Backspace;
			case XK_space:		 return Key::Space;
			case XK_Menu:		 return Key::Menu;
			case XK_KP_0:		 return Key::Numpad0;
			case XK_KP_1:		 return Key::Numpad1;
			case XK_KP_2:		 return Key::Numpad2;
			case XK_KP_3:		 return Key::Numpad3;
			case XK_KP_4:		 return Key::Numpad4;
			case XK_KP_5:		 return Key::Numpad5;
			case XK_KP_6:		 return Key::Numpad6;
			case XK_KP_7:		 return Key::Numpad7;
			case XK_KP_8:		 return Key::Numpad8;
			case XK_KP_9:		 return Key::Numpad9;
			case XK_Num_Lock:	 return Key::NumLock;
			case XK_KP_Divide:	 return Key::Divide;
			case XK_KP_Multiply: return Key::Multiply;
			case XK_KP_Subtract: return Key::Minus;
			case XK_KP_Add:		 return Key::Plus;
			case XK_F1:			 return Key::F1;
			case XK_F2:			 return Key::F2;
			case XK_F3:			 return Key::F3;
			case XK_F4:			 return Key::F4;
			case XK_F5:			 return Key::F5;
			case XK_F6:			 return Key::F6;
			case XK_F7:			 return Key::F7;
			case XK_F8:			 return Key::F8;
			case XK_F9:			 return Key::F9;
			case XK_F10:		 return Key::F10;
			case XK_F11:		 return Key::F11;
			case XK_F12:		 return Key::F12;
			case XK_a:			 return Key::A;
			case XK_b:			 return Key::B;
			case XK_c:			 return Key::C;
			case XK_d:			 return Key::D;
			case XK_e:			 return Key::E;
			case XK_f:			 return Key::F;
			case XK_g:			 return Key::G;
			case XK_h:			 return Key::H;
			case XK_i:			 return Key::I;
			case XK_j:			 return Key::J;
			case XK_k:			 return Key::K;
			case XK_l:			 return Key::L;
			case XK_m:			 return Key::M;
			case XK_n:			 return Key::N;
			case XK_o:			 return Key::O;
			case XK_p:			 return Key::P;
			case XK_q:			 return Key::Q;
			case XK_r:			 return Key::R;
			case XK_s:			 return Key::S;
			case XK_t:			 return Key::T;
			case XK_u:			 return Key::U;
			case XK_v:			 return Key::V;
			case XK_w:			 return Key::W;
			case XK_x:			 return Key::X;
			case XK_y:			 return Key::Y;
			case XK_z:			 return Key::Z;
			case XK_0:			 return Key::Num0;
			case XK_1:			 return Key::Num1;
			case XK_2:			 return Key::Num2;
			case XK_3:			 return Key::Num3;
			case XK_4:			 return Key::Num4;
			case XK_5:			 return Key::Num5;
			case XK_6:			 return Key::Num6;
			case XK_7:			 return Key::Num7;
			case XK_8:			 return Key::Num8;
			case XK_9:			 return Key::Num9;
			case XK_bracketleft: return Key::LBracket;
			case XK_braceright:	 return Key::RBracket;
			case XK_semicolon:	 return Key::Semicolon;
			case XK_comma:		 return Key::Comma;
			case XK_equal:		 return Key::Equal;
			case XK_slash:		 return Key::Slash;
			case XK_backslash:	 return Key::Backslash;
			default: break;
		}

		return Key::Non;
	}

	i32 keyToSpecificPlatformKey(Key key)
	{
		switch (key)
		{
		case Key::Non:
			return -1;
		case Key::Left:
			return XK_Left;
		case Key::Up:
			return XK_Up;
		case Key::Right:
			return XK_Right;
		case Key::Down:
			return XK_Down;
		case Key::Insert:
			return XK_Insert;
		case Key::Home:
			return XK_Home;
		case Key::Delete:
			return XK_Delete;
		case Key::End:
			return XK_End;
		case Key::PageUp:
			return XK_Page_Up;
		case Key::PageDown:
			return XK_Page_Down;
		case Key::Print:
			return XK_Print;
		case Key::Scroll:
			return XK_Scroll_Lock;
		case Key::Pause:
			return XK_Pause;
		case Key::Escape:
			return XK_Escape;
		case Key::Tab:
			return XK_Tab;
		case Key::Caps:
			return XK_Caps_Lock;
		case Key::LShift:
			return XK_Shift_L;
		case Key::RShift:
			return XK_Shift_R;
		case Key::LControl:
			return XK_Control_L;
		case Key::RControl:
			return XK_Control_R;
		case Key::LAlt:
			return XK_Alt_L;
		case Key::RAlt:
			return XK_Alt_R;
		case Key::Return:
			return XK_Return;
		case Key::Backspace:
			return XK_BackSpace;
		case Key::Space:
			return XK_space;
		case Key::Numpad0:
			break;
		case Key::Numpad1:
			break;
		case Key::Numpad2:
			break;
		case Key::Numpad3:
			break;
		case Key::Numpad4:
			break;
		case Key::Numpad5:
			break;
		case Key::Numpad6:
			break;
		case Key::Numpad7:
			break;
		case Key::Numpad8:
			break;
		case Key::Numpad9:
			break;
		case Key::NumLock:
			break;
		case Key::Divide:
			break;
		case Key::Multiply:
			break;
		case Key::Minus:
			break;
		case Key::Plus:
			break;
		case Key::F1:
			break;
		case Key::F2:
			break;
		case Key::F3:
			break;
		case Key::F4:
			break;
		case Key::F5:
			break;
		case Key::F6:
			break;
		case Key::F7:
			break;
		case Key::F8:
			break;
		case Key::F9:
			break;
		case Key::F10:
			break;
		case Key::F11:
			break;
		case Key::F12:
			break;
		case Key::A:
			break;
		case Key::B:
			break;
		case Key::C:
			break;
		case Key::D:
			break;
		case Key::E:
			break;
		case Key::F:
			break;
		case Key::G:
			break;
		case Key::H:
			break;
		case Key::I:
			break;
		case Key::J:
			break;
		case Key::K:
			break;
		case Key::L:
			break;
		case Key::M:
			break;
		case Key::N:
			break;
		case Key::O:
			break;
		case Key::P:
			break;
		case Key::Q:
			break;
		case Key::R:
			break;
		case Key::S:
			break;
		case Key::T:
			break;
		case Key::U:
			break;
		case Key::V:
			break;
		case Key::W:
			break;
		case Key::X:
			break;
		case Key::Y:
			break;
		case Key::Z:
			break;
		case Key::Num1:
			break;
		case Key::Num2:
			break;
		case Key::Num3:
			break;
		case Key::Num4:
			break;
		case Key::Num5:
			break;
		case Key::Num6:
			break;
		case Key::Num7:
			break;
		case Key::Num8:
			break;
		case Key::Num9:
			break;
		case Key::Num0:
			break;
		case Key::LBracket:
			break;
		case Key::RBracket:
			break;
		case Key::Semicolon:
			break;
		case Key::Comma:
			break;
		case Key::Equal:
			break;
		case Key::Slash:
			break;
		case Key::Backslash:
			break;
		case Key::Count:
			break;
		default: break;
		}

		return -1;
	}
}
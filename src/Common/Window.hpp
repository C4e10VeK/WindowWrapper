#ifndef WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP
#define WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP

#include "IPlatformWindowBase.hpp"

#if defined(_WIN32) || defined(__MINGW32__)
#include "../WinApiWindow/WAWindow.hpp"
#elif defined(__linux) && !defined(__MINGW32__)
#include "../LinuxWindow/X11Window.hpp"
#endif

namespace winWrap
{
	using Window = PlatformWindow;
}

#endif // WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP

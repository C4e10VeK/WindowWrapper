#ifndef WINDOWWRAPPER_SRC_COMMON_WINWRAP_HPP
#define WINDOWWRAPPER_SRC_COMMON_WINWRAP_HPP

#include "IPlatformWindowBase.hpp"

#ifdef __linux
#include "../LinuxWindow/X11Window.hpp"
#elifdef _WIN32
#include "../WinApiWindow/WAWindow.hpp"
#endif

namespace winWrap
{
#ifdef __linux
    using Window = winWrap::X11Window;
#elifdef _WIN32
    using Window = winWrap::WAWindow;
#endif
}

#endif // WINDOWWRAPPER_SRC_COMMON_WINWRAP_HPP

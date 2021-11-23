#ifndef WINDOWWRAPPER_SRC_COMMON_WINWRAP_HPP
#define WINDOWWRAPPER_SRC_COMMON_WINWRAP_HPP

#include "IWindow.hpp"
#include "../LinuxWindow/X11Window.hpp"

namespace winWrap
{
#ifdef __linux
    using Window = X11Window;
#else
    using Window = X11Window;
#endif

    Window createWindow(const std::string &title, int width, int height)
    {
        return {title, width, height};
    }
}

#endif // WINDOWWRAPPER_SRC_COMMON_WINWRAP_HPP

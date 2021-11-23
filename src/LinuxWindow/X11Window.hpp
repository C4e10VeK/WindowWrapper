#ifndef WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP
#define WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP

#include <string>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "../Common/IPlatformWindowBase.hpp"

namespace winWrap
{
    class X11Window final : public IPlatformWindowBase
    {
    private:
        ::Window m_xWindow{};
        Display *m_display{};
        int m_screen{};

        int m_width;
        int m_height;

    public:
        explicit X11Window(int width = 800, int height = 600);

        ~X11Window() override;

        bool init(const std::string &title) override;

        void setTitle(const std::string &title) override;

        void pollEvent();
    };
}

#endif // WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP

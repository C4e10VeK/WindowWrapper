#ifndef WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP
#define WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP

#include <string>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "../Common/IWindow.hpp"

namespace winWrap
{
    class X11Window : public IWindow
    {
    public:
        Window m_xWindow{};
        Display *m_display{};
        int m_screen{};

        std::string m_title;
        bool m_isClosed;

        int m_width;
        int m_height;

        friend int main();
    public:
        X11Window(std::string title, int width, int height);

        explicit X11Window(const std::string &title);

        ~X11Window() override;

        bool init() override;

        bool isClosed() const override;

        void close() override;

        std::string getTitle() const override;

        void setTitle(const std::string &title) override;
    };
}

#endif // WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP

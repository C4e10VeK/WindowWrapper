#include "X11Window.hpp"

namespace winWrap
{
    X11Window::X11Window(std::string title, int width, int height)
    : m_title(std::move(title)),
      m_isClosed(false),
      m_width(width),
      m_height(height) { }

    X11Window::X11Window(const std::string &title) : X11Window(title, 800, 600) { }

    X11Window::~X11Window()
    {
        XDestroyWindow(m_display, m_xWindow);
        XCloseDisplay(m_display);
    }

    bool X11Window::init()
    {
        m_display = XOpenDisplay(nullptr);
        if (m_display == nullptr)
        {
            return false;
        }

        m_screen = DefaultScreen(m_display);

        XSetWindowAttributes atrs = {
            .background_pixel = 0xffffff,
            .border_pixel = 0,
            .event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask |
                          PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
                          ExposureMask | FocusChangeMask | VisibilityChangeMask |
                          EnterWindowMask | LeaveWindowMask | PropertyChangeMask,
            .colormap = XCreateColormap(m_display, RootWindow(m_display, m_screen), DefaultVisual(m_display, m_screen), AllocNone)
        };

        m_xWindow = XCreateWindow(
            m_display,
            RootWindow(m_display, m_screen),
            0, 0,
            m_width, m_height,
            0,
            DefaultDepth(m_display, m_screen),
            InputOutput,
            DefaultVisual(m_display, m_screen),
            CWColormap | CWEventMask | CWBackPixel | CWBorderPixel,
            &atrs
        );

        XSelectInput(m_display, m_xWindow, ExposureMask | KeyPressMask);
        XMapWindow(m_display, m_xWindow);

        XStoreName(m_display, m_xWindow, m_title.c_str());

        if (!m_xWindow)
        {
            return false;
        }

        return true;
    }

    bool X11Window::isClosed() const { return m_isClosed; }

    void X11Window::close()
    {
        m_isClosed = true;
    }

    std::string X11Window::getTitle() const { return m_title; }

    void X11Window::setTitle(const std::string &title)
    {
        m_title = title;
        XStoreName(m_display, m_xWindow, m_title.c_str());
    }
}

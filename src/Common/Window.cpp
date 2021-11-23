#include "Window.hpp"

#if defined(_WIN32) || defined(__MINGW32__)
#include "../WinApiWindow/WAWindow.hpp"
using PlatformWindow = winWrap::WAWindow;
#elif defined(__linux)
#include "../LinuxWindow/X11Window.hpp"
using PlatformWindow = winWrap::X11Window;
#endif

namespace winWrap
{
    std::shared_ptr<IPlatformWindowBase> Window::createWindow(int width, int height)
    {
        return std::make_shared<PlatformWindow>(width, height);
    }

    Window::Window(const std::string &title, int width, int height)
        : m_platformWindowBase(createWindow(width, height)),
          m_title(title),
          m_isClosed(false) {}

    bool Window::init()
    {
        return m_platformWindowBase->init(m_title);
    }

    bool Window::isClosed() const
    {
        return m_isClosed;
    }

    void Window::close()
    {
        m_isClosed = true;
    }

    std::string Window::getTitle() const
    {
        return m_title;
    }

    void Window::setTitle(const std::string &title)
    {
        m_title = title;
        m_platformWindowBase->setTitle(m_title);
    }

    bool Window::init(const std::string &title, int width, int height)
    {
        return true;
    }
}

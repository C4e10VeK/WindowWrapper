#include "X11Window.hpp"

#include <utility>

namespace winWrap
{
	PlatformWindow::PlatformWindow(std::string title, int width, int height)
	: m_width(width),
	  m_height(height),
	  m_title(std::move(title)),
	  m_isClosed(true) { if (!init(m_title, m_width, m_height)) std::abort(); }

	PlatformWindow::~PlatformWindow()
	{
		XDestroyWindow(m_display, m_xWindow);
		XCloseDisplay(m_display);
	}

	bool PlatformWindow::init(const std::string &title, int width, int height)
	{
		m_title = title;
		m_width = width;
		m_height = height;

		m_display = XOpenDisplay(nullptr);
		if (m_display == nullptr)
		{
			return false;
		}

		m_screen = DefaultScreen(m_display);

		XSetWindowAttributes atrs = {
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
			m_position.x, m_position.y,
			m_width, m_height,
			0,
			DefaultDepth(m_display, m_screen),
			InputOutput,
			DefaultVisual(m_display, m_screen),
			CWColormap | CWEventMask | CWBorderPixel,
			&atrs
		);

		m_atomDeleteWindow = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(m_display, m_xWindow, &m_atomDeleteWindow, 1);

		XSelectInput(m_display, m_xWindow, ExposureMask | KeyPressMask);
		XMapWindow(m_display, m_xWindow);

		XStoreName(m_display, m_xWindow, m_title.c_str());

		if (!m_xWindow)
		{
			return false;
		}

		return true;
	}

	bool PlatformWindow::isClosed() const
	{
		return m_isClosed;
	}

	void PlatformWindow::close()
	{
		m_isClosed = true;
	}

	i32 PlatformWindow::getWidth() const
	{
		return m_width;
	}

	i32 PlatformWindow::getHeight() const
	{
		return m_height;
	}

	const ivec2 &PlatformWindow::getPosition() const
	{
		return m_position;
	}

	void PlatformWindow::setPosition(const ivec2 &position)
	{
		m_position = position;
	}

	const std::string &PlatformWindow::getTitle() const
	{
		return m_title;
	}

	void PlatformWindow::setTitle(const std::string &title)
	{
		m_title = title;
		XStoreName(m_display, m_xWindow, title.c_str());
	}

	void PlatformWindow::setResizable(bool resizable)
	{

	}

	void PlatformWindow::pollEvent()
	{
		while (XPending(m_display))
		{
			XEvent e;
			XNextEvent(m_display, &e);

			switch (e.type)
			{
				case KeyPress:
					m_KeyPressed(*this, e.xkey.keycode);
					break;
				case KeyRelease:
						break;
				case ClientMessage:
					{
						if (e.xclient.data.l[0] == m_atomDeleteWindow)
							close();
					}
					break;
				case DestroyNotify:
					close();
					break;
				default:
					break;
			}
		}
	}
}
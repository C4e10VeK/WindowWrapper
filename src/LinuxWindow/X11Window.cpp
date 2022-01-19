#include "X11Window.hpp"

#include <Common/InternalEvent.hpp>

#include "../Common/InputUtils.hpp"
#include "../Common/VulkanUtils.hpp"

namespace winWrap
{
	PlatformWindow::~PlatformWindow()
	{
		if (m_display == nullptr) return;

		XDestroyWindow(m_display, m_xWindow);
		XFlush(m_display);
		XCloseDisplay(m_display);
	}

	bool PlatformWindow::init(const std::string &title, const WindowParams &params)
	{
		return createSpecificPlatformWindow(title, params);
	}

	i32 PlatformWindow::getWidth() const
	{
		XWindowAttributes atr;
		XGetWindowAttributes(m_display, m_xWindow, &atr);
		return atr.width;
	}

	i32 PlatformWindow::getHeight() const
	{
		XWindowAttributes atr;
		XGetWindowAttributes(m_display, m_xWindow, &atr);
		return atr.height;
	}

	Size PlatformWindow::getSize() const
	{
		XWindowAttributes atr;
		XGetWindowAttributes(m_display, m_xWindow, &atr);
		return {atr.width, atr.height};
	}

	ivec2 PlatformWindow::getPosition() const
	{
		return ivec2(0);
	}

	void PlatformWindow::setPosition(const ivec2 &position)
	{
		XMoveWindow(m_display, m_xWindow, position.x, position.y);
		XFlush(m_display);
	}

	void PlatformWindow::setTitle(const std::string &title)
	{
		XStoreName(m_display, m_xWindow, title.c_str());
	}

	void PlatformWindow::setResizable(bool resizable)
	{

	}

	bool PlatformWindow::pollEvents(InternalEvent &event)
	{
		XEvent xEvent;

		if (!XPending(m_display)) return false;

		XNextEvent(m_display, &xEvent);

		switch (xEvent.type)
		{
			case Expose:
				{

				}
				break;
			case KeyPress:
				{
					Key key = Key::Non;
					for (int i = 0; i < 4; ++i)
					{
						key = specificPlatformKeyToKey({XLookupKeysym(&xEvent.xkey, i)});
						if (key != Key::Non)
							break;
					}

					event.type = EventType::KeyPressed;
					event.key = key;
				}
				return true;
			case KeyRelease:
				{
					Key key = Key::Non;
					for (int i = 0; i < 4; ++i)
					{
						key = specificPlatformKeyToKey({XLookupKeysym(&xEvent.xkey, i)});
						if (key != Key::Non)
							break;
					}

					event.type = EventType::KeyReleased;
					event.key = key;
				}
				return true;
			case ConfigureNotify:
				{
					ivec2 size(xEvent.xconfigurerequest.width, xEvent.xconfigurerequest.height);
					event.type = EventType::Resized;
					event.size = size;
				}
				break;
			case ClientMessage:
					{
						if (xEvent.xclient.data.l[0] == m_atoms.atomDeleteWindow)
						{
							event.type = EventType::Closed;
						}
					}
				return true;
		}

		return false;
	}

	bool PlatformWindow::createVulkanSurface(VkInstance instance, VkSurfaceKHR &surface)
	{
		return createVulkanSurfacePr(instance, *this, surface);
	}

	bool PlatformWindow::createSpecificPlatformWindow(const std::string &title, const WindowParams &params)
	{
		m_display = XOpenDisplay(nullptr);
		if (m_display == nullptr)
			return false;

		initAtoms();

		m_screen = DefaultScreen(m_display);
		Window root = RootWindow(m_display, m_screen);
		Colormap colormap = XCreateColormap(m_display, root, DefaultVisual(m_display, m_screen), AllocNone);

		XSetWindowAttributes atr = {
			.border_pixel = 0,
			.event_mask = FocusChangeMask      | ButtonPressMask     |
						  ButtonReleaseMask    | ButtonMotionMask    |
						  PointerMotionMask    | KeyPressMask        |
						  KeyReleaseMask       | StructureNotifyMask |
						  EnterWindowMask      | LeaveWindowMask     |
						  VisibilityChangeMask | PropertyChangeMask  |
						  SubstructureNotifyMask,
			.colormap = colormap
		};

		m_xWindow = XCreateWindow(
			m_display,
			root, params.position.x, params.position.y, params.size.width,
			params.size.height,
			0,
			DefaultDepth(m_display, m_screen),
			InputOutput,
			DefaultVisual(m_display, m_screen),
			CWColormap | CWEventMask | CWBorderPixel,
			&atr);

		if (!m_xWindow)
		{
			XCloseDisplay(m_display);
			return false;
		}

		XSetWMProtocols(m_display, m_xWindow, &m_atoms.atomDeleteWindow, 1);

		if (!params.resizeable)
		{
			XSizeHints *sizeHints = XAllocSizeHints();

			sizeHints->flags = PMaxSize | PMinSize | USPosition;
			sizeHints->min_height = params.size.height;
			sizeHints->max_height = params.size.height;
			sizeHints->min_width = params.size.width;
			sizeHints->max_width = params.size.width;
			sizeHints->x = params.position.x;
			sizeHints->y = params.position.y;

			XSetWMNormalHints(m_display, m_xWindow, sizeHints);
			XFree(sizeHints);
		}

		XSelectInput(m_display, m_xWindow, ExposureMask | KeyPressMask);
		XMapWindow(m_display, m_xWindow);
		XRaiseWindow(m_display, m_xWindow);

		XStoreName(m_display, m_xWindow, title.c_str());

		return true;
	}

	void PlatformWindow::initAtoms()
	{
		m_atoms.atomDeleteWindow = XInternAtom(m_display, "WM_DELETE_WINDOW", false);
		m_atoms.atomResizeWindow = XInternAtom(m_display, "WM_ACTION_RESIZE", false);
		m_atoms.atomSize = XInternAtom(m_display, "WM_SIZE_HINTS", false);
		m_atoms.atomWMIcon = XInternAtom(m_display, "_NET_WM_ICON", false);
	}
}

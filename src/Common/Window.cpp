#include <Common/Window.hpp>
#include <utility>

#if defined(_WIN32) || defined(__MINGW32__)
#include "../WinApiWindow/WAWindow.hpp"
#elif defined(__linux__) && !defined(__MINGW32__)
#include "../LinuxWindow/X11Window.hpp"
#endif

#include <Common/InternalEvent.hpp>
#include <iostream>

namespace winWrap
{
	Window::Window() : m_platformWindow(nullptr), m_isClosed(true), keyEvent(m_keyEvent)
	{}

	Window::Window(std::string title, const WindowParams &params)
		: m_title(std::move(title)),
	  	  m_params(params),
	  	  m_isClosed(false),
		  keyEvent(m_keyEvent)
	{
		m_platformWindow = createSpecificPlatformWindow();
		m_platformWindow->init(title, params);	
	}

	bool Window::init(const std::string &title, const WindowParams &params)
	{
		close();

		m_title = title;
		m_params = params;
		m_isClosed = false;

		if (m_platformWindow == nullptr)
			m_platformWindow = createSpecificPlatformWindow();

		return m_platformWindow->init(title, params);
	}

	i32 Window::getWidth() const
	{
		return m_params.width;
	}

	i32 Window::getHeight() const
	{
		return m_params.height;
	}

	const vec2<i32> &Window::getPosition() const
	{
		return m_params.position;
	}

	void Window::setPosition(const vec2<i32> &position)
	{
		m_params.position = position;
		m_platformWindow->setPosition(position);
	}

	const std::string &Window::getTitle() const
	{
		return m_title;
	}

	void Window::setTitle(const std::string &title)
	{
		m_title = title;
		m_platformWindow->setTitle(title);
	}

	bool Window::isClosed() const
	{
		return m_isClosed;
	}

	void Window::close()
	{
		m_isClosed = true;
		if (m_platformWindow != nullptr)
		{
			m_platformWindow.reset();
		}
	}

	void Window::pollEvent()
	{
		InternalEvent event{};
		while(m_platformWindow && m_platformWindow->pollEvent(event))
		{
			switch (event.type)
			{
				case EventType::KeyPressed:
					m_keyEvent(*this, event.key, EventType::KeyPressed);
					break;
				case EventType::KeyReleased:
					m_keyEvent(*this, event.key, EventType::KeyReleased);
					break;
				case EventType::Closed:
					close();
					break;
				default:
					break;
			}
		}
	}

	std::unique_ptr<IPlatformWindow> Window::createSpecificPlatformWindow()
	{
		return std::make_unique<PlatformWindow>();
	}
}

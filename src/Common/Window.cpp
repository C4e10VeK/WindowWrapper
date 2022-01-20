#include <Common/Window.hpp>
#include <utility>

#if defined(_WIN32) || defined(__MINGW32__)
#include "../WinApiWindow/WAWindow.hpp"
#elif defined(__linux__) && !defined(__MINGW32__)
#include "../LinuxWindow/X11Window.hpp"
#endif

#include <Common/InternalEvent.hpp>
#include <iostream>
#include <future>

#include "VulkanUtils.hpp"

namespace winWrap
{
	struct Test
	{
		void teest(int a, int b)
		{
			std::cout << a + b << std::endl;
		}
	};

	Window::Window()
		: m_platformWindow(nullptr),
	  	  m_isClosed(true),
	  	  keyPressed(m_keyPressed),
	  	  keyReleased(m_keyReleased),
	  	  resized(m_resizeEvent),
		  mouseMoved(m_mouseMoved),
		  closed(m_closeEvent) {}

	Window::Window(const std::string &title, const WindowParams &params)
		: m_title(title),
	  	  m_isClosed(false),
		  keyPressed(m_keyPressed),
		  keyReleased(m_keyReleased),
		  resized(m_resizeEvent),
		  mouseMoved(m_mouseMoved),
		  closed(m_closeEvent)
	{
		m_platformWindow = createSpecificPlatformWindow();
		m_platformWindow->init(title, params);	
	}

	Window::~Window()
	{
		destroy();
	}

	bool Window::init(const std::string &title, const WindowParams &params)
	{
		close();
		destroy();

		Callback<int, int> test;

		m_title = title;
		m_isClosed = false;

		if (m_platformWindow == nullptr)
			m_platformWindow = createSpecificPlatformWindow();

		return m_platformWindow->init(title, params);
	}

	bool Window::isClosed() const
	{
		return m_platformWindow == nullptr || m_isClosed;
	}

	void Window::close()
	{
		m_closeEvent();
		m_isClosed = true;
	}

	void Window::destroy()
	{
		if (m_platformWindow == nullptr) return;
		m_platformWindow.reset();
	}

	i32 Window::getWidth() const
	{
		return m_platformWindow != nullptr ? m_platformWindow->getWidth() : 0;
	}

	i32 Window::getHeight() const
	{
		return m_platformWindow != nullptr ? m_platformWindow->getHeight() : 0;
	}

	Size Window::getSize() const
	{
		static Size errSize(1);
		return m_platformWindow != nullptr ? m_platformWindow->getSize() : errSize;
	}

	ivec2 Window::getPosition() const
	{
		static ivec2 err(0);
		return m_platformWindow != nullptr ? m_platformWindow->getPosition() : err;
	}

	void Window::setPosition(const ivec2 &position)
	{
		if (m_platformWindow == nullptr) return;

		m_platformWindow->setPosition(position);
	}

	const std::string &Window::getTitle() const
	{
		return m_title;
	}

	void Window::setTitle(const std::string &title)
	{
		if (m_platformWindow == nullptr) return;

		m_title = title;
		m_platformWindow->setTitle(title);
	}

	WindowParams Window::getParams()
	{
		return WindowParams(getWidth(), getHeight(), getPosition(), "");
	}

	void Window::pollEvents()
	{
		InternalEvent event{};
		while(m_platformWindow && m_platformWindow->pollEvents(event))
		{
			std::future<void> handle = std::async(std::launch::async, [&]()
			{
				switch (event.type)
				{
				case EventType::KeyPressed:
					m_keyPressed(*this, event.key);
					break;
				case EventType::KeyReleased:
					m_keyReleased(*this, event.key);
					break;
				case EventType::Resized:
					m_resizeEvent(*this, event.size);
					break;
				case EventType::MouseMoved:
					m_mouseMoved(*this, event.mousePos);
					break;
				case EventType::Closed:
					close();
					break;
				default:
					break;
				}
			});
		}
	}

	bool Window::createVulkanSurface(VkInstance instance, VkSurfaceKHR &surface)
	{
		return m_platformWindow->createVulkanSurface(instance, surface);
	}

	std::vector<const char *> Window::getVulkanExtensions()
	{
		return getRequiredExtensions();
	}

	std::unique_ptr<IPlatformWindow> Window::createSpecificPlatformWindow()
	{
		return std::make_unique<PlatformWindow>();
	}
}

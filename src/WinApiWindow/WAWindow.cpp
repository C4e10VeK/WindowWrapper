#include "WAWindow.hpp"
#include <windowsx.h>

#include <iostream>

#include "../Common/InputUtils.hpp"
#include "../Common/VulkanUtils.hpp"

namespace winWrap
{
	void PlatformWindow::InternalEventList::push(const InternalEvent &event)
	{
		m_events.emplace(event);
	}

	InternalEvent PlatformWindow::InternalEventList::pop()
	{
		InternalEvent res = m_events.front();
		m_events.pop();
		return res;
	}

	bool PlatformWindow::InternalEventList::isEmpty() const
	{
		return m_events.empty();
	}

	PlatformWindow::~PlatformWindow()
	{
		DestroyWindow(m_windowHandle);
		FreeModule(m_windowInstance);
	}

	bool PlatformWindow::init(const std::string &title,  const WindowParams &params)
	{
		return createSpecificPlatformWindow(title, params);
	}

	// TODO: set title return error
	void PlatformWindow::setTitle(const std::string &title)
	{
		SetWindowText(m_windowHandle, title.c_str());

		std::cout << "Error in " << __func__ << ": " << GetLastError() << std::endl;
	}

	i32 PlatformWindow::getWidth() const
	{
		RECT wRect;
		GetClientRect(m_windowHandle, &wRect);
		return wRect.right - wRect.left;
	}

	i32 PlatformWindow::getHeight() const
	{
		RECT wRect;
		GetClientRect(m_windowHandle, &wRect);
		return wRect.bottom - wRect.top;
	}

	Size PlatformWindow::getSize() const
	{
		RECT wRect;
		GetClientRect(m_windowHandle, &wRect);
		return {wRect.right - wRect.left, wRect.bottom - wRect.top};
	}

	Size PlatformWindow::getWindowSize() const
	{
		RECT wRect;
		GetWindowRect(m_windowHandle, &wRect);
		return {wRect.right - wRect.left, wRect.bottom - wRect.top};
	}

	ivec2 PlatformWindow::getPosition() const
	{
		return ivec2(0);
	}

	void PlatformWindow::setPosition(const ivec2 &position)
	{
		SetWindowPos(m_windowHandle, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	void PlatformWindow::setResizable(bool resizable)
	{

	}

	bool PlatformWindow::pollEvents(InternalEvent &event)
	{
		MSG msg{};
		while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (!m_eventList.isEmpty())
		{
			event = m_eventList.pop();
			return true;
		}

		return false;
	}

	bool PlatformWindow::createVulkanSurface(VkInstance instance, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *surface)
	{
		return createVulkanSurfacePr(instance, *this, pAllocator, surface);
	}

	bool PlatformWindow::createVulkanSurface(VkInstance instance, VkSurfaceKHR &surface)
	{
		return createVulkanSurfacePr(instance, *this, nullptr, &surface);
	}

	bool PlatformWindow::createSpecificPlatformWindow(const std::string &title, const WindowParams &params)
	{
		m_windowInstance = GetModuleHandle(nullptr);

		if (m_windowInstance == nullptr)
			return false;

		if (!createWindowClass(title))
		{
			std::cerr << "Error windowclass create: " << GetLastError() << std::endl;
			return false;
		}

		DWORD dwStyle = WS_OVERLAPPEDWINDOW;

		if (!params.resizeable)
			dwStyle ^= WS_THICKFRAME;

		m_windowHandle = CreateWindowExA(
				0,
				title.c_str(),
				title.c_str(),
				dwStyle,
				params.position.x, params.position.y,
				params.size.width, params.size.height,
				nullptr, nullptr, m_windowInstance, nullptr
			);

		if (m_windowHandle == nullptr)
		{
			std::cerr << "Error window create: " << GetLastError() << std::endl;
			return false;
		}

		SetWindowLongPtr(m_windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		m_callback = SetWindowLongPtr(m_windowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&PlatformWindow::windowProc));

		ShowWindow(m_windowHandle, 1);

		return true;
	}

	bool PlatformWindow::createWindowClass(const std::string &title)
	{
		WNDCLASSEX wcex = { 0 };

		wcex.cbSize = sizeof(wcex);
		wcex.lpfnWndProc = &PlatformWindow::windowProc;
		wcex.cbWndExtra = 0;
		wcex.cbClsExtra = 0;
		wcex.hInstance = m_windowInstance;
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.lpszClassName = title.c_str();
		wcex.lpszMenuName = title.c_str();

		return RegisterClassEx(&wcex);
	}

	LRESULT PlatformWindow::windowProcess(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_CLOSE:
				{
					InternalEvent event{};
					event.type = EventType::Closed;
					m_eventList.push(event);
				}
				return 0;
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				{
					InternalEvent event{};
					event.type = EventType::KeyPressed;
					event.key = specificPlatformKeyToKey({wParam, lParam});
					m_eventList.push(event);
				}
				break;
			case WM_KEYUP:
			case WM_SYSKEYUP:
				{
					InternalEvent event{};
					event.type = EventType::KeyReleased;
					event.key = specificPlatformKeyToKey({wParam, lParam});
					m_eventList.push(event);
				}
				break;
			case WM_SIZE:
				{
					InternalEvent event;
					event.type = EventType::Resized;
					event.size = getSize();
					m_eventList.push(event);
				}
				break;
			case WM_LBUTTONDOWN:
				{
					InternalEvent event;
					event.type = EventType::MouseButtonPressed;
					event.mouseBtn = Button::Left;
					m_eventList.push(event);
				}
				break;
			case WM_LBUTTONUP:
				{
					InternalEvent event;
					event.type = EventType::MouseButtonReleased;
					event.mouseBtn = Button::Left;
					m_eventList.push(event);
				}
				break;
			case WM_RBUTTONDOWN:
				{
					InternalEvent event;
					event.type = EventType::MouseButtonPressed;
					event.mouseBtn = Button::Right;
					m_eventList.push(event);
				}
				break;
			case WM_RBUTTONUP:
				{
					InternalEvent event;
					event.type = EventType::MouseButtonReleased;
					event.mouseBtn = Button::Right;
					m_eventList.push(event);
				}
				break;
			case WM_MBUTTONDOWN:
				{
					InternalEvent event;
					event.type = EventType::MouseButtonPressed;
					event.mouseBtn = Button::Middle;
					m_eventList.push(event);
				}
				break;
			case WM_MBUTTONUP:
				{
					InternalEvent event;
					event.type = EventType::MouseButtonReleased;
					event.mouseBtn = Button::Middle;
					m_eventList.push(event);
				}
				break;
			case WM_MOUSEMOVE:
				{
					InternalEvent event;
					event.type = EventType::MouseMoved;
					event.mousePos = dvec2(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
					m_eventList.push(event);
				}
				break;
			default:
				break;
		}

		return DefWindowProc(m_windowHandle, uMsg, wParam, lParam);
	}

	LRESULT CALLBACK PlatformWindow::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		PlatformWindow *pWindow = reinterpret_cast<PlatformWindow *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		if (pWindow == nullptr) return DefWindowProc(hwnd, uMsg, wParam, lParam);

		LRESULT res = pWindow->windowProcess(uMsg, wParam, lParam);

		return res;
	}
}

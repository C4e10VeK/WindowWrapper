#include "WAWindow.hpp"

#include <iostream>

#include <Common/InternalEvent.hpp>

namespace winWrap
{
	PlatformWindow::~PlatformWindow()
	{
		DestroyWindow(m_windowHandle);
		FreeModule(m_windowInstance);
	}

	bool PlatformWindow::init(const std::string &title,  const WindowParams &params)
	{
		return createSpecificPlatformWindow(title, params);
	}

	void PlatformWindow::setTitle(const std::string &title)
	{
		SetWindowText(m_windowHandle, title.c_str());

		std::cout << "Error in " << __func__ << ": " << GetLastError() << std::endl;
	}

	i32 PlatformWindow::getWidth() const
	{
		RECT wRect;
		GetWindowRect(m_windowHandle, &wRect);
		return wRect.right;
	}

	i32 PlatformWindow::getHeight() const
	{
		RECT wRect;
		GetWindowRect(m_windowHandle, &wRect);
		return wRect.bottom;
	}

	const ivec2 &PlatformWindow::getPosition() const
	{
		static ivec2 o(0);
		return o;
	}

	void PlatformWindow::setPosition(const ivec2 &position)
	{
		SetWindowPos(m_windowHandle, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}

	bool PlatformWindow::pollEvent(InternalEvent &event)
	{

	}

	bool PlatformWindow::createSpecificPlatformWindow(const std::string &title, const WindowParams &params)
	{
		m_windowInstance = GetModuleHandle(nullptr);

		if (m_windowInstance == nullptr)
			return false;

		if (!createWindowClass())
		{
			std::cerr << "Error windowclass create: " << GetLastError() << std::endl;
			return false;
		}

		m_windowHandle = CreateWindowExA(
				0,
				title.c_str(),
				title.c_str(),
				WS_OVERLAPPEDWINDOW,
				params.position.x, params.position.y,
				params.width, params.height,
				nullptr, nullptr, m_windowInstance, nullptr
			);

		if (m_windowHandle == nullptr)
		{
			std::cerr << "Error window create: " << GetLastError() << std::endl;
			return false;
		}

		SetWindowLongPtr(m_windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

		ShowWindow(m_windowHandle, 1);

		return true;
	}

	bool PlatformWindow::createWindowClass(const std::string &title)
	{
		WNDCLASSEX wcex = { 0 };

		wcex.cbSize = sizeof(wcex);
		wcex.lpfnWndProc = &PlatformWindow::WindowProc;
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

	LRESULT CALLBACK PlatformWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		PlatformWindow *pWindow = reinterpret_cast<PlatformWindow *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		if (pWindow == nullptr) return DefWindowProc(hwnd, uMsg, wParam, lParam);

		switch (uMsg)
		{
			case WM_DESTROY:
				{

				}
				break;
			case WM_KEYDOWN:
				{

				}
				break;
			case WM_KEYUP:
				{

				}
				break;
			default:
				return 0;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
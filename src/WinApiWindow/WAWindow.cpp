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
		m_title = title;
		m_params = params;
		m_isClosed = false;

		return createSpecificPlatformWindow();
	}

	bool PlatformWindow::isClosed() const
	{
		return m_isClosed;
	}

	void PlatformWindow::close()
	{
		m_isClosed = true;
	}

	const std::string &PlatformWindow::getTitle() const
	{
		return m_title;
	}

	void PlatformWindow::setTitle(const std::string &title)
	{
		m_title = title;
		SetWindowText(m_windowHandle, m_title.c_str());

		std::cout << "Error in " << __func__ << ": " << GetLastError() << std::endl;
	}

	i32 PlatformWindow::getWidth() const
	{
		return m_params.width;
	}

	i32 PlatformWindow::getHeight() const
	{
		return m_params.height;
	}

	const ivec2 &PlatformWindow::getPosition() const
	{
		return m_params.position;
	}

	void PlatformWindow::setPosition(const ivec2 &position)
	{
		m_params.position = position;
	}

	bool PlatformWindow::pollEvent(InternalEvent &event)
	{

	}

	bool PlatformWindow::createSpecificPlatformWindow()
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
				m_title.c_str(),
				m_title.c_str(),
				WS_OVERLAPPEDWINDOW,
				m_params.position.x, m_params.position.y,
				m_params.width, m_params.height,
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

	bool PlatformWindow::createWindowClass()
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
		wcex.lpszClassName = m_title.c_str();
		wcex.lpszMenuName = m_title.c_str();

		return RegisterClassEx(&wcex);
	}

	LRESULT CALLBACK PlatformWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		auto *pWindow = reinterpret_cast<PlatformWindow *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		if (pWindow == nullptr) return DefWindowProc(hwnd, uMsg, wParam, lParam);

		switch (uMsg)
		{
			case WM_DESTROY:
				{
					pWindow->close();
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
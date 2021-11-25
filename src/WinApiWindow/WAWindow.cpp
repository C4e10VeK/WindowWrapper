#include <Common/Window.hpp>

#include <iostream>

namespace winWrap
{
	PlatformWindow::PlatformWindow(std::string title, const WindowParams &params)
		: m_params(params),
		  m_title(std::move(title)),
		  m_isClosed(false) { init(); }

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

	void PlatformWindow::pollEvent()
	{
		while (PeekMessage(&m_winMsg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_winMsg);
			DispatchMessage(&m_winMsg);

			if (m_winMsg.message == WM_QUIT)
				close();
		}
	}

	bool PlatformWindow::createSpecificPlatformWindow()
	{
		m_windowInstance = GetModuleHandle(nullptr);

		WNDCLASS wc = WNDCLASS();

		wc.lpfnWndProc = &PlatformWindow::WindowProc;
		wc.hInstance = m_windowInstance;
		wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wc.lpszClassName = m_title.c_str();
		wc.lpszMenuName = m_title.c_str();
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

		if (!RegisterClass(&wc))
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
					pWindow->m_KeyPressed(*pWindow, wParam);
				}
				break;
			default:
				break;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
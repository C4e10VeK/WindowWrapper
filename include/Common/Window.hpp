#ifndef WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP
#define WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP

#if defined(_WIN32) || defined(__MINGW32__)
#include <windows.h>
#define WINDOWS_COMPILE
#elif defined(__linux) && !defined(__MINGW32__)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#define LINUX_COMPILE
#endif

#include "IPlatformWindow.hpp"
#include "WindowParams.hpp"
#include "Event.hpp"

namespace winWrap
{

	class PlatformWindow final : public IPlatformWindow
{
	private:
		using KeyPressEvent = Event<IWindow&, u32>;

#ifdef WINDOWS_COMPILE
		MSG m_winMsg;
		HWND m_windowHandle;
		HDC m_hdc;
		HINSTANCE m_windowInstance;
#elif defined(LINUX_COMPILE)
		::Window m_xWindow{};
		Display *m_display{};
		int m_screen{};
		Atom m_atomDeleteWindow{};
#endif

		WindowParams m_params;
		std::string m_title;

		bool m_isClosed;

		KeyPressEvent m_KeyPressed;
	public:
		KeyPressEvent::IType &keyPressed{m_KeyPressed};

		PlatformWindow() : m_params(), m_title(), m_isClosed(true) { }
		PlatformWindow(std::string title, const WindowParams &params);

		~PlatformWindow() override;

		bool init(const std::string &title, const WindowParams &params) override;

		bool isClosed() const override;
		void close() override;

		i32 getWidth() const override;
		i32 getHeight() const override;

		const ivec2 &getPosition() const override;
		void setPosition(const ivec2 &position) override;

		const WindowParams &getParams() const;

		const std::string &getTitle() const override;
		void setTitle(const std::string &title) override;

		void setResizable(bool resizable);

		void pollEvent() override;

	private:
		bool createSpecificPlatformWindow();
		void init()
		{
			if (!createSpecificPlatformWindow())
				std::abort();
		}

#ifdef WINDOWS_COMPILE
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif
	};
	using Window = PlatformWindow;
}

#endif // WINDOWWRAPPER_SRC_COMMON_WINDOW_HPP

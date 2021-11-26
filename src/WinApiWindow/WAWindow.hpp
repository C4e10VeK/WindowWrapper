#ifndef WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP
#define WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP

#include <windows.h>

#include <Common/IPlatformWindow.hpp>
#include <Common/Noncopybale.hpp>
#include <Common/Event.hpp>
#include <Common/WindowParams.hpp>

namespace winWrap
{
	class InternalEvent;

	class PlatformWindow : noncopybale, public IPlatformWindow
	{
	private:
		MSG m_winMsg;
		HWND m_windowHandle;
		HDC m_hdc;
		HINSTANCE m_windowInstance;

	public:

		PlatformWindow() = default;

		~PlatformWindow() override;

		bool init(const std::string &title, const WindowParams &params) override;

		bool isClosed() const override;
		void close() override;

		i32 getWidth() const override;
		i32 getHeight() const override;

		const ivec2 &getPosition() const override;
		void setPosition(const ivec2 &position) override;

		const WindowParams &getParams() const override;

		const std::string &getTitle() const override;
		void setTitle(const std::string &title) override;

		void setResizable(bool resizable);

		bool pollEvent(InternalEvent &event) override;

	private:
		bool createSpecificPlatformWindow();
		void init();

		bool createWindowClass();

		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}

#endif // WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP

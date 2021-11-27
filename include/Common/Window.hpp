#ifndef WINDOWWRAPPER_WINDOW_HPP
#define WINDOWWRAPPER_WINDOW_HPP

#include <memory>
#include <string>

#include "Noncopybale.hpp"
#include "IWindow.hpp"

#include "IPlatformWindow.hpp"
#include "InternalEvent.hpp"

namespace winWrap
{
	struct WindowParams;

	class Window : noncopybale, public IWindow
	{
	private:
		using KeyEvent = Event<IWindow &, Key, EventType>;
		std::unique_ptr<IPlatformWindow> m_platformWindow;

		std::string m_title;

		bool m_isClosed;

		KeyEvent m_keyEvent;
	public:
		KeyEvent::IType &keyEvent;

		Window();
		Window(std::string title, const WindowParams &params);

		bool init(const std::string &title, const WindowParams &params) override;

		bool isClosed() const override;
		void close() override;

		i32 getHeight() const override;
		i32 getWidth() const override;

		void setPosition(const ivec2 &position) override;
		const ivec2 & getPosition() const override;

		const std::string & getTitle() const override;
		void setTitle(const std::string &title) override;

		WindowParams getParams() override;

		void pollEvent() override;

	private:
		static std::unique_ptr<IPlatformWindow> createSpecificPlatformWindow();
	};
}

#endif // WINDOWWRAPPER_WINDOW_HPP

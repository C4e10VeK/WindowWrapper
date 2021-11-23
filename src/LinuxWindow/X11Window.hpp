#ifndef WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP
#define WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP

#include <string>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "../Common/Types.hpp"
#include "../Common/IPlatformWindowBase.hpp"
#include "../Common/Event.hpp"

#include "../Common/VectorT.hpp"
#include "../Common/WindowParams.hpp"

namespace winWrap
{
	class PlatformWindow final : public IPlatformWindowBase
	{
	private:
		using KeyPressEvent = Event<IWindow&, u32>;

		::Window m_xWindow{};
		Display *m_display{};
		int m_screen{};
		Atom m_atomDeleteWindow{};

		int m_width;
		int m_height;
		ivec2 m_position;

		std::string m_title;

		bool m_isClosed{false};

		KeyPressEvent m_KeyPressed;
	public:
		KeyPressEvent::IType &keyPressed{m_KeyPressed};

		PlatformWindow() = default;
		PlatformWindow(std::string title, i32 width, i32 height);

		~PlatformWindow() override;

		bool init(const std::string &title, i32 width, i32 height) override;

		bool isClosed() const override;
		void close() override;

		i32 getWidth() const override;
		i32 getHeight() const override;

		const ivec2 &getPosition() const;
		void setPosition(const ivec2 &position);

		const std::string &getTitle() const override;
		void setTitle(const std::string &title) override;

		void setResizable(bool resizable);

		void pollEvent() override;
	};
}
#endif // WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP

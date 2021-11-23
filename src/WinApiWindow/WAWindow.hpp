#ifndef WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP
#define WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP

#include "../Common/IPlatformWindowBase.hpp"
#include "../Common/Types.hpp"
#include "../Common/Event.hpp"

namespace winWrap
{
	class PlatformWindow : public IPlatformWindowBase
	{
	private:
		using KeyPressed = Event<IWindow &, u32>;

		std::string m_title;

		KeyPressed m_keyPressed;
	public:
		KeyPressed::IType &keyPressed{m_keyPressed};

		bool init(const std::string &title, int width, int height) override;

		bool isClosed() const override;
		void close() override;

		const std::string &getTitle() const override;
		void setTitle(const std::string &title) override;

		i32 getWidth() const override;
		i32 getHeight() const override;

		void pollEvent() override;
	};
}


#endif // WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP

#ifndef WINDOWWRAPPER_WINDOW_HPP
#define WINDOWWRAPPER_WINDOW_HPP

#include <memory>
#include <string>

#include "Noncopybale.hpp"
#include "IWindow.hpp"
#include "Vulkan.hpp"

#include "IPlatformWindow.hpp"
#include "InternalEvent.hpp"

namespace winWrap
{
	struct WindowParams;

	class Window : noncopybale, public IWindow
	{
	private:
		using KeyPressedEvent = Event<IWindow &, Key>;
		using KeyReleasedEvent = Event<IWindow &, Key>;
		using ResizeEvent = Event<IWindow &, Size>;
		using CloseEvent = Event<>;

		std::unique_ptr<IPlatformWindow> m_platformWindow;

		std::string m_title;

		bool m_isClosed;

		KeyPressedEvent m_keyPressed;
		KeyReleasedEvent m_keyReleased;
		ResizeEvent m_resizeEvent;
		CloseEvent m_closeEvent;
	public:
		KeyPressedEvent::IType &keyPressed;
		KeyReleasedEvent::IType &keyReleased;
		ResizeEvent::IType &resizeEvent;
		CloseEvent::IType &closeEvent;

		Window();
		Window(std::string title, const WindowParams &params);

		~Window();

		bool init(const std::string &title, const WindowParams &params) override;

		[[nodiscard]] bool isClosed() const override;
		void close() override;

		void destroy();

		[[nodiscard]] i32 getHeight() const override;
		[[nodiscard]] i32 getWidth() const override;

		[[nodiscard]] Size getSize() const override;

		[[nodiscard]] ivec2 getPosition() const override;
		void setPosition(const ivec2 &position) override;

		[[nodiscard]] const std::string &getTitle() const override;
		void setTitle(const std::string &title) override;

		WindowParams getParams() override;

		void pollEvent() override;

		bool createVulkanSurface(VkInstance instance, VkSurfaceKHR &surface);

		static std::vector<const char*> getVulkanExtensions();
	private:
		static std::unique_ptr<IPlatformWindow> createSpecificPlatformWindow();
	};
}

#endif // WINDOWWRAPPER_WINDOW_HPP

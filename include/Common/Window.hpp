#ifndef WINDOWWRAPPER_WINDOW_HPP
#define WINDOWWRAPPER_WINDOW_HPP

#include <memory>
#include <string>
#include <vector>

#include "Noncopybale.hpp"
#include "Callback.hpp"
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
		using KeyPressedCallback = Callback<IWindow &, Key>;
		using KeyReleasedCallback = Callback<IWindow &, Key>;
		using ResizeCallback = Callback<IWindow &, Size>;
		using MouseMoveCallback = Callback<IWindow &, dvec2>;
		using CloseCallback = Callback<>;

		std::unique_ptr<IPlatformWindow> m_platformWindow;

		std::string m_title;

		bool m_isClosed;

		KeyPressedCallback m_keyPressed;
		KeyReleasedCallback m_keyReleased;
		ResizeCallback m_resizeEvent;
		MouseMoveCallback m_mouseMoved;
		CloseCallback m_closeEvent;
	public:
		KeyPressedCallback::IType &keyPressed;
		KeyReleasedCallback::IType &keyReleased;
		ResizeCallback::IType &resized;
		MouseMoveCallback::IType &mouseMoved;
		CloseCallback::IType &closed;

		Window();
		Window(const std::string &title, const WindowParams &params);

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

		void pollEvents() override;

		bool createVulkanSurface(VkInstance instance, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *surface);

		bool createVulkanSurface(VkInstance instance, VkSurfaceKHR &surface);

		static std::vector<const char*> getVulkanExtensions();
	private:
		static std::unique_ptr<IPlatformWindow> createSpecificPlatformWindow();
	};
}

#endif // WINDOWWRAPPER_WINDOW_HPP

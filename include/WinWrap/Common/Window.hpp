#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Noncopyable.hpp"
#include "Callback.hpp"
#include "IWindow.hpp"
#include "Vulkan.hpp"

#include "IPlatformWindow.hpp"
#include "InternalEvent.hpp"

namespace winWrap
{
	struct WindowParams;

	class Window : noncopyable, public IWindow
	{
	private:
		using KeyPressedCallback = Callback<IWindow &, Key>;
		using KeyReleasedCallback = Callback<IWindow &, Key>;
		using ResizeCallback = Callback<IWindow &, Size>;
		using MouseButtonPressedCallback = Callback<IWindow &, Button>;
		using MouseButtonReleasedCallback = Callback<IWindow &, Button>;
		using MouseMoveCallback = Callback<IWindow &, dvec2>;
		using CloseCallback = Callback<>;

		std::unique_ptr<IPlatformWindow> m_platformWindow;

		std::string m_title;

		bool m_isClosed;

		KeyPressedCallback m_keyPressed;
		KeyReleasedCallback m_keyReleased;
		ResizeCallback m_resizeEvent;
		MouseButtonPressedCallback m_mouseButtonPressed;
		MouseButtonReleasedCallback m_mouseButtonReleased;
		MouseMoveCallback m_mouseMoved;
		CloseCallback m_closeEvent;
	public:
		KeyPressedCallback::IType &keyPressed;
		KeyReleasedCallback::IType &keyReleased;
		ResizeCallback::IType &resized;
		MouseButtonPressedCallback::IType &mouseButtonPressed;
		MouseButtonReleasedCallback::IType &mouseButtonReleased;
		MouseMoveCallback::IType &mouseMoved;
		CloseCallback::IType &closed;

		Window();

		/**
		 * @brief Construct a new Window by params. Closes the program if window creation failed
		 * 
		 * @param title 
		 * @param params 
		 */
		Window(const std::string &title, const WindowParams &params);

		~Window();

		/**
		 * @brief init window by params
		 * 
		 * @param title 
		 * @param params 
		 * @return true if window was created without error else false. 
		 */
		bool init(const std::string &title, const WindowParams &params) override;

		/**
		 * @brief check window is closed
		 * 
		 * @return true if window closed else false
		 */
		[[nodiscard]] bool isClosed() const override;

		/**
		 * @brief Close window
		 * 
		 */
		void close() override;

		void destroy();

		/**
		 * @brief Get the window height
		 * 
		 * @return i32 
		 */
		[[nodiscard]] i32 getHeight() const override;

		/**
		 * @brief Get the window width
		 * 
		 * @return i32 
		 */
		[[nodiscard]] i32 getWidth() const override;

		/**
		 * @brief Get the window size
		 * 
		 * @return Size 
		 */
		[[nodiscard]] Size getSize() const override;

		[[nodiscard]] Size getWindowSize() const override;

		/**
		 * @brief Get the window position
		 * 
		 * @return ivec2 
		 */
		[[nodiscard]] ivec2 getPosition() const override;

		/**
		 * @brief Set the window position
		 * 
		 * @param position 
		 */
		void setPosition(const ivec2 &position) override;

		/**
		 * @brief Get the window title
		 * 
		 * @return const std::string& 
		 */
		[[nodiscard]] const std::string &getTitle() const override;

		/**
		 * @brief Set the window title
		 * 
		 * @param title 
		 */
		void setTitle(const std::string &title) override;

		/**
		 * @brief Get the window params
		 * 
		 * @return WindowParams 
		 */
		WindowParams getParams() override;

		/**
		 * @brief poll window events
		 * 
		 */
		void pollEvents() override;

		/**
		 * @brief Create a Vulkan Surface
		 * 
		 * @param instance 
		 * @param pAllocator 
		 * @param surface 
		 * @return true if vksurface was created and return VK_SUCCESS else false
		 */
		bool createVulkanSurface(VkInstance instance, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *surface);

		/**
		 * @brief Create a Vulkan Surface
		 * 
		 * @param instance 
		 * @param surface 
		 * @return true if vksurface was created and return VK_SUCCESS else false
		 */
		bool createVulkanSurface(VkInstance instance, VkSurfaceKHR &surface);

		/**
		 * @brief Get the Required Vulkan Extensions
		 * 
		 * @return std::vector<const char*> 
		 */
		static std::vector<const char*> getVulkanExtensions();
	private:
		static std::unique_ptr<IPlatformWindow> createSpecificPlatformWindow();
	};
}


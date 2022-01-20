#ifndef WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP
#define WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP

#include <queue>

#include <windows.h>

#include <Common/IPlatformWindow.hpp>
#include <Common/Noncopybale.hpp>
#include <Common/WindowParams.hpp>
#include <Common/InternalEvent.hpp>

#include "Common/VulkanUtils.hpp"

namespace winWrap
{
	class PlatformWindow : noncopybale, public IPlatformWindow
	{
	private:
		MSG m_winMsg{};
		HWND m_windowHandle{nullptr};
		HDC m_hdc{nullptr};
		HINSTANCE m_windowInstance{nullptr};
		LONG_PTR m_callback;

		class InternalEventList final
		{
		private:
			std::queue<InternalEvent> m_events;
		public:
			void push(const InternalEvent &event);
			InternalEvent pop();
			bool isEmpty() const;
		};

		InternalEventList m_eventList;

		friend VkResult createVulkanSurfacePr(VkInstance instance, PlatformWindow &window, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR *surface);
		friend bool createVulkanSurfacePr(VkInstance instance, PlatformWindow &window, VkSurfaceKHR &surface);
	public:

		PlatformWindow() = default;

		~PlatformWindow() override;

		bool init(const std::string &title, const WindowParams &params) override;

		[[nodiscard]] i32 getWidth() const override;
		[[nodiscard]] i32 getHeight() const override;

		[[nodiscard]] Size getSize() const override;

		[[nodiscard]] ivec2 getPosition() const override;
		void setPosition(const ivec2 &position) override;

		void setTitle(const std::string &title) override;

		void setResizable(bool resizable) override;

		bool pollEvents(InternalEvent &event) override;

		bool createVulkanSurface(VkInstance instance, VkSurfaceKHR &surface) override;
	private:
		bool createSpecificPlatformWindow(const std::string &title, const WindowParams &params);
		bool createWindowClass(const std::string &title);

		LRESULT windowProcess(UINT uMsg, WPARAM wParam, LPARAM lParam);

		static LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}

#endif // WINDOWWRAPPER_SRC_WINAPIWINDOW_WAWINDOW_HPP

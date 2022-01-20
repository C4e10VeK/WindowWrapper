#ifndef WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP
#define WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <Common/IPlatformWindow.hpp>
#include <Common/Noncopybale.hpp>
#include <Common/WindowParams.hpp>

#include "../Common/VulkanUtils.hpp"

namespace winWrap
{

	struct InternalEvent;

	class PlatformWindow final : noncopybale, public IPlatformWindow
	{
	private:
		::Window m_xWindow{};
		Display *m_display{};
		int m_screen{};

		struct Atoms
		{
			Atom atomDeleteWindow;
			Atom atomResizeWindow;
			Atom atomSize;
			Atom atomWMIcon;
		};

		Atoms m_atoms;

		friend class Window;
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

		void initAtoms();
	};
}

#endif // WINDOWWRAPPER_SRC_LINUXWINDOW_X11WINDOW_HPP

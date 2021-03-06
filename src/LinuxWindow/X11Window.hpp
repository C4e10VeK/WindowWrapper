#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <WinWrap/Common/IPlatformWindow.hpp>
#include <WinWrap/Common/Noncopyable.hpp>
#include <WinWrap/Common/WindowParams.hpp>

namespace winWrap
{

	struct InternalEvent;

	class PlatformWindow final : noncopyable, public IPlatformWindow
	{
	private:
		struct Atoms
		{
			Atom atomDeleteWindow;	
			Atom atomWMPing;
		};

		Atoms m_atoms;
		::Window m_xWindow{};
		Display *m_display{};
		int m_screen{};

		Size m_prevSize{};

		friend class Window;
		friend bool createVulkanSurfacePr(VkInstance instance, PlatformWindow &window, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR *surface);
	public:	
		PlatformWindow() = default;

		~PlatformWindow() override;

		bool init(const std::string &title, const WindowParams &params) override;

		[[nodiscard]] i32 getWidth() const override;
		[[nodiscard]] i32 getHeight() const override;

		[[nodiscard]] Size getSize() const override;
		[[nodiscard]] Size getWindowSize() const override;

		[[nodiscard]] ivec2 getPosition() const override;
		void setPosition(const ivec2 &position) override;

		void setTitle(const std::string &title) override;

		void setResizable(bool resizable) override;

		bool pollEvents(InternalEvent &event) override;

		bool createVulkanSurface(VkInstance instance, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR *surface) override;

		bool createVulkanSurface(VkInstance instance, VkSurfaceKHR &surface) override;
	private:
		bool createSpecificPlatformWindow(const std::string &title, const WindowParams &params);

		void initAtoms();
	};
}


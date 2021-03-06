#pragma once

#include <string>
#include "Types.hpp"
#include "Vulkan.hpp"

namespace winWrap
{
	template <typename T>
	struct vec2;

	using ivec2 = vec2<i32>;
	using Size = ivec2;

	struct InternalEvent;
	struct WindowParams;

	class IPlatformWindow
	{
	public:
		virtual ~IPlatformWindow() = default;

		virtual bool init(const std::string &title, const WindowParams &params) = 0;

		[[nodiscard]] virtual i32 getWidth() const = 0;
		[[nodiscard]] virtual i32 getHeight() const = 0;

		[[nodiscard]] virtual Size getSize() const = 0;
		[[nodiscard]] virtual Size getWindowSize() const = 0;

		[[nodiscard]] virtual ivec2 getPosition() const = 0;
		virtual void setPosition(const ivec2 &position) = 0;

		virtual void setTitle(const std::string &title) = 0;

		virtual void setResizable(bool resizable) = 0;

		virtual bool pollEvents(InternalEvent &event) = 0;

		virtual bool createVulkanSurface(VkInstance instance, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *surface) = 0;

		virtual bool createVulkanSurface(VkInstance instance, VkSurfaceKHR &surface) = 0;
	};	
}


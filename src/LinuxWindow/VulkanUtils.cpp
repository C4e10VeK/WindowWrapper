#include "../Common/VulkanUtils.hpp"
#include "X11Window.hpp"
#include <dlfcn.h>
#include <cstring>

struct VkXlibSurfaceCreateInfoKHR {
	VkStructureType				   sType;
	const void*					   pNext;
	winWrap::u32 				   flags;
	Display*					   dpy;
	Window						   window;
};

using PFN_vkCreateXlibSurfaceKHR = VkResult (VK_API_CALL *)(VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

namespace winWrap
{
	class VulkanWrapper
	{
	private:
		void *m_vkLibrary;
	public:
		PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
		PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;

		VulkanWrapper()
			: m_vkLibrary(nullptr),
			  vkGetInstanceProcAddr(nullptr),
			  vkEnumerateInstanceExtensionProperties(nullptr) { }

		~VulkanWrapper()
		{
			closeLib();
		}

		bool loadLib()
		{
			if (m_vkLibrary)
				return true;

			m_vkLibrary = dlopen("libvulkan.so.1", RTLD_LAZY | RTLD_LOCAL);
			if (m_vkLibrary == nullptr)
				return false;

			vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>( dlsym(m_vkLibrary, "vkGetInstanceProcAddr"));
			if (vkGetInstanceProcAddr == nullptr)
			{
				closeLib();
				return false;
			}

			vkEnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(dlsym(m_vkLibrary, "vkEnumerateInstanceExtensionProperties"));
			if (vkEnumerateInstanceExtensionProperties == nullptr)
			{
				closeLib();
				return false;
			}

			return true;
		}

		bool isAvailable()
		{
			if (m_vkLibrary == nullptr)
				return false;
			
			u32 count;
			std::vector<VkExtensionProperties> properties;

			VkResult err = vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
			if (err)
			{
				closeLib();
				return false;
			}

			properties.resize(count);

			err =vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data());
			if (err)
			{
				closeLib();
				return false;
			}

			bool hasSurface = false;
			bool hasPlatformSurface = false;
			for (auto &p : properties)
			{
				if (!std::strcmp(p.extensionName, "VK_KHR_surface"))
				{
					hasSurface = true;
					continue;
				}
				if (!std::strcmp(p.extensionName, "VK_KHR_xlib_surface"))
				{
					hasPlatformSurface = true;
				}
			}

			return hasSurface && hasPlatformSurface;
		}
	private:
		void closeLib()
		{
			if (m_vkLibrary == nullptr) return;
			dlclose(m_vkLibrary);
			m_vkLibrary = nullptr;
		}

	};

	bool createVulkanSurfacePr(VkInstance instance, PlatformWindow &window, VkSurfaceKHR &surface)
	{
		VulkanWrapper vk;

		if (!vk.loadLib())
			return false;

		if (!vk.isAvailable())
			return false;

		VkXlibSurfaceCreateInfoKHR info = {
			.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR,
			.dpy = window.m_display,
			.window = window.m_xWindow
		};

		auto vkCreateXlibSurfaceKHR = reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(vk.vkGetInstanceProcAddr(instance, "vkCreateXlibSurfaceKHR"));
		if (vkCreateXlibSurfaceKHR == nullptr)
			return false;

		return (vkCreateXlibSurfaceKHR(instance, &info, nullptr, &surface) == VK_SUCCESS);
	}

	std::array<std::string, 2> getRequiredExtensions()
	{
		return {"VK_KHR_surface", "VK_KHR_xlib_surface"};
	}
}


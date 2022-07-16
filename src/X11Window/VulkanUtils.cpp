#include "../Common/VulkanUtils.hpp"
#include "X11Window.hpp"
#include <dlfcn.h>
#include <cstring>
#include <iostream>
#include <X11/Xlib-xcb.h>

struct VkXlibSurfaceCreateInfoKHR {
	VkStructureType				   sType;
	const void*					   pNext;
	winWrap::u32 				   flags;
	Display*					   dpy;
	Window						   window;
};

struct VkXcbSurfaceCreateInfoKHR {
	VkStructureType				  sType;
	const void*					  pNext;
	winWrap::u32				  flags;
	xcb_connection_t*			  connection;
	xcb_window_t				  window;
};

using PFN_vkCreateXlibSurfaceKHR = VkResult (VK_API_CALL *)(VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);
using PFN_vkCreateXcbSurfaceKHR = VkResult (VK_API_CALL *)(VkInstance instance, const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

namespace winWrap
{
	class VulkanWrapper
	{
	private:
		void *m_vkLibrary;
		bool m_avaible;
		bool m_xcbSupport;
		bool m_xlibSupport;
	public:
		PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
		PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;

		VulkanWrapper()
			: m_vkLibrary(nullptr),
			  m_avaible(false),
			  m_xcbSupport(false),
			  m_xlibSupport(false),
			  vkGetInstanceProcAddr(nullptr),
			  vkEnumerateInstanceExtensionProperties(nullptr) { }

		~VulkanWrapper()
		{
			closeLib();
		}

		void loadLib()
		{
			if (m_vkLibrary)
				return;

			m_vkLibrary = dlopen("libvulkan.so.1", RTLD_LAZY | RTLD_LOCAL);
			if (m_vkLibrary == nullptr)
				return;

			vkGetInstanceProcAddr =
				reinterpret_cast<PFN_vkGetInstanceProcAddr>( dlsym(m_vkLibrary, "vkGetInstanceProcAddr"));
			if (vkGetInstanceProcAddr == nullptr)
			{
				closeLib();
				return;
			}

			vkEnumerateInstanceExtensionProperties =
				reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(dlsym(m_vkLibrary, "vkEnumerateInstanceExtensionProperties"));
			if (vkEnumerateInstanceExtensionProperties == nullptr)
			{
				closeLib();
				return;
			}

			u32 count;
			std::vector<VkExtensionProperties> properties;

			VkResult err = vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
			if (err)
			{
				closeLib();
				return;
			}

			properties.resize(count);

			err = vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data());
			if (err)
			{
				closeLib();
				return;
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
				if (!std::strcmp(p.extensionName, "VK_KHR_xcb_surface"))
				{
					m_xcbSupport = true;
				}
				if (!std::strcmp(p.extensionName, "VK_KHR_xlib_surface"))
				{
					m_xlibSupport = true;
				}
			}

			m_avaible = hasSurface && (m_xlibSupport || m_xcbSupport);
		}

		bool isAvailable() const
		{
			return m_avaible;
		}

		bool isXcbSupport() const
		{
			return m_xcbSupport;
		}

		bool isXlibSupport() const
		{
			return m_xlibSupport;
		}
	private:
		void closeLib()
		{
			if (m_vkLibrary == nullptr) return;
			dlclose(m_vkLibrary);
			m_vkLibrary = nullptr;
		}

	};

	bool createVulkanSurfacePr(VkInstance instance, PlatformWindow &window, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR *surface)
	{
		VulkanWrapper vk;

		vk.loadLib();

		if (!vk.isAvailable())
			return false; 

		if (vk.isXcbSupport())
		{
			auto vkCreateXcbSurfaceKHR =
				reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(vk.vkGetInstanceProcAddr(instance, "vkCreateXcbSurfaceKHR"));
			if (vkCreateXcbSurfaceKHR == nullptr)
				return false;
			
			xcb_connection_t *connection = XGetXCBConnection(window.m_display);
			if (connection == nullptr)
				return false;

			VkXcbSurfaceCreateInfoKHR info = {
				.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
				.connection = connection,
				.window = static_cast<u32>(window.m_xWindow)
			};

			return vkCreateXcbSurfaceKHR(instance, &info, pAllocator, surface) == VK_SUCCESS;
		}
		if (vk.isXlibSupport())
		{
			auto vkCreateXlibSurfaceKHR = 
				reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(vk.vkGetInstanceProcAddr(instance, "vkCreateXlibSurfaceKHR"));
			if (vkCreateXlibSurfaceKHR == nullptr)
				return false;

			VkXlibSurfaceCreateInfoKHR info = {
				.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
				.dpy = window.m_display,
				.window = window.m_xWindow
			};

			return vkCreateXlibSurfaceKHR(instance, &info, pAllocator, surface) == VK_SUCCESS;
		}

		return false;
	}

	std::vector<const char *> getRequiredExtensions()
	{
		VulkanWrapper vk;
		vk.loadLib();

		if (vk.isXcbSupport())
			return {"VK_KHR_surface", "VK_KHR_xcb_surface"};
		if (vk.isXlibSupport())
			return {"VK_KHR_surface", "VK_KHR_xlib_surface"};
		
		return {};
	}
}


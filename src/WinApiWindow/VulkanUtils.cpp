#include "../Common/VulkanUtils.hpp"
#include "WAWindow.hpp"
#include <cstring>

struct VkWin32SurfaceCreateInfoKHR {
	VkStructureType					sType;
	const void*						pNext;
	winWrap::u32					flags;
	HINSTANCE						hinstance;
	HWND							hwnd;
};

using PFN_vkCreateWin32SurfaceKHR = VkResult (VK_API_CALL *)(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface);

namespace winWrap
{
	class VulkanWrapper
	{
	private:
		HMODULE m_vkLibrary;
	public:
		PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr;
		PFN_vkEnumerateInstanceExtensionProperties vkEnumerateInstanceExtensionProperties;

		VulkanWrapper()
			: m_vkLibrary(nullptr),
			  vkGetInstanceProcAddr(nullptr),
			  vkEnumerateInstanceExtensionProperties(nullptr) {}

		~VulkanWrapper()
		{
			FreeLibrary(m_vkLibrary);
		}

		bool loadLib()
		{
			if (m_vkLibrary) return true;

			m_vkLibrary = LoadLibrary("vulkan-1.dll");

			if (m_vkLibrary == nullptr)
				return false;

			vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(GetProcAddress(m_vkLibrary, "vkGetInstanceProcAddr"));
			if (vkGetInstanceProcAddr == nullptr)
			{
				closeLib();
				return false;
			}

			vkEnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(vkGetInstanceProcAddr(nullptr, "vkEnumerateInstanceExtensionProperties"));
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

			err = vkEnumerateInstanceExtensionProperties(nullptr, &count, properties.data());
			if (err)
			{
				closeLib();
				return false;
			}

			bool hasSurface = false;
			bool hasPlatformSurface = false;
			for (auto &p : properties)
			{
				if (!strcmp(p.extensionName, "VK_KHR_surface"))
				{
					hasSurface = true;
					continue;
				}
				if (!strcmp(p.extensionName, "VK_KHR_win32_surface"))
					hasPlatformSurface = true;
			}

			return hasSurface && hasPlatformSurface;
		}
	private:
		void closeLib()
		{
			if (m_vkLibrary == nullptr) return;
			FreeLibrary(m_vkLibrary);
			m_vkLibrary = nullptr;
		}
	};

	bool createVulkanSurfacePr(VkInstance instance, PlatformWindow &window, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR *surface)
	{
		VulkanWrapper vk;

		if (!vk.loadLib())
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		
		if (!vk.isAvailable())
			return VK_ERROR_EXTENSION_NOT_PRESENT;

		VkWin32SurfaceCreateInfoKHR info = {
			.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
			.hinstance = window.m_windowInstance,
			.hwnd = window.m_windowHandle
		};

		auto vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vk.vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR"));

		if (vkCreateWin32SurfaceKHR == nullptr)
			return VK_ERROR_EXTENSION_NOT_PRESENT;

		return vkCreateWin32SurfaceKHR(instance, &info, pAllocator, surface) == VK_SUCCESS;
	}

	std::vector<const char*> getRequiredExtensions()
	{
		return {"VK_KHR_surface", "VK_KHR_win32_surface"};
	}
} // namespace winWrap

#ifndef WINDOWWRAPPER_VULKAN_UTILS_HPP
#define WINDOWWRAPPER_VULKAN_UTILS_HPP

#include <vector>

#include <Common/Types.hpp>
#include <Common/Vulkan.hpp>

#ifdef _WIN32
#define VK_API_CALL __stdcall 
#else
#define VK_API_CALL
#endif

enum VkStructureType {
	VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR = 1000004000,
	VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR = 1000005000,
	VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR = 1000009000,
	VK_STRUCTURE_TYPE_MAX_ENUM = 0x7FFFFFFF
};

struct VkExtensionProperties {
	char		extensionName[256];
	uint32_t	specVersion;
};

using VkBool = winWrap::u32;

using PFN_vkVoidFunction = void (VK_API_CALL *)(void);
using PFN_vkGetInstanceProcAddr = PFN_vkVoidFunction (VK_API_CALL *)(VkInstance instance, const char* pName);
using PFN_vkEnumerateInstanceExtensionProperties = VkResult (VK_API_CALL *)(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);

namespace winWrap
{
	class PlatformWindow;

	VkResult createVulkanSurfacePr(VkInstance instance, PlatformWindow &window, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR *surface);

	bool createVulkanSurfacePr(VkInstance instance, PlatformWindow &window, VkSurfaceKHR &surface);

	std::vector<const char *> getRequiredExtensions();
} // namespace winwrap


#endif

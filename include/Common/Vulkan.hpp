#ifndef WINDOWWRAPPER_VULKAN_HPP
#define WINDOWWRAPPER_VULKAN_HPP

using VkInstance = struct VkInstance_T*;

#if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)

using VkSurfaceKHR = struct VkSurfaceKHR_T*;

#else

using VkSurfaceKHR = uint64_t;

#endif

struct VkAllocationCallbacks;

#endif
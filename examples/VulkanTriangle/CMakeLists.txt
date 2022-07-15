project(VulkanTriangle)

find_package(Vulkan REQUIRED)

add_executable(${PROJECT_NAME} VulkanTriangle.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} PRIVATE winwrap Vulkan::Vulkan)
target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/include" Vulkan::Headers)

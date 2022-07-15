project(SimpleWindow)

add_executable(${PROJECT_NAME} SimpleWindow.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_link_libraries(${PROJECT_NAME} PRIVATE winwrap)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

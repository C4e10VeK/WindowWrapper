cmake_minimum_required(VERSION 3.10)
project(WindowWrapper VERSION 0.0.1.2021)

file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_options(${PROJECT_NAME} PRIVATE)

find_package(X11 REQUIRED)

if(${X11_FOUND})
	message(STATUS "x11 found at ${X11_LIBRARIES}")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${X11_INCLUDE_DIR})


cmake_minimum_required(VERSION 3.10)
project(WindowWrapper VERSION 0.0.1.2021)

set(LIBS "")
set(INCLUDES "")

if(UNIX AND NOT APPLE AND NOT MINGW)
	set(PLATFORM_PATH "LinuxWindow")
	message(STATUS "OS Linux")
	find_package(X11 REQUIRED)
	set(LIBS ${X11_LIBRARIES} ${CMAKE_DL_LIBS})
	list(APPEND INCLUDES ${X11_INCLUDE_DIR})
elseif(WIN32 OR MINGW)
	message(STATUS "OS Windows")
	set(PLATFORM_PATH "WinApiWindow")
endif()

if(MSVC)
	message(STATUS "MSVC compiler")
elseif(MINGW)
	message(STATUS "MinGW compiler")
	set(LINK_OPTIONS -static)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	message(STATUS "Clang compiler")
endif()

file(GLOB_RECURSE HEADER_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/Common/*.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/${PLATFORM_PATH}/*.hpp")

file(GLOB_RECURSE SOURCE_FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/src/Common/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/${PLATFORM_PATH}/*.cpp")

add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/examples/SimpleWindow.cpp"  ${SOURCE_FILES} ${HEADER_FILES})
# add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES} "${CMAKE_CURRENT_SOURCE_DIR}/include")

cmake_minimum_required(VERSION 3.10)
project(WindowWrapper VERSION 0.0.1.2021)

option(WINWRAP_BUILD_SHARED "" OFF)

set(LIBS "")
set(INCLUDES "")

if(UNIX AND NOT APPLE AND NOT MINGW)
	set(PLATFORM_PATH "LinuxWindow")
	message(STATUS "OS Linux")
	find_package(X11 REQUIRED)
	set(LIBS ${X11_LIBRARIES})
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
	if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
		message(STATUS "Clang windows compiler")
	elseif (CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "GNU")
		message(STATUS "Clang linux compiler")
	endif()
endif()

file(GLOB_RECURSE HEADER_FILES
		"${CMAKE_SOURCE_DIR}/include/*.hpp"
		"${CMAKE_SOURCE_DIR}/src/Common/*.hpp"
		"${CMAKE_SOURCE_DIR}/src/${PLATFORM_PATH}/*.hpp")

file(GLOB_RECURSE SOURCE_FILES
		"${CMAKE_SOURCE_DIR}/src/Common/*.cpp"
		"${CMAKE_SOURCE_DIR}/src/${PLATFORM_PATH}/*.cpp")

if (WINWRAP_BUILD_SHARED)
	set(BUILD_TYPE SHARED)
else()
	set(BUILD_TYPE STATIC)
endif ()

#add_library(${PROJECT_NAME} ${BUILD_TYPE} ${SOURCE_FILES} ${HEADER_FILES})
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_compile_options(${PROJECT_NAME} PRIVATE -fno-omit-frame-pointer -fno-omit-frame-pointer)
target_link_options(${PROJECT_NAME} PRIVATE ${LINK_OPTIONS} -fno-omit-frame-pointer -fno-omit-frame-pointer)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES} "${CMAKE_SOURCE_DIR}/include")

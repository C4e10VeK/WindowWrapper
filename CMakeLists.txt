cmake_minimum_required(VERSION 3.10)
project(WindowWrapper VERSION 0.0.1.2021)

set(LIBS "")
set(INCLUDES "")

if(UNIX AND NOT APPLE)
	message(STATUS "OS Linux")
	if(MINGW)
		message(STATUS "MinGW compiler")
		set(PLATFORM_PATH "WinApiWindow")
		set(LINK_OPTIONS -static)
	else()
		set(PLATFORM_PATH "LinuxWindow")
		find_package(X11 REQUIRED)
		list(APPEND LIBS ${X11_LIBRARIES})
		list(APPEND INCLUDES ${X11_INCLUDE_DIR})
	endif()
elseif(WIN32)
	message(STATUS "OS Windows")
	set(PLATFORM_PATH "WinApiWindow")
	if(MSVC)
		message(STATUS "MSVC compiler")
		set(PLATFORM_PATH "WinApiWindow")
	elseif(MINGW)
		message(STATUS "MinGW compiler")
		set(LINK_OPTIONS -static)
	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
		message(STATUS "Clang compiler")
	else()
		message(FATAL_ERROR "Unsupported compiler")
	endif()
endif()

file(GLOB_RECURSE HEADER_FILES
		"${CMAKE_SOURCE_DIR}/include/*.hpp")

file(GLOB_RECURSE SOURCE_FILES
		"${CMAKE_SOURCE_DIR}/src/main.cpp"
		"${CMAKE_SOURCE_DIR}/src/Common/*.cpp"
		"${CMAKE_SOURCE_DIR}/src/${PLATFORM_PATH}/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_options(${PROJECT_NAME} PRIVATE ${LINK_OPTIONS})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES} "${CMAKE_SOURCE_DIR}/include")


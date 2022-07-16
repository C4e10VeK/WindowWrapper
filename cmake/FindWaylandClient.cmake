# Slightly modified version of https://gist.github.com/mariobadr/acc3c8adf4b4e722705be38c3deac59a

find_path(
	WaylandClient_INCLUDE_DIR
  NAMES wayland-client.h
)

find_library(
	WaylandClient_LIBRARY
  NAMES wayland-client libwayland-client
)

if(WaylandClient_INCLUDE_DIR AND WaylandClient_LIBRARY)
	add_library(Wayland::Client UNKNOWN IMPORTED)

  set_target_properties(
		Wayland::Client PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES "${WaylandClient_INCLUDE_DIR}"
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
		IMPORTED_LOCATION "${WaylandClient_LIBRARY}"
  )
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  WaylandClient
  REQUIRED_VARS WaylandClient_LIBRARY WaylandClient_INCLUDE_DIR
)

mark_as_advanced(
  WaylandClient_INCLUDE_DIR
  WaylandClient_LIBRARY
)

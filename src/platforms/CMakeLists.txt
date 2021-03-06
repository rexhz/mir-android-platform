# This needs to change whenever the ABI between the platform
# modules and the server changes in an incompatible way.
# This ABI is much smaller than the full libmirplatform ABI.
#
# TODO: Add an extra driver-ABI check target.
set(MIR_SERVER_GRAPHICS_PLATFORM_ABI 15)
set(MIR_SERVER_GRAPHICS_PLATFORM_STANZA_VERSION 0.32)  # TODO or 1.0?
set(MIR_SERVER_GRAPHICS_PLATFORM_ABI ${MIR_SERVER_GRAPHICS_PLATFORM_ABI} PARENT_SCOPE)
set(MIR_SERVER_GRAPHICS_PLATFORM_VERSION "MIR_GRAPHICS_PLATFORM_${MIR_SERVER_GRAPHICS_PLATFORM_STANZA_VERSION}")
set(MIR_SERVER_GRAPHICS_PLATFORM_VERSION ${MIR_SERVER_GRAPHICS_PLATFORM_VERSION} PARENT_SCOPE)

set(MIR_SERVER_PLATFORM_PATH
  ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/mir/server-platform
)
set(MIR_SERVER_PLATFORM_PATH
  ${MIR_SERVER_PLATFORM_PATH}
  PARENT_SCOPE
)

set(MIR_CLIENT_PLATFORM_ABI 5)
set(MIR_CLIENT_PLATFORM_STANZA_VERSION 5)
set(MIR_CLIENT_PLATFORM_ABI ${MIR_CLIENT_PLATFORM_ABI} PARENT_SCOPE)
set(MIR_CLIENT_PLATFORM_VERSION "MIR_CLIENT_PLATFORM_${MIR_CLIENT_PLATFORM_STANZA_VERSION}")
set(MIR_CLIENT_PLATFORM_VERSION ${MIR_CLIENT_PLATFORM_VERSION} PARENT_SCOPE)

set(server_common_include_dirs
  ${PROJECT_SOURCE_DIR}/include/platform
  ${PROJECT_SOURCE_DIR}/include/renderers/gl
  ${PROJECT_SOURCE_DIR}/include/renderers/sw
)

# TODO platform implementations shouldn't depend on private APIs
set(server_common_include_dirs
  ${server_common_include_dirs}
  ${CMAKE_CURRENT_SOURCE_DIR}/common/server
  ${PROJECT_SOURCE_DIR}/src/include/platform
)

set(server_symbol_map ${CMAKE_CURRENT_SOURCE_DIR}/common/server/symbols.map)

set(client_common_include_dirs
  ${PROJECT_SOURCE_DIR}/include/client
  ${CMAKE_CURRENT_SOURCE_DIR}/common/client
)

# TODO client platform implementations shouldn't depend on private APIs
set(client_common_include_dirs
  ${client_common_include_dirs}
  ${PROJECT_SOURCE_DIR}/src/include/client
)

add_subdirectory(common/)
add_subdirectory(android/)


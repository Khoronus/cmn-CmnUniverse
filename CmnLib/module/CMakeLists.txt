# Check which libraries or OS compile.
#if (USE_WIN32)
#set (COMPILE_WITH_WIN32 1)
#else()
#set (COMPILE_WITH_WIN32 0)
#endif()

if (USE_MEMORYMANAGER)
set (DO_USE_MEMORYMANAGER 1)
else()
set (DO_USE_MEMORYMANAGER 0)
endif()

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/module/cmnlibcore/inc/cmnlibcore/libdefine.hpp.in"
  "${PROJECT_SOURCE_DIR}/module/cmnlibcore/inc/cmnlibcore/libdefine.hpp"
  )

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/module/version/version.hpp.in"
  "${PROJECT_SOURCE_DIR}/module/version/version.hpp"
  )

SET( PROJ_INCLUDES  "${CMAKE_SOURCE_DIR}/module")

add_subdirectory (cmnlibcore)
add_subdirectory (ts)
add_subdirectory (container)
add_subdirectory (string)
add_subdirectory (control)
add_subdirectory (system)
add_subdirectory (cmnlibworld)

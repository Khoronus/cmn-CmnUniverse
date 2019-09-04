# Check which libraries or OS compile.

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/module/version/version.hpp.in"
  "${PROJECT_SOURCE_DIR}/module/version/version.hpp"
  )


######################################################################
# Add Common Library

SET( PROJ_INCLUDES "${CMAKE_SOURCE_DIR}/module" ${PROJ_INCLUDES_CMNLIB})
SET( PROJ_LIBRARIES_COMMON ${PROJ_LIBRARIES_COMMON_CMNLIB})

#IF(MSVC)
#   ADD_DEFINITIONS(/arch:SSE2)
#   ADD_DEFINITIONS(-D__SSE2__)
#ENDIF(MSVC)

add_subdirectory (cmnipcore)
add_subdirectory (codify)
add_subdirectory (cmnipcontainer)
add_subdirectory (draw)
add_subdirectory (feature)
add_subdirectory (filter)
add_subdirectory (graph)
add_subdirectory (group)
add_subdirectory (histogram)
add_subdirectory (measure)
add_subdirectory (photo)
add_subdirectory (signal)
add_subdirectory (transform)
add_subdirectory (morphology)
add_subdirectory (tree)
add_subdirectory (cmnipworld)
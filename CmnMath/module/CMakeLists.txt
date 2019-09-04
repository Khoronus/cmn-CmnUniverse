# Check which libraries or OS compile.
if (USE_OPENCV)
set (COMPILE_WITH_OPENCV 1)
else()
set (COMPILE_WITH_OPENCV 0)
endif()

if (USE_CMNLIB)
set (COMPILE_WITH_CMNLIB 1)
else()
set (COMPILE_WITH_CMNLIB 0)
endif()

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/module/cmnmathcore/inc/cmnmathcore/libdefine.hpp.in"
  "${PROJECT_SOURCE_DIR}/module/cmnmathcore/inc/cmnmathcore/libdefine.hpp"
  )

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

add_subdirectory (cmnmathcore)
add_subdirectory (arithmetic)
add_subdirectory (function)
add_subdirectory (algebra)
add_subdirectory (algebralinear)
add_subdirectory (coordinatesystem)
add_subdirectory (geometry)
add_subdirectory (geometricprimitive)
add_subdirectory (memory)
add_subdirectory (numericalmethod)
add_subdirectory (numericanalysis)
add_subdirectory (numericsystem)
add_subdirectory (projection)
add_subdirectory (statistics)
add_subdirectory (trigonometry)
add_subdirectory (noise)
add_subdirectory (pointcloud)
add_subdirectory (cmnmathworld)
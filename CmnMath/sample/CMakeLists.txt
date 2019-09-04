#######################################################################
macro(CREATE_EXAMPLE NAME SOURCES LIBRARIES)
	set(srcs)
	set(flsrcs)
	foreach(src ${SOURCES})
		if("${src}" MATCHES ".fl$")
         list(APPEND flsrcs ${src})
		else()
			list(APPEND srcs ${src})
		endif("${src}" MATCHES ".fl$")
	endforeach(src)

	add_executable(${NAME} ${srcs})
	include_directories(${PROJ_INCLUDES} ${PROJ_OPENCV_INCLUDES} ${Boost_INCLUDE_DIR})
	target_link_libraries(${NAME} ${LIBRARIES} ${PROJ_LIBRARIES_COMMON} ${OpenCV_LIBRARIES} ${Boost_LIBRARIES})

	# ------------------------
	# DEFINITIONS
	# ------------------------

	add_definitions(-DUNICODE -D_UNICODE)

    install(TARGETS ${NAME}
      DESTINATION ${CMAKE_INSTALL_PREFIX}/examples
    )

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()

#    IF(MSVC)
#	ADD_DEFINITIONS(/arch:SSE2)
#	ADD_DEFINITIONS(-D__SSE2__)
#    ENDIF(MSVC)

endmacro(CREATE_EXAMPLE NAME SOURCES LIBRARIES)

#######################################################################
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  "${CMAKE_SOURCE_DIR}/module" 
  )

#######################################################################
if (BUILD_EXAMPLES)
CREATE_EXAMPLE(sample_algebralinear_algebralinear sample_algebralinear_algebralinear "algebralinear")
CREATE_EXAMPLE(sample_numericsystem_numericsystem sample_numericsystem_numericsystem "algebralinear;numericsystem")
CREATE_EXAMPLE(sample_coordinatesystem_coordinatesystem sample_coordinatesystem_coordinatesystem "coordinatesystem")
CREATE_EXAMPLE(sample_statistics_statistics sample_statistics_statistics "algebralinear;statistics")
CREATE_EXAMPLE(sample_geometry_geometry sample_geometry_geometry "geometry")
CREATE_EXAMPLE(sample_geometry_clockwise sample_geometry_clockwise "geometry")
CREATE_EXAMPLE(sample_geometry_contain sample_geometry_contain "geometry")
CREATE_EXAMPLE(sample_trigonometry_trigonometry sample_trigonometry_trigonometry "trigonometry")
CREATE_EXAMPLE(sample_numericanalysis_interpolation sample_numericanalysis_interpolation "numericanalysis")
CREATE_EXAMPLE(sample_numericanalysis_fitting sample_numericanalysis_fitting "numericanalysis")
CREATE_EXAMPLE(sample_numericanalysis_curvefitting sample_numericanalysis_curvefitting "numericanalysis")
CREATE_EXAMPLE(sample_pointcloud_pointcloud sample_pointcloud_pointcloud "pointcloud")
CREATE_EXAMPLE(sample_noise_noise.cpp sample_noise_noise.cpp "noise")
endif(BUILD_EXAMPLES)

#######################################################################
if (USE_STATIC)
  set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
  foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  endforeach()
endif (USE_STATIC)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

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
	target_link_libraries(${NAME} ${LIBRARIES})

	# ------------------------
	# DEFINITIONS
	# ------------------------

	add_definitions(-DUNICODE -D_UNICODE)

   install(TARGETS ${NAME}
      DESTINATION ${CMAKE_INSTALL_PREFIX}/examples
      )

endmacro(CREATE_EXAMPLE NAME SOURCES LIBRARIES)

#######################################################################
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  "${CMAKE_SOURCE_DIR}/module"
  )

#######################################################################
if (BUILD_EXAMPLES)
CREATE_EXAMPLE(sample_system_consoletext sample_system_consoletext "system")
CREATE_EXAMPLE(sample_string_stringconversion sample_string_stringconversion "string")
CREATE_EXAMPLE(sample_string_stringformatconversion sample_string_stringformatconversion "string")
CREATE_EXAMPLE(sample_container_splaytreenaive sample_container_splaytreenaive "container")
CREATE_EXAMPLE(sample_container_splaytreewiki sample_container_splaytreewiki "container")
CREATE_EXAMPLE(sample_control_logreporter sample_control_logreporter "control;system")
CREATE_EXAMPLE(test_filelog test_filelog "control")
CREATE_EXAMPLE(test_memory test_memory "cmnlibcore")
CREATE_EXAMPLE(test_container test_container "container")
CREATE_EXAMPLE(test_reportmessage test_reportmessage "string")
endif(BUILD_EXAMPLES)

#######################################################################
#Use static compiler library or dynamic
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

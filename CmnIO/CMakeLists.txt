######################################################################
# The project name
cmake_minimum_required (VERSION 3.13)

######################################################################
# Import macro
include ("../cmakemacro/cmake_macro_setvariables.txt")

######################################################################
# Read the path configuration file
file(READ "../configure/path_configuration.txt" pt_conf)
string(REPLACE "\n" ";" PATH_FULL_LIST ${pt_conf})
message(STATUS "list = ${PATH_FULL_LIST}")
#Get the first variable
GET_PATH("${PATH_FULL_LIST}" "path_opencv " path_opencv)
message(STATUS "path_opencv = (${path_opencv})")

######################################################################
# The project name
cmake_minimum_required (VERSION 3.13)
SET( MAIN_PROJ_NAME      "CmnIO" )
project (${MAIN_PROJ_NAME})

set(CMNIO_VERSION_MAJOR 0 CACHE STRING "major version of cmnio" FORCE)
set(CMNIO_VERSION_MINOR 5 CACHE STRING "minor version of cmnio" FORCE)
set(CMNIO_VERSION_SUBMINOR 0 CACHE STRING "subminor version of cmnio" FORCE)
set(CMNIO_VERSION_PATCH 1 CACHE STRING "patch version of cmnio" FORCE)
set(CMNIO_VERSION "${CMNIO_VERSION_MAJOR}.${CMNIO_VERSION_MINOR}.${CMNIO_VERSION_SUBMINOR}.${CMNIO_VERSION_PATCH}"
                             CACHE STRING "version of cmnio" FORCE)
set(CMNIO_VERSION_NAME \"CmnIOAlpha\" CACHE STRING "name version of cmnio" FORCE)

# set a debug postfix
set(CMAKE_DEBUG_POSTFIX "-dbg")

# installation destinations
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "Install prefix (e.g. /usr/local/)" FORCE)
endif()
if(UNIX)
    include(GNUInstallDirs)

    set(CMNIO_INC_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/module") 
    set(CMNIO_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}") 
    set(CMNIO_LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNIO_ARCHIVE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNIO_FRAMEWORK_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")

    set(CMNIO_CMAKE_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/cmnio/cmake")
    set(CMNIO_ADDITIONAL_FILES_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/module")

    set(CMNIO_RUNTIME_INSTALL_DIR "bin") # for the nodesize_dbg, just ignore version and the like
    set(CMNIO_INC_INSTALL_DIR "include/cmnio") # header filestree

elseif(WIN32)
    set(CMNIO_INC_INSTALL_DIR "module")
    set(CMNIO_RUNTIME_INSTALL_DIR   "bin") 
    set(CMNIO_LIBRARY_INSTALL_DIR   "bin")
    set(CMNIO_ARCHIVE_INSTALL_DIR   "lib")
    set(CMNIO_FRAMEWORK_INSTALL_DIR "bin")

    set(CMNIO_CMAKE_CONFIG_INSTALL_DIR "cmake")
    set(CMNIO_ADDITIONAL_FILES_INSTALL_DIR "./")
else()
	message(FATAL_ERROR "Could not set install folders for this platform!")
endif()

######################################################################
# Options
option (USE_STATIC "Use static library" OFF)
option (BUILD_EXAMPLES "Build Samples" ON)
option (USE_OPENCV "Compile with OpenCV" ON)
option (USE_CMNLIB "Compile with CMNLIB" ON)

######################################################################
# OpenCV
if (USE_OPENCV)
find_package(OpenCV REQUIRED PATHS ${path_opencv})
endif(USE_OPENCV)

# CmnLib
IF (USE_CMNLIB)
find_package(CmnLib REQUIRED PATHS "../CmnLib/build/install/cmake")
ENDIF (USE_CMNLIB)

# CmnMath
find_package(CmnMath REQUIRED PATHS "../CmnMath/build/install/cmake")

######################################################################
#Add library and link
add_library(${MAIN_PROJ_NAME} "CmnIO/empty_cmake.cpp")
target_link_libraries(${MAIN_PROJ_NAME} cmniocore)
target_link_libraries(${MAIN_PROJ_NAME} cmnioworld)
target_link_libraries(${MAIN_PROJ_NAME} filesio)
target_link_libraries(${MAIN_PROJ_NAME} generator)
target_link_libraries(${MAIN_PROJ_NAME} ${PROJ_LIBRARIES})
#Add include
#Possible error: https://cmake.org/cmake/help/v3.2/manual/cmake-packages.7.html#creating-packages
target_include_directories(${MAIN_PROJ_NAME} INTERFACE
  # Ok, relocatable:
  $<INSTALL_INTERFACE:module> 
)

#Install Library
install(TARGETS ${MAIN_PROJ_NAME} EXPORT ${MAIN_PROJ_NAME}Targets
        RUNTIME       DESTINATION ${CMNIO_RUNTIME_INSTALL_DIR}
        LIBRARY       DESTINATION ${CMNIO_LIBRARY_INSTALL_DIR}
        ARCHIVE       DESTINATION ${CMNIO_ARCHIVE_INSTALL_DIR}
        FRAMEWORK     DESTINATION ${CMNIO_FRAMEWORK_INSTALL_DIR})

######################################################################
# Recurse into the subdirectories. 
add_subdirectory (module)
add_subdirectory (sample)

######################################################################
# install readme and license
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_CURRENT_SOURCE_DIR}/README.md" DESTINATION ${CMNIO_ADDITIONAL_FILES_INSTALL_DIR})
# install headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/module" DESTINATION ${CMNIO_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")
# install main headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/CmnIO" DESTINATION ${CMNIO_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")

set_target_properties(${MAIN_PROJ_NAME} PROPERTIES
                                       OUTPUT_NAME "${MAIN_PROJ_NAME}-${CMNIO_VERSION}")
# Write/install version file
include(CMakePackageConfigHelpers)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/cmake/${MAIN_PROJ_NAME}-version.cmake")
write_basic_package_version_file(${version_file}
                                 VERSION ${CMNIO_VERSION}
                                 COMPATIBILITY AnyNewerVersion)


#add files (if necessary)	
string(TOLOWER ${MAIN_PROJ_NAME} main_proj_name_lowcase)							 
install(EXPORT ${MAIN_PROJ_NAME}Targets DESTINATION ${CMNIO_CMAKE_CONFIG_INSTALL_DIR}
		                               FILE ${main_proj_name_lowcase}-config.cmake
									   NAMESPACE ${MAIN_PROJ_NAME}::)
install(FILES ${version_file} DESTINATION ${CMNIO_CMAKE_CONFIG_INSTALL_DIR})

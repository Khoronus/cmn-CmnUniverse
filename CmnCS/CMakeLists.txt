######################################################################
# The project name
cmake_minimum_required (VERSION 3.13)

######################################################################
# Import macro
include ("../cmakemacro/cmake_macro_setvariables.txt")

######################################################################
# Read the path configuration file (global)
# get the location of the global configuration path
file(READ "../configure/global_path_configuration.txt" pt_global)
string(REPLACE "\n" ";" PATH_GLOBAL_LIST ${pt_global})
GET_PATH("${PATH_GLOBAL_LIST}" "path_global " path_global)
set(PLATFORM_PATH "${path_global}")
message(STATUS "PLATFORM_PATH = (${PLATFORM_PATH})")
# get the location of the global configuration projects path
find_file (pt_location_global NAMES "global_projects_path_configuration.txt" REQUIRED 
  PATHS ${PLATFORM_PATH} 
  DOC "Path to global configuration paths.")
string(REPLACE "\n" ";" PATH_LOCATION_LIST ${pt_location_global})
message(STATUS "list = ${PATH_LOCATION_LIST}")
# read the configuration file global
file(READ "${pt_location_global}" pt_conf_global)
#string(REPLACE "\n" ";" PATH_GLOBAL_FULL_LIST ${pt_conf_global})
#message(STATUS "list = ${PATH_GLOBAL_FULL_LIST}")

######################################################################
# Read the path configuration file (local)
set(path_local_cfg "${CMAKE_SOURCE_DIR}/../configure/path_configuration.txt")
if (EXISTS ${path_local_cfg})
  file(READ ${path_local_cfg} pt_conf)
  message(STATUS "[+] open:${path_local_cfg}")
else()
  message(STATUS "[-] open:${path_local_cfg}")
endif()

######################################################################
# Combine global and local
string(CONCAT MULTI ${pt_conf_global} ${pt_conf})
# remove all the new lines
string(REPLACE "\n" ";" PATH_FULL_LIST ${MULTI})
message(STATUS "list = ${PATH_FULL_LIST}")

######################################################################
# Get the first variable
GET_PATH("${PATH_FULL_LIST}" "path_opencv " path_opencv)
message(STATUS "path_opencv = (${path_opencv})")

######################################################################
# The project name
cmake_minimum_required (VERSION 3.13)
SET( MAIN_PROJ_NAME      "CmnCS" )
project (${MAIN_PROJ_NAME})

set(CMNCS_VERSION_MAJOR 0 CACHE STRING "major version of cmncs" FORCE)
set(CMNCS_VERSION_MINOR 6 CACHE STRING "minor version of cmncs" FORCE)
set(CMNCS_VERSION_SUBMINOR 0 CACHE STRING "subminor version of cmncs" FORCE)
set(CMNCS_VERSION_PATCH 0 CACHE STRING "patch version of cmncs" FORCE)
set(CMNCS_VERSION "${CMNCS_VERSION_MAJOR}.${CMNCS_VERSION_MINOR}.${CMNCS_VERSION_SUBMINOR}.${CMNCS_VERSION_PATCH}"
                             CACHE STRING "version of cmncs" FORCE)
set(CMNCS_VERSION_NAME \"CmnCSAlpha\" CACHE STRING "name version of cmncs" FORCE)

# set a debug postfix
set(CMAKE_DEBUG_POSTFIX "-dbg")

# installation destinations
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "Install prefix (e.g. /usr/local/)" FORCE)
endif()
if(UNIX)
    include(GNUInstallDirs)

    set(CMNCS_INC_INSTALL_DIR "module")  
    set(CMNCS_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}") 
    set(CMNCS_LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNCS_ARCHIVE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNCS_FRAMEWORK_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")

    set(CMNCS_CMAKE_CONFIG_INSTALL_DIR "cmake")
    set(CMNCS_ADDITIONAL_FILES_INSTALL_DIR "./")

    set(CMNCS_RUNTIME_INSTALL_DIR "bin") # for the nodesize_dbg, just ignore version and the like
    set(CMNCS_INC_INSTALL_DIR "module") # header filestree
elseif(WIN32)
    set(CMNCS_INC_INSTALL_DIR "module")
    set(CMNCS_RUNTIME_INSTALL_DIR   "bin") 
    set(CMNCS_LIBRARY_INSTALL_DIR   "bin")
    set(CMNCS_ARCHIVE_INSTALL_DIR   "lib")
    set(CMNCS_FRAMEWORK_INSTALL_DIR "bin")

    set(CMNCS_CMAKE_CONFIG_INSTALL_DIR "cmake")
    set(CMNCS_ADDITIONAL_FILES_INSTALL_DIR "./")
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
add_library(${MAIN_PROJ_NAME} "CmnCS/empty_cmake.cpp")
target_link_libraries(${MAIN_PROJ_NAME} cmncscore)
target_link_libraries(${MAIN_PROJ_NAME} cmncsworld)
target_link_libraries(${MAIN_PROJ_NAME} computationalgeometry)
#target_link_libraries(${MAIN_PROJ_NAME} computationalgeometry2)
#target_link_libraries(${MAIN_PROJ_NAME} graphs)
target_link_libraries(${MAIN_PROJ_NAME} indexing)
target_link_libraries(${MAIN_PROJ_NAME} ${PROJ_LIBRARIES})
#Add include
#Possible error: https://cmake.org/cmake/help/v3.2/manual/cmake-packages.7.html#creating-packages
target_include_directories(${MAIN_PROJ_NAME} INTERFACE
  # Ok, relocatable:
  $<INSTALL_INTERFACE:module> 
)

#Install Library
install(TARGETS ${MAIN_PROJ_NAME} EXPORT ${MAIN_PROJ_NAME}Targets
        RUNTIME       DESTINATION ${CMNCS_RUNTIME_INSTALL_DIR}
        LIBRARY       DESTINATION ${CMNCS_LIBRARY_INSTALL_DIR}
        ARCHIVE       DESTINATION ${CMNCS_ARCHIVE_INSTALL_DIR}
        FRAMEWORK     DESTINATION ${CMNCS_FRAMEWORK_INSTALL_DIR})

######################################################################
# Recurse into the subdirectories. 
add_subdirectory (module)
add_subdirectory (sample)

######################################################################
# install readme and license
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_CURRENT_SOURCE_DIR}/README.md" DESTINATION ${CMNCS_ADDITIONAL_FILES_INSTALL_DIR})
# install headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/module" DESTINATION ${CMNCS_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")
# install main headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/CmnCS" DESTINATION ${CMNCS_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")

set_target_properties(${MAIN_PROJ_NAME} PROPERTIES
                                       OUTPUT_NAME "${MAIN_PROJ_NAME}-${CMNCS_VERSION}")
# Write/install version file
include(CMakePackageConfigHelpers)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/cmake/${MAIN_PROJ_NAME}-version.cmake")
write_basic_package_version_file(${version_file}
                                 VERSION ${CMNCS_VERSION}
                                 COMPATIBILITY AnyNewerVersion)


#add files (if necessary)
string(TOLOWER ${MAIN_PROJ_NAME} main_proj_name_lowcase)								 
install(EXPORT ${MAIN_PROJ_NAME}Targets DESTINATION ${CMNCS_CMAKE_CONFIG_INSTALL_DIR}
		                               FILE ${main_proj_name_lowcase}-config.cmake
									   NAMESPACE ${MAIN_PROJ_NAME}::)
install(FILES ${version_file} DESTINATION ${CMNCS_CMAKE_CONFIG_INSTALL_DIR})

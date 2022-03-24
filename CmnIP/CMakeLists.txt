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
set(path_local_cfg "../configure/path_configuration.txt")
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
SET( MAIN_PROJ_NAME      "CmnIP" )
project (${MAIN_PROJ_NAME})

set(CMNIP_VERSION_MAJOR 0 CACHE STRING "major version of cmnip" FORCE)
set(CMNIP_VERSION_MINOR 5 CACHE STRING "minor version of cmnip" FORCE)
set(CMNIP_VERSION_SUBMINOR 0 CACHE STRING "subminor version of cmnip" FORCE)
set(CMNIP_VERSION_PATCH 3 CACHE STRING "patch version of cmnip" FORCE)
set(CMNIP_VERSION "${CMNIP_VERSION_MAJOR}.${CMNIP_VERSION_MINOR}.${CMNIP_VERSION_SUBMINOR}.${CMNIP_VERSION_PATCH}"
                             CACHE STRING "version of cmnip" FORCE)
set(CMNIP_VERSION_NAME \"CmnIPAlpha\" CACHE STRING "name version of cmnip" FORCE)

# set a debug postfix
set(CMAKE_DEBUG_POSTFIX "-dbg")

# installation destinations
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "Install prefix (e.g. /usr/local/)" FORCE)
endif()
if(UNIX)
    include(GNUInstallDirs)

    set(CMNIP_INC_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/module") 
    set(CMNIP_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}") 
    set(CMNIP_LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNIP_ARCHIVE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNIP_FRAMEWORK_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")

    set(CMNIP_CMAKE_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/cmnip/cmake")
    set(CMNIP_ADDITIONAL_FILES_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/module")

    set(CMNIP_RUNTIME_INSTALL_DIR "bin") # for the nodesize_dbg, just ignore version and the like
    set(CMNIP_INC_INSTALL_DIR "include/cmnip") # header filestree

elseif(WIN32)
    set(CMNIP_INC_INSTALL_DIR "module")
    set(CMNIP_RUNTIME_INSTALL_DIR   "bin") 
    set(CMNIP_LIBRARY_INSTALL_DIR   "bin")
    set(CMNIP_ARCHIVE_INSTALL_DIR   "lib")
    set(CMNIP_FRAMEWORK_INSTALL_DIR "bin")

    set(CMNIP_CMAKE_CONFIG_INSTALL_DIR "cmake")
    set(CMNIP_ADDITIONAL_FILES_INSTALL_DIR "./")
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
add_library(${MAIN_PROJ_NAME} "CmnIP/empty_cmake.cpp")
target_link_libraries(${MAIN_PROJ_NAME} cmnipcore)
target_link_libraries(${MAIN_PROJ_NAME} cmnipworld)
target_link_libraries(${MAIN_PROJ_NAME} ${PROJ_LIBRARIES})
#Add include
#Possible error: https://cmake.org/cmake/help/v3.2/manual/cmake-packages.7.html#creating-packages
target_include_directories(${MAIN_PROJ_NAME} INTERFACE
  # Ok, relocatable:
  $<INSTALL_INTERFACE:module> 
)

#Install Library
install(TARGETS ${MAIN_PROJ_NAME} EXPORT ${MAIN_PROJ_NAME}Targets
        RUNTIME       DESTINATION ${CMNIP_RUNTIME_INSTALL_DIR}
        LIBRARY       DESTINATION ${CMNIP_LIBRARY_INSTALL_DIR}
        ARCHIVE       DESTINATION ${CMNIP_ARCHIVE_INSTALL_DIR}
        FRAMEWORK     DESTINATION ${CMNIP_FRAMEWORK_INSTALL_DIR})

######################################################################
# Recurse into the subdirectories. 
add_subdirectory (module)
add_subdirectory (sample)

######################################################################
# install readme and license
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_CURRENT_SOURCE_DIR}/README.md" DESTINATION ${CMNIP_ADDITIONAL_FILES_INSTALL_DIR})
# install headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/module" DESTINATION ${CMNIP_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")
# install main headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/CmnIP" DESTINATION ${CMNIP_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")

set_target_properties(${MAIN_PROJ_NAME} PROPERTIES
                                       OUTPUT_NAME "${MAIN_PROJ_NAME}-${CMNIP_VERSION}")
# Write/install version file
include(CMakePackageConfigHelpers)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/cmake/${MAIN_PROJ_NAME}-version.cmake")
write_basic_package_version_file(${version_file}
                                 VERSION ${CMNIP_VERSION}
                                 COMPATIBILITY AnyNewerVersion)


#add files (if necessary)		
string(TOLOWER ${MAIN_PROJ_NAME} main_proj_name_lowcase)						 
install(EXPORT ${MAIN_PROJ_NAME}Targets DESTINATION ${CMNIP_CMAKE_CONFIG_INSTALL_DIR}
		                               FILE ${main_proj_name_lowcase}-config.cmake
									   NAMESPACE ${MAIN_PROJ_NAME}::)
install(FILES ${version_file} DESTINATION ${CMNIP_CMAKE_CONFIG_INSTALL_DIR})

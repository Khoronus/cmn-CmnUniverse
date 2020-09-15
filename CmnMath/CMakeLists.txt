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
SET( MAIN_PROJ_NAME      "CmnMath" )
project (${MAIN_PROJ_NAME})

set(CMNMATH_VERSION_MAJOR 0 CACHE STRING "major version of cmnmath" FORCE)
set(CMNMATH_VERSION_MINOR 7 CACHE STRING "minor version of cmnmath" FORCE)
set(CMNMATH_VERSION_SUBMINOR 1 CACHE STRING "subminor version of cmnmath" FORCE)
set(CMNMATH_VERSION_PATCH 0 CACHE STRING "patch version of cmnmath" FORCE)
set(CMNMATH_VERSION "${CMNMATH_VERSION_MAJOR}.${CMNMATH_VERSION_MINOR}.${CMNMATH_VERSION_SUBMINOR}.${CMNMATH_VERSION_PATCH}"
                             CACHE STRING "version of cmnmath" FORCE)
set(CMNMATH_VERSION_NAME \"CmnMathAlpha\" CACHE STRING "name version of cmnmath" FORCE)

# set a debug postfix
set(CMAKE_DEBUG_POSTFIX "-dbg")

# installation destinations
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "Install prefix (e.g. /usr/local/)" FORCE)
endif()
if(UNIX)
    include(GNUInstallDirs)

    set(CMNMATH_INC_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/module") 
    set(CMNMATH_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}") 
    set(CMNMATH_LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNMATH_ARCHIVE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNMATH_FRAMEWORK_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")

    set(CMNMATH_CMAKE_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/cmnmath/cmake")
    set(CMNMATH_ADDITIONAL_FILES_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/module")

    set(CMNMATH_RUNTIME_INSTALL_DIR "bin") # for the nodesize_dbg, just ignore version and the like
    set(CMNMATH_INC_INSTALL_DIR "include/cmnmath") # header filestree

elseif(WIN32)
    set(CMNMATH_INC_INSTALL_DIR "module")
    set(CMNMATH_RUNTIME_INSTALL_DIR   "bin") 
    set(CMNMATH_LIBRARY_INSTALL_DIR   "bin")
    set(CMNMATH_ARCHIVE_INSTALL_DIR   "lib")
    set(CMNMATH_FRAMEWORK_INSTALL_DIR "bin")

    set(CMNMATH_CMAKE_CONFIG_INSTALL_DIR "cmake")
    set(CMNMATH_ADDITIONAL_FILES_INSTALL_DIR "./")
else()
	message(FATAL_ERROR "Could not set install folders for this platform!")
endif()

# The version number
set (VERSION_MAJOR 0)
set (VERSION_MINOR 5)
set (VERSION_SUBMINOR 0)
set (VERSION_PATCH 0)
set (VERSION_NAME \"CmnMathAlpha\")

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

######################################################################
# CmnLib
find_package(CmnLib REQUIRED PATHS "../CmnLib/build/install/cmake")

######################################################################
#Add library and link
add_library(${MAIN_PROJ_NAME} "CmnMath/empty_cmake.cpp")
target_link_libraries(${MAIN_PROJ_NAME} algebralinear)
target_link_libraries(${MAIN_PROJ_NAME} cmnmathcore)
target_link_libraries(${MAIN_PROJ_NAME} cmnmathworld)
target_link_libraries(${MAIN_PROJ_NAME} coordinatesystem)
target_link_libraries(${MAIN_PROJ_NAME} geometricprimitive)
target_link_libraries(${MAIN_PROJ_NAME} memory)
target_link_libraries(${MAIN_PROJ_NAME} noise)
target_link_libraries(${MAIN_PROJ_NAME} numericanalysis)
target_link_libraries(${MAIN_PROJ_NAME} numericsystem)
target_link_libraries(${MAIN_PROJ_NAME} pointcloud)
target_link_libraries(${MAIN_PROJ_NAME} projection)
target_link_libraries(${MAIN_PROJ_NAME} statistics)
target_link_libraries(${MAIN_PROJ_NAME} trigonometry)
target_link_libraries(${MAIN_PROJ_NAME} ${PROJ_LIBRARIES})
#Add include
#Possible error: https://cmake.org/cmake/help/v3.2/manual/cmake-packages.7.html#creating-packages
target_include_directories(${MAIN_PROJ_NAME} INTERFACE
  # Ok, relocatable:
  $<INSTALL_INTERFACE:module> 
)

#Install Library
install(TARGETS ${MAIN_PROJ_NAME} EXPORT ${MAIN_PROJ_NAME}Targets
        RUNTIME       DESTINATION ${CMNMATH_RUNTIME_INSTALL_DIR}
        LIBRARY       DESTINATION ${CMNMATH_LIBRARY_INSTALL_DIR}
        ARCHIVE       DESTINATION ${CMNMATH_ARCHIVE_INSTALL_DIR}
        FRAMEWORK     DESTINATION ${CMNMATH_FRAMEWORK_INSTALL_DIR})

######################################################################
# Recurse into the subdirectories. 
add_subdirectory (module)
add_subdirectory (sample)

######################################################################
# install readme and license
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_CURRENT_SOURCE_DIR}/README.md" DESTINATION ${CMNMATH_ADDITIONAL_FILES_INSTALL_DIR})
# install headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/module" DESTINATION ${CMNMATH_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")
# install main headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/CmnMath" DESTINATION ${CMNMATH_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")

set_target_properties(${MAIN_PROJ_NAME} PROPERTIES
                                       OUTPUT_NAME "${MAIN_PROJ_NAME}-${CMNMATH_VERSION}")
# Write/install version file
include(CMakePackageConfigHelpers)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/cmake/${MAIN_PROJ_NAME}-version.cmake")
write_basic_package_version_file(${version_file}
                                 VERSION ${CMNMATH_VERSION}
                                 COMPATIBILITY AnyNewerVersion)


#add files (if necessary)								 
install(EXPORT ${MAIN_PROJ_NAME}Targets DESTINATION ${CMNMATH_CMAKE_CONFIG_INSTALL_DIR}
		                               FILE ${MAIN_PROJ_NAME}-config.cmake
									   NAMESPACE ${MAIN_PROJ_NAME}::)
install(FILES ${version_file} DESTINATION ${CMNMATH_CMAKE_CONFIG_INSTALL_DIR})
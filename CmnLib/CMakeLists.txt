######################################################################
# The project name
cmake_minimum_required (VERSION 3.13)

######################################################################
# Import macro
include ("../cmakemacro/cmake_macro_setvariables.txt")

######################################################################
# The project name
SET( MAIN_PROJ_NAME      "CmnLib" )
project (${MAIN_PROJ_NAME})

set(CMNLIB_VERSION_MAJOR 0 CACHE STRING "major version of cmnlib" FORCE)
set(CMNLIB_VERSION_MINOR 8 CACHE STRING "minor version of cmnlib" FORCE)
set(CMNLIB_VERSION_SUBMINOR 0 CACHE STRING "subminor version of cmnlib" FORCE)
set(CMNLIB_VERSION_PATCH 0 CACHE STRING "patch version of cmnlib" FORCE)
set(CMNLIB_VERSION "${CMNLIB_VERSION_MAJOR}.${CMNLIB_VERSION_MINOR}.${CMNLIB_VERSION_SUBMINOR}.${CMNLIB_VERSION_PATCH}"
                             CACHE STRING "version of cmnlib" FORCE)
set(CMNLIB_VERSION_NAME \"CmnLibAlpha\" CACHE STRING "name version of cmnlib" FORCE)

# set a debug postfix
set(CMAKE_DEBUG_POSTFIX "-dbg")

# installation destinations
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING "Install prefix (e.g. /usr/local/)" FORCE)
endif()
if(UNIX)
    include(GNUInstallDirs)

    #set(CMNLIB_INC_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/module")
    set(CMNLIB_INC_INSTALL_DIR "module")  
    set(CMNLIB_RUNTIME_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}") 
    set(CMNLIB_LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNLIB_ARCHIVE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
    set(CMNLIB_FRAMEWORK_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")

    set(CMNLIB_CMAKE_CONFIG_INSTALL_DIR "cmake")
    set(CMNLIB_ADDITIONAL_FILES_INSTALL_DIR "./")

    set(CMNLIB_RUNTIME_INSTALL_DIR "bin") # for the nodesize_dbg, just ignore version and the like
    set(CMNLIB_INC_INSTALL_DIR "module") # header filestree

elseif(WIN32)
    set(CMNLIB_INC_INSTALL_DIR "module")
    set(CMNLIB_RUNTIME_INSTALL_DIR   "bin") 
    set(CMNLIB_LIBRARY_INSTALL_DIR   "bin")
    set(CMNLIB_ARCHIVE_INSTALL_DIR   "lib")
    set(CMNLIB_FRAMEWORK_INSTALL_DIR "bin")

    set(CMNLIB_CMAKE_CONFIG_INSTALL_DIR "cmake")
    set(CMNLIB_ADDITIONAL_FILES_INSTALL_DIR "./")
else()
	message(FATAL_ERROR "Could not set install folders for this platform!")
endif()


######################################################################
# Definitions

# Windows' math include does not define constants by default.
# Set this definition so it does.
# Also set NOMINMAX so the min and max functions are not overwritten with macros.
IF(MSVC)
    add_definitions(-D_USE_MATH_DEFINES)
    add_definitions(-DNOMINMAX)
    add_definitions(-DUNICODE -D_UNICODE)
ENDIF()

######################################################################
# Options
option (USE_WIN32 "Compile with Win32" ON)

#Add library and link
add_library(${MAIN_PROJ_NAME} "CmnLib/empty_cmake.cpp")
target_link_libraries(${MAIN_PROJ_NAME} cmnlibcore)
target_link_libraries(${MAIN_PROJ_NAME} cmnlibworld)
target_link_libraries(${MAIN_PROJ_NAME} container)
target_link_libraries(${MAIN_PROJ_NAME} control)
target_link_libraries(${MAIN_PROJ_NAME} string)
target_link_libraries(${MAIN_PROJ_NAME} system)
target_link_libraries(${MAIN_PROJ_NAME} ts)
target_link_libraries(${MAIN_PROJ_NAME} ${PROJ_LIBRARIES})
#Add include
#Possible error: https://cmake.org/cmake/help/v3.2/manual/cmake-packages.7.html#creating-packages
target_include_directories(${MAIN_PROJ_NAME} INTERFACE
  # Ok, relocatable:
  $<INSTALL_INTERFACE:module> 
)

#Install Library
install(TARGETS ${MAIN_PROJ_NAME} EXPORT ${MAIN_PROJ_NAME}Targets
        RUNTIME       DESTINATION ${CMNLIB_RUNTIME_INSTALL_DIR}
        LIBRARY       DESTINATION ${CMNLIB_LIBRARY_INSTALL_DIR}
        ARCHIVE       DESTINATION ${CMNLIB_ARCHIVE_INSTALL_DIR}
        FRAMEWORK     DESTINATION ${CMNLIB_FRAMEWORK_INSTALL_DIR})

######################################################################
# Options
#option (USE_STATIC "Use static library" OFF)
option (BUILD_EXAMPLES "Build Samples" ON)
#option (USE_WIN32 "Compile with Win32" ON)

######################################################################
# Recurse into the subdirectories. 
add_subdirectory (module)
add_subdirectory (sample)

######################################################################
# install readme and license
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_CURRENT_SOURCE_DIR}/README.md" DESTINATION ${CMNLIB_ADDITIONAL_FILES_INSTALL_DIR})
# install headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/module" DESTINATION ${CMNLIB_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")
# install main headers
install(DIRECTORY "${CMAKE_SOURCE_DIR}/CmnLib" DESTINATION ${CMNLIB_ADDITIONAL_FILES_INSTALL_DIR}
          FILES_MATCHING PATTERN "*.hpp")

set_target_properties(${MAIN_PROJ_NAME} PROPERTIES
                                       OUTPUT_NAME "${MAIN_PROJ_NAME}-${CMNLIB_VERSION}")
# Write/install version file
include(CMakePackageConfigHelpers)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/cmake/${MAIN_PROJ_NAME}-version.cmake")
write_basic_package_version_file(${version_file}
                                 VERSION ${CMNLIB_VERSION}
                                 COMPATIBILITY AnyNewerVersion)


#add files (if necessary)	
string(TOLOWER ${MAIN_PROJ_NAME} main_proj_name_lowcase)
install(EXPORT ${MAIN_PROJ_NAME}Targets DESTINATION ${CMNLIB_CMAKE_CONFIG_INSTALL_DIR}
		                               FILE ${main_proj_name_lowcase}-config.cmake
									   NAMESPACE ${MAIN_PROJ_NAME}::)
install(FILES ${version_file} DESTINATION ${CMNLIB_CMAKE_CONFIG_INSTALL_DIR})


# Print all the variables
print_all_variables()

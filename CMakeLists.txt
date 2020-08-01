# --------------------------------------------------
#   Copyright (C): OpenGATE Collaboration
#   This software is distributed under the terms
#   of the GNU Lesser General  Public Licence (LGPL)
#   See LICENSE.md for further details
# --------------------------------------------------

cmake_minimum_required(VERSION 2.8.12)
project(gam_g4)

set(CMAKE_CXX_STANDARD 14)

# Need python 
find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
message(STATUS "GAM - PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
message(STATUS "GAM - PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
message(STATUS "GAM - PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")

# Need Geant4
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})
message(STATUS "GAM - Geant4 version = ${Geant4_VERSION}")

# Need pybind11
find_package(pybind11 REQUIRED)
message(STATUS "GAM - pybind11 version = ${pybind11_VERSION}")
message(STATUS "GAM - pybind11 = ${pybind11_INCLUDE_DIRS}")

# itk
find_package(ITK 5.0 REQUIRED)
if (ITK_FOUND)
    include("${ITK_USE_FILE}")
    message(STATUS "GAM - ITK version = ${ITK_VERSION}")
else (ITK_FOUND)
    message(FATAL_ERROR "Cannot build without ITK.  Please set ITK_DIR.")
endif (ITK_FOUND)

# -DCMAKE_CXX_FLAGS="-Wno-self-assign"


# Create the geant4 python module
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/g4_bindings/*.cpp"
        "${PROJECT_SOURCE_DIR}/gam_lib/*.cpp"
        )
pybind11_add_module(gam_g4
        #NO_EXTRAS
        #THIN_LTO
        gam_g4.cpp
        ${all_SRCS}
        )

if (WIN32)
    if (MSVC)
        #message("I am MSCV")
        set_target_properties(gam_g4 PROPERTIES COMPILE_FLAGS "/MP /bigobj ")
        # set_target_properties(geant4 PROPERTIES LINK_FLAGS "/LTCG ")
        #        if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
        #            message("I am HERE")
        #            # Enforce size-based optimization and link time code generation on MSVC
        #            # (~30% smaller binaries in experiments).
        #            set_target_properties(geant4 APPEND_STRING PROPERTY COMPILE_FLAGS "/Os /GL ")
        #            set_target_properties(geant4 APPEND_STRING PROPERTY LINK_FLAGS "/LTCG ")
        #        endif()
    endif ()
endif ()

target_link_libraries(gam_g4 PRIVATE pybind11::module ${Geant4_LIBRARIES} ${ITK_LIBRARIES})
# Do not not add ${PYTHON_LIBRARIES}) here (seg fault)

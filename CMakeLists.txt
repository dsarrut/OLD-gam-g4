# --------------------------------------------------
#   Copyright (C): OpenGATE Collaboration
#   This software is distributed under the terms
#   of the GNU Lesser General  Public Licence (LGPL)
#   See LICENSE.md for further details
# --------------------------------------------------

cmake_minimum_required(VERSION 2.8.12)
project(geant4)

set(CMAKE_CXX_STANDARD 14)

# Need python 
find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")

# Need Geant4
find_package(Geant4 REQUIRED)
INCLUDE(${Geant4_USE_FILE})

# Need pybind11
find_package(pybind11 REQUIRED)

# itk
find_package(ITK)
if(ITK_FOUND)
    include("${ITK_USE_FILE}")
else(ITK_FOUND)
    message(FATAL_ERROR "Cannot build without ITK.  Please set ITK_DIR.")
endif(ITK_FOUND)

# a simple G4 test
#ADD_EXECUTABLE(g4_test1 g4_test1.cpp)
#target_link_libraries(g4_test1 ${Geant4_LIBRARIES})

# Create the geant4 python module
pybind11_add_module(geant4

        #NO_EXTRAS
        #THIN_LTO

        geant4.cpp

        pyG4ThreeVector.cpp
        pyG4String.cpp
        pyG4RotationMatrix.cpp
        pyG4UnitsTable.cpp

        pyG4Material.cpp
        pyG4NistManager.cpp

        pyG4VSolid.cpp
        pyG4Box.cpp
        pyG4VPhysicalVolume.cpp
        pyG4PVPlacement.cpp
        pyG4LogicalVolume.cpp
        pyG4VUserDetectorConstruction.cpp
        pyG4GeometryManager.cpp

        pyPhysicsLists.cpp
        pyG4VUserPhysicsList.cpp
        pyG4VModularPhysicsList.cpp
        pyG4VUserPrimaryGeneratorAction.cpp
        pyG4PhysListFactory.cpp
        pyG4VUserActionInitialization.cpp
        pyG4ProductionCutsTable.cpp
        pyG4Run.cpp
        pyG4Event.cpp
        pyG4Track.cpp
        pyG4Step.cpp
        pyG4StepPoint.cpp
        pyG4UserRunAction.cpp
        pyG4UserEventAction.cpp
        pyG4UserTrackingAction.cpp
        pyG4UserSteppingAction.cpp
        pyG4ParticleGun.cpp
        pyG4VPrimaryGenerator.cpp
        pyG4ParticleTable.cpp
        pyG4ParticleDefinition.cpp

        G4UserSteppingBatchAction.h
        pyG4UserSteppingBatchAction.cpp

        pyG4VSteppingVerbose.cpp
        pyG4RunManager.cpp
        pyG4UImanager.cpp
        pyG4UIsession.cpp
        pyRandomize.cpp

        pyG4VPrimitiveScorer.cpp

        GateUserSteppingAction.cpp
        pyGateUserSteppingAction.cpp
        GateTestActor.cpp
        pyGateTestActor.cpp

        #GateEventAction.h
        #GateAction.cpp
        GateVActor.cpp
        GateAActor.cpp
        GateDoseActor.cpp
        GateSimulationStatisticsActor.cpp

        pyGateVActor.cpp
        pyGateAActor.cpp
        pyGateDoseActor.cpp
        pyGateSimulationStatisticsActor.cpp

        )

if (WIN32)
    if (MSVC)
        #message("I am MSCV")
        set_target_properties(geant4 PROPERTIES COMPILE_FLAGS "/MP /bigobj ")

        # set_target_properties(geant4 PROPERTIES LINK_FLAGS "/LTCG ")

#        if (NOT ${U_CMAKE_BUILD_TYPE} MATCHES DEBUG)
#            message("I am HERE")
#            # Enforce size-based optimization and link time code generation on MSVC
#            # (~30% smaller binaries in experiments).
#            set_target_properties(geant4 APPEND_STRING PROPERTY COMPILE_FLAGS "/Os /GL ")
#            set_target_properties(geant4 APPEND_STRING PROPERTY LINK_FLAGS "/LTCG ")
#        endif()
    endif()
endif()

target_link_libraries(geant4 PRIVATE pybind11::module ${Geant4_LIBRARIES})
# NO ${PYTHON_LIBRARIES}) here (seg fault)

# test proton in waterbox_log
#set(CMAKE_CXX_FLAGS "-O2")
ADD_EXECUTABLE(g4_test5 g4_test5.cpp)
#set_target_properties(g4_test5 PROPERTIES COMPILE_FLAGS "/MP /bigobj ")
target_link_libraries(g4_test5 ${Geant4_LIBRARIES})

# test simple G4
ADD_EXECUTABLE(g4_test6 g4_test6.cpp)
target_link_libraries(g4_test6 ${Geant4_LIBRARIES})

# test simple G4
ADD_EXECUTABLE(g4_test7 g4_test7.cpp GateTestActor.cpp)
target_link_libraries(g4_test7 ${Geant4_LIBRARIES})

# test simple G4
ADD_EXECUTABLE(g4_test8 g4_test8.cpp GateTestActor.cpp)
target_link_libraries(g4_test8 ${Geant4_LIBRARIES})

# test simple G4 : batch
ADD_EXECUTABLE(g4_test9 g4_test9.cpp GateVActor.cpp GateDoseActor.cpp)
target_link_libraries(g4_test9 ${Geant4_LIBRARIES})

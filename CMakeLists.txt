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
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
# message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
# message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
# message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")

# Need Geant4
find_package(Geant4 REQUIRED)
INCLUDE(${Geant4_USE_FILE})

# Need pybind11
find_package(pybind11 REQUIRED)

# a simple G4 test
#ADD_EXECUTABLE(g4_test1 g4_test1.cpp)
#target_link_libraries(g4_test1 ${Geant4_LIBRARIES})

# test proton in waterbox
ADD_EXECUTABLE(g4_test5 g4_test5.cpp)
target_link_libraries(g4_test5 ${Geant4_LIBRARIES})

# Create the geant4 python module
pybind11_add_module(geant4
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
        pyG4VUserActionInitialization.cpp
        pyG4Run.cpp
        pyG4Event.cpp
        pyG4Step.cpp
        pyG4UserRunAction.cpp
        pyG4UserEventAction.cpp
        pyG4UserSteppingAction.cpp
        pyG4ParticleGun.cpp
        pyG4VPrimaryGenerator.cpp
        pyG4ParticleTable.cpp
        pyG4ParticleDefinition.cpp

        pyG4VSteppingVerbose.cpp
        pyG4RunManager.cpp
        pyG4UImanager.cpp
        pyRandomize.cpp
        )

target_link_libraries(geant4 PRIVATE pybind11::module ${Geant4_LIBRARIES})
# NO ${PYTHON_LIBRARIES}) here (seg fault)




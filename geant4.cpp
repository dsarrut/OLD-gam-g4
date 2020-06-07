// --------------------------------------------------
//   Copyright (C): OpenGATE Collaboration
//   This software is distributed under the terms
//   of the GNU Lesser General  Public Licence (LGPL)
//   See LICENSE.md for further details
// --------------------------------------------------

#include <pybind11/pybind11.h>

namespace py = pybind11;

// management
void init_G4ThreeVector(py::module &);

void init_G4String(py::module &);

void init_G4RotationMatrix(py::module &);

// CLHEP
void init_Randomize(py::module &);

// materials
void init_G4NistManager(py::module &);

void init_G4Material(py::module &);

// run
void init_G4RunManager(py::module &);

void init_G4VUserDetectorConstruction(py::module &);

void init_G4VUserPhysicsList(py::module &);

void init_G4VModularPhysicsList(py::module &);

void init_G4VUserPrimaryGeneratorAction(py::module &);

void init_G4VUserActionInitialization(py::module &);

// geometry/management
void init_G4VSolid(py::module &);

void init_G4VPhysicalVolume(py::module &);

void init_G4LogicalVolume(py::module &);

void init_G4GeometryManager(py::module &);

// geometry/solids
void init_G4Box(py::module &);

// geometry/volume
void init_G4PVPlacement(py::module &);

// specific to python 
void init_G4PhysicsLists(py::module &);

// event
void init_G4ParticleGun(py::module &);

void init_G4VPrimaryGenerator(py::module &);

void init_G4Event(py::module &);

// particles/management
void init_G4ParticleTable(py::module &);

void init_G4ParticleDefinition(py::module &);

// tracking
void init_G4VSteppingVerbose(py::module &);

// intercoms
void init_G4UImanager(py::module &);

PYBIND11_MODULE(geant4, m) {

    init_G4ThreeVector(m);
    init_G4String(m);
    init_G4RotationMatrix(m);

    init_Randomize(m);

    init_G4NistManager(m);
    init_G4Material(m);

    init_G4VSteppingVerbose(m);

    init_G4RunManager(m);
    init_G4VUserDetectorConstruction(m);
    init_G4VUserPhysicsList(m);
    init_G4VModularPhysicsList(m);
    init_G4VUserPrimaryGeneratorAction(m);
    init_G4VUserActionInitialization(m);

    init_G4VSolid(m);
    init_G4VPhysicalVolume(m);
    init_G4LogicalVolume(m);
    init_G4GeometryManager(m);

    init_G4Box(m);

    init_G4PVPlacement(m);

    init_G4PhysicsLists(m);

    init_G4VPrimaryGenerator(m);
    init_G4ParticleGun(m);
    init_G4Event(m);

    init_G4ParticleTable(m);
    init_G4ParticleDefinition(m);

    init_G4UImanager(m);
}

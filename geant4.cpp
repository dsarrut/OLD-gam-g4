#include <pybind11/pybind11.h>

namespace py = pybind11;

// General
void init_G4ThreeVector(py::module &);
void init_G4String(py::module &);
void init_G4RotationMatrix(py::module &);

// Materials
void init_G4NistManager(py::module &);
void init_G4Material(py::module &);

// Solids and volumes
void init_G4VSolid(py::module &);
void init_G4Box(py::module &);

void init_G4VPhysicalVolume(py::module &);
void init_G4PVPlacement(py::module &);

void init_G4LogicalVolume(py::module &);
void init_G4VUserDetectorConstruction(py::module &);
//void init_G4RunManager(py::module &);

// Physict lists
void init_G4VUserPhysicsList(py::module &);
void init_G4PhysicsLists(py::module &);

PYBIND11_MODULE(geant4, m) {

  init_G4String(m);
  init_G4ThreeVector(m);
  init_G4RotationMatrix(m);  

  init_G4NistManager(m);
  init_G4Material(m);
  init_G4VSolid(m);
  init_G4Box(m);

  init_G4VPhysicalVolume(m);
  init_G4PVPlacement(m);
  
  init_G4LogicalVolume(m);
  init_G4VUserDetectorConstruction(m);
  //  init_G4RunManager(m);

  init_G4VUserPhysicsList(m);
  init_G4PhysicsLists(m);
}

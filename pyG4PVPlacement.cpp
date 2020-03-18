
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4Version.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"

// https://pybind11.readthedocs.io/en/stable/advanced/classes.html#virtual-and-inheritance
// Needed helper class because of the pure virtual method
class PyG4PVPlacement : public G4PVPlacement {
public:
  /* Inherit the constructors */
  using G4PVPlacement::G4PVPlacement;

  /* Trampoline (need one for each virtual function) */
  G4int GetCopyNo() const override {
    PYBIND11_OVERLOAD(G4int, // Return type 
                      G4PVPlacement, // Parent class 
                      GetCopyNo, // Name of function in C++ (must match Python name) 
                      // No argument here  
                      );
  }
};




void init_G4PVPlacement(py::module & m) {
  py::class_<G4PVPlacement, PyG4PVPlacement, G4VPhysicalVolume>(m, "G4PVPlacement")

    .def(py::init<G4RotationMatrix*, const G4ThreeVector&,
	 G4LogicalVolume*, const G4String&,
	 G4LogicalVolume*, G4bool, G4int>())
    
    .def(py::init<const G4Transform3D&, G4LogicalVolume*,
	 const G4String&, G4LogicalVolume*, G4bool, G4int>())
    
    .def(py::init<G4RotationMatrix*, const G4ThreeVector&,
	 const G4String, G4LogicalVolume*,
	 G4VPhysicalVolume*, G4bool, G4int>())
    
    .def(py::init<const G4Transform3D&, const G4String&,
	 G4LogicalVolume*, G4VPhysicalVolume*, G4bool, G4int>())

    .def(py::init<G4RotationMatrix*, const G4ThreeVector&,
	 G4LogicalVolume*, const G4String&,
	 G4LogicalVolume*, G4bool, G4int, G4bool>())

    .def(py::init<const G4Transform3D&, G4LogicalVolume*,
	 const G4String&, G4LogicalVolume*, G4bool, G4int, G4bool>())

    .def(py::init<G4RotationMatrix*, const G4ThreeVector&,
	 const G4String, G4LogicalVolume*,
	 G4VPhysicalVolume*, G4bool, G4int, G4bool>())

    .def(py::init<const G4Transform3D&, const G4String&,
	 G4LogicalVolume*, G4VPhysicalVolume*, G4bool, G4int, G4bool>())

    // FIXME 
    .def("CheckOverlaps", &G4PVPlacement::CheckOverlaps) //, f_CheckOverlaps())


    .def("GetCopyNo", &G4PVPlacement::GetCopyNo)
    

    
    // debug destructor
    .def("__del__",
         [](const G4PVPlacement&) -> void { 
           std::cerr << "deleting G4PVPlacement" << std::endl;
         })
    ;
}


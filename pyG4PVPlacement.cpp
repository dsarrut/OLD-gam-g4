
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4Version.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"

// ?????????
//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(f_CheckOverlaps,
//                                       CheckOverlaps, 0, 3)


void init_G4PVPlacement(py::module & m) {
  py::class_<G4PVPlacement, G4VPhysicalVolume>(m, "G4PVPlacement")

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

    .def("CheckOverlaps", &G4PVPlacement::CheckOverlaps) //, f_CheckOverlaps())


    // debug destructor
    .def("__del__",
         [](const G4PVPlacement&) -> void { 
           std::cerr << "deleting G4PVPlacement" << std::endl;
         })
    ;
}


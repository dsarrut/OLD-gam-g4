
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4Version.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"

// https://pybind11.readthedocs.io/en/stable/advanced/classes.html#virtual-and-inheritance
// Needed helper class because of the pure virtual method
class PyG4PVPlacement : public G4PVPlacement {
public:
  /* Inherit the constructors */
  using G4PVPlacement::G4PVPlacement;

  /* Trampoline (need one for each virtual function) */
  // Here only when py::init_alias is used instead of py::init
  G4int GetCopyNo() const override {
    std::cout << "I am in PyG4PVPlacement::GetCopyNo" << std::endl;
    PYBIND11_OVERLOAD(G4int, // Return type 
                      G4PVPlacement, // Parent class 
                      GetCopyNo, // Name of function in C++ (must match Python name) 
                      // No argument here  
                      );
  }
};


// G4int call_GetCopyNo(const G4VPhysicalVolume * base) {
//   std::cout << "I am in call_GetCopyNo " << std::endl;
//   return base->GetCopyNo();
// }

void init_G4PVPlacement(py::module & m) {
  py::class_<G4PVPlacement, PyG4PVPlacement, G4VPhysicalVolume>(m, "G4PVPlacement")

    
    .def(py::init_alias<G4RotationMatrix*, const G4ThreeVector&,
         G4LogicalVolume*, const G4String&,
         G4LogicalVolume*, G4bool, G4int, G4bool>())
    
    /*
      .def(py::init<>([](G4RotationMatrix * r,
      const G4ThreeVector & t,
      G4LogicalVolume * l,
      const G4String & s,
      G4LogicalVolume * l2,
      G4bool b,
      G4int i,
      G4bool b2) {
      std::cout << "================= Constructor G4PVPlacement" << std::endl;
      //return std::unique_ptr<G4PVPlacement>(new G4PVPlacement(r,t,l,s,l2,b,i,b2));
      return new G4PVPlacement(r,t,l,s,l2,b,i,b2);
      }))
    */
    /*
    
      .def(py::init_alias<const G4Transform3D&, G4LogicalVolume*,
      const G4String&, G4LogicalVolume*, G4bool, G4int>())
    
      .def(py::init_alias<G4RotationMatrix*, const G4ThreeVector&,
      const G4String, G4LogicalVolume*,
      G4VPhysicalVolume*, G4bool, G4int>())
    
      .def(py::init_alias<const G4Transform3D&, const G4String&,
      G4LogicalVolume*, G4VPhysicalVolume*, G4bool, G4int>())

      .def(py::init_alias<G4RotationMatrix*, const G4ThreeVector&,
      G4LogicalVolume*, const G4String&,
      G4LogicalVolume*, G4bool, G4int, G4bool>())

      .def(py::init_alias<const G4Transform3D&, G4LogicalVolume*,
      const G4String&, G4LogicalVolume*, G4bool, G4int, G4bool>())

      .def(py::init_alias<G4RotationMatrix*, const G4ThreeVector&,
      const G4String, G4LogicalVolume*,
      G4VPhysicalVolume*, G4bool, G4int, G4bool>())

      .def(py::init_alias<const G4Transform3D&, const G4String&,
      G4LogicalVolume*, G4VPhysicalVolume*, G4bool, G4int, G4bool>())
    */

    // FIXME 
    .def("CheckOverlaps", &G4PVPlacement::CheckOverlaps) //, f_CheckOverlaps())


    //    .def("GetCopyNo", &G4PVPlacement::GetCopyNo)
    //.def("GetCopyNo", &call_GetCopyNo)
    /*
      .def("GetCopyNo",
      [](const G4PVPlacement & s) -> G4int {
      std::cout << "I am in G4PVPlacement::GetCopyNo " << std::endl;
      return s.GetCopyNo();
      }
      )
    */
    
    // debug destructor
    .def("__del__",
         [](const G4PVPlacement&) -> void { 
           std::cerr << "deleting G4PVPlacement" << std::endl;
         })
    ;
}


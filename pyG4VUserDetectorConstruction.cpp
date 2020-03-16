
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

namespace py = pybind11;

void init_G4VUserDetectorConstruction(py::module & m) {
  
  py::class_<G4VUserDetectorConstruction>(m, "G4VUserDetectorConstruction")

    .def("Construct",
         &G4VUserDetectorConstruction::Construct,
         py::return_value_policy::reference)

    /*
      .def("Construct", //&G4VUserDetectorConstruction::Construct, 
      //     pure_virtual(&G4VUserDetectorConstruction::Construct),
      [](G4VUserDetectorConstruction * s) {
      std::cout << "Construct pure virtual" << std::endl;
      return s->Construct();
      }, 
      py::return_value_policy::reference)
    */
    ;
}

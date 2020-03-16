
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4Box.hh"

void init_G4Box(py::module & m) {
  py::class_<G4Box, G4VSolid>(m, "G4Box")

    // constructors
    .def(py::init<const G4String&, G4double, G4double, G4double>())

    .def("GetXHalfLength", &G4Box::GetXHalfLength)
    .def("GetYHalfLength", &G4Box::GetYHalfLength)
    .def("GetZHalfLength", &G4Box::GetZHalfLength)
    .def("SetXHalfLength", &G4Box::SetXHalfLength)
    .def("SetYHalfLength", &G4Box::SetYHalfLength)
    .def("SetZHalfLength", &G4Box::SetZHalfLength)

    // operators
    //.def(self_ns::str(self))
    ;

}


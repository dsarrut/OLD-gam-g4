
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Event.hh"


void init_G4VUserPrimaryGeneratorAction(py::module & m) {

  py::class_<G4VUserPrimaryGeneratorAction>(m, "G4VUserPrimaryGeneratorAction")
    .def("GeneratePrimaries", &G4VUserPrimaryGeneratorAction::GeneratePrimaries)
    ;
}


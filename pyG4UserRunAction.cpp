// --------------------------------------------------
//   Copyright (C): OpenGATE Collaboration
//   This software is distributed under the terms
//   of the GNU Lesser General  Public Licence (LGPL)
//   See LICENSE.md for further details
// --------------------------------------------------

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "G4UserRunAction.hh"
#include "G4Run.hh"

void init_G4UserRunAction(py::module &m) {

    py::class_<G4UserRunAction>(m, "G4UserRunAction")
      .def("BeginOfRunAction", &G4UserRunAction::BeginOfRunAction)
      .def("EndOfRunAction", &G4UserRunAction::EndOfRunAction);
}


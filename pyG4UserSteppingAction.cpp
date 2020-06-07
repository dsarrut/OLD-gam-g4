// --------------------------------------------------
//   Copyright (C): OpenGATE Collaboration
//   This software is distributed under the terms
//   of the GNU Lesser General  Public Licence (LGPL)
//   See LICENSE.md for further details
// --------------------------------------------------

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

void init_G4UserSteppingAction(py::module &m) {

    py::class_<G4UserSteppingAction>(m, "G4UserSteppingAction")
      .def("UserSteppingAction", &G4UserSteppingAction::UserSteppingAction);
}


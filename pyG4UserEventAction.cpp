// --------------------------------------------------
//   Copyright (C): OpenGATE Collaboration
//   This software is distributed under the terms
//   of the GNU Lesser General  Public Licence (LGPL)
//   See LICENSE.md for further details
// --------------------------------------------------

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "G4UserEventAction.hh"
#include "G4Event.hh"

void init_G4UserEventAction(py::module &m) {

    py::class_<G4UserEventAction>(m, "G4UserEventAction")
      .def("BeginOfEventAction", &G4UserEventAction::BeginOfEventAction)
      .def("EndOfEventAction", &G4UserEventAction::EndOfEventAction);
}


/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include "GateVActor.h"
#include "G4Step.hh"
#include "G4VPrimitiveScorer.hh"

void init_GateVActor(py::module &m) {

    py::class_<GateVActor, G4VPrimitiveScorer>(m, "GateVActor")
      .def(py::init<std::string>())
      .def("RegisterSD", &GateVActor::RegisterSD)
      .def("BeforeStart", &GateVActor::BeforeStart)
      .def_readwrite("actions", &GateVActor::actions)
      .def_readonly("batch_step_count", &GateVActor::batch_step_count)
      .def_readwrite("batch_size", &GateVActor::batch_size)
      .def("ProcessBatch", &GateVActor::ProcessBatch)
      //.def("BeginOfEventAction", &GateVActor::BeginOfEventAction)
      //.def("SteppingAction", &GateVActor::SteppingAction)
      .def("EndOfRunAction", &GateVActor::EndOfRunAction)
      ;
}


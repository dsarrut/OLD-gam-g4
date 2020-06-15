/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */
#include <pybind11/pybind11.h>
#include "GateSimulation.h"

namespace py = pybind11;

void init_GateSimulation(py::module &m) {
    py::class_<GateSimulation>(m, "GateSimulation")
      .def(py::init())
      .def("InitializationStart", &GateSimulation::InitializationStart)
      .def("InitializationEnd", &GateSimulation::InitializationEnd)
      .def("Start", &GateSimulation::Start)
      ;

}

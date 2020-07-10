/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "GateAActor.h"

void init_GateAActor(py::module &m) {

    py::class_<GateAActor, GateVActor>(m, "GateAActor")
      .def(py::init());

}


/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "GateTestActor.h"
#include "G4Step.hh"
#include "G4VPrimitiveScorer.hh"


class PyGateTestActor : public GateTestActor {
public:
    /* Inherit the constructors */
    using GateTestActor::GateTestActor;

    /*
    void UserSteppingAction(const G4Step *aStep) {
        // std::cout << "PyGateTestActor trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateTestActor,
                          UserSteppingAction,
                          aStep
        );
    }

    void UserSteppingBatchAction() {
        // std::cout << "PyGateTestActor trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateTestActor,
                          UserSteppingBatchAction,
        );
    }
     */
};


void init_GateTestActor(py::module &m) {

    py::class_<GateTestActor, G4VPrimitiveScorer, PyGateTestActor>(m, "GateTestActor")
      .def(py::init())
      //.def("UserSteppingAction", &GateTestActor::UserSteppingAction)
      //.def("UserSteppingBatchAction", &GateTestActor::UserSteppingBatchAction)
        .def("RegisterSD", &GateTestActor::RegisterSD)
        .def("PrintDebug", &GateTestActor::PrintDebug)
    ;
}


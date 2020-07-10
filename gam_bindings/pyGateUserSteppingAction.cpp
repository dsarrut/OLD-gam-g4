/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "GateUserSteppingAction.h"
#include "G4Step.hh"


class PyGateUserSteppingAction : public GateUserSteppingAction {
public:
    /* Inherit the constructors */
    using GateUserSteppingAction::GateUserSteppingAction;

    /*
    void UserSteppingAction(const G4Step *aStep) {
        // std::cout << "PyGateUserSteppingAction trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateUserSteppingAction,
                          UserSteppingAction,
                          aStep
        );
    }

    void UserSteppingBatchAction() {
        // std::cout << "PyGateUserSteppingAction trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateUserSteppingAction,
                          UserSteppingBatchAction,
        );
    }
     */
};


void init_GateUserSteppingAction(py::module &m) {

    py::class_<GateUserSteppingAction, G4UserSteppingAction, PyGateUserSteppingAction>(m, "GateUserSteppingAction")
      .def(py::init())
      //.def("UserSteppingAction", &GateUserSteppingAction::UserSteppingAction)
      //.def("UserSteppingBatchAction", &GateUserSteppingAction::UserSteppingBatchAction)
      ;
}


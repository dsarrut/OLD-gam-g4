/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */
#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "G4UserSteppingBatchAction.h"
#include "G4UserSteppingAction.hh"
#include "G4Step.hh"


class PyG4UserSteppingBatchAction : public G4UserSteppingBatchAction {
public:
    /* Inherit the constructors */
    using G4UserSteppingBatchAction::G4UserSteppingBatchAction;

    void UserSteppingAction(const G4Step *aStep) {
        // std::cout << "PyG4UserSteppingBatchAction trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          G4UserSteppingBatchAction,
                          UserSteppingAction,
                          aStep
        );
    }

    void UserSteppingBatchAction() {
        // std::cout << "PyG4UserSteppingBatchAction trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          G4UserSteppingBatchAction,
                          UserSteppingBatchAction,
        );
    }
};


void init_G4UserSteppingBatchAction(py::module &m) {

    py::class_<G4UserSteppingBatchAction, G4UserSteppingAction, PyG4UserSteppingBatchAction>(m, "G4UserSteppingBatchAction")
      .def(py::init<int>())
      .def("UserSteppingAction", &G4UserSteppingBatchAction::UserSteppingAction)
      .def("UserSteppingBatchAction", &G4UserSteppingBatchAction::UserSteppingBatchAction)
      ;
}


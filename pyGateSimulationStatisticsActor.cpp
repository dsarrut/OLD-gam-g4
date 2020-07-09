/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "G4Step.hh"

namespace py = pybind11;

#include "GateSimulationStatisticsActor.h"

class PyGateSimulationStatisticsActor : public GateSimulationStatisticsActor {
public:
    /* Inherit the constructors */
    using GateSimulationStatisticsActor::GateSimulationStatisticsActor;

    /*
    void BeginOfEventAction(const G4Event *event) {
        //std::cout << "PyGateSimulationStatisticsActor event trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateSimulationStatisticsActor,
                          BeginOfEventAction,
                          event
        );
    }

    void SteppingAction(G4Step *step) {
        //std::cout << "PyGateSimulationStatisticsActor step trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateSimulationStatisticsActor,
                          SteppingAction,
                          step
        );
    }
*/

    void StepBatchAction() {
        // std::cout << "PyGateSimulationStatisticsActor trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateSimulationStatisticsActor,
                          StepBatchAction,
        );
    }

};

void init_GateSimulationStatisticsActor(py::module &m) {
    py::class_<GateSimulationStatisticsActor, PyGateSimulationStatisticsActor, GateVActor>(m, "GateSimulationStatisticsActor")
      .def(py::init())
      .def("StepBatchAction", &GateSimulationStatisticsActor::StepBatchAction)
      .def_readonly("step_count", &GateSimulationStatisticsActor::step_count)

      ;
}


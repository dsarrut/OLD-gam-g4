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

PYBIND11_MAKE_OPAQUE(std::vector<G4Step*>);

namespace py = pybind11;

#include "GateDoseActor.h"
#include "GateVActor.h"
//#include "itkImage.h"

class PyGateDoseActor : public GateDoseActor {
public:
    /* Inherit the constructors */
    using GateDoseActor::GateDoseActor;

    /*
    void BeginOfEventAction(const G4Event *event) {
        //std::cout << "PyGateDoseActor event trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateDoseActor,
                          BeginOfEventAction,
                          event
        );
    }

    void SteppingAction(G4Step *step) {
        //std::cout << "PyGateDoseActor step trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateDoseActor,
                          SteppingAction,
                          step
        );
    }
*/

    void SteppingBatchAction() {
        // std::cout << "PyGateDoseActor trampoline " << std::endl;
        PYBIND11_OVERLOAD(void,
                          GateDoseActor,
                          SteppingBatchAction,
        );
    }

};

/*struct Wrapper {
    std::unique_ptr<GateDoseActor::ImageType::Pointer> real;
};
 */

void init_GateDoseActor(py::module &m) {
    py::bind_vector<std::vector<G4Step *>>(m, "VectorStep");
    py::class_<GateDoseActor, PyGateDoseActor, GateVActor>(m, "GateDoseActor")
      //PyGateDoseActor
      .def(py::init())
      .def("GetNbStep", &GateDoseActor::GetNbStep)
      .def("PrintDebug", &GateDoseActor::PrintDebug)
      .def("InitSteps", &GateDoseActor::InitSteps)
      .def_readwrite("batch_size", &GateDoseActor::batch_size)
        //.def("BeginOfEventAction", &GateDoseActor::BeginOfEventAction)
      .def("SteppingBatchAction", &GateDoseActor::SteppingBatchAction)
      //.def_readonly("steps", &GateDoseActor::steps)
      .def_readonly("step_edep", &GateDoseActor::step_edep)
      .def_readonly("step_position", &GateDoseActor::step_position)
        //.def("SteppingAction", &GateDoseActor::SteppingAction)
        /*.def("GetDoseImage",
             [](GateDoseActor *s) {
                 std::cout << "I am here" << std::endl;
                 //return py::capsule(s->GetDoseImage());
                 //(void*)s->GetDoseImage();
                 auto i = s->GetDoseImage();
                 Wrapper wclass;
                 wclass.real.reset(i);
                 return wclass;
             })
             */
      ;
}


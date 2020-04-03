
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Event.hh"

class PyG4VUserPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  /* Inherit the constructors */
  using G4VUserPrimaryGeneratorAction::G4VUserPrimaryGeneratorAction;

  /* Trampoline (need one for each virtual function) */
  void GeneratePrimaries(G4Event* anEvent) override {
    std::cout << "--------------> TREMPOLINE PyG4VUserPrimaryGeneratorAction::GeneratePrimaries "<< std::endl;
    PYBIND11_OVERLOAD_PURE(void, 
                           G4VUserPrimaryGeneratorAction, 
                           GeneratePrimaries,
                           anEvent
                           );
  }
  
};



void init_G4VUserPrimaryGeneratorAction(py::module & m) {

  py::class_<G4VUserPrimaryGeneratorAction, PyG4VUserPrimaryGeneratorAction>(m, "G4VUserPrimaryGeneratorAction")

    .def(py::init_alias<>())

    .def("GeneratePrimaries", &G4VUserPrimaryGeneratorAction::GeneratePrimaries)
    
    ;
}


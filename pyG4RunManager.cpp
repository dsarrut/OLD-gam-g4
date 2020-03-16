
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>


#include "G4RunManager.hh"

namespace py = pybind11;


void init_G4RunManager(py::module & m) {
  
  py::class_<G4RunManager>(m, "G4RunManager")
    .def(py::init())


    // test with known arg type
    .def("Initialize",      &G4RunManager::Initialize)
    .def("RestoreRandomNumberStatus", &G4RunManager::RestoreRandomNumberStatus)


    .def("SetUserInitialization", py::overload_cast<G4VUserDetectorConstruction*>
         (&G4RunManager::SetUserInitialization))

    //.def("SetUserInitialization", py::overload_cast<G4VUserPhysicsList*>
    //(&G4RunManager::SetUserInitialization))

    // .def("set", py::overload_cast<int>(&Pet::set), "Set the pet's age")
    // .def("set", py::overload_cast<const std::string &>(&Pet::set), "Set the pet's name");


    ;

}

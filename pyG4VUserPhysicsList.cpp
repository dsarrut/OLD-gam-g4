
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4VUserPhysicsList.hh"

// https://pybind11.readthedocs.io/en/stable/advanced/classes.html
// Needed helper class because of the pure virtual method
class PyG4VUserPhysicsList : public G4VUserPhysicsList {
public:
  /* Inherit the constructors */
  using G4VUserPhysicsList::G4VUserPhysicsList;

  /* Trampoline (need one for each virtual function) */
  void ConstructParticle() override {
    std::cout << "--------------> TREMPOLINE PyG4VUserPhysicsList::ConstructParticle "<< std::endl;
    PYBIND11_OVERLOAD_PURE(void, 
                           G4VUserPhysicsList, 
                           ConstructParticle,
                           );
  }

  void ConstructProcess() override {
    std::cout << "--------------> TREMPOLINE PyG4VUserPhysicsList::ConstructProcess "<< std::endl;
    PYBIND11_OVERLOAD_PURE(void,
                           G4VUserPhysicsList,
                           ConstructProcess,
                           );
  }

  
  void SetCuts() override {
    std::cout << "--------------> TREMPOLINE PyG4VUserPhysicsList::SetCuts "<< std::endl;
    PYBIND11_OVERLOAD(void, // Return type 
                      G4VUserPhysicsList, // Parent class 
                      SetCuts, // Name of function in C++ (must match Python name) 
                      // No argument here  
                      );
  }
  
  
};


void init_G4VUserPhysicsList(py::module & m) {

  py::class_<G4VUserPhysicsList, PyG4VUserPhysicsList>(m, "G4VUserPhysicsList")

    .def(py::init<>())

    // pure virtual 
    .def("ConstructParticle", &G4VUserPhysicsList::ConstructParticle)
    .def("ConstructProcess", &G4VUserPhysicsList::ConstructParticle)

    // virtual 
    .def("SetCuts", &G4VUserPhysicsList::SetCuts)

    /*
    .def("SetCuts", //&G4VUserPhysicsList::SetCuts)
         [](G4VUserPhysicsList & p) -> void {
           std::cout << "$$$$$$$ I am in G4VUserPhysicsList::SetCuts" << std::endl;
           p.SetCuts();
         })
    */

    .def("SetDefaultCutValue", &G4VUserPhysicsList::SetDefaultCutValue)
    .def("GetDefaultCutValue", &G4VUserPhysicsList::GetDefaultCutValue)

    // .def("StorePhysicsTable",     &G4VUserPhysicsList::StorePhysicsTable,
    //      f_StorePhysicsTable()) 
    .def("IsPhysicsTableRetrieved", &G4VUserPhysicsList::IsPhysicsTableRetrieved)
    .def("IsStoredInAscii", &G4VUserPhysicsList::IsStoredInAscii)
    .def("GetPhysicsTableDirectory", 
         &G4VUserPhysicsList::GetPhysicsTableDirectory,
         py::return_value_policy::copy)
    //return_value_policy<return_by_value>())
    .def("SetStoredInAscii", &G4VUserPhysicsList::SetStoredInAscii)
    .def("ResetStoredInAscii", &G4VUserPhysicsList::ResetStoredInAscii)

    .def("DumpList", &G4VUserPhysicsList::DumpList)

    .def("DumpCutValuesTable", &G4VUserPhysicsList::DumpCutValuesTable)
    .def("DumpCutValuesTableIfRequested", &G4VUserPhysicsList::DumpCutValuesTableIfRequested)

    // .def("SetCutValue",           f1_SetCutValue)
    // .def("SetCutValue",           f2_SetCutValue)
    // .def("SetParticleCuts",       f1_SetParticleCuts, f_SetParticleCuts())
    // .def("SetParticleCuts",       f2_SetParticleCuts, f_SetParticleCuts())

    .def("SetVerboseLevel", &G4VUserPhysicsList::SetVerboseLevel)
    .def("GetVerboseLevel", &G4VUserPhysicsList::GetVerboseLevel)
    .def("SetCutsWithDefault", &G4VUserPhysicsList::SetCutsWithDefault)
    .def("SetCutsForRegion", &G4VUserPhysicsList::SetCutsForRegion)
    .def("GetApplyCuts", &G4VUserPhysicsList::GetApplyCuts)
    ;

  // Note that exposed items are limited,
  // because this class object is mainly for internal uses or obsolete.
  // Construct
  // BuildPhysicsTable
  // PreparePhysicsTable
  // SetPhysicsTableRetrieved
  // ReSetPhysicsTableRetrieved
  // SetApplyCuts
  // DumpCutValues (obsolete)
  // ResetCuts;
}

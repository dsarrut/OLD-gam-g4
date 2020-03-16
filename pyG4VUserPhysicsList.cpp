
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4VUserPhysicsList.hh"

// using namespace boost::python;

// // ====================================================================
// // thin wrappers
// // ====================================================================
// namespace pyG4VUserPhysicsList {

// struct CB_G4VUserPhysicsList :
//   G4VUserPhysicsList, wrapper<G4VUserPhysicsList> {

//   void ConstructParticle() {
//     get_override("ConstructParticle")();
//   }

//   void ConstructProcess() {
//     get_override("ConstructProcess")();
//   }

//   void SetCuts() {
//     get_override("SetCuts")();
//   }
// };

// SetCutValue
// void (G4VUserPhysicsList::*f1_SetCutValue)(G4double, const G4String&)
//   = &G4VUserPhysicsList::SetCutValue;
// void (G4VUserPhysicsList::*f2_SetCutValue)(G4double, const G4String&,
// 					   const G4String&)
//   = &G4VUserPhysicsList::SetCutValue;

// // SetParticleCuts
// void (G4VUserPhysicsList::*f1_SetParticleCuts)(G4double,
//                                                G4ParticleDefinition*,
//                                                G4Region*)
//   = &G4VUserPhysicsList::SetParticleCuts;
// void (G4VUserPhysicsList::*f2_SetParticleCuts)(G4double,
//                                                G4ParticleDefinition*,
//                                                G4Region*)
//   = &G4VUserPhysicsList::SetParticleCuts;

// // StorePhysicsTable
// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(f_StorePhysicsTable,
// 				                               StorePhysicsTable, 0, 1)
// // SetParticleCuts
// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(f_SetParticleCuts,
// 				                               SetParticleCuts, 2, 3)

// }

// using namespace pyG4VUserPhysicsList;

void init_G4VUserPhysicsList(py::module & m) {

  py::class_<G4VUserPhysicsList>(m, "G4VUserPhysicsList")

    .def("ConstructParticle", &G4VUserPhysicsList::ConstructParticle)
    //pure_virtual(&G4VUserPhysicsList::ConstructProcess))
    .def("ConstructProcess", &G4VUserPhysicsList::ConstructParticle)
    //pure_virtual(&G4VUserPhysicsList::ConstructProcess))
    .def("SetCuts", &G4VUserPhysicsList::SetCuts)
    //pure_virtual(&G4VUserPhysicsList::SetCuts))

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


#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4Version.hh"
#include "G4NistManager.hh"

// namespace pyG4NistManager {

// // FindOrBuildElement
// G4Element*(G4NistManager::*f1_FindOrBuildElement)(G4int, G4bool)
//   = &G4NistManager::FindOrBuildElement;

// G4Element*(G4NistManager::*f2_FindOrBuildElement)(const G4String&, G4bool)
//   = &G4NistManager::FindOrBuildElement;

// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(f_FindOrBuildElement,
// 				       FindOrBuildElement, 1, 2)

// // PrintElement
// void(G4NistManager::*f1_PrintElement)(const G4String&) const
//   = &G4NistManager::PrintElement;
// void(G4NistManager::*f2_PrintElement)(G4int) const
//   = &G4NistManager::PrintElement;

// // FindOrBuildMaterial
// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(f_FindOrBuildMaterial,
// 				       FindOrBuildMaterial, 1, 2)

// // ConstructNewMaterial
// G4Material*(G4NistManager::*f1_ConstructNewMaterial)
//   (const G4String&, const std::vector<G4String>&,
//    const std::vector<G4int>&, G4double, G4bool,
//    G4State, G4double, G4double)
//   = &G4NistManager::ConstructNewMaterial;

// G4Material*(G4NistManager::*f2_ConstructNewMaterial)
//   (const G4String&, const std::vector<G4String>&,
//    const std::vector<G4double>&, G4double, G4bool,
//    G4State, G4double, G4double)
//   = &G4NistManager::ConstructNewMaterial;

// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(f_ConstructNewMaterial,
// 				       ConstructNewMaterial, 4, 8)

// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(f_ConstructNewGasMaterial,
// 				       ConstructNewGasMaterial, 4, 5)

// }

// using namespace pyG4NistManager;

// #endif

// ====================================================================
// module definition
// ====================================================================


void init_G4NistManager(py::module & m) {

  py::class_<G4NistManager>(m, "G4NistManager")

    .def("Instance", &G4NistManager::Instance, py::return_value_policy::reference)

    .def("SetVerbose",          &G4NistManager::SetVerbose)
    .def("GetVerbose",          &G4NistManager::GetVerbose)
    // ---
    
    // #if G4VERSION_NUMBER < 910
    //     .def("RegisterElement",     &G4NistManager::RegisterElement)
    //     .def("DeRegisterElement",   &G4NistManager::DeRegisterElement)
    // #endif
                       
    .def("GetElement", &G4NistManager::GetElement)//,
    //	 return_internal_reference<>())

    .def("FindOrBuildMaterial",
         [](G4NistManager * m,
            const G4String& symb,
            G4bool isotopes=true,
            G4bool warning=false) {
           return m->FindOrBuildMaterial(symb, isotopes, warning); },
         py::arg("symb"),
         py::arg("isotopes")=true,
         py::arg("warning")=false)

    
    // &G4NistManager::FindOrBuildElement,
    // py::arg("symb"), py::arg("isotope")=true))
      
    /*
      f_FindOrBuildElement()
      [return_value_policy<reference_existing_object>()])
      .def("FindOrBuildElement",  f2_FindOrBuildElement,
      f_FindOrBuildElement()
      [return_value_policy<reference_existing_object>()])
    */
    
    .def("GetNumberOfElements", &G4NistManager::GetNumberOfElements)
    .def("GetZ",                &G4NistManager::GetZ)
    .def("GetIsotopeMass",      &G4NistManager::GetIsotopeMass)

    //.def("PrintElement",        f1_PrintElement)
    //.def("PrintElement",        f2_PrintElement)

    .def("PrintG4Element",      &G4NistManager::PrintG4Element)
    // ---

    // #if G4VERSION_NUMBER < 910
    //     .def("RegisterMaterial",    &G4NistManager::RegisterMaterial)
    //     .def("DeRegisterMaterial",  &G4NistManager::DeRegisterMaterial)
    // #endif

    .def("GetMaterial",         &G4NistManager::GetMaterial)//,
    //   return_value_policy<reference_existing_object>())
    .def("FindOrBuildMaterial", &G4NistManager::FindOrBuildMaterial)//,
    // f_FindOrBuildMaterial()
    // [return_value_policy<reference_existing_object>()])
    /*
      .def("ConstructNewMaterial", f1_ConstructNewMaterial,
      f_ConstructNewMaterial()
      [return_value_policy<reference_existing_object>()])
      .def("ConstructNewMaterial", f2_ConstructNewMaterial,
      f_ConstructNewMaterial()
      [return_value_policy<reference_existing_object>()])
    */
    
    //#if G4VERSION_NUMBER >= 910
    .def("ConstructNewGasMaterial", &G4NistManager::ConstructNewGasMaterial)//,
    // f_ConstructNewGasMaterial()
    // [return_value_policy<reference_existing_object>()])
    //#endif
    
    .def("GetNumberOfMaterials", &G4NistManager::GetNumberOfMaterials)
    .def("ListMaterials",        &G4NistManager::ListMaterials)
    .def("PrintG4Material",      &G4NistManager::PrintG4Material)
    ;
  //#endif
}

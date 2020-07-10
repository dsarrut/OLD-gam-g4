/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "G4NistManager.hh"

void init_G4NistManager(py::module &m) {

    py::class_<G4NistManager>(m, "G4NistManager")

      .def("Instance", &G4NistManager::Instance, py::return_value_policy::reference)

      .def("SetVerbose", &G4NistManager::SetVerbose)
      .def("GetVerbose", &G4NistManager::GetVerbose)

      .def("GetElement", &G4NistManager::GetElement, py::return_value_policy::reference_internal)

      .def("FindOrBuildMaterial",
           [](G4NistManager *m,
              const G4String &symb,
              G4bool isotopes = true,
              G4bool warning = false) {
               return m->FindOrBuildMaterial(symb, isotopes, warning);
           },
           py::arg("symb"),
           py::arg("isotopes") = true,
           py::arg("warning") = false)


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
      .def("GetZ", &G4NistManager::GetZ)
      .def("GetIsotopeMass", &G4NistManager::GetIsotopeMass)

        //.def("PrintElement",        f1_PrintElement)
        //.def("PrintElement",        f2_PrintElement)

      .def("PrintG4Element", &G4NistManager::PrintG4Element)
        // ---

      .def("GetMaterial", &G4NistManager::GetMaterial, py::return_value_policy::reference)

      .def("FindOrBuildMaterial", &G4NistManager::FindOrBuildMaterial, py::return_value_policy::reference)
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

      .def("ConstructNewGasMaterial", &G4NistManager::ConstructNewGasMaterial, py::return_value_policy::reference)
        // f_ConstructNewGasMaterial()

      .def("GetNumberOfMaterials", &G4NistManager::GetNumberOfMaterials)
      .def("ListMaterials", &G4NistManager::ListMaterials)
      .def("PrintG4Material", &G4NistManager::PrintG4Material);
}

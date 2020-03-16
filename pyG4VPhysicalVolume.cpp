
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include "G4Version.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4VPVParameterisation.hh"

namespace py = pybind11;

void init_G4VPhysicalVolume(py::module & m) {

  py::class_<G4VPhysicalVolume>(m, "G4VPhysicalVolume")

    .def("SetTranslation",       &G4VPhysicalVolume::SetTranslation)
    .def("GetTranslation",       &G4VPhysicalVolume::GetTranslation)//,
         //         return_value_policy<return_by_value>())
    
    .def("GetObjectTranslation", &G4VPhysicalVolume::GetObjectTranslation)
    .def("GetFrameTranslation",  &G4VPhysicalVolume::GetObjectTranslation)

    .def("SetRotation",          &G4VPhysicalVolume::SetRotation)
    // FIXME 
    // .def("GetRotation",          f1_GetRotation,
    //      return_internal_reference<>())
    // .def("GetRotation",          f2_GetRotation,
    //      return_internal_reference<>())
    
    .def("GetObjectRotationValue", &G4VPhysicalVolume::GetObjectRotationValue)
    .def("GetFrameRotation",       &G4VPhysicalVolume::GetFrameRotation, py::return_value_policy::reference_internal)

    .def("SetLogicalVolume",     &G4VPhysicalVolume::SetLogicalVolume)
    .def("SetMotherLogical",     &G4VPhysicalVolume::SetMotherLogical)
    .def("GetLogicalVolume",     &G4VPhysicalVolume::GetLogicalVolume, py::return_value_policy::reference_internal)
    .def("GetMotherLogical",     &G4VPhysicalVolume::GetMotherLogical, py::return_value_policy::reference_internal)
    
    .def("SetName",             &G4VPhysicalVolume::SetName)
    .def("GetName",             &G4VPhysicalVolume::GetName, py::return_value_policy::copy)
    //      return_value_policy<return_by_value>())

    .def("SetCopyNo",           &G4VPhysicalVolume::SetCopyNo)
    .def("GetCopyNo",           &G4VPhysicalVolume::GetCopyNo)
    
    .def("IsMany",              &G4VPhysicalVolume::IsMany)
    .def("IsReplicated",        &G4VPhysicalVolume::IsReplicated)
    .def("IsParameterised",     &G4VPhysicalVolume::IsParameterised)
    .def("GetMultiplicity",     &G4VPhysicalVolume::GetMultiplicity)
    .def("GetParameterisation", &G4VPhysicalVolume::GetParameterisation, py::return_value_policy::reference)
    //      return_value_policy<reference_existing_object>())

    // debug destructor
    .def("__del__",
         [](const G4VPhysicalVolume&) -> void { 
           std::cerr << "---------------> deleting G4VPhysicalVolume" << std::endl;
         })

    
    ;
}

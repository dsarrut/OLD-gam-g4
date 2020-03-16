
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4Event.hh"

void init_G4Event(py::module & m) {
  py::class_<G4Event>(m, "G4Event")

    .def(py::init<int>())

    .def("Print",              &G4Event::Print)
    .def("Draw",               &G4Event::Draw)
    .def("SetEventID",         &G4Event::SetEventID)
    .def("GetEventID",         &G4Event::GetEventID)
    .def("SetEventAborted",    &G4Event::SetEventAborted)
    .def("IsAborted",          &G4Event::IsAborted)

    .def("AddPrimaryVertex",   &G4Event::AddPrimaryVertex)
    .def("GetNumberOfPrimaryVertex", &G4Event::GetNumberOfPrimaryVertex)
    .def("GetPrimaryVertex",   &G4Event::GetPrimaryVertex, py::return_value_policy::reference_internal)
    //	 f_GetPrimaryVertex()[return_internal_reference<>()])

    
    .def("GetTrajectoryContainer", &G4Event::GetTrajectoryContainer, py::return_value_policy::reference_internal)
    //	 return_internal_reference<>())

    .def("SetUserInformation", &G4Event::SetUserInformation)
    .def("GetUserInformation", &G4Event::GetUserInformation, py::return_value_policy::reference_internal)
    //	 return_internal_reference<>())
    
    ;

  // reduced functionality...
  //.def("SetHCofThisEvent",   &G4Event::SetHCofThisEvent)
  //.def("GetHCofThisEvent",   &G4Event::SetHCofThisEvent,
  //     return_internal_reference<>())
  //.def("SetDCofThisEvent",   &G4Event::SetHCofThisEvent)
  //.def("GetDCofThisEvent",   &G4Event::SetHCofThisEvent,
  //     return_internal_reference<>())

}

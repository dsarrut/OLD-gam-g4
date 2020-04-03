
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4UImanager.hh"
#include "G4UIcommandTree.hh"

// ====================================================================
// wrappers
// ====================================================================
// namespace pyG4UImanager {

// // ApplyCommand
// G4int(G4UImanager::*f1_ApplyCommand)(const char*) = &G4UImanager::ApplyCommand;
// G4int(G4UImanager::*f2_ApplyCommand)(const G4String&) =
//   &G4UImanager::ApplyCommand;

// // CreateHTML
// BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(f_CreateHTML, CreateHTML, 0, 1)


//////////////////////////////////////////////
G4int ApplyUICommand_1(const G4String& cmdstr)
//////////////////////////////////////////////
{
  G4UImanager* UImgr= G4UImanager::GetUIpointer();
  G4int returnVal= UImgr-> ApplyCommand(cmdstr);
  if( returnVal == fCommandSucceeded ) return returnVal;

  G4int paramIndex= returnVal % 100;
  G4int commandStatus= returnVal - paramIndex;

  switch(commandStatus) {
  case fCommandSucceeded:
    break;

  case fCommandNotFound:
    G4cout << "command <" << UImgr-> SolveAlias(cmdstr)
           << "> not found" << G4endl;
    break;

  case fIllegalApplicationState:
    G4cout << "illegal application state -- command refused"
           << G4endl;
    break;

  case fParameterOutOfRange:
    break;

  case fParameterOutOfCandidates:
    G4cout << "Parameter is out of candidate list (index "
           << paramIndex << ")"
           << G4endl;
    break;

  case fParameterUnreadable:
    G4cout << "Parameter is wrong type and/or is not omittable (index "
           << paramIndex << ")" << G4endl;
    break;

  case fAliasNotFound:
    break;

  default:
    G4cout << "command refused (" << commandStatus << ")" << G4endl;
    break;
  }

  return returnVal;
}

/////////////////////////////////////////////////
G4int ApplyUICommand_2(const std::string& cmdstr)
/////////////////////////////////////////////////
{
  return ApplyUICommand_1(cmdstr);
}

//}

//using namespace pyG4UImanager;

// ====================================================================
// module definition
// ====================================================================
void init_G4UImanager(py::module & m) {
  
  py::class_<G4UImanager>(m, "G4UImanager")
    
    .def("GetUIpointer",  &G4UImanager::GetUIpointer, py::return_value_policy::reference)
    //.staticmethod("GetUIpointer")
    
    .def("GetCurrentValues", &G4UImanager::GetCurrentValues)
    .def("ExecuteMacroFile", &G4UImanager::ExecuteMacroFile)

    // .def("ApplyCommand",     f1_ApplyCommand)
    // .def("ApplyCommand",     f2_ApplyCommand)

    .def("ApplyCommand", py::overload_cast<const char *>(&G4UImanager::ApplyCommand))
    .def("ApplyCommand", py::overload_cast<const G4String&>(&G4UImanager::ApplyCommand))
    
    //.def("CreateHTML",       &G4UImanager::CreateHTML, f_CreateHTML())
    .def("SetMacroSearchPath", &G4UImanager::SetMacroSearchPath)
    .def("GetMacroSearchPath", &G4UImanager::GetMacroSearchPath, py::return_value_policy::copy)
    //        return_value_policy<return_by_value>())

    .def("SetPauseAtBeginOfEvent", &G4UImanager::SetPauseAtBeginOfEvent)
    .def("GetPauseAtBeginOfEvent", &G4UImanager::GetPauseAtBeginOfEvent)
    .def("SetPauseAtEndOfEvent",   &G4UImanager::SetPauseAtEndOfEvent)
    .def("GetPauseAtEndOfEvent",   &G4UImanager::GetPauseAtEndOfEvent)
    .def("SetVerboseLevel",        &G4UImanager::SetVerboseLevel)
    .def("GetVerboseLevel",        &G4UImanager::GetVerboseLevel)

    .def("GetTree",   &G4UImanager::GetTree, py::return_value_policy::reference)
    //         return_value_policy<reference_existing_object>())
    ;

  // ---
  //def("ApplyUICommand",    ApplyUICommand_1);
  //def("ApplyUICommand",    ApplyUICommand_2);

}


#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4VUserActionInitialization.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SteppingVerbose.hh"
#include "G4Event.hh"


void init_G4VUserActionInitialization(py::module & m) {

  py::class_<G4VUserActionInitialization>(m, "G4VUserActionInitialization")


    // pure virtual 
    // Virtual method to be implemented by the user to instantiate user action
    .def("Build", &G4VUserActionInitialization::Build)
    
    // Virtual method to be implemented by the user to instantiate user run action
    // class object to be used by G4MTRunManager. This method is not invoked in
    // the sequential mode. The user should not use this method to instantiate
    // user action classes rather than user run action.
    .def("BuildForMaster", &G4VUserActionInitialization::BuildForMaster)
    
    // Virtual method to be implemented by the user if (s)he has a concrete
    // SteppingVerbose class to be used by the worker thread. In this case
    // (s)he should instantiate her/his SteppingVerbose in the concrete
    // implementation of this method and return its pointer. If this method is
    // not implemented, the default G4SteppingVerbose will be used. Please note
    // that this method affects only for the worker thread.
    .def("InitializeSteppingVerbose", &G4VUserActionInitialization::InitializeSteppingVerbose)

    // G4VSteppingVerbose* FIXME 

    /*
    .def("SetUserAction",
         py::overload_cast<G4VUserPrimaryGeneratorAction*>(&G4VUserActionInitialization::SetUserAction, py::const_))
    */
    
    /*
      protected: // with description
      void SetUserAction(G4VUserPrimaryGeneratorAction*) const;
      void SetUserAction(G4UserRunAction*) const;
      void SetUserAction(G4UserEventAction*) const;
      void SetUserAction(G4UserStackingAction*) const;
      void SetUserAction(G4UserTrackingAction*) const;
      void SetUserAction(G4UserSteppingAction*) const;
    */
    

    ;
}


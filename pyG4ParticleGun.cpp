
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

//#include "ParticleGunAction.hh"
#include "G4ParticleGun.hh"
#include "G4RunManager.hh"
#include "G4VPrimaryGenerator.hh"

// ====================================================================
// namespace pyParticleGun {

// G4ParticleGun* Construct()
// {
//   G4RunManager* runMgr= G4RunManager::GetRunManager();

//   ParticleGunAction* pga= new ParticleGunAction;
//   runMgr-> SetUserAction(pga);

//   return pga-> GetParticleGun();
// }

// }

// using namespace pyParticleGun;

void init_G4ParticleGun(py::module & m) {
  
  py::class_<G4ParticleGun, G4VPrimaryGenerator>(m, "G4ParticleGun")

    .def(py::init())
    .def(py::init<int>())

    
  //   ("ParticleGunAction", "primary generator action with particle gun")
  //   .def("GetParticleGun", &ParticleGunAction::GetParticleGun,
  //        return_internal_reference<>())
  //   ;

  // // ---
  // def("Construct", Construct,
  //     return_value_policy<reference_existing_object>());

    ;
}


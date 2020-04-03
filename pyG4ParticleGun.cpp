
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


    .def("GeneratePrimaryVertex", &G4ParticleGun::GeneratePrimaryVertex)
    .def("SetParticleDefinition", &G4ParticleGun::SetParticleDefinition)

    .def("SetParticleMomentumDirection", &G4ParticleGun::SetParticleMomentumDirection)

    .def("SetParticleEnergy", &G4ParticleGun::SetParticleEnergy)

    .def("SetParticlePosition",   &G4ParticleGun::SetParticlePosition)

    /*

      void SetParticleDefinition
      (G4ParticleDefinition * aParticleDefinition);
      void SetParticleEnergy(G4double aKineticEnergy);
      void SetParticleMomentum(G4double aMomentum);
      void SetParticleMomentum(G4ParticleMomentum aMomentum);
      void SetParticleMomentumDirection
      (G4ParticleMomentum aMomentumDirection)
      { particle_momentum_direction =  aMomentumDirection.unit(); }
      void SetParticleCharge(G4double aCharge)
      { particle_charge = aCharge; }
      void SetParticlePolarization(G4ThreeVector aVal)
      { particle_polarization = aVal; }
      void SetNumberOfParticles(G4int i)
      { NumberOfParticlesToBeGenerated = i; }

      public:
      G4ParticleDefinition* GetParticleDefinition() const
      { return particle_definition; }
      G4ParticleMomentum GetParticleMomentumDirection() const
      { return particle_momentum_direction; }
      G4double GetParticleEnergy() const
      { return particle_energy; }
      G4double GetParticleMomentum() const
      { return particle_momentum; }
      G4double GetParticleCharge() const
      { return particle_charge; }
      G4ThreeVector GetParticlePolarization() const
      { return particle_polarization; }
      G4int GetNumberOfParticles() const
      { return NumberOfParticlesToBeGenerated; }
    */    
    
    //   ("ParticleGunAction", "primary generator action with particle gun")
    //   .def("GetParticleGun", &ParticleGunAction::GetParticleGun,
    //        return_internal_reference<>())
    //   ;
    
    // // ---
    // def("Construct", Construct,
    //     return_value_policy<reference_existing_object>());

    ;
}


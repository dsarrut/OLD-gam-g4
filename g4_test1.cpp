#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include <getopt.h>
#include <cstdlib>
#include <queue>
#include <locale.h>

#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4VModularPhysicsList.hh"
#include "QBBC.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"


class Test1DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  Test1DetectorConstruction():
    G4VUserDetectorConstruction() {}
    
  virtual ~Test1DetectorConstruction() {}

  virtual G4VPhysicalVolume* Construct() {
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
  
    G4bool checkOverlaps = true;

    // world
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
    G4Box* solidWorld =    
      new G4Box("World", 2*m, 2*m, 2*m);
    G4LogicalVolume* logicWorld =                         
      new G4LogicalVolume(solidWorld,          //its solid
                          world_mat,           //its material
                          "World");            //its name
    G4VPhysicalVolume* physWorld = 
      new G4PVPlacement(0,                     //no rotation
                        G4ThreeVector(),       //at (0,0,0)
                        logicWorld,            //its logical volume
                        "World",               //its name
                        0,                     //its mother  volume
                        false,                 //no boolean operation
                        0,                     //copy number
                        checkOverlaps);        //overlaps checking
                     
    // waterbox
    G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
   
    G4Box* solidEnv =    
      new G4Box("waterbox", 20*cm, 20*cm, 20*cm);
    G4LogicalVolume* logicEnv =                         
      new G4LogicalVolume(solidEnv,            //its solid
                          env_mat,             //its material
                          "waterbox");         //its name
    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(),         //at (0,0,0)
                      logicEnv,                //its logical volume
                      "waterbox",              //its name
                      logicWorld,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking
    return physWorld; 
  }
    
};


class Test1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  Test1PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun  = new G4ParticleGun(n_particle);

    // default particle kinematic
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    G4ParticleDefinition* particle
      = particleTable->FindParticle(particleName="gamma");
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
    fParticleGun->SetParticleEnergy(6.*MeV);
  }
  virtual ~Test1PrimaryGeneratorAction() {}

  // method from the base class
  virtual void GeneratePrimaries(G4Event* anEvent) {
    G4double size = 0.8; 
    G4double x0 = size * 200 * (G4UniformRand()-0.5);
    G4double y0 = size * 200 * (G4UniformRand()-0.5);
    G4double z0 = -0.5 * 200;
  
    fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

    fParticleGun->GeneratePrimaryVertex(anEvent);

  }
  
  // method to access particle gun
  const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
private:
  G4ParticleGun* fParticleGun; // pointer a to G4 gun class
};



//-----------------------------------------------------------------------------
int main()
{
  // construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // Physics list
  G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // set mandatory initialization classes
  runManager->SetUserInitialization(new Test1DetectorConstruction);
  runManager->SetUserInitialization(physicsList);
  //  runManager->SetUserInitialization(new Test1G4ActionInitialization);
  runManager->SetUserAction(new Test1PrimaryGeneratorAction);

  // initialize G4 kernel
  runManager->Initialize();

  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 2");
  UI->ApplyCommand("/event/verbose 2");
  UI->ApplyCommand("/tracking/verbose 2");

  // start a run
  int numberOfEvent = 3;
  runManager->BeamOn(numberOfEvent);

  // job termination
  delete runManager;
  return 0;
}
//-----------------------------------------------------------------------------

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

// #include <getopt.h>
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

#include "G4UserRunAction.hh"
#include "G4UserSteppingAction.hh"
#include "G4UserSteppingBatchAction.h"
#include "G4UserEventAction.hh"
#include "G4VUserActionInitialization.hh"
#include "GateTestActor.h"

#include <chrono>

using namespace std::chrono;

class GateUIsession : public G4UIsession {
public:

    virtual G4int ReceiveG4cout(const G4String &coutString) {
        //std::cout << "HERE " << coutString << std::endl;
        return 0;
    }

    virtual G4int ReceiveG4cerr(const G4String &cerrString) {
        std::cout << "HERE CERR  " << cerrString << std::endl;
        return 0;
    }

};

class Test1DetectorConstruction : public G4VUserDetectorConstruction {
public:
    Test1DetectorConstruction() :
      G4VUserDetectorConstruction() {}

    virtual ~Test1DetectorConstruction() {
        std::cout << "destructor Test1DetectorConstruction" << std::endl;

    }

    G4LogicalVolume *waterbox_log;
    G4LogicalVolume *world_log;

    virtual G4VPhysicalVolume *Construct() {
        // Get nist material manager
        G4NistManager *nist = G4NistManager::Instance();

        G4bool checkOverlaps = true;

        // world
        G4Material *world_mat = nist->FindOrBuildMaterial("G4_AIR");

        G4Box *solidWorld =
          new G4Box("World", 5 * m, 5 * m, 5 * m);
        world_log =
          new G4LogicalVolume(solidWorld,          //its solid
                              world_mat,           //its material
                              "World");            //its name
        G4VPhysicalVolume *physWorld =
          new G4PVPlacement(0,                     //no rotation
                            G4ThreeVector(),       //at (0,0,0)
                            world_log,            //its logical volume
                            "World",               //its name
                            0,                     //its mother  volume
                            false,                 //no boolean operation
                            0,                     //copy number
                            checkOverlaps);        //overlaps checking

        // waterbox_log
        G4Material *env_mat = nist->FindOrBuildMaterial("G4_WATER");

        G4Box *solidEnv =
          new G4Box("waterbox_log", 20 * cm, 20 * cm, 20 * cm);
        waterbox_log =
          new G4LogicalVolume(solidEnv,            //its solid
                              env_mat,             //its material
                              "waterbox_log");         //its name
        auto position = G4ThreeVector(0, 0, 25 * cm);
        new G4PVPlacement(0,                       //no rotation
                          position,                //at (0,0,25)
                          waterbox_log,                //its logical volume
                          "waterbox_log",              //its name
                          world_log,              //its mother  volume
                          false,                   //no boolean operation
                          0,                       //copy number
                          checkOverlaps);          //overlaps checking
        return physWorld;
    }

};

class Test1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    Test1PrimaryGeneratorAction() {
        init();
    }

    void init() {
        G4int n_particle = 1;
        fParticleGun = new G4ParticleGun(n_particle);

        // default particle kinematic
        G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
        G4String particleName;
        G4ParticleDefinition *particle
          = particleTable->FindParticle(particleName = "proton");
        //= particleTable->FindParticle(particleName = "gamma");
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
        fParticleGun->SetParticleEnergy(150. * MeV);
        //fParticleGun->SetParticleEnergy(0.1 * MeV);
    }

    virtual ~Test1PrimaryGeneratorAction() {}

    // method from the base class
    virtual void GeneratePrimaries(G4Event *anEvent) {
        G4double size = 3 * cm;
        G4double x0 = size * (G4UniformRand() - 0.5);
        G4double y0 = size * (G4UniformRand() - 0.5);
        G4double z0 = 0;
        // std::cout << "position particle " << x0 << " " << y0 << " " << z0 << std::endl;
        fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }

    // method to access particle gun
    const G4ParticleGun *GetParticleGun() const { return fParticleGun; }

private:
    G4ParticleGun *fParticleGun; // pointer a to G4 gun class
};

//-----------------------------------------------------------------------------
class B1RunAction : public G4UserRunAction {
public:
    B1RunAction() : G4UserRunAction() {}

    virtual ~B1RunAction() {}

    virtual void BeginOfRunAction(const G4Run *) {
        std::cout << "Start RUN " << std::endl;
    }

    virtual void EndOfRunAction(const G4Run *) {}
};

//-----------------------------------------------------------------------------
class B1EventAction : public G4UserEventAction {
public:
    B1EventAction(B1RunAction * /*runAction*/) : G4UserEventAction() {}

    virtual ~B1EventAction() {}

    virtual void BeginOfEventAction(const G4Event *event) {
        //std::cout << "BeginOfEventAction " << event->GetEventID() << std::endl;
    }

    virtual void EndOfEventAction(const G4Event * /*event*/) {}
};

//-----------------------------------------------------------------------------
class B1SteppingAction : public G4UserSteppingAction {
public:

    std::vector<double> depth_dose;
    int nb_step;
    int nb_step_wb;

    B1SteppingAction(B1EventAction * /*eventAction*/) : G4UserSteppingAction() {
        depth_dose.resize(100);
        nb_step = 0;
        nb_step_wb = 0;
    }

    virtual ~B1SteppingAction() {
        std::cout << "End Step " << nb_step << " " << nb_step_wb << std::endl;
    }

    // method from the base class
    virtual void UserSteppingAction(const G4Step *step) {
        //std::cout << "UserSteppingAction " << step->GetTotalEnergyDeposit() << std::endl;
        nb_step += 1;
        auto sp = step->GetPreStepPoint();
        auto name = sp->GetPhysicalVolume()->GetName();
        if (name != "waterbox_log") return;

        nb_step_wb += 1;
        auto edep = step->GetTotalEnergyDeposit();
        auto density = 1.0;
        auto volume = 1.0;
        auto dose = edep / density / volume / gray;
        auto depth = 400;
        auto p = step->GetPostStepPoint()->GetPosition();
        int n = (int)depth_dose.size();
        auto i = (int) ((p.z() - 50) / depth * n);
        if (i > (n - 1)) i = n - 1;
        depth_dose[i] += dose;
    }
};

//-----------------------------------------------------------------------------
class B1SteppingBatchAction : public G4UserSteppingBatchAction {
public:

    int num_batch;

    B1SteppingBatchAction(B1EventAction * /*eventAction*/) :
      G4UserSteppingBatchAction(100000) {
        num_batch = 0;
    }

    virtual ~B1SteppingBatchAction() {
        std::cout << "dest B1SteppingBatchAction " << num_batch << std::endl;
    }

    // method from the base class
    virtual void UserSteppingBatchAction() {
        //std::cout << "UserSteppingBatchAction " << std::endl;
        num_batch++;
    }
};


//-----------------------------------------------------------------------------
class B1ActionInitialization : public G4VUserActionInitialization {
public:

    B1ActionInitialization() : G4VUserActionInitialization() {
    }

    virtual ~B1ActionInitialization() {}

    virtual void BuildForMaster() const {
        B1RunAction *runAction = new B1RunAction;
        SetUserAction(runAction);
    }

    virtual void Build() const {
        //static Test1PrimaryGeneratorAction * gen = new Test1PrimaryGeneratorAction;
        //SetUserAction(gen);
        SetUserAction(new Test1PrimaryGeneratorAction);
        B1RunAction *runAction = new B1RunAction;
        SetUserAction(runAction);
        B1EventAction *eventAction = new B1EventAction(runAction);
        SetUserAction(eventAction);
        //SetUserAction(new B1SteppingAction(eventAction));
        //SetUserAction(new B1SteppingBatchAction(eventAction));
        //gen->init();
    }
};


//-----------------------------------------------------------------------------
int main() {

    std::cout << "hello world" << std::endl;

    // get the pointer to the UI manager and set verbosities
    G4UImanager *UI = G4UImanager::GetUIpointer();
    //UI->ApplyCommand("/run/verbose 2");
    //UI->ApplyCommand("/event/verbose 2");
    //UI->ApplyCommand("/tracking/verbose 2");
    GateUIsession *LoggedSession = new GateUIsession;
    UI->SetCoutDestination(LoggedSession);

    // construct the default run manager
    G4RunManager *runManager = new G4RunManager;
    std::cout << "end" << std::endl;

    auto DC = new Test1DetectorConstruction;
    runManager->SetUserInitialization(DC);

    // Physics list
    G4VModularPhysicsList *physicsList = new QBBC;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    particleTable->DumpTable("ALL");

    // set mandatory initialization classes
    //runManager->SetUserInitialization(physicsList);
    //runManager->SetUserAction(new Test1PrimaryGeneratorAction);
    runManager->SetUserInitialization(new B1ActionInitialization);

    std::cout << "before rnd engine" << std::endl;
    auto engine = new CLHEP::MTwistEngine;
    G4Random::setTheEngine(engine);
    long seed = 4532;
    G4Random::setTheSeeds(&seed, 0);
    std::cout << "after rnd engine" << std::endl;

    // initialize G4 kernel
    runManager->Initialize();

    // get the pointer to the UI manager and set verbosities
    //UI->ApplyCommand("/run/verbose 2");
    //UI->ApplyCommand("/event/verbose 2");
    //UI->ApplyCommand("/tracking/verbose 2");

    auto actor = new GateTestActor();
    actor->RegisterSD(DC->waterbox_log);

    auto actor2 = new GateTestActor();
    actor2->RegisterSD(DC->waterbox_log);

    auto actor3 = new GateTestActor();
    actor3->RegisterSD(DC->world_log);

    // start a run
    //int numberOfEvent = 30000;
    int numberOfEvent = 5000;
    auto start = high_resolution_clock::now();
    runManager->BeamOn(numberOfEvent);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    std::cout << "timing " << duration.count() / 1000.0 << " s " << std::endl;
    std::cout << "numberOfEvent " << numberOfEvent << std::endl;
    actor->PrintDebug();
    actor2->PrintDebug();
    actor3->PrintDebug();

    //delete actor;

    // job termination
    //delete runManager;
    return 0;
}
//-----------------------------------------------------------------------------

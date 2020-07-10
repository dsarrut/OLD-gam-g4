/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include "GateVActor.h"
#include "G4SDManager.hh"


GateVActor::GateVActor(std::string name) : G4VPrimitiveScorer(name) {
    std::cout << "GateVActor construction " << name << std::endl;
}

GateVActor::~GateVActor() {
    std::cout << "GateVActor destructor " << std::endl;
}

void GateVActor::BeforeStart() {
    batch_step_count = 0;
}

G4bool GateVActor::ProcessHits(G4Step * /*step*/,
                               G4TouchableHistory * /*touchable*/) {
    // FIXME not clear if needed
    // SteppingAction(step);
    ProcessBatch();
    return true;
}

void GateVActor::RegisterSD(G4LogicalVolume *l) {
    logicalVolumes.push_back(l);
    // std::cout << "GateVActor RegisterSD " << std::endl;
    // FIXME : check if already set
    // FIXME : allow several volume to be registered.
    auto currentSD = l->GetSensitiveDetector();
    G4MultiFunctionalDetector *mfd;
    if (!currentSD) {
        // std::cout << "first actor for this volume" << std::endl;
        mfd = new G4MultiFunctionalDetector("mfd_" + l->GetName());
        // do not always create check if exist
        // auto pointer
        G4SDManager::GetSDMpointer()->AddNewDetector(mfd);
        l->SetSensitiveDetector(mfd);
    } else {
        // std::cout << "already an actor reuse it" << std::endl;
        mfd = dynamic_cast<G4MultiFunctionalDetector *>(currentSD);
    }
    mfd->RegisterPrimitive(this);
}

void GateVActor::BeginOfEventAction(const G4Event * /*event*/) {
    //std::cout << "GateVActor BeginOfEventAction " << std::endl;
}

void GateVActor::StepBatchAction() {
    // nothing, will be overwritten
}

//virtual void SteppingAction(G4Step *step);

void GateVActor::ProcessBatch(bool force) {
    batch_step_count ++;
    if (force or batch_step_count >= batch_size) {
        StepBatchAction();
        batch_step_count = 0;
    }
}

// FIXME --> need batch at the end of run ?

void GateVActor::EndOfEventAction(const G4Event * /*event*/) {
    //std::cout << "GateVActor EndOfEventAction " << std::endl;
}

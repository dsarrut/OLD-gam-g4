/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include "GateDoseActor.h"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"

GateDoseActor::GateDoseActor() : GateVActor("DoseActor") {
    std::cout << "GateDoseActor construction " << std::endl;
    nb_step = 0;
    nb_event = 0;
    batch_current = 0;
    nb_batch = 0;
    batch_size = 500;
}

GateDoseActor::~GateDoseActor() {
    std::cout << "GateDoseActor destructor " << std::endl;
    std::cout << "event = " << nb_event
              << " step = " << nb_step
              << " batch = " << nb_batch << std::endl;
}

void GateDoseActor::PrintDebug() {
    std::cout << "event = " << nb_event
              << " step = " << nb_step
              << " batch = " << nb_batch
              << " edep = " << edep
              << std::endl;
}

void GateDoseActor::BeginOfEventAction(const G4Event * /*event */) {
    //std::cout << "GateDoseActor BeginOfEventAction " << std::endl;
    //std::cout << mDoseImage->GetLargestPossibleRegion().GetSize() << std::endl;
    nb_event += 1;
}

void GateDoseActor::InitSteps() {
    //steps.resize(batch_size);
    step_edep.resize(batch_size);
    step_position.resize(batch_size);
    edep = 0;
    volDepth = -1;
    std::cout << "GateDoseActor init steps size = " << step_edep.size() << std::endl;
}

void GateDoseActor::ComputeVolumeDepth(G4TouchableHistory *touchable) {
    volDepth = 0;
    auto currentVol = touchable->GetVolume(0)->GetLogicalVolume();
    int maxDepth = touchable->GetHistoryDepth();
    int depth = 0;
    bool found = false;
    int transDepth = maxDepth;
    std::cout << "Find volume depth " << currentVol->GetName()
              << " max " << maxDepth << std::endl;
    while (!found) {
        auto name = currentVol->GetName();
        for (auto l:logicalVolumes) {
            std::cout << "depth " << depth << " "
                      << l->GetName() << std::endl;
            if (name == l->GetName()) {
                found = true;
                continue;
            }
        }
        if (!found) {
            depth++;
            transDepth--;
            if (depth >= maxDepth)
                found = true;
        }
    }
    std::cout << "End with depth " << depth
    << " transdepth " << transDepth << std::endl;
    if (depth >= maxDepth) {
        std::cerr << "Error depth " << std::endl;
        exit(0);
    }
    volDepth = transDepth;
}

void GateDoseActor::SteppingAction(G4Step *step) {
    //std::cout << "GateDoseActor SteppingAction " << batch_current << std::endl;
    //steps[batch_current] = step; //new G4Step(*step);
    //steps[batch_current] = new G4Step(*step);
    step_edep[batch_current] = step->GetTotalEnergyDeposit();

    // This position is in world coordinate system (not in volume)
    auto touchable = step->GetPreStepPoint()->GetTouchable();
    //auto copyNo = touchable->GetVolume(0)->GetCopyNo();
    auto worldPos = step->GetPreStepPoint()->GetPosition();
    if (volDepth == -1) ComputeVolumeDepth((G4TouchableHistory *) (touchable));
    auto localPos = touchable->GetHistory()->GetTransform(volDepth).TransformPoint(worldPos);

    step_position[batch_current] = localPos;

    // volume
    //auto prePosition = touchable->GetHistory()->GetTransform(transDepth).TransformPoint(worldPre);

    nb_step += 1;
    batch_current += 1;
    if (batch_current >= batch_size) {
        SteppingBatchAction();
        batch_current = 0;
    }
}


void GateDoseActor::SteppingBatchAction() {
    std::cout << "GateDoseActor Batch " << nb_batch << std::endl;
    nb_batch += 1;
    //for(auto s:steps) {
    //   edep += s->GetTotalEnergyDeposit();
    //}
    for (auto e:step_edep)
        edep += e;
}


/*
GateDoseActor::ImageType * GateDoseActor::GetDoseImage() {
    return mDoseImage;
}
*/
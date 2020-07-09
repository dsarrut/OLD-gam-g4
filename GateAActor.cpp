/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include "GateAActor.h"

GateAActor::GateAActor() : GateVActor("AActor") {
    std::cout << "GateAActor construction " << std::endl;
}

GateAActor::~GateAActor() {
    std::cout << "GateAActor destructor " << std::endl;
    std::cout << "A " << nb_event << " " << nb_step << std::endl;
}


void GateAActor::BeginOfEventAction(const G4Event * /*event*/) {
    //std::cout << "GateAActor BeginOfEventAction " << std::endl;
    nb_event += 1;
}


void GateAActor::SteppingAction(G4Step * /*step*/) {
    //std::cout << "GateAActor SteppingAction " << std::endl;
    nb_step += 1;
}
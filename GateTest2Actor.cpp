/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "GateTest2Actor.h"

GateTest2Actor::GateTest2Actor(GateAction * action) : GateVActor("Test2", action) {
    std::cout << "GateTest2Actor Constructor" << std::endl;
}

GateTest2Actor::~GateTest2Actor() {
    std::cout << "GateTest2Actor Destructor" << std::endl;
    //delete mfd;
}

void GateTest2Actor::Build() {
    std::cout << "Build " std::endl;



    RegisterSteppingAction();
    RegisterBeginOfEventAction();
}

void GateTest2Actor::SteppingAction(G4Step * step) {
    std::cout << "step " std::endl;
}

void GateTest2Actor::BeginOfEventAction(const G4Event * event) {
    std::cout << "Begin event " << event->GetEventID() << std::endl;
}

/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include "GateAction.h"
#include "GateEventAction.h"

GateAction::GateAction() : G4VUserActionInitialization() {

}

GateAction::~GateAction() {

}

void GateAction::Build() const {
    std::cout << "GateAction::Build " << std::endl;
    // FIXME check not NULL
    SetUserAction(primaryGeneratorAction);

    // Create the action of all events types
    eventAction = new GateEventAction;
    SetUserAction(eventAction);

    // Register all actors if needed
    for (auto actor:actors) {
        std::cout << "actor" << actor->GetName() << std::endl;
        actor->RegisterAction(this);
    }
}

void GateAction::BuildForMaster() const {
    std::cout << "GateAction::BuildForMaster ?? STOP" << std::endl;
    exit(0)
}

void GateAction::RegisterSource(G4VUserPrimaryGeneratorAction *p) {
    primaryGeneratorAction = p;
}

void GateAction::RegisterActor(GateVActor *actor) {
    actor.push_back(actor);
}

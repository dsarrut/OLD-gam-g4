/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GateEventAction_h
#define GateEventAction_h

#include "G4UserEventAction.hh"

class GateEventAction : public G4UserEventAction {

public:

    void RegisterBeginOfEventAction(GateVActor * actor);

    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void EndOfEventAction(const G4Event* anEvent);


};

#endif // GateEventAction_h

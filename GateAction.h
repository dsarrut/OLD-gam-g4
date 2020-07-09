/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GateAction_h
#define GateAction_h

#include "G4VUserActionInitialization.hh"
#include "GateVActor.h"

class GateAction : public G4VUserActionInitialization {

public:

    GateAction();
    virtual ~GateAction();
    virtual void Build() const;
    virtual void BuildForMaster() const;
    void RegisterSource(G4VUserPrimaryGeneratorAction *);
    void RegisterActor(GateVActor * actor);

protected:
    G4VUserPrimaryGeneratorAction * primaryGeneratorAction;
    std::vector<GateVActor *> actors;
    GateEventAction * eventAction;
};

#endif // GateAction_h

/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GateAActor_h
#define GateAActor_h

#include "GateVActor.h"
#include "G4Event.hh"

class GateAActor : public GateVActor {

public:

    GateAActor();

    virtual ~GateAActor();

    virtual void BeginOfEventAction(const G4Event *event);
    virtual void SteppingAction(G4Step * step);

    // FIXME later -> get output !

    int nb_event = 0;
    int nb_step = 0;

};

#endif // GateAActor_h

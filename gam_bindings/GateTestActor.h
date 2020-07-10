/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GateTestActor_h
#define GateTestActor_h

#include "G4VPrimitiveScorer.hh"
#include "G4Event.hh"

class GateTestActor : public G4VPrimitiveScorer {

public:

    GateTestActor();

    virtual ~GateTestActor();

    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    void RegisterSD(G4LogicalVolume * logical_volume);
    void PrintDebug();

    void BeginOfEventAction(G4Event * event);

    int num_step;
    G4MultiFunctionalDetector * mfd;
};

#endif // GateTestActor_h

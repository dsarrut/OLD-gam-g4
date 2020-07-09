/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GateTest2Actor_h
#define GateTest2Actor_h

#include "G4VPrimitiveScorer.hh"
#include "G4Event.hh"

class GateTest2Actor : public G4VPrimitiveScorer {

public:

    GateTest2Actor();

    virtual ~GateTest2Actor();

    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    void RegisterSD(G4LogicalVolume * logical_volume);
    void PrintDebug();

    void BeginOfEventAction(G4Event * event);

    int num_step;
    G4MultiFunctionalDetector * mfd;
};

#endif // GateTest2Actor_h

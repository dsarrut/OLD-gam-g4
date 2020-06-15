/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GateUserSteppingAction_h
#define GateUserSteppingAction_h

#include "G4UserSteppingAction.hh"

class GateUserSteppingAction : public G4UserSteppingAction {

public:

    GateUserSteppingAction();

    virtual ~GateUserSteppingAction();

    virtual void UserSteppingAction(const G4Step *);

};

#endif // GateUserSteppingAction_h

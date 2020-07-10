/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include "GateUserSteppingAction.h"
#include <iostream>

GateUserSteppingAction::GateUserSteppingAction():G4UserSteppingAction() {
    std::cout << "GateUserSteppingAction Constructor " << std::endl;
}

GateUserSteppingAction::~GateUserSteppingAction() {

}

void GateUserSteppingAction::UserSteppingAction(const G4Step *step) {
    //std::cout << "UserSteppingAction " << std::endl;
}
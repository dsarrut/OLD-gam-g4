/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include "GateSimulationStatisticsActor.h"
#include "GateVActor.h"

/*GateSimulationStatisticsActor::GateSimulationStatisticsActor(std::string name) : G4VPrimitiveScorer(name) {
    std::cout << "GateSimulationStatisticsActor construction " << name << std::endl;
}

GateSimulationStatisticsActor::~GateSimulationStatisticsActor() {
    std::cout << "GateSimulationStatisticsActor destructor " << std::endl;
}

void GateSimulationStatisticsActor::BeforeStart() {

}
*/

void GateSimulationStatisticsActor::BeforeStart() {
    step_count = 0;
}


G4bool GateSimulationStatisticsActor::ProcessHits(G4Step *, G4TouchableHistory *) {
    //std::cout << "GateSimulationStatisticsActor ProcessHits "
    //<< step_count << " " << batch_current << std::endl;
    step_count++;
    ProcessBatch(); // not needed FIXME test only
    return true;
}
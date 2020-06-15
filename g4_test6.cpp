

#include "G4RunManager.hh"
#include "G4VModularPhysicsList.hh"
#include "QBBC.hh"

#include <chrono>

using namespace std::chrono;

//-----------------------------------------------------------------------------
int main() {

    std::cout << "hello world" << std::endl;
    // construct the default run manager
    G4RunManager *runManager = new G4RunManager;
    std::cout << "done" << std::endl;

    G4VModularPhysicsList *physicsList = new QBBC;
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);

    // job termination
    // delete runManager;
    return 0;
}
//-----------------------------------------------------------------------------

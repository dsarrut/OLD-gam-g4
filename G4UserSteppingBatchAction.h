

#ifndef G4UserSteppingBatchAction_h
#define G4UserSteppingBatchAction_h 1

#include "G4UserSteppingAction.hh"
#include <iostream>

class G4UserSteppingBatchAction : public G4UserSteppingAction {

public:

    int num_step;
    int batch_size;

    G4UserSteppingBatchAction(int b) : G4UserSteppingAction() {
        std::cout << "constructor G4UserSteppingBatchAction" << std::endl;
        num_step = 0;
        batch_size = b;
    }

    virtual ~G4UserSteppingBatchAction() {}

    virtual void UserSteppingAction(const G4Step *) {
        //std::cout << "step " << std::endl;
        num_step += 1;
        if (num_step >= batch_size) {
            UserSteppingBatchAction();
            num_step = 0;
        }
    }

    virtual void UserSteppingBatchAction() {
        std::cout << "step batch   " << num_step << std::endl;
    }

};

#endif



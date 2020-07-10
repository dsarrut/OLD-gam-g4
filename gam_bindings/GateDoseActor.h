/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#ifndef GateDoseActor_h
#define GateDoseActor_h

#include "GateVActor.h"
#include "G4Event.hh"
//#include "itkImage.h"

class GateDoseActor : public GateVActor {

public:

    GateDoseActor();

    virtual ~GateDoseActor();

    virtual void BeginOfEventAction(const G4Event *event);

    virtual void SteppingAction(G4Step *step);

    void InitSteps();
    void ComputeVolumeDepth(G4TouchableHistory* touchable);

    virtual void SteppingBatchAction();

    void PrintDebug();

    // debug
    int GetNbStep() const { return nb_step; }
    void GetDoseImage2() {}
    //typedef itk::Image<float, 3> ImageType;
    //ImageType::Pointer GetDoseImage() { return mDoseImage; }

    // FIXME later -> get output !

    //ImageType::Pointer mDoseImage;
    int nb_event = 0;
    int nb_step = 0;
    int nb_batch = 0;
    int batch_size;
    int batch_current;
    //std::vector<G4Step*> steps;
    double edep = 0;
    int volDepth;

    std::vector<double> step_edep;
    std::vector<G4ThreeVector> step_position;

};

#endif // GateDoseActor_h


#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4VPrimaryGenerator.hh"
#include "G4Event.hh"

void init_G4VPrimaryGenerator(py::module & m) {
  py::class_<G4VPrimaryGenerator>(m, "G4VPrimaryGenerator")
    
    //.def(py::init())

    .def("GeneratePrimaryVertex",
         /*  [](G4VPrimaryGenerator * p, G4Event* evt) {
           std::cout << "G4VPrimaryGenerator pure virtual" << std::endl;
           return p->GeneratePrimaryVertex(evt);
           })*/
         &G4VPrimaryGenerator::GeneratePrimaryVertex)

    /*
      class G4VPrimaryGenerator
      {
      public: // with description
      // static service method for checking a point is included in the (current) world
      static G4bool CheckVertexInsideWorld(const G4ThreeVector& pos);

      public: // with description
      // Constructor and destrucot of this base class
      G4VPrimaryGenerator();
      virtual ~G4VPrimaryGenerator();

      // Pure virtual method which a concrete class derived from this base class must
      // have a concrete implementation
      virtual void GeneratePrimaryVertex(G4Event* evt) = 0;

      protected:
      G4ThreeVector         particle_position;
      G4double              particle_time;

      public:
      G4ThreeVector GetParticlePosition()
      { return particle_position; }
      G4double GetParticleTime()
      { return particle_time; }
      void SetParticlePosition(G4ThreeVector aPosition)
      { particle_position = aPosition; }
      void SetParticleTime(G4double aTime)
      { particle_time = aTime; }
      };
    */
    ;
}

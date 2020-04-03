
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include <vector>
#include <algorithm>

#include "FTFP_BERT.hh"
#include "FTFP_BERT_ATL.hh"
#include "FTFP_BERT_HP.hh"
#include "FTFP_BERT_TRV.hh"
#include "FTFP_INCLXX.hh"
#include "FTFP_INCLXX_HP.hh"
#include "FTF_BIC.hh"
#include "LBE.hh"

#include "NuBeam.hh"
#include "QBBC.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_BIC.hh"
#include "QGSP_BIC_AllHP.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_FTFP_BERT.hh"
#include "QGSP_INCLXX.hh"
#include "QGSP_INCLXX_HP.hh"
#include "QGS_BIC.hh"
#include "Shielding.hh"

#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"

// macro for adding physics lists
#define ADD_PHYSICS_LIST(m, plname)                     \
  py::class_<plname, G4VModularPhysicsList>(m, #plname) \
  .def(py::init());                                     \
  AddPhysicsList(#plname);

namespace pyPhysicsLists {

  static std::vector<std::string> plList;

  void AddPhysicsList(const G4String& plname) {
    std::cout << "AddPhysicsList " << plname << std::endl;
    plList.push_back(plname);
  }

  void ListPhysicsList() {
    for (unsigned int i=0; i< plList.size(); i++) {
      G4cout << plList[i] << G4endl;
    }
  }

}

using namespace pyPhysicsLists;



class PyQBBC : public QBBC {
public:
  /* Inherit the constructors */
  using QBBC::QBBC;

  /* Trampoline (need one for each virtual function) */
  void SetCuts() override {
    std::cout << "--------------> TREMPOLINE PyQBBC::SetCuts "<< std::endl;
    PYBIND11_OVERLOAD(void,
                      QBBC, 
                      SetCuts, 
                      );
  }
  

  void ConstructParticle() override {
    std::cout << "--------------> TREMPOLINE PyQBBC::ConstructParticle "<< std::endl;
    PYBIND11_OVERLOAD(void, 
                      QBBC,
                      ConstructParticle,
                      );
  }

  void ConstructProcess() override {
    std::cout << "--------------> TREMPOLINE PyQBBC::ConstructProcess "<< std::endl;
    PYBIND11_OVERLOAD(void,
                      QBBC, 
                      ConstructProcess, 
                      );
  }

};





void init_G4PhysicsLists(py::module & m) {

  m.def("ListPhysicsList", ListPhysicsList);

  ADD_PHYSICS_LIST(m, FTFP_BERT);
  /*  ADD_PHYSICS_LIST(m, FTFP_BERT_ATL);
      ADD_PHYSICS_LIST(m, FTFP_BERT_HP);
      ADD_PHYSICS_LIST(m, FTFP_BERT_TRV);
      ADD_PHYSICS_LIST(m, FTFP_INCLXX);
      ADD_PHYSICS_LIST(m, FTFP_INCLXX_HP);
      ADD_PHYSICS_LIST(m, FTF_BIC);
      ADD_PHYSICS_LIST(m, LBE);
      ADD_PHYSICS_LIST(m, NuBeam);
  */

  // ADD_PHYSICS_LIST(m, QBBC);

  py::class_<QBBC, PyQBBC, G4VModularPhysicsList>(m, "QBBC")
    .def(py::init<G4int,G4String>())

    .def("ConstructParticle", &QBBC::ConstructParticle)
    .def("ConstructProcess", &QBBC::ConstructProcess)

    // FIXME cannot compile ???
    //.def("SetCuts", &QBBC::SetCuts)

    /*
      .def("SetCuts", [](QBBC * s) {
      std::cout << "QBBC @@@@@@ SetCuts" << std::endl;
      s->G4VUserPhysicsList::SetCuts();
      })
    */

    ;

  /*ADD_PHYSICS_LIST(m, QGSP_BERT);
    ADD_PHYSICS_LIST(m, QGSP_BERT_HP);
    ADD_PHYSICS_LIST(m, QGSP_BIC);
    ADD_PHYSICS_LIST(m, QGSP_BIC_AllHP);
    ADD_PHYSICS_LIST(m, QGSP_BIC_HP);
    ADD_PHYSICS_LIST(m, QGSP_FTFP_BERT);
    ADD_PHYSICS_LIST(m, QGSP_INCLXX);
    ADD_PHYSICS_LIST(m, QGSP_INCLXX_HP);
    ADD_PHYSICS_LIST(m, QGS_BIC);
    ADD_PHYSICS_LIST(m, Shielding);
  */

  // sort PL vector
  std::sort(plList.begin(), plList.end());
}

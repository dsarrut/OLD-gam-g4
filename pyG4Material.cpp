
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include "G4Material.hh"
#include "G4UnitsTable.hh"

// using namespace boost::python;

// // ====================================================================
// // thin wrappers
// // ====================================================================
// namespace pyG4Material {

// // AddElement
// void (G4Material::*f1_AddElement)(G4Element*, G4int)
//   = &G4Material::AddElement;
// void (G4Material::*f2_AddElement)(G4Element*, G4double)
//   = &G4Material::AddElement;

// // GetMaterial
// G4Material* (*f1_GetMaterial)(const G4String&, G4bool)
//   = &G4Material::GetMaterial;
// G4Material* (*f2_GetMaterial)(G4double, G4double, G4double)
//   = &G4Material::GetMaterial;
// G4Material* (*f3_GetMaterial)(size_t, G4double)
//   = &G4Material::GetMaterial;

// BOOST_PYTHON_FUNCTION_OVERLOADS(f_GetMaterial, G4Material::GetMaterial, 1, 2)

// // raw pointer -> Python list conversion
// list f_GetFractionVector(const G4Material* material)
// {
//   list fracList;
//   const G4double* fracVec= material-> GetFractionVector();
//   G4int nele= material-> GetNumberOfElements();
//   for(G4int i=0; i<nele; i++) {
//     fracList.append(fracVec[i]);
//   }
//   return fracList;
// }

// list f_GetAtomsVector(const G4Material* material)
// {
//   list atomsList;
//   const G4int* atomsVec= material-> GetAtomsVector();
//   G4int nele= material-> GetNumberOfElements();
//   for(G4int i=0; i<nele; i++) {
//     atomsList.append(atomsVec[i]);
//   }
//   return atomsList;
// }

// list f_GetVecNbOfAtomsPerVolume(const G4Material* material)
// {
//   list nbOfAtomsPerVolumeList;
//   const G4double* nbOfAtomsPerVolumeVec= material-> GetVecNbOfAtomsPerVolume();
//   G4int nele= material-> GetNumberOfElements();
//   for(G4int i=0; i<nele; i++) {
//     nbOfAtomsPerVolumeList.append(nbOfAtomsPerVolumeVec[i]);
//   }
//   return nbOfAtomsPerVolumeList;
// }

// list f_GetAtomicNumDensityVector(const G4Material* material)
// {
//   list atomicNumDensityList;
//   const G4double* atomicNumDensityVec= material-> GetAtomicNumDensityVector();
//   G4int nele= material-> GetNumberOfElements();
//   for(G4int i=0; i<nele; i++) {
//     atomicNumDensityList.append(atomicNumDensityVec[i]);
//   }
//   return atomicNumDensityList;
// }

// // copy constructor is private, so ...
// void Print(G4Material& mat)
// {
//   G4cout << mat;
// }

// }

// using namespace pyG4Material;

// // ====================================================================
// // module definition
// // ====================================================================


void init_G4Material(py::module & m) {

  py::class_<G4Material>(m, "G4Material")
    .def(py::init<const G4String&, G4double, G4double, G4double>())
    .def(py::init<const G4String&, G4double, G4int>())

    // private copy constructor
    /*
      .def(py::init<const G4Material&>(),
      [](const G4Material &a) {
      G4Material b(a);
      return a;
      },
      )
    */

    //    .def(py::self = py::self)
    // .def("__mul__", [](const G4Material &a) {
    //                   G4Material b(a);
    //                   return a;
    //                 },
    //   py::is_operator())

    // stream output /// NOT SURE this is the right way to do
    .def("__repr__", [](const G4Material &material) {
                       //std::cout << "ici" << a << std::endl;
                       //return "toto";
                       
                       //std::cout << "before" << std::endl;
                       std::ostringstream flux;
                       flux << material;
                       return flux.str();
                       
                       std::cout << "before" << std::endl;
                       std::ios::fmtflags mode = flux.flags();
                       flux.setf(std::ios::fixed,std::ios::floatfield);
                       G4long prec = flux.precision(3);
                       std::cout << "before" << std::endl;
                       std::cout << "before " << material.GetName() << std::endl;
                         
                       flux
                         << " Material: "         << std::setw(8) <<  material.GetName()
                         << " " << material.GetChemicalFormula() << " "
                         << "  density: "         << std::setw(6) << std::setprecision(3)  
                         << G4BestUnit(material.GetDensity(),"Volumic Mass") 
                         << "  RadL: "            << std::setw(7)  << std::setprecision(3)  
                         << G4BestUnit(material.GetRadlen(),"Length")
                         << "  Nucl.Int.Length: " << std::setw(7)  << std::setprecision(3)  
                         << G4BestUnit(material.GetNuclearInterLength(),"Length") 
                         << "\n" << std::setw(30)   
                         << "  Imean: "           << std::setw(7)  << std::setprecision(3)
                         
                         << G4BestUnit(material.GetIonisation()->GetMeanExcitationEnergy(),"Energy")
                         
                         << "  temperature: " << std::setw(6) << std::setprecision(2)  
                         << (material.GetTemperature())/CLHEP::kelvin << " K"
                         << "  pressure: "    << std::setw(6) << std::setprecision(2)   
                         << (material.GetPressure())/CLHEP::atmosphere << " atm" << "\n";
  
                       std::cout << "before" << std::endl;
                       for (G4int i=0; i<material.GetNumberOfElements(); i++) {
                         flux 
                           << "\n   ---> " << (*(material.GetElementVector()))[i] 
                           << "\n          ElmMassFraction: " 
                           << std::setw(6)<< std::setprecision(2) 
                           << (material.GetFractionVector()[i])/CLHEP::perCent << " %" 
                           << "  ElmAbundance "     << std::setw(6)<< std::setprecision(2) 
                           << 100*(material.GetVecNbOfAtomsPerVolume()[i])
                           /(material.GetTotNbOfAtomsPerVolume())
                           << " % \n";
                       }
                       std::cout << "before" << std::endl;
                       flux.precision(prec);    
                       flux.setf(mode,std::ios::floatfield);

                       /*
                         if(material.IsExtended())
                         { static_cast<const G4ExtendedMaterial*>(material)->Print(flux); }
                       */

                       return flux.str();

  
                       //std::cout << "after" << std::endl;
                       //os << a; // Seg fault ?
                       // std::cout << "after" << std::endl;
                       // std::cout << "--> " << a << std::endl;
                       // std::cout << "la = " << os.str() << std::endl;
                       //return os.str();
                       //                       return "toto";
                     })
    /*
      .def("Print", [](const G4Material & a) {
      G4cout << "ici" << a << std::endl;
      return "toto";
      })
    */
    
    //.def("AddElement",          f1_AddElement)
    //.def("AddElement",          f2_AddElement)
    .def("AddMaterial",         &G4Material::AddMaterial)
    .def("GetName",             &G4Material::GetName)//,
    //         return_value_policy<reference_existing_object>())
    .def("GetChemicalFormula",  &G4Material::GetChemicalFormula)
    //   return_value_policy<reference_existing_object>())
    .def("SetName",             &G4Material::SetName)
    .def("SetChemicalFormula",  &G4Material::SetChemicalFormula)
    .def("GetDensity",          &G4Material::GetDensity)
    .def("GetState",            &G4Material::GetState)
    .def("GetTemperature",      &G4Material::GetTemperature)
    .def("GetPressure",         &G4Material::GetPressure)
    // ---
    .def("GetElementVector",    &G4Material::GetElementVector)//,
    //	 return_internal_reference<>())
    .def("GetElement",          &G4Material::GetElement)//,
    //   return_value_policy<reference_existing_object>())
    .def("GetTotNbOfAtomsPerVolume",  &G4Material::GetTotNbOfAtomsPerVolume)
    .def("GetTotNbOfElectPerVolume",  &G4Material::GetTotNbOfElectPerVolume)
    // .def("GetFractionVector",         f_GetFractionVector)
    // .def("GetAtomsVector",            f_GetAtomsVector)
    // .def("GetVecNbOfAtomsPerVolume",  f_GetVecNbOfAtomsPerVolume)
    // .def("GetAtomicNumDensityVector", f_GetAtomicNumDensityVector)

    .def("GetElectronDensity",        &G4Material::GetElectronDensity)
    .def("GetRadlen",                 &G4Material::GetRadlen)
    .def("GetNuclearInterLength",     &G4Material::GetNuclearInterLength)
    .def("GetIonisation",             &G4Material::GetIonisation)//,
    //	 return_internal_reference<>())
    .def("GetSandiaTable",            &G4Material::GetSandiaTable)//,
    //	 return_internal_reference<>())

    .def("GetZ",                  &G4Material::GetZ)
    .def("GetA",                  &G4Material::GetA)
    .def("SetMaterialPropertiesTable", &G4Material::SetMaterialPropertiesTable)
    .def("GetMaterialPropertiesTable", &G4Material::GetMaterialPropertiesTable)
    //	 return_internal_reference<>())
    .def("GetMaterialTable",      &G4Material::GetMaterialTable)
    //	 return_value_policy<reference_existing_object>())

    //    .staticmethod("GetMaterialTable")
    .def_property_readonly_static("GetMaterialTable",
                                  [](py::object) { return G4Material::GetMaterialTable(); } )

    .def("GetNumberOfMaterials",  &G4Material::GetNumberOfMaterials)

    //.staticmethod("GetNumberOfMaterials")
    .def_property_readonly_static("GetNumberOfMaterials",
                                  [](py::object) { return G4Material::GetNumberOfMaterials(); } )
    
    .def("GetIndex",              &G4Material::GetIndex)
    // .def("GetMaterial",           f1_GetMaterial, f_GetMaterial()
    //      [return_value_policy<reference_existing_object>()])
    // .def("GetMaterial",           f2_GetMaterial,
    //      return_value_policy<reference_existing_object>())
    // .def("GetMaterial",           f3_GetMaterial,
    //      return_value_policy<reference_existing_object>())
    
    //.staticmethod("GetMaterial")
    .def_property_readonly_static("GetMaterial",
                                  [](py::object, const G4String &name, G4bool warning=true)
                                  { return G4Material::GetMaterial(name, warning); } )

    // ---
    //.def(self_ns::str(self))
    //    .def("Print", Print)
    ;

  // ---
  py::enum_<G4State>(m, "G4State")
    .value("kStateUndefined", kStateUndefined)
    .value("kStateSolid",     kStateSolid)
    .value("kStateLiquid",    kStateLiquid)
    .value("kStateGas",       kStateGas)
    .export_values()
    ;
  
}

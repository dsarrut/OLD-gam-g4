

Some hints boost-python vs pybind11


- bases is not any longer required. Only its template argument must
  remain, in the same position of what was there before.

- The noncopyable template argument should not be provided (everything
  is noncopyable unless specified) - if something is to be made
  copyable, a copy constructor should be provided to python
  
  
  
- return policies
  https://pybind11.readthedocs.io/en/stable/advanced/functions.html
 
  return_value_policy<reference_existing_object>
  -->
  py::return_value_policy::reference 
  
  return_internal_reference<>()
  -->
  py::return_value_policy::reference_internal
      
  return_value_policy<return_by_value>()
  --> 
  py::return_value_policy::copy	 ??????
  

- add_property
  -->
  .def_readwrite


- debug
  python -q -X faulthandler

- .staticmethod("XXX")
  --> normal .def ??


- overloading methods
  --> 
  (for example)
   py::overload_cast<G4VUserPrimaryGeneratorAction*>(&G4RunManager::SetUserAction))


- pure virtual need a trampoline class
  https://pybind11.readthedocs.io/en/stable/advanced/classes.html


- singleton
  // No destructor for this singleton class
  py::class_<G4RunManager, std::unique_ptr<G4RunManager, py::nodelete>>(m, "G4RunManager")




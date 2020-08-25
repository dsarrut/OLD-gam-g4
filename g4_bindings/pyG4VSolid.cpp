/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General  Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */
#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "G4Version.hh"
#include "G4VSolid.hh"

void init_G4VSolid(py::module &m) {
    py::class_<G4VSolid>(m, "G4VSolid")

        .def("GetName", &G4VSolid::GetName)
        .def("SetName", &G4VSolid::SetName)
        .def("DumpInfo", &G4VSolid::DumpInfo)

        .def("GetCubicVolume", &G4VSolid::GetCubicVolume)
        .def("GetSurfaceArea", &G4VSolid::GetSurfaceArea)
        .def("GetPointOnSurface", &G4VSolid::GetPointOnSurface)

        // operators
        //.def(self == self)
        ;
}


This **experiment** is a **work in progress**. Even the name (gam) is temporary.

- The folder `gam-g4/g4_bindings` contains C++ source code that maps some Geant4 classes into a Python module. 
- The folder `gam-g4/gam_lib` contains additional C++ classes that extends Geant4 functionalities (also mapped to Python).

At the end of the compilation process a single Python module is available, named `gam_g4` and is ready to use from the Python side via the `gam` python module: https://github.com/dsarrut/gam

# How to install ?

Note1: the following installation is for developers. For user, a simple `pip install gam` will be sufficient. 

Note2: the process will be simplified.  

## 1) First, create a Python environment and activate it.

If you use conda:

```
conda create --name gam_env python=3.8
conda activate gam_env
```

See: https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html

If you dont use conda: 

```
python3 -m venv gam_env 
source gam_env/bin/activate
```

See: https://docs.python.org/3/tutorial/venv.html

## 2) Install required software


Install [Geant4](https://geant4.web.cern.ch) , with Multithreading=ON, and QT visualization. QT should work when install in the python environment, for example with `conda install qt`.

Install [ITK](https://itk.org).

## 3) Clone the repository (with submodules!)

`git clone --recurse-submodules  https://github.com/dsarrut/gam_g4`

## 4) Compile the c++ part

Go in the folder and:

`pip install -e .`


It will create some files, ready to be compiled, but will fail, it is "normal" (well, it is not really normal, but the current way. Of course it will be improved).

Then, go in the created folder and `cmake` :

```
cd build/temp.linux-x86_64-3.6

cmake -DGeant4_DIR=~/src/geant4/build-geant4.10.07-debug-mt -DPYTHON_EXECUTABLE=~/src/py/miniconda3/envs/gam_env/bin/python -DPYTHON_INCLUDE_DIR=~/src/py/miniconda3/envs/gam_env/include -DPYTHON_LIBRARY=~/src/py/miniconda3/envs/gam/lib/libpython3.so -DITK_DIR=~/src/itk/build-v5.2.0 -DROOT_DIR=~/src/geant4/build-root -DCMAKE_CXX_FLAGS="-Wno-pedantic"  . 
```


Of course, replace all folders by yours.

Then compile:

`make -j 12`

## 5) On linux

Sometimes on Linux machine, you will need to add the following path to find dynamic library :

``` 
export LD_PRELOAD=~/src/geant4/build-geant4.10.07-debug-mt/BuildProducts/lib64/libG4processes.so:${LD_PRELOAD}
```

We dont know yet why this is required and are currently working to improve this.

## 6) Test

Start python: `python` and type `import gam_g4`. The first time, Geant4 data will be downloaded. You can now access some G4 functions in Python.

For example:

```
a = gam_g4.G4ThreeVector(0)
print(a)
```

## 7) Start doing simulation 

See https://github.com/OpenGamGate/gam and https://github.com/OpenGamGate/gam_tests




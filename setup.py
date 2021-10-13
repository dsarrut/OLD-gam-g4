import os
import re
import sys
import platform
import subprocess
import glob

from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext
from distutils.version import LooseVersion


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):

    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            cmake_version = LooseVersion(re.search(r'version\s*([\d.]+)', out.decode()).group(1))
            if cmake_version < '3.1.0':
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        # required for auto-detection of auxiliary "native" libs

        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable,
                      ]

        # cfg = 'Debug' if self.debug else 'Release'
        cfg = 'Release'
        build_args = ['--config', cfg]

        # Pile all .so in one place and use $ORIGIN as RPATH
        cmake_args += ["-DCMAKE_BUILD_WITH_INSTALL_RPATH=TRUE"]
        cmake_args += ["-DCMAKE_INSTALL_RPATH_USE_LINK_PATH=TRUE"]
        cmake_args += ["-DCMAKE_INSTALL_RPATH={}".format("$ORIGIN")]

        # cmake_args += ['-DGeant4_DIR=~/src/geant4/geant4.10.7-mt-build']
        # cmake_args += ['-DPYTHON_EXECUTABLE=/Users/dsarrut/src/py/miniconda3/envs/gam/bin/python']
        # cmake_args += ['-DPYTHON_INCLUDE_DIR=/Users/dsarrut/src/py/miniconda3/envs/gam//include']
        # cmake_args += ['-DPYTHON_LIBRARY=/Users/dsarrut/src/py/miniconda3/envs/gam/lib/libpython3.8.dylib']
        # cmake_args += ['-DCMAKE_CXX_FLAGS="-Wno-self-assign -Wno-extra-semi"']
        # cmake_args += ['-DITK_DIR=~/src/itk/build-v5.1.2']

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(cfg.upper(), extdir)]
            # cmake_args += ['-G "CodeBlocks - NMake Makefiles"']
            if sys.maxsize > 2 ** 32:
                cmake_args += ['-A', 'x64']
            build_args += ['--', '/m']
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j4']

        env = os.environ.copy()

        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(env.get('CXXFLAGS', ''),
                                                              self.distribution.get_version())

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env)

        # subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)

        subprocess.check_call(['cmake',
                               '--build', '.',
                               '--target', ext.name
                               ] + build_args,
                              cwd=self.build_temp)

if platform.system() == "Darwin":
  package_data = {'gam_g4': ['plugins/platforms/*.dylib'] + ['plugins/imageformats/*.dylib'] + ['plugins/miniconda/libQt5Svg.5.9.7.dylib']}
  #package_data = {}
else:
  package_data = {'gam_g4': ['plugins/*/*.so'] }

setup(

    # FIXME --> DO NOT USE YET

    name='gam_g4',
    version='0.1.2',
    author='Opengate Collaboration',
    author_email='david.sarrut@creatis.insa-lyon.fr',
    description='A test project using pybind11 and CMake',
    long_description='',
    ext_package='gam_g4',
    ext_modules=[CMakeExtension('gam_g4')],
    cmdclass=dict(build_ext=CMakeBuild),
    packages=find_packages(),
    package_data=package_data,
    zip_safe=False,
    python_requires='>=3.5',
    install_requires=[
        'wget',
    ],
)

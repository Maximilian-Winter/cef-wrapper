import subprocess
from pathlib import Path, PurePath

from Cython.Build import cythonize
from setuptools import setup, Extension, PackageFinder
from setuptools.command.build_ext import build_ext as build_ext


CPPFLAGS = ['/std:c++17' ]
extensions = [
    Extension(name="PyCef.src", sources=["./PyCef/src/pycef.pyx"],
              include_dirs=["../../"],
              libraries=["user32", "libcef_dll_wrapper", "libcef", "cefwrapper"],
              library_dirs=["./lib/"],
              extra_compile_args=CPPFLAGS)

]
setup(
    name='PyCef',
    description="A python wrapper for the chromium embed framework.",
    long_description="This is a python wrapper for the Chromium Embedded Framework.\n"
                     "It is still in a very early stage. But already has basic functionality"
                     " for loading an url and add javascript bindings in python",
    cmdclass={'build_ext': build_ext},
    ext_modules=cythonize(extensions),
    packages=['PyCef'],
    package_data={'PyCef': ['./bin/*.exe', './bin/*.dll', './bin/*.dat', './bin/*.pak', './bin/*.bin', './bin/*.json',
                            './cefsubprocess/*.exe', './cefsubprocess/*.dll', './cefsubprocess/*.dat',
                            './cefsubprocess/*.pak', './cefsubprocess/*.bin', './cefsubprocess/*.json',
                            './bin/locales/*.pak', './cefsubprocess/locales/*.pak']},
    zip_safe=False,
    version="0.0.1"
)

[![License:MIT](https://img.shields.io/badge/License-MIT-blue?style=plastic)](LICENSE)
[![C++ CI build](../../actions/workflows/build.yml/badge.svg)](../../actions/workflows/build.yml)

### kernel_cpp

small library for retrieving kernel's command-line

## <sub>Depends</sub>

 - [common_cpp](https://github.com/oskarirauta/common_cpp)
 - [throws_cpp](https://github.com/oskarirauta/throws_cpp)

## <sub>Importing</sub>

 - clone listed submodules to directories omitting _cpp, for example, common_cpp to directory common
 - include submodule's objs as uppercased submodule's name (omitting _cpp) _OBJS, for example, $(COMMON_OBJS)
 - include submodule's Makefile.incs in your Makefile, for example common/Makefile.inc
 - link with submodule object, for example $(COMMON_OBJS)

All paths are modifiable, check Makefiles for examples. To be able to build provided example code, remember
to clone this repository with --recursive-submodules enabled, unless you used release tarball with merged
submodules.

## <sub>Example</sub>

Sample code reads, shows and parses your kernel's command line.

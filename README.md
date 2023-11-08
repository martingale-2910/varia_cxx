varia_cxx
=========

A simple repository for just-for-fun C++ coding.

A collection of various different bits and pieces exploring topics such as:
- stochastic simulations
- numerical methods 
- variadic programming
- concurrent programming

The code is organized into standalone projects in the `/src` folder, with each project `proj` in a separate `/src/proj` subfolder.

## Requirements
A `clang` or `g++` compiler that supports `std=c++17`.

## Usage
To build the project `proj` run the following command from the repo's main folder:
```bash
make PROJ=proj
```
Without specifying the `PROJ` value the default project `hello_world` will be built.

You can choose whether to build the project in **debug** mode (`make debug`) or in **release** mode (`make release`)
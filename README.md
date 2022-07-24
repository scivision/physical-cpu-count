# Physical CPU count

This code was adapted from Kitware KWSYS.
More sophisticated approaches to Physical CPU count are available in projects including:

* [HWLOC](https://github.com/open-mpi/hwloc)
* Google [cpu_features](https://github.com/google/cpu_features)

For projects that use MPI on a wide variety of computers running MacOS, Linux, and Windows we have found this single-file approach adequate to determine physical CPU count.
For MacOS with Apple Silicon, we extract the count of the "fast" CPU cores.

Examples are given in [app/](./app) for C, C++ and Fortran calling the only public-facing function:

```c
unsigned int cpu_count()
```

Build the examples and test:

```sh
cmake -B build
cmake --build build
ctest --test-dir build
```

Works with every compiler we tried including: GCC, Clang, Intel oneAPI, Visual Studio.

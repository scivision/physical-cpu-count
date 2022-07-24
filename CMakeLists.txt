cmake_minimum_required(VERSION 3.14...3.24)

project(CPUcount LANGUAGES C CXX)

enable_testing()

option(fortran "enable Fortran support" true)

if(fortran)
  enable_language(Fortran)
endif()

# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()

add_library(cpu_count OBJECT cpu_count.cpp)
target_include_directories(cpu_count PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(cpu_count PRIVATE cxx_std_11)

if(fortran)
  add_executable(cpu_f app/main.f90 $<TARGET_OBJECTS:cpu_count>)
  add_test(NAME CPUfortran COMMAND cpu_f)
endif()

add_executable(cpu_c app/main.c $<TARGET_OBJECTS:cpu_count>)
target_include_directories(cpu_c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME CPUc COMMAND cpu_c)

add_executable(cpu_cpp app/main.cpp $<TARGET_OBJECTS:cpu_count>)
target_include_directories(cpu_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME CPUcpp COMMAND cpu_cpp)

get_property(tests DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY TESTS)

set_property(TEST ${tests} PROPERTY TIMEOUT 5)

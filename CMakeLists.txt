cmake_minimum_required(VERSION 3.15...3.29)

project(CPUcount LANGUAGES C CXX)

enable_testing()

option(fortran "enable Fortran support" true)
option(cppcheck "enable cppcheck")

if(fortran)
  enable_language(Fortran)
endif()

set(CMAKE_CXX_STANDARD 11)

# --- add warnings

if(CMAKE_C_COMPILER_ID MATCHES "Clang|Intel|GNU")
  add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-Wno-unused-function>")
endif()

if(PROJECT_IS_TOP_LEVEL)

if(CMAKE_C_COMPILER_ID MATCHES "Clang|Intel|GNU")
  add_compile_options("$<$<COMPILE_LANGUAGE:C,CXX>:-Wall;-Wextra>")
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
  add_compile_options("$<$<COMPILE_LANGUAGE:C,CXX>:/W4>")
endif()

endif()

if(MINGW)
  add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wno-cast-function-type>)
endif()

# CPPcheck
if(cppcheck)
  find_program(cppcheck_exe NAMES cppcheck REQUIRED)
  set(cppcheck_opts --enable=all --inline-suppr --quiet --suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck.supp)
  set(CMAKE_C_CPPCHECK ${cppcheck_exe} --std=c++${CMAKE_CXX_STANDARD} ${cppcheck_opts})
  set(CMAKE_CXX_CPPCHECK ${cppcheck_exe} --std=c++${CMAKE_CXX_STANDARD} ${cppcheck_opts})
endif()

add_library(cpu_count OBJECT src/cpu_count.cpp)
target_include_directories(cpu_count PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(cpu_count PRIVATE $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)

if(fortran)
  add_executable(cpu_f app/main.f90)
  target_link_libraries(cpu_f PRIVATE cpu_count)
  add_test(NAME CPUfortran COMMAND cpu_f)
endif()

add_executable(cpu_c app/main.c)
target_link_libraries(cpu_c PRIVATE cpu_count)
add_test(NAME CPUc COMMAND cpu_c)

add_executable(cpu_cpp app/main.cpp)
target_link_libraries(cpu_cpp PRIVATE cpu_count)
add_test(NAME CPUcpp COMMAND cpu_cpp)

file(GENERATE OUTPUT .gitignore CONTENT "*")

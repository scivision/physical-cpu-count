cmake_minimum_required(VERSION 3.15...3.26)

project(CPUcount LANGUAGES C CXX)

enable_testing()

option(fortran "enable Fortran support" true)

if(fortran)
  enable_language(Fortran)
endif()

# --- add warnings

if(CMAKE_C_COMPILER_ID MATCHES "Clang|Intel|GNU")
  add_compile_options("$<$<COMPILE_LANGUAGE:C,CXX>:-Wall;-Wextra>")
elseif(CMAKE_C_COMPILER_ID MATCHES "MSVC")
  add_compile_options("$<$<COMPILE_LANGUAGE:C,CXX>:/W4>")
endif()
if(MINGW)
  add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wno-cast-function-type>)
endif()

add_library(cpu_count OBJECT src/cpu_count.cpp)
target_include_directories(cpu_count PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_features(cpu_count PRIVATE cxx_std_11)
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

// Demo program for cpu_count

#include <iostream>

#include "cpu_count.h"

int main(){

  std::cout << "Physical CPU count: " << cpu_count() << std::endl;

  return EXIT_SUCCESS;

}

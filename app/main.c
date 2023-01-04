// Demo program for cpu_count

#include <stdio.h>
#include <stdlib.h>

#include "cpu_count.h"

int main(){

  printf("Physical CPU count: %d\n", cpu_count());

  return EXIT_SUCCESS;
}

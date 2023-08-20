// Demo program for cpu_count

#include <stdio.h>
#include <stdlib.h>

#include "cpu_count.h"

int main(void){

  printf("Physical CPU count: %u\n", cpu_count());

  return EXIT_SUCCESS;
}

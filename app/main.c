// Demo program for cpu_count

#include <stdio.h>

#include "cpu_count.h"

int main(){

  printf("Physical CPU count: %d\n", cpu_count());

  return 0;

}

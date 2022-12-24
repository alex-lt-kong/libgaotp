#include <stdio.h>
#include <stdlib.h>
#include "../src/libgaotp.c"

int main() {

  char SECRET[] = "HYOFYAHVEIHZWGXEBEBRIURVLQEIYPEQJFUKQRYREKJOKJVO";
  getOTOP(SECRET);
  return 0;
}

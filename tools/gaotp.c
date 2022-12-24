#include <stdio.h>
#include <stdlib.h>
#include "../src/libgaotp.c"

int main() {

  char SECRET[] = "HYOFYAHVEIHZWGXEBEBRIURVLQEIYPEQJFUKQRYREKJOKJVO";
  size_t output_len = 0;
  uint8_t* outputBytes = decode_base32_string_to_bytes(SECRET, &output_len);
  if (outputBytes == NULL) {
    fprintf(stderr, "error\n");
    return 1;
  }
  for (size_t i = 0; i < output_len; ++i) {
    printf("%x", outputBytes[i]);
  }
  printf("\n");
  getOTOP(outputBytes, output_len);
  free(outputBytes);
  return 0;
}

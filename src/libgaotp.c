#include <stdio.h>
#include <time.h>
#include <mycrypto/hmac.h>
#include <mycrypto/sha1.h>
#include <mycrypto/base32.h>

void getOTOP(unsigned char* keyBytes, size_t len) {

  time_t utime = (floor((unsigned long)time(NULL) / 30));;
  // Little-endian to big-endian (so this function only works on little-endian machine)
  utime = ((utime & 0xffffffffffffffff) << 32) | ((utime & 0xffffffff00000000) >> 32);
  utime = ((utime & 0x0000ffff0000ffff) << 16) | ((utime & 0xffff0000ffff0000) >> 16);
  utime = ((utime & 0x00ff00ff00ff00ff) <<  8) | ((utime & 0xff00ff00ff00ff00) >>  8);
  uint8_t hash[SHA1_HASH_SIZE];
  printf("hmac_sha1() calling\n");
  hmac_sha1(keyBytes, len, (uint8_t*)&utime, sizeof(utime), hash);
  printf("hmac_sha1() called\n");
  //Get offset position
  uint64_t offset = hash[19] & 0x0f;
  uint32_t truncatedHash;
  //Truncate hash
  truncatedHash =
    (hash[offset] & 0x7f) << 24 |
    (hash[offset + 1] & 0xff) << 16 |
    (hash[offset + 2] & 0xff) << 8 |
    (hash[offset + 3] & 0xff);

  printf("%u\n", truncatedHash % 1000000); //Mod truncated hash to get the 6 digit OTP
}

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <arpa/inet.h>
#include <mycrypto/hmac.h>
#include <mycrypto/sha1.h>
#include <mycrypto/base32.h>

void getOTOP(const char* secret_b32) {
  size_t secret_len = 0;
  uint8_t* secret_bytes = decode_base32_string_to_bytes(secret_b32, &secret_len);
  time_t utime = (floor((unsigned long)time(NULL) / 30));;
    if (htonl(47) != 47) {
		// Little endian per
		// https://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program

		// This is just a fancy to switch endianness from little-endian to big-endian
    utime = ((utime & 0xffffffffffffffff) << 32) | ((utime & 0xffffffff00000000) >> 32);
    utime = ((utime & 0x0000ffff0000ffff) << 16) | ((utime & 0xffff0000ffff0000) >> 16);
    utime = ((utime & 0x00ff00ff00ff00ff) <<  8) | ((utime & 0xff00ff00ff00ff00) >>  8);
  };  
  uint8_t hash[SHA1_HASH_SIZE];

  hmac_sha1(secret_bytes, secret_len, (uint8_t*)&utime, sizeof(utime), hash);

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

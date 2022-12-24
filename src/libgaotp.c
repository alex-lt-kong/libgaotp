#include <stdio.h>
#include <time.h>
#include <math.h>
#include <arpa/inet.h>
#include <mycrypto/hmac.h>
#include <mycrypto/sha1.h>
#include <mycrypto/base32.h>

int32_t get_otp(const char* secret_b32, int64_t unix_time) {
    int64_t secret_len = 0;
    uint8_t* secret_bytes = decode_base32_string_to_bytes(secret_b32, &secret_len);
    if (secret_len < 0) {
        return secret_len;
    }
    if (unix_time < 0) {
        unix_time = (unsigned long)time(NULL);
    }
    unix_time = floor(unix_time / 30);
    if (htonl(47) != 47) {
        // htonl(47) != 47 means running on a little-endian system according to:
        // https://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program

        // switch endianness of int64 from little-endian to big-endian
        unix_time = ((unix_time & 0xffffffffffffffff) << 32) | ((unix_time & 0xffffffff00000000) >> 32);
        unix_time = ((unix_time & 0x0000ffff0000ffff) << 16) | ((unix_time & 0xffff0000ffff0000) >> 16);
        unix_time = ((unix_time & 0x00ff00ff00ff00ff) <<  8) | ((unix_time & 0xff00ff00ff00ff00) >>  8);
    };  
    uint8_t hash[SHA1_HASH_SIZE];

    hmac_sha1(secret_bytes, secret_len, (uint8_t*)&unix_time, sizeof(unix_time), hash);

    //Get offset position
    uint64_t offset = hash[19] & 0x0f;
    int32_t truncatedHash;
    //Truncate hash
    truncatedHash =
    (hash[offset] & 0x7f) << 24 |
    (hash[offset + 1] & 0xff) << 16 |
    (hash[offset + 2] & 0xff) << 8 |
    (hash[offset + 3] & 0xff);

    return truncatedHash % 1000000;
    //Mod truncated hash to get the 6 digit OTP
}

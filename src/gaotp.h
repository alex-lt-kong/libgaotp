#include <stdlib.h>
#include <stdint.h>

/**
 * @brief generate the Google Authenticator-compatible one-time passqword by a base32-encoded secret key and
 * unix timestamp
 * @param secret_b32 a null-terminated base32-encoded secret key
 * @param unix_time unix timestamp of the OTP, pass a negative value to use the computer's local time.
 * @returns an integer representing the OTP. On error:
 * -1 if secret_key is not a valid base32 string;
 * -2 if malloc() failed
*/
int32_t get_otp(const char* secret_b32, int64_t unix_time);

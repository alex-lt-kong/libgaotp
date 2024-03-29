#include <assert.h>
#include <node_api.h>
#include <stdio.h>
#include <gaotp.h>
#include <string.h>

// Refer to here for more examples: https://github.com/nodejs/node-addon-examples


static napi_value get_otp_napi(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 2;
  napi_value args[2];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  if (argc < 2) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments");
    return NULL;
  }

  napi_valuetype valuetype0;
  status = napi_typeof(env, args[0], &valuetype0);
  assert(status == napi_ok);

  napi_valuetype valuetype1;
  status = napi_typeof(env, args[1], &valuetype1);
  assert(status == napi_ok);

  if (valuetype0 != napi_string || valuetype1 != napi_number) {
    napi_throw_type_error(env, NULL, "Wrong arguments");
    return NULL;
  }

  const size_t buf_size = 2048 + 1;
  size_t result;
  char secret_b32[buf_size];
  status = napi_get_value_string_latin1(env, args[0], secret_b32, buf_size, &result);
  if (result >= buf_size - 1) {
    fprintf(stderr, "WARNING: the base32-encoded secret will be truncated to %lu characters\n", buf_size - 1);
  }
  assert(status == napi_ok);

  int64_t uinx_time;
  status = napi_get_value_int64(env, args[1], &uinx_time);
  assert(status == napi_ok);

  int otp = get_otp(secret_b32, uinx_time);

  napi_value otp_napi;
  status = napi_create_double(env, otp, &otp_napi);
  assert(status == napi_ok);

  return otp_napi;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor get_otp_descriptor = DECLARE_NAPI_METHOD("get_otp", get_otp_napi);
  status = napi_define_properties(env, exports, 1, &get_otp_descriptor);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
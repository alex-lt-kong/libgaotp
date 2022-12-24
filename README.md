# libgaotp

A two-factor authentication library that is compatible with the
[Google Authenticator](https://en.wikipedia.org/wiki/Google_Authenticator) [Android](https://play.google.com/store/apps/details?id=com.google.android.apps.authenticator2&hl=en&gl=US&pli=1)/
[iOS](https://apps.apple.com/us/app/google-authenticator/id388497605) Apps (or to be specific, the open
standards developed by the [Initiative for Open Authentication (OATH)](https://openauthentication.org/)
(which is unrelated to OAuth))
  * Google Authenticator is [open-sourced](https://github.com/google/google-authenticator), but it does not provide
  an API for thrid-party to use (as Google Authenticator is a mobile app).
  * Google also open sourced another repository called [google-authenticator-libpam](https://github.com/google/google-authenticator-libpam), but
  it seems still a bit less straightforward for some simple application.
  * Ideally, there should be an API as simple as this: a function caller passes a SECRET_KEY to the function and
  it returns the six-digit One-time password (OTP). This library does exactly this and more--it provides bindings for
  Python and Node.js, apart from shared objects to C/C++.

This library is developed and tested only on little-endian systems. It should work on big-endian systems, but it is
not tested.

## Dependencies

* [libmycrypto](https://github.com/alex-lt-kong/libmycrypto): a simple cryptography library.
* `cmake`: `apt install cmake` 

## Build and install


### C/C++ shared object
```
mkdir -p ./build
cd build
cmake ..
make
```
```
sudo make install
```

### Node.js binding

* `npm install -g node-gyp`

```
node-gyp configure
node-gyp build
```
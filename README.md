# libgaotp

A two-factor authentication library that is compatible with the
[Google Authenticator](https://en.wikipedia.org/wiki/Google_Authenticator) 
[Android](https://play.google.com/store/apps/details?id=com.google.android.apps.authenticator2&hl=en&gl=US&pli=1)/
[iOS](https://apps.apple.com/us/app/google-authenticator/id388497605) Apps (or to be specific, the open
standards developed by the [Initiative for Open Authentication (OATH)](https://openauthentication.org/)
(which is unrelated to OAuth) based on [RFC6238](https://www.ietf.org/rfc/rfc6238.txt)
  * Google Authenticator is [open-sourced](https://github.com/google/google-authenticator), but it does not provide
  an API for thrid-party to use (as Google Authenticator is a mobile app).
  * Google also open sourced another repository called
  [google-authenticator-libpam](https://github.com/google/google-authenticator-libpam), but
  it seems still a bit less straightforward for some simple application.
  * Ideally, there should be an API as simple as this: a function caller passes a SECRET_KEY to the function and
  it returns the six-digit One-time password (OTP). This library does exactly this and more--it provides bindings for
  Python and Node.js, apart from shared objects to C/C++.

This library is developed for little-endian architecture platforms. 
It does not work on big-endian architecture platforms.

## Dependencies

* [libmycrypto](https://github.com/alex-lt-kong/libmycrypto): a simple cryptography library.
* `cmake`: `apt install cmake` 

## Build and install


### C/C++ shared object

* Build
```
mkdir -p ./build
cd build
cmake ..
make
```
* Install
```
sudo make install
```

### Node.js binding

* Make sure `node` and `npm` are installed.
* Make sure the C/C++ shared object (previous section) is `make install`ed.
* `node-gyp`, used to build Node.js' native addon: `npm install -g node-gyp`.
  * Depending on the exact installation method, `node-gyp` may be directly invokded or via
  `./node_modules/node-gyp/bin/node-gyp.js`

* Build
```
cd ./bindings/node/
node-gyp configure
node-gyp build
```

* Test
```
node gaotp.js
```

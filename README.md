# libgaotp

It is nice to add two-factor authentication to some simple web services without relying on third-party online services
to provide SMS/email functionalities. Using Google Authenticator could be a straightforward way--providing a secret
key to Google Authenticator [[Android](https://play.google.com/store/apps/details?id=com.google.android.apps.authenticator2)
/[iOS](https://apps.apple.com/us/app/google-authenticator/id388497605)] and then we get time-based 2FA.

Unfortunately, while Google Authenticator is [open-sourced](https://github.com/google/google-authenticator), 
it is only a mobile application and it does not provide an API for server-side OTP verification. Google also open
sourced another repository called [google-authenticator-libpam](https://github.com/google/google-authenticator-libpam),
but it seems still a bit too heavy for prototyping/toy projects.

Ideally, a library should provide one single API as simple as this: caller passes a SECRET_KEY to the function and
the function returns the six-digit One-time password (OTP) consistent with Google Authenticator, allowing the server
program to verify the OTP passed by users.

This library does exactly this, for C/C++, Node.js and Python.

Note that this library is developed for little-endian architecture platforms. It does not work on big-endian
architecture platforms. (Fortunately, x86 and most ARM architectures are little-endian)

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

### Python binding

* As Python provides native C interoperability. As long as the *C/C++ share object* is `make`ed, we should
be able to simply run the Python script.

```
cd ./bindings/python/
python3 gaotp.py
```

### Node.js binding

* Node.js's binding is a bit more complicated as we need to compile a translation layer into Node.js native addon.
* Make sure `node` and `npm` are installed.
* Make sure the *C/C++ shared object* is `make install`ed.
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

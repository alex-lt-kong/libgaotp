# libgatotp

A two-factor authentication library that is compatible with the
[Google Authenticator](https://en.wikipedia.org/wiki/Google_Authenticator) [Android](https://play.google.com/store/apps/details?id=com.google.android.apps.authenticator2&hl=en&gl=US&pli=1)/
[iOS](https://apps.apple.com/us/app/google-authenticator/id388497605) Apps
  * Google Authenticator is [open-sourced](https://github.com/google/google-authenticator), but it does not provide
  an API for thrid-party to use (as Google Authenticator is a mobile app).
  * Google also open sourced another repository called [google-authenticator-libpam](https://github.com/google/google-authenticator-libpam), but
  it seems still a bit less straightforward for some simple application.
  * Ideally, there should be an API as simple as this: a function caller passes a SECRET_KEY to the function and
  it returns the six-digit One-time password (OTP). This library does exactly this.

# Using Visual Studio Code

* Install Microsofts Arduino Extension
* Check your `c_cpp_properties.json`:
    * Make sure your `includePath` contains the path where the Arduino IDE
      installs libraries
    * Make `defines` include `"USBCON"`
* Make a test compile with `[STRG]` + `[ALT]` + `[R]`
* Check if there are any errors in your source files. If so, double check your
  `includePath` settings.

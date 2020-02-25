# php-periphery-serial [![Build Status](https://travis-ci.org/1nv1/php-periphery.svg?branch=master)](https://travis-ci.org/vsergeev/c-periphery) [![GitHub release](https://img.shields.io/github/release/1nv1/php-periphery.svg?maxAge=7200)](https://img.shields.io/github/release/1nv1/php-periphery-serial/all.svg) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/vsergeev/c-periphery/blob/master/LICENSE)

A php extension for peripheral I/O Serial in GNU/Linux.

## Introduction

The goal of this project is build a wrapper (serial I/O) of [c-periphery](https://github.com/vsergeev/c-periphery)
library.

## Warning

This project really has two goal, the first is create a wrapper and the second
is learn about php extensions. It's my first project around this.

Right now I uploaded to sourceforge two compilations of the extension. One is
for x86_64 target system and the other was build on a x86.
The last one was tested with real electronics hardware without problems.

# Next steps

- [x] Public attributes
- [x] Testing arguments
- [ ] Test again over real hardware (x86/x86_64)
- [x] Documentation of class
- [ ] I will keep uploading compiled versions
- [ ] Errors support

# Documentation

You can access to documentation to class in this [link](docs/class_serial.md).

# Download

You can download the compiled library in the [sourceforge](https://sourceforge.net/projects/php-periphery-serial/) page.

# Build

You need apply the following steps:

```
# phpize
# ./configure --enable-periphery_serial
# make
# make install
```

# Example

This is a simple example:

```php

<?php

// Class for use periphery-serial
require_once dirname(__FILE__).$relative_path_to."/class/Periphery.php";

// Create an instance
$pb = new Periphery\Serial();

// Yo can see the version of c-periphery embedded
echo "Version: ".$pb->version().PHP_EOL;

// Now, open the serial port: path to device and baudrate
$res = $pb->open("/dev/ttyUSB0", 38400) ? 'yes' : 'no';
if ($res == 'no') {
  echo "Error at open!".PHP_EOL;
  die();
}
echo "Open: yes".PHP_EOL;

echo "Flush...".PHP_EOL;
$pb->flush();

// Take the "string" to send and convert it in array
$send = str_split("RP");
echo "Write: ".$pb->write($send, 2).PHP_EOL;
echo "Read: ";

// Do you need wait 30 bytes response with a 2 senconds of timeout?
$res = $pb->read(30, 2000);
if (!empty($res)) { var_dump($res); }
else { echo PHP_EOL; }

// You expects 30 bytes with a 2 senconds of timeout
echo "Close: ".($pb->close() ? 'yes' : 'no').PHP_EOL;

```

# License

php-periphery-serial is MIT licensed. See the included [LICENSE](LICENSE) file.

# php-periphery-serial [![Build Status](https://travis-ci.org/1nv1/php-periphery.svg?branch=master)](https://travis-ci.org/vsergeev/c-periphery) [![GitHub release](https://img.shields.io/github/release/1nv1/php-periphery.svg?maxAge=7200)](https://github.com/1nv1/php-periphery-serial) [![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/vsergeev/c-periphery/blob/master/LICENSE)

A php extension for peripheral I/O Serial in GNU/Linux.

## Warning

This project isn't yet useful. The commits are a backup process only.

## Introduction

The goal of this project is build a wrapper (serial I/O) of [c-periphery](https://github.com/vsergeev/c-periphery)
library.

## Warning

This project really has two goal, the first is create a wrapper and the second
is learn about php extensions. It's my first project around this.

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

# License

php-periphery-serial is MIT licensed. See the included [LICENSE](LICENSE) file.

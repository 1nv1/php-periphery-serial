/*
 * php-periphery by Nelson Lombardo
 * https://github.com/1nv1/php-periphery-serial
 * License: MIT
 */

#ifndef _PHP_PERIPHERY_SERIAL_H_
#define _PHP_PERIPHERY_SERIAL_H_

#include <c-periphery/src/version.h>
#include <c-periphery/src/serial.c>

#define _STRINGIFY(x) #x
#define STRINGIFY(x)  _STRINGIFY(x)

#define PHP_PERIPHERY_SERIAL_GIT_HASH \
  STRINGIFY(PHP_PERIPHERY_SERIAL_GIT_HASH_STR)

#define PHP_PERIPHERY_SERIAL_VERSION \
  STRINGIFY(PERIPHERY_VERSION_MAJOR) "" \
  STRINGIFY(PERIPHERY_VERSION_MINOR) "" \
  STRINGIFY(PERIPHERY_VERSION_PATCH)

#define PHP_PERIPHERY_SERIAL_EXTNAME "periphery_serial"

PHP_MINIT_FUNCTION(periphery_serial);
PHP_MSHUTDOWN_FUNCTION(periphery_serial);
PHP_RINIT_FUNCTION(periphery_serial);
PHP_RSHUTDOWN_FUNCTION(periphery_serial);
PHP_MINFO_FUNCTION(periphery_serial);

PHP_FUNCTION(periphery_serial_init);
PHP_FUNCTION(periphery_serial_open);
PHP_FUNCTION(periphery_serial_read);
PHP_FUNCTION(periphery_serial_write);
PHP_FUNCTION(periphery_serial_poll);
PHP_FUNCTION(periphery_serial_flush);
PHP_FUNCTION(periphery_serial_input_waiting);
PHP_FUNCTION(periphery_serial_output_waiting);
PHP_FUNCTION(periphery_serial_close);
PHP_FUNCTION(periphery_serial_version);
PHP_FUNCTION(periphery_serial_git_hash);

#endif

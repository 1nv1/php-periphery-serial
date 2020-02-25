PHP_ARG_ENABLE(periphery_serial, [ ], [ --enable-periphery_serial   Enable periphery wrapper ])
if test "$PHP_PERIPHERY_SERIAL" != "no"; then
GH=`git rev-parse HEAD`
PHP_NEW_EXTENSION(periphery_serial, src/php_periphery_serial.c, $ext_shared, , -DPHP_PERIPHERY_SERIAL_GIT_HASH_STR=$GH)
fi

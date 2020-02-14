/*
 * php-periphery by Nelson Lombardo
 * https://github.com/1nv1/php-periphery-serial
 * License: MIT
 */

#include <php.h>

#include <time.h>
#include <unistd.h>

#include "php_periphery_serial.h"

static int le_periphery_serial_descriptor;
static int le_periphery_serial_iter_descriptor;

zend_function_entry periphery_serial_functions[] = {
  PHP_FE(periphery_serial_init, NULL)
  PHP_FE(periphery_serial_open, NULL)
  PHP_FE(periphery_serial_close, NULL)
  PHP_FE(periphery_serial_version, NULL)
  PHP_FE_END
};

zend_module_entry periphery_serial_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_PERIPHERY_SERIAL_EXTNAME,
  periphery_serial_functions,
  PHP_MINIT(periphery_serial),           /* Module init callback */
  PHP_MSHUTDOWN(periphery_serial),       /* Module shutdown callback */
  PHP_RINIT(periphery_serial),           /* Request init callback */
  PHP_RSHUTDOWN(periphery_serial),       /* Request shutdown callback */
  PHP_MINFO(periphery_serial),           /* Module info callback */
  PHP_PERIPHERY_SERIAL_VERSION,
  STANDARD_MODULE_PROPERTIES,
};

ZEND_GET_MODULE(periphery_serial);


static void periphery_descriptor_dtor(zend_resource *rsrc TSRMLS_DC)
{
  free(rsrc->ptr);
}

static zend_always_inline serial_t* periphery_serial_fetch_resource(zval *res, zval *return_value TSRMLS_DC)
{
  serial_t *serial;

  return (serial_t*)zend_fetch_resource(Z_RES_P(res), PHP_PERIPHERY_SERIAL_EXTNAME, le_periphery_serial_descriptor);
}


PHP_MINIT_FUNCTION(periphery_serial)
{
  le_periphery_serial_descriptor = zend_register_list_destructors_ex(
    periphery_descriptor_dtor,
    NULL,
    PHP_PERIPHERY_SERIAL_EXTNAME,
    module_number
  );

  le_periphery_serial_iter_descriptor = zend_register_list_destructors_ex(
    periphery_descriptor_dtor,
    NULL,
    "periphery_serial_iterator",
    module_number
  );

  return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(periphery_serial)
{
  return SUCCESS;
}

PHP_RINIT_FUNCTION(periphery_serial)
{
  return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(periphery_serial)
{
  return SUCCESS;
}

PHP_MINFO_FUNCTION(periphery_serial)
{
}

static zend_always_inline void periphery_serial_register_resource(zval *return_value, serial_t *serial TSRMLS_DC)
{
  ZVAL_RES(return_value, zend_register_resource(serial, le_periphery_serial_descriptor));
}

PHP_FUNCTION(periphery_serial_init)
{
  serial_t *serial;
  serial = serial_new();
  periphery_serial_register_resource(return_value, serial TSRMLS_CC);
}

PHP_FUNCTION(periphery_serial_open)
{
  zval *zserial;
  serial_t *serial;
  zend_string *zdevice;
  zend_string *zparity;
  int device_len;
  uint32_t baudrate;
  int databits;
  serial_parity_t parity;
  int stopbits;
  bool xonxoff;
  bool rtscts;
  int ret;
  int qarg;

  ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 5)
    Z_PARAM_ZVAL(zserial)
    Z_PARAM_STR(zdevice)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(baudrate)
    Z_PARAM_LONG(databits)
    Z_PARAM_STR(zparity)
  ZEND_PARSE_PARAMETERS_END();

  // Baudrate control
  switch (baudrate)
  {
    case 1200:   break;
    case 2400:   break;
    case 4800:   break;
    case 9600:   break;
    case 19200:  break;
    case 14400:  break;
    case 38400:  break;
    case 57600:  break;
    case 115200: break;
    default:     RETVAL_FALSE;
  }

  if (strcmp(ZSTR_VAL(zparity), "none") == 0) { parity = PARITY_NONE; }
  else if (strcmp(ZSTR_VAL(zparity), "odd") == 0) { parity = PARITY_ODD; }
  if (strcmp(ZSTR_VAL(zparity), "even") == 0) { parity = PARITY_EVEN; }

  serial = periphery_serial_fetch_resource(zserial, return_value TSRMLS_CC);

  /* Default settings of optional arguments */
  databits = 8;
  parity = PARITY_NONE;
  stopbits = 1;
  xonxoff = 0;
  rtscts = 0;

  if ((ret = serial_open_advanced(serial, ZSTR_VAL(zdevice), baudrate, databits, parity, stopbits, xonxoff, rtscts)) < 0) {
    RETVAL_FALSE;
  }
  RETVAL_TRUE;
}

PHP_FUNCTION(periphery_serial_close)
{
  zval *zserial;
  serial_t *serial;
  int ret;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zserial) == FAILURE) {
    RETVAL_FALSE;
  }

  serial = periphery_serial_fetch_resource(zserial, return_value TSRMLS_CC);

  if ((ret = serial_close(serial)) < 0) RETVAL_FALSE;

  RETVAL_TRUE;
}

PHP_FUNCTION(periphery_serial_version)
{
  RETVAL_STRING(PHP_PERIPHERY_SERIAL_VERSION);
}

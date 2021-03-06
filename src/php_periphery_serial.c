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
  PHP_FE(periphery_serial_read, NULL)
  PHP_FE(periphery_serial_write, NULL)
  PHP_FE(periphery_serial_poll, NULL)
  PHP_FE(periphery_serial_flush, NULL)
  PHP_FE(periphery_serial_input_waiting, NULL)
  PHP_FE(periphery_serial_output_waiting, NULL)
  PHP_FE(periphery_serial_close, NULL)
  PHP_FE(periphery_serial_version, NULL)
  PHP_FE(periphery_serial_git_hash, NULL)
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
  int xonxoff;
  int rtscts;
  int ret;
  int qarg;

  /* Default settings of optional arguments */
  databits = 8;
  parity = PARITY_NONE;
  stopbits = 1;
  xonxoff = 0;
  rtscts = 0;

  ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 2, 8)
    Z_PARAM_ZVAL(zserial)
    Z_PARAM_STR(zdevice)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(baudrate)
    Z_PARAM_LONG(databits)
    Z_PARAM_STR(zparity)
    Z_PARAM_LONG(stopbits)
    Z_PARAM_LONG(xonxoff)
    Z_PARAM_LONG(rtscts)
  ZEND_PARSE_PARAMETERS_END();

  if (strcmp(ZSTR_VAL(zparity), "none") == 0) { parity = PARITY_NONE; }
  else if (strcmp(ZSTR_VAL(zparity), "odd") == 0) { parity = PARITY_ODD; }
  else if (strcmp(ZSTR_VAL(zparity), "even") == 0) { parity = PARITY_EVEN; }

  serial = periphery_serial_fetch_resource(zserial, return_value TSRMLS_CC);

  if ((ret = serial_open_advanced(serial, ZSTR_VAL(zdevice), baudrate, databits, parity, stopbits, xonxoff, rtscts)) < 0) {
    RETVAL_FALSE;
  }
  RETVAL_TRUE;
}

PHP_FUNCTION(periphery_serial_read)
{
  zval retval;
  zval *zserial;
  serial_t *serial;
  static char buf[256];
  int timeout_ms;
  size_t len;
  int length;
  int ret;

  /* Default settings of optional arguments */
  timeout_ms = -1;
  length = 0;
  len = sizeof(char);

  ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 1, 3)
    Z_PARAM_ZVAL(zserial)
    Z_PARAM_OPTIONAL
    Z_PARAM_LONG(length)
    Z_PARAM_LONG(timeout_ms)
  ZEND_PARSE_PARAMETERS_END();

  if (length) { len = length * len; }

  serial = periphery_serial_fetch_resource(zserial, return_value TSRMLS_CC);

  ret = serial_read(serial, buf, len, timeout_ms);

  if (ret < 0) {
    RETURN_NULL();
  }

  array_init(return_value);
  for (int i = 0; i < ret; i++) {
    add_index_long(return_value, i, 0xFF & buf[i]);
  }

  return;
}

PHP_FUNCTION(periphery_serial_write)
{
  zval *zserial;
  HashTable *arr_hash;
  HashPosition pos;
  zval *input;
  zval *arr;
  char *buf, *bufi, *buft;
  int len;
  serial_t *serial;
  int ret;
  int i;

  ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
    Z_PARAM_ZVAL(zserial)
    Z_PARAM_ZVAL(input)
    Z_PARAM_LONG(len)
  ZEND_PARSE_PARAMETERS_END();

  buf = (char*) malloc(len * sizeof(char));
  arr_hash = Z_ARRVAL_P(input);
  serial = periphery_serial_fetch_resource(zserial, return_value TSRMLS_CC);

  for (
    zend_hash_internal_pointer_reset_ex(arr_hash, &pos), i = 0;
    (arr = zend_hash_get_current_data_ex(arr_hash, &pos)) != NULL;
    zend_hash_move_forward_ex(arr_hash, &pos), i++, buf++
  ) {
    if (Z_TYPE_P(arr) == IS_STRING) {
      buft = strdup(Z_STRVAL_P(arr));
      *buf = buft[0];
    }
    else if (Z_TYPE_P(arr) == IS_LONG) {
      buf = Z_STRVAL_P(arr);
    } else {
      RETVAL_FALSE;
    }
    if (i == 0) { bufi = buf; }
  }
  *buf = '\0';
  buf = bufi;

  if ((ret = serial_write(serial, buf, len)) < 0) {
    RETVAL_FALSE;
  }

  RETVAL_LONG(ret);
}

PHP_FUNCTION(periphery_serial_poll)
{
  zval *zserial;
  serial_t *serial;
  int timeout_ms;
  int ret;

  ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
    Z_PARAM_ZVAL(zserial)
    Z_PARAM_LONG(timeout_ms)
  ZEND_PARSE_PARAMETERS_END();

  serial = periphery_serial_fetch_resource(zserial, return_value TSRMLS_CC);

  if ((ret = serial_poll(serial, timeout_ms)) > 0) {
    RETVAL_TRUE;
  }

  RETVAL_FALSE;
}


PHP_FUNCTION(periphery_serial_flush)
{
  zval *zserial;
  serial_t *serial;
  int ret;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &zserial) == FAILURE) {
    RETVAL_FALSE;
  }

  serial = periphery_serial_fetch_resource(zserial, return_value TSRMLS_CC);

  if ((ret = serial_flush(serial)) < 0) {
    RETVAL_FALSE;
  }

  RETVAL_TRUE;
}

PHP_FUNCTION(periphery_serial_input_waiting)
{
  zval *zserial;
  serial_t *serial;
  unsigned int count;
  int ret;

  ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
    Z_PARAM_ZVAL(zserial)
  ZEND_PARSE_PARAMETERS_END();

  serial = periphery_serial_fetch_resource(zserial, return_value TSRMLS_CC);

  count = 0;
  if ((ret = serial_input_waiting(serial, &count)) < 0) {
    RETVAL_FALSE;
  }

  RETVAL_LONG(count);

}

PHP_FUNCTION(periphery_serial_output_waiting)
{
  zval *zserial;
  serial_t *serial;
  unsigned int count;
  int ret;

  ZEND_PARSE_PARAMETERS_START_EX(ZEND_PARSE_PARAMS_THROW, 3, 3)
    Z_PARAM_ZVAL(zserial)
    ZEND_PARSE_PARAMETERS_END();

  serial = periphery_serial_fetch_resource(zserial, return_value TSRMLS_CC);

  count = 0;
  if ((ret = serial_output_waiting(serial, &count)) < 0) {
    RETVAL_FALSE;
  }

  RETVAL_LONG(count);

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

  if ((ret = serial_close(serial)) < 0) {
    RETVAL_FALSE;
  }

  RETVAL_TRUE;
}

PHP_FUNCTION(periphery_serial_version)
{
  RETVAL_STRING(PHP_PERIPHERY_SERIAL_VERSION);
}

PHP_FUNCTION(periphery_serial_git_hash)
{
  RETVAL_STRING(PHP_PERIPHERY_SERIAL_GIT_HASH);
}

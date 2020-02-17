--TEST--
periphery_serial: Basic Functionality
--FILE--
<?php
$serial = periphery_serial_init();
var_dump($serial);
echo "Open: ".periphery_serial_open($serial, "/dev/ttyS0", 9600).PHP_EOL;
echo "Read: ".(periphery_serial_read($serial, 10, 100) == NULL ? 1 : 0).PHP_EOL;
$send = str_split('Hola');
echo "Write: ".periphery_serial_write($serial, $send, count($send)).PHP_EOL;
periphery_serial_flush($serial);
echo "Flush...".PHP_EOL;
echo "Close: ".periphery_serial_close($serial).PHP_EOL;
--EXPECTF--
resource(4) of type (periphery_serial)
Open: 1
Read: 1
Write: -5
Flush...
Close: 1
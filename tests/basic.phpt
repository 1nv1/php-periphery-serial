--TEST--
periphery_serial: Basic Functionality
--FILE--
<?php
$serial = periphery_serial_init();
var_dump($serial);
echo "Open: ".periphery_serial_open($serial, "/dev/ttyS0", 9600).PHP_EOL;
echo "Read: ".(periphery_serial_read($serial, 10, 100) == NULL ? 1 : 0).PHP_EOL;
echo "Close: ".periphery_serial_close($serial).PHP_EOL;
--EXPECTF--
resource(4) of type (periphery_serial)
Open: 1
Read: 1
Close: 1
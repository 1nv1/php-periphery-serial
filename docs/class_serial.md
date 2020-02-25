### NAME

Serial Class for Linux userspace termios `tty` devices.

### SYNOPSIS

``` php
require_once "class/Periphery.php";

-- Constructor
object = new Periphery\Serial()

object->open(device <path string>, baudrate <number>)
object{device=<path string>, baudrate=<number>, databits=8, parity="none", stopbits=1, xonxoff=false, rtscts=false}

-- Methods
object->read(length <number>, [timeout <number>]) --> <array>
object->read{length=<length>, timeout=nil} --> <array>
object->write(data <array>) --> <number>
object->poll(timeout_ms) --> <boolean>
object->flush()
object->input_waiting() --> <number> or <boolean>
object->output_waiting() --> <number> or <boolean>
object->close()

-- Properties
object.baudrate     mutable <number>
object.databits     mutable <number>
object.parity       mutable <string>
object.stopbits     mutable <number>
object.xonxoff      mutable <boolean>
object.rtscts       mutable <boolean>
```

### CONSTANTS

* Serial parity
    * `"none"` - No parity
    * `"odd"` - Odd parity
    * `"even"` - Even parity

### DESCRIPTION

``` php
object->open(device <path string>, baudrate <number>) --> <boolean>
object->open(device=<path string>, baudrate=<number>, databits=8, parity="none", stopbits=1, xonxoff=false, rtscts=false) --> <boolean>
```

Open open the `tty` device at the specified path with the specified baudrate, and the defaults of 8 data bits, no parity, 1 stop bit, no software flow control (xonxoff), and no hardware flow control (rtscts). Defaults may be overridden with the table constructor. Parity can be "none", "odd", "even" (see [constants](#constants) above).

Example:
``` php
object->open("/dev/ttyUSB0", 115200);
object->open("/dev/ttyUSB0", 115200, "none", 1);
```

Returns FALSE if it's fail, TRUE if success.

--------------------------------------------------------------------------------

``` php
object->read(length <number>, [timeout_ms <number>]) --> <array>
object->read(length=<length>, timeout_ms=nil) --> <array>
```
Read up to `length` number of bytes from the serial port with an optional timeout. `timeout_ms` can be 0 for a non-blocking read, negative for a blocking read that will block until `length` number of bytes are read, or positive specifying a timeout in milliseconds for a blocking read. The default is a blocking read that will block until `length` number of bytes are read.

For a non-blocking or timeout bound read, `read()` returns a string with the bytes read, whose length is less than or equal to the length requested. For a blocking read (default), `read()` returns a array with the bytes read, whose length is the length requested.

--------------------------------------------------------------------------------

``` php
object->write(data <array>) --> <number>
```
Write the specified `data` array to the serial port.

Returns the number of bytes written.

--------------------------------------------------------------------------------

``` php
object->poll(timeout) --> <boolean>
```
Poll for data available for reading from the serial port. `timeout` can be positive for a timeout in milliseconds, 0 for a non-blocking poll, or a negative number for a blocking poll.

Returns `true` if data is available for reading from the serial port, otherwise returns `false`.

--------------------------------------------------------------------------------

``` php
object->flush()
```
Flush the write buffer of the serial port, blocking until all bytes are written.

--------------------------------------------------------------------------------

``` php
object->input_waiting() --> <number>
```
Query the number of bytes waiting to be read from the serial port.

Returns the number of bytes.

--------------------------------------------------------------------------------

``` php
object->output_waiting() --> <number>
```
Query the number of bytes waiting to be written to the serial port.

Returns the number of bytes.

--------------------------------------------------------------------------------

``` php
object->close()
```
Close the `tty` device.

--------------------------------------------------------------------------------

``` php
Property object->baudrate <number>
Property object->databits <number>
Property object->parity   <string>
Property object->stopbits <number>
Property object->xonxoff  <boolean>
Property object->rtscts   <boolean>
```
Get or set the baudrate, data bits, parity, stop bits, software flow control (xonxoff), or hardware flow control (rtscts), respectively, of the underlying `tty` device.

Databits can be 5, 6, 7, or 8. Stopbits can be 1, or 2. Parity can be "none", "odd", or "even".

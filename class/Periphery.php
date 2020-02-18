<?php

namespace Periphery;

class Serial {

  private $serial;
  private $res;
  private $device;
  private $baudrate;
  private $timeout_ms;
  private $output;

  public function __construct()
  {
    $this->serial = periphery_serial_init();
    if ($this->serial) { return TRUE; }
    else { return FALSE; }
  }

  public function open($device, $baudrate = 9600)
  {
    $this->device = $device;
    if (!empty($this->device)) { return FALSE; }
    $this->baudrate = $baudrate;
    $this->res = periphery_serial_open($this->serial, $this->device, $this->baudrate);
    return $this->res;
  }

  public function read($len, $timeout_ms = 500)
  {
    $this->timeout_ms = $timeout_ms;
    $this->output = periphery_serial_read($this->serial, $len, $timeout_ms);
    return $this->output;
  }

  public function write($input, $len = 0)
  {
    $len = $len == 0 ? count($input) : $len;
    $this->output = periphery_serial_write($this->serial, $input, $len);
    return $this->output;
  }

  public function flush()
  {
    periphery_serial_flush($this->serial);
  }

  public function close()
  {
    $this->res = periphery_serial_close($this->serial);
    return $this->res;
  }

  public function version()
  {
    return periphery_serial_version();
  }

}

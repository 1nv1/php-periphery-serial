<?php

namespace Periphery;

class Serial {

  private $serial;
  private $res;
  private $timeout_ms = 500;
  private $output;

  public $device;
  public $baudrate;
  public $parity;
  public $stopbits;
  public $xonxoff;
  public $rtscts;

  private function _testRange($v, $va, $vb)
  {
    if (($v >= $va) && ($v <= $vb)) return TRUE;
    else return FALSE;
  }

  private function _testArray($v, $r)
  {
    foreach($r as $b) {
      if ($r == $v)
        return TRUE;
    }
    return FALSE;
  }

  public function __construct()
  {
    $this->serial = periphery_serial_init();
    if ($this->serial) { return TRUE; }
    else { return FALSE; }
  }

  public function open($device, $baudrate = 9600, $databits = 8, $parity = "none", $stopbits = 1, $xonxoff = 0, $rtscts = 0)
  {
    $bd_ref = array(50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800, 500000, 576000, 921600, 1000000, 1152000, 1500000, 2000000)
    if (!empty($device)) {
      $this->device = NULL;
      return FALSE;
    } else {
      $this->device = $device;
    }
    if ($this->_testArray($baudrate, $br_ref) == TRUE)
    {
      $this->baudrate = $baudrate;
    } else {
      $this->baudrate = NULL;
      return FALSE;
    }
    if ($this->_testRange($databits, 5, 8) == TRUE)
    {
      $this->databits = $databits;
    } else {
      $this->databits = NULL;
      return FALSE;
    }
    if (($parity == "none") || ($parity == "odd") || ($parity == "even"))
    {
      $this->parity = $parity;
    } else {
      $this->parity = NULL;
      return FALSE;
    }
    if (_testRange($stopbits, 1, 2) == TRUE)
    {
      $this->stopbits = $stopbits;
    } else {
      $this->stopbits = NULL;
      return FALSE;
    }
    if ($this->_testRange($xonxoff, 0, 1) == TRUE)
    {
      $this->xonoff = $xonxoff;
    } else {
      $this->xonoff = NULL;
      return FALSE;
    }
    if ($this->_testRange($rtscts, 0, 1) == TRUE)
    {
      $this->rtscts = $rtscts;
    } else {
      $this->rtscts = NULL;
      return FALSE;
    }
    $this->res = periphery_serial_open(
                                       $this->serial,
                                       $this->device,
                                       $this->baudrate,
                                       $this->databits,
                                       $this->parity,
                                       $this->stopbits,
                                       $this->xonxoff,
                                       $this->rtscts
                                      );
    return $this->res;
  }

  public function read($len, $timeout_ms)
  {
    $timeout_ms = !empty($timeout_ms) ? $this->timeout_ms : $timeout_ms;
    $this->output = periphery_serial_read($this->serial, $len, $timeout_ms);
    return $this->output;
  }

  public function write($input, $len = 0)
  {
    $len = $len == 0 ? count($input) : $len;
    $this->output = periphery_serial_write($this->serial, $input, $len);
    return $this->output;
  }

  public function poll($timeout_ms = 0)
  {
    $this->output = periphery_serial_poll($this->serial, $timeout_ms);
    return $this->output;
  }

  public function flush()
  {
    periphery_serial_flush($this->serial);
  }

  public function input_waiting()
  {
    $this->output = periphery_serial_input_waiting($this->serial);
    return $this->output;
  }

  public function output_waiting()
  {
    $this->output = periphery_serial_output_waiting($this->serial);
    return $this->output;
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

  public function git_hash()
  {
    return periphery_serial_git_hash();
  }

}

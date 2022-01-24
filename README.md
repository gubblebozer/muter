Transmission Error Mute Circuit for the Twisted Pear Opus DAC
-------------------------------------------------------------

_YES, I COULD HAVE DONE THIS WITH A 555._

Board:

  - Adafruit Metro Mini 328

Logic:

  - 3.3V

Pins:

  - 2: <input>  WM8804 TRANS_ERR
  - 3: <output> WM8741 MUTE

This code burns the CPU to poll for a high TRANS_ERR pin on the WM8804
S/PDIF receiver.  When it sees one, it mutes the WM8741 DAC for 250ms.

The built-in LED indicates that the DAC is muted.


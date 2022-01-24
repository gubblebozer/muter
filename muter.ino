////////////////////////////////////////////////////////////////////////////////
/// Transmission Error Mute Circuit for the Twisted Pear Opus DAC
///
/// YES, I COULD HAVE DONE THIS WITH A 555.
///
/// Board:
///
///   - Adafruit Metro Mini 328
///
/// Logic:
///
///   - 3.3V
///
/// Pins:
///
///   - 2: <input>  WM8804 TRANS_ERR
///   - 3: <output> WM8741 MUTE
///
/// This code burns the CPU to poll for a high TRANS_ERR pin on the WM8804
/// S/PDIF receiver.  When it sees one, it mutes the WM8741 DAC for 250ms.
///
/// The built-in LED indicates that the DAC is muted.
////////////////////////////////////////////////////////////////////////////////
typedef enum g_pins {
    G_TRANS_ERR = 2,
    G_MUTE      = 3,
} g_pins;

bool muted = false;

////////////////////////////////////////////////////////////////////////////////
/// Mute the WM8741 by setting the mute line to low.
////////////////////////////////////////////////////////////////////////////////
void
mute(void)
{
    digitalWrite(G_MUTE, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    muted = true;
}

////////////////////////////////////////////////////////////////////////////////
/// Unmute the WM8741
////////////////////////////////////////////////////////////////////////////////
void
unmute(void)
{
    muted = false;
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(G_MUTE, HIGH);
}

////////////////////////////////////////////////////////////////////////////////
/// Bring up the system in muted state, and delay a few seconds like this.
////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(G_TRANS_ERR, INPUT);
  pinMode(G_MUTE, OUTPUT);

  // start out muted, let everything settle
  mute();
  delay(3000);

  // Serial.begin(9600);
  // Serial.println("awake");
}

////////////////////////////////////////////////////////////////////////////////
/// Loop, polling for transmission error.  When detected, mute the WM8741 for
/// 250ms.  Keep the DAC muted for as long as there's a transmission error.
////////////////////////////////////////////////////////////////////////////////
void loop() {

    while (digitalRead(G_TRANS_ERR)) {
        mute();
        // Serial.println("TRANS_ERR");
        delay(250);
    }

    if (muted)
        unmute();
}

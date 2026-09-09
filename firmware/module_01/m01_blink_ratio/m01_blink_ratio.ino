/*
  m01_blink_ratio.ino
  Module 1 -- Part 1: Blink and digital output

  Modified from the Arduino built-in Blink example (public domain):
    https://docs.arduino.cc/built-in-examples/basics/Blink/
    modified 8 May 2014 by Scott Fitzgerald
    modified 2 Sep 2016 by Arturo Guadalupi
    modified 8 Sep 2016 by Colby Newman

  Our changes: drive an external LED on pin 9 alongside LED_BUILTIN, and select the
  HIGH:LOW time ratio with one constant so the three required cases can be run
  without editing the delays each time.

  Team:      TEC 8
  Board:     Arduino Uno, USB powered.  TEC POWER SUPPLY OFF for all of Module 1.
  Wiring:    Built-in LED on pin 13 (LED_BUILTIN).
             External LED: pin 9 -> 150 kOhm series resistor -> LED anode;
             LED cathode -> GND.  (Pin 9 is re-used by Part 4 for PWM, so the
             same LED and resistor serve both parts.)
  Baud:      9600
  Output:    a banner at startup naming the ratio, times, period and duty.
  Produces:  values recorded in data/module_01/m01_scope_measurements.md section 3

  Version:   v2 (2026-09-09) -- rebuilt on the stock Blink example with the delays
             actually used in lab. v1 used 500/500 ms and pin 8, which was wrong.

  ----------------------------------------------------------------------------
  HOW TO RUN THE THREE REQUIRED CASES
  Set RATIO_CASE below to 0, 1, then 2 and upload each time.

  Predicted from the constants below -- these only restate what is written here,
  so they are NOT measurements:

    case 0  1:1    on 1000 / off 1000 ms   T = 2.000 s   f = 0.500 Hz   duty 50.0 %
    case 1  10:1   on 1000 / off  100 ms   T = 1.100 s   f = 0.909 Hz   duty 90.9 %
    case 2  1:10   on  100 / off 1000 ms   T = 1.100 s   f = 0.909 Hz   duty  9.1 %

  Note that the PERIOD IS NOT CONSTANT here: one delay is held at the stock
  1000 ms and the other scaled, so changing the ratio changes period and
  frequency as well as duty cycle. Contrast Part 4, where the PWM period is fixed
  by the timer at ~2.04 ms and only the duty cycle follows the potentiometer.
  That contrast is worth a sentence in the evidence note.

  NO PHOTOGRAPH FOR THIS PART. At 0.5-0.9 Hz the BK 2120B's spot crawls across
  the screen and the phosphor decays long before the sweep completes, so no
  persistent trace forms -- there is nothing to shoot. To measure instead:
    high / low voltage : DC-coupled scope, or a DMM. Steady levels, easy.
    period             : stopwatch over TEN cycles, divide by ten.
    duty cycle         : on-time over period, timed the same way.

  Expect a measured period slightly OVER the predicted value: delay() blocks for
  at least the requested time, and digitalWrite plus loop overhead add to it.
  ----------------------------------------------------------------------------
*/

const char* VERSION = "m01_blink_ratio v2";

// 0 = 1:1   (1000 ms on, 1000 ms off)
// 1 = 10:1  (1000 ms on,  100 ms off)
// 2 = 1:10  ( 100 ms on, 1000 ms off)
const int RATIO_CASE = 0;

const int PIN_EXTERNAL_LED = 9;   // 150 kOhm series resistor to the LED

const unsigned long ON_MS[]  = {1000, 1000,  100};
const unsigned long OFF_MS[] = {1000,  100, 1000};

void setup() {
  Serial.begin(9600);
  Serial.println(VERSION);   // proves which build is on the board

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_EXTERNAL_LED, OUTPUT);

  unsigned long on = ON_MS[RATIO_CASE];
  unsigned long off = OFF_MS[RATIO_CASE];
  unsigned long period = on + off;

  Serial.print("RATIO_CASE ");
  Serial.print(RATIO_CASE);
  Serial.print(": on ");
  Serial.print(on);
  Serial.print(" ms, off ");
  Serial.print(off);
  Serial.print(" ms -> period ");
  Serial.print(period / 1000.0, 3);
  Serial.print(" s, f ");
  Serial.print(1000.0 / period, 3);
  Serial.print(" Hz, duty ");
  Serial.print(100.0 * on / period, 1);
  Serial.println(" %");
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(PIN_EXTERNAL_LED, HIGH);
  delay(ON_MS[RATIO_CASE]);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(PIN_EXTERNAL_LED, LOW);
  delay(OFF_MS[RATIO_CASE]);
}

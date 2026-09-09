# Oscilloscope and bench measurements — Module 1

**STATUS: §3 (Blink) is closed — reported as calculated. Everything else is empty and needs
the bench.**

Print this page or keep it open on the laptop while the Arduino and scope are in front
of you. Every blank below is required by the A1 evidence checklist. Include units.

Recorded by: ______________  Date: ____________

**Scope: BK Precision 2120B, 30 MHz dual trace — ANALOG.** No cursors, no measurement
readout, no screenshot export. Every number below is read off the graticule in divisions and
converted with the knob settings, so **record the settings with every trace**:

    period     = (divisions per cycle) × (TIME/DIV)
    frequency  = 1 / period
    amplitude  = (vertical divisions) × (VOLTS/DIV) × (probe attenuation)
    duty cycle = (divisions high / divisions per cycle) × 100 %

Probe attenuation: ×1 / ×10 (circle — the scope does not know, and getting it wrong
scales every voltage by 10). Input coupling: DC (not AC — you need the true 0 V and 5 V).

---

## 1. Reference voltage

| Quantity | Value | How obtained |
|---|---|---|
| V_ref (Arduino 5V rail) | ______ V | measured with DMM / assumed nominal 5.00 V (circle) |
| One-count resolution ΔV = V_ref / 1024 | ______ mV | calculated |

> All sketches in this repo use `/1024.0`. If you measure V_ref and it is not 5.00 V,
> update the constant in every sketch **and** say so in the evidence note.

---

## 2. ADC range (sketch: `m01_adc_raw`)

| Quantity | ADC counts | Voltage (V) |
|---|---|---|
| Minimum reachable (pot fully one way) | | |
| Maximum reachable (pot fully other way) | | |
| Midrange setting chosen and held | | |

Spread observed at the fixed midrange setting, untouched: ______ counts
(e.g. "values wander between 511 and 514")

---

## 3. Blink timing (sketch: `m01_blink_ratio`; `LED_BUILTIN` pin 13 + external LED pin 9)

**Reported as calculated, not measured — by decision.** The values below come from the sketch
constants and nominal ATmega328P levels, and the evidence note says so explicitly. Nothing on
this page needs filling for Part 1.

| RATIO_CASE | Ratio | On (ms) | Off (ms) | Period (s) | Frequency (Hz) | Duty (%) | High (V) | Low (V) |
|---|---|---|---|---|---|---|---|---|
| 0 | 1:1 | 1000 | 1000 | 2.000 | 0.500 | 50.0 | 5.0 nom. | 0.0 nom. |
| 1 | 10:1 | 1000 | 100 | 1.100 | 0.909 | 90.9 | 5.0 nom. | 0.0 nom. |
| 2 | 1:10 | 100 | 1000 | 1.100 | 0.909 | 9.1 | 5.0 nom. | 0.0 nom. |

### Optional upgrade to measured values

If bench time appears, this takes a few minutes and no camera. Fill the row and change the
wording in the note from "calculated" to "measured".

| RATIO_CASE | High (V) | Low (V) | 10 cycles (s) | Period (s) | Duty (%) |
|---|---|---|---|---|---|
| 0 | | | | | |
| 1 | | | | | |
| 2 | | | | | |

Voltages: DC-coupled scope or a DMM — the levels are steady. Timing: stopwatch over **ten**
cycles divided by ten, keeping reaction error near 1 %. Two things only a measurement shows:
whether the high level reaches 5 V and how far it sags under LED current (______ V connected
vs ______ V disconnected), and whether the period exceeds 1.000 s because `delay()` blocks for
*at least* the requested time (excess ______ ms, or "below my timing resolution").

## 4. Timing of 1000 conversions (sketch: `m01_avg_timing`)

| Quantity | Value |
|---|---|
| Elapsed time for 1000 `analogRead()` calls | ______ µs |
| Time per conversion | ______ µs |
| Conversions per second | ______ /s |
| Arduino reference value | ≈100 µs, ≈10 000 /s |
| Agreement? | |

---

## 5. LED PWM (sketch: `m01_pwm_from_pot`, pin 9)

Take readings at **two substantially different** potentiometer settings.

| | Setting A (low) | Setting B (high) |
|---|---|---|
| VOLTS/DIV | | |
| TIME/DIV | | |
| Probe attenuation | | |
| Divisions per cycle | | |
| Divisions high | | |
| Vertical divisions (low→high) | | |
| Averaged voltage from Serial Monitor (V) | | |
| PWM value shown (0–255) | | |
| High voltage (V) | | |
| Low voltage (V) | | |
| Period (ms) | | |
| Frequency (Hz) | | |
| Measured duty cycle (%) | | |
| Expected duty = PWM/255 × 100 (%) | | |
| Figure file | `m01_fig04_pwm_waveform.jpg` — **have this** | `m01_fig05_pwm_waveform_B.jpg` is the *same* setting; setting B still needs shooting |

Expected frequency on Uno pin 9: ≈490 Hz. Measured: ______ Hz. Difference: ______ %

Which quantities change with the potentiometer, and which stay approximately fixed?

______________________________________________________________________

---

## 6. Smallest discrete voltage jump

From the N=1-only Serial Plotter capture, the smallest nonzero change between two
consecutive points: ______ mV

Compared with ΔV = V_ref/1024 = ______ mV. Ratio: ______

(`analysis/module_01/averaging_stats.py` computes this for you from the raw capture —
use this row to cross-check the script against what you read off the plot.)

---

## 7. What the oscilloscope showed that the serial displays did not

Three bullets, written at the bench while you can still see both:

- 
- 
- 

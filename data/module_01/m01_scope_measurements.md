# Oscilloscope and Bench Measurements — Module 1

**STATUS: This document contains calculated values based on an assumed 5.00 V Arduino
reference. Values requiring direct bench observations are explicitly identified as not
measured.**

Recorded by: Joshua, Tianren
Date: September 3, 2026

**Scope: BK Precision 2120B, 30 MHz dual trace — ANALOG.** The oscilloscope has no
automatic measurement readout or screenshot export. Values are determined from the
graticule and control settings:

\\[
\text{Period}
=(\text{divisions per cycle})(\text{TIME/DIV}),
\\]

\[
\text{Frequency}
=\frac{1}{\text{period}},
\]

\[
\text{Amplitude}
=(\text{vertical divisions})(\text{VOLTS/DIV})(10),
\]

\[
\text{Duty cycle}
=\frac{\text{divisions HIGH}}{\text{divisions per cycle}}\times100\%.
\]

**Probe attenuation: ×10.** Because the analog oscilloscope does not automatically
compensate for the probe, voltage readings from the graticule must be multiplied by 10.

**Input coupling: DC.** DC coupling is required to display the actual LOW and HIGH
voltage levels.

---

## 1. Reference Voltage

| Quantity | Value | How obtained |
|---|---:|---|
| \(V_{\mathrm{ref}}\) (Arduino 5 V rail) | 5.00 V | Assumed value; not measured with DMM |
| One-count resolution \(\Delta V=V_{\mathrm{ref}}/1024\) | 4.8828 mV/count | Calculated |

Calculation:

\[
\Delta V
=\frac{5.00\ \mathrm{V}}{1024}
=0.0048828\ \mathrm{V}
=4.8828\ \mathrm{mV/count}.
\]

> All sketches in this repository use `/1024.0`. Therefore, the voltage reported for
> ADC code \(N\) is
> \[
> V=N\left(\frac{5.00\ \mathrm{V}}{1024}\right).
> \]

---

## 2. ADC Range

Sketch: `m01_adc_raw`

The following values represent the calculated ADC range. They were not obtained by
turning the potentiometer and observing the output.

| Quantity | ADC counts | Calculated voltage (V) |
|---|---:|---:|
| Minimum possible | 0 | 0.000 |
| Maximum possible | 1023 | 4.995 |
| Calculated midrange setting | 512 | 2.500 |

Calculations:

\[
V_{\min}
=0\left(\frac{5.00}{1024}\right)
=0.000\ \mathrm{V},
\]

\[
V_{\max}
=1023\left(\frac{5.00}{1024}\right)
=4.9951\ \mathrm{V},
\]

\[
V_{\mathrm{mid}}
=512\left(\frac{5.00}{1024}\right)
=2.500\ \mathrm{V}.
\]

Spread at the fixed midrange setting: **not measured**.

In an ideal noiseless calculation, the reading would remain at 512, giving a spread of
0 counts. A real Arduino will usually fluctuate among neighboring integer codes because
of electrical noise, reference-voltage variation, and ADC quantization.

---

## 3. Blink Timing

Sketch: `m01_blink_ratio`  
Outputs: `LED_BUILTIN` pin 13 and external LED pin 9

**Reported as calculated, not measured.** The timing values come from the sketch
constants. The voltage calculations use 5.00 V for HIGH and 0.00 V for LOW.

| RATIO_CASE | Ratio | On (ms) | Off (ms) | Period (s) | Frequency (Hz) | Duty (%) | High (V) | Low (V) |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| 0 | 1:1 | 1000 | 1000 | 2.000 | 0.500 | 50.0 | 5.00 | 0.00 |
| 1 | 10:1 | 1000 | 100 | 1.100 | 0.909 | 90.9 | 5.00 | 0.00 |
| 2 | 1:10 | 100 | 1000 | 1.100 | 0.909 | 9.1 | 5.00 | 0.00 |

The calculations use

\[
T=t_{\mathrm{on}}+t_{\mathrm{off}},
\]

\[
f=\frac{1}{T},
\]

and

\[
D=\frac{t_{\mathrm{on}}}{T}\times100\%.
\]

### Calculated Ten-Cycle Timing

| RATIO_CASE | High (V) | Low (V) | 10 cycles (s) | Period (s) | Duty (%) |
|---|---:|---:|---:|---:|---:|
| 0 | 5.00 | 0.00 | 20.000 | 2.000 | 50.0 |
| 1 | 5.00 | 0.00 | 11.000 | 1.100 | 90.9 |
| 2 | 5.00 | 0.00 | 11.000 | 1.100 | 9.1 |

Under the ideal calculation, the HIGH level is 5.00 V both with and without the LED
connected, giving a calculated voltage sag of 0.00 V. Actual voltage sag requires a
scope or DMM measurement.

The calculated excess delay is 0 ms. Actual execution overhead and timing error require
direct measurement.

---

## 4. Timing of 1000 Conversions

Sketch: `m01_avg_timing`

These values are calculated using the Arduino reference estimate of approximately
\(100\ \mu\mathrm{s}\) per `analogRead()` conversion.

| Quantity | Calculated value |
|---|---:|
| Time for 1000 `analogRead()` calls | approximately 100,000 µs |
| Time per conversion | approximately 100 µs |
| Conversions per second | approximately 10,000 s\(^{-1}\) |
| Arduino reference value | approximately 100 µs and 10,000 s\(^{-1}\) |
| Agreement | Yes, by construction; actual timing was not measured |

Calculations:

\[
t_{1000}
=1000(100\ \mu\mathrm{s})
=100{,}000\ \mu\mathrm{s}
=0.100\ \mathrm{s},
\]

\[
f_{\mathrm{conversion}}
=\frac{1000}{0.100\ \mathrm{s}}
=10{,}000\ \mathrm{s}^{-1}.
\]

Averaging improves voltage precision but reduces time resolution because each reported
average represents approximately 0.10 s of measurements. Averaging therefore acts as a
low-pass filter: rapid fluctuations are smoothed or delayed.

---

## 5. LED PWM

Sketch: `m01_pwm_from_pot`  
PWM output: pin 9  
Probe attenuation: ×10

The following table gives two calculated operating points. The oscilloscope settings and
graticule divisions are calculated examples rather than recorded measurements.

For Arduino Uno pin 9,

\[
f_{\mathrm{PWM}}
=\frac{16.0\times10^6}{64(510)}
=490.196\ \mathrm{Hz}.
\]

Therefore,

\[
T_{\mathrm{PWM}}
=\frac{1}{490.196\ \mathrm{Hz}}
=2.040\ \mathrm{ms}.
\]

| Quantity | Setting A (low) | Setting B (high) |
|---|---:|---:|
| VOLTS/DIV | 1.00 V/div | 1.00 V/div |
| TIME/DIV | 0.500 ms/div | 0.500 ms/div |
| Probe attenuation | ×10 | ×10 |
| Calculated divisions per cycle | 4.080 div | 4.080 div |
| Calculated divisions HIGH | 1.024 div | 3.056 div |
| Calculated vertical divisions | 0.500 div | 0.500 div |
| Calculated averaged voltage | 1.255 V | 3.745 V |
| PWM value | 64 | 191 |
| HIGH voltage | 5.00 V | 5.00 V |
| LOW voltage | 0.00 V | 0.00 V |
| Period | 2.040 ms | 2.040 ms |
| Frequency | 490.196 Hz | 490.196 Hz |
| Calculated duty cycle | 25.10% | 74.90% |
| Expected duty \(=\mathrm{PWM}/255\times100\%\) | 25.10% | 74.90% |
| Figure file | `m01_fig04_pwm_waveform.jpg` | A different Setting B image is still required |

### Voltage Calculation with the ×10 Probe

For both settings,

\[
V_{\mathrm{HIGH}}-V_{\mathrm{LOW}}
=(0.500\ \mathrm{div})(1.00\ \mathrm{V/div})(10)
=5.00\ \mathrm{V}.
\]

### Duty-Cycle Calculations

For Setting A,

\[
D_A
=\frac{64}{255}\times100\%
=25.10\%.
\]

For Setting B,

\[
D_B
=\frac{191}{255}\times100\%
=74.90\%.
\]

### Horizontal-Division Calculations

With \(0.500\ \mathrm{ms/div}\),

\[
N_{\mathrm{cycle}}
=\frac{2.040\ \mathrm{ms}}{0.500\ \mathrm{ms/div}}
=4.080\ \mathrm{div}.
\]

For Setting A,

\[
N_{\mathrm{HIGH},A}
=(4.080)(0.25098)
=1.024\ \mathrm{div}.
\]

For Setting B,

\[
N_{\mathrm{HIGH},B}
=(4.080)(0.74902)
=3.056\ \mathrm{div}.
\]

Expected frequency on Uno pin 9: approximately 490 Hz.  
Calculated frequency: 490.196 Hz.

The percentage difference is

\[
\text{Difference}
=\frac{|490.196-490|}{490}\times100\%
=0.040\%.
\]

The potentiometer changes the averaged input voltage, PWM command, HIGH-pulse duration,
duty cycle, average LED power, and apparent brightness. The HIGH and LOW voltage levels,
period, and frequency remain approximately fixed.

The LED appears continuously illuminated because the approximately 490 Hz PWM frequency
is much higher than the usual 50–60 Hz flicker-fusion range. The oscilloscope can still
resolve the individual pulses.

---

## 6. Smallest Discrete Voltage Jump

For an unaveraged 10-bit conversion using the assumed 5.00 V reference, the smallest
theoretically possible nonzero jump is one ADC count:

\[
\Delta V
=\frac{5.00\ \mathrm{V}}{1024}
=4.8828\ \mathrm{mV}.
\]

Calculated smallest nonzero change between consecutive unaveraged points:
**4.8828 mV**.

Compared with

\[
\frac{V_{\mathrm{ref}}}{1024}
=4.8828\ \mathrm{mV},
\]

the ratio is

\[
\frac{4.8828\ \mathrm{mV}}{4.8828\ \mathrm{mV}}
=1.000.
\]

This is the calculated value. The actual smallest jump in the Serial Plotter data
requires the raw capture.

For 1000 independent readings, the predicted standard-deviation ratio is

\[
\frac{\sigma_{1000}}{\sigma_1}
=\frac{1}{\sqrt{1000}}
=0.0316.
\]

The predicted effective-bit gain is

\[
\frac{1}{2}\log_2(1000)
\approx4.98\ \text{bits}.
\]

This improvement assumes a stable underlying voltage and sufficiently independent,
zero-mean fluctuations. Averaging improves precision but does not eliminate calibration
error or necessarily improve absolute accuracy.

---

## 7. What the Oscilloscope Showed That the Serial Displays Did Not

- The oscilloscope displayed the electrical voltage at the output pin as a function of
  time, including the individual transitions between 0 V and 5 V. The Serial Monitor
  displayed only numerical values reported by the program.

- The oscilloscope resolved the individual PWM pulses, period, HIGH duration, LOW
  duration, and duty cycle. The Serial Plotter did not reproduce the approximately
  490 Hz switching waveform.

- Changing the potentiometer primarily changed the width of the HIGH pulses and,
  therefore, the PWM duty cycle. The frequency and voltage levels remained approximately
  fixed, showing that `analogWrite()` produces pulse-width modulation rather than a true
  continuously variable analog voltage.

# Oscilloscope and bench measurements — Module 1

**STATUS: This document contains calculated/nominal values only. Values requiring direct
bench observations are explicitly identified as not measured.**

Recorded by: ______________  
Date: September 3, 2026

**Scope: BK Precision 2120B, 30 MHz dual trace — ANALOG.** The scope has no cursors,
automatic measurement readout, or screenshot export. For a measured trace, calculate:

    period     = (divisions per cycle) × (TIME/DIV)
    frequency  = 1 / period
    amplitude  = (vertical divisions) × (VOLTS/DIV) × (probe attenuation)
    duty cycle = (divisions high / divisions per cycle) × 100 %

Input coupling should be DC so that the true LOW and HIGH voltage levels are displayed.

---

## 1. Reference voltage

| Quantity | Value | How obtained |
|---|---:|---|
| \(V_{\mathrm{ref}}\) (Arduino 5 V rail) | 5.00 V | Assumed nominal; not measured with DMM |
| One-count resolution \(\Delta V=V_{\mathrm{ref}}/1024\) | 4.8828 mV/count | Calculated |

Calculation:

\[
\Delta V
=\frac{5.00\ \mathrm{V}}{1024}
=0.0048828\ \mathrm{V}
=4.8828\ \mathrm{mV/count}.
\]

> All sketches in this repository use `/1024.0`. Therefore, the reported voltage
> corresponding to ADC code \(N\) is \(V=N(5.00/1024)\).

---

## 2. ADC range (sketch: `m01_adc_raw`)

The following values represent the ideal calculated ADC range. They were not obtained by
turning the potentiometer and observing the output.

| Quantity | ADC counts | Calculated voltage (V) |
|---|---:|---:|
| Minimum possible | 0 | 0.000 |
| Maximum possible | 1023 | 4.995 |
| Calculated midrange setting | 512 | 2.500 |

Calculations:

\[
V_{\min}=0\left(\frac{5.00}{1024}\right)=0.000\ \mathrm{V},
\]

\[
V_{\max}=1023\left(\frac{5.00}{1024}\right)=4.9951\ \mathrm{V},
\]

\[
V_{\mathrm{mid}}=512\left(\frac{5.00}{1024}\right)=2.500\ \mathrm{V}.
\]

Spread at the fixed midrange setting: **not measured**. In an ideal noiseless calculation,
the reading would remain at 512, giving a spread of 0 counts. A real Arduino will usually
wander among several neighboring integer codes because of electrical noise, reference-voltage
variation, and ADC quantization.

---

## 3. Blink timing (sketch: `m01_blink_ratio`; `LED_BUILTIN` pin 13 and external LED pin 9)

**Reported as calculated, not measured.** The timing values come from the sketch constants,
and the voltage levels are nominal ATmega328P digital-output levels.

| RATIO_CASE | Ratio | On (ms) | Off (ms) | Period (s) | Frequency (Hz) | Duty (%) | High (V) | Low (V) |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| 0 | 1:1 | 1000 | 1000 | 2.000 | 0.500 | 50.0 | 5.00 nominal | 0.00 nominal |
| 1 | 10:1 | 1000 | 100 | 1.100 | 0.909 | 90.9 | 5.00 nominal | 0.00 nominal |
| 2 | 1:10 | 100 | 1000 | 1.100 | 0.909 | 9.1 | 5.00 nominal | 0.00 nominal |

The calculations use

\[
T=t_{\mathrm{on}}+t_{\mathrm{off}},
\qquad
f=\frac{1}{T},
\qquad
D=\frac{t_{\mathrm{on}}}{T}\times100\%.
\]

### Calculated ten-cycle timing

| RATIO_CASE | High (V) | Low (V) | 10 cycles (s) | Period (s) | Duty (%) |
|---|---:|---:|---:|---:|---:|
| 0 | 5.00 nominal | 0.00 nominal | 20.000 | 2.000 | 50.0 |
| 1 | 5.00 nominal | 0.00 nominal | 11.000 | 1.100 | 90.9 |
| 2 | 5.00 nominal | 0.00 nominal | 11.000 | 1.100 | 9.1 |

Under the ideal calculation, the HIGH level is 5.00 V both with and without the LED
connected, so the calculated voltage sag is 0.00 V. Actual voltage sag cannot be determined
without measurement. The nominal excess delay is 0 ms, but real execution overhead also
requires measurement.

---

## 4. Timing of 1000 conversions (sketch: `m01_avg_timing`)

These values are calculated from the Arduino reference estimate of approximately
\(100\ \mu\mathrm{s}\) per `analogRead()` conversion.

| Quantity | Value |
|---|---:|
| Calculated time for 1000 `analogRead()` calls | approximately 100,000 µs |
| Calculated time per conversion | approximately 100 µs |
| Calculated conversions per second | approximately 10,000 s\(^{-1}\) |
| Arduino reference value | approximately 100 µs and 10,000 s\(^{-1}\) |
| Agreement? | Yes, by construction; actual timing was not measured |

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

Averaging improves precision but reduces time resolution because each reported average
represents approximately 0.10 s of measurements. It therefore acts as a low-pass filter:
rapid fluctuations are smoothed or delayed.

---

## 5. LED PWM (sketch: `m01_pwm_from_pot`, pin 9)

The following table gives two calculated operating points. The scope settings and graticule
divisions are reasonable theoretical display settings, not recorded measurements.

For Arduino Uno pin 9,

\[
f_{\mathrm{PWM}}
=\frac{16.0\times10^6}{64(510)}
=490.196\ \mathrm{Hz},
\]

so

\[
T_{\mathrm{PWM}}
=\frac{1}{490.196}
=2.040\ \mathrm{ms}.
\]

| Quantity | Setting A (low) | Setting B (high) |
|---|---:|---:|
| VOLTS/DIV | 1.00 V/div assumed | 1.00 V/div assumed |
| TIME/DIV | 0.500 ms/div assumed | 0.500 ms/div assumed |
| Probe attenuation | ×1 assumed | ×1 assumed |
| Calculated divisions per cycle | 4.080 div | 4.080 div |
| Calculated divisions HIGH | 1.024 div | 3.056 div |
| Calculated vertical divisions | 5.00 div | 5.00 div |
| Calculated averaged voltage | 1.255 V | 3.745 V |
| PWM value used | 64 | 191 |
| HIGH voltage | 5.00 V nominal | 5.00 V nominal |
| LOW voltage | 0.00 V nominal | 0.00 V nominal |
| Period | 2.040 ms | 2.040 ms |
| Frequency | 490.196 Hz | 490.196 Hz |
| Calculated duty cycle | 25.10% | 74.90% |
| Expected duty \(=\mathrm{PWM}/255\times100\%\) | 25.10% | 74.90% |
| Figure file | `m01_fig04_pwm_waveform.jpg` | A different Setting B image is still required |

Duty-cycle calculations:

\[
D_A=\frac{64}{255}\times100\%=25.10\%,
\]

\[
D_B=\frac{191}{255}\times100\%=74.90\%.
\]

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

\[
\text{Difference}
=\frac{|490.196-490|}{490}\times100\%
=0.040\%.
\]

The potentiometer changes the averaged input voltage, PWM command, HIGH-pulse duration,
duty cycle, average LED power, and apparent brightness. The HIGH and LOW voltage levels,
period, and frequency remain approximately fixed.

The LED appears continuously illuminated because the approximately 490 Hz PWM frequency is
far above the usual 50–60 Hz flicker-fusion range, although the oscilloscope can still resolve
the individual pulses.

---

## 6. Smallest discrete voltage jump

For an unaveraged 10-bit conversion using the nominal 5.00 V reference, the smallest
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
V_{\mathrm{ref}}/1024=4.8828\ \mathrm{mV},
\]

the ratio is

\[
\frac{4.8828}{4.8828}=1.000.
\]

This is the predicted value. The actual smallest jump in the Serial Plotter data must be
obtained from the raw capture.

For 1000 independent readings, the ideal standard-deviation ratio is

\[
\frac{\sigma_{1000}}{\sigma_1}
=\frac{1}{\sqrt{1000}}
=0.0316.
\]

The ideal effective-bit gain is

\[
\frac{1}{2}\log_2(1000)
\approx4.98\ \text{bits}.
\]

This improvement assumes a stable underlying voltage and sufficiently independent,
zero-mean fluctuations. Averaging improves precision but does not eliminate calibration
error or necessarily improve absolute accuracy.

---

## 7. What the oscilloscope showed that the serial displays did not

- The oscilloscope displays the electrical voltage at the output pin as a function of time,
  including the individual transitions between the nominal 0 V and 5 V levels. The Serial
  Monitor only displays numerical values reported by the program.

- The oscilloscope resolves the individual PWM pulses, their period, HIGH duration, LOW
  duration, and duty cycle. The Serial Plotter does not sample rapidly enough to reproduce
  the approximately 490 Hz switching waveform reliably.

- Changing the potentiometer primarily changes the width of the HIGH pulses and therefore
  the PWM duty cycle. The PWM frequency and HIGH and LOW voltage levels remain approximately
  fixed, showing that `analogWrite()` produces pulse-width modulation rather than a true
  continuously variable analog voltage.

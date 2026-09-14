# A1 — Module 1 Evidence Note

**Phys 39 — Instrumentation and Thermal Physics · Team TEC 8**

| | |
|---|---|
| **Assessment code** | A1 |
| **Team members** | Aferiat, Joshua; Yin, Tianren S. |
| **Experiment date** | September 3, 2026 |
| **Repository URL** | https://github.com/joshuaaferiat/LabModule1 |
| **Git checkpoint (GC) commit** | d599c5b6628bc05869fed1e465264807e7533028 |

> **Safety.** The Arduino was powered by USB only. The TEC power supply remained off for every measurement reported here.
>
> **Conventions.** Communication was conducted at 9600 baud. Voltage was calculated using
> `ADC counts × 5.00 / 1024`, so one count corresponds to 4.883 mV. The reference voltage
> was not measured; an assumed value of 5.00 V is used throughout this note. The
> oscilloscope probe was set to **×10**, so voltage measurements from the graticule include
> a factor of 10.

---

## 1. Apparatus

![Labeled apparatus](../../figures/module_01/m01_fig01_apparatus.jpg)

**Figure 1.** Module 1 apparatus. Arduino Uno (ELEGOO UNO R3) on USB power; 100 kΩ trimmer
potentiometer configured as a voltage divider into `A0`; LED with a 150 kΩ series resistor;
and oscilloscope probe. The thermistor, TEC 8 cold plate, and bench supply were present but
not powered.

**Wiring.** The potentiometer outer terminals were connected to `5V` and `GND`, and the
wiper was connected to `A0`. The built-in LED was driven by pin 13. The external LED
circuit was pin `9` → 150 kΩ resistor → LED → `GND`; the same LED was used in Parts 1
and 4. The oscilloscope was connected to CH2 with DC coupling, the ×10 probe tip was
connected to pin `9`, and the ground clip was connected to Arduino `GND`.

**Instrument.** BK Precision 2120B, 30 MHz dual-trace analog oscilloscope. It has no
cursors, automatic measurement readout, or screenshot export. Scope values were read
from the graticule and converted using the front-panel settings and ×10 probe factor.

The voltage conversion is

```math
\Delta V
=
(\text{vertical divisions})
(\text{VOLTS/DIV})
(10).
```

### 150 kΩ Series Resistor

The assignment specifies a resistor between 200 Ω and 4000 Ω, so the 150 kΩ resistor
used here is a departure from the assigned range. A suitable resistor in the assigned
range was not available during the recorded setup.

For a blue LED with approximately $V_f=3.1\ \mathrm{V}$ on a 5.00 V rail, the current is

```math
I
=
\frac{5.00\ \mathrm{V}-3.1\ \mathrm{V}}
{150\ \mathrm{k\Omega}}
\approx
13\ \mu\mathrm{A}.
```

This current is roughly forty times smaller than the current produced by the largest
resistor in the assigned range, making the LED brightness change difficult to observe
by eye.

The resistor does not materially affect the pin-voltage measurement because the
oscilloscope measures the output-pin voltage rather than LED current. At approximately
13 µA, the output driver is effectively unloaded, so little voltage sag is expected.

---

## 2. Code

| Sketch | Supports |
|---|---|
| [`m01_blink_ratio.ino`](../../firmware/module_01/m01_blink_ratio/m01_blink_ratio.ino) | §5 Blink |
| [`m01_adc_raw.ino`](../../firmware/module_01/m01_adc_raw/m01_adc_raw.ino) | §3 ADC |
| [`m01_adc_voltage.ino`](../../firmware/module_01/m01_adc_voltage/m01_adc_voltage.ino) | §3 voltage conversion |
| [`m01_avg_compare.ino`](../../firmware/module_01/m01_avg_compare/m01_avg_compare.ino) | §4 averaging |
| [`m01_avg_stats_onboard.ino`](../../firmware/module_01/m01_avg_stats_onboard/m01_avg_stats_onboard.ino) | §4 onboard statistics |
| [`m01_avg_timing.ino`](../../firmware/module_01/m01_avg_timing/m01_avg_timing.ino) | §4 acquisition time |
| [`m01_pwm_from_pot.ino`](../../firmware/module_01/m01_pwm_from_pot/m01_pwm_from_pot.ino) | §5 PWM |

Superseded variants are stored in
[`firmware/module_01/archive/`](../../firmware/module_01/archive/) and produced none of
the reported results.

**Provenance.** `m01_blink_ratio.ino` is a consolidated reconstruction. The lab work used
direct edits to the stock Arduino Blink example, and this file reproduces the three cases
using the same delay constants. The §3 captures were made with an earlier sketch that
printed bare integers rather than the `ADC:<n>` format used by the current file.

---

## 3. ADC Digitization

![ADC range sweep](../../figures/module_01/m01_fig08_adc_sweep.jpg)

**Figure 8.** Potentiometer swept across its travel. The visible Serial Monitor values
are 1022, 1022, 1022, 1023, 1022, 1022, and 1022.

![ADC dither](../../figures/module_01/m01_fig07_adc_dither.jpg)

**Figure 7.** Vertical axis expanded to 1015–1024 counts with the potentiometer
untouched. The figure shows one- to two-count fluctuations near the upper end of the
range.

| Quantity | Value | Basis |
|---|---:|---|
| Maximum count reached | **1023 = 4.995 V** | Measured, Figure 8 |
| Lowest count visible during sweep | **20 = 97.7 mV** | Measured mid-sweep; an upper bound on the endpoint minimum |
| Estimated lower endpoint | **approximately 0–2 counts = 0–9.77 mV** | Inferred from the divider connection to GND |
| Estimated midrange | **approximately 512 counts = 2.500 V** | Calculated midpoint of the ADC range |
| Estimated fixed-midrange range | **511–513 counts = 2.495–2.505 V** | Estimated from the observed one- to two-count dither |
| One-count step | **4.883 mV** | Calculated using the assumed 5.00 V reference |

The endpoint minimum and midrange were not preserved in photographs. The lower endpoint
and midrange values are therefore estimated from the voltage-divider configuration and
the observed ADC dither rather than reported as direct measurements.

### ADC Voltage Calculations

The one-count voltage step is

```math
\Delta V
=
\frac{5.00\ \mathrm{V}}{1024}
=
0.0048828\ \mathrm{V}
=
4.883\ \mathrm{mV}.
```

The maximum reported voltage using the sketch’s `/1024.0` conversion is

```math
V_{\max}
=
1023
\left(
\frac{5.00\ \mathrm{V}}{1024}
\right)
=
4.9951\ \mathrm{V}.
```

The lowest visible value corresponds to

```math
V_{20}
=
20
\left(
\frac{5.00\ \mathrm{V}}{1024}
\right)
=
0.09766\ \mathrm{V}.
```

The calculated midrange is

```math
V_{\mathrm{mid}}
=
512
\left(
\frac{5.00\ \mathrm{V}}{1024}
\right)
=
2.500\ \mathrm{V}.
```

The estimated midrange limits are

```math
V_{511}
=
511
\left(
\frac{5.00\ \mathrm{V}}{1024}
\right)
=
2.4951\ \mathrm{V},
```

and

```math
V_{513}
=
513
\left(
\frac{5.00\ \mathrm{V}}{1024}
\right)
=
2.5049\ \mathrm{V}.
```

### Why the Readings Occupy Discrete Levels

The ADC does not directly report a continuous voltage. It reports which of 1024
integer-code intervals contains the input voltage. The 0–5 V span is divided into
1024 intervals of approximately 4.883 mV each.

Every input within one interval produces the same code, so the output can only be one
of 1024 integer values. Printing `2.4561 V` instead of `503` rescales the integer into
volts but does not add physical information. The extra decimal places come from the
arithmetic and do not demonstrate finer single-conversion resolution.

The apparent smoothness of a plotted trace comes from the plotter drawing lines between
discrete samples, not from the ADC resolving intermediate values.

### Do the Values Vary When Nothing Is Touched?

Yes. Figures 7 and 8 show the reported code moving between neighboring values while the
potentiometer is untouched, with an observed spread of approximately one to two counts
or 5–10 mV.

Possible sources include thermal noise in the divider, ripple and switching noise on the
USB-derived 5 V rail, mains pickup on the leads, and the ADC comparator’s internal noise.

Because the divider uses a 100 kΩ potentiometer, its Thévenin source impedance reaches
25 kΩ at midrange. This exceeds the ATmega328P recommendation of approximately 10 kΩ or
less, leaving the sample-and-hold capacitor less time to settle and making the measurement
more susceptible to these effects.

This dither also enables averaging to improve effective precision. If every conversion
returned exactly the same ADC code, averaging would return that same code and could not
recover additional information. When neighboring codes are sampled, their relative
frequency contains information about the input voltage’s position between those codes.

### Serial Monitor Versus Serial Plotter

Serial Monitor gives the exact integer for every sample, making a one-count change
unambiguous. It also displays labels and other text. However, a scrolling column of
numbers makes it difficult to identify drift, oscillation, or longer-term behavior.

Serial Plotter shows the signal’s shape immediately. The expanded trace in Figure 7
makes the one- to two-count fluctuation visible at a glance, and a slow drift would
appear as a slope. However, the plotter does not clearly show the exact value of each
point and discards text that it cannot interpret as plotted numerical data.

The two displays therefore provide complementary information.

---

## 4. Averaging and Acquisition Time

### Available-Data Estimate

The required 100-point unaveraged and averaged captures were not saved. However,
Figure 8 contains the following seven visible ADC readings:

`1022, 1022, 1022, 1023, 1022, 1022, 1022`

These values permit a limited estimate of the unaveraged mean and sample standard
deviation. The calculation is based on seven samples rather than the required
100-point data block.

The mean ADC code is

```math
\overline{N}
=
\frac{6(1022)+1023}{7}
=
1022.1429.
```

Using the assumed 5.00 V reference, the corresponding mean voltage is

```math
\overline{V}
=
1022.1429
\left(
\frac{5.00\ \mathrm{V}}{1024}
\right)
=
4.99093\ \mathrm{V}.
```

The sample standard deviation of the seven ADC codes is

```math
s_N
=
\sqrt{
\frac{
\sum_{i=1}^{7}(N_i-\overline{N})^2
}{
7-1
}
}
=
0.37796\ \mathrm{count}.
```

Converting the sample standard deviation to voltage gives

```math
s_V
=
(0.37796\ \mathrm{count})
\left(
\frac{4.8828\ \mathrm{mV}}{\mathrm{count}}
\right)
=
1.846\ \mathrm{mV}.
```

| Data block | Available points | Readings averaged per point, $N$ | Mean voltage | Standard deviation | Ratio to unaveraged |
|---|---:|---:|---:|---:|---:|
| Observed unaveraged subset | 7 | 1 | **4.99093 V** | **1.846 mV** | 1.000 |
| Predicted long average | Predicted only | 1000 | **4.99093 V** | **0.0584 mV** | 0.0316 |

The observed transition between ADC codes 1022 and 1023 establishes a smallest observed
nonzero voltage jump of one ADC count:

```math
\Delta V_{\min}
=
\frac{5.00\ \mathrm{V}}{1024}
=
4.8828\ \mathrm{mV}.
```

[`analysis/module_01/averaging_stats.py`](../../analysis/module_01/averaging_stats.py)
can calculate the required table directly if a complete raw capture becomes available.

### Why Averaging Improves Precision

Suppose each conversion has independent random error with standard deviation
$\sigma_1$. For an average of $N$ independent measurements, the standard deviation of
the mean is

```math
\sigma_N
=
\frac{\sigma_1}{\sqrt{N}}.
```

Therefore,

```math
\frac{\sigma_N}{\sigma_1}
=
\frac{1}{\sqrt{N}}.
```

For $N=1000$,

```math
\frac{\sigma_{1000}}{\sigma_1}
=
\frac{1}{\sqrt{1000}}
=
0.0316.
```

Applying this prediction to the seven-point estimate gives

```math
\sigma_{1000}
=
\frac{1.846\ \mathrm{mV}}{\sqrt{1000}}
=
0.0584\ \mathrm{mV}.
```

The ideal number of effective bits gained is

```math
\text{bits gained}
=
\log_2(\sqrt{N})
=
\frac{1}{2}\log_2(N).
```

For $N=1000$,

```math
\text{bits gained}
=
\frac{1}{2}\log_2(1000)
=
\frac{1}{2}(9.966)
=
4.98
\approx
5\ \text{bits}.
```

Under suitable conditions, averaging can therefore allow a 10-bit ADC to report an
estimate with approximately 15 bits of effective precision.

This prediction requires the following assumptions:

- The underlying voltage remains constant during the averaging interval.
- The fluctuations have approximately zero mean.
- Successive measurement errors are sufficiently independent.
- There is enough analog noise or dither to sample neighboring ADC codes.

Correlated errors do not decrease as $1/\sqrt{N}$. For example, correlated 60 Hz mains
pickup may remain after averaging instead of canceling.

### Precision Is Not Accuracy

Averaging reduces random scatter around the value reported by the instrument. It does
not remove systematic calibration error.

For example, if the actual reference voltage were 4.93 V while the sketch assumed
5.00 V, the fractional calibration difference would be

```math
\frac{5.00-4.93}{5.00}
\times
100\%
=
1.4\%.
```

No amount of averaging would remove this difference. The averaged values could have
less scatter while remaining systematically incorrect. This is why the unmeasured
reference voltage remains a limitation of this analysis.

### Acquisition-Time Reconstruction

The Arduino Uno uses a 16 MHz system clock. With the default ADC prescaler of 128,
the ADC clock is

```math
f_{\mathrm{ADC}}
=
\frac{16\ \mathrm{MHz}}{128}
=
125\ \mathrm{kHz}.
```

A standard ADC conversion requires approximately 13 ADC clock cycles. Therefore,

```math
t_{\mathrm{conversion}}
=
\frac{13}{125\,000\ \mathrm{s}^{-1}}
=
104\ \mu\mathrm{s}.
```

For 1000 conversions,

```math
t_{1000}
=
1000
(104\ \mu\mathrm{s})
=
104\,000\ \mu\mathrm{s}
=
0.104\ \mathrm{s}.
```

The corresponding conversion rate is

```math
f_{\mathrm{conversion}}
=
\frac{1000}{0.104\ \mathrm{s}}
\approx
9615\ \mathrm{conversions/s}.
```

| Quantity | Reconstructed value | Basis |
|---|---:|---|
| Time for 1000 conversions | **approximately 104,000 µs** | ADC clock calculation |
| Time per conversion | **approximately 104 µs** | 13 cycles at 125 kHz |
| Conversion rate | **approximately 9615 conversions/s** | Calculated |
| Additional software overhead | Not included | Requires a direct `micros()` result |

The elapsed time returned by `micros()` would be slightly longer because `analogRead()`
contains function and loop overhead. The value of 104,000 µs represents the ADC
conversion time reconstructed from the microcontroller clock configuration.

### Averaging as a Low-Pass Filter

Averaging 1000 consecutive samples produces an averaging interval of approximately
0.104 s. This operation acts as a boxcar low-pass filter.

Rapid fluctuations tend to cancel, producing the improvement in precision. However, a
real change occurring during the averaging interval is smoothed and delayed. Frequency
components near and above approximately 10 Hz are strongly attenuated, and the reported
value is delayed by approximately half the averaging interval.

This tradeoff is central to the instrument being developed. A temperature controller
that averages heavily may read its sensor more precisely but respond to disturbances
later. A control loop acting on delayed information may overshoot or oscillate.

Choosing $N$ therefore means balancing a noisy, fast response against a quieter,
slower response.

---

## 5. Digital Output and PWM

### Blink — Reconstructed from Programmed Timing

![Part 1 bench](../../figures/module_01/m01_fig06_part1_bench.jpg)

**Figure 6.** Part 1 bench and components. This image documents the setup. The external
LED is not wired in the photograph and the oscilloscope screen is blank, so the image
does not independently document the timing measurements.

The sketch began as the stock Arduino Blink example and was modified to drive an
external LED on pin 9 alongside `LED_BUILTIN`. A constant selects the HIGH-to-LOW
timing ratio.

The timing values were reconstructed from the programmed `delay()` constants. The HIGH
and LOW levels were calculated using 5.00 V and 0.00 V. No independent oscilloscope
timing record was preserved.

| `RATIO_CASE` | Ratio | On/off (ms) | Period (s) | Frequency (Hz) | Duty cycle | High/Low (V) |
|---|---|---:|---:|---:|---:|---:|
| 0 | 1:1 | 1000/1000 | 2.000 | 0.500 | 50.0% | 5.0/0.0 |
| 1 | 10:1 | 1000/100 | 1.100 | 0.909 | 90.9% | 5.0/0.0 |
| 2 | 1:10 | 100/1000 | 1.100 | 0.909 | 9.1% | 5.0/0.0 |

The calculations use

```math
T
=
t_{\mathrm{on}}
+
t_{\mathrm{off}},
```

```math
f
=
\frac{1}{T},
```

and

```math
D
=
\frac{t_{\mathrm{on}}}{T}
\times
100\%.
```

One delay was held at 1000 ms while the other was changed. Therefore, the period and
frequency change between the 1:1 case and the other two cases, in addition to the change
in duty cycle. The 10:1 and 1:10 cases have the same period and frequency but different
duty cycles.

The calculated periods are lower bounds because `delay()` blocks for at least the
requested interval while `digitalWrite()` and loop overhead add a small amount of time.

### Analog-Scope Persistence Limitation

At 0.5–0.9 Hz, a single Blink period is comparable to or longer than the BK Precision
2120B’s complete slowest sweep:

```math
(0.1\ \mathrm{s/div})
(10\ \mathrm{div})
=
1.0\ \mathrm{s}.
```

At this sweep rate, the CRT spot moves slowly across the screen and the phosphor fades
before a complete persistent trace forms. The PWM waveform is approximately three
orders of magnitude faster and therefore produces a persistent trace.

### PWM — Part 4

![Part 4 wiring](../../figures/module_01/m01_fig09_part4_wiring.jpg)

**Figure 9.** Bench wiring used for Part 4.

![PWM setting A](../../figures/module_01/m01_fig04b_pwm_measured.jpg)

**Figure 4b.** Setting A. The graticule was calibrated using ten grid spacings measured
from the photograph: 97, 96, 95, 96, 95, 95, 95, 95, 95, and 96 pixels. This gives
approximately 95.0 pixels per division. The spacing is uniform to approximately ±1%,
so perspective distortion is small.

![PWM setting A, fast sweep](../../figures/module_01/m01_fig05b_pwm_measured_fast.jpg)

**Figure 5b.** The same PWM signal at a faster sweep speed, providing an independent
check of Figure 4b.

![PWM setting B](../../figures/module_01/m01_fig10b_pwm_settingB_measured.jpg)

**Figure 10b.** Setting B.

| Quantity | Setting A | Setting B | Basis |
|---|---:|---:|---|
| **Duty cycle** | **64%** | **25%** | Measured ratio; independent of probe factor and knob calibration |
| Period | 4.13 div | 2.72 div | Measured from the photographs |
| Amplitude | 1.05 div | 2.58 div | Measured from the photographs |
| Probe attenuation | ×10 | ×10 | Probe setting |
| VOLTS/DIV | 0.5 V/div | 0.2 V/div | Reconstructed from the division count and approximately 5 V swing |
| High/Low voltage | approximately 5.3/0 V | approximately 5.2/0 V | Calculated using the ×10 probe factor |
| Implied `analogWrite()` value | approximately 163/255 | approximately 63/255 | Inferred from duty cycle |
| Implied averaged input voltage | approximately 3.20 V | approximately 1.24 V | Inferred through `map()` and ADC conversion |
| TIME/DIV | 0.500 ms/div | **0.750 ms/div** | A from calibrated scale; B reconstructed from Timer1 period |
| Period in time | 2.065 ms | **2.040 ms** | Calculated from divisions and effective TIME/DIV |
| **Frequency** | **484.3 Hz** | **490.2 Hz** | A from the scope scale; B reconstructed from Timer1 timing |

### Voltage Calculation with the ×10 Probe

For Setting A,

```math
V_{\mathrm{pp},A}
=
(1.05\ \mathrm{div})
(0.5\ \mathrm{V/div})
(10)
=
5.25\ \mathrm{V}.
```

Therefore, the Setting A HIGH and LOW levels are approximately 5.3 V and 0 V.

For Setting B,

```math
V_{\mathrm{pp},B}
=
(2.58\ \mathrm{div})
(0.2\ \mathrm{V/div})
(10)
=
5.16\ \mathrm{V}.
```

Therefore, the Setting B HIGH and LOW levels are approximately 5.2 V and 0 V.

### Setting A Frequency

For Setting A,

```math
T_A
=
(4.13\ \mathrm{div})
(0.500\ \mathrm{ms/div})
=
2.065\ \mathrm{ms}.
```

Thus,

```math
f_A
=
\frac{1}
{2.065\times10^{-3}\ \mathrm{s}}
=
484.3\ \mathrm{Hz}.
```

Compared with the expected 490.2 Hz,

```math
\text{percentage difference}
=
\frac{|484.3-490.2|}
{490.2}
\times
100\%
\approx
1.2\%.
```

Figures 4b and 5b were photographed at different sweep speeds and give consistent
periods to approximately 0.2%. Agreement with the expected frequency supports the
0.500 ms/div interpretation.

### Setting B Timebase Reconstruction

The Arduino Uno pin-9 PWM frequency is set by Timer1. Using the standard timer
configuration, the expected PWM frequency is approximately 490.2 Hz. Therefore, the
corresponding period is

```math
T_B
=
\frac{1}
{490.196\ \mathrm{Hz}}
=
2.040\ \mathrm{ms}.
```

The Setting B photograph shows one period spanning 2.72 horizontal divisions. The
effective TIME/DIV value is therefore reconstructed as

```math
\left(
\frac{\mathrm{TIME}}
{\mathrm{DIV}}
\right)_B
=
\frac{T_B}
{N_{\mathrm{cycle},B}}
=
\frac{2.040\ \mathrm{ms}}
{2.72\ \mathrm{div}}
=
0.750\ \mathrm{ms/div}.
```

Using this reconstructed timebase,

```math
T_B
=
(2.72\ \mathrm{div})
(0.750\ \mathrm{ms/div})
=
2.040\ \mathrm{ms},
```

and

```math
f_B
=
\frac{1}
{2.040\times10^{-3}\ \mathrm{s}}
=
490.2\ \mathrm{Hz}.
```

Thus, the effective timebase during the Setting B photograph was reconstructed as
**0.750 ms/div**, giving a period of **2.040 ms** and a frequency of **490.2 Hz**.

The most likely explanation for the nonstandard effective scale is that the variable
timebase control was not positioned at its calibrated detent. Because the timebase was
reconstructed using the expected Timer1 frequency, the Setting B frequency is
timer-derived rather than an independent frequency measurement.

### Which Quantities Change and Which Remain Fixed?

After accounting for the different oscilloscope scales, the two settings are consistent
with approximately the same 5.2 V amplitude and approximately the same 2.04 ms PWM
period.

The potentiometer changed the duty cycle from 64% to 25%. The HIGH and LOW voltage
levels and timer-controlled frequency remained approximately fixed.

This is consistent with the microcontroller operation. The PWM period is determined by
the timer, prescaler, and 16 MHz clock. `analogWrite()` changes the timer compare value
and therefore changes the duty cycle rather than the timer frequency.

### Why the LED Looks Continuously Lit

At approximately 485–490 Hz, the LED switches on and off nearly 500 times each second.
This is approximately an order of magnitude above the common 50–60 Hz flicker-fusion
range, so the visual system integrates the pulses into a continuous apparent brightness.
The oscilloscope does not perform this visual integration and therefore displays the
individual pulses.

Flicker fusion is not one universal frequency. It depends on brightness, contrast,
peripheral versus central vision, the apparent size of the source, and the observer.
Therefore, 50–60 Hz is an approximate reference range rather than a universal threshold.

### Precision Through the Signal Chain

`m01_pwm_from_pot` averages 1000 ADC readings and then converts the result to `int`
before applying `map(..., 0, 1023, 0, 255)`.

The additional effective precision obtained through averaging cannot survive unchanged
in an 8-bit actuator command because the PWM output has only 256 command levels.
Precision at the sensor therefore does not automatically become precision at the
actuator.

This is an important instrument-design constraint that will matter when the same signal
chain controls the TEC.

### What the Oscilloscope Showed That the Serial Displays Did Not

The essential distinction is between a direct electrical measurement of the output pin
and values selected and printed by software. Serial Monitor and Serial Plotter report
samples acquired and processed by the sketch at the rate selected by the program. The
oscilloscope displays the voltage on the wire using its own independent timebase.

The serial displays could not show the approximately 2 ms PWM period because
communication at 9600 baud, together with program execution and delays, produces reports
at only a few tens of hertz. This is several orders of magnitude slower than the PWM
waveform. The serial output also reports the commanded duty value rather than directly
measuring the waveform produced by the pin.

The oscilloscope resolved the individual pulses, HIGH and LOW voltage levels, duty
cycle, and period. It therefore showed whether the hardware produced the waveform
requested by the software. The serial output shows what the software believes or
commands, whereas the oscilloscope shows what the electrical hardware produces.

---

## 6. C1 Question 9 — Arduino Uno Analog Input

The Arduino Uno analog input is a successive-approximation ADC that measures **voltage**.
It does not directly measure current or resistance, although a voltage-divider circuit
can convert resistance into a measurable voltage.

The ADC measures relative to a reference voltage. In this experiment, the input range
is treated as 0–5.00 V. An input at or above the reference saturates at the maximum code.

The converter is **10-bit**, so it divides the input range into

```math
2^{10}
=
1024
```

levels and reports integer codes from **0 to 1023**.

One count corresponds to

```math
\Delta V
=
\frac{V_{\mathrm{ref}}}{1024}
=
\frac{5.00\ \mathrm{V}}{1024}
\approx
4.88\ \mathrm{mV}.
```

A conversion takes approximately 104 µs, giving a conversion rate of approximately

```math
f
=
\frac{1}
{104\times10^{-6}\ \mathrm{s}}
\approx
9615\ \mathrm{samples/s}.
```

The practical reporting rate is lower because `Serial.print()` and any `delay()`
statements add time.

Six analog channels, A0–A5, share one converter through an analog multiplexer. The
channels are sampled sequentially rather than simultaneously, and the sample-and-hold
capacitor must settle after switching channels.

The microcontroller documentation recommends a source impedance of approximately
**10 kΩ or less** because the sample-and-hold capacitor must charge through the source
impedance during a limited sampling interval.

The 100 kΩ potentiometer divider used here reaches a Thévenin impedance of 25 kΩ at
midrange and therefore exceeds that recommendation. This is a limitation of the
assigned circuit.

---

## 7. C1 Question 10 — Arduino Uno PWM Output

A PWM output is a **digital** pin that switches rapidly between approximately 0 V and
5 V. It is controlled using `analogWrite(pin, value)`, where `value` ranges from
**0 to 255**.

The command determines the duty cycle:

```math
D
=
\frac{\text{value}}
{255}
\times
100\%.
```

The switching frequency is set by the timer hardware. On the Arduino Uno, it is
approximately **490 Hz** on pins 3, 9, 10, and 11 and approximately 980 Hz on pins 5
and 6.

### PWM Is Not a True Analog Voltage

At each instant, the output pin is at either its LOW or HIGH voltage. It does not remain
at an intermediate voltage. What changes is the fraction of each period spent HIGH.

The average voltage over a period is approximately

```math
V_{\mathrm{avg}}
=
D V_{\mathrm{HIGH}},
```

where $D$ is written as a fraction between 0 and 1.

This average becomes physically meaningful when a load integrates the pulses. Examples
include an RC low-pass filter, the thermal mass of a heater, the mechanical inertia of a
motor, or persistence of vision when viewing an LED.

An oscilloscope shows the individual square-wave pulses. A slower DC voltmeter may
report their average. Both observations describe the same signal at different time
resolutions.

### Why a Power Stage Is Required

An ATmega328P output pin can supply only tens of milliamperes at approximately 5 V,
corresponding to tens of milliwatts. A motor or TEC may require several amperes from a
separate supply. Connecting such a load directly to the Arduino pin could damage the
microcontroller.

An H-bridge serves as the power stage. The low-power Arduino logic signal controls a
high-current path from the external supply through the load, allowing the
microcontroller to control the power without carrying the load current directly.

The H-bridge also permits current to flow in either direction through the load. This is
essential for a TEC because reversing the current exchanges the hot and cold faces. The
controller can therefore use one actuator for both heating and cooling.$V_f=3.1\ \mathrm{V}$ on a 5.00 V rail, the current is

```math
I
=
\frac{5.00\ \mathrm{V}-3.1\ \mathrm{V}}
{150\ \mathrm{k\Omega}}
\approx 13\ \mu\mathrm{A}.
```

This is roughly forty times smaller than the current produced by the largest resistor in
the assigned range, making the Part 4 brightness change difficult to see by eye. It does
not materially affect the reported pin-voltage measurement because the oscilloscope reads
the output-pin voltage rather than LED current. At approximately 13 µA, the output driver
is effectively unloaded, so little voltage sag is expected.

---

## 2. Code

| Sketch | Supports |
|---|---|
| [`m01_blink_ratio.ino`](../../firmware/module_01/m01_blink_ratio/m01_blink_ratio.ino) | §5 Blink |
| [`m01_adc_raw.ino`](../../firmware/module_01/m01_adc_raw/m01_adc_raw.ino) | §3 ADC |
| [`m01_adc_voltage.ino`](../../firmware/module_01/m01_adc_voltage/m01_adc_voltage.ino) | §3 conversion |
| [`m01_avg_compare.ino`](../../firmware/module_01/m01_avg_compare/m01_avg_compare.ino) | §4 averaging |
| [`m01_avg_stats_onboard.ino`](../../firmware/module_01/m01_avg_stats_onboard/m01_avg_stats_onboard.ino) | §4 onboard statistics |
| [`m01_avg_timing.ino`](../../firmware/module_01/m01_avg_timing/m01_avg_timing.ino) | §4 acquisition time |
| [`m01_pwm_from_pot.ino`](../../firmware/module_01/m01_pwm_from_pot/m01_pwm_from_pot.ino) | §5 PWM |

Superseded variants are stored in
[`firmware/module_01/archive/`](../../firmware/module_01/archive/) and produced none of
the reported results.

**Provenance.** `m01_blink_ratio.ino` is a consolidated reconstruction. The lab work used
direct edits to the stock Arduino Blink example, and this file reproduces the three cases
using the same delay constants. The §3 captures were made with an earlier sketch that
printed bare integers rather than the `ADC:<n>` format used by the current file.

---

## 3. ADC Digitization

![ADC range sweep](../../figures/module_01/m01_fig08_adc_sweep.jpg)

**Figure 8.** Potentiometer swept across its travel. Serial Monitor displays 1022, 1022,
1022, 1023, 1022, 1022, and 1022.

![ADC dither](../../figures/module_01/m01_fig07_adc_dither.jpg)

**Figure 7.** Vertical axis expanded to 1015–1024 counts with the potentiometer untouched.

| Quantity | Value | Source |
|---|---:|---|
| Maximum count reached | **1023 = 4.995 V** | Measured, Figure 8 |
| Lowest count observed | **20 = 97.7 mV** | Measured mid-sweep; an **upper bound** on the minimum, not the actual minimum |
| Dither at a fixed setting | **1–2 counts ≈ 5–10 mV** | Measured, Figures 7 and 8 |
| One-count step, $\Delta V=V_{\mathrm{ref}}/1024$ | **4.883 mV** | Calculated using the assumed 5.00 V reference |

The one-count voltage step is

```math
\Delta V
=
\frac{5.00\ \mathrm{V}}{1024}
=
0.0048828\ \mathrm{V}
=
4.883\ \mathrm{mV}.
```

The maximum reported voltage using the sketch’s `/1024.0` conversion is

```math
V_{\max}
=
1023\left(\frac{5.00\ \mathrm{V}}{1024}\right)
=
4.9951\ \mathrm{V}.
```

The lowest observed value corresponds to

```math
V_{20}
=
20\left(\frac{5.00\ \mathrm{V}}{1024}\right)
=
0.09766\ \mathrm{V}.
```

### Why the Readings Occupy Discrete Levels

The ADC does not directly report a voltage. It reports which of 1024 integer-code
intervals contains the input voltage. The 0–5 V span is divided into 1024 intervals of
approximately 4.883 mV each. Every input within one interval produces the same code, and
the output can only be one of 1024 integer values.

Printing `2.4561 V` instead of `503` rescales the integer into volts but adds no physical
information. The underlying conversion still has only 1024 possible outcomes. The extra
decimal places come from the arithmetic and do not demonstrate finer single-conversion
resolution. The apparent smoothness of a plotted trace comes from the plotter drawing
lines between discrete samples.

### Do the Values Vary When Nothing Is Touched?

Yes. Both figures show the reported code moving between 1022 and 1023 while the
potentiometer is untouched, occasionally spanning approximately two counts or 5–10 mV.

Possible sources include thermal noise in the divider, ripple and switching noise on the
USB-derived 5 V rail, mains pickup on the leads, and the ADC comparator’s internal noise.
Because the divider uses a 100 kΩ potentiometer, its Thévenin source impedance reaches
25 kΩ at midrange. This exceeds the ATmega328P recommendation of approximately 10 kΩ or
less, leaving the sample-and-hold capacitor less time to settle and making the measurement
more susceptible to these effects.

This dither is also necessary for the averaging experiment. If the input were perfectly
stable and every conversion returned the same code, averaging would return that same code
and could not recover additional information. When neighboring codes are sampled, the
fraction of readings occupying each code contains information about the input’s position
between those codes.

### Serial Monitor Versus Serial Plotter

Serial Monitor gives the exact integer for every sample, making a one-count change
unambiguous. It also displays labels and other text. However, a scrolling column of
numbers makes it difficult to identify drift, oscillation, or longer-term behavior.

Serial Plotter shows the signal’s shape immediately. The expanded trace in Figure 7 makes
the one- to two-count variation visible at a glance, and a slow drift would appear as a
slope. However, the plotter does not clearly show the exact value of each point and
discards text that it cannot interpret as plotted numerical data. The two displays
therefore provide complementary information.

---

## 4. Averaging and Acquisition Time

### Available-Data Estimate

The required 100-point unaveraged and averaged captures were not saved. However, Figure 8
contains the following seven visible ADC readings:

`1022, 1022, 1022, 1023, 1022, 1022, 1022`

These values permit a limited empirical estimate of the unaveraged mean and sample standard
deviation. The estimate is based on seven samples rather than the required 100 samples and
is identified accordingly.

The mean ADC code is

```math
\overline{N}
=
\frac{6(1022)+1023}{7}
=
1022.1429.
```

Using the assumed 5.00 V reference, the corresponding mean voltage is

```math
\overline{V}
=
1022.1429
\left(
\frac{5.00\ \mathrm{V}}{1024}
\right)
=
4.99093\ \mathrm{V}.
```

For the seven observed codes, the sample standard deviation is

```math
s_N
=
\sqrt{
\frac{
\sum_{i=1}^{7}(N_i-\overline{N})^2
}{
7-1
}
}
=
0.37796\ \mathrm{count}.
```

Converting this result to voltage gives

```math
s_V
=
(0.37796\ \mathrm{count})
\left(
\frac{4.8828\ \mathrm{mV}}{\mathrm{count}}
\right)
=
1.846\ \mathrm{mV}.
```

| Data block | Available points | Readings averaged per point, $N$ | Mean voltage | Standard deviation | Ratio to unaveraged |
|---|---:|---:|---:|---:|---:|
| Observed unaveraged subset | 7 | 1 | **4.99093 V** | **1.846 mV** | 1.000 |
| Predicted long average | Predicted only | 1000 | **4.99093 V** | **0.0584 mV** | 0.0316 |

The predicted standard deviation for a 1000-reading average is

```math
\sigma_{1000}
=
\frac{\sigma_1}{\sqrt{1000}}
=
\frac{1.846\ \mathrm{mV}}{\sqrt{1000}}
=
0.0584\ \mathrm{mV}.
```

Therefore,

```math
\frac{\sigma_{1000}}{\sigma_1}
=
\frac{0.0584}{1.846}
=
0.0316.
```

The observed transition between ADC codes 1022 and 1023 also establishes that the smallest
observed nonzero voltage jump was one ADC count:

```math
\Delta V_{\min}
=
\frac{5.00\ \mathrm{V}}{1024}
=
4.8828\ \mathrm{mV}.
```

### Acquisition-Time Estimate

The Arduino reference gives approximately 100 µs per `analogRead()` conversion. Therefore,
the estimated acquisition time for 1000 conversions is

```math
t_{1000}
=
1000(100\ \mu\mathrm{s})
=
100{,}000\ \mu\mathrm{s}
=
0.100\ \mathrm{s}.
```

The corresponding conversion rate is

```math
f_{\mathrm{conversion}}
=
\frac{1000}{0.100\ \mathrm{s}}
=
10{,}000\ \mathrm{conversions/s}.
```

| Quantity | Derived value | Status |
|---|---:|---|
| Mean of the seven visible unaveraged readings | 4.99093 V | Calculated from Figure 8 |
| Sample standard deviation of those readings | 1.846 mV | Calculated from Figure 8 |
| Smallest observed nonzero jump | 4.8828 mV | One ADC count |
| Predicted standard deviation after averaging 1000 readings | 0.0584 mV | Statistical prediction |
| Time for 1000 conversions | approximately 100,000 µs | Arduino reference estimate |
| Time per conversion | approximately 100 µs | Arduino reference estimate |
| Conversion rate | approximately 10,000 conversions/s | Arduino reference estimate |

These calculations show the expected scale of the averaging improvement and acquisition
time. They do not constitute the missing 100-point averaged measurement or a direct
`micros()` timing result.

### Why Averaging Improves Precision

Suppose each conversion has independent random error with standard deviation $\sigma_1$.
For an average of $N$ independent measurements, the standard deviation of the mean is

```math
\sigma_N
=
\frac{\sigma_1}{\sqrt{N}}.
```

Therefore,

```math
\frac{\sigma_N}{\sigma_1}
=
\frac{1}{\sqrt{N}}.
```

For $N=1000$,

```math
\frac{\sigma_{1000}}{\sigma_1}
=
\frac{1}{\sqrt{1000}}
=
0.0316.
```

The ideal number of effective bits gained is

```math
\text{bits gained}
=
\log_2(\sqrt{N})
=
\frac{1}{2}\log_2(N).
```

For $N=1000$,

```math
\text{bits gained}
=
\frac{1}{2}\log_2(1000)
=
\frac{1}{2}(9.966)
=
4.98
\approx 5\ \text{bits}.
```

Under suitable conditions, averaging can therefore allow a 10-bit ADC to report an
estimate with approximately 15 bits of effective precision.

The calculation requires several assumptions:

- The underlying voltage must remain constant during the averaging interval.
- The fluctuations must have approximately zero mean.
- Successive errors must be sufficiently independent.
- There must be enough analog noise or dither to sample neighboring ADC codes.

Correlated errors do not decrease as $1/\sqrt{N}$. For example, correlated 60 Hz mains
pickup can remain after averaging instead of canceling.

### Precision Is Not Accuracy

Averaging reduces random scatter around the value reported by the instrument. It does
not remove systematic error. For example, if the actual reference voltage were 4.93 V
while the sketch assumed 5.00 V, the fractional calibration difference would be

```math
\frac{5.00-4.93}{5.00}\times100\%
=
1.4\%.
```

No amount of averaging would remove this difference. The averaged values could have less
scatter while remaining systematically incorrect. This is why measuring the reference
voltage is important and why the unmeasured reference is a limitation of this note.

### Time Cost: Averaging as a Low-Pass Filter

The Arduino reference gives approximately 100 µs per `analogRead()` conversion, or about
10 kSa/s. The calculated time for 1000 readings is therefore

```math
t_{1000}
=
1000(100\ \mu\mathrm{s})
=
100{,}000\ \mu\mathrm{s}
=
0.10\ \mathrm{s}.
```

This does not include arithmetic or Serial output time.

Averaging 1000 consecutive samples acts as a boxcar filter with a width of approximately
0.10 s. Rapid fluctuations tend to cancel, producing the precision improvement, but a
real change occurring during the averaging window is smoothed and delayed. Frequency
components near and above approximately 10 Hz are strongly attenuated, and the reported
value is delayed by approximately half the averaging interval.

This tradeoff is central to the instrument being developed. A temperature controller
that averages heavily may read its sensor more precisely but respond to disturbances
later. A control loop acting on delayed information may overshoot or oscillate. Choosing
$N$ therefore means balancing a noisy, fast response against a quieter, slower response.

---

## 5. Digital Output and PWM

### Blink — Part 1

![Part 1 bench](../../figures/module_01/m01_fig06_part1_bench.jpg)

**Figure 6.** Part 1 bench and components. This image documents the setup only. The
external LED is not wired in this photograph and the oscilloscope screen is blank, so the
image does not demonstrate that the circuit was running.

The sketch began as the stock Arduino Blink example and was modified to drive an
external LED on pin 9 alongside `LED_BUILTIN`. A constant selects the HIGH-to-LOW timing
ratio. The timing values below come from the programmed delay constants. The voltage
values are calculated using 5.00 V for HIGH and 0.00 V for LOW. These values were not
measured.

| `RATIO_CASE` | Ratio | On/off (ms) | Period (s) | Frequency (Hz) | Duty (%) | High/Low (V) |
|---|---|---:|---:|---:|---:|---:|
| 0 | 1:1 | 1000 / 1000 | 2.000 | 0.500 | 50.0 | 5.0 / 0.0 |
| 1 | 10:1 | 1000 / 100 | 1.100 | 0.909 | 90.9 | 5.0 / 0.0 |
| 2 | 1:10 | 100 / 1000 | 1.100 | 0.909 | 9.1 | 5.0 / 0.0 |

The calculations use

```math
T
=
t_{\mathrm{on}}+t_{\mathrm{off}},
```

```math
f
=
\frac{1}{T},
```

and

```math
D
=
\frac{t_{\mathrm{on}}}{T}\times100\%.
```

One delay was held at the stock 1000 ms while the other was changed. Therefore, period
and frequency change between the 1:1 case and the other two cases, in addition to the
change in duty cycle. The 10:1 and 1:10 cases have the same period and frequency but
different duty cycles.

The calculated periods should be treated as lower bounds. `delay()` blocks for at least
the requested interval, while `digitalWrite()` and loop overhead add a small amount of
time. The true periods should therefore be slightly longer than 2.000 s and 1.100 s.

**No oscilloscope figure was obtained for Blink.** At 0.5–0.9 Hz, a single period is
longer than the BK Precision 2120B’s entire slowest sweep:

```math
(0.1\ \mathrm{s/div})(10\ \mathrm{div})
=
1.0\ \mathrm{s}.
```

At that sweep rate, the CRT spot moves slowly across the screen and the phosphor fades
before a complete persistent trace forms. The PWM waveform below is approximately three
orders of magnitude faster and therefore produces a persistent trace.

### PWM — Part 4, Measured

![Part 4 wiring](../../figures/module_01/m01_fig09_part4_wiring.jpg)

**Figure 9.** Bench wiring used for Part 4.

![PWM setting A](../../figures/module_01/m01_fig04b_pwm_measured.jpg)

**Figure 4b.** Setting A. The graticule was calibrated using ten grid spacings measured
from the photograph: 97, 96, 95, 96, 95, 95, 95, 95, 95, and 96 pixels. This gives
approximately 95.0 pixels per division. The spacing is uniform to approximately ±1%, so
perspective distortion is small.

![PWM setting A, fast sweep](../../figures/module_01/m01_fig05b_pwm_measured_fast.jpg)

**Figure 5b.** The same PWM signal at a faster sweep speed, providing an independent
check of Figure 4b.

![PWM setting B](../../figures/module_01/m01_fig10b_pwm_settingB_measured.jpg)

**Figure 10b.** Setting B.

| Quantity | Setting A | Setting B | Basis |
|---|---:|---:|---|
| **Duty cycle** | **64%** | **25%** | Measured ratio; independent of probe factor and knob calibration |
| Period | 4.13 div | 2.72 div | Measured from graticule |
| Amplitude | 1.05 div | 2.58 div | Measured from graticule |
| Probe attenuation | ×10 | ×10 | Probe setting |
| VOLTS/DIV | 0.5 V/div | 0.2 V/div | Inferred from the measured divisions and approximately 5 V logic swing |
| High/Low voltage | approximately 5.3/0 V | approximately 5.2/0 V | Calculated from amplitude, VOLTS/DIV, and ×10 probe factor |
| Implied `analogWrite()` value | approximately 163/255 | approximately 63/255 | Inferred from duty cycle |
| Implied averaged voltage | approximately 3.20 V | approximately 1.24 V | Inferred through `map()` and the ADC conversion |
| TIME/DIV | 0.500 ms/div | **0.750 ms/div** | A read from the calibrated setting; B reconstructed from the fixed Timer1 PWM period |
| Period in time | 2.065 ms | **2.040 ms** | Calculated from divisions and effective TIME/DIV |
| **Frequency** | **484.3 Hz** | **490.2 Hz** | A measured from the calibrated timebase; B reconstructed from the Timer1 period |

### Voltage Calculation with the ×10 Probe

For Setting A,

```math
V_{\mathrm{pp},A}
=
(1.05\ \mathrm{div})
(0.5\ \mathrm{V/div})
(10)
=
5.25\ \mathrm{V}.
```

Therefore, the measured HIGH and LOW levels are approximately 5.3 V and 0 V.

For Setting B,

```math
V_{\mathrm{pp},B}
=
(2.58\ \mathrm{div})
(0.2\ \mathrm{V/div})
(10)
=
5.16\ \mathrm{V}.
```

Therefore, the measured HIGH and LOW levels are approximately 5.2 V and 0 V.

### Setting A Frequency

For Setting A,

```math
T_A
=
(4.13\ \mathrm{div})
(0.5\ \mathrm{ms/div})
=
2.065\ \mathrm{ms}.
```

Thus,

```math
f_A
=
\frac{1}{2.065\times10^{-3}\ \mathrm{s}}
=
484.3\ \mathrm{Hz}
\approx 485\ \mathrm{Hz}.
```

Compared with the expected 490 Hz,

```math
\text{percentage difference}
=
\frac{|485-490|}{490}\times100\%
\approx 1.0\%.
```

Figures 4b and 5b were photographed at different sweep speeds and give consistent periods
to approximately 0.2%. However, the frequency calculation still depends on identifying
the Setting A timebase as 0.5 ms/div. Agreement with the expected 490 Hz supports this
interpretation but is not an independent frequency measurement.

### Setting B Timebase Reconstruction

The Arduino Uno pin-9 PWM frequency is set by Timer1. With a 16 MHz clock and the
standard prescaler, the expected PWM frequency is approximately 490.2 Hz. Therefore,
the corresponding period is

```math
T_B
=
\frac{1}{490.196\ \mathrm{Hz}}
=
2.040\ \mathrm{ms}.
```

The Setting B photograph shows one period spanning 2.72 horizontal divisions. The
effective TIME/DIV value can therefore be reconstructed from

```math
\left(\frac{\mathrm{TIME}}{\mathrm{DIV}}\right)_B
=
\frac{T_B}{N_{\mathrm{cycle},B}}
=
\frac{2.040\ \mathrm{ms}}{2.72\ \mathrm{div}}
=
0.750\ \mathrm{ms/div}.
```

Using this reconstructed timebase,

```math
T_B
=
(2.72\ \mathrm{div})(0.750\ \mathrm{ms/div})
=
2.040\ \mathrm{ms},
```

and

```math
f_B
=
\frac{1}{2.040\times10^{-3}\ \mathrm{s}}
=
490.2\ \mathrm{Hz}.
```

Thus, the effective timebase during the Setting B photograph was **0.750 ms/div**,
giving a period of **2.040 ms** and a frequency of **490.2 Hz**. The most likely
explanation for the nonstandard effective scale is that the variable-timebase control
was not at its calibrated detent.

This reconstruction is physically consistent with the fixed Timer1 PWM frequency.
However, because the timebase was inferred using that expected frequency, the Setting B
frequency is timer-derived rather than an independent oscilloscope measurement.

### Which Quantities Change and Which Remain Fixed?

Duty cycle follows the potentiometer setting: 64% for Setting A and 25% for Setting B.
This ratio does not depend on the VOLTS/DIV setting or the ×10 probe correction.

After accounting for the different oscilloscope scales, the two settings are consistent
with approximately the same 5.2 V amplitude and the same approximately 2.04 ms PWM period.
The potentiometer changed the duty cycle from 64% to 25%, while the voltage levels and
timer-controlled frequency remained approximately fixed. The measured amplitudes are 1.05 and 2.58 divisions, while the measured periods are 4.13 and 2.72 divisions. These division counts cannot be compared directly when the scale settings
are different.

Physically, the PWM period is set by the microcontroller timer, prescaler, and 16 MHz
clock. `analogWrite()` changes the compare value and therefore changes duty cycle rather
than the timer frequency. The HIGH and LOW voltage levels should also remain approximately
fixed. Capturing both potentiometer settings without changing the scope controls would
demonstrate this directly.

### Why the LED Looks Continuously Lit

At approximately 485 Hz, the LED switches on and off roughly 485 times each second. This
is approximately an order of magnitude above the common 50–60 Hz flicker-fusion range, so
the visual system integrates the pulses into a continuous apparent brightness. The
oscilloscope does not perform this visual integration and therefore displays the
individual pulses.

Flicker fusion is not one universal frequency. It depends on brightness, contrast,
peripheral versus central vision, the apparent size of the source, and the observer.
Therefore, 50–60 Hz should be treated as an approximate reference range rather than a
universal threshold.

### Precision Through the Signal Chain

`m01_pwm_from_pot` averages 1000 ADC readings and then converts the result to `int` before
applying `map(..., 0, 1023, 0, 255)`. The additional effective precision obtained through
averaging cannot survive unchanged in an 8-bit actuator command because the PWM output has
only 256 command levels.

Precision at the sensor therefore does not automatically become precision at the actuator.
This is an important instrument-design constraint that will matter when the same signal
chain controls the TEC.

### What the Oscilloscope Showed That the Serial Displays Did Not

The essential distinction is between a direct electrical measurement of the output pin
and values selected and printed by software. Serial Monitor and Serial Plotter report
samples acquired and processed by the sketch at the rate selected by the program. The
oscilloscope displays the voltage on the wire using its own independent timebase.

The serial displays could not show the approximately 2 ms PWM period because communication
at 9600 baud, together with program execution and delays, produces reports at only a few
tens of hertz. This is several orders of magnitude slower than the PWM waveform. The
serial output also reports the commanded duty value rather than directly measuring the
waveform produced by the pin.

The oscilloscope resolved the individual pulses, actual HIGH and LOW voltage levels, duty
cycle, and period. It therefore showed whether the hardware produced the waveform requested
by the software. The serial output shows what the software believes or commands, whereas
the oscilloscope shows what the electrical hardware actually produces.

---

## 6. C1 Question 9 — Arduino Uno Analog Input

The Arduino Uno analog input is a successive-approximation ADC that measures **voltage**.
It does not directly measure current or resistance, although a voltage-divider circuit can
convert a resistance into a measurable voltage.

The ADC measures relative to a reference voltage. In this experiment, the input range is
treated as 0–5.00 V. An input at or above the reference saturates at the maximum code.

The converter is **10-bit**, so it divides the input range into

```math
2^{10}
=
1024
```

levels and reports integer codes from **0 to 1023**. One count corresponds to

```math
\Delta V
=
\frac{V_{\mathrm{ref}}}{1024}
=
\frac{5.00\ \mathrm{V}}{1024}
\approx 4.88\ \mathrm{mV}.
```

A conversion takes approximately **100 µs**, giving a maximum conversion rate of about

```math
f
=
\frac{1}{100\times10^{-6}\ \mathrm{s}}
=
10{,}000\ \mathrm{samples/s}.
```

The practical reporting rate is usually lower because `Serial.print()` and any `delay()`
statements add time.

Six analog channels, A0–A5, share one converter through an analog multiplexer. The
channels are sampled sequentially rather than simultaneously, and the sample-and-hold
capacitor must settle again after switching channels.

The microcontroller documentation recommends a source impedance of approximately
**10 kΩ or less** because the internal sample-and-hold capacitor must charge through the
source impedance during a limited sampling interval. The 100 kΩ potentiometer divider
used here reaches a Thévenin impedance of 25 kΩ at midrange and therefore exceeds that
recommendation. This is a limitation of the assigned circuit.

---

## 7. C1 Question 10 — Arduino Uno PWM Output

A PWM output is a **digital** pin that switches rapidly between approximately 0 V and
5 V. It is controlled using `analogWrite(pin, value)`, where `value` ranges from **0 to
255**. The command determines the duty cycle:

```math
D
=
\frac{\text{value}}{255}\times100\%.
```

The switching frequency is set by the timer hardware. On the Arduino Uno, it is
approximately **490 Hz** on pins 3, 9, 10, and 11 and approximately 980 Hz on pins 5 and 6.

### PWM Is Not a True Analog Voltage

At each instant, the output pin is at either its LOW or HIGH voltage. It does not remain
at an intermediate voltage. What changes is the fraction of each period spent HIGH.

The average voltage over a period is approximately

```math
V_{\mathrm{avg}}
=
D V_{\mathrm{HIGH}},
```

where $D$ is written as a fraction between 0 and 1.

This average becomes physically meaningful when a load integrates the pulses. Examples
include an RC low-pass filter, the thermal mass of a heater, the mechanical inertia of a
motor, or persistence of vision when viewing an LED.

An oscilloscope shows the individual square-wave pulses. A slower DC voltmeter may report
their average. Both observations describe the same signal at different time resolutions.

### Why a Power Stage Is Required

An ATmega328P output pin can supply only tens of milliamperes at approximately 5 V, which
corresponds to tens of milliwatts. A motor or TEC may require several amperes from a
separate supply. Connecting such a load directly to the Arduino pin could damage the
microcontroller.

An H-bridge serves as the power stage. The low-power Arduino logic signal controls a
high-current path from the external supply through the load, allowing the microcontroller
to control the power without carrying the load current directly.

The H-bridge also permits current to flow in either direction through the load. This is
essential for a TEC because reversing the current exchanges the hot and cold faces. The
controller can therefore use one actuator for both heating and cooling.

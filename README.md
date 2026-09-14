# LabModule1 — First Contact With The Instrument

**Course:** Phys 39 — Instrumentation and Thermal Physics  
**Team:** TEC 8  
**Repository:** https://github.com/joshuaaferiat/LabModule1

Semester project: an Arduino-based closed-loop temperature controller built from a
thermistor, a thermoelectric cooler (TEC/Peltier), an H-bridge driver, a bench supply,
and a liquid-cooled heat exchanger.

This repository contains the firmware, raw measurements, figures, analysis scripts,
and written evidence notes for each module.

---

## Repository Map

| Path | Contents |
|---|---|
| `firmware/module_NN/<sketch_name>/` | Arduino sketches. One folder per sketch; the folder name must match the `.ino` filename. |
| `data/module_NN/` | Raw measurements preserved as captured. |
| `figures/module_NN/` | Screenshots and photographs referenced by the evidence notes. |
| `analysis/module_NN/` | Scripts and calculations used to analyze measurements. |
| `docs/module_notes/module_NN_evidence.md` | Graded evidence note for each module. |
| `docs/reference/` | Checkoff text, calibration records, and settings that apply across modules. |
| `hardware/` | Apparatus photographs, wiring information, bill of materials, and safety notes. |

Raw measurements belong in `data/`, images in `figures/`, calculations in `analysis/`,
and conclusions in `docs/`.

Reported values are identified according to their source:

- **Measured:** obtained directly from a saved display, photograph, or raw capture.
- **Calculated:** obtained mathematically from measured or programmed quantities.
- **Estimated:** inferred from incomplete recorded data.
- **Reconstructed:** recovered using known hardware behavior together with recorded evidence.

---

## Conventions

- **Serial:** 9600 baud for every Module 1 sketch. Each current sketch prints a `VERSION`
  string so Serial Monitor can identify the build running on the board.

- **ADC:** voltage is calculated as `counts × 5.00 / 1024`. The ADC is 10-bit, with
  1024 levels and codes from 0 through 1023. One count corresponds to approximately
  4.883 mV when using the assumed 5.00 V reference.

- **ADC divisor:** all current sketches use 1024. Two earlier versions used 1023; see
  `MIGRATION.md`.

- **Oscilloscope probe:** the probe was set to **×10**. Voltage calculations therefore use

  `voltage = vertical divisions × VOLTS/DIV × 10`.

- **Figures:** filenames follow `m01_figNN_<description>`. PNG is used for screenshots
  and JPG for photographs.

---

## Module 1 — First Contact with the Instrument

**Safety boundary:** The TEC power supply remained **off** throughout Module 1. The Arduino
was powered by USB only. The TEC, H-bridge, heat exchanger, thermistor, and safety cutoff
were inspected but not energized.

### Progress by Assignment Part

| Part | Topic | State |
|---|---|---|
| 1 | Blink and digital output at three HIGH-to-LOW ratios | **Reconstructed from programmed timing.** Period, frequency, and duty cycle were calculated from the sketch’s delay constants. No independent scope timing capture was preserved. |
| 2 | `AnalogReadSerial` and potentiometer divider | **Partly captured.** Figure 8 records values near the upper endpoint and Figure 7 records fixed-setting dither. |
| 3A | ADC minimum, maximum, midrange, and discrete levels | **Partly measured and partly estimated.** Maximum 1023 and one- to two-count dither were measured. The lower endpoint and midrange were estimated from the circuit configuration. |
| 3B | ADC counts converted to voltage | **Calculated.** Current sketches use `counts × 5.00 / 1024`. |
| 3C | Comparison of \(N=1\) and \(N=1000\) averaging | **Preliminary estimate only.** Seven visible readings provide an unaveraged mean and sample standard deviation. The required two 100-point captures were not preserved. |
| 3D | Acquisition time for 1000 conversions | **Reconstructed from ADC timing.** Approximately 104 µs per conversion and 104,000 µs for 1000 conversions, excluding software overhead. |
| 4 | Averaged potentiometer voltage controlling LED PWM | **Measured and reconstructed.** Duty cycles of 64% and 25% were measured. Setting A frequency was calculated from the scope scale; Setting B timebase was reconstructed from Timer1 timing. |

---

## Sketches

All sketches use 9600 baud.

| Sketch | Part | Purpose | Evidence state |
|---|---|---|---|
| [`m01_blink_ratio`](firmware/module_01/m01_blink_ratio/) | 1 | Drives `LED_BUILTIN` and an external LED on pin 9; `RATIO_CASE` selects 1:1, 10:1, or 1:10 timing | Consolidated reconstruction of the lab edits |
| [`m01_adc_raw`](firmware/module_01/m01_adc_raw/) | 2, 3A | Prints `ADC:<0-1023>` for Serial Monitor and Serial Plotter | Equivalent earlier version produced Figures 7 and 8 |
| [`m01_adc_voltage`](firmware/module_01/m01_adc_voltage/) | 3B | Prints ADC count and converted voltage | Code present; output not separately captured |
| [`m01_avg_compare`](firmware/module_01/m01_avg_compare/) | 3C | Produces 100 points at \(N=1000\) and 100 points at \(N=1\) | Code present; required capture not preserved |
| [`m01_avg_stats_onboard`](firmware/module_01/m01_avg_stats_onboard/) | 3C | Calculates mean and sample standard deviation on the Arduino | Code present; run not preserved |
| [`m01_avg_timing`](firmware/module_01/m01_avg_timing/) | 3D | Uses `micros()` around 1000 `analogRead()` calls | Code present; direct timing output not preserved |
| [`m01_pwm_from_pot`](firmware/module_01/m01_pwm_from_pot/) | 4 | Maps averaged potentiometer voltage to `analogWrite()` on pin 9 | Produced Figures 4b, 5b, 9, and 10b |

Superseded variants are stored in
[`firmware/module_01/archive/`](firmware/module_01/archive/) and were not used for the
reported results.

---

## Results

### Part 1 — Blink Timing

The values were reconstructed from the programmed `delay()` constants.

| `RATIO_CASE` | Ratio | On/off time (ms) | Period (s) | Frequency (Hz) | Duty cycle |
|---|---|---:|---:|---:|---:|
| 0 | 1:1 | 1000/1000 | 2.000 | 0.500 | 50.0% |
| 1 | 10:1 | 1000/100 | 1.100 | 0.909 | 90.9% |
| 2 | 1:10 | 100/1000 | 1.100 | 0.909 | 9.1% |

The calculations use:

- `period = on time + off time`
- `frequency = 1 / period`
- `duty cycle = on time / period × 100%`

The 10:1 and 1:10 cases have the same period and frequency but opposite duty-cycle
behavior. The calculated periods are lower bounds because loop and `digitalWrite()`
overhead add a small amount of time beyond the programmed delays.

No persistent scope trace was obtained for Blink. At 0.5–0.9 Hz, one period is comparable
to or longer than the oscilloscope’s complete slowest sweep of 1.0 s. The CRT phosphor
fades before a stable full-period trace can form.

---

### Part 3A — ADC Digitization

| Quantity | Value | Basis |
|---|---:|---|
| Maximum count | **1023 = 4.995 V** | Measured, Figure 8 |
| Lowest visible count | **20 = 97.7 mV** | Measured mid-sweep; an upper bound on the endpoint minimum |
| Estimated lower endpoint | **approximately 0–2 counts = 0–9.77 mV** | Inferred from the divider connection to GND |
| Estimated midrange | **approximately 512 counts = 2.500 V** | Calculated midpoint |
| Estimated midrange range | **511–513 counts = 2.495–2.505 V** | Estimated using the observed dither |
| Fixed-setting dither | **1–2 counts = approximately 5–10 mV** | Measured, Figures 7 and 8 |
| One-count step | **4.883 mV** | Calculated using the assumed 5.00 V reference |

The lower endpoint and midrange were not preserved in photographs. Their values were
estimated from the voltage-divider configuration and the observed one- to two-count
fluctuation.

The ADC produces discrete integer codes because a 10-bit converter divides the input
range into 1024 intervals. Printing more decimal places after converting the code to
voltage does not increase the physical resolution of one conversion.

---

### Part 3C — Preliminary Averaging Estimate

Figure 8 contains seven visible values:

`1022, 1022, 1022, 1023, 1022, 1022, 1022`

Statistics calculated from this seven-point subset are:

| Quantity | Value |
|---|---:|
| Mean ADC code | 1022.1429 |
| Mean voltage | **4.99093 V** |
| Sample standard deviation | **1.846 mV** |
| Smallest observed nonzero jump | **4.8828 mV** |
| Predicted \(N=1000\) standard deviation | **0.0584 mV** |
| Predicted \(\sigma_{1000}/\sigma_1\) | **0.0316** |
| Predicted effective-bit gain | **approximately 4.98 bits** |

For independent zero-mean fluctuations, averaging \(N\) measurements predicts

`σ_N / σ_1 = 1 / √N`.

For \(N=1000\), the predicted ratio is 0.0316. Applying that ratio to the seven-point
sample standard deviation gives approximately 0.0584 mV.

These values are preliminary estimates and do not replace the missing 100-point
unaveraged and averaged captures.

---

### Part 3D — Acquisition-Time Reconstruction

The Uno uses a 16 MHz system clock and the default ADC prescaler of 128, giving an ADC
clock of 125 kHz. A standard conversion requires approximately 13 ADC clock cycles.

| Quantity | Reconstructed value | Basis |
|---|---:|---|
| ADC clock | 125 kHz | 16 MHz divided by 128 |
| Time per conversion | **approximately 104 µs** | 13 ADC cycles |
| Time for 1000 conversions | **approximately 104,000 µs = 0.104 s** | ADC conversion time |
| Conversion rate | **approximately 9615 conversions/s** | Calculated |
| Function and loop overhead | Not included | Requires direct `micros()` output |

The direct result from `m01_avg_timing` was not preserved. The actual elapsed time would
be slightly longer than 104,000 µs because of function and loop overhead.

Averaging over approximately 0.104 s acts as a boxcar low-pass filter. It reduces rapid
random fluctuations but also smooths and delays genuine changes in the input.

---

### Part 4 — PWM Output

The oscilloscope probe was set to **×10**.

| Quantity | Setting A | Setting B | Basis |
|---|---:|---:|---|
| Duty cycle | **64%** | **25%** | Measured directly as HIGH width divided by period |
| Period on graticule | 4.13 div | 2.72 div | Measured from photographs |
| Amplitude on graticule | 1.05 div | 2.58 div | Measured from photographs |
| Probe attenuation | ×10 | ×10 | Probe setting |
| VOLTS/DIV | 0.5 V/div | 0.2 V/div | Reconstructed from graticule and approximately 5 V swing |
| HIGH/LOW voltage | approximately 5.3/0 V | approximately 5.2/0 V | Calculated using the ×10 factor |
| Implied `analogWrite()` value | approximately 163/255 | approximately 63/255 | Inferred from duty cycle |
| Implied averaged input voltage | approximately 3.20 V | approximately 1.24 V | Inferred through `map()` |
| TIME/DIV | 0.500 ms/div | **0.750 ms/div** | A from calibrated scale; B reconstructed from Timer1 timing |
| Period | **2.065 ms** | **2.040 ms** | Calculated |
| Frequency | **484.3 Hz** | **490.2 Hz** | A from scope scale; B reconstructed from Timer1 timing |

Setting A voltage:

`1.05 div × 0.5 V/div × 10 = 5.25 V`

Setting B voltage:

`2.58 div × 0.2 V/div × 10 = 5.16 V`

Setting A period and frequency:

- `4.13 div × 0.500 ms/div = 2.065 ms`
- `1 / 2.065 ms = 484.3 Hz`

Setting A differs from 490.2 Hz by approximately 1.2%.

For Setting B, the known Timer1 period of approximately 2.040 ms and the measured
2.72 divisions per period give an effective timebase of

`2.040 ms / 2.72 div = 0.750 ms/div`.

The Setting B timebase was therefore reconstructed as 0.750 ms/div. Its resulting
490.2 Hz frequency is timer-derived rather than an independent frequency measurement.
The nonstandard effective scale indicates that the variable-timebase control was
probably not at its calibrated detent.

After correcting for the different scope settings, the two measurements are consistent
with approximately the same 5.2 V amplitude and 2.04 ms period. The potentiometer
changed the duty cycle, while the voltage levels and timer-controlled frequency remained
approximately fixed.

---

## Figures

| Figure | File | State |
|---|---|---|
| 1 | `m01_fig01_apparatus.jpg` | Labeled apparatus |
| 2 | `m01_fig02_avg_transition.png` | Required averaging transition capture not preserved |
| 3 | `m01_fig03_unaveraged_only.png` | Required unaveraged-only capture not preserved |
| 4 | `m01_fig04_pwm_waveform.jpg` | Original PWM photograph |
| 4b | `m01_fig04b_pwm_measured.jpg` | Setting A measurement overlay |
| 5 | `m01_fig05_pwm_waveform_B.jpg` | Earlier PWM photograph |
| 5b | `m01_fig05b_pwm_measured_fast.jpg` | Setting A at a faster sweep |
| 6 | `m01_fig06_part1_bench.jpg` | Part 1 setup; not a timing result |
| 7 | `m01_fig07_adc_dither.jpg` | Fixed-setting ADC dither |
| 8 | `m01_fig08_adc_sweep.jpg` | ADC sweep and upper endpoint |
| 9 | `m01_fig09_part4_wiring.jpg` | Part 4 wiring |
| 10b | `m01_fig10b_pwm_settingB_measured.jpg` | Setting B PWM trace |

Bench records are stored in
[`data/module_01/m01_scope_measurements.md`](data/module_01/m01_scope_measurements.md).

Serial captures belong in `data/module_01/`. The analysis script

[`analysis/module_01/averaging_stats.py`](analysis/module_01/averaging_stats.py)

calculates the averaging statistics when a complete `m01_avg_compare` capture is
available.

---

## Wiring

- **Potentiometer:** 100 kΩ trimmer; outer terminals connected to `5V` and `GND`,
  with the wiper connected to `A0`.
- **Built-in LED:** pin `13` (`LED_BUILTIN`), used in Part 1.
- **External LED:** pin `9` → 150 kΩ resistor → LED anode; LED cathode → `GND`.
- **Oscilloscope:** CH2, DC coupling, ×10 probe on pin `9`, ground clip on Arduino `GND`.
- **TEC system:** no connection to the TEC, H-bridge, or bench supply during Module 1.

---

## Equipment

| Item | Identification |
|---|---|
| Microcontroller | ELEGOO UNO R3; Arduino Uno-compatible ATmega328P board |
| Oscilloscope | BK Precision 2120B, 30 MHz dual-trace analog oscilloscope |
| Probe | 8100 series switchable probe, used in the **×10** position |
| Sensor | Bead-type NTC thermistor on the apparatus; unused during Module 1 |
| Actuator assembly | TEC 8 Peltier element mounted on a machined cold plate |
| Heat exchanger | ID-COOLING twin-fan radiator |
| Bench supply | Switching supply with 110/220 V selection; off throughout Module 1 |
| Divider | 100 kΩ trimmer potentiometer |
| LED series resistor | **150 kΩ**; outside the specified 200–4000 Ω range because a suitable resistor was not available during the recorded setup |

Apparatus photographs are stored in [`hardware/`](hardware/).

---

## Reproducing a Measurement

1. Open the required sketch folder under `firmware/module_01/` in the Arduino IDE.
2. Select **Tools → Board → Arduino Uno**, and then select the appropriate serial port.
3. Upload the sketch.
4. Open Serial Monitor at **9600 baud**.
5. Confirm that the printed `VERSION` string matches the intended sketch.
6. Save the raw output in `data/module_01/` using the naming convention documented in
   that folder.
7. Save oscilloscope and apparatus images in `figures/module_01/`.
8. Run the corresponding script in `analysis/module_01/`.
9. Update the evidence note with values clearly labeled as measured, calculated,
   estimated, or reconstructed.
10. Commit and push the completed checkpoint.

To obtain the full commit hash after pushing:

```bash
git rev-parse HEAD

# LabModule1 — Temperature Control Instrument

**Course:** Phys 39 — Instrumentation and Thermal Physics
**Team:** TEC 8
**Repository:** `https://github.com/joshuaaferiat/LabModule1`

Semester project: an Arduino-based closed-loop temperature controller built from a thermistor,
a thermoelectric cooler (TEC/Peltier), an H-bridge driver, a bench supply and a liquid-cooled
heat exchanger. This repository holds the firmware, raw measurements, figures and written
evidence notes for every module.

---

## Repository map

| Path | What lives here |
|---|---|
| `firmware/module_NN/<sketch_name>/` | Arduino sketches. One folder per sketch; the folder name **must** equal the `.ino` name, or the IDE will not open it. |
| `data/module_NN/` | Raw measurements exactly as captured. Never edited afterwards. |
| `figures/module_NN/` | Screenshots and photographs referenced by the evidence notes. |
| `docs/module_notes/module_NN_evidence.md` | The graded evidence note for each module (A1, A2, …). |
| `docs/reference/` | Notes that outlive one module: checkoff text, calibration, settings. |
| `hardware/` | Apparatus photographs, wiring, bill of materials, safety notes. |

Raw goes in `data/`, pictures in `figures/`, arithmetic in `analysis/`, prose and conclusions
in `docs/`. Every number quoted in an evidence note traces back to a file in `data/`, either
directly or through a script in `analysis/`.

## Conventions

- **Serial:** 9600 baud for every Module 1 sketch. The first line each sketch prints is its
  `VERSION` string, so Serial Monitor identifies the build actually running on the board.
- **ADC:** volts = counts × 5.00 / 1024. Ten-bit, 1024 levels, codes 0–1023, ΔV ≈ 4.88 mV.
  Standardised on 1024 across all sketches (two originally used 1023 — see `MIGRATION.md`).
- **Figures:** `m01_figNN_<description>` — PNG for screenshots, JPG for photographs.

---

## Module 1 — First Contact With The Instrument

**Safety boundary:** the TEC power supply stayed **off** for all of Module 1; the Arduino ran
on USB power only. The TEC, H-bridge, heat exchanger, thermistor and safety cutoff were
inspected but never energised.

### Progress by assignment part

| Part | What it covers | State |
|---|---|---|
| 1 | Blink, digital output at three on:off ratios | **Reported as calculated** — values from the sketch's delay constants, labeled as such. No scope figure: at 0.5–0.9 Hz the analog CRT spot crawls and never forms a persistent trace. |
| 2 | `analogReadSerial`, potentiometer divider | Sketch ready; readings not yet captured |
| 3A | ADC min / max / midrange, discrete levels | **Partly measured** — max 1023, dither 1–2 counts. Midrange hold and settled minimum outstanding. |
| 3B | ADC counts → volts | Sketch ready; not captured |
| 3C | N = 1 vs N = 1000 averaging | Not started — largest outstanding block |
| 3D | Time cost of 1000 conversions | Not started |
| 4 | Averaged pot voltage → PWM → LED brightness | **Measured**: 485 Hz; duty 64 % and 25 % at two settings. Knob settings still unrecorded, so period-held-fixed is unproven. |

Full outstanding list, audited against the A1 rubric:
[`docs/reference/MISSING_ITEMS.md`](docs/reference/MISSING_ITEMS.md)

### Sketches

All at 9600 baud. `TODO` in the last column: mark each one you have actually uploaded and
watched run — the README should not claim more than was tested.

| Sketch | Part | What it does | Uploaded & verified |
|---|---|---|---|
| [`m01_blink_ratio`](firmware/module_01/m01_blink_ratio/) | 1 | Stock Arduino Blink, modified: `LED_BUILTIN` + external LED on pin 9, `RATIO_CASE` = 0/1/2 for 1:1, 10:1, 1:10 |
| [`m01_adc_raw`](firmware/module_01/m01_adc_raw/) | 2, 3A | Prints `ADC:<0-1023>` for Serial Monitor and Plotter |
| [`m01_adc_voltage`](firmware/module_01/m01_adc_voltage/) | 3B | Prints ADC count and converted voltage |
| [`m01_avg_compare`](firmware/module_01/m01_avg_compare/) | 3C | 100 points at N = 1000, then 100 at N = 1, repeating |
| [`m01_avg_stats_onboard`](firmware/module_01/m01_avg_stats_onboard/) | 3C | Mean and sample σ computed on the Arduino — independent check on the analysis script |
| [`m01_avg_timing`](firmware/module_01/m01_avg_timing/) | 3D | `micros()` around 1000 `analogRead()` calls |
| [`m01_pwm_from_pot`](firmware/module_01/m01_pwm_from_pot/) | 4 | Averaged pot voltage → `analogWrite` on pin 9 → LED | ☑ produced Figures 4 and 5 |

Superseded variants are kept in [`firmware/module_01/archive/`](firmware/module_01/archive/)
and were not used for any submitted number.

### Results so far

**Part 4 — PWM output, measured** from Figures 4b and 5b:

| Quantity | Value | Note |
|---|---|---|
| Frequency | 485 Hz | vs ≈490 Hz expected on Uno pin 9 |
| Period | 2.06 ms | two sweep speeds agree to 0.2 % |
| Duty, setting A | 64 % | implies `analogWrite` ≈163 / 255 |
| Duty, setting B | **25 %** | implies ≈64 / 255 — duty clearly follows the pot |
| Amplitude | 1.05 div (A), 2.58 div (B) | V/div was changed between sessions |

**Part 3A — ADC, measured**

| Quantity | Value |
|---|---|
| Maximum count | 1023 (= 4.995 V) |
| Lowest count observed | 20 — mid-sweep, an upper bound on the minimum |
| Dither at a fixed setting | 1–2 counts (≈5–10 mV) |
| One-count step ΔV | 4.883 mV (calculated, V_ref nominal 5.00 V) |

**Part 1 — Blink, calculated** from the delay constants in the modified stock Blink sketch:

| `RATIO_CASE` | Ratio | On/off (ms) | Period (s) | Frequency (Hz) | Duty (%) |
|---|---|---|---|---|---|
| 0 | 1:1 | 1000 / 1000 | 2.000 | 0.500 | 50.0 |
| 1 | 10:1 | 1000 / 100 | 1.100 | 0.909 | 90.9 |
| 2 | 1:10 | 100 / 1000 | 1.100 | 0.909 | 9.1 |

Period and frequency change between cases as well as duty — one delay was held at the stock
1000 ms and the other scaled. Contrast Part 4, where the timer fixes the period and only duty
follows the pot.

### Figures

| Figure | File | State |
|---|---|---|
| 1 | `m01_fig01_apparatus.jpg` | Labeled apparatus, 10 callouts |
| 2 | `m01_fig02_avg_transition.png` | Outstanding — Serial Plotter, N = 1 ↔ N = 1000 transition centred |
| 3 | `m01_fig03_unaveraged_only.png` | Outstanding — N = 1 block alone |
| 4, 4b | `m01_fig04_pwm_waveform.jpg`, `m01_fig04b_pwm_measured.jpg` | PWM trace + measurement overlay |
| 5, 5b | `m01_fig05_pwm_waveform_B.jpg`, `m01_fig05b_pwm_measured_fast.jpg` | Same signal, faster sweep |
| 6 | `m01_fig06_part1_bench.jpg` | Part 1 bench and components (setup, not a result) |

Bench numbers go in
[`data/module_01/m01_scope_measurements.md`](data/module_01/m01_scope_measurements.md).
Serial captures go in `data/module_01/`; run
[`analysis/module_01/averaging_stats.py`](analysis/module_01/averaging_stats.py) on the
`m01_avg_compare` capture to fill the averaging table.

### Wiring

- 100 kΩ trimmer potentiometer (stock part, as the assignment specifies): outer terminals → `5V` and `GND`, wiper → `A0`
- Built-in LED on pin `13` (`LED_BUILTIN`), used in Part 1
- External LED, shared by Parts 1 and 4: pin `9` → **150 kΩ** series resistor → LED anode; cathode → `GND`
- Oscilloscope: probe on `TODO: pin ___`, ground clip on Arduino `GND`, CH2, DC coupled
- No connection to the TEC, H-bridge or bench supply in this module

---

## Equipment

| Item | Identification |
|---|---|
| Microcontroller | ELEGOO UNO R3 (Arduino Uno compatible, ATmega328P) |
| Oscilloscope | BK Precision 2120B, 30 MHz dual trace — **analog**: no cursors, no measurement readout, no screenshot export |
| Probe | 8100 series, ×1/×10 switchable — `TODO: which position?` |
| Sensor | NTC thermistor (bead type, on the rig; unused in Module 1) |
| Actuator assembly | TEC 8 — Peltier element on a machined cold plate |
| Heat exchanger | ID-COOLING twin-fan radiator |
| Bench supply | Switching supply, 110/220 V selectable — off throughout Module 1 |
| Divider | 100 kΩ trimmer potentiometer (stock, as specified) |
| LED series resistor | **150 kΩ**, used throughout Module 1 — above the 200–4000 Ω the handout specifies; see the evidence note |

Apparatus photographs are in [`hardware/`](hardware/).

## Reproducing a measurement

1. Open the sketch folder under `firmware/module_01/` in the Arduino IDE.
2. **Tools → Board → Arduino Uno**, then select the port.
3. Upload, then open Serial Monitor at **9600 baud**. The first line is the sketch's `VERSION`
   string — confirm it matches the sketch you meant to upload.
4. Capture the output into `data/module_01/`, following the naming convention in that folder's
   README.
5. Run the matching script in `analysis/module_01/` to regenerate the reported statistics.

`git log -1 --format=%H` prints the full hash. Export the A1 PDF **after** the final push, so
the hash on page 1 is the hash of the pushed checkpoint.

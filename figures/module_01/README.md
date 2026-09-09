# figures/module_01

## Status

| File | Figure | Status |
|---|---|---|
| `m01_fig01_apparatus.jpg` | 1 | **DONE** — labeled, 10 numbered callouts + legend. Two blanks to fill (resistor value, probe pin). |
| `m01_fig01_apparatus_ORIGINAL_unlabeled.jpg` | — | Source photo the labeled version was built from. Keep for provenance; not submitted. |
| `m01_fig01b_bench_with_scope.jpg` | — | Context shot: rig with the BK 2120B in frame. Optional supplement. |
| `m01_fig01c_bench_wide.jpg` | — | Context shot: bench with scope and laptop. Optional supplement. |
| `m01_fig06_part1_bench.jpg` | 6 | **DONE** — labeled Part 1 bench shot. Was previously filed as the duplicate `m01_fig01d`; that copy is deleted. |
| `m01_fig02_avg_transition.png` | 2 | **MISSING** — Serial Plotter, N=1 ↔ N=1000 transition near the center |
| `m01_fig03_unaveraged_only.png` | 3 | **MISSING** — N=1 block alone, scaled so discrete steps are resolvable |
| `m01_fig04_pwm_waveform.jpg` | 4 | **DONE** — trigger locked, panel in frame, CH2 DC coupled |
| `m01_fig04b_pwm_measured.jpg` | 4b | **DONE** — measurement overlay: 4.13 div period, 64 % duty, 1.05 div amplitude |
| `m01_fig05_pwm_waveform_B.jpg` | 5 | **DONE** — same signal, faster sweep |
| `m01_fig05b_pwm_measured_fast.jpg` | 5b | **DONE** — 10.31 div period, 62 % duty; cross-checks Fig 4b to 0.2 % |
| — | — | **STILL MISSING:** a PWM trace at a clearly different pot setting, to show duty moving while period and amplitude hold |
| `m01_fig07_adc_dither.jpg` | 7 | **DONE** — ADC dither 1–2 counts at a fixed setting |
| `m01_fig08_adc_sweep.jpg` | 8 | **DONE** — sweep; monitor reads 1022/1023 → max = 1023 |
| `m01_fig09_part4_wiring.jpg` | 9 | **DONE** — labeled Part 4 wiring, 8 callouts |
| `m01_fig10_pwm_settingB.jpg` | 10 | **DONE** — PWM at the second pot setting |
| `m01_fig10b_pwm_settingB_measured.jpg` | 10b | **DONE** — measurement overlay, duty = 25 % |
| `_not_usable/scope_earlier_knobs_cropped.jpg` | — | First scope photo; unusable, reason below. |

> Figures 2 and 3 are still missing, so the numbering is not contiguous in the note. Renumber
> everything once those two screenshots exist — doing it now would only have to be redone.

Only Figure 1 needs to be a photograph. Figures 2 and 3 are screenshots (use the OS
screenshot tool, not a phone). Figures 4 and 5 are photographs, because the lab scope is analog — see below.
The `*b` figures are measurement overlays generated from those photographs.

---

## Your oscilloscope is analog. This changes what you have to capture.

The bench scope is a **BK Precision 2120B, 30 MHz dual trace** — an analog CRT scope. It has
no digital readout, no cursors, no measurement display, and no way to export a screenshot.
Everything the assignment asks for (period, frequency, high and low voltage, duty cycle) has
to be read off the graticule by hand and converted using the front-panel knob settings.

**That is why the first scope photo, now in `_not_usable/`, cannot be used.** The screen is in frame, but the
VOLTS/DIV and TIME/DIV knobs are cropped out of the shot, and an analog scope puts nothing
on screen to recover them from. Without those two numbers, a trace 2.5 divisions wide is not
2.5 milliseconds or 2.5 microseconds or 2.5 anything — it is unmeasurable. The trace also
looks unlocked: the high and low levels appear as separate broken horizontal bands with no
visible rising or falling edges, which is what an untriggered display looks like.

### Shooting the remaining trace (second pot setting)

1. **Get a stable trace first.** Set the trigger source to the channel you are probing, set
   coupling to DC, and adjust the TRIGGER LEVEL until the waveform locks and stops drifting.
   You should see square pulses with visible vertical edges, not two floating bands.
2. **Set DC coupling** on the input (the AC/GND/DC slide switch, not AC) — you need the true
   0 V and 5 V levels, and AC coupling removes the DC offset that carries that information.
3. **Frame the shot so the knobs are in it.** Take the photo far enough back that the screen
   *and* the VOLTS/DIV and TIME/DIV settings are readable in the same image. Figures 4 and 5
   got the panel in frame but still not at an angle where the knob pointers can be read —
   close, but write the settings down as well.
4. **Write the settings down anyway**, into `data/module_01/m01_scope_measurements.md`. Do
   not rely on reading them back off a photo.
5. Check the probe attenuation. If the probe is set to ×10, the actual voltage is 10× the
   VOLTS/DIV reading unless the scope knows about it — and an analog scope of this age does
   not. Getting this wrong turns 5 V into 0.5 V.
6. Shoot straight on, lights off the screen, and let the phone focus on the trace.

### Reading numbers off the graticule

    period      = (horizontal divisions per cycle) × (TIME/DIV)
    frequency   = 1 / period
    amplitude   = (vertical divisions) × (VOLTS/DIV) × (probe attenuation)
    duty cycle  = (divisions high / divisions per full cycle) × 100 %

At ≈490 Hz the period is ≈2.04 ms, so a 0.5 ms/div setting puts about four divisions per
cycle across the screen — a good starting point.

---

## Naming and rules

    m01_figNN_<short_description>.<png|jpg>

- PNG for screenshots, JPG for photographs.
- Capture the **whole** Serial Plotter window including its axes.
- Keep files a few MB at most; resize oversized phone photos.
- Every figure must be referenced from the evidence note. Unreferenced files are clutter.
- An unlabeled apparatus photo does not earn the rubric point. Figure 1 is already labeled;
  if you retake it, label the new one too.

---

## What Figures 4 and 5 measured

Both were shot with the trigger locked and CH2 DC coupled, and the graticule in Figure 4 is
uniform to ±1 % across the screen, so the photos are genuinely measurable.

| | Fig 4b | Fig 5b |
|---|---|---|
| Period | 4.13 div | 10.31 div |
| Period in time | 2.065 ms | 2.062 ms |
| Frequency | 485 Hz | 485 Hz |
| Duty cycle | 64 % | 62 % |
| Amplitude | 1.05 div | 1.14 div |

The two were shot at different sweep speeds — the 2.50 ratio between them is exactly the
0.5 → 0.2 ms/div step — and they agree on the period to 0.2 %, against ≈490 Hz expected on
pin 9. Duty ≈63 % implies `analogWrite` ≈160 of 255.

The TIME/DIV setting itself is still a **deduction**, not an observation: the knob pointers are
not legible in either photo. Read them off the panel and record them in
`data/module_01/m01_scope_measurements.md`, and check the ×1/×10 switch on the 8100 probe
while you are there.

---

## Part 1 has a bench figure, but no oscilloscope figure

Figure 6 documents the Part 1 setup and components. It is a bench photograph, not a result:
the external LED is not wired in it and the scope screen is blank, so it shows what was used,
not what happened. Do not caption it as though it were evidence the circuit ran.

Part 1 gets no oscilloscope figure, and that is a decision about the instrument rather than a
gap. The Blink sketch holds on + off at 1000 ms, so the waveform is 1 Hz. The BK 2120B's
slowest sweep is 0.1 s/div, which fits one period across the ten divisions — but at that speed
the spot crawls and the phosphor decays before the sweep finishes, so no persistent trace ever
forms. There is nothing on the screen to photograph.

The assignment does not ask for one either: A1 step 6 requires "the LED-PWM oscilloscope image
or hand sketch" — the PWM waveform, which Figures 4 and 5 cover. For Blink it asks only that
the high and low voltages, period, frequency and duty cycle be *reported*.

By decision the Part 1 values are reported as calculated from the sketch constants, labeled as
such in the note rather than presented as results. That the PWM waveform photographs and the
Blink waveform cannot is itself worth a sentence in the note — a concrete illustration of the
persistence limit of an analog CRT.

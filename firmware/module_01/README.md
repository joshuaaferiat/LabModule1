# firmware/module_01

All sketches run at **9600 baud** and use **volts = counts × 5.00 / 1024**.

## Folder rule (Arduino IDE requirement)

Each sketch sits in a folder whose name exactly matches the `.ino` filename:

    firmware/module_01/m01_adc_raw/m01_adc_raw.ino     ← opens correctly
    S2/analog.ino                                       ← the old flat layout; IDE relocates it

This is why the files were renamed. It is not cosmetic — the IDE refuses to open a sketch
whose folder and file names disagree, and it merges every `.ino` in a folder into one
compilation unit, which is why `S2/` with eight sketches in it could never be opened as a
sketch folder at all.

## Sketches

| Folder | Part | Purpose | Serial output |
|---|---|---|---|
| `m01_blink_ratio` | 1 | Stock Arduino Blink, modified: `LED_BUILTIN` + external LED on pin 9; `RATIO_CASE` = 0/1/2 gives 1:1, 10:1, 1:10 | ratio/period/duty banner at startup |
| `m01_adc_raw` | 2, 3A | Raw `analogRead(A0)` integers | `ADC:512` |
| `m01_adc_voltage` | 3B | ADC count plus converted voltage | `ADC:512` then `Voltage:2.50` |
| `m01_avg_compare` | 3C | 100 points at N=1000, then 100 at N=1, forever | `Ave1000_Point_1 Voltage_V:2.4561` |
| `m01_avg_stats_onboard` | 3C helper | On-board mean and sample σ of 100 single readings | `Mean_V:2.46  s:0.0073` |
| `m01_avg_timing` | 3D | `micros()` around 1000 `analogRead()` calls | `Elapsed_us:` and `Conversions_per_second:` |
| `m01_pwm_from_pot` | 4 | Averaged pot voltage → PWM on pin 9 → LED | tab-separated voltage / PWM / duty |

## Version strings

Every sketch declares `const char* VERSION` and prints it immediately after `Serial.begin()`.
The first line in Serial Monitor therefore names the sketch and version now on the board.

**Bump the version whenever you change a sketch.** This is what makes C1 oral question 1
answerable: "how can you tell the uploaded board is running that version?" — because the
monitor says so, not because the file on disk looks right.

## The output format that makes Serial Plotter behave

`m01_avg_compare` prints **one** plotted numeric field per line:

    Ave1000_Point_1 Voltage_V:2.4561
    Ave1_Point_1 Voltage_V:2.4570

The `Ave…_Point_…` tag identifies the block in Serial Monitor; Serial Plotter ignores it
because it is not a labeled number. The field name `Voltage_V` is **identical** for both
blocks on purpose — naming them `Voltage_avg1_V` and `Voltage_avg1000_V` would make the
plotter draw two separate curves and destroy the transition you need to screenshot.

Note that `m01_adc_voltage` deliberately breaks this rule: it prints two labeled fields and
therefore plots two curves. That is fine for Part 3B, where you are just watching the
conversion work. Do not carry the habit into Part 3C.

## archive/

`archive/tryagain3C_alt_avg_compare/` and `archive/4_pwm_avg10/` are earlier attempts kept
for reference. Each sits in its own folder so the IDE can still open it. Do not use them for
submitted results — `m01_avg_compare` and `m01_pwm_from_pot` are the principal sketches, and
the evidence note links to those.

If the team decides these add nothing, delete them; git history keeps them either way. Two
extra files are cheap, but eight ambiguously named ones were what made the original layout
hard to grade.

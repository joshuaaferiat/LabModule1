# hardware/

Documentation of the physical instrument that outlives any single module. Module-specific
figures belong in `figures/module_NN/`; this folder is for the apparatus itself.

## In this folder

| File | Contents |
|---|---|
| `rig_tray_layout.jpg` | The assembled rig seen from above in its storage tray: bench supply, breadboard, terminal block, cold plate on the machined mount, radiator underneath |
| `rig_tec8_assembly.jpg` | The TEC 8 assembly in the tray — cold plate, terminal block and the ID-COOLING twin-fan radiator, with the unit label visible |
| `rig_parts_bin.jpg` | The parts bin: Arduino, H-bridge module on its heatsink, jumper wires, screwdriver set, and the machined block with its two bores |

## Bill of materials — identified so far

| Item | Identification |
|---|---|
| Microcontroller | ELEGOO UNO R3 (Arduino Uno compatible, ATmega328P) |
| Oscilloscope | BK Precision 2120B, 30 MHz dual trace — **analog**: no cursors, no measurement readout, no screenshot export |
| Probe | 8100 series, ×1/×10 switchable — position not yet recorded |
| Divider | 100 kΩ trimmer potentiometer (stock part, as the assignment specifies) |
| LED series resistor | **150 kΩ** used throughout Module 1 — above the 200–4000 Ω the handout specifies |
| Actuator assembly | **TEC 8** — Peltier element on a machined cold plate. The unit label appears on both the cold plate and the radiator, so the whole assembly is one numbered set. |
| Heat exchanger | ID-COOLING twin-fan radiator |
| Bench supply | Switching supply, 110/220 V selectable by switch — off throughout Module 1 |
| Sensor | NTC thermistor, bead type on flying leads — coefficients not yet recorded |

Two entries are still unread: the H-bridge part number and the thermistor type. Both are
Module 2 concerns, but they are easier to read off the parts now than to hunt for later.

## Worth adding, not yet written

- **`wiring_module_01.md`** — the breadboard connections as built. Currently duplicated in the
  root README and the evidence note; a single file here would stop them drifting.
- **`wiring_full_system.md`** — the full controller wiring, added as it is built.
- **`safety_notes.md`** — safety-cutoff behaviour, TEC supply limits, what may be powered when.

## Module 1 safety statement

Repeat this in each note. The TEC power supply stays **off** for all of Module 1; the Arduino
is powered by USB only. The TEC, H-bridge, heat exchanger, thermistor and safety cutoff may be
inspected but not energised. The course verifies the measurement and communication chain before
applying actuator power.
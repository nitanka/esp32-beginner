# ESP32_Beginner — Project Notes

## Project structure

Each exercise/circuit lives in its own self-contained folder:

```
ESP32_Beginner/
  led-blink/
    platformio.ini      # board config for this exercise
    wokwi.toml           # points to this folder's own build output
    diagram.json         # Wokwi circuit (board + wiring)
    src/main.cpp
    .pio/build/...        # generated on build, not committed
  button-input/          # next exercise, same layout
    ...
```

To add a new exercise, copy this layout into a new sibling folder and adjust
`platformio.ini` (board type) and `diagram.json` (wiring) as needed.

## Wokwi simulation (in VSCode)

- `wokwi.toml` must sit next to `diagram.json`, both at the root of the
  exercise folder (not inside `src/`).
- `wokwi.toml` firmware paths are relative to its own folder:
  ```toml
  [wokwi]
  version = 1
  firmware = '.pio/build/esp32doit-devkit-v1/firmware.bin'
  elf = '.pio/build/esp32doit-devkit-v1/firmware.elf'
  ```
- Build once before simulating so those files exist:
  ```bash
  cd led-blink
  ~/.platformio/penv/bin/pio run
  ```
- Open the exercise's `main.cpp` (or any file in that folder) so the Wokwi
  extension picks up the nearest `wokwi.toml`, then run the simulation.

## Flashing to a real physical ESP32

`wokwi.toml` / `diagram.json` are only used by the simulator — they're
ignored when uploading to real hardware. What gets flashed is the compiled
`firmware.bin` (+ `bootloader.bin`, `partitions.bin`) built into
`.pio/build/<env>/`.

```bash
cd led-blink
~/.platformio/penv/bin/pio run -t upload
```

This builds first, then flashes over serial via `esptool.py`, then the board
reboots and runs the new firmware.

## Selecting the target board (multiple ESP32s connected)

List connected serial devices:
```bash
~/.platformio/penv/bin/pio device list
```
Each ESP32 shows up as its own `/dev/cu.usbserial-XXXX` (macOS) entry with a
USB VID/PID and description (e.g. CP2102/CH340 USB-UART bridge). Unplugging
one board at a time and re-running the command is the reliable way to match
a port to a physical board.

Pin the target explicitly, either per-command:
```bash
pio run -t upload --upload-port /dev/cu.usbserial-1410
```
or permanently in that exercise's `platformio.ini`:
```ini
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
upload_port = /dev/cu.usbserial-1410
monitor_port = /dev/cu.usbserial-1410
```

## Erasing flash on a real physical ESP32

Wipes the entire flash (firmware + any stored data), leaving the board
blank until reflashed:
```bash
cd led-blink
~/.platformio/penv/bin/pio run -t erase
```

## `pio` CLI location

`pio` isn't on PATH by default on this machine — use the full path:
```
~/.platformio/penv/bin/pio
```

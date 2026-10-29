# Serial Port Commander

A Qt Widgets desktop prototype for sending file-management commands to a serial-connected device and inspecting its binary replies. The device must implement the matching custom protocol; this is not a general-purpose file browser for arbitrary serial devices.

## Features

- Select an available serial port and set its baud rate (8 data bits, no parity, 1 stop bit).
- Send status, file-check, directory-listing and file-read commands.
- Inspect received bytes as hexadecimal and text.
- Save received data to a local `.bin` file and inspect an existing local binary file.
- Reveal experimental create/delete commands with the delete-mode checkbox.

The interface includes Russian labels. File upload, rename and a parsed remote directory view are not implemented. Loading a local file only displays it; it does not upload it.

## Build and run

Requires a C++11 compiler, Qt 5 with Widgets and SerialPort, qmake, and make. On Debian/Ubuntu, install `build-essential qtbase5-dev libqt5serialport5-dev`.

```sh
git clone https://github.com/andreystashev/serial-port-commander.git
cd serial-port-commander
mkdir build
cd build
qmake ../stmFM.pro
make -j2
./stmFM
```

Alternatively, open `stmFM.pro` in Qt Creator and select a Qt 5 desktop kit. Your account needs access to the serial device (for example, membership in the appropriate device group on Linux).

## Usage and protocol

1. Attach a device, choose its port, enter its baud rate, and press **Start**. Start refreshes the port list while preserving an available selection. If no ports were present at launch, press Start to discover the newly attached device, then select it and press Start again if needed.
2. Use the command buttons and inspect the replies. Firmware must agree on the address, command codes, byte order and checksum.
3. To receive a file, trigger the file-read command and wait for the full reply. Enter a local basename in the input field and press **Write File** to save `<basename>.bin`.

Commands begin with `0x3A`, followed by a 16-bit address (default `0x0020`), an 8-bit command, a 16-bit payload length, optional payload, and a 16-bit checksum. Multi-byte fields currently use host byte order. The legacy checksum tables are retained for compatibility and are not a verified standard CRC implementation.

For responses beginning with `fsize: N\r\n`, saving requires exactly N payload bytes and removes only that header. Other replies are saved verbatim. Saving leaves the receive buffer intact, so repeated saves produce identical files. Incomplete size-prefixed replies do not overwrite an existing file.

This is an experimental device tool: it does not validate incoming checksums, parse reply frames, or acknowledge completed transfers. Create/delete commands require compatible firmware and can change remote data.

## Tests

Run these commands from the repository root:

```sh
mkdir build-tests
cd build-tests
qmake ../tests/tests.pro
make -j2
QT_QPA_PLATFORM=offscreen ./serial_port_tests
```

The [GitHub Actions workflow](.github/workflows/ci.yml) builds the application and runs these tests on Ubuntu with Qt 5 for pushes and pull requests.

Tests cover disconnected commands, binary payload preservation, repeated saves, malformed/truncated responses, and empty checksum input. They do not require serial hardware. A real device is needed to validate the wire protocol end to end.

## Screenshot

<img width="859" alt="Serial Port Commander interface" src="https://github.com/andreystashev/serial-port-commander/assets/70208784/f67922d8-734c-4528-9635-9e5382358c9e">

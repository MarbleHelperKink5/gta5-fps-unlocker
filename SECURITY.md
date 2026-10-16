# Security Policy

## Scope

GtaV-Optimizer reads and writes memory inside a running `GTA5.exe`
process on the local machine. It does **not** phone home, does **not**
modify game files on disk, and does **not** interact with Rockstar
Online services.

## Supported versions

| Version | Supported |
|---------|-----------|
| 2.4.x   | ✅        |
| 2.3.x   | ⚠️ security fixes only |
| < 2.3   | ❌        |

## Reporting a vulnerability

If you find a memory-safety bug, an unintended write outside the
intended patch region, or a way this tool could be abused to affect
other processes, please email `security@gta5-fps-unlocker.dev` or open
a private security advisory on GitHub.

Please do **not** open public issues for exploitable bugs. We aim to
acknowledge within 72 hours.

## Known limitations

- The injector requires `SeDebugPrivilege`. Run as Administrator.
- Offsets are build-specific. Using stale offsets can crash the game —
  always run a fresh scan after a title update.
- Use at your own risk. Modifying a running game process may violate
  Rockstar's Terms of Service. This project is intended for
  single-player and offline use only.
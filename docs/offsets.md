# Offset Reference

Offsets are relative to the `GTA5.exe` module base and change with
every Rockstar title update. Always re-scan after patching.

| Build      | fps_limiter | stutter_threshold | shader_cache_size |
|------------|-------------|-------------------|-------------------|
| 1.0.2944   | 0x1412A4F80 | 0x1412A5B10       | 0x1412A6100       |
| 1.0.3028   | 0x1412A5180 | 0x1412A5C90       | 0x1412A6280       |
| 1.0.3095   | 0x1412A4F80 | 0x1412A5B10       | 0x1412A6100       |

## How to re-scan

1. Launch GTA V, load into story mode.
2. Run `gta5-optimizer --scan` (WIP flag) or use the signatures in
   `config/patterns.toml` with an external scanner.
3. Copy the resulting addresses into `config/optimizer.toml`.
4. Restart the optimizer.

## Notes

- `fps_limiter` is a 6-byte conditional branch — we NOP it.
- `stutter_threshold` is a float that the engine compares against
  frame delta; setting it to `0.0f` disables the clamp.
- `shader_cache_size` is an `int32` in bytes; `0x40000000` = 1 GiB.
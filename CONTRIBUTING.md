# Contributing to GtaV-Optimizer

Thanks for wanting to help make GTA V run smoother on PC.

## Ground rules

- This project is a **hobbyist frametime / FPS unlocker** for GTA V single-player and private sessions. Do not submit code that targets GTA Online anti-cheat bypasses — those PRs are closed without review.
- Never commit hardcoded offsets that only work on your local game build. Use `config/patterns.toml` signatures and let the scanner resolve them.
- All patches must be reversible. `PatchHandler` stores original bytes for a reason.

## Workflow

1. Fork, branch off `main`, name branches like `feat/shader-boost-v2` or `fix/stutter-threshold`.
2. Build with the provided CMakeLists: `cmake -B build && cmake --build build`.
3. Run the smoke tests: `ctest --test-dir build`.
4. Open a PR describing which GTA V build (e.g. `1.0.3095`) you tested against.

## Code style

- C++20, 4-space indent, `snake_case` for files, `PascalCase` for types.
- No new third-party dependencies without discussion in an issue first.
- Log everything through `utils/logger.h` — no raw `printf`.

## Reporting offset breakage

After a Rockstar title update, offsets shift. Open an issue titled
`[offset-drift] build 1.0.XXXX` and attach a fresh signature scan log.
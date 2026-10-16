# Architecture

GtaV-Optimizer is split into a small number of layers so that each
optimization can be added or removed independently.

    main.cpp
      └─ core::OptimizerCore
           ├─ core::ConfigLoader        (TOML config + offsets)
           ├─ services::MemoryService   (RPM/WPM wrapper)
           ├─ handlers::PatchHandler    (NOP / float / int writes)
           ├─ utils::SignatureScanner   (pattern → offset)
           └─ modules/
                ├─ fps_unlock
                ├─ stutter_fix
                └─ shader_boost

## Layers

- **entry** — `src/main.cpp`, argument parsing, watchdog thread.
- **core** — attach/detach lifecycle, config loading.
- **services** — process memory primitives, module base resolution.
- **handlers** — higher-level patch operations with rollback.
- **modules** — feature-specific install routines.
- **overlay** — D3D11 Present hook (in progress).
- **injector** — LoadLibraryW remote-thread DLL loader.
- **csharp** — optional WinForms tray companion.

## Offset resolution

Offsets in `config/optimizer.toml` are the fast path. When they go
stale (after a title update) `config/patterns.toml` signatures are
used by `SignatureScanner` to re-derive them at runtime.
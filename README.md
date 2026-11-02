# Air Quality Code Review Qualification Kit

This repository qualifies a code-review agent against a small C11 air-quality
application. The application processes simulated sensor readings, calculates a
rolling AQI average, classifies air quality, and determines whether an alert is
required.

The source intentionally contains small requirement and coding-standard
deviations for the reviewing agent to identify. These deviations are review
findings, not compilation failures.

## Project layout

| Path | Description |
|---|---|
| `air_quality/HLR.md` | High-level product requirements |
| `air_quality/LLR.md` | Low-level, implementation-verifiable requirements |
| `air_quality/CODE_STANDARD.md` | Mandatory C coding standard, including traceability, naming, and arithmetic rules |
| `air_quality/src/aq_monitor.h` | Public module interface and AQI constants |
| `air_quality/src/aq_monitor.c` | Air-quality module implementation |
| `air_quality/src/main.c` | Application entry point and simulated sensor integration |
| `air_quality/AVP-001.md` | Private verification procedure for `aq_monitor.c` |
| `air_quality/AVP-002.md` | Private verification procedure for `main.c` |
| `air_quality/AVP-003.md` | Private agent-process verification procedure |
| `air_quality/build.bat` | GCC build-and-run script |
| `.github/agents/code-reviewer.agent.md` | Custom code-review agent definition |

## Simulated sensor data

`main.c` consumes a fixed sensor sequence defined in `aq_monitor.h`:

```text
42, 78, 125, 520, 180
```

The sequence includes normal, elevated, invalid, and unhealthy AQI values.

## Build and run

The project requires GCC available on `PATH`. From the repository root, run:

```bat
air_quality\build.bat
```

The script compiles the application as C11 using:

```text
gcc -std=c11 -Wall -Wextra -Werror
```

It writes `air_quality\build\air_quality_monitor.exe` and then executes it.

## Qualification procedure

1. Keep all `air_quality/AVP-*.md` files inaccessible to the candidate agent.
2. Provide `HLR.md`, `LLR.md`, `CODE_STANDARD.md`, and the `air_quality/src/`
   source files.
3. Ask the agent to report only substantiated findings, including the violated
   identifier, source location, explanation, impact, and recommended fix.
4. Score the `aq_monitor.c` review using `AVP-001.md` and the `main.c` review
   using `AVP-002.md`.
5. Use `AVP-003.md` to assess whether the agent followed the prescribed review
   process.

Each per-source AVP contains its expected findings, false-positive guards,
scoring criteria, and a result template.

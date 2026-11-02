# High-Level Requirements

## HLR-001 — Measurement processing

The system shall obtain an Air Quality Index (AQI) measurement once per polling
cycle and calculate a rolling average from valid measurements only.

## HLR-002 — AQI classification

The system shall classify the rolling AQI average using these inclusive bands:

| AQI | Classification |
|---:|---|
| 0–50 | GOOD |
| 51–100 | MODERATE |
| 101–150 | UNHEALTHY_FOR_SENSITIVE_GROUPS |
| 151–200 | UNHEALTHY |
| 201–300 | VERY_UNHEALTHY |
| 301–500 | HAZARDOUS |

## HLR-003 — Health alert

The system shall raise an alert when the rolling AQI average is 151 or greater
and clear the alert below 151.

## HLR-004 — Invalid measurements

The system shall reject an invalid sensor measurement without updating the
rolling average or the alert state.

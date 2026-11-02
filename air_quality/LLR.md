# Low-Level Requirements

## LLR-SENSOR-001 — Sensor range validation

`aq_sensor_read` shall return `AQ_STATUS_RANGE_ERROR` for every raw sensor
reading greater than 500. It shall return `AQ_STATUS_OK` only for readings in
the inclusive range 0 through 500.

## LLR-FILTER-001 — Valid input to filter

`aq_filter_add` shall be called only after `aq_sensor_read` returns
`AQ_STATUS_OK`.

## LLR-FILTER-002 — Rolling average

`aq_filter_average` shall return the arithmetic mean of the values currently
stored in the filter. It shall return zero when the filter contains no values.

## LLR-CLASSIFY-001 — Classification boundary

`aq_classify` shall return `AQ_CLASS_UNHEALTHY_FOR_SENSITIVE_GROUPS` for every
AQI from 101 through 150, inclusive.

## LLR-ALERT-001 — Alert threshold

`aq_alert_required` shall return `true` for every AQI value greater than or
equal to 151, and `false` otherwise.

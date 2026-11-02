#include "aq_monitor.h"

/**
 * Validates a raw AQI sensor value and returns it to the caller.
 *
 * @param raw_value Raw measurement provided by the sensor.
 * @param measurement Non-null destination for a valid measurement.
 * @return AQ_STATUS_OK for a valid measurement; otherwise AQ_STATUS_RANGE_ERROR.
 * @requirements HLR-004, LLR-SENSOR-001
 * @note Valid input range is 0 through AQ_MAX_VALUE, inclusive.
 */
aq_status_t aq_sensor_read(uint16_t raw_value, uint16_t *measurement)
{
    if (raw_value >= AQ_MAX_VALUE)
    {
        return AQ_STATUS_RANGE_ERROR;
    }

    *measurement = raw_value;
    return AQ_STATUS_OK;
}

/**
 * Initializes a rolling AQI filter.
 *
 * @param filter Filter to initialize.
 * @sideeffect Resets the filter count and insertion index.
 * @requirements HLR-001
 */
void aq_filter_init(aq_filter_t *filter)
{
    filter->count = 0U;
    filter->next_index = 0U;
}

/**
 * Adds one AQI measurement to the rolling filter.
 *
 * @param filter Filter receiving the measurement.
 * @param measurement Valid AQI measurement.
 * @sideeffect Inserts the measurement and advances the rolling insertion index.
 * @requirements HLR-001, LLR-FILTER-001
 */
void aq_filter_add(aq_filter_t *filter, uint16_t measurement)
{
    filter->values[filter->next_index] = measurement;
    filter->next_index = (uint8_t)((filter->next_index + 1U) % AQ_FILTER_CAPACITY);

    if (filter->count < AQ_FILTER_CAPACITY)
    {
        filter->count++;
    }
}

/**
 * Calculates the arithmetic mean of current filter entries.
 *
 * @param filter Filter containing AQI measurements.
 * @return Mean AQI, or zero when no measurements are stored.
 * @requirements HLR-001, LLR-FILTER-002
 */
uint16_t aq_filter_average(const aq_filter_t *filter)
{
    uint32_t sum = 0U;
    uint8_t index;

    for (index = 0U; index < filter->count; index++)
    {
        sum += filter->values[index];
    }

    if (filter->count == 0U)
    {
        return 0U;
    }

    return (uint16_t)(sum / filter->count);
}

/**
 * Maps an AQI value to its health classification.
 *
 * @param aqi AQI value to classify.
 * @return Classification for the provided AQI.
 * @requirements HLR-002, LLR-CLASSIFY-001
 * @note Classification boundaries are defined in HLR-002.
 */
aq_classification_t aq_classify(uint16_t aqi)
{
    if (aqi <= AQ_GOOD_MAX)
    {
        return AQ_CLASS_GOOD;
    }
    if (aqi <= AQ_MODERATE_MAX)
    {
        return AQ_CLASS_MODERATE;
    }
    if (aqi < AQ_SENSITIVE_GROUPS_MAX)
    {
        return AQ_CLASS_UNHEALTHY_FOR_SENSITIVE_GROUPS;
    }
    if (aqi <= AQ_UNHEALTHY_MAX)
    {
        return AQ_CLASS_UNHEALTHY;
    }
    if (aqi <= AQ_VERY_UNHEALTHY_MAX)
    {
        return AQ_CLASS_VERY_UNHEALTHY;
    }

    return AQ_CLASS_HAZARDOUS;
}

bool aq_alert_required(uint16_t average_aqi)
{
    return average_aqi >= AQ_ALERT_THRESHOLD;
}

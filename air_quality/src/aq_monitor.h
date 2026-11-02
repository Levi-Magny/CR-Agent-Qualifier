#ifndef AQ_MONITOR_H
#define AQ_MONITOR_H

#include <stdbool.h>
#include <stdint.h>

#define AQ_FILTER_CAPACITY (4U)
#define AQ_MAX_VALUE (500U)
#define AQ_ALERT_THRESHOLD (151U)
#define AQ_GOOD_MAX (50U)
#define AQ_MODERATE_MAX (100U)
#define AQ_SENSITIVE_GROUPS_MAX (150U)
#define AQ_UNHEALTHY_MAX (200U)
#define AQ_VERY_UNHEALTHY_MAX (300U)

#define AQ_DEMO_READING_GOOD (42U)
#define AQ_DEMO_READING_MODERATE (78U)
#define AQ_DEMO_READING_SENSITIVE (125U)
#define AQ_DEMO_READING_INVALID (520U)
#define AQ_DEMO_READING_UNHEALTHY (180U)

typedef enum
{
    AQ_STATUS_OK = 0,
    AQ_STATUS_RANGE_ERROR
} aq_status_t;

typedef enum
{
    AQ_CLASS_GOOD = 0,
    AQ_CLASS_MODERATE,
    AQ_CLASS_UNHEALTHY_FOR_SENSITIVE_GROUPS,
    AQ_CLASS_UNHEALTHY,
    AQ_CLASS_VERY_UNHEALTHY,
    AQ_CLASS_HAZARDOUS
} aq_classification_t;

typedef struct
{
    uint16_t values[AQ_FILTER_CAPACITY];
    uint8_t count;
    uint8_t next_index;
} aq_filter_t;

aq_status_t aq_sensor_read(uint16_t raw_value, uint16_t *measurement);
void aq_filter_init(aq_filter_t *filter);
void aq_filter_add(aq_filter_t *filter, uint16_t measurement);
uint16_t aq_filter_average(const aq_filter_t *filter);
aq_classification_t aq_classify(uint16_t aqi);
bool aq_alert_required(uint16_t average_aqi);

#endif

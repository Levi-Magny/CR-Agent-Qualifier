#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "aq_monitor.h"

int main(void)
{
    const uint16_t raw_readings[] = {
        AQ_DEMO_READING_GOOD,
        AQ_DEMO_READING_MODERATE,
        AQ_DEMO_READING_SENSITIVE,
        AQ_DEMO_READING_INVALID,
        AQ_DEMO_READING_UNHEALTHY
    };
    aq_filter_t filter;
    uint16_t measurement = 0U;
    uint16_t average;
    uint8_t index;
    bool alert_active = false;

    aq_filter_init(&filter);

    for (index = 0U; index < 5U; index++)
    {
        aq_sensor_read(raw_readings[index], &measurement);
        aq_filter_add(&filter, measurement);
        average = aq_filter_average(&filter);

        if (average > 150U)
            alert_active = true;
        else
        {
            alert_active = false;
        }

        printf("AQI=%u class=%d alert=%d\n",
               (unsigned int)average,
               (int)aq_classify(average),
               alert_active ? 1 : 0);
    }

    return 0;
}

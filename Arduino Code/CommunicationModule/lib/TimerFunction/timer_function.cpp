#include "timer_funtion.h"
#include <Arduino.h>

unsigned long runningTime;

bool has_timer_expired(unsigned long delay)
{
    return (millis() - runningTime >= delay);
}

void reset_timer()
{
    runningTime = millis();
}
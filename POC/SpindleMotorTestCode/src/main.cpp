#include <Arduino.h>

#define SPINDLE_MOTOR_PIN A0
#define RAMP_UP_DELAY 2000

void ramp_up_spindle_motor_rpm();
bool timer_function();

void setup()
{
    Serial.begin(9600);
    pinMode(SPINDLE_MOTOR_PIN, OUTPUT);
}

void loop()
{
    ramp_up_spindle_motor_rpm();
}

void ramp_up_spindle_motor_rpm()
{
    static int analogInput = 0;
    if ((analogInput < 255) && (timer_function()))
    {
        analogWrite(SPINDLE_MOTOR_PIN, ((analogInput += 64) - 1)); //Motor starts spinning at 192
        Serial.println(analogInput);
    }
}

bool timer_function()
{
    static unsigned long pastTime;
    unsigned long currentTime = millis();

    if (currentTime - pastTime >= RAMP_UP_DELAY)
    {
        pastTime = currentTime;
        return true;
    }
    return false;
}
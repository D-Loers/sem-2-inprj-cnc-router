#include "serial_comm.h"

void send_serial_message(String msg)
{
    msg.trim();
    String modifiedMsg = "$" + msg + ";";
    modifiedMsg.trim();
    Serial.println(modifiedMsg);
}

bool retrieve_serial_msg(String *msg)
{
    if (msg == NULL)
    {
        return false;
    }

    *msg = Serial.readStringUntil('\n');
    msg->trim();

    return true;
}

bool wait_on_serial_msg()
{
    return (Serial.available() > 0);
}

uint8_t process_serial_msg(String msg, uint8_t *returnValue)
{
    if (returnValue == NULL)
    {
        return false;
    }

    *returnValue = 0;

    if (msg == "ACK")
    {
        *returnValue = 1;
    }
    else if (msg == "NACK")
    {
        *returnValue = 2;
    }
    else if (msg == "OH")
    {
        *returnValue = 3;
    }

    return true;
}
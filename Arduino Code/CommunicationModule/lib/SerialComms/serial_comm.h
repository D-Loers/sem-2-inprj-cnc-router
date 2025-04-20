#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <Arduino.h>

void send_serial_message(String msg);
bool retrieve_serial_msg(String *msg);
bool wait_on_serial_msg();
uint8_t process_serial_msg(String msg, uint8_t *returnVlaue);

#endif
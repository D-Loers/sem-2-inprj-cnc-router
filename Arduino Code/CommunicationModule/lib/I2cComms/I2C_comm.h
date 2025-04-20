#ifndef I2C_COMM_H
#define I2C_COMM_H

#include <Wire.h>
#include <stdio.h>

#define AMOUNT_OF_INCOMING_BYTE 4

void req_sm_data(uint8_t address);

bool is_sm_data_avaible();

uint16_t get_sm_data();

#endif
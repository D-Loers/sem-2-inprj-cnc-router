#include "I2C_comm.h"

void req_sm_data(uint8_t address)
{
    Wire.requestFrom((int)address, (int)AMOUNT_OF_INCOMING_BYTE);
}

bool is_sm_data_avaible()
{
    return (Wire.available() > 0);
}

uint16_t get_sm_data()
{
    return Wire.read();
}
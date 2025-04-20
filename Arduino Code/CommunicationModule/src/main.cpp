#include <Arduino.h>
#include <DHT20.h>
#include "serial_comm.h"
#include "socket_comm.h"
#include "timer_funtion.h"
#include "I2C_comm.h"
#include <Wire.h>

#define TIMEOUT_DELAY 5000
#define MAX_AMOUNT_OF_ATTEMPS 3
#define ADDR_SM 0x10
#define MAX_TEMP 4000

enum states
{
  INIT,
  WAITING_ON_SOCKET_CONNETION,
  WAITING_ON_SOCKET_MSG,
  PROCESS_SOCKET_MSG,
  TERMINATE_SOCKET_CONNECTION,
  START_PROJECT,
  CHECK_MM_STATUS,
  WAIT_RESP_MM,
  MM_TIMOUT,
  PROCESS_MM_RESP,
  GET_SENSOR_DATA,
  PROCESS_SENSOR_DATA,
  SEND_DATA_TO_APP,
  WAIT_RESP_APP,
  PROCESS_RESP_APP,
};

char network_ssid[] = "LAPTOP-8VAGIICL";
char network_password[] = "{973E33z";

WiFiServer server(8888);
WiFiClient client;
DHT20 dht;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  static states state = INIT;
  static String msg;
  static String *p_msg = &msg;
  static uint8_t returnValue;
  static uint8_t *p_returnValue = &returnValue;
  static uint8_t attempts = 0;
  static float tempReading = 0;
  msgBluePrint socketMsg;

  if (!is_wifi_connected())
  {
    setup_wifi_connection(network_ssid, network_password);
  }

  switch (state)
  {
  case INIT:
  {
    state = WAITING_ON_SOCKET_CONNETION;
    server.begin();
  }
  break;

  case WAITING_ON_SOCKET_CONNETION:
  {
    client = server.available();
    if (client)
    {
      if (client.connected())
      {
        state = WAITING_ON_SOCKET_MSG;
        reset_timer();
      }
    }
  }
  break;

  case WAITING_ON_SOCKET_MSG:
  {
    if (!has_timer_expired(TIMEOUT_DELAY))
    {
      if (is_socket_msg_available(client))
      {
        if (get_socket_msg(p_msg, client))
        {
          state = PROCESS_SOCKET_MSG;
        }
      }
    }
    else
    {
      state = TERMINATE_SOCKET_CONNECTION;
    }
  }
  break;

  case PROCESS_SOCKET_MSG:
  {
    if (process_socket_msg(*p_msg, p_returnValue))
    {
      if (*p_returnValue == 4)
      {
        send_socket_msg("ACK", client);
        state = GET_SENSOR_DATA; // For testing
        reset_timer();
      }
      else if (*p_returnValue == 7 || *p_returnValue == 8 || *p_returnValue == 9)
      {
        send_socket_msg("ACK", client);
        state = GET_SENSOR_DATA; // For testing
        reset_timer();
      }
      else
      {
        attempts++;
        if (attempts >= MAX_AMOUNT_OF_ATTEMPS)
        {
          state = TERMINATE_SOCKET_CONNECTION;
        }
        else
        {
          attempts = 0;
          send_socket_msg("NACK", client);
          state = WAITING_ON_SOCKET_MSG;
        }
      }
    }
  }
  break;

  case TERMINATE_SOCKET_CONNECTION:
  {
    client.flush();
    client.stop();
    state = WAITING_ON_SOCKET_CONNETION;
  }
  break;

    // case START_PROJECT:
    // {
    //   state = CHECK_MM_STATUS;
    // }
    // break;

    // case CHECK_MM_STATUS:
    // {
    //   send_serial_message("$STATUS;");
    //   state = WAIT_RESP_MM;
    // }
    // break;

    // case WAIT_RESP_MM:
    // {
    //   if (!has_timer_expired(TIMEOUT_DELAY))
    //   {
    //     if (wait_on_serial_msg())
    //     {
    //       if (retrieve_serial_msg(p_msg))
    //       {
    //         state = PROCESS_MM_RESP;
    //       }
    //     }
    //   }
    //   else
    //   {
    //     state = MM_TIMOUT;
    //   }
    // }
    // break;

    // case MM_TIMOUT:
    //   socketMsg.errorCode = "ERR_03";
    //   state = SEND_DATA_TO_APP;
    //   break;

    // case PROCESS_MM_RESP:
    //   if (process_serial_msg(*p_msg, p_returnValue))
    //   {
    //     if (*p_returnValue)
    //     {
    //       state = GET_SENSOR_DATA;
    //     }
    //     else
    //     {
    //       state = CHECK_MM_STATUS;
    //     }
    //   }
    //   break;

  case GET_SENSOR_DATA:
  {
    if (dht.read())
    {
      tempReading = dht.getTemperature();
    }
    socketMsg.tempReading = tempReading;
    state = PROCESS_SENSOR_DATA;
  }
  break;

  case PROCESS_SENSOR_DATA:
  {
    if (tempReading <= MAX_TEMP)
    {
      socketMsg.errorCode = "ERR_00";
    }
    else
    {
      socketMsg.errorCode = "ERR_01";
    }
    state = SEND_DATA_TO_APP;
  }
  break;

  case SEND_DATA_TO_APP:
  {
    send_socket_msg(socketMsg, client);
    state = WAIT_RESP_APP;
    reset_timer();
  }
  break;

  case WAIT_RESP_APP:
  {
    if (!has_timer_expired(TIMEOUT_DELAY))
    {
      if (is_socket_msg_available(client))
      {
        if (get_socket_msg(p_msg, client))
        {
          state = PROCESS_RESP_APP;
        }
      }
    }
    else
    {
      state = TERMINATE_SOCKET_CONNECTION;
    }
  }
  break;

  case PROCESS_RESP_APP:
  {
    if (process_socket_msg(*p_msg, p_returnValue))
    {
      if (*p_returnValue == 4)
      {
        send_socket_msg("ACK", client);
        state = WAITING_ON_SOCKET_MSG;
        reset_timer();
      }
      else
      {
        attempts++;
        if (attempts >= MAX_AMOUNT_OF_ATTEMPS)
        {
          state = TERMINATE_SOCKET_CONNECTION;
        }
        else
        {
          attempts = 0;
          send_socket_msg("NACK", client);
          state = SEND_DATA_TO_APP;
        }
      }
    }
  }
  break;
  }
}
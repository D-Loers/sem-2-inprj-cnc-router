#ifndef SOCKET_COMM_H
#define SOCKET_LCOMM_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

typedef struct
{
    String tempReading;
    String errorCode;
    String mmState;

} msgBluePrint;

void setup_wifi_connection(char *ssid, char *password);
bool is_wifi_connected();
bool connect_to_client(WiFiClient *client, WiFiServer server);
bool is_socket_msg_available(WiFiClient client);
bool get_socket_msg(String *socket_msg, WiFiClient client);
void send_socket_msg(String msg, WiFiClient client);
void send_socket_msg(msgBluePrint msg, WiFiClient client);
bool process_socket_msg(String msg, uint8_t *returnValue);

#endif
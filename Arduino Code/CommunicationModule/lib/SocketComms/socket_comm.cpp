#include "socket_comm.h"

void setup_wifi_connection(char *ssid, char *password)
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
        ;
}

bool is_wifi_connected()
{
    return (WiFi.isConnected());
}

bool connect_to_client(WiFiClient *client, WiFiServer server)
{
    if (client == NULL)
    {
        return false;
    }

    while (*client)
    {
        *client = server.available();
    }
    Serial.println("socket found");
    return true;
}

bool is_socket_msg_available(WiFiClient client)
{
    return (client.available() > 0);
}

bool get_socket_msg(String *msg, WiFiClient client)
{
    if (msg == NULL)
    {
        return false;
    }

    *msg = client.readStringUntil('\n');
    msg->trim();

    return true;
}

void send_socket_msg(String msg, WiFiClient client)
{
    msg.trim();
    String modifiedMsg = "$" + msg + ";";
    modifiedMsg.trim();
    client.println(modifiedMsg);
}

void send_socket_msg(msgBluePrint msg, WiFiClient client)
{
    client.println("$" + msg.tempReading + ";" + msg.errorCode + ";" + ";" + msg.mmState + ";");
}

bool process_socket_msg(String msg, uint8_t *returnValue)
{
    if (returnValue == NULL)
    {
        return false;
    }

    if (msg == "$ACK")
    {
        *returnValue = 1;
    }
    else if (msg == "$NACK;")
    {
        *returnValue = 2;
    }
    else if (msg == "$ESTOP;")
    {
        *returnValue = 3;
    }
    else if (msg == "$START;")
    {
        *returnValue = 4;
    }
    else if (msg == "$COMPLETE;")
    {
        *returnValue = 5;
    }
    else if (msg == "$STOP;")
    {
        *returnValue = 6;
    }
    else if (msg.startsWith("G"))
    {
        *returnValue = 7;
    }
    else if (msg.startsWith("F"))
    {
        *returnValue = 8;
    }
    else if (msg.startsWith("M"))
    {
        *returnValue = 9;
    }
    else
    {
        *returnValue = 0;
    }

    return true;
}
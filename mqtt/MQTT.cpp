#include "MQTT.hpp"
#include <cstring>
#include <iostream>

namespace MQTT
{
Client::Client(const char *serverURI, const char *clientId)
{
    int rc{MQTTClient_create(&m_client, serverURI, clientId, MQTTCLIENT_PERSISTENCE_NONE, NULL)};
    if (rc != MQTTCLIENT_SUCCESS)
    {
        throw MQTT::Error("Failed to create client, return code: " + rc);
    };
}

void Client::connect(const char *username, const char *password)
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = username;
    conn_opts.password = password;
    int rc{MQTTClient_connect(m_client, &conn_opts)};
    if (rc != MQTTCLIENT_SUCCESS)
    {
        throw MQTT::Error("Failed to connect, return code: " + rc);
    }
}

void Client::publishMessage(const char *topicName, const char *payload, unsigned long timeoutMs, bool retained)
{
    MQTTClient_deliveryToken token;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = const_cast<void *>(static_cast<const void *>(payload));
    pubmsg.payloadlen = static_cast<int>(strlen(payload));
    pubmsg.qos = m_qos;
    pubmsg.retained = retained;
    int rc{MQTTClient_publishMessage(m_client, topicName, &pubmsg, &token)};
    if (rc != MQTTCLIENT_SUCCESS)
    {
        throw MQTT::Error("Failed to publish message, return code: " + rc);
    }

    rc = MQTTClient_waitForCompletion(m_client, token, timeoutMs);
    if (rc != MQTTCLIENT_SUCCESS)
    {
        throw MQTT::Error("Failed to publish message within the specified timeout, return code: " + rc);
    }

    std::cout << "Message on topic " << topicName << " delivered with token " << token << '\n';
}

void Client::disconnect()
{
    int rc{MQTTClient_disconnect(m_client, m_disconnectTimeoutMs)};
    if (rc != MQTTCLIENT_SUCCESS)
    {
        throw MQTT::Error("Failed to disconnect, return code: " + rc);
    }
}

Client::~Client()
{
    MQTTClient_destroy(&m_client);
}
}; // namespace MQTT

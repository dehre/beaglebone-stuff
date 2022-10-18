#pragma once

#include "MQTTClient.h"
#include <stdexcept>

namespace MQTT
{
class Error : public std::runtime_error
{
  public:
    Error(const char *err) : std::runtime_error{err}
    {
    }
};

class Client
{
  public:
    Client(const char *serverURI, const char *clientId);
    Client(const MQTT::Client &) = delete;
    Client &operator=(const MQTT::Client &) = delete;
    void connect(const char *username = nullptr, const char *password = nullptr);
    void publishMessage(const char *topicName, const char *payload, unsigned long timeoutMs, bool retained = false);
    void disconnect();
    ~Client();

  private:
    MQTTClient m_client{};
    static constexpr int m_qos{1};
    static constexpr int m_disconnectTimeoutMs{5000};
};
}; // namespace MQTT

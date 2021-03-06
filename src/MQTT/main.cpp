#include <iostream>
#include "MQTTClient.h"
#include "MQTTConnectOptions.h"
#include "Utils.h"
#include "NetworkSecurityOptions.h"

void MQTTOnConnected()
{
	LOGI("MQTT connected");
}

void MQTTOnDisconnected()
{
	LOGI("MQTT disconnected");
}

void MQTTOnPublished()
{
	LOGI("Published");
}

void MQTTOnReceived(std::string topic, std::string payload)
{
	LOGI("Topic: %s - Payload: %s", topic.c_str(), payload.c_str());
}

int main()
{
	SOCKET_START
	MQTTConnectOptions connectOptions;
	connectOptions.SetCleanSession(true);
	connectOptions.SetKeepAlive(MQTT_KEEP_ALIVE);
	connectOptions.SetUsername("dinhhuy258");
	connectOptions.SetPassword("123456");
	MQTTClient mqttClient("127.0.0.1", 8883, "MQTTClient");
	mqttClient.MQTTOnReceivedPayload(MQTTOnReceived);
	std::string command;
	NetworkSecurityOptions::enableServerCertificate = true;
	NetworkSecurityOptions::certificateAuthority = "//home/dinhhuy258//Desktop//SSL//mqtt_ca.crt";
	NetworkSecurityOptions::clientCertificate = "//home//dinhhuy258//Desktop//SSL//mqtt_client.crt";
	NetworkSecurityOptions::clientPrivateKey = "//home//dinhhuy258//Desktop//SSL//mqtt_client.key";
	NetworkSecurityOptions::clientPrivateKeyPassword = "123456";
	while (true)
	{
		std::cin >> command;
		if (!command.compare("connect"))
		{
			mqttClient.Connect(connectOptions, true);
		}
		else if (!command.compare("publish"))
		{
			mqttClient.Publish("Hello", "Hello from mqtt", 2, false);
		}
		else if (!command.compare("subscribe"))
		{
			mqttClient.Subscribe("Hello", 1);
		}
		else if (!command.compare("unsubscribe"))
		{
			mqttClient.Unsubscribe("Hello");
		}
		else if (!command.compare("exit"))
		{
			break;
		}
	}
	SOCKET_END
}
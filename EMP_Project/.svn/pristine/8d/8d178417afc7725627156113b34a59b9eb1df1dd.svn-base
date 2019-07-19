/*
 * mqtt.h
 *
 *  Created on: 18.09.2017
 *      Author: mario.richter
 */

#ifndef SOURCE_INCLUDE_MQTT_H_
#define SOURCE_INCLUDE_MQTT_H_

// System header
#include <string>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <MQTTClient.h>
#include "log/logger.h"
#include <jansson.h>

#include <native/task.h>
#include <native/timer.h>

// external library header
#include "GaGCppAPI.h"
#include "GaAppBaseLib.h"




#define GAMMA_UNLOADER_BASE_VAR "UnloaderMqtt.data"

// jansson

/*Sample:
{"DefinitionsID":" XLS_MagazinNutzen.SECS.HER-XLS-DammDisp105",
"Columns":{"Panel":"30E721808037001870000BT","EquipmentName":" HER-XLS-DammDisp105","TS_SECS":"2019000008095056"}}

 */
enum {
    Panel,
	EquipmentName,
	TS_SECS,
    COLUMN_MAX_SIZE
};

enum {
	newTeleTS_SECS,
	newTelePanel,
    newTeleCOLUMN_MAX_SIZE
};


static const char *jsonColumnName[] = {
    "PanelID",
    "EquipmentName",
    "TS_SECS"
};

static const char *newTelejsonColumnName[] = {
    "TS",
    "ContainerId"
};

namespace UnloaderMqtt
{
  void* startThread(void *ptr);

  class mqtt
  {
  public:

	  void taskDisplay(void *arg);


      /*callback functions*/
      void mqttConnlost(void *context, char *cause);
      int mqttMsgArrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
      void mqttDelivered(void *context, MQTTClient_deliveryToken dt);
      /**
       * @short Constructor for the mqtt class used to publish data to a MQTT server.
       * @param _server Name of the MQTT server
       * @param _clientName Name of the client (= own name)
       */
      mqtt(std::string _server, std::string _clientName, std::string _topicSend, std::string _topicRec);
      /**
       * @short Destructor for the mqtt class used to publish data to a MQTT server.
       */
      virtual ~mqtt();

      /**
       * @short gamma service watchdog
       * task done in this thread:
       *  - attach application to gamma service
       *  - check for lost connections
       *  - reconnect, when service is available
       */
      void watchDog();

      /**
       * @short send a message to a mqtt server
       * @param _topic the topic of the new message
       * @param _message the message itself
       * @return true, if message was published
       * @return false, if no mqtt connection is established
       */
      bool sendMessage(std::string _topic, std::string _message);

      /**
       * @short Check if client is connected
       * @return true, if connection is established
       * @return false, if client is disconnected
       */
      bool isClientConnected(void);

      /**
       * @short Callback function signalizes mqtt packet is delivered.
       * @param context the message context
       * @param dt MQTT Client delivery token
       * @return None
       */
      //static void delivered(void *context, MQTTClient_deliveryToken dt);

      /**
       * @short Callback function signalizes arrival of new message.
       * @param context the message context
       * @param topicName the topic name of the arrived message
       * @param topicLen length of the topic
       * @param message the mqtt message that just arrived
       * @return 1, if message was handled (default).
       */
      //static int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);

      /**
       * @short Callback function signalizes connection loss.
       * @param context the message context
       * @param cause the cause for the connection loss
       * @return None
       */
      //static void connlost(void *context, char *cause);

    private:
      /**
       * @short Start the watchdog function which creates a thread to supervise the MQTT connection.
       * @return None.
       */
      void startWatchDog();

      /**
       * @short Start the watchdog thread.
       * @param ptr pointer to thread (passed from pthread_create)
       * @return None.
       */
      //void* startThread(void *ptr);

      /**
       * @short Reset (to 0) a thread pointer.
       * @param _pt Thread pointer to set to zero.
       * @return None
       */
      void resetThreadPT(pthread_t& _pt);

      /**
       * @short Check if thread pointer is 0.
       * @return false, if pointer is not zero.
       * @return true, if pointer is zero.
       */
      bool threatPTisNull (pthread_t& _pt);



      /**
       * @short Token to check if the MQTT message was delivered
       */
      volatile MQTTClient_deliveryToken deliveredtoken;

      /**
       * @short the MQTT client
       */
      MQTTClient client;

      /**
       * @short MQTT server name
       */
      std::string server;

      /**
       * @short MQTT client name (= own name)
       */
      std::string clientName;

      /**
       * @short watch dog task handle
       */
      pthread_t mWatchDogTask;

      /**
       * @short mutex to wake watch dog up
       */
      pthread_mutex_t mWatchDogWakeUp;

      /**
       * @short signal to watch dog thread => terminate thread
       */
      bool mWatchDocAbbort;

      uint32_t    mqtt_telegram_timestamp, mqtt_telegram_counter;
      bool        mqtt_error_connection, mqtt_error_initial_connection;

      std::string loggerName;

      char       time_hms[20];
 /*     std::string xmlMqttAddress;
      std::string xmlMqttClientId;
      std::string xmlMqttTopic;
      uint32_t    xmlMqttTimeout;*/
      std::string MqttTopicSend;
      std::string MqttTopicRec;

      json_t  *jsonName, *jsonVersion, *jsonColumns;
      json_t  *jsonColumnValue[COLUMN_MAX_SIZE];

      const std::string gammaBaseVar = GAMMA_UNLOADER_BASE_VAR;
      std::string mqttTeleVersion;

      std::string SecsGemPanelId;
      std::string SecsGemEquipmentName;
      std::string SecsGemTimeStamp;
      bool		  newSecsGemPanelId;

    public:

	  //getter setter
      bool getNewSecsGemPanelId()
      {
    	  return newSecsGemPanelId;
      }

      void ackNewSecsGemPanelId()
      {
    	  newSecsGemPanelId = false;
      }

      std::string getSecsGemPanelId()
	  {
		  return SecsGemPanelId;
	  }
      std::string getSecsGemEquipmentName()
	  {
    	  return SecsGemEquipmentName;
	  }
      std::string getSecsGemTimeStamp()
      {
    	  return SecsGemTimeStamp;
      }

  };
}

#endif /* SOURCE_INCLUDE_MQTT_H_ */

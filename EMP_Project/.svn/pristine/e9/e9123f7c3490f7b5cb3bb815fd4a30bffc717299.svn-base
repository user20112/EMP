/*
 * mqtt.cpp
 *
 *  Created on: 18.09.2017
 *      Author: mario.richter
 */

#include "mqtt.h"

#include <time.h>
#include <stdexcept>
#include <iostream>
#define MQTT_QOS 2

namespace UnloaderMqtt
{

// **************************************************************************************************
    // ** wrapper functions for callbacks
    // **************************************************************************************************
/*    void taskDisplayCallback(void *arg)
    {
    	mqtt* inst = reinterpret_cast<mqtt*>(arg);
        if (inst != nullptr)
            inst->taskDisplay();
    }
*/
    void mqttConnlostCallback(void *context, char *cause)
    {
    	mqtt* inst = reinterpret_cast<mqtt*>(context);
        if (inst != nullptr)
        {
            inst->mqttConnlost(context, cause);
        }
    }

    int mqttMsgArrvdCallback(void *context, char *topicName, int topicLen, MQTTClient_message *message)
    {
    	mqtt* inst = reinterpret_cast<mqtt*>(context);
        if (inst != nullptr)
            return inst->mqttMsgArrvd(context, topicName, topicLen, message);
        else
            return 1;
    }

    void mqttDeliveredCallback(void *context, MQTTClient_deliveryToken dt)
    {
    	mqtt* inst = reinterpret_cast<mqtt*>(context);
        if (inst != nullptr)
            inst->mqttDelivered(context, dt);
    }


  // **************************************************************************************************
  // ** mqtt constructor
  // **************************************************************************************************

    mqtt::mqtt(std::string _server, std::string _clientName,  std::string _topicSend, std::string _topicRec)
    :server (_server),
	clientName (_clientName),
    MqttTopicSend(_topicSend),
    MqttTopicRec(_topicRec)
  {
    int result = 0;
    loggerName = "mqtt";
    SecsGemPanelId = "ERROR";	// wie bei Cognex
    SecsGemEquipmentName = "NULL";
    SecsGemTimeStamp = "NULL";
    newSecsGemPanelId = false;
    mqttTeleVersion="-1";
    el::Loggers::getLogger(loggerName.c_str());

    CLOG(INFO, loggerName.c_str()) << "create MQTT client "<< clientName << " (connect to server: " << server << ")";

    result = MQTTClient_create(&client, server.append(":1883").c_str(), clientName.c_str(), MQTTCLIENT_PERSISTENCE_NONE, nullptr);
    //alt result = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    result = MQTTClient_setCallbacks(client, (void*) this, mqttConnlostCallback, mqttMsgArrvdCallback, mqttDeliveredCallback);
    resetThreadPT(mWatchDogTask);
    mWatchDogWakeUp = PTHREAD_MUTEX_INITIALIZER;
    mWatchDocAbbort = false;

    pthread_mutex_lock(&mWatchDogWakeUp);
    result = pthread_create(&mWatchDogTask, NULL, startThread, (void*)this);
    if (result)
    {
      throw std::logic_error("create watchdog thread failed");
    }
  }

  // **************************************************************************************************
  // ** mqtt destructor
  // **************************************************************************************************
  mqtt::~mqtt()
  {
    CLOG(INFO, loggerName.c_str()) << "destroy MQTT client "<< clientName;
    pthread_mutex_unlock(&mWatchDogWakeUp);
    mWatchDocAbbort = true;
    pthread_join(mWatchDogTask, NULL);
    resetThreadPT(mWatchDogTask);

    MQTTClient_destroy(&client);
  }

  // **************************************************************************************************
  // ** sendMessage
  // **************************************************************************************************
  bool mqtt::sendMessage(std::string _topic, std::string _message)
  {
    if (MQTTClient_isConnected(client))
    {
      MQTTClient_message pubmsg = MQTTClient_message_initializer;
      MQTTClient_deliveryToken token;

      pubmsg.payload = (void*)_message.c_str();
      pubmsg.payloadlen = _message.size();
      pubmsg.retained = 0;

      MQTTClient_publishMessage(client, _topic.c_str(), &pubmsg, &token);
      return (true);
    }
    else
    {
      return (false);
    }
  }

  // **************************************************************************************************
  // ** watchDog
  // **************************************************************************************************
  void mqtt::watchDog(void)
  {
    int retryTime = 2;

    CLOG(INFO, loggerName.c_str()) << "monitoring of MQTT service connection started.";

    do
    {
      if (MQTTClient_isConnected(client))
      {
        retryTime = 2;
      }
      else
      {
        int rc;
        MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
        conn_opts.keepAliveInterval = 20;
        conn_opts.cleansession = 1;

        if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
        {
          CLOG(ERROR, loggerName.c_str()) << "connect MQTT service failed: return code " << rc;
          retryTime = 5;
        }
        else
        {

          MQTTClient_subscribe(client,MqttTopicRec.c_str(), MQTT_QOS);
          CLOG(INFO,loggerName.c_str()) << clientName << " subscribe to " << MqttTopicRec;

          CLOG(INFO, loggerName.c_str()) << "MQTT service becomes alive again";
          retryTime = 2;
        }
      }

      // wait some time or until thread is waked up by parent
      struct timespec abs_time = {0};
      time_t timeNow = time(NULL);
      abs_time.tv_sec = timeNow + retryTime;

      pthread_mutex_timedlock(&mWatchDogWakeUp, &abs_time);
    } while (!mWatchDocAbbort);

    if (MQTTClient_isConnected(client))
    {
      MQTTClient_disconnect(client, 10000);
    }

    CLOG(INFO, loggerName.c_str()) << "monitoring of MQTT service connection stopped. Application is detached from service!";
  }

  // **************************************************************************************************
  // ** resetThreadPT
  // **************************************************************************************************
  void mqtt::resetThreadPT(pthread_t& _pt)
  {
    _pt = 0L;
  }

  // **************************************************************************************************
  // ** threatPTisNull
  // **************************************************************************************************
  bool mqtt::threatPTisNull (pthread_t& _pt)
  {
    return (_pt == 0L);
  }

  // **************************************************************************************************
  // ** isClientConnected
  // **************************************************************************************************
  bool mqtt::isClientConnected(void)
  {
    if(MQTTClient_isConnected(client))
      return true;
    else
      return false;
  }

  // **************************************************************************************************
  // ** startThread
  // **************************************************************************************************
  void* startThread(void *ptr)
  {
    if (ptr != nullptr)
    {
      mqtt* m = (mqtt*)(ptr);
      m->watchDog();
    }
    return (nullptr);
  }

  // **************************************************************************************************
  // ** delivered
  // **************************************************************************************************
  void mqtt::mqttDelivered(void *context, MQTTClient_deliveryToken dt)
  {
  }

  // **************************************************************************************************
  // ** msgarrvd
  // **************************************************************************************************
  int mqtt::mqttMsgArrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
  {
      uint32_t columnIndex;

      json_t *root;
      json_error_t error;
      //char    *mqtt_payload;

      mqtt_error_connection = false;

      mqtt_telegram_timestamp = time(NULL);
      mqtt_telegram_counter++;
      /*printf("\n MessageArrvd \n");*/
      if(!message)
      {
    	  /*CLOG(DEBUG, loggerName.c_str())<< "Message = NULL";*/
    	  printf("\n MessageArrvd 0 \n");
      }
      else
      {
    	  /*CLOG(DEBUG, loggerName.c_str())<< "strlen(payload): " << strlen((char*)message->payload)
    	        << " payloadlen: "<< message->payloadlen
				<< " payload: " << (char*)message->payload
				<< "END";
    	  printf("\n MessageArrvd 1 \n");*/
      }

      root = json_loads((char*) message->payload, JSON_DISABLE_EOF_CHECK, &error);

      if (!root)
      {
          /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: json_loads [" << error.line << "]->[" << error.text << "]"
          << "strlen(payload): " << strlen((char*)message->payload)
          << " payloadlen: "<< message->payloadlen
		  << "END";
          printf("\n MessageArrvd 2 \n");*/
          MQTTClient_freeMessage(&message);
          MQTTClient_free(topicName);
          return(false);
      }
      if (!json_is_object(root))
      {
          /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: !json_is_object(root)"
        		  << "json.type: " << root->type
				  << "json.refcount" << root->refcount<< "END";
          printf("\n MessageArrvd 3 \n");*/
          json_decref(root);
          MQTTClient_freeMessage(&message);
          MQTTClient_free(topicName);
          return(false);
      }


		jsonVersion = json_object_get(root, "Version");
		if (!json_is_string(jsonVersion))
		{
			mqttTeleVersion="0";
			//CLOG(DEBUG, loggerName.c_str())<< "ERROR: !json_is_string(jsonVersion)";
			//printf("\n MessageArrvd 6 \n");
			//const char *key;
			//json_t *value;
			//int i=0;
			//json_object_foreach(root, key, value) {
				// block of code that uses key and value
			 // i++;
			  /*CLOG(DEBUG, loggerName.c_str())<< "DEBUG: json.key " << i << ": " << key << " != " << "Version";*/
			 // printf("\n MessageArrvd 7 \n");
			//}
			//json_decref(root);
			//MQTTClient_freeMessage(&message);
			//MQTTClient_free(topicName);
			//return(false);
		}
		else
		{
			mqttTeleVersion = json_string_value(jsonVersion);
			//syslog(LOG_ERR,"DEBUG: jsonVersion[%s]  %s,(%d)\n",json_string_value(jsonVersion), __FILE__, __LINE__);
			//printf("\n MQTT-Telegram Version: %s \n",mqttTeleVersion.c_str());
			/*CLOG(DEBUG, loggerName.c_str())<< "MQTT-Telegram Version: " << json_integer_value(jsonVersion);*/
		}
      if(std::atoi(mqttTeleVersion.c_str())<1)
      {// altes Telegramm

		  jsonName = json_object_get(root, "DefinitionId");
		  if (!json_is_string(jsonName))
		  {
			  /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: !json_is_string(jsonName)";
			  printf("\n MessageArrvd 4 \n");*/
			  const char *key;
			  json_t *value;
			  int i=0;
			  json_object_foreach(root, key, value) {
				  /* block of code that uses key and value */
				  i++;
				  /*CLOG(DEBUG, loggerName.c_str())<< "DEBUG: json.key " << i << ": " << key << " != " << "DefinitionID";
				  printf("\n MessageArrvd 5 \n");*/
			  }

			  json_decref(root);
			  MQTTClient_freeMessage(&message);
			  MQTTClient_free(topicName);
			  return(false);
		  }
		  //syslog(LOG_ERR,"DEBUG: jsonName[%s]  %s,(%d)\n",json_string_value(jsonName), __FILE__, __LINE__);

		  jsonColumns = json_object_get(root, "Columns");
		  if (!json_is_object(jsonColumns))
		  {
			  /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: !json_is_object(jsonColumns)";
			  printf("\n MessageArrvd 8 \n");*/
			  json_decref(root);
			  MQTTClient_freeMessage(&message);
			  MQTTClient_free(topicName);
			  return(false);
		  }

		  for (columnIndex = 0; columnIndex < COLUMN_MAX_SIZE; columnIndex++)
		  {
			  jsonColumnValue[columnIndex] = json_object_get(jsonColumns, jsonColumnName[columnIndex]);
			  if (!json_is_string(jsonColumnValue[columnIndex]))
			  {
				  /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: !json_is_string(jsonColumnValue[columnIndex])";
				  printf("\n MessageArrvd  9 \n");*/
				  json_decref(jsonColumns);
				  MQTTClient_freeMessage(&message);
				  MQTTClient_free(topicName);
				  return(false);
			  }
			  //syslog(LOG_ERR,"DEBUG: jsonColumnValue[%s]->[%s]  %s,(%d)\n", jsonColumnName[columnIndex], json_string_value(jsonColumnValue[columnIndex]), __FILE__, __LINE__);
		  }
		  if (json_string_value(jsonColumnValue[Panel]) != SecsGemPanelId)
		  {
			  // New ID received
			  SecsGemPanelId		= json_string_value(jsonColumnValue[Panel]);					// Panel ID: 30E721808037001870000BT --> Nutzen ID ersetzt bisherigen Wert von Cognex Reader
			  SecsGemEquipmentName	= json_string_value(jsonColumnValue[EquipmentName]);	// EquipmentName: HER-XLS-DammDisp105
			  SecsGemTimeStamp		= json_string_value(jsonColumnValue[TS_SECS]);
			  newSecsGemPanelId = true;

			  /*CLOG(DEBUG, loggerName.c_str())<< "New PanelID(" << SecsGemPanelId << ") EquipmentName: " << SecsGemEquipmentName << " Time: " << SecsGemTimeStamp;
			  printf("\n MessageArrvd 10 \n");*/
		  }
		  else
		  {
			  // Duplicated ID received
			  // sollte nicht vorkommen, weil Topic update nur bei Änderung kommt
			  // fals es trotzdem kommt, wurde was falsches von SECS Gem eingetragen!
			  /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: Duplicated PanelID (" << json_string_value(jsonColumnValue[Panel]) <<") Time: " << json_string_value(jsonColumnValue[TS_SECS]) << " EquipmentName: " << json_string_value(jsonColumnValue[EquipmentName]);
			  printf("\n MessageArrvd 11 \n");*/
		  }
      }
      else
      {// neues Telegramm nach XLS2 Standard
    	  jsonName = json_object_get(root, "Source");
		  if (!json_is_string(jsonName))
		  {
			  /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: !json_is_string(jsonName)";
			  printf("\n MessageArrvd 4 \n");*/
			  const char *key;
			  json_t *value;
			  int i=0;
			  json_object_foreach(root, key, value) {
				  /* block of code that uses key and value */
				  i++;
				  /*CLOG(DEBUG, loggerName.c_str())<< "DEBUG: json.key " << i << ": " << key << " != " << "DefinitionID";
				  printf("\n MessageArrvd 5 \n");*/
			  }

			  json_decref(root);
			  MQTTClient_freeMessage(&message);
			  MQTTClient_free(topicName);
			  return(false);
		  }
		  //syslog(LOG_ERR,"DEBUG: jsonName[%s]  %s,(%d)\n",json_string_value(jsonName), __FILE__, __LINE__);

		  jsonColumns = json_object_get(root, "Data");
		  if (!json_is_object(jsonColumns))
		  {
			  /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: !json_is_object(jsonColumns)";*/
			  printf("\n MessageArrvd 8 \n");
			  json_decref(root);
			  MQTTClient_freeMessage(&message);
			  MQTTClient_free(topicName);
			  return(false);
		  }

		  for (columnIndex = 0; columnIndex < newTeleCOLUMN_MAX_SIZE; columnIndex++)
		  {
			  jsonColumnValue[columnIndex] = json_object_get(jsonColumns, newTelejsonColumnName[columnIndex]);
			  if (!json_is_string(jsonColumnValue[columnIndex]))
			  {
				  /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: !json_is_string(jsonColumnValue[columnIndex])";
				  printf("\n MessageArrvd  9 \n");*/
				  json_decref(jsonColumns);
				  MQTTClient_freeMessage(&message);
				  MQTTClient_free(topicName);
				  return(false);
			  }
			  //syslog(LOG_ERR,"DEBUG: jsonColumnValue[%s]->[%s]  %s,(%d)\n", jsonColumnName[columnIndex], json_string_value(jsonColumnValue[columnIndex]), __FILE__, __LINE__);
		  }
		  if (json_string_value(jsonColumnValue[newTelePanel]) != SecsGemPanelId)
		  {
			  // New ID received
			  SecsGemPanelId		= json_string_value(jsonColumnValue[newTelePanel]);					// Panel ID: 30E721808037001870000BT --> Nutzen ID ersetzt bisherigen Wert von Cognex Reader
			  SecsGemEquipmentName	= json_string_value(jsonName);	// EquipmentName: HER-XLS-DammDisp105
			  SecsGemTimeStamp		= json_string_value(jsonColumnValue[newTeleTS_SECS]);
			  newSecsGemPanelId = true;

			  /*CLOG(DEBUG, loggerName.c_str())<< "New PanelID(" << SecsGemPanelId << ") EquipmentName: " << SecsGemEquipmentName << " Time: " << SecsGemTimeStamp;*/
			  //printf("\n MessageArrvd 10 \n");
		  }
		  else
		  {
			  // Duplicated ID received
			  // sollte nicht vorkommen, weil Topic update nur bei Änderung kommt
			  // fals es trotzdem kommt, wurde was falsches von SECS Gem eingetragen!
			  /*CLOG(DEBUG, loggerName.c_str())<< "ERROR: Duplicated PanelID (" << json_string_value(jsonColumnValue[Panel]) <<") Time: " << json_string_value(jsonColumnValue[TS_SECS]) << " EquipmentName: " << json_string_value(jsonColumnValue[EquipmentName]);
			  printf("\n MessageArrvd 11 \n");*/
		  }
      }
      MQTTClient_freeMessage(&message);
      MQTTClient_free(topicName);
      return (true);
  }

  // **************************************************************************************************
  // ** connlost
  // **************************************************************************************************
  void mqtt::mqttConnlost(void *context, char *cause)
  {
    if (cause != nullptr)
      std::cerr << "connect MQTT service lost: \"" << cause << "\"" << std::endl;
    else
      std::cerr << "connect MQTT service lost: unknown reason" << std::endl;
  }

}



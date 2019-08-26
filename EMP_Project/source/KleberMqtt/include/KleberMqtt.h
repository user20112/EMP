/*
 * KleberMqtt.h
 *
 *  Created on: 21.11.2017
 *      Author: mario.richter
 */

#ifndef SOURCE_KLEBERMQTT_INCLUDE_KLEBERMQTT_H_
#define SOURCE_KLEBERMQTT_INCLUDE_KLEBERMQTT_H_

// System header
#include <string>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>

#include <ncurses.h>
#include <jansson.h>

#include <MQTTClient.h>

#include <native/task.h>
#include <native/timer.h>

// external library header
#include "GaGCppAPI.h"
#include "GaAppBaseLib.h"

// standard logger name
#define LOGGER_NAME             "KleberMqtt"
#define GAMMA_BASE_VAR          "KleberMqtt.data"

// define times in ns
#define ms  1000000
#define us     1000

#define MQTT_QOS                2
#define MQTT_RECONNECT_DELAY    1000001     // in microseconds

// interrupt times
#define TIME_DISPLAY       (313*ms)

// xml IO's
typedef struct {
    std::string Function;
    uint32_t    no;
    bool        use;
}IO;

// jansson
enum {
    Headline_1,
    Headline_2_1,
    Headline_2_2,
    Potlifetime_Absolute,
    Potlifetime_Remaining,
    Message,
    ColorHeadline_1_Background,
    ColorHeadline_1_Textcolor,
    ColorHeadline_2_1_Background,
    ColorHeadline_2_1_Textcolor,
    ColorHeadline_2_2_Background,
    ColorHeadline_2_2_Textcolor,
    ColorPotlifetime_Background,
    ColorPotlifetime_Textcolor,
    ColorMessage_Background,
    ColorMessage_Textcolor,
    SignalTower_Green,
    SignalTower_Yellow,
    SignalTower_Red,
    SignalTower_Buzzer,
    COLUMN_MAX_SIZE
};

static const char *jsonColumnName[] = {
    "Headline_1",
    "Headline_2_1",
    "Headline_2_2",
    "Potlifetime_Absolute",
    "Potlifetime_Remaining",
    "Message",
    "ColorHeadline_1_Background",
    "ColorHeadline_1_Textcolor",
    "ColorHeadline_2_1_Background",
    "ColorHeadline_2_1_Textcolor",
    "ColorHeadline_2_2_Background",
    "ColorHeadline_2_2_Textcolor",
    "ColorPotlifetime_Background",
    "ColorPotlifetime_Textcolor",
    "ColorMessage_Background",
    "ColorMessage_Textcolor",
    "ColorSignalTower_Green",
    "ColorSignalTower_Yellow",
    "ColorSignalTower_Red",
    "BuzzerActive"
};


// realtime task
//void task_display(void *arg);


namespace KleberMqtt {

  void taskDisplay(void *arg);

  /**
   * @short TODO: add your module description here
   */
  class KleberMqtt : public GaAppBaseLib::ModuleInterface, public GaGCppAPI::GaTask
  {
    public:
      /**
       * @short constructor
       *
       * @remark
       * don't add more input parameter, because the calling function wouldn't know them!
       *
       * __actual situation__
       *
       * the constructor is called during all modules will be loaded. There is no guarantee witch modules are active now.
       * During the construction the module is only for its own and should not try to connect to other modules.
       *
       * __jobs to do here__
       *  - parse xml configuration and setup this instance
       *  - create and connect to own gamma variables and scheduler slots
       *
       * @param _instanceName name of this instance
       * @param _configInfo pointer to xml configuration node
       */
      KleberMqtt(const char* _instanceName,
          pugi::xml_node* _configInfo);

      /**
       * @short destructor
       *
       * __actual situation__
       *
       * the application is shutting down and unload all modules.
       *
       * __jobs to do here__
       *  - Clean up your stuff
       */
      ~KleberMqtt();

      /**
       * @short method will be called by application before cycle task will be started
       *
       * __actual situation__
       *
       * all modules are loaded and the gamma middleware contain all needed variables, but the values do not necessarily have to be valid!
       *
       * __jobs to do here__
       *  - browse gamma variables
       *  - connect to other modules
       *
       */
      virtual void prepareStart();

      /**
       * @short method will be called by application after cycle task is stopped
       *
       * __actual situation__
       *
       * all cyclic task and scheduler are stopped. This is the last chance to get values from gamma. During this call no values should be changed anymore.
       *
       * __jobs to do here__
       *  - make needed backups
       *  - disconnect from gamma
       */
      virtual void cleanUp();

      /**
       * @short general command interface
       *
       * the application has a user terminal. Commands can be forwarded to a module by using the syntax [moduleName]:[command] [args...]
       * This function will be called, when a command for this module is given to the terminal.
       *
       * @param _cmdLine command as string including all arguments
       */
      virtual void execCommand(std::string& _cmdLine);

      // Mqtt callbacks
      void mqttConnlost(void *context, char *cause);
      int mqttMsgArrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
      void mqttDelivered(void *context, MQTTClient_deliveryToken dt);

      uint8_t toColor(json_t  *buff);

      void taskDisplay();
      MQTTClient client;

    protected:
      /**
       *
       * @return
       */
      virtual int32_t taskInit() noexcept;

      /**
       *
       * @return
       */
      virtual int32_t taskDeinit() noexcept;

      /**
       *
       * @param taskHandle
       * @param frameNumber
       * @return
       */
      virtual int32_t taskRun(gs_Task taskHandle, const uint32_t* frameNumber) noexcept;

    private:

      FILE *fd;
      SCREEN *scr;

      bool isMqttConfBad;

      std::string mGammaPathBase;                     ///< @short path base to gamma PV's
      std::string mGammaSlot;                         ///< @short name of gamma scheduler slot

      RT_TASK display_task;

      MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

      uint32_t    mqtt_telegram_timestamp, mqtt_telegram_counter;
      bool        mqtt_error_connection, mqtt_error_initial_connection;

      char       time_hms[20];
      std::string xmlMqttAddress;
      std::string xmlMqttClientId;
      std::string xmlMqttTopic;
      uint32_t    xmlMqttTimeout;

      json_t  *jsonName, *jsonVersion, *jsonColumns;
      json_t  *jsonColumnValue[COLUMN_MAX_SIZE];

      uint32_t inputCount, outputCount;
      IO xmlInput[8], xmlOutput[8];

      bool    jsonSignalTower_Green;
      bool    jsonSignalTower_Yellow;
      bool    jsonSignalTower_Red;
      bool    jsonSignalTower_Buzzer;
      bool    buzzerConfirmed;

      uint32_t  inConfirmation_Button;        // input/output numbers; if 0, I/O is not used.
      uint32_t  outSignalTower_Green;
      uint32_t  outSignalTower_Yellow;
      uint32_t  outSignalTower_Red;
      uint32_t  outSignalTower_Buzzer;

      GaGCppAPI::TypedPV<uint8_t>     digInConfirmButton;
      GaGCppAPI::TypedPV<uint8_t>     digOutSignalGreen;
      GaGCppAPI::TypedPV<uint8_t>     digOutSignalYellow;
      GaGCppAPI::TypedPV<uint8_t>     digOutSignalRed;
      GaGCppAPI::TypedPV<uint8_t>     digOutSignalBuzzer;
      GaGCppAPI::TypedPV<uint8_t>     digOutErrorStatus;

      const std::string mLoggerName = LOGGER_NAME;
      const std::string gammaBaseVar = GAMMA_BASE_VAR;

      uint16_t taskCounter;
  };
}

#endif /* SOURCE_KLEBERMQTT_INCLUDE_KLEBERMQTT_H_ */

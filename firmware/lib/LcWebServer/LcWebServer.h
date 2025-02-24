#ifndef LCWEBSERVER_H
#define LCWEBSERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Cfg.h>

/**
 * @defgroup LcWebServer web server class for LocoCard Emulator
 *
 * @{
 */
/**

* @brief class for hold information of a web connection
*/
class LcWebServer
{
   public:
      LcWebServer(Cfg *ActualConfig) { Config = ActualConfig; WebServer = new ESP8266WebServer; };
      void Start(void);
      void SetUriCb(const Uri &uri, TrivialCB handler);
      void HandleClient(void);
      void HandleRootPage(void);
      void HandleConfigPage(void);
      void HandleLocoPage(void);
      void HandleConfigGet(void);
   private:
      ESP8266WebServer *WebServer;
      Cfg *Config;
};

/** @} */

#endif

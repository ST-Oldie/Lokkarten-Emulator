#ifndef LCWEBSERVER_H
#define LCWEBSERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <map>
#include <Cfg.h>
#include <loco.h>
#include <LocoCard.h>

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
      LcWebServer(Cfg *ActualConfig);
      void Start(void);
      void SetUriCb(const Uri &uri, TrivialCB handler);
      void HandleClient(void);
      void HandleRootPage(void);
      void HandleConfigPage(void);
      void HandleLocoPage(void);
      void HandleEmptyPage(void);
      void HandleConfigGet(void);
      void HandleLoco2Card(void);
      void HandleRemCard(void);
      void HandleSaveCard(void);
   private:
      ESP8266WebServer *WebServer;
      Loco Lokomotive;
      LocoCard VirtLokKarte;
      Cfg *Config;
      std::map<int, char *> FileNames;
};

/** @} */

#endif

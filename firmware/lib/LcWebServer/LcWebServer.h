#ifndef LCWEBSERVER_H
#define LCWEBSERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

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
      LcWebServer();
      void Start(void);
      String GetRequestGETParameter(void);
      void SendHTMLPage(String HTMLPage);
      String GetWebRequestHostAddress(void) { return WebRequestHostAddress; };
   private:
      WiFiClient Client;
      WiFiServer *Server;
      String WebRequestHostAddress;
};

/** @} */

#endif

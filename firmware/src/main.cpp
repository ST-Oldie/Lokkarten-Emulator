#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <ESP8266WiFi.h>
#include <Cfg.h>
#include <LocoSet.h>
#include <LocoCard.h>
#include <loco.h>
#include <LcWifi.h>
#include <LcWebServer.h>
#include <HtmlPages.h>

/* define fuer Test der Basisklassen fuer Lok, Lokliste, ... */
//#define TEST_BASIC

/**
* @mainpage Lokkartenemulator
*
* Firmware f&uuml;r die Hardware des Lokkarten-Emulators
*
* @author Michael Bernstein
*/

#define SPI_MISO    12
#define SPI_MOSI    13
#define SPI_CLK     14
#define SPI_CS      15

LocoSet LokSatz;
LocoCard VirtLokKarte;
Loco Lokomotive;
Cfg Config;
LcWifi WifiClientServer;
LcWebServer WifiWebServer;

#ifdef TEST_BASIC
#include "test_basic.h"
#endif

void setup(void)
{
   Config.ReadIniconfig();
#ifdef TEST_BASIC
   test_basic_setup();
#else
   Serial.begin(115200);
   WifiClientServer.SetBothModesNetworkStationAndAccessPoint();
   WifiClientServer.Connect(Config.GetCfgVal(CFG_VALUE_SSID), Config.GetCfgVal(CFG_VALUE_PASSWORD));
   WifiClientServer.AccessPointStart((char *)"Lokkartenemulator");
   WifiWebServer.Start();
#endif
}

void loop(void)
{
#ifdef TEST_BASIC
   test_basic_loop();
#else
   String GETParameter;
  
   GETParameter = WifiWebServer.GetRequestGETParameter();
   if (GETParameter.length() > 0)
   {
      // we got a request, client connection stays open
      if (GETParameter.length() > 1)
      {
         // request contains some GET parameter
         DecGETConfigValues(GETParameter, Config);
         if (WifiWebServer.GetWebRequestHostAddress() == "192.168.4.1")
         {  char *SSID, *Password;

            Config.WriteIniconfig();
            SSID = Config.GetCfgVal(CFG_VALUE_SSID);
            Password = Config.GetCfgVal(CFG_VALUE_PASSWORD);
            WifiClientServer.Disconnect();
            WifiClientServer.Connect(SSID, Password);
         }
      }

      String HTMLPageWithConfigForm;

      if (WifiWebServer.GetWebRequestHostAddress() == "192.168.4.1")                  //   the user entered this address in the browser, to get the configuration webpage               
      {
         WifiClientServer.SetBothModesNetworkStationAndAccessPoint();
         HTMLPageWithConfigForm = EncHTMLConfigValues("ESP32 Webserver CONFIG", Config) + "<br>IP Address: " + WifiClientServer.GetOwnIPAddressInRouterNetwork();       // build a new Configuration webpage with form and new ConfigValues entered in textboxes
      }
      else                                                         // the user entered the ESP32 address in router network in the browser, to get normal webpage
      {
         HTMLPageWithConfigForm = EncHTMLConfigValues("ESP32 Webserver Demo", Config);                                       // build a new webpage to control the LED
      }

      WifiWebServer.SendHTMLPage(HTMLPageWithConfigForm);    // send out the webpage to client = webbrowser and close client connection
   }
   delay(50);
#endif
}

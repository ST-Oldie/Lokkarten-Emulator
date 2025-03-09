#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <ESP8266WiFi.h>
#include <LocoCard.h>
#include <Cfg.h>
#include <LcWifi.h>
#include <LcWebServer.h>

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

#ifdef TEST_BASIC
LocoSet LokSatz;
LocoCard VirtLokKarte;
Loco Lokomotive;
#endif
Cfg *Config;
LcWifi *WifiClientServer;
LcWebServer *WifiWebServer;

#ifdef TEST_BASIC
#include "test_basic.h"
#else
void LcHandleRootPage()
{
   WifiWebServer->HandleRootPage();
}

void LcHandleConfigPage()
{
   WifiWebServer->HandleConfigPage();
}

void LcHandleLocoPage()
{
   WifiWebServer->HandleLocoPage();
}

void LcHandleEmptyPage()
{
   WifiWebServer->HandleEmptyPage();
}

void LcHandleConfigGet()
{
   WifiWebServer->HandleConfigGet();
}

void LcHandleLoco2Card()
{
   WifiWebServer->HandleLoco2Card();
}

void LcHandleRemCard()
{
   WifiWebServer->HandleRemCard();
}

void LcHandleSaveCard()
{
   WifiWebServer->HandleSaveCard();
}
#endif

void setup(void)
{
   SD.begin(SPI_CS);
   Config = new Cfg;
   Config->ReadIniconfig();
#ifdef TEST_BASIC
   test_basic_setup();
#else
#ifdef DEBUG_OUTPUT
   Serial.begin(115200);
#endif
   WifiClientServer = new LcWifi(Config);
   WifiWebServer = new LcWebServer(Config);
   WifiClientServer->Start();
   WifiWebServer->SetUriCb((const char *)"/", LcHandleRootPage);
   WifiWebServer->SetUriCb((const char *)"/config.htm", LcHandleConfigPage);
   WifiWebServer->SetUriCb((const char *)"/loco.htm", LcHandleLocoPage);
   WifiWebServer->SetUriCb((const char *)"/empty.htm", LcHandleEmptyPage);
   WifiWebServer->SetUriCb((const char *)"/config_action", LcHandleConfigGet);
   WifiWebServer->SetUriCb((const char *)"/insert_loco", LcHandleLoco2Card);
   WifiWebServer->SetUriCb((const char *)"/rem_loco", LcHandleRemCard);
   WifiWebServer->SetUriCb((const char *)"/save_loco", LcHandleSaveCard);
   WifiWebServer->Start();
#ifdef DEBUG_OUTPUT
   Serial.println("System ready");
#endif
#endif
}

const uint16_t clientIntervall = 30;             // intervall to send data to a server in seconds. Set to 30 if you want to send data each 30 seconds
unsigned long ss = 0;                            // current second since startup
uint32_t clientPreviousSs = 0 - clientIntervall; // last second when data was sent to server

void loop(void)
{
#ifdef TEST_BASIC
   test_basic_loop();
#else
   ss = millis() / 1000;
   if (clientIntervall > 0 && (ss - clientPreviousSs) >= clientIntervall)
   {
      clientPreviousSs = ss;
   }
   WifiWebServer->HandleClient();
#endif
}

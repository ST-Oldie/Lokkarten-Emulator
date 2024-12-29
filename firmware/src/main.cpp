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


// Build a HTML page with a form which shows textboxes to enter the values
// returns the HTML code of the page
String EncodeFormHTMLFromConfigValues(String TitleOfForm, int CountOfConfigValues)
{  String ConfigValue, TableRowHTML, StyleHTML;

   // Head of the HTML page
   String HTMLPage = "<!DOCTYPE html><html><body><h2>" + TitleOfForm + "</h2><form><table>";
   // configuration values
   StyleHTML = " Style =\"background-color: #FFE4B5;\" " ;   // yellow
   if (Config.GetCfgVal(CFG_VALUE_SSID) != (char *)NULL)
      ConfigValue = Config.GetCfgVal(CFG_VALUE_SSID);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>" + ConfigValue + "</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\" " + StyleHTML + " /></th></tr>";
   HTMLPage += TableRowHTML;
   if (Config.GetCfgVal(CFG_VALUE_PASSWORD) != (char *)NULL)
      ConfigValue = Config.GetCfgVal(CFG_VALUE_PASSWORD);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>" + ConfigValue + "</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\" " + StyleHTML + " /></th></tr>";
   HTMLPage += TableRowHTML;
   // add the submit button
   HTMLPage += "</table><br/><input type=\"submit\" value=\"Submit\" />";
   // footer of the webpage
   HTMLPage += "</form></body></html>";
   return HTMLPage;
}

// Decodes a GET parameter (expression after ? in URI (URI = expression entered in address field of webbrowser)), like "Country=Germany&City=Aachen"
// and set the ConfigValues
int DecodeGETParameterAndSetConfigValues(String GETParameter)
{  int posFirstCharToSearch, count;

   posFirstCharToSearch = 1;
   count = 0;
   // while a "&" is in the expression, after a start position to search
   while (GETParameter.indexOf('&', posFirstCharToSearch) > -1)
   {
      int posOfSeparatorChar = GETParameter.indexOf('&', posFirstCharToSearch);  // position of & after start position
      int posOfValueChar = GETParameter.indexOf('=', posFirstCharToSearch);      // position of = after start position
      switch (count)
      {
         case 0:
            Config.SetCfgVal(CFG_VALUE_SSID, GETParameter.substring(posOfValueChar + 1, posOfSeparatorChar));
            break;
         case 1:
            Config.SetCfgVal(CFG_VALUE_PASSWORD, GETParameter.substring(posOfValueChar + 1, posOfSeparatorChar));
            break;
      }
      posFirstCharToSearch = posOfSeparatorChar + 1;  // shift the start position to search after the &-char 
      count++;
   }
   // no more & chars found
   int posOfValueChar = GETParameter.indexOf('=', posFirstCharToSearch);       // search for =
   switch (count)
   {
      case 0:
         Config.SetCfgVal(CFG_VALUE_SSID, GETParameter.substring(posOfValueChar + 1, GETParameter.length()));
         break;
      case 1:
         Config.SetCfgVal(CFG_VALUE_PASSWORD, GETParameter.substring(posOfValueChar + 1, GETParameter.length()));
         break;
   }
   count++;
   return count;
}

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
         DecodeGETParameterAndSetConfigValues(GETParameter);
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
         HTMLPageWithConfigForm = EncodeFormHTMLFromConfigValues("ESP32 Webserver CONFIG", 3) + "<br>IP Address: " + WifiClientServer.GetOwnIPAddressInRouterNetwork();       // build a new Configuration webpage with form and new ConfigValues entered in textboxes
      }
      else                                                         // the user entered the ESP32 address in router network in the browser, to get normal webpage
      {
         HTMLPageWithConfigForm = EncodeFormHTMLFromConfigValues("ESP32 Webserver Demo", 1);                                       // build a new webpage to control the LED
      }

      WifiWebServer.SendHTMLPage(HTMLPageWithConfigForm);    // send out the webpage to client = webbrowser and close client connection
   }
   delay(50);
#endif
}

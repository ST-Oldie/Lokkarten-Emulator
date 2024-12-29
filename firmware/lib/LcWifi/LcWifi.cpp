#include <ESP8266WiFi.h>
#include "LcWifi.h"

/**
* @addtogroup LxWifi
*
* @{
*/

boolean LcWifi::Connect(char *SSID, char *Password)
{  int WiFiConnectTimeOut;

   WiFi.begin(SSID, Password);
   /* we wait until connection is established or 10 seconds are gone */
   WiFiConnectTimeOut = 0;
   while ((WiFi.status() != WL_CONNECTED) && (WiFiConnectTimeOut < 10))
   {
      delay(1000);
       WiFiConnectTimeOut++;
   }
   return(WiFi.status() == WL_CONNECTED);
}

boolean LcWifi::Disconnect(void)
{  int WiFiConnectTimeOut;

   WiFi.disconnect();
   WiFiConnectTimeOut = 0;
   while ((WiFi.status() == WL_CONNECTED) && (WiFiConnectTimeOut < 10))
   {
      delay(1000);
      WiFiConnectTimeOut++;
   }
   return(WiFi.status() != WL_CONNECTED);
}

void LcWifi::AccessPointStart(char *AccessPointNetworkSSID)
{ 
   WiFi.softAP(AccessPointNetworkSSID);
}

void LcWifi::SetBothModesNetworkStationAndAccessPoint(void)
{
   WiFi.mode(WIFI_AP_STA);
}

String LcWifi::GetOwnIPAddressInRouterNetwork(void)
{
   return WiFi.localIP().toString();
}

/** @} */

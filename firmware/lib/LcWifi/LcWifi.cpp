#include <ESP8266WiFi.h>
#include <Cfg.h>
#include "LcWifi.h"

/**
* @addtogroup LxWifi
*
* @{
*/

static IPAddress LocalIp(192, 168, 4, 1);
static IPAddress GatewayIp(192, 168, 4, 10);
static IPAddress SubnetMask(255, 255, 255, 0);
static IPAddress PrimaryDnsIp(8, 8, 8, 8);

void LcWifi::Start(void)
{
   SetWifiMode(LC_WIFI_CLIENT);
   if ((Config->GetCfgVal(CFG_VALUE_SSID) == (char *)NULL) ||
       (Config->GetCfgVal(CFG_VALUE_PASSWORD) == (char *)NULL) ||
       !Connect(Config->GetCfgVal(CFG_VALUE_SSID), Config->GetCfgVal(CFG_VALUE_PASSWORD)))
   {
      SetWifiMode(LC_WIFI_ACCESS_POINT);
      AccessPointStart((char *)"Lokkartenemulator");
   }
}

boolean LcWifi::Connect(char *SSID, char *Password)
{  int WiFiConnectTimeOut;
   IPAddress CfgLocalIp, CfgGatewayIp, CfgSubnetMask, CfgPrimaryDnsIp;

   CfgLocalIp.fromString(Config->GetCfgVal(CFG_VALUE_LOCAL_IP));
   CfgGatewayIp.fromString(Config->GetCfgVal(CFG_VALUE_GATEWAY_IP));
   CfgSubnetMask.fromString(Config->GetCfgVal(CFG_VALUE_SUBNET_MASK));
   CfgPrimaryDnsIp.fromString(Config->GetCfgVal(CFG_VALUE_DNS_IP));
   WiFi.config(CfgLocalIp, CfgGatewayIp, CfgSubnetMask, CfgPrimaryDnsIp);
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
   WiFi.config(LocalIp, GatewayIp, SubnetMask, PrimaryDnsIp);
   WiFi.softAP(AccessPointNetworkSSID);
}

void LcWifi::SetBothModesNetworkStationAndAccessPoint(void)
{
   WiFi.mode(WIFI_AP_STA);
}

void LcWifi::SetWifiMode(int Mode)
{
   switch (Mode)
   {
      case LC_WIFI_ACCESS_POINT:
         WiFi.mode(WIFI_AP);
         break;
      case LC_WIFI_CLIENT:
         WiFi.mode(WIFI_STA);
         break;
      case LC_WIFI_BOTH:
         WiFi.mode(WIFI_AP_STA);
         break;
   }
}

String LcWifi::GetOwnIPAddressInRouterNetwork(void)
{
   return WiFi.localIP().toString();
}

/** @} */

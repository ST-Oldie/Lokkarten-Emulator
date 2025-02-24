#ifndef LCWIFI_H
#define LCWIFI_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Cfg.h>

/**
 * @defgroup LcWifi class for connection to wifi
 *
 * @{
 */
/**

* @brief class for hold information of a wifi connction
*/
class LcWifi
{
   public:
      LcWifi(Cfg *ActualConfig) { Config = ActualConfig; };
      void Start(void);
   private:
      Cfg *Config;
      boolean Connect(char *SSID, char *Password);
      boolean Disconnect(void);
      String GetOwnIPAddressInRouterNetwork(void);
      void AccessPointStart(char *AccessPointNetworkSSID);
      void SetBothModesNetworkStationAndAccessPoint(void);
#define LC_WIFI_ACCESS_POINT 1
#define LC_WIFI_CLIENT       2
#define LC_WIFI_BOTH         3
      void SetWifiMode(int Mode);
};

/** @} */

#endif

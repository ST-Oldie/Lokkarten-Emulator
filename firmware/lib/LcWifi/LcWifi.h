#ifndef LCWIFI_H
#define LCWIFI_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

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
      boolean Connect(char *SSID, char *Password);
      boolean Disconnect(void);
      String GetOwnIPAddressInRouterNetwork(void);
      void AccessPointStart(char *AccessPointNetworkSSID);
      void SetBothModesNetworkStationAndAccessPoint(void);
};

/** @} */

#endif

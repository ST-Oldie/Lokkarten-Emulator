#include <stdlib.h>
#include <string.h>
#include <IniFile.h>
#include "Cfg.h"

#define INI_FILE_NAME   "/lc.ini"
#define INI_FILE_LENGTH 80
#define CFG_SECTION_LOCOCARD "lococards"
#define CFG_SECTION_WLAN     "wlan"
#define DEV_CFG_VALUE_LOCO_PATH "/locos/"

void Cfg::ReadIniconfig(void)
{  IniFile LcIni(INI_FILE_NAME);
   char buffer[INI_FILE_LENGTH];

   if (LcIni.open())
   {
      if (LcIni.validate(buffer, INI_FILE_LENGTH))
      {
         if (LcIni.getValue(CFG_SECTION_LOCOCARD, CFG_VALUE_LOCO_PATH, buffer, sizeof(buffer)))
            CfgValues[CFG_VALUE_LOCO_PATH] = strdup(buffer);
         else
            CfgValues[CFG_VALUE_LOCO_PATH] = strdup(DEV_CFG_VALUE_LOCO_PATH);
         if (LcIni.getValue(CFG_SECTION_WLAN, CFG_VALUE_SSID, buffer, sizeof(buffer)))
            CfgValues[CFG_VALUE_SSID] = strdup(buffer);
         else
            CfgValues[CFG_VALUE_SSID] = (char *)NULL;
         if (LcIni.getValue(CFG_SECTION_WLAN, CFG_VALUE_PASSWORD, buffer, sizeof(buffer)))
            CfgValues[CFG_VALUE_PASSWORD] = strdup(buffer);
         else
            CfgValues[CFG_VALUE_PASSWORD] = (char *)NULL;
         if (LcIni.getValue(CFG_SECTION_WLAN, CFG_VALUE_LOCAL_IP, buffer, sizeof(buffer)))
            CfgValues[CFG_VALUE_LOCAL_IP] = strdup(buffer);
         else
            CfgValues[CFG_VALUE_LOCAL_IP] = (char *)NULL;
         if (LcIni.getValue(CFG_SECTION_WLAN, CFG_VALUE_GATEWAY_IP, buffer, sizeof(buffer)))
            CfgValues[CFG_VALUE_GATEWAY_IP] = strdup(buffer);
         else
            CfgValues[CFG_VALUE_GATEWAY_IP] = (char *)NULL;
         if (LcIni.getValue(CFG_SECTION_WLAN, CFG_VALUE_SUBNET_MASK, buffer, sizeof(buffer)))
            CfgValues[CFG_VALUE_SUBNET_MASK] = strdup(buffer);
         else
            CfgValues[CFG_VALUE_SUBNET_MASK] = (char *)NULL;
         if (LcIni.getValue(CFG_SECTION_WLAN, CFG_VALUE_DNS_IP, buffer, sizeof(buffer)))
            CfgValues[CFG_VALUE_DNS_IP] = strdup(buffer);
         else
            CfgValues[CFG_VALUE_DNS_IP] = (char *)NULL;
      }
      else
      {
         CfgValues[CFG_VALUE_LOCO_PATH] = strdup(DEV_CFG_VALUE_LOCO_PATH);
         CfgValues[CFG_VALUE_SSID] = (char *)NULL;
         CfgValues[CFG_VALUE_PASSWORD] = (char *)NULL;
         CfgValues[CFG_VALUE_LOCAL_IP] = (char *)NULL;
         CfgValues[CFG_VALUE_GATEWAY_IP] = (char *)NULL;
         CfgValues[CFG_VALUE_SUBNET_MASK] = (char *)NULL;
         CfgValues[CFG_VALUE_DNS_IP] = (char *)NULL;
      }
      LcIni.close();
   }
   else
   {
      CfgValues[CFG_VALUE_LOCO_PATH] = strdup(DEV_CFG_VALUE_LOCO_PATH);
      CfgValues[CFG_VALUE_SSID] = (char *)NULL;
      CfgValues[CFG_VALUE_PASSWORD] = (char *)NULL;
      CfgValues[CFG_VALUE_LOCAL_IP] = (char *)NULL;
      CfgValues[CFG_VALUE_GATEWAY_IP] = (char *)NULL;
      CfgValues[CFG_VALUE_SUBNET_MASK] = (char *)NULL;
      CfgValues[CFG_VALUE_DNS_IP] = (char *)NULL;
   }
}

void Cfg::WriteIniconfig(void)
{  fs::File CfgFile;

   CfgFile = SD.open(INI_FILE_NAME, FILE_WRITE);
   CfgFile.printf("[%s]\n", CFG_SECTION_LOCOCARD);
   CfgFile.printf("%s=%s\n", CFG_VALUE_LOCO_PATH, CfgValues[CFG_VALUE_LOCO_PATH]);
   CfgFile.printf("[%s]\n", CFG_SECTION_WLAN);
   if (CfgValues[CFG_VALUE_SSID] != (char *)NULL)
      CfgFile.printf("%s=%s\n", CFG_VALUE_SSID, CfgValues[CFG_VALUE_SSID]);
   if (CfgValues[CFG_VALUE_PASSWORD] != (char *)NULL)
      CfgFile.printf("%s=%s\n", CFG_VALUE_PASSWORD, CfgValues[CFG_VALUE_PASSWORD]);
   if (CfgValues[CFG_VALUE_LOCAL_IP] != (char *)NULL)
      CfgFile.printf("%s=%s\n", CFG_VALUE_LOCAL_IP, CfgValues[CFG_VALUE_LOCAL_IP]);
   if (CfgValues[CFG_VALUE_GATEWAY_IP] != (char *)NULL)
      CfgFile.printf("%s=%s\n", CFG_VALUE_GATEWAY_IP, CfgValues[CFG_VALUE_GATEWAY_IP]);
   if (CfgValues[CFG_VALUE_SUBNET_MASK] != (char *)NULL)
      CfgFile.printf("%s=%s\n", CFG_VALUE_SUBNET_MASK, CfgValues[CFG_VALUE_SUBNET_MASK]);
   if (CfgValues[CFG_VALUE_DNS_IP] != (char *)NULL)
      CfgFile.printf("%s=%s\n", CFG_VALUE_DNS_IP, CfgValues[CFG_VALUE_DNS_IP]);
   CfgFile.close();
}

char *Cfg::GetCfgVal(char *Key)
{
   return(CfgValues[Key]);
}

void Cfg::SetCfgVal(char *Key, char *Value)
{  char *OldVal;

   OldVal = CfgValues[Key];
   CfgValues.erase(Key);
   if (OldVal != (char *)NULL)
      free((void *)OldVal);
   CfgValues[Key] = strdup(Value);
}

void Cfg::SetCfgVal(char *Key, String Value)
{  char *OldVal;

   OldVal = CfgValues[Key];
   CfgValues.erase(Key);
   if (OldVal != (char *)NULL)
      free((void *)OldVal);
   CfgValues[Key] = strdup(Value.c_str());
}

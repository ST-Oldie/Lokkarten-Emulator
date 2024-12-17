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
      }
      else
      {
         CfgValues[CFG_VALUE_LOCO_PATH] = strdup(DEV_CFG_VALUE_LOCO_PATH);
      }
      LcIni.close();
   }
   else
   {
      CfgValues[CFG_VALUE_LOCO_PATH] = strdup(DEV_CFG_VALUE_LOCO_PATH);
   }
}

void Cfg::WriteIniconfig(void)
{  fs::File CfgFile;

   CfgFile = SD.open(INI_FILE_NAME, FILE_WRITE);
   CfgFile.printf("[%s]\n", CFG_SECTION_LOCOCARD);
   CfgFile.printf("%s=%s\n", CFG_VALUE_LOCO_PATH, CfgValues[CFG_VALUE_LOCO_PATH]);
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
   free((void *)OldVal);
   CfgValues[Key] = strdup(Value);
}

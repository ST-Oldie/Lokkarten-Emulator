#include <IniFile.h>
#include "Cfg.h"

#define INI_FILE_NAME   "/lc.ini"
#define INI_FILE_LENGTH 80
#define FS_PATH         "/locos/"

extern "C" {

//char CfgFsPath[MAX_FS_PATH_LEN];

void CfgReadIniconfig(void)
{  IniFile LcIni(INI_FILE_NAME);
   char buffer[INI_FILE_LENGTH];

   /* preset cfg varables */
   strcpy(CfgFsPath, FS_PATH);
   if (LcIni.open())
   {
      if (LcIni.validate(buffer, INI_FILE_LENGTH))
      {
         if (LcIni.getValue("lococards", "path", buffer, sizeof(buffer)))
            strcpy(CfgFsPath, buffer);
      }
      LcIni.close();
   }
}

}
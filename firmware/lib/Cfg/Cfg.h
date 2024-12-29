#ifndef CFG
#define CFG

#include <map>

#define MAX_FS_PATH_LEN 255
#define CFG_VALUE_LOCO_PATH (char *)"path"
#define CFG_VALUE_SSID      (char *)"ssid"
#define CFG_VALUE_PASSWORD  (char *)"password"

class Cfg
{
   public:
      void ReadIniconfig(void);
      void WriteIniconfig(void);
      char *GetCfgVal(char *Key);
      void SetCfgVal(char *Key, char *Value);
      void SetCfgVal(char *Key, String Value);
   private:
      std::map<char *, char *> CfgValues;
};

#endif

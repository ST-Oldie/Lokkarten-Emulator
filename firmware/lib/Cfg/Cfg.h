#ifndef CFG
#define CFG

#include <map>

#define MAX_FS_PATH_LEN 255
#define CFG_VALUE_LOCO_PATH "path"

class Cfg
{
   public:
      void ReadIniconfig(void);
      void WriteIniconfig(void);
      char *GetCfgVal(char *Key);
      void SetCfgVal(char *Key, char *Value);
   private:
      std::map<char *, char *> CfgValues;
};

#endif

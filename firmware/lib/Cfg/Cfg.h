#ifndef CFG
#define CFG

#define MAX_FS_PATH_LEN 255

char CfgFsPath[MAX_FS_PATH_LEN];

extern "C" {

void CfgReadIniConfig(void);

}

#endif

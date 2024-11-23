#ifndef CFG
#define CFG

#define MAX_FS_PATH_LEN 255

extern char CfgFsPath[MAX_FS_PATH_LEN];

void CfgReadIniConfig(void);

#endif

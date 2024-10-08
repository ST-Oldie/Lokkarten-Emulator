#ifndef LOCO_SET_H
#define LOCO_SET_H

#include <set>
#include <FS.h>

class LocoSet
{
   public:
      void EmptySet(void);
      boolean ReadSet(fs::File LocoSetFile);
      boolean WriteSet(fs::File LocoSetFile);
      void AddLocoFileName(const char *LocoFileName);
      char *begin(void);
      char *next(void);
   private:
      std::set<char *> LocoFileNames;
      std::set<char *>::iterator LocoFileNamesItr;
};

#endif
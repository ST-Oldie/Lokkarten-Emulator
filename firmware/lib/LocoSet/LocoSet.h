#ifndef LOCO_SET_H
#define LOCO_SET_H

#include <set>
#include <FS.h>

/**
 * @defgroup LOCO_SET class for a set of locos
 *
 * @{
 */

/**
* @brief class for a set of locos
*/
class LocoSet
{
   public:
      void EmptySet(void);                            /** remove all entries from the set */
      boolean ReadSet(fs::File LocoSetFile);          /** read set of locos from file */
      boolean WriteSet(fs::File LocoSetFile);         /** write set of locos to file */
      void AddLocoFileName(const char *LocoFileName); /** add a loco to a set of locos */
      char *begin(void);                              /** get first entry of set of locos */
      char *next(void);                               /** get next entry of set of locos */
   private:
      std::set<char *> LocoFileNames;                 /** data container for locos */
      std::set<char *>::iterator LocoFileNamesItr;    /** iterator for all locos in set */
};

/** @} */

#endif
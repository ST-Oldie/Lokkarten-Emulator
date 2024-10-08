#include <string.h>
#include <LocoSet.h>

/**
* @addtogroup LOCO_SET
*
* @{
*/

void LocoSet::EmptySet(void)
{
   for (LocoFileNamesItr = LocoFileNames.begin(); LocoFileNamesItr != LocoFileNames.end(); ++LocoFileNamesItr)
   {
      free(*LocoFileNamesItr);
   }
   LocoFileNames.clear();
}

boolean LocoSet::ReadSet(fs::File LocoSetFile)
{  char OneLine[15];
   int LineLength;

   while (LocoSetFile.available())
   {
      LineLength = LocoSetFile.readBytesUntil('\n', OneLine, sizeof(OneLine) - 1);
      if (LineLength > 0)
      {
         if (OneLine[LineLength - 1] == '\r')
         {
            LineLength--; // to remove \r if we have DOS lineends
         }
         OneLine[LineLength] = '\0';
         LocoFileNames.insert(strdup(OneLine));
      }
   }
   return(true);
}

boolean LocoSet::WriteSet(fs::File LocoSetFile)
{
   for (LocoFileNamesItr = LocoFileNames.begin(); LocoFileNamesItr != LocoFileNames.end(); ++LocoFileNamesItr)
   {
      LocoSetFile.println(*LocoFileNamesItr);
   }
   return(true);
}

void LocoSet::AddLocoFileName(const char *LocoFileName)
{
   LocoFileNames.insert(strdup(LocoFileName));
}

char *LocoSet::begin(void)
{
   LocoFileNamesItr = LocoFileNames.begin();
   return(*LocoFileNamesItr);
}

char *LocoSet::next(void)
{
   if (LocoFileNamesItr != LocoFileNames.end())
   {
      LocoFileNamesItr++;
      return(*LocoFileNamesItr);
   }
   else
   {
      return((char *)NULL);
   }
}

/** @} */

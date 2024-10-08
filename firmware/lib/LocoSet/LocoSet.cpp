#include <string.h>
#include <LocoSet.h>

void LocoSet::EmptySet(void)
{  std::set<char *>::iterator LocoSetIterator;

   for (LocoSetIterator = LocoFileNames.begin(); LocoSetIterator != LocoFileNames.end(); ++LocoSetIterator)
   {
      free(*LocoSetIterator);
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
{  std::set<char *>::iterator LocoSetIterator;

   for (LocoSetIterator = LocoFileNames.begin(); LocoSetIterator != LocoFileNames.end(); ++LocoSetIterator)
   {
      LocoSetFile.println(*LocoSetIterator);
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
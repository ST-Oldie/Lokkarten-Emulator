#include <cs2_write.h>
#include <cs2_file.h>
#include "loco.h"
#include "loco.h"

void Loco::Serialize(void)
{
}

void Loco::Deserialize(void)
{
}

void Loco::Write2Cs2(FILE *LokCs2Stream)
{  unsigned int i;

   Cs2WriteTitleByName(LokCs2Stream, CS2_PARAGRAPH_STRING_LOKOMOTIVE, 0);
   Cs2WriteStringValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_NAME, GetName(), 1);
   Cs2WriteULongValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_UID, GetUid(), 1);
   Cs2WriteHexValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_ADRESSE, GetAdresse(), 1);
   Cs2WriteStringValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_TYP, GetTyp(), 1);
   Cs2WriteHexValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_SID, 1, 1);
   Cs2WriteULongValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_MFXUID, GetMfxUid(), 1);
   Cs2WriteStringValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_ICON, GetName(), 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_SYMBOL, GetSymbol(), 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_AV, GetAv(), 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_BV, GetBv(), 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_VOLUME, GetVolume(), 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_VELOCITY, GetVelocity(), 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_RICHTUNG, GetDirection(), 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_TACHOMAX, 320, 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_VMAX, GetVmax(), 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_VMIN, GetVmin(), 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_XPROTOKOLL, 0, 1);
   Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_MFXTYP, 0, 1);
   Cs2WriteHexValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_STAND, 0, 1);
   Cs2WriteHexValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_FAHRT, 0, 1);
   for (i = 0; i < GetNumFkts(); i++)
   {
      Cs2WriteTitleByName(LokCs2Stream, CS2_FILE_VALUE_STRING_FUNKTIONEN, 1);
      Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_NR, i, 2);
      if (GetFktTyp(i) != 0)
         Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_TYP, GetFktTyp(i), 2);
      if (GetFktDauer(i) != 0)
         Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_DAUER, GetFktDauer(i), 2);
      if (GetFktWert(i) != 0)
         Cs2WriteIntValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_WERT, GetFktWert(i), 2);
      if ((GetFktTyp(i) != 0) &&
          (GetFktDauer(i) != 0) &&
          (GetFktWert(i) != 0))
      {
         Cs2WriteHexValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_VORWAERTS, 0, 2);
         Cs2WriteHexValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_RUECKWAERTS, 0, 2);
      }
   }
   Cs2WriteHexLongValueByName(LokCs2Stream, CS2_FILE_VALUE_STRING_INTRAKTION, 0xffffffff, 1);
}

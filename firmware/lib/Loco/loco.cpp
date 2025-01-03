#include <HardwareSerial.h>
#include <cs2_write.h>
#include <cs2_file.h>
#include "loco.h"
#include "loco.h"

/**
* @addtogroup LOCO
*
* @{
*/

Loco::Loco()
{
   SetEmpty();
}

boolean Loco::IsEmpty(void)
{
   return(LocoIsEmpty);
}

void Loco::SetEmpty(void)
{
   memset(BinData, 0xff, I2C_DEVICESIZE_24LC64);
   LocoIsEmpty = true;
}

void Loco::Serialize(void)
{
}

void Loco::Deserialize(void)
{
}

boolean Loco::ReadBin(fs::File LocoFile)
{  size_t BinSize;
   boolean Ret;

   BinSize = LocoFile.size();
   if (BinSize != I2C_DEVICESIZE_24LC64)
   {
      Ret = false;
   }
   else
   {
      Ret = LocoFile.read(BinData, BinSize) == (int)BinSize;
      if (!Ret)
      {
         SetEmpty();
      }
      else
      {
         LocoIsEmpty = false;
      }
   }
   return(Ret);
}

boolean Loco::WriteBin(fs::File LocoFile)
{  size_t Written;

   Written = LocoFile.write(BinData, I2C_DEVICESIZE_24LC64);
   return(Written == I2C_DEVICESIZE_24LC64);
}

void Loco::Write2Cs2(fs::File LocoFile)
{  unsigned int i;

   Cs2WriteTitleByName(LocoFile, CS2_PARAGRAPH_STRING_LOKOMOTIVE, 0);
   Cs2WriteStringValueByName(LocoFile, CS2_FILE_VALUE_STRING_NAME, GetName(), 1);
   Cs2WriteULongValueByName(LocoFile, CS2_FILE_VALUE_STRING_UID, GetUid(), 1);
   Cs2WriteHexValueByName(LocoFile, CS2_FILE_VALUE_STRING_ADRESSE, GetAdresse(), 1);
   Cs2WriteStringValueByName(LocoFile, CS2_FILE_VALUE_STRING_TYP, GetTyp(), 1);
   Cs2WriteHexValueByName(LocoFile, CS2_FILE_VALUE_STRING_SID, 1, 1);
   Cs2WriteULongValueByName(LocoFile, CS2_FILE_VALUE_STRING_MFXUID, GetMfxUid(), 1);
   Cs2WriteStringValueByName(LocoFile, CS2_FILE_VALUE_STRING_ICON, GetName(), 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_SYMBOL, GetSymbol(), 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_AV, GetAv(), 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_BV, GetBv(), 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_VOLUME, GetVolume(), 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_VELOCITY, GetVelocity(), 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_RICHTUNG, GetDirection(), 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_TACHOMAX, 320, 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_VMAX, GetVmax(), 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_VMIN, GetVmin(), 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_XPROTOKOLL, 0, 1);
   Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_MFXTYP, 0, 1);
   Cs2WriteHexValueByName(LocoFile, CS2_FILE_VALUE_STRING_STAND, 0, 1);
   Cs2WriteHexValueByName(LocoFile, CS2_FILE_VALUE_STRING_FAHRT, 0, 1);
   for (i = 0; i < GetNumFkts(); i++)
   {
      Cs2WriteTitleByName(LocoFile, CS2_FILE_VALUE_STRING_FUNKTIONEN, 1);
      Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_NR, i, 2);
      if (GetFktTyp(i) != 0)
         Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_TYP, GetFktTyp(i), 2);
      if (GetFktDauer(i) != 0)
         Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_DAUER, GetFktDauer(i), 2);
      if (GetFktWert(i) != 0)
         Cs2WriteIntValueByName(LocoFile, CS2_FILE_VALUE_STRING_WERT, GetFktWert(i), 2);
      if ((GetFktTyp(i) != 0) &&
          (GetFktDauer(i) != 0) &&
          (GetFktWert(i) != 0))
      {
         Cs2WriteHexValueByName(LocoFile, CS2_FILE_VALUE_STRING_VORWAERTS, 0, 2);
         Cs2WriteHexValueByName(LocoFile, CS2_FILE_VALUE_STRING_RUECKWAERTS, 0, 2);
      }
   }
   Cs2WriteHexLongValueByName(LocoFile, CS2_FILE_VALUE_STRING_INTRAKTION, 0xffffffff, 1);
}

/** @} */

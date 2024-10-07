#include <stdlib.h>
#include <string.h>
#include <FS.h>
#include "cs2_write.h"


/** @file */

/**
 * @defgroup CS2_WRITE Cs2 Write Group
 *
 * @{
 */

static const char *ParagraphNames[] = {
   "",
   CS2_PARAGRAPH_STRING_LOK,
   CS2_PARAGRAPH_STRING_NUMLOKS,
   CS2_PARAGRAPH_STRING_LOKOMOTIVE,
   CS2_PARAGRAPH_STRING_GLEISBILD,
   CS2_PARAGRAPH_STRING_GLEISBILDSEITE,
   CS2_PARAGRAPH_STRING_MAGNETARTIKEL,
   CS2_PARAGRAPH_STRING_FAHRSTRASSEN
};

/**
* @brief Scheiben eines Paragraphen
*
* Diese Funktion schreibt die &Uuml;berschrift eines Absatz (Paragraph).
*
* @param[in] LocoFile Fileobject zum Scheiben
* @param[in] Paragraph Titel des zu schriebenden Paragraphs als Text.
*/
void Cs2WriteParagraphByName(fs::File LocoFile, char *Paragraph)
{
   LocoFile.printf("[%s]\n", Paragraph);
}

/**
* @brief Scheiben eines Paragraphen
*
* Diese Funktion schreibt die &Uuml;berschrift eines Absatz (Paragraph).
*
* @param[in] LocoFile Fileobject zum Scheiben
* @param[in] Cs2ParagraphType Titel des zu schriebenden Paragraphs als
* Datentyp aus der cs2parse.h
*/
void Cs2WriteParagraphByType(fs::File LocoFile, int Cs2ParagraphType)
{
   LocoFile.printf("[%s]\n", ParagraphNames[Cs2ParagraphType]);
}

/**
* @brief Schreiben eines Titels
*
* Diese Funktion schreibt einen Titel (Variable ohne Wert).
*
* @param[in] LocoFile Fileobject zum Scheiben
* @param[in] Title Name des zu schreibenden Titels (Variable ohne Wert)
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteTitleByName(fs::File LocoFile, const char *Title, int Level)
{  int i;

   if (Level > 0)
      LocoFile.print(' ');
   for (i = 0; i < Level; i++)
      LocoFile.print('.');
   LocoFile.printf("%s\n", Title);
}

/**
* @brief Schreiben einer Zeichenkette
*
* Diese Funktion schreibt eine Variable als Text.
*
* @param[in] LocoFile Fileobject zum Scheiben
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteStringValueByName(fs::File LocoFile, const char *Title, char *Value, int Level)
{  int i;

   if (Level > 0)
      LocoFile.print(' ');
   for (i = 0; i < Level; i++)
      LocoFile.print('.');
   LocoFile.printf("%s=%s\n", Title, Value);
}

/**
* @brief Schreiben einer 16 Bit Zahl
*
* Diese Funktion schreibt eine Variable als Zahl.
*
* @param[in] LocoFile Fileobject zum Scheiben
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteIntValueByName(fs::File LocoFile, const char *Title, int Value, int Level)
{  int i;

   if (Level > 0)
      LocoFile.print(' ');
   for (i = 0; i < Level; i++)
      LocoFile.print('.');
   LocoFile.printf("%s=%d\n", Title, Value);
}

/**
* @brief Schreiben einer 16 Bit Zahl als Hexadezimalwert
*
* Diese Funktion schreibt eine Variable als Hexwert.
*
* @param[in] LocoFile Fileobject zum Scheiben
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteHexValueByName(fs::File LocoFile, const char *Title, int Value, int Level)
{  int i;

   if (Level > 0)
      LocoFile.print(' ');
   for (i = 0; i < Level; i++)
      LocoFile.print('.');
   LocoFile.printf("%s=0x%x\n", Title, Value);
}

/**
* @brief Schreiben einer 32 Bit Zahl
*
* Diese Funktion schreibt eine Variable als vorzeichenlose lange Zahl.
*
* @param[in] LocoFile Fileobject zum Scheiben
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteULongValueByName(fs::File LocoFile, const char *Title, unsigned long Value, int Level)
{  int i;

   if (Level > 0)
      LocoFile.print(' ');
   for (i = 0; i < Level; i++)
      LocoFile.print('.');
   LocoFile.printf("%s=0x%lx\n", Title, Value);
}

/**
* @brief Schreiben einer 32 Bit Zahl als Hexadezimalwert
*
* Diese Funktion schreibt eine Variable als vorzeichenlosen langen Hexwert.
*
* @param[in] LocoFile Fileobject zum Scheiben
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteHexLongValueByName(fs::File LocoFile, const char *Title, unsigned long Value, int Level)
{  int i;

   if (Level > 0)
      LocoFile.print(' ');
   for (i = 0; i < Level; i++)
      LocoFile.print('.');
   LocoFile.printf("%s=0x%lx\n", Title, Value);
}

/**
* @brief Schreiben einer Gleitkommazahl
*
* Diese Funktion schreibt eine Variable als Gleitkommazahl.
*
* @param[in] LocoFile Fileobject zum Scheiben
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteFloatValueByName(fs::File LocoFile, const char *Title, float Value, int Level)
{  int i;

   if (Level > 0)
      LocoFile.print(' ');
   for (i = 0; i < Level; i++)
      LocoFile.print('.');
   LocoFile.printf("%s=%1.3f\n", Title, (double)Value);
}

/** @} */

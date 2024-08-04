#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cs2_write.h"


/** @file */

/**
 * @defgroup CS2_WRITE Cs2 Write Group
 *
 * @{
 */

//static char *FileNames[] = {
//   "",
//   CS2_FILE_STRING_LOKOMOTIVE
//};

static char *ParagraphNames[] = {
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
* @brief &Ouml;ffnen einer *.cs2 Datei zum Schreiben
*
* Diese Funktion &ouml;ffnet eine *.cs2 Datei anhand des Namens.
*
* @param[in] Name Der Name der zu &ouml;ffnenden Datei. Es wird automatisch
*            der Webroot von apache2 mit dem Pfad f&uuml;r die CS Konfigdateien
*            vorangestellt (/var/www/config)
*
* @return Zeiger auf die Filestruktur, NULL im Fehlerfall.
*/
FILE *Cs2OpenByName(char *Name)
{
   return(fopen(Name, "w"));
}

/**
* @brief Schlie&szlig;en der Datei
*
* Diese Funktion schlie&szlig;t die Konfigdatei und ruft nur fclose() auf.
*
* @param[in] Stream Zeiger auf die Filestruktur
*/
void Cs2Close(FILE *Stream)
{
   fclose(Stream);
}

/**
* @brief Scheiben eines Paragraphen
*
* Diese Funktion schreibt die &Uuml;berschrift eines Absatz (Paragraph).
*
* @param[in] Stream Zeiger auf die Filestruktur
* @param[in] Paragraph Titel des zu schriebenden Paragraphs als Text.
*/
void Cs2WriteParagraphByName(FILE *Stream, char *Paragraph)
{
   fprintf(Stream, "[%s]\n", Paragraph);
}

/**
* @brief Scheiben eines Paragraphen
*
* Diese Funktion schreibt die &Uuml;berschrift eines Absatz (Paragraph).
*
* @param[in] Stream Zeiger auf die Filestruktur
* @param[in] Cs2ParagraphType Titel des zu schriebenden Paragraphs als
* Datentyp aus der cs2parse.h
*/
void Cs2WriteParagraphByType(FILE *Stream, int Cs2ParagraphType)
{
   fprintf(Stream, "[%s]\n", ParagraphNames[Cs2ParagraphType]);
}

/**
* @brief Schreiben eines Titels
*
* Diese Funktion schreibt einen Titel (Variable ohne Wert).
*
* @param[in] Stream Zeiger auf die Filestruktur
* @param[in] Title Name des zu schreibenden Titels (Variable ohne Wert)
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteTitleByName(FILE *Stream, const char *Title, int Level)
{  int i;

   if (Level > 0)
      fputc(' ', Stream);
   for (i = 0; i < Level; i++)
      fputc('.', Stream);
   fprintf(Stream, "%s\n", Title);
}

/**
* @brief Schreiben einer Zeichenkette
*
* Diese Funktion schreibt eine Variable als Text.
*
* @param[in] Stream Zeiger auf die Filestruktur
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteStringValueByName(FILE *Stream, const char *Title, char *Value, int Level)
{  int i;

   if (Level > 0)
      fputc(' ', Stream);
   for (i = 0; i < Level; i++)
      fputc('.', Stream);
   fprintf(Stream, "%s=%s\n", Title, Value);
}

/**
* @brief Schreiben einer 16 Bit Zahl
*
* Diese Funktion schreibt eine Variable als Zahl.
*
* @param[in] Stream Zeiger auf die Filestruktur
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteIntValueByName(FILE *Stream, const char *Title, int Value, int Level)
{  int i;

   if (Level > 0)
      fputc(' ', Stream);
   for (i = 0; i < Level; i++)
      fputc('.', Stream);
   fprintf(Stream, "%s=%d\n", Title, Value);
}

/**
* @brief Schreiben einer 16 Bit Zahl als Hexadezimalwert
*
* Diese Funktion schreibt eine Variable als Hexwert.
*
* @param[in] Stream Zeiger auf die Filestruktur
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteHexValueByName(FILE *Stream, const char *Title, int Value, int Level)
{  int i;

   if (Level > 0)
      fputc(' ', Stream);
   for (i = 0; i < Level; i++)
      fputc('.', Stream);
   fprintf(Stream, "%s=0x%x\n", Title, Value);
}

/**
* @brief Schreiben einer 32 Bit Zahl
*
* Diese Funktion schreibt eine Variable als vorzeichenlose lange Zahl.
*
* @param[in] Stream Zeiger auf die Filestruktur
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteULongValueByName(FILE *Stream, const char *Title, unsigned long Value, int Level)
{  int i;

   if (Level > 0)
      fputc(' ', Stream);
   for (i = 0; i < Level; i++)
      fputc('.', Stream);
   fprintf(Stream, "%s=0x%lx\n", Title, Value);
}

/**
* @brief Schreiben einer 32 Bit Zahl als Hexadezimalwert
*
* Diese Funktion schreibt eine Variable als vorzeichenlosen langen Hexwert.
*
* @param[in] Stream Zeiger auf die Filestruktur
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteHexLongValueByName(FILE *Stream, const char *Title, unsigned long Value, int Level)
{  int i;

   if (Level > 0)
      fputc(' ', Stream);
   for (i = 0; i < Level; i++)
      fputc('.', Stream);
   fprintf(Stream, "%s=0x%lx\n", Title, Value);
}

/**
* @brief Schreiben einer Gleitkommazahl
*
* Diese Funktion schreibt eine Variable als Gleitkommazahl.
*
* @param[in] Stream Zeiger auf die Filestruktur
* @param[in] Title Name der zu schreibenden Variable
* @param[in] Value Wert der Variable
* @param[in] Level Ebene im Baum (Anzahl Punkte)
*/
void Cs2WriteFloatValueByName(FILE *Stream, const char *Title, float Value, int Level)
{  int i;

   if (Level > 0)
      fputc(' ', Stream);
   for (i = 0; i < Level; i++)
      fputc('.', Stream);
   fprintf(Stream, "%s=%1.3f\n", Title, (double)Value);
}

/** @} */

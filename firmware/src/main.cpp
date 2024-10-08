#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <LocoSet.h>
#include <LocoCard.h>
#include <loco.h>
#include "BR_xx.h"

/**
* @mainpage Lokkartenemulator
*
* Firmware f&uuml;r die Hardware des Lokkarten-Emulators
*
* @author Michael Bernstein
*/

#define SPI_MISO    12
#define SPI_MOSI    13
#define SPI_CLK     14
#define SPI_CS      15

#define LOCO_SIZE   272
#define FS_PATH     "/LocoCards"

uint8_t loco_id = 10;
int sd_card;
File root;
LocoSet LokSatz;
LocoCard VirtLokKarte;
Loco Lokomotive;
int UserCmd;

/* Test with simple BIN File of BR86 */
void copy_loco_data()
{  uint16_t i;

   for (i = 0; i < LOCO_SIZE; i++)
   {
      Lokomotive.GetBinData()[i] = pgm_read_byte_far(&BR86_bin[i]);
   }
}

void printDirectory(File dir, int numTabs)
{
   while (true)
   {
      File entry =  dir.openNextFile();
      if (! entry)
      {
         // no more files
         break;
      }
      for (uint8_t i = 0; i < numTabs; i++) {
         Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
   }
}

void read_sd_card(void)
{
   Serial.print("Initialising SD Card ... ");
   if (!SD.begin(SPI_CS))
   {
      Serial.println("initialization failed - no SD Card inserted ?");
      sd_card = 0;
   }
   else
   {
      Serial.println("success :-)");
      sd_card = 1;
   }
   if (sd_card)
   {
      root = SD.open(FS_PATH);
      if (root)
      {
         printDirectory(root, 0);
      }
      else
      {
         Serial.println("no directorty /LocoCards !");
      }
   }
}

void empty_card(void)
{
   Lokomotive.SetEmpty();
}

void insert_card(void)
{
   if (!VirtLokKarte.LoadCard(Lokomotive.GetBinData()))
      Serial.println("load loco to fram failed");
   else
      VirtLokKarte.SetConnection(Connected2Ms2);
}

void remove_card(void)
{
   VirtLokKarte.SetConnection(Disconnected);
}

void read_loco(void)
{  String LokFileName;
   fs::File LocoFile;

   Serial.print("Dateiname: ");
   LokFileName = Serial.readString();
   LocoFile = SD.open(LokFileName, FILE_READ);
   Lokomotive.ReadBin(LocoFile);
   LocoFile.close();
}

void write_loco(void)
{  String LokFileName;
   fs::File LocoFile;

   Serial.print("Dateiname: ");
   LokFileName = Serial.readString();
   LocoFile = SD.open(LokFileName, FILE_WRITE);
   Lokomotive.WriteBin(LocoFile);
   LocoFile.close();
}

void add_loco_to_set(void)
{  String LokFileName;

   Serial.print("Dateiname: ");
   LokFileName = Serial.readString();
   LokSatz.AddLocoFileName(LokFileName.c_str());
}

void insert_loco_set(void)
{  char *LocoFileName;
   fs::File LocoFile;

   LocoFileName = LokSatz.begin();
   while (LocoFileName != (char *)NULL)
   {
      LocoFile = SD.open(LocoFileName, FILE_READ);
      Lokomotive.ReadBin(LocoFile);
      LocoFile.close();
      VirtLokKarte.SetConnection(Connected2Cpu);
      VirtLokKarte.LoadCard(Lokomotive.GetBinData());
      VirtLokKarte.SetConnection(Connected2Ms2);
      delay(500);
      LocoFileName = LokSatz.next();
   }
}

void print_menu(void)
{
   Serial.println("Lokkartenemulator");
   Serial.println("1 - Read SD Karte");
   Serial.println("2 - empty loco card");
   Serial.println("3 - insert loco card");
   Serial.println("4 - remove loco card");
   Serial.println("5 - read loco");
   Serial.println("6 - write loco");
   Serial.println("7 - init loco with dummy");
   Serial.println("8 - add loco to set");
   Serial.println("8 - insert loco set");
   Serial.print("> ");
}

void setup()
{
   delay(3000);
   Serial.begin(115200);
   Serial.println(__FILE__);
   Serial.println("Serial EEPROM version:");
   Serial.println(I2C_EEPROM_VERSION);

   if (!VirtLokKarte.LoadCard(Lokomotive.GetBinData()))
      Serial.println("load loco to fram failed");

   print_menu();
}

void loop()
{
   UserCmd = Serial.read();
   if (UserCmd != -1)
   {
      switch (UserCmd)
      {
         case '1':
            read_sd_card();
            break;
         case '2':
            empty_card();
            break;
         case '3':
            insert_card();
            break;
         case '4':
            remove_card();
            break;
         case '5':
            read_loco();
            break;
         case '6':
            write_loco();
            break;
         case '7':
            copy_loco_data();
            break;
         case '8':
            add_loco_to_set();
            break;
         case '9':
            insert_loco_set();
            break;
      }
      print_menu();
   }
}

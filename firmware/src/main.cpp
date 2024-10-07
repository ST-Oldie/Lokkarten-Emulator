#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
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

   Serial.print("Dateiname: ");
   LokFileName = Serial.readString();
   Lokomotive.ReadBin(SD.open(LokFileName, FILE_READ));
}

void write_loco(void)
{  String LokFileName;

   Serial.print("Dateiname: ");
   LokFileName = Serial.readString();
   Lokomotive.WriteBin(SD.open(LokFileName, FILE_WRITE));
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
      }
      print_menu();
   }
}

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

uint8_t loco_id = 10;
int sd_card;
File root;
LocoCard VirtLokKarte;
Loco Lokomotive;
int UserCmd;

/* Test with simple BIN File of BR86 */
void copy_loco_data()
{  uint16_t i;

   Lokomotive.SetBinSize(LOCO_SIZE);
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
      root = SD.open("/LocoCards");
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

void print_menu(void)
{
   Serial.println("Lokkartenemulator");
   Serial.println("1 - Test von Gerd");
   Serial.println("2 - Read SD Karte");
   Serial.print("> ");
}

void do_gb_test(void)
{
   Serial.println("Cycle");
   delay(2000);
   loco_id = loco_id +1;
   if (loco_id > 70)
      loco_id = 10;
   Lokomotive.GetBinData()[246]++;
   if (Lokomotive.GetBinData()[246] > 0x39)
   {
      Lokomotive.GetBinData()[246]=0x30;
   }
   Lokomotive.GetBinData()[5]=loco_id;
   Lokomotive.GetBinData()[11]=loco_id;
   Serial.printf("Loco ID: %d\n", loco_id);
   VirtLokKarte.SetConnection(Connected2Cpu);
   if (!VirtLokKarte.LoadCard(Lokomotive.GetBinData(), Lokomotive.GetBinSize()))
      Serial.println("load loco to fram failed");
   Serial.println("Card Change");
   delay(500);
   VirtLokKarte.SetConnection(Connected2Ms2);
}

void setup()
{
   delay(3000);
   Serial.begin(115200);
   Serial.println(__FILE__);
   Serial.println("Serial EEPROM version:");
   Serial.println(I2C_EEPROM_VERSION);

   copy_loco_data();

   read_sd_card();

   if (!VirtLokKarte.LoadCard(Lokomotive.GetBinData(), Lokomotive.GetBinSize()))
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
            do_gb_test();
            break;
         case '2':
            read_sd_card();
            break;
      }
      print_menu();
   }
}

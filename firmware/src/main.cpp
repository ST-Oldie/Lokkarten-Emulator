#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <LocoCard.h>
#include <loco.h>
#include "BR_xx.h"

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

/* Test with simple BIN File of BR86 */
void copy_loco_data(){
  uint16_t i;
  for (i = 0; i < LOCO_SIZE; i++) {
    Lokomotive.GetBinData()[i] = pgm_read_byte_far(&BR86_bin[i]);
  }
  Lokomotive.SetBinSize(LOCO_SIZE);
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
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

void setup() {
  delay(3000);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("Serial EEPROM version:");
  Serial.println(I2C_EEPROM_VERSION);

  copy_loco_data();

  Serial.print("Initialising SD Card ... ");
  if (!SD.begin(SPI_CS)) {
    Serial.println("initialization failed - no SD Card inserted ?");
    sd_card = 0;
  } else {
    Serial.println("success :-)");
    sd_card = 1;
  }

  if (sd_card) {
    root = SD.open("/LocoCards");
    if (root) {
      printDirectory(root, 0);
    } else {
      Serial.println("no directorty /LocoCards !");
    }
  }

  if (!VirtLokKarte.LoadCard(Lokomotive.GetBinData(), Lokomotive.GetBinSize()))
    Serial.println("load loco to fram failed");
}


void loop() {
  Serial.println("Cycle");
  delay(2000);
  loco_id = loco_id +1;
  if (loco_id > 70)
     loco_id = 10;
  Lokomotive.GetBinData()[246]++;
  if (Lokomotive.GetBinData()[246] > 0x39) {
    Lokomotive.GetBinData()[246]=0x30;
  }
  Lokomotive.GetBinData()[5]=loco_id;
  Lokomotive.GetBinData()[11]=loco_id;
  Serial.printf("Loco ID: %d\n", loco_id);
  VirtLokKarte.RemoveCard();
  if (!VirtLokKarte.LoadCard(Lokomotive.GetBinData(), Lokomotive.GetBinSize()))
    Serial.println("load loco to fram failed");
  Serial.println("Card Change");
  delay(500);
  VirtLokKarte.InsertCard();
}

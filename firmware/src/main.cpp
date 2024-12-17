#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Cfg.h>
#include <LocoSet.h>
#include <LocoCard.h>
#include <loco.h>

/* define fuer Test der Basisklassen fuer Lok, Lokliste, ... */
#define TEST_BASIC

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

LocoSet LokSatz;
LocoCard VirtLokKarte;
Loco Lokomotive;
Cfg Config;

#ifdef TEST_BASIC
#include "test_basic.h"
#endif

void setup()
{
   Config.ReadIniconfig();
#ifdef TEST_BASIC
   test_basic_setup();
#endif
}

void loop()
{
#ifdef TEST_BASIC
   test_basic_loop();
#endif
}

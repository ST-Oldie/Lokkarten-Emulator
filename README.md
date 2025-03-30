Die Maerlin Mobile Station 2 (MS2) bietet die Moeglichkeit, Lokomotiven auch
auf einer I2C Speicherkarte mit serielle EEPROM zu speichern. Es gibt eine
Emulation einer solchen Karte mit uController, die es ermoeglicht
Lokkartenimages z.B. von einer SD-Karte einzulesen und dann der MS2 zu
praesentieren. Die Harddware dazu findet man unter
https://github.com/GBert/railroad im Unterverzeichnis ms2-card-esp8266 und
wurde von Gerhard Bertelsmann entwickelt.

Unter firmware sind die Sourcen der Firmware fuer diese Hardware zu finden.

Unter hardware befindet sich eine Kopie der Hardware auis dem Repositoy von
Gerhard Bertelsmann, damit saemtliche Dateien aus einem Repository bezogen
werden koennen.

Die LICENSE gilt deshalb nur fuer die firmware.

Die Entwicklungsumgebung kann nach dem Vorschlag von Gerd Bertelsmann aus
dem Stummi Forum aufgesetzt werden:
https://www.stummiforum.de/t202512f7-Lokkarten-Emulator-Interesse-1.html#msg26732

Nach dem clonen des Repositories bzw. Download als ZIP und entpacken, öffnet
man mit Visual Studio Code das Verzeichnis "firmware".

Achtung: zur Zeit enthält die verwendete iniFile Library ein Problem. Sie kennt
nicht den ESP8266. Damit schlägt der Build fehl. Es muß also der folgende Workaround
gemacht werden:

Die iniFile lib wird ja im Projektverzeichnis der Firmware nach
.pio\libdeps\esp122 geklont. Dort muß unter src die Datei IniFile.cpp editiert
werden. In Zeile 386 steht:

#if defined(ARDUINO_ARCH_ESP32) && !defined(PREFER_SDFAT_LIBRARY)
 
Diese Zeile muß geändert werden auf:

#if (defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)) && !defined(PREFER_SDFAT_LIBRARY)

----------------------------------------------------------------------

The Maerlin Mobile Station 2 (MS2) allows to store locomotives on an I2C
smartcard with serial EEPROM. There is a amulation of such a device. This
allows to use card images e.g. from sd card and present them to the MS2. The
hardware files can be found at https://github.com/GBert/railroad in the
subdirectory ms2-card-esp8266. The hardware is deveoped by Gerhard Bertelsmann.

The firmware directory contains the sourced files for the firmware of this
hardware.

The hardware directory contains a copy of hardware from the repository from
Gerhard Bertelsmann. This should allow to get hardware and software files
from one repository.

So the LICENSE is only valid for firmware.

The development environment can be set up like a suggestion from Gerd Bertelsmann
in the Stummi Forum:
https://www.stummiforum.de/t202512f7-Lokkarten-Emulator-Interesse-1.html#msg26732

After cloning the repositories or download and unzip the sources, open the folder
"firmware" in Visual Studio Code.

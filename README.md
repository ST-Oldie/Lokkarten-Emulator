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

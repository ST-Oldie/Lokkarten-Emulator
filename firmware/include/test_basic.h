#include "BR_xx.h"

#define LOCO_SIZE       272

/* Test with simple BIN File of BR86 */
void copy_loco_data()
{  uint16_t i;

   for (i = 0; i < LOCO_SIZE; i++)
   {
      Lokomotive.GetBinData()[i] = pgm_read_byte_far(&BR86_bin[i]);
   }
}

void ReadFileName(const char *Prompt, char *FileNameBuf)
{  unsigned int ndx;
   char rc, endMarker = '\r';
   bool newData;

   Serial.print(Prompt);
   Serial.print(": ");
   newData = false;
   ndx = 0;
   rc = 0;
   do
   {
      while (Serial.available() == 0)
         ;
      while (Serial.available() > 0 && newData == false && rc != endMarker)
      {
         rc = Serial.read();
         if (rc != endMarker)
         {
            Serial.print(rc);
            FileNameBuf[ndx] = rc;
            ndx++;
         }
         else
         {
            FileNameBuf[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
         }
      }
   } while (rc != endMarker);
   Serial.println("");
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

void read_sd_card(const char *Path)
{  File root;

   if (!SD.exists(Path))
   {
      Serial.print("directory ");
      Serial.print(Path);
      Serial.println(" not exist, create");
      if (!SD.mkdir(Path))
      {
         Serial.print("can not create ");
         Serial.println(Path);
      }
   }
   root = SD.open(Path);
   if (root)
   {
      printDirectory(root, 0);
   }
   else
   {
      Serial.print("no directorty ");
      Serial.print(Path);
      Serial.println(" !");
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
   VirtLokKarte.UnloadCard(Lokomotive.GetBinData());
   VirtLokKarte.SetConnection(Disconnected);
}

void read_loco(void)
{  char LokFileName[80], FullName[250];
   fs::File LocoFile;

   ReadFileName("Dateiname", LokFileName);
   strcpy(FullName, CfgFsPath);
   strcat(FullName, "/");
   strcat(FullName, LokFileName);
   Serial.println(FullName);
   LocoFile = SD.open(FullName, FILE_READ);
   Lokomotive.ReadBin(LocoFile);
   LocoFile.close();
}

void write_loco(void)
{  char LokFileName[80], FullName[250];
   fs::File LocoFile;

   ReadFileName("Dateiname", LokFileName);
   strcpy(FullName, CfgFsPath);
   strcat(FullName, "/");
   strcat(FullName, LokFileName);
   Serial.println(FullName);
   LocoFile = SD.open(FullName, FILE_WRITE);
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

void chg_dir(void)
{
   ReadFileName("SD Card Path: ", CfgFsPath);
   if (!SD.exists(CfgFsPath))
   {
      Serial.print("directory ");
      Serial.print(CfgFsPath);
      Serial.println(" not exist, create");
      if (!SD.mkdir(CfgFsPath))
      {
         Serial.print("can not create ");
         Serial.println(CfgFsPath);
      }
   }
}

void print_menu(void)
{
   Serial.println("Lokkartenemulator");
   Serial.println("1 - Read SD Karte         2 - empty loco card");
   Serial.println("3 - insert loco card      4 - remove loco card");
   Serial.println("5 - read loco             6 - write loco");
   Serial.println("7 - init loco with dummy  8 - add loco to set");
   Serial.println("9 - insert loco set       a - change directory");
   Serial.print("> ");
}

void test_basic_setup(void)
{
   delay(3000);
   Serial.begin(115200);
   Serial.println(__FILE__);
   Serial.println("Serial EEPROM version:");
   Serial.println(I2C_EEPROM_VERSION);

   Serial.print("Initialising SD Card ... ");
   if (!SD.begin(SPI_CS))
   {
      Serial.println("initialization failed - no SD Card inserted ?");
   }

   CfgReadIniConfig();

   print_menu();
}

void test_basic_loop(void)
{  int UserCmd;

   UserCmd = Serial.read();
   if (UserCmd != -1)
   {
      switch (UserCmd)
      {
         case '1':
            read_sd_card(CfgFsPath);
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
         case 'a':
            chg_dir();
            break;
      }
      print_menu();
   }
}

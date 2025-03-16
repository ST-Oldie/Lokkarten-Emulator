#include <ESP8266WiFi.h>
#include <SD.h>
#include <map>
#include <HtmlPages.h>
#include <Cfg.h>
#include "LcWebServer.h"

/**
* @addtogroup LcWebServer
*
* @{
*/

LcWebServer::LcWebServer(Cfg *ActualConfig)
{
   Config = ActualConfig;
   WebServer = new ESP8266WebServer;
}

void LcWebServer::Start(void)
{
   WebServer->begin();
}

void LcWebServer::SetUriCb(const Uri &Uri, TrivialCB Handler)
{
   WebServer->on(Uri, Handler);
}

void LcWebServer::HandleClient(void)
{
   WebServer->handleClient();
}

void LcWebServer::HandleRootPage(void)
{
   WebServer->send(200, "text/html", EncHTMLRootPage("Lococard"));
}

void LcWebServer::HandleConfigPage(void)
{
   WebServer->send(200, "text/html", EncHTMLConfigPage("Lococard Config", Config));
}

void GetLocos(File dir, std::map<int, char *> &FileNames)
{  String LocoList;
   int i;

   i = 0;
   while (true)
   {
      File entry =  dir.openNextFile();
      if (!entry)
      {
         // no more files
         break;
      }
      if (!entry.isDirectory())
      {
         FileNames[i] = strdup((char *)entry.name());
         i++;
      }
      entry.close();
   }
}

File OpenLocoDir(Cfg *Config)
{  char *Path;

   Path = Config->GetCfgVal(CFG_VALUE_LOCO_PATH);
   if (strcmp(Path, "/") != 0)
   {
      if (!SD.exists(Path))
      {
         SD.mkdir(Path);
      }
   }
   return(SD.open(Path));
}

void LcWebServer::HandleLocoPage(void)
{  File root;
   unsigned int i;

   for (i = 0; i < FileNames.size(); i++)
      free(FileNames[i]);
   FileNames.clear();
   root = OpenLocoDir(Config);
   if (root)
   {
      GetLocos(root, FileNames);
   }
   WebServer->send(200, "text/html", EncHTMLLocoPage("Lococard Locos", FileNames));
}

void LcWebServer::HandleEmptyPage(void)
{
   Lokomotive.SetEmpty();
   if (VirtLokKarte.LoadCard(Lokomotive.GetBinData()))
      VirtLokKarte.SetConnection(Connected2Ms2);
   WebServer->send(200, "text/html", EncHTMLEmptyPage("Lococard Empty"));
}

void LcWebServer::HandleConfigGet(void)
{  String FormValue;

   Config->SetCfgVal(CFG_VALUE_SSID, WebServer->arg(0));
   Config->SetCfgVal(CFG_VALUE_PASSWORD, WebServer->arg(1));
   Config->SetCfgVal(CFG_VALUE_LOCAL_IP, WebServer->arg(2));
   Config->SetCfgVal(CFG_VALUE_GATEWAY_IP, WebServer->arg(3));
   Config->SetCfgVal(CFG_VALUE_SUBNET_MASK, WebServer->arg(4));
   Config->SetCfgVal(CFG_VALUE_DNS_IP, WebServer->arg(5));
   Config->SetCfgVal(CFG_VALUE_LOCO_PATH, WebServer->arg(6));
   Config->WriteIniconfig();
   WebServer->send(200, "text/html", EncHTMLRootPage("Lococard"));
}

void LcWebServer::HandleLoco2Card(void)
{  char FullName[250];
   fs::File LocoFile;
   int i;

   i = 0;
   while ((WebServer->arg(i) == "0") && (i < WebServer->args()))
   {
      i++;
   }
   if (i < WebServer->args())
   {
      strcpy(FullName, Config->GetCfgVal(CFG_VALUE_LOCO_PATH));
      if (FullName[strlen(FullName) - 1] != '/')
      {
         strcat(FullName, "/");
      }
      strcat(FullName, FileNames[i]);
      LocoFile = SD.open(FullName, FILE_READ);
      if (LocoFile)
      {
         Lokomotive.ReadBin(LocoFile);
         LocoFile.close();
         if (VirtLokKarte.LoadCard(Lokomotive.GetBinData()))
            VirtLokKarte.SetConnection(Connected2Ms2);
      }
   }
   FileNames.clear();
   WebServer->send(200, "text/html", EncHTMLRemoveCard("Lococard"));
}

void LcWebServer::HandleRemCard(void)
{
   if (VirtLokKarte.GetConnection() == Connected2Ms2)
   {
      VirtLokKarte.UnloadCard(Lokomotive.GetBinData());
      VirtLokKarte.SetConnection(Disconnected);
   }
   WebServer->send(200, "text/html", EncHTMLRootPage("Lococard"));
}

void LcWebServer::HandleSaveCard(void)
{  char FullName[250];
   fs::File LocoFile;

   VirtLokKarte.UnloadCard(Lokomotive.GetBinData());
   VirtLokKarte.SetConnection(Disconnected);
   if (!WebServer->arg(0).isEmpty())
   {
      strcpy(FullName, Config->GetCfgVal(CFG_VALUE_LOCO_PATH));
      if (FullName[strlen(FullName) - 1] != '/')
      {
         strcat(FullName, "/");
      }
      strcat(FullName, WebServer->arg(0).c_str());
      SD.remove(FullName);
      LocoFile = SD.open(FullName, FILE_WRITE);
      Lokomotive.WriteBin(LocoFile);
      LocoFile.close();
   }
   WebServer->send(200, "text/html", EncHTMLRootPage("Lococard"));
}

/** @} */

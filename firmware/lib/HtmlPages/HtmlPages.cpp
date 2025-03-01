#include <Arduino.h>
#include <SD.h>
#include <Cfg.h>

static String HtmlHead(String TitleOfForm)
{
   return "<!DOCTYPE html><html><body><h1>" + TitleOfForm + "</h1><p>";
}

static String HtmlFooter(void)
{
   return "</body></html>";
}

String EncHTMLRootPage(String TitleOfForm)
{
   String HTMLPage = HtmlHead(TitleOfForm);
   HTMLPage += "<ul>";
   HTMLPage += "<li><a href=\"config.htm\">Konfiguration</A>";
   HTMLPage += "<li><a href=\"loco.htm\">Liste der Lokomotiven</A>";
   HTMLPage += "<li><a href=\"empty.htm\">Leere Lococard einlegen</A>";
   HTMLPage += "</ul>";
   HTMLPage += HtmlFooter();
   return HTMLPage;
}

// Build a HTML page with a form which shows textboxes to enter the config values
// returns the HTML code of the page
String EncHTMLConfigPage(String TitleOfForm, Cfg *Config)
{  String ConfigValue, TableRowHTML;

   String HTMLPage = HtmlHead(TitleOfForm);
   HTMLPage += "<form action=/config_action><table>\n";
   if (Config->GetCfgVal(CFG_VALUE_SSID) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_SSID);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>SSID</th><td><input name=\"SSID\" value=\"" + ConfigValue + "\"/></td></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_PASSWORD) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_PASSWORD);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>Password</th><td><input name=\"Password\" value=\"" + ConfigValue + "\"></td></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_LOCAL_IP) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_LOCAL_IP);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>IP</th><td><input name=\"IP\" value=\"" + ConfigValue + "\"></td></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_GATEWAY_IP) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_GATEWAY_IP);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>Gateway</th><td><input name=\"Gateway\" value=\"" + ConfigValue + "\"></td></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_SUBNET_MASK) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_SUBNET_MASK);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>Netmask</th><td><input name=\"Mask\" value=\"" + ConfigValue + "\"></td></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_DNS_IP) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_DNS_IP);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>DNS</th><td><input name=\"DNS\" value=\"" + ConfigValue + "\"></td></tr>\n";
   HTMLPage += TableRowHTML;
   TableRowHTML = "<tr><td colspan=2><hr></td></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_LOCO_PATH) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_LOCO_PATH);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>Pfad</th><td><input name=\"Pfad\" value=\"" + ConfigValue + "\"></td></tr>\n";
   HTMLPage += TableRowHTML;
   // add the submit button
   HTMLPage += "</table><br><button type=\"submit\" value=\"Submit\">ok</button></form>";
   HTMLPage += HtmlFooter();
   return HTMLPage;
}

String printDirectory(File dir)
{  String LocoList;

   LocoList = "<form action=/insert_loco><ul>";
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
         LocoList += "<input type=\"radio\" id=\"";
         LocoList += entry.name();
         LocoList += "\" name=\"loco\" value=\"";
         LocoList += entry.name();
         LocoList += "\">";
         LocoList += "<label for=\"";
         LocoList += entry.name();
         LocoList += "\">";
         LocoList += entry.name();
         LocoList += "</label><br>";
      }
      entry.close();
   }
   LocoList += "</ul><br><button type=\"submit\" value=\"Submit\">Insert</buttpn></form>";
   return(LocoList);
}

File OpenLocoDir(Cfg *Config)
{  char *Path;

   Path = Config->GetCfgVal(CFG_VALUE_LOCO_PATH);
   Serial.println(Path);
   if (strcmp(Path, "/") != 0)
   {
      if (!SD.exists(Path))
      {
         SD.mkdir(Path);
      }
   }
   return(SD.open(Path));
}

String EncHTMLLocoPage(String TitleOfForm, Cfg *Config)
{  File root;

   String HTMLPage = HtmlHead(TitleOfForm);
   root = OpenLocoDir(Config);
   if (root)
   {
      HTMLPage += printDirectory(root);
   }
   else
      HTMLPage += "no loco directory";
   HTMLPage += HtmlFooter();
   return HTMLPage;
}

String EncHTMLEmptyPage(String TitleOfForm)
{
   String HTMLPage = HtmlHead(TitleOfForm);
   HTMLPage += "<form action=/save_loco>";
   HTMLPage += "Locofile Name: <input name=\"name\" value=\"\"><br>\n";
   HTMLPage += "<button type=\"submit\" value=\"Submit\">Save Lococard</button></form>";
   HTMLPage += HtmlFooter();
   return HTMLPage;
}

String EncHTMLRemoveCard(String TitleOfForm)
{
   String HTMLPage = HtmlHead(TitleOfForm);
   HTMLPage += "<form action=/rem_loco><button type=\"submit\" value=\"Submit\">Remove Lococard</button></form>";
   HTMLPage += HtmlFooter();
   return HTMLPage;
}
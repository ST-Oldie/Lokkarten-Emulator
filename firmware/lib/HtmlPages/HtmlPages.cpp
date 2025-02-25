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
   HTMLPage += "<li><a href=\"loco.htm\">Lokomotiven</A>";
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
   TableRowHTML = "<tr><th>SSID</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\"/></th></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_PASSWORD) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_PASSWORD);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>Password</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\"></th></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_LOCAL_IP) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_LOCAL_IP);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>IP</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\"></th></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_GATEWAY_IP) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_GATEWAY_IP);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>Gateway</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\"></th></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_SUBNET_MASK) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_SUBNET_MASK);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>Netmask</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\"></th></tr>\n";
   HTMLPage += TableRowHTML;
   if (Config->GetCfgVal(CFG_VALUE_DNS_IP) != (char *)NULL)
      ConfigValue = Config->GetCfgVal(CFG_VALUE_DNS_IP);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>DNS</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\"></th></tr>\n";
   HTMLPage += TableRowHTML;
   // add the submit button
   HTMLPage += "</table><br/><input type=\"submit\" value=\"Submit\" /></form>";
   HTMLPage += HtmlFooter();
   return HTMLPage;
}

String printDirectory(File dir)
{  String LocoList;

   LocoList = "<ul>";
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
         LocoList += "<li>";
         LocoList += entry.name();
      }
      entry.close();
   }
   LocoList += "</ul>";
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

#include <Arduino.h>
#include <Cfg.h>

// Build a HTML page with a form which shows textboxes to enter the config values
// returns the HTML code of the page
String EncHTMLConfigValues(String TitleOfForm, Cfg& Config)
{  String ConfigValue, TableRowHTML, StyleHTML;

   // Head of the HTML page
   String HTMLPage = "<!DOCTYPE html><html><body><h2>" + TitleOfForm + "</h2><form><table>";
   // configuration values
   StyleHTML = " Style =\"background-color: #FFE4B5;\" " ;   // yellow
   if (Config.GetCfgVal(CFG_VALUE_SSID) != (char *)NULL)
      ConfigValue = Config.GetCfgVal(CFG_VALUE_SSID);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>" + ConfigValue + "</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\" " + StyleHTML + " /></th></tr>";
   HTMLPage += TableRowHTML;
   if (Config.GetCfgVal(CFG_VALUE_PASSWORD) != (char *)NULL)
      ConfigValue = Config.GetCfgVal(CFG_VALUE_PASSWORD);
   else
      ConfigValue = "";
   TableRowHTML = "<tr><th>" + ConfigValue + "</th><th><input name=\"" + ConfigValue + "\" value=\"" + ConfigValue + "\" " + StyleHTML + " /></th></tr>";
   HTMLPage += TableRowHTML;
   // add the submit button
   HTMLPage += "</table><br/><input type=\"submit\" value=\"Submit\" />";
   // footer of the webpage
   HTMLPage += "</form></body></html>";
   return HTMLPage;
}

// Decodes a GET parameter (expression after ? in URI (URI = expression entered in address field of webbrowser)), like "Country=Germany&City=Aachen"
// and set the ConfigValues
int DecGETConfigValues(String GETParameter, Cfg& Config)
{  int posFirstCharToSearch, count;

   posFirstCharToSearch = 1;
   count = 0;
   // while a "&" is in the expression, after a start position to search
   while (GETParameter.indexOf('&', posFirstCharToSearch) > -1)
   {
      int posOfSeparatorChar = GETParameter.indexOf('&', posFirstCharToSearch);  // position of & after start position
      int posOfValueChar = GETParameter.indexOf('=', posFirstCharToSearch);      // position of = after start position
      switch (count)
      {
         case 0:
            Config.SetCfgVal(CFG_VALUE_SSID, GETParameter.substring(posOfValueChar + 1, posOfSeparatorChar));
            break;
         case 1:
            Config.SetCfgVal(CFG_VALUE_PASSWORD, GETParameter.substring(posOfValueChar + 1, posOfSeparatorChar));
            break;
      }
      posFirstCharToSearch = posOfSeparatorChar + 1;  // shift the start position to search after the &-char 
      count++;
   }
   // no more & chars found
   int posOfValueChar = GETParameter.indexOf('=', posFirstCharToSearch);       // search for =
   switch (count)
   {
      case 0:
         Config.SetCfgVal(CFG_VALUE_SSID, GETParameter.substring(posOfValueChar + 1, GETParameter.length()));
         break;
      case 1:
         Config.SetCfgVal(CFG_VALUE_PASSWORD, GETParameter.substring(posOfValueChar + 1, GETParameter.length()));
         break;
   }
   count++;
   return count;
}

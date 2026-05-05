#include <Arduino.h>
#include <SD.h>
#include <set>
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
   HTMLPage += "<li><a href=\"set.htm\">Lococard Liste erzeugen</A>";
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

String EncHTMLLocoPage(String TitleOfForm, std::map<int, char *> &FileNames)
{  File root;
   unsigned int i;

   String HTMLPage = HtmlHead(TitleOfForm);
   HTMLPage += "<form action=/insert_loco><ul>";
   for (i = 0; i < FileNames.size(); i++)
   {
      HTMLPage += "<input type=\"radio\" id=\"";
      HTMLPage += FileNames[i];
      HTMLPage += "\" name=\"loco\" value=\"";
      HTMLPage += FileNames[i];
      HTMLPage += "\">";
      HTMLPage += "<label for=\"";
      HTMLPage += FileNames[i];
      HTMLPage += "\">";
      HTMLPage += FileNames[i];
      HTMLPage += "</label><br>";
   }
   HTMLPage += "</ul><br><button type=\"submit\" value=\"Submit\">Insert</buttpn></form>";
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

// Build a HTML page with a name selector that allows selecting from a list of names
// Accepts a title and a vector of names to select from
// returns the HTML code of the page
String EncHTMLNameSelectorPage(String TitleOfForm, std::vector<String> names)
{
   String HTMLPage = HtmlHead(TitleOfForm);
   HTMLPage += "<script type=\"text/javascript\">";
   HTMLPage += "function MoveEntry(Source, Dest) {";
   HTMLPage += "    var leftlist = document.getElementById(Source);";
   HTMLPage += "    var selItem = leftlist.selectedIndex;";
   HTMLPage += "    if (selItem == -1) {";
   HTMLPage += "        window.alert(\"You must first select an item on the left side.\")";
   HTMLPage += "    } else {";
   HTMLPage += "        var rightlist = document.getElementById(Dest);";
   HTMLPage += "        var newOption = leftlist[selItem].cloneNode(true);";
   HTMLPage += "        leftlist.removeChild(leftlist[selItem]);";
   HTMLPage += "        rightlist.appendChild(newOption);";
   HTMLPage += "    }";
   HTMLPage += "}";
   HTMLPage += "</script>";
   HTMLPage += "<form>";
   HTMLPage += "<table>";
   HTMLPage += "<tr><th>Lok images</th><th>&nbsp;</th><th>Lokliste</th></tr>";
   HTMLPage += "<tr>";
   HTMLPage += "<td>";
   HTMLPage += "<select id=\"t1available\" size=\"10\">";
   for (unsigned int i = 0; i < names.size(); i++)
   {
      HTMLPage += "<option>" + names[i] + "</option>";
      if (i < names.size() - 1)
         HTMLPage += ", ";
   }
   HTMLPage += "</select>";
   HTMLPage += "</td>";
   HTMLPage += "<td>";
   HTMLPage += "<input id=\"t1add\" type=\"button\" value=\">\" onclick=\"MoveEntry('t1available', 't1published');\"><br>";
   HTMLPage += "<input id=\"t1remove\" type=\"button\" value=\"<\" onclick=\"MoveEntry('t1published', 't1available');\"><br>";
   HTMLPage += "</td>";
   HTMLPage += "<td>";
   HTMLPage += "<select id=\"t1published\" size=\"10\"></select>";
   HTMLPage += "</td>";
   HTMLPage += "</tr>";
   HTMLPage += "</table>";
   HTMLPage += "</form>";
   HTMLPage += HtmlFooter();
   return HTMLPage;
}

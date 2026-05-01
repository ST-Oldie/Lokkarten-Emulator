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
   String HTMLPage = "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>";
   HTMLPage += TitleOfForm;
   HTMLPage += "</title><style>";
   HTMLPage += "* { margin: 0; padding: 0; box-sizing: border-box; }";
   HTMLPage += "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; display: flex; justify-content: center; align-items: center; padding: 20px; }";
   HTMLPage += ".container { background: white; border-radius: 12px; box-shadow: 0 20px 60px rgba(0, 0, 0, 0.3); max-width: 600px; width: 100%; overflow: hidden; }";
   HTMLPage += ".header { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; padding: 30px; text-align: center; }";
   HTMLPage += ".header h1 { margin-bottom: 10px; font-size: 28px; }";
   HTMLPage += ".header p { opacity: 0.9; font-size: 14px; }";
   HTMLPage += ".content { padding: 30px; }";
   HTMLPage += ".search-box { margin-bottom: 20px; }";
   HTMLPage += ".search-box input { width: 100%; padding: 12px; border: 2px solid #e0e0e0; border-radius: 8px; font-size: 16px; transition: all 0.3s; }";
   HTMLPage += ".search-box input:focus { outline: none; border-color: #667eea; box-shadow: 0 0 8px rgba(102, 126, 234, 0.2); }";
   HTMLPage += ".controls { display: flex; gap: 10px; margin-bottom: 20px; }";
   HTMLPage += ".btn { flex: 1; padding: 10px 15px; border: none; border-radius: 6px; font-size: 14px; cursor: pointer; transition: all 0.3s; font-weight: 600; }";
   HTMLPage += ".btn-primary { background: #667eea; color: white; }";
   HTMLPage += ".btn-primary:hover { background: #5568d3; transform: translateY(-2px); box-shadow: 0 4px 12px rgba(102, 126, 234, 0.4); }";
   HTMLPage += ".btn-secondary { background: #f5f5f5; color: #333; }";
   HTMLPage += ".btn-secondary:hover { background: #e0e0e0; }";
   HTMLPage += ".list-container { border: 2px solid #e0e0e0; border-radius: 8px; max-height: 350px; overflow-y: auto; background: #f9f9f9; margin-bottom: 20px; }";
   HTMLPage += ".list-container::-webkit-scrollbar { width: 8px; }";
   HTMLPage += ".list-container::-webkit-scrollbar-track { background: #f1f1f1; border-radius: 10px; }";
   HTMLPage += ".list-container::-webkit-scrollbar-thumb { background: #667eea; border-radius: 10px; }";
   HTMLPage += ".list-container::-webkit-scrollbar-thumb:hover { background: #5568d3; }";
   HTMLPage += ".name-item { padding: 12px 15px; border-bottom: 1px solid #eee; display: flex; align-items: center; transition: background 0.2s; }";
   HTMLPage += ".name-item:hover { background: #f0f0f0; }";
   HTMLPage += ".name-item input { margin-right: 12px; cursor: pointer; width: 18px; height: 18px; accent-color: #667eea; }";
   HTMLPage += ".name-item label { flex: 1; cursor: pointer; user-select: none; }";
   HTMLPage += ".selected-names { margin-bottom: 20px; }";
   HTMLPage += ".selected-names h3 { margin-bottom: 10px; color: #333; font-size: 16px; }";
   HTMLPage += ".tags { display: flex; flex-wrap: wrap; gap: 8px; }";
   HTMLPage += ".tag { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; padding: 6px 12px; border-radius: 20px; font-size: 14px; display: flex; align-items: center; gap: 8px; }";
   HTMLPage += ".tag button { background: none; border: none; color: white; cursor: pointer; font-size: 16px; padding: 0; line-height: 1; }";
   HTMLPage += ".tag button:hover { opacity: 0.8; }";
   HTMLPage += ".stats { background: #f5f5f5; padding: 12px 15px; border-radius: 6px; font-size: 14px; color: #666; text-align: center; }";
   HTMLPage += ".empty-state { text-align: center; padding: 30px 20px; color: #999; }";
   HTMLPage += "</style></head><body>";
   HTMLPage += "<div class=\"container\">";
   HTMLPage += "<div class=\"header\"><h1>";
   HTMLPage += TitleOfForm;
   HTMLPage += "</h1><p>Select names from the list below</p></div>";
   HTMLPage += "<div class=\"content\">";
   HTMLPage += "<div class=\"search-box\"><input type=\"text\" id=\"searchInput\" placeholder=\"Search names...\"></div>";
   HTMLPage += "<div class=\"controls\"><button class=\"btn btn-primary\" onclick=\"selectAll()\">Select All</button><button class=\"btn btn-secondary\" onclick=\"clearAll()\">Clear All</button></div>";
   HTMLPage += "<div class=\"list-container\" id=\"namesList\"></div>";
   HTMLPage += "<div class=\"selected-names\"><h3>Selected Names (<span id=\"selectedCount\">0</span>)</h3><div class=\"tags\" id=\"selectedTags\"></div></div>";
   HTMLPage += "<div class=\"stats\">Total available: <strong>";
   HTMLPage += names.size();
   HTMLPage += "</strong> names</div>";
   HTMLPage += "</div></div>";
   HTMLPage += "<script>";
   HTMLPage += "const allNames = [";
   for (unsigned int i = 0; i < names.size(); i++)
   {
      HTMLPage += "\"" + names[i] + "\"";
      if (i < names.size() - 1)
         HTMLPage += ", ";
   }
   HTMLPage += "];";
   HTMLPage += "const selected = new Set();";
   HTMLPage += "function renderList(filter = '') {";
   HTMLPage += "  const container = document.getElementById('namesList');";
   HTMLPage += "  const filtered = allNames.filter(n => n.toLowerCase().includes(filter.toLowerCase()));";
   HTMLPage += "  if (filtered.length === 0) {";
   HTMLPage += "    container.innerHTML = '<div class=\"empty-state\">No names found</div>';";
   HTMLPage += "    return;";
   HTMLPage += "  }";
   HTMLPage += "  container.innerHTML = filtered.map(name => `";
   HTMLPage += "    <div class=\"name-item\">";
   HTMLPage += "      <input type=\"checkbox\" id=\"${name}\" onchange=\"toggleName('${name}')\">";
   HTMLPage += "      <label for=\"${name}\">${name}</label>";
   HTMLPage += "    </div>`;";
   HTMLPage += "  }".replace("\"`", "`");
   HTMLPage += "  filtered.forEach(name => {";
   HTMLPage += "    if (selected.has(name)) {";
   HTMLPage += "      document.getElementById(name).checked = true;";
   HTMLPage += "    }";
   HTMLPage += "  });";
   HTMLPage += "}";
   HTMLPage += "function updateSelected() {";
   HTMLPage += "  document.getElementById('selectedCount').textContent = selected.size;";
   HTMLPage += "  const tagsDiv = document.getElementById('selectedTags');";
   HTMLPage += "  tagsDiv.innerHTML = Array.from(selected).map(name => `";
   HTMLPage += "    <div class=\"tag\"><span>${name}</span><button type=\"button\" onclick=\"removeName('${name}')\">×</button></div>`;";
   HTMLPage += "  }".replace("\"`", "`");
   HTMLPage += "}";
   HTMLPage += "function toggleName(name) {";
   HTMLPage += "  if (selected.has(name)) {";
   HTMLPage += "    selected.delete(name);";
   HTMLPage += "  } else {";
   HTMLPage += "    selected.add(name);";
   HTMLPage += "  }";
   HTMLPage += "  updateSelected();";
   HTMLPage += "}";
   HTMLPage += "function removeName(name) {";
   HTMLPage += "  selected.delete(name);";
   HTMLPage += "  document.getElementById(name).checked = false;";
   HTMLPage += "  updateSelected();";
   HTMLPage += "}";
   HTMLPage += "function selectAll() {";
   HTMLPage += "  allNames.forEach(name => selected.add(name));";
   HTMLPage += "  renderList(document.getElementById('searchInput').value);";
   HTMLPage += "  updateSelected();";
   HTMLPage += "}";
   HTMLPage += "function clearAll() {";
   HTMLPage += "  selected.clear();";
   HTMLPage += "  renderList(document.getElementById('searchInput').value);";
   HTMLPage += "  updateSelected();";
   HTMLPage += "}";
   HTMLPage += "document.getElementById('searchInput').addEventListener('input', (e) => {";
   HTMLPage += "  renderList(e.target.value);";
   HTMLPage += "});";
   HTMLPage += "renderList();";
   HTMLPage += "</script>";
   HTMLPage += "</body></html>";
   return HTMLPage;
}

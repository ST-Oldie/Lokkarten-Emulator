#ifndef HTMPPAGES_H
#define HTMLPAGEDS_H

#include <Arduino.h>
#include <map>
#include <Cfg.h>

String EncHTMLRootPage(String TitleOfForm);
String EncHTMLConfigPage(String TitleOfForm, Cfg *Config);
String EncHTMLLocoPage(String TitleOfForm, std::map<int, char *> &FileNames);
String EncHTMLEmptyPage(String TitleOfForm);
String EncHTMLRemoveCard(String TitleOfForm);

#endif
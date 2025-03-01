#ifndef HTMPPAGES_H
#define HTMLPAGEDS_H

#include <Arduino.h>
#include <Cfg.h>

String EncHTMLRootPage(String TitleOfForm);
String EncHTMLConfigPage(String TitleOfForm, Cfg *Config);
String EncHTMLLocoPage(String TitleOfForm, Cfg *Config);
String EncHTMLEmptyPage(String TitleOfForm);
String EncHTMLRemoveCard(String TitleOfForm);

#endif
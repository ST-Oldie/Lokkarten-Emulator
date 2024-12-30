#ifndef HTMPPAGES_H
#define HTMLPAGEDS_H

#include <Arduino.h>
#include <Cfg.h>

String EncHTMLConfigValues(String TitleOfForm, Cfg& Config);
int DecGETConfigValues(String GETParameter, Cfg& Config);

#endif
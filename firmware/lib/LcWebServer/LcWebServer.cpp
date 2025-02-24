#include <ESP8266WiFi.h>
#include <HtmlPages.h>
#include <Cfg.h>
#include "LcWebServer.h"

/**
* @addtogroup LcWebServer
*
* @{
*/

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

void LcWebServer::HandleLocoPage(void)
{
   WebServer->send(200, "text/html", EncHTMLLocoPage("Lococard Locos", Config));
}

void LcWebServer::HandleConfigGet(void)
{  String FormValue;

   Config->SetCfgVal(CFG_VALUE_SSID, WebServer->arg(0));
   Config->SetCfgVal(CFG_VALUE_PASSWORD, WebServer->arg(1));
   Config->SetCfgVal(CFG_VALUE_LOCAL_IP, WebServer->arg(2));
   Config->SetCfgVal(CFG_VALUE_GATEWAY_IP, WebServer->arg(3));
   Config->SetCfgVal(CFG_VALUE_SUBNET_MASK, WebServer->arg(4));
   Config->SetCfgVal(CFG_VALUE_DNS_IP, WebServer->arg(5));
   Config->WriteIniconfig();
}

/** @} */

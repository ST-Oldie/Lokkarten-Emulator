#include <ESP8266WiFi.h>
#include "LcWebServer.h"

/**
* @addtogroup LcWebServer
*
* @{
*/

LcWebServer::LcWebServer()
{
   Server = new WiFiServer(80);
}

void LcWebServer::Start(void)
{
   Server->begin();
}

//  Call this function regularly to look for client requests
//  template see https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/SimpleWiFiServer/SimpleWiFiServer.ino
//  returns empty string if no request from any client
//  returns GET Parameter: everything after the "/?" if ADDRESS/?xxxx was entered by the user in the webbrowser
//  returns "-" if ADDRESS but no GET Parameter was entered by the user in the webbrowser
//  remark: client connection stays open after return
String LcWebServer::GetRequestGETParameter(void)
{  String GETParameter, currentLine;
   char c;

   GETParameter = "";
   Client = Server->accept();
   if (Client)
   {
      currentLine = "";
      while (Client.connected())
      {
         if (Client.available())
         {
            c = Client.read();
            if (c == '\n')
            {
               if (currentLine.length() == 0)
               {
                  if (GETParameter == "")
                  {
                     GETParameter = "-";
                  }
                  break;
               }
               else
               {
                  currentLine = "";
               }
            }
            else if (c != '\r')
            {
               currentLine += c;
            }
            if (c=='\r' && currentLine.startsWith("GET /?")) 
            {
               // we see a "GET /?" in the HTTP data of the client request
               // user entered ADDRESS/?xxxx in webbrowser, xxxx = GET Parameter
               // extract everything behind the ? and before a space
               GETParameter = currentLine.substring(currentLine.indexOf('?') + 1, currentLine.indexOf(' ', 6));
            }
            if (c=='\r' && currentLine.startsWith("Host:")) 
            {
               // we see a "Host:" in the HTTP data of the client request
               // user entered ADDRESS or ADDRESS/... in webbrowser, ADDRESS = Server IP-Address of HTTP-Request
               // extract everything behind the space character and store Server IP-Address of HTTP-Request
               int IndexOfBlank = currentLine.indexOf(' ');
               WebRequestHostAddress = currentLine.substring(IndexOfBlank + 1, currentLine.length());
            }
         }
      }
   }
   return GETParameter;
}

// Send HTML page to client, as HTTP response
// client connection must be open (call Webserver_GetRequestGETParameter() first)
void LcWebServer::SendHTMLPage(String HTMLPage)
{  String httpResponse = "";

   // begin with HTTP response header
   httpResponse += "HTTP/1.1 200 OK\r\n";
   httpResponse += "Content-type:text/html\r\n\r\n";
   // then the HTML page
   httpResponse += HTMLPage;
   // The HTTP response ends with a blank line:
   httpResponse += "\r\n";
   // send it out to TCP/IP client = webbrowser 
   Client.println(httpResponse);
   // close the connection
   Client.stop();
}

/** @} */

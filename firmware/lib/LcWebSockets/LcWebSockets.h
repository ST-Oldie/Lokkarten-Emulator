#ifndef LCWEBSOCKETS_H
#define LCWEBSOCKETS_H

#include <WebSocketServer.h>

/**
 * @defgroup LcWebSockets web socket server class for LocoCard Emulator
 *
 * @{
 */
/**

* @brief class for hold information of a web connection
*/
class LcWebSockets
{
   public:
      LcWebSockets();
   private:
      WebSocketServer  *Server;
};

/** @} */

#endif

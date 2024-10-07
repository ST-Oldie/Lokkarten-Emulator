#ifndef LOCO_CARD_H
#define LOCO_CARD_H

#include <I2C_eeprom.h>

typedef enum ConnectionType {
   Disconnected,
   Connected2Cpu,
   Connected2Ms2
};

class LocoCard: I2C_eeprom
{
   public:
      LocoCard();

      void SetConnection(ConnectionType NewConnection);
      ConnectionType GetConnection(void);
      boolean LoadCard(const uint8_t *Loco, unsigned int Size);

   private:
      ConnectionType ActualConnection;

      void InsertCard(void);
      void RemoveCard(void);
      void ConnectToCpu(void);
      void DisconnectFromCpu(void);
};

#endif
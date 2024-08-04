#ifndef LOCO_CARD_H
#define LOCO_CARD_H

#include <I2C_eeprom.h>

class LocoCard
{
   public:
      LocoCard();

      void InsertCard(void);
      void RemoveCard(void);
      boolean IsInserted(void);
      void ConnectToCpu(boolean Connect);
      boolean IsConnected(void);
      boolean LoadCard(const uint8_t *Loco, unsigned int Size);

   private:
      I2C_eeprom *Fram;
      boolean CardIsInserted;
      boolean IsConnectedToCpu;
};

#endif
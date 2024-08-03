#ifndef LOCO_CARD
#define LOCO_CARD

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
      boolean LoadCard(const uint8_t *Loco, uint16_t Size);

   private:
      I2C_eeprom *Fram;
      boolean CardIsInserted;
      boolean IsConnectedToCpu;
};

#endif
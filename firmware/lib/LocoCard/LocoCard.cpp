#include <Arduino.h>
#include <Wire.h>
#include "LocoCard.h"

#define I2C_Select   2
#define I2C_SDA      4
#define I2C_SCL      5
#define I2C_CLOCK    100000
#define I2C_ADDRESS  0x50
#define Card_Change  16

LocoCard::LocoCard()
{
   pinMode(Card_Change, OUTPUT);
   pinMode(I2C_Select, OUTPUT);
   Wire.begin(I2C_SDA, I2C_SCL);
   Wire.setClock(I2C_CLOCK);
   digitalWrite(Card_Change, 0);
   CardIsInserted = false;
   digitalWrite(I2C_Select, 0);
   IsConnectedToCpu = false;
   Fram = new I2C_eeprom(I2C_ADDRESS, I2C_DEVICESIZE_24LC64);
   Fram->begin();
}

void LocoCard::InsertCard(void)
{
   digitalWrite(Card_Change, 1);
   CardIsInserted = true;
}

void LocoCard::RemoveCard(void)
{
   digitalWrite(Card_Change, 0);
   CardIsInserted = false;
}

boolean LocoCard::IsInserted(void)
{
   return CardIsInserted;
}

void LocoCard::ConnectToCpu(boolean Connect)
{
   digitalWrite(I2C_Select, Connect?1:0);
   IsConnectedToCpu = Connect;
}

boolean LocoCard::IsConnected(void)
{
   return IsConnectedToCpu;
}

boolean LocoCard::LoadCard(const uint8_t *Loco, unsigned int Size)
{  boolean ret;

   ConnectToCpu(true);
   if (Fram->isConnected())
   {
      if (Fram->writeBlock(0, (const uint8_t *)Loco, Size) == 0)
      {
         ret = true;
      }
      else
      {
         ret = false;
      }
   }
   else
   {
      ret = false;
   }
   ConnectToCpu(false);
   return(ret);
}

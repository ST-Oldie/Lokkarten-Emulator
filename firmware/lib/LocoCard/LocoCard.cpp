#include <Arduino.h>
#include <Wire.h>
#include "LocoCard.h"

/**
* @addtogroup LOCO_CARD
*
* @{
*/

#define I2C_Select   2
#define I2C_SDA      4
#define I2C_SCL      5
#define I2C_CLOCK    100000
#define I2C_ADDRESS  0x50
#define Card_Change  16

LocoCard::LocoCard(): I2C_eeprom(I2C_ADDRESS, I2C_DEVICESIZE_24LC64)
{
   pinMode(Card_Change, OUTPUT);
   pinMode(I2C_Select, OUTPUT);
   Wire.begin(I2C_SDA, I2C_SCL);
   Wire.setClock(I2C_CLOCK);
   digitalWrite(Card_Change, 0);
   digitalWrite(I2C_Select, 0);
   ActualConnection = Disconnected;
   begin();
}

void LocoCard::SetConnection(ConnectionType NewConnection)
{
   if (NewConnection != ActualConnection)
   {
      // first disconnect virtual loco card
      if (ActualConnection == Connected2Cpu)
      {
         DisconnectFromCpu();
      }
      else if (ActualConnection == Connected2Ms2)
      {
         RemoveCard();
      }
      // then connect virtual loco card
      if (NewConnection == Connected2Cpu)
      {
         ConnectToCpu();
      }
      else if (NewConnection == Connected2Ms2)
      {
         InsertCard();
      }
      // and store new connection status
      ActualConnection = NewConnection;
   }
}

ConnectionType LocoCard::GetConnection(void)
{
   return(ActualConnection);
}

void LocoCard::InsertCard(void)
{
   digitalWrite(Card_Change, 1);
}

void LocoCard::RemoveCard(void)
{
   digitalWrite(Card_Change, 0);
}

void LocoCard::ConnectToCpu(void)
{
   digitalWrite(I2C_Select, 1);
}

void LocoCard::DisconnectFromCpu(void)
{
   digitalWrite(I2C_Select, 0);
}

boolean LocoCard::LoadCard(const uint8_t *Loco)
{  boolean ret;
   ConnectionType OldConnection;

   // store old conenction status and connect to cpu if not
   OldConnection = ActualConnection;
   if (OldConnection != Connected2Cpu)
   {
      SetConnection(Connected2Cpu);
   }
   if (isConnected())
   {
      // fram is connected to cpu, write content of loco card
      if (writeBlock(0, Loco, I2C_DEVICESIZE_24LC64) == 0)
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
   // restore old connection status
   SetConnection(OldConnection);
   return(ret);
}

boolean LocoCard::UnloadCard(uint8_t *Loco)
{  boolean ret;
   ConnectionType OldConnection;

   // store old conenction status and connect to cpu if not
   OldConnection = ActualConnection;
   if (OldConnection != Connected2Cpu)
   {
      SetConnection(Connected2Cpu);
   }
   if (isConnected())
   {
      // fram is connected to cpu, read content of loco card
      if (readBlock(0, Loco, I2C_DEVICESIZE_24LC64) == 0)
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
   // restore old connection status
   SetConnection(OldConnection);
   return(ret);
}

/** @} */

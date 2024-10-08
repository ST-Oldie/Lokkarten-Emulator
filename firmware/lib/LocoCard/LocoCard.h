#ifndef LOCO_CARD_H
#define LOCO_CARD_H

#include <I2C_eeprom.h>

/**
 * @defgroup LOCO_CARD class for a loco card
 *
 * @{
 */

/**
* @brief enum for different types of how the FRAM is connected
*/
enum ConnectionType {
   Disconnected,  /** FRAM is neither connected to CPU nor connected to MS2 */
   Connected2Cpu, /** FRAM is conencted to CPU */
   Connected2Ms2  /** FRAM is connected to MS2 */
};

/**
* @brief class for handling the FRAM
*/
class LocoCard: I2C_eeprom
{
   public:
      LocoCard();

      void SetConnection(ConnectionType NewConnection); /** connect to CPU od MS2 or disconnect */
      ConnectionType GetConnection(void);               /** get, how the FRAM was connected */
      boolean LoadCard(const uint8_t *Loco);            /** load binary data into the FRAM */
      boolean UnloadCard(uint8_t *Loco);          /** read binary data from the FRAM */

   private:
      ConnectionType ActualConnection; /** is the loco card connected to ms2, cpu or not connected */

      void InsertCard(void);        /** connect FRAM to MS2 */
      void RemoveCard(void);        /** disconnect FRAM from MS2 */
      void ConnectToCpu(void);      /** connect FRAM to CPU */
      void DisconnectFromCpu(void); /** disconneect FRAM from CPU */
};

/** @} */

#endif
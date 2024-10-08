#ifndef LOCO_H
#define LOCO_H

#include <stdio.h>
#include <string.h>
#include <I2C_eeprom.h>
#include <FS.h>

/**
 * @defgroup LOCO class for hold data of a loco
 *
 * @{
 */

/**
* @brief number of functions (light, ...)
*/
#define LOCO_NUM_FUNCTIONS 32

/**
* @brief struct for one loco function
*/
typedef struct {
   uint16_t Typ;
   uint16_t Dauer;
   uint16_t Wert;
} LokFktTyp;

/**
* @brief macros to set values in LokFktTyp
*/
#define LokFktSetTyp(Data, Val)   (Data)->Typ=Val
#define LokFktSetDauer(Data, Val) (Data)->Dauer=Val
#define LokFktSetWert(Data, Val)  (Data)->Wert=Val

/**
* @brief macros to get values from LokFktTyp
*/
#define LokFktGetTyp(Data, Val)   (Data)->Typ
#define LokFktGetDauer(Data, Val) (Data)->Dauer
#define LokFktGetWert(Data, Val)  (Data)->Wert

/**
* @brief class for hold information of a loco
*/
class Loco
{
   public:
      Loco();

      boolean IsEmpty(void);               /** returns, if loco is empty */
      void SetEmpty(void);                 /** set loco to empty (all bytes to 0xff) */
      void Serialize(void);                /** convert loco info to bin image */
      void Deserialize(void);              /** convert bin image to loco info */
      boolean ReadBin(fs::File LocoFile);  /** read binary image file */
      boolean WriteBin(fs::File LocoFile); /** write binary iameg file */
      void Write2Cs2(fs::File LocoFile);   /** write loco info as lokomotive.cs2 snippet */
      // set properties
      void SetUid(uint32_t Val)         { Uid = Val; };
      void SetName(char *Val)           { strcpy(Name, Val); };
      void SetAdresse(uint16_t Val)     { Adresse = Val; };
      void SetTyp(char *Val)            { strcpy(Typ, Val); };
      void SetMfxUid(uint32_t Val)      { MfxUid = Val; };
      void SetSymbol(uint16_t Val)      { Symbol = Val; };
      void SetAv(uint16_t Val)          { Av = Val; };
      void SetBv(uint16_t Val)          { Bv = Val; };
      void SetVolume(uint16_t Val)      { Volume = Val; };
      void SetVelocity(uint16_t Val)    { Velocity = Val; };
      void SetDirection(uint16_t Val)   { Direction = Val; };
      void SetVmax(uint16_t Val)        { Vmax = Val; };
      void SetVmin(uint16_t Val)        { Vmin = Val; };
      // set properties for loco functions
      void SetNumFkts(unsigned int Val) { NumFkts = Val; };
      void SetFktTyp(unsigned int Idx, uint16_t Val)   { Fkt[Idx].Typ = Val; };
      void SetFktDauer(unsigned int Idx, uint16_t Val) { Fkt[Idx].Dauer = Val; };
      void SetFktWert(unsigned int Idx, uint16_t Val)  { Fkt[Idx].Wert = Val; };
      // get properties
      uint8_t *GetBinData(void)      { return BinData; };
      uint32_t GetUid(void)          { return Uid; };
      char *GetName(void)            { return Name; };
      uint16_t GetAdresse(void)      { return Adresse; };
      char *GetTyp(void)             { return Typ; };
      uint32_t GetMfxUid(void)       { return MfxUid; };
      uint16_t GetSymbol(void)       { return Symbol; };
      uint16_t GetAv(void)           { return Av; };
      uint16_t GetBv(void)           { return Bv; };
      uint16_t GetVolume(void)       { return Volume; };
      uint16_t GetVelocity(void)     { return Velocity; };
      uint16_t GetDirection(void)    { return Direction; };
      uint16_t GetVmax(void)         { return Vmax; };
      uint16_t GetVmin(void)         { return Vmin; };
      // get properties for loco functions
      unsigned int GetNumFkts(void)          { return NumFkts; };
      uint16_t GetFktTyp(unsigned int Idx)   { return Fkt[Idx].Typ; };
      uint16_t GetFktDauer(unsigned int Idx) { return Fkt[Idx].Dauer; };
      uint16_t GetFktWert(unsigned int Idx)  { return Fkt[Idx].Wert; };

   private:
      // loco as binary data how it is stored on I2C memory
      uint8_t BinData[I2C_DEVICESIZE_24LC64]; /** binary image fie data */
      boolean LocoIsEmpty;                    /** is BinData set to empty (all bytes to 0xff) */
      // decoded loco information
      uint32_t Uid;
      char Name[17];
      uint16_t Adresse;
      char Typ[20];
      uint32_t MfxUid;
      uint16_t Symbol;
      uint16_t Av;
      uint16_t Bv;
      uint16_t Volume;
      uint16_t Velocity;
      uint16_t Direction;
      uint16_t Vmax;
      uint16_t Vmin;
      unsigned int NumFkts;
      LokFktTyp Fkt[LOCO_NUM_FUNCTIONS];
};

/** @} */

#endif

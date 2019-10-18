/**
 * @file     crc.h (180.ARM_Peripherals/Project_Headers/crc.h)
 * @brief    External Watchdog Monitor
 *
 * @version  V4.12.1.230
 * @date     13 April 2016
 */

#ifndef HEADER_CRC_H_
#define HEADER_CRC_H_
 /*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
#include "derivative.h"
#include "hardware.h"

namespace USBDM {

/**
 * @addtogroup CRC_Group CRC, Cyclic Redundancy Check
 * @brief Abstraction for Cyclic Redundancy Check
 * @{
 */

/**
 * Type Of Transpose For Writes.
 * Defines the transpose configuration of the data written to the CRC data register.
 */
enum CrcWriteTranspose {
   CrcWriteTranspose_None          = CRC_CTRL_TOT(0), //!< No transpose
   CrcWriteTranspose_Bits          = CRC_CTRL_TOT(1), //!< Transpose bits only
   CrcWriteTranspose_BitsAndBytes  = CRC_CTRL_TOT(2), //!< Transpose bits and bytes
   CrcWriteTranspose_Bytes         = CRC_CTRL_TOT(3), //!< Transpose bytes only
};

/**
 * Type Of Transpose For Read.
 * Identifies the transpose configuration of the value read from the CRC Data register
 */
enum CrcReadTranspose {
   CrcReadTranspose_None          = CRC_CTRL_TOT(0), //!< No transpose
   CrcReadTranspose_Bits          = CRC_CTRL_TOT(1), //!< Transpose bits only
   CrcReadTranspose_BitsAndBytes  = CRC_CTRL_TOT(2), //!< Transpose bits and bytes
   CrcReadTranspose_Bytes         = CRC_CTRL_TOT(3), //!< Transpose bytes only
};

/**
 * Complement Read Of CRC Data Register.
 * Some CRC protocols require the final checksum to be XORed with 0xFFFFFFFF or 0xFFFF.
 * Asserting this enables on the fly complementing of read data.
 */
enum CrcReadComplement {
   CrcReadComplement_Inactive = CRC_CTRL_FXOR(0), //!< No complement of CRC data register on read
   CrcReadComplement_Active   = CRC_CTRL_FXOR(1), //!< Complement of CRC data register on read
};

/**
 * Width of CRC protocol.
 */
enum CrcWidth {
   CrcWidth_16bits = CRC_CTRL_TCRC(0), //!< 16-bit CRC protocol
   CrcWidth_32bits = CRC_CTRL_TCRC(1), //!< 32-bit CRC protocol
};


/**
 * Template class representing the Cyclic Redundancy Check Monitor.
 *
 * The cyclic redundancy check (CRC) module generates 16/32-bit CRC code for error detection.
 * The CRC module provides a programmable polynomial, WAS, and other parameters
 * required to implement a 16-bit or 32-bit CRC standard.
 * The 16/32-bit code is calculated for 32 bits of data at a time.
 *
 * Example CRC methods provided
 * See http://reveng.sourceforge.net/crc-catalogue/
 * @code
 *                      CRC-16/CCIT-FALSE ARC(CRC-16) CRC-32
 * Width                16 bits           16 bits     32 bits
 * Polynomial           0x1021            0x8005      0x04C11DB7
 * Initial seed         0xFFFF            0x0000      0xFFFFFFFF
 * Input transform      None              B&B         B&B
 * Output transform     None              B&B         B&B
 * Complement checksum  No                No          Yes
 * @endcode
 *
 * @tparam info      Information class for CRC
 */
template<class Info>
class CrcBase_T {

public:
   /**
    * Hardware instance pointer.
    *
    * @return Reference to CRC hardware
    */
   static __attribute__((always_inline)) volatile CRC_Type &crc() { return Info::crc(); }

public:

   /**
    * Basic enable CRC.
    *
    * Includes enabling clock
    */
   static void enable() {

      // Enable clock to CRC interface
      Info::enableClock();
   }

   /**
    * Enable with default settings.
    */
   static void defaultConfigure() {
      enable();
      // Initialise hardware
//      crc().GPOLY = Info::gpoly;
   }

   /**
    * Configure CRC.
    *
    * @param crcWidth           Width of CRC protocol.
    * @param crcWriteTranspose  Type of transpose for Writes.
    * @param crcReadTranspose   Type of transpose for read.
    * @param crcReadComplement  Complement read of CRC data register.
    */
   static __attribute__((always_inline)) void configure(
         CrcWidth             crcWidth,
         CrcWriteTranspose    crcWriteTranspose,
         CrcReadTranspose     crcReadTranspose,
         CrcReadComplement    crcReadComplement) {
      enable();
      crc().CTRL = crcWidth|crcWriteTranspose|crcReadTranspose|crcReadComplement;
   }

   /**
    * Write polynomial value used for CRC calculation.
    *
    * @param polynomialValue Polynomial value used for CRC calculation
    */
   static void writePolynomial(uint32_t polynomialValue) {
      crc().GPOLY = polynomialValue;
   }

   /**
    * Get polynomial value used for CRC calculation.
    *
    * @return Polynomial value used for CRC calculation
    */
   static uint32_t getPolynomial(uint32_t polynomialValue) {
      uint32_t data = crc().GPOLY;
      if ((crc().CTRL&CRC_CTRL_TCRC_MASK) == 0) {
         data &= 0xFFFF;
      }
      return data;
   }

   /**
    * Write seed value for CRC calculation.
    *
    * @param seedValue  Seed value to initialise CRC calculation
    */
   static void writeSeed(uint32_t seedValue) {
      crc().CTRL |= CRC_CTRLHU_WAS_MASK;
      crc().DATA = seedValue;
      crc().CTRL &= ~CRC_CTRLHU_WAS_MASK;
   }

   /**
    * Write data value for CRC calculation.
    *
    * @param dataValue  Data value for CRC calculation
    */
   static void writeData8(uint8_t dataValue) {
      crc().DATALL = dataValue;
   }

   /**
    * Write data value for CRC calculation.
    *
    * @param dataValue  Data value for CRC calculation
    */
   static void writeData16(uint16_t dataValue) {
      crc().DATAL = dataValue;
   }

   /**
    * Write data value for CRC calculation.
    *
    * @param dataValue  Data value for CRC calculation
    */
   static void writeData32(uint32_t dataValue) {
      crc().DATA = dataValue;
   }

   /**
    * Get calculated CRC value.
    *
    * @return Calculated CRC value
    */
   static uint32_t getCalculatedCrc() {
      uint32_t data = crc().DATA;
      if ((crc().CTRL&CRC_CTRL_TCRC_MASK) == 0) {
         // Truncate to 16-bit value
         data &= 0xFFFF;
      }
      return data;
   }

   /**
    * Disable interface to CRC.
    */
   static void disable() {
      Info::disableClock();
   }

   /**
    * Configure CRC-16/CCIT-FALSE
    * See http://reveng.sourceforge.net/crc-catalogue/
    */
   static void configure_Crc16_ccit_false() {
      configure(
            CrcWidth_16bits,
            CrcWriteTranspose_None,
            CrcReadTranspose_None,
            CrcReadComplement_Inactive
            );
      writePolynomial(0x1021);
      writeSeed(0xFFFF);
   }

   /**
    * Configure ARC (aka CRC-16)
    * See http://reveng.sourceforge.net/crc-catalogue/
    */
   static void configure_Crc16() {
      configure(
            CrcWidth_16bits,
            CrcWriteTranspose_BitsAndBytes,
            CrcReadTranspose_BitsAndBytes,
            CrcReadComplement_Inactive
            );
      writePolynomial(0x8005);
      writeSeed(0x0000);
   }

   /**
    * Configure CRC-32
    * See http://reveng.sourceforge.net/crc-catalogue/
    */
   static void configure_Crc32() {
      configure(
            CrcWidth_32bits,
            CrcWriteTranspose_BitsAndBytes,
            CrcReadTranspose_BitsAndBytes,
            CrcReadComplement_Active
            );
      writePolynomial(0x04c11db7);
      writeSeed(0xffffffff);
   }

};

#if defined(USBDM_CRC_IS_DEFINED)
class Crc : public CrcBase_T<CrcInfo> {};
#endif

#if defined(USBDM_CRC0_IS_DEFINED)
class Crc0 : public CrcBase_T<Crc0Info> {};
#endif

/**
 * End CRC_Group
 * @}
 */
} // End namespace USBDM

#endif /* HEADER_CRC_H_ */

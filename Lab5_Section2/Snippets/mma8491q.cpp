/**
 * @file mma8491q.cpp
 *
 *  Created on: 22/11/2013
 *      Author: podonoghue
 */
#include "mma8491q.h"
#include "delay.h"
 /*
 * *****************************
 * *** DO NOT EDIT THIS FILE ***
 * *****************************
 *
 * This file is generated automatically.
 * Any manual changes will be lost.
 */
namespace USBDM {

#define MMA8491Q_STATUS_ZYXDR_MASK   (1<<3)

/**
 * Obtains measurements from the accelerometer
 *
 * @param[out] status  Indicates status of x, y & z measurements
 * @param[out] x       X axis value
 * @param[out] y       Y axis value
 * @param[out] z       Z axis value
 */
void MMA8491Q::readAccelerometerXYZ(int &status, int16_t &x, int16_t &y, int16_t &z) {
   uint8_t dataXYZ[7] = {STATUS};

   // Receive 7 registers (status, X-high, X-low, Y-high, Y-low, Z-high & Z-low)
   i2c.txRx(DEVICE_ADDRESS, 1, sizeof(dataXYZ), dataXYZ);

   // Unpack data and return
   status = dataXYZ[0];
   x = (((int16_t)((dataXYZ[1]<<8)+dataXYZ[2]))>>2) + offsetX;
   y = (((int16_t)((dataXYZ[3]<<8)+dataXYZ[4]))>>2) + offsetY;
   z = (((int16_t)((dataXYZ[5]<<8)+dataXYZ[6]))>>2) + offsetZ;
}

/**
 * Calibrate accelerometer
 */
void MMA8491Q::calibrateAccelerometer() {

   offsetX = 0;
   offsetY = 0;
   offsetZ = 0;

   const int calibration1G = 1024;

   int16_t Xout_Accel_14_bit, Yout_Accel_14_bit, Zout_Accel_14_bit;
   int     Xout_Accel=0, Yout_Accel=0, Zout_Accel=0;

   // Average 8 samples to reduce noise
   for (int i=0; i<8; i++) {
      int status;
      active();
      do {
         waitUS(1000);
         readAccelerometerXYZ(status, Xout_Accel_14_bit, Yout_Accel_14_bit, Zout_Accel_14_bit);
      } while ((status & MMA8491Q_STATUS_ZYXDR_MASK) == 0);
      standby();
      Xout_Accel += Xout_Accel_14_bit;
      Yout_Accel += Yout_Accel_14_bit;
      Zout_Accel += Zout_Accel_14_bit;
   }

   offsetX = -(Xout_Accel/8);                  // Compute X-axis offset correction value
   offsetY = -(Yout_Accel/8);                  // Compute Y-axis offset correction value
   offsetZ = -(Zout_Accel/8 - calibration1G);  // Compute Z-axis offset correction value
}

} // End namespace USBDM

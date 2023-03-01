#ifndef _Sensor_Vl5310x
#define _Sensor_Vl5310x

#include "VL53L0X.h"

VL53L0X sensor;
//int distance;
const int numReadings =10;
int readings[numReadings];
int readIndex =0;
int total =0;
int avarage =0;

// Uncomment this line to use long range mode. This
// increases the sensitivity of the sensor and extends its
// potential range, but increases the likelihood of getting
// an inaccurate reading because of reflections from objects
// other than the intended target. It works best in dark
// conditions.

#define LONG_RANGE

// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

//#define HIGH_SPEED
//#define HIGH_ACCURACY


class Sensor_Vl5310x
{
private:
    /* data */
public:
    Sensor_Vl5310x(/* args */);
    int Avarage(bool);
};

Sensor_Vl5310x::Sensor_Vl5310x(/* args */)
{
 for (int i = 0; i < numReadings; i++)    {
  readings[i] = 0 ;
}
  Wire.begin();
  sensor.init(true);
  sensor.setAddress(0x30);
  sensor.setTimeout(500);
  if (!sensor.init())  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
 
    // sensor.writeReg(VL53L0X::SYSRANGE_START, 0x02);
#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.001);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);

#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
 sensor.startContinuous(0);
}

int Sensor_Vl5310x::Avarage(bool SeriPrint){

// for (int i = 0; i < 10; i++)
// {
//  // Str = (String)sensor.readRangeContinuousMillimeters(); //.readRangeSingleMillimeters();
//    distance =sensor.readReg16Bit(sensor.RESULT_RANGE_STATUS +10);
// sensor.writeReg(sensor.SYSTEM_INTERRUPT_CLEAR, 0x01);
//   	Str= (String)distance;
// }
//  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
total =  total - readings[readIndex];
int veri =sensor.readReg16Bit(sensor.RESULT_RANGE_STATUS +10);
sensor.writeReg(sensor.SYSTEM_INTERRUPT_CLEAR, 0x01);
if(veri <= 1200 || 0 < veri ){ 
readings[readIndex] = veri;
total  = total+ readings[readIndex];
readIndex = readIndex +1;
if( readIndex >= numReadings )
  readIndex =0;

  avarage = total /numReadings;
}
if(SeriPrint)
    Serial.println(avarage);

return avarage;
}


#endif
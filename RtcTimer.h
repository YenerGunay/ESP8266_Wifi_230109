#ifndef _RtcTimer
#define _RtcTimer

#include "RTClib.h"
RTC_DS3231 rtc;


class RtcTimer
{
private:
    /* data */
public:
    RtcTimer(/* args */);
//    void setupRTC();
    void RtcLoop(bool);
    DateTime datetim();
   void DateTimeSet(String);
};


RtcTimer::RtcTimer(/* args */)
{
  // if (!rtc.begin()) {
  //   Serial.println("Couldn't find RTC");
  //   Serial.flush();
  //   while (1) delay(10);
  // }
  rtc.begin();
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2023, 1, 29, 14, 02, 00)); 
  } 
  //Serial.println("RTC Timer ayarlama!");
 
}
  
// #define dat "01/29/2023"
// #define tim "12:12:12"

void RtcTimer::DateTimeSet(String datTim){
  uint8_t _MM = datTim.substring(0,2).toInt();
  uint8_t _dd = datTim.substring(3,5).toInt();
  uint16_t _yyyy = datTim.substring(6,10).toInt();
  uint8_t _hh = datTim.substring(11,13).toInt();
  uint8_t _mm = datTim.substring(14,16).toInt();
  uint8_t _ss = datTim.substring(17,19).toInt();
   Serial.println(_MM);
   Serial.println(_dd);
   Serial.println(_yyyy);
   Serial.println(_hh);
   Serial.println(_mm);
   Serial.println(_ss);
   
  Serial.println(datTim);
  rtc.begin();
  rtc.adjust(DateTime(_yyyy, _MM, _dd, _hh, _mm, _ss)); 
  
  // // rtc.begin();
  // //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   //rtc.adjust(DateTime(2023, 1, 29, 14, 02, 00)); 
 //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

 //  rtc.adjust(DateTime(F("01/29/2023"), F("14:07:12")));
    //dat datTim.substring(0,10);
  //  tim = datTim.substring(11,18);
   //rtc.adjust(DateTime(F(dat),F(tim)));


  //  Serial.println(datTim.substring(0,10));
  //  Serial.println(datTim.substring(11,18));
  //  Serial.println(datTim.substring(0,2));
  //  Serial.println(datTim.substring(3,5));
  //  Serial.println(datTim.substring(6,10));
  //  Serial.println(datTim.substring(11,13));
  //  Serial.println(datTim.substring(14,16));
  //  Serial.println(datTim.substring(17,19));
}



//DateTime now;
DateTime RtcTimer::datetim(){
  DateTime now2 = rtc.now();
  return now2;
}

// void RtcTimer::setupRTC(){
//   // if (!rtc.begin()) {
//   //   Serial.println("Couldn't find RTC");
//   //   Serial.flush();
//   //   while (1) delay(10);
//   // }
//   rtc.begin();
//   if (rtc.lostPower()) {
//     Serial.println("RTC lost power, let's set the time!");
//     // When time needs to be set on a new device, or after a power loss, the
//     // following line sets the RTC to the date & time this sketch was compiled
//     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//     // This line sets the RTC with an explicit date & time, for example to set
//     // January 21, 2014 at 3am you would call:
//     //rtc.adjust(DateTime(2023, 1, 29, 14, 02, 00)); 
//   }
// }

int count =0;
bool LedFlashOn =false;
void RtcTimer::RtcLoop(bool serialPrint){
   // DateTime now = rtc.now();
    // Serial.print(now.year(), DEC);
    // Serial.print('/');
    // Serial.print(now.month(), DEC);
    char datetime_format2[] = "MM/DD/YYYY hh:mm:ss";
    char time_format[] = "hhmmss";
    display.set(datetim().toString(datetime_format2), ALIGN_RIGHT);
    display.set(datetim().toString(time_format), ALIGN_RIGHT);
    display.setDot(3, LedFlashOn);
    display.setDot(5, LedFlashOn);

    if(count > 250) {
        if(LedFlashOn) {
          LedFlashOn=false;
        }
        else{ 
          LedFlashOn=true;
        }
      display.show(count);
      count=0;
       if(serialPrint){
      Serial.println(datetim().toString(datetime_format2));
 }
      }
      count++;
    // display.setDot(3, true);
    // display.setDot(5, true);
    // display.show(100);
 }


#endif
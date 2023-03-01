/*********
 * Proje NAme   : ESP8266_WifiManager    
 * Proje Start  : 09-01-2023    
 * Proje Create : Yener 
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
  https://randomnerdtutorials.com/wifimanager-with-esp8266-autoconnect-custom-parameter-and-manage-your-ssid-and-password/
  https://www.youtube.com/watch?v=VnfX9YJbaU8
  http://robojax.com/learn/arduino/
  https://github.com/G6EJD
*********/

//#define TarihSaat
//#define TarihSaat_Lcd
//#define MesafeOlcer_Vl5310
//#define FULL
//#define APMode
#define Lcd_7Sehment
#define SKETCH_VERSION "1.0.2+2"


#include <Arduino.h>
#include <SoftwareSerial.h>
// #include "RTClib.h"
#include <SPI.h>


#include "Sys_Variables.h"
#include "MyClass/ESP8266_Html.h"
ESP8266_Html espHtml;
#include "MyClass/Scale.h"




myShiftDisplay myDisplay;


Scale ScaleView ;
#if defined(TarihSaat)
#include "MyClass/RtcTimer.h"     // RTC_DS3231 rtc;
RtcTimer rtcTim;
#endif

#if defined(IniRead)
#include "MyClass/Ini_ReadWrite.h"
Ini_ReadWrite inired;
#endif

#if defined(MesafeOlcer_Vl5310)
#include "MyClass/Sensor_Vl5310x.h"
Sensor_Vl5310x vl5310;
#endif


 void setup() {
  ScaleView.Parametre();
  delay(1000);

  pinMode(TRIGGER_PIN_PRINT, INPUT_PULLUP);
  pinMode(TRIGGER_PIN_FS, INPUT_PULLUP);

 //SevenSegmenDispayShowVinc("DENSi", 0, 7, true);
  Serial.begin(SerailBouderate1);
  Serial2.begin(SerailBouderate2 , SWSERIAL_8N1 ,RXD2,TXD2 ,false,128);
  myDisplay.showDisplay7S("Densi", 1 ,0);
    myDisplay.show(1000);

  // myDisplay.digit7segment("Densi",1000 ,0);
  //   clearDisplay();

  // myDisplay.digit7segment("Densi",1000 ,0);
  // clearDisplay();

#if defined(MesafeOlcer_Vl5310)
    Sensor_Vl5310x();
#endif
  //myDisplay.showDisplay7S("Densi", 10 ,0);

// Eğer Açılışta seri port aktif ve bilgi geliyor ise
// Seri Port olarak çalışmaya devam et.
if(Serial.available() > 0){
  PortOnOf=false;
   //myDisplay.digit7segment("Serial", 100 ,0);
  return;
}
else
  {
    espHtml.setupHTML();
}

  //  if ( digitalRead(TRIGGER_PIN_PRINT) == HIGH ){
  //    espHtml.setupHTML();
  //  } 
  //  else {
  //   WiFi.mode(WIFI_STA);
  //   WiFiManager wifiManager;
  //   wifiManager.resetSettings();
  //   wifiManager.setConfigPortalTimeout(timeout);
  //   if (!wifiManager.startConfigPortal("Pasam_OnDemandAP")) {
  //     Serial.println("AP Bağlantı Sorunu Kontrol Ediniz");
  //     delay(3000);
  //     //reset and try again, or maybe put it to deep sleep
  //     ESP.reset();
  //     delay(100);
  //   }
    // //if you get here you have connected to the WiFi
    // Serial.println("Bağlanti Basarili :)");
    // }

  #if defined(Lcd_7Sehment)
  String str = "fi" + (String)WiFi.RSSI();
  myDisplay.showDisplay7S(str ,500,0);

  str = WiFi.localIP().toString();
  str = str.substring(str.length()-6, str.length());
  myDisplay.showDisplay7S(str ,1000,0);
  clearDisplay();
  #endif

}




// int j=0;
// i++;
// if(i> 20){
//   j++;
//   i=0; }
// String str ="-";
// str += j;
//  digit7segment("ABCD");
//   return;
void loop(){
//Serial.println("Loop a girdi");
Gosterge_Sifirla++;
if(Gosterge_Sifirla > 200){
    Gosterge= "0";
    Par_Point = 0;
    Gosterge_Sifirla = 0; 
    }

  myDisplay.showDisplay7S(Gosterge ,1,0);
myDisplay.show(1);
 if ( digitalRead(TRIGGER_PIN_PRINT) == LOW ){
          Serial.println(ltFs.Fs_IniRead("/net.ini"));
          //display.show(500);
          delay(1500);
       return;
       ltFs.Fs_ReadLabel(labelName);
   } 
   else if ( digitalRead(TRIGGER_PIN_FS) == LOW ){
      //  Serial.print("Kısa bastın Oku : "); 
      //  Serial.println(ltFs.Fs_IniRead("[Plu]","PLU2="));
    //return;
     Serial.println("Reset Ap Moda geçme");
      espHtml.ESP8266_FactoryMod();

    //display.show(1500);
    myDisplay.showDisplay7S("FACTOR" ,1500,0);
   } 

//#endif

#if defined(MesafeOlcer_Vl5310)
  display.show((String)vl5310.Avarage(true) ,200, ALIGN_RIGHT);
#endif
#if defined(TarihSaat_Lcd)
  rtcTim.RtcLoop(false);
#endif


 espHtml.ESP8266_Htmlweb();

 
 // display.show();

  //display.update();
}



//bool send_nRF=false;
//char chr_end = '=';//; 	//int str_end = 10;
String Str_UartRead;//= "ST,GS,+02.1238,T=000.000,kg\r\n";
void serialEvent(){	// void SerialRead()
// // https://koddefteri.net/arduino/ileri-arduino-dersleri/arduino-seri-port-nesnesi.html
	if(Serial.available() > 0)	{
    char c = Serial.read();
    Str_UartRead += c;
    if( c== Par_endChr ){
      if(Str_UartRead.startsWith(";AA56xx:")){
        Serial.print("Gelen data ayikla :");
        Serial.println(Str_UartRead);

//int sa[6];//, //, t=0;
int r=0;
int leng =Str_UartRead.length();
for (int i=0; i < leng; i++)
{ 
 if(Str_UartRead.charAt(i) == ',') 
  { 
   // sa[t] = Str_UartRead.substring(r, i).toInt(); 
    Serial.println( Str_UartRead.substring(r, i+1).toInt());
     r=(i+1); 
    // t++; 
  }
}
    
      Str_UartRead="";
      }
      else if( Str_UartRead.length() > (size_t)(Par_TextSize -1) ){
 scale.DisplayGeneral(Str_UartRead, false);
 Str_UartRead="";

      }
    }

	}

	// //	send_nRF = true;
	// 	byte gelen[Par_TextSize]; 								// gelen adında 32 indisli dizi oluştur
  //       //int st =Serial.readBytesUntil(0xA,gelen,32); 	// gelen veriden 32 byte oku ve gelen dizisine aktar
	// 	int st = Serial.readBytesUntil(Par_Chr ,gelen,Par_TextSize); 	// gelen veriden 32 byte oku ve gelen dizisine aktar
	// 	for (int i = 0; i < st; i++)        {
  //           Str_UartRead += (char)gelen[i];
  //       }
  //       scale.DisplayGeneral(Str_UartRead, true);
  //       Str_UartRead="";
/*

  if (Serial.available() > 0) { // Eğer seri porta veri geldiyse
    gelen = Serial.readStringUntil('a'); // gelen veriyi "a" karakterine kadar oku ve gelen değişkenine aktar
  }
*/
//  String gelen;
//  String Gelen2; 
//   if (Serial.available() > 0) { // Eğer seri porta veri geldiyse
//     gelen = Serial.readStringUntil(Par_Chr); // gelen veriyi "a" karakterine kadar oku ve gelen değişkenine aktar
//     Gelen2 += gelen; 
//      if(Gelen2.length() > 4 )
//      {
//         scale.DisplayGeneral(Gelen2, true);
//         Gelen2 ="";
//      }
//   }
}



/*
/////////Bu fonksiyon ile Donanımsal Interrupt(Kesme) tanımlamış oluyoruz. Bu sayede butona bastığımızda
//kodun neresinde olursa olsun hemen reaksiyon göstererek buton işlemleri gerçekleştirilmiş olur.
ICACHE_RAM_ATTR void Alarmstop() {
  if (digitalRead(TRIGGER_PIN_PRINT) == LOW) {
      Serial.println("Butona BAsıldı");
          
  }
  return;
  if (!button) { //butona şu ana kadar hiç basılmamışsa yani ilk basışı ifade ediyoruz
    if (digitalRead(TRIGGER_PIN_PRINT) == HIGH) { //ve D1 pini HIGH olmuş yani butona basılmışsa
      buttonSayac = millis(); //basma süresini takip edecek bir sayac tanımlıyoruz
      button = true; //ve butona basıldı bilgisini tutan değişkeni TRUE yapıyoruz.
    }
  } 
  else { // eğer butona daha öncesinde basılmış ise
    if (digitalRead(TRIGGER_PIN_PRINT) == LOW) { //ve artık buton bırakılmış ise
      button = false; //butonu tekrar false a çek
      if ((millis() - buttonSayac) >= 50) {
          if ((millis() - buttonSayac) >= 3000) 
          {
          Serial.println(">3 sn");
          
          }
          else {
          Serial.println("<3 sn");

          // resetle = true;   //resetleme işleminin gerçekleştiğini güncelle ve TRUE yap
          // resetecek=true; //yukarıdakinin benzeri bir kullanım için
          }
          Serial.print("Sayac :");
          Serial.println(buttonSayac);
           Serial.print("Milis :");
          Serial.println(millis());
          buttonSayac=0;
        //   sayac = 0; 
//         if ((millis() - buttonSayac) >= 3000) { //toplam basma süresi 3sn den fazla sürmüş ise
//           Serial.println(">3 sn");
//           resetle = true;   //resetleme işleminin gerçekleştiğini güncelle ve TRUE yap
//           resetecek=true; //yukarıdakinin benzeri bir kullanım için
//         } else {       //////3sn den az bir basma olmuş ise
// //          alarmdurdur(); //bunu sadece alarm durdurma işlemi olarak kullan
//           sayac = 0;  //işimiz bitince de buton süre sayacını sıfırla
//           Serial.println("<3 sn");
//         }
      }
    }
  }

}
*/
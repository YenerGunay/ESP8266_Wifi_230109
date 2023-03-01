#define ServerVersion "1.2"
String webpage = "";
String labelName ="RP80VI_001.bin";
//char datetime_format[] = "MM/DD/YYYY hh:mm:ss";
//rtc.   DateTime now = rtc.now();
bool labelLogoChange = true;
int PluNo = 0;
int LabNo = 1;



SoftwareSerial Serial2;
bool   SD_present = true;
#define RXD2 13
#define TXD2 15


#define LOAD 16	//15;
#define SCLK 0  //4	//5 //14;
#define SDI  2  //0 //4 //13;

#ifdef ESP8266

//#define SD_CS_pin           D8         // The pin on Wemos D1 Mini for SD Card Chip-Select
#define TRIGGER_PIN_PRINT  12   //0
#define TRIGGER_PIN_FS     14     //2
// #define RXD2 16
// #define TXD2 17
#else
#define SD_CS_pin           5        // Use pin 5 on MH-T Live ESP32 version of Wemos D1 Mini for SD Card Chip-Select
#endif                               // Use pin 13 on Wemos ESP32 Pro



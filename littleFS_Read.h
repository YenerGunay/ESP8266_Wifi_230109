#ifndef _LittleFS_Read
#define _LittleFS_Read

#include "LittleFS.h"
#include <Arduino.h>
#include <FS.h>
//#include "ESP8266_Html.h"
//#include "ShiftDisplay.h"
const char _Menu_Start[] PROGMEM = R"=====([Network]
ModulMac1=01:23:45:67:89:AB
ModulIPNa=192.168.31.1
ModulMask=255.255.255.0
ModulGetw=192.168.31.2
[ApMode]
WifiMode=0
NetwSsid=Densi_Display
NetwPasw=
NetwIpNa=10.10.101.254
NetwMask=255.255.255.0
[Ssid]
SSIDName=Densi
SSIDPasw=
SSIDTcpi=10.10.100.3
SSIDMask=255.255.255.0
SSIDGetw=10.10.100.254
ServerOn=0
ServerIp=10.10.100.254
ServerPo=8899
[Parametre]
Size=9
Location=0
WeightStart=0
WeightStop=8
TareStart=0
TareStop=0
UnitStart=0
EndChar=61
TextMode=Yes
[Modul]
Comport1=1
Comport2=1
BaudeRate=115200
[Plu]
PLU1=1
PLU2=2
[Label]
Label1=label1
Label2=label2
)=====";



int timeout = 120;
int sel = 0;
// const char *filename1 = "RP80VI_005.bin";  //"index.html";//"2MB.txt"; 
// const char *filename2 = "RP80VI_006.bin";  //"index.html";//"2MB.txt"; 
  enum en_var { _0_PluName, _1_PluCode, _2_Origine,_3_LotNo, _4_FisNo, _5_Adress, _6_Grup, _7_Fiyat, _8_Oparator, _9_Text1, _10_Ack1,
   _11_Ack2, _12_Ack3, _13_Ack4, _14_Ack5, _15_Ack6, _16_Ack7, _17_Ack8, _18_Ack9, _19_Ack10, _20_Text2,
   _21_Text3, _22_Text4, _23_Text5, _24_KasaDarasi, _25_PaletDarasi, _26_KasaSayisi, _27_PaletSayisi,_28_PaketAdet,_29_PaketSayisi, _30_SKSaati,
   _31_Saat, _32_Tarih ,_33_SkTarihi ,_34_EAN13, _35_Rezerve, _36_Brut, _37_Dara, _38_Net, _39_Toplam, _40_ParcaSayisi,
   _41_SiraNo, _42_Birim, _43_HesFiyat, _44_Adres1, _45_Adres2, _46_Adres3, _47_EAN128Tatih, _48_EAN128Net, _49_GToplam, _50};

String _varStr[] ={ "urun", "ukodu123n","orginn","lotn","fisn","adresn","grupn","fiyan","Opratorn","text1n",
                      "acik1n", "acik2n","acik3n","acik4n","acik5n","acik6n","acik7n","acik8n","acik9n","acik10n",
                      "text2n", "text3n","text4n","text5n","kasan","paletn","ksayisin","psayisin","padetn","paketpayisin",
                      "sksaatn","saatn", "tarihn","sktarihn","123456789012","rezerve", "brutn","daran","netn","toplamn","parcasayisin",
                      "siranon","birim" };

//String _PluList2[] ={"Karpuz","Domates","Soğan","Salatalik", "Üzüm","Patattes"};
String _PluList[20];// ={"1","2","3","4","5","6","7","8","9","10"};
String _PluCodeList[20];//={"1","2","3","4","5","6","7","8","9","10"};
String _LabelList[20];
File file;

class littleFS_Read
{
private:
    /* data */
public:
//    void setupLittleFS();    
    void Fs_ReadLabel(String);
    void Fs_ReadPlu(int);
    void LittleFS_Erase(String);
//    void LittleFS_Write(String);
    void FileCreate(String  ,String);
    void LittleFS_OpenDir(String);
    //void Fs_IniRead();
    String Fs_IniRead(String);
    String Fs_IniRead(const char* ,const char* );
    bool Fs_IniWrite(const char* ,const char* ,const char* );

    //const char _Menu_Start[]; 

};









String readLine()
{
String received = "";
char ch;
  while (file.available()){
    ch = file.read();
    if (ch == '\n'){
      return String(received);
      }
    else{    
    //);
    received += ch;
    }
  }
return "";
}

void littleFS_Read::LittleFS_Erase(String fileName)
  {
  LittleFS.remove(fileName);
  Serial.println(fileName + "dosyasi silindi..."); 
}

void littleFS_Read::LittleFS_OpenDir(String DirName)
  {
    Dir root = LittleFS.openDir(DirName);
    while (root.next())
    {
      File file = root.openFile("r");
    Serial.print("  FILE: ");
    Serial.print(root.fileName());
    Serial.print("  SIZE: ");
    Serial.print(file.size());
    time_t t = file.getLastWrite();
    struct tm * tmstruct = localtime(&t);
    file.close();
    Serial.printf("  LAST WRITE: %d-%02d-%02d %02d:%02d:%02d\n", (tmstruct->tm_year) + 1900, (tmstruct->tm_mon) + 1, tmstruct->tm_mday, tmstruct->tm_hour, tmstruct->tm_min, tmstruct->tm_sec);
 
    }
    

}

// void littleFS_Read::LittleFS_Write(String fileName){
//   if(LittleFS.begin()){
//     Serial.println("Dosya islemleri oluşturuluyor");
//   }
//   else {
//     Serial.println("Dosya yazma islemi Hatali");
//   }
//   file = LittleFS.open(fileName ,"a");
//   if(file){
//     Serial.println("Dosya yazma islemi başlandi");
//     }
//     else{
//       Serial.println("Dosya acilirken hata olustu");
//     }
//   file.println("Bu satiri ben ekledim oldumu açaba iiiğğüüööçç");
//   Serial.println("Bu satiri ben ekledim oldumu açaba iiiğğüüööçç");
//   file.close();
// }












//https://lezzetlirobottarifleri.com/arduino-ile-sd-kart-kullanimi/
//https://www.donskytech.com/esp8266-webserver-using-littlefs/
void littleFS_Read::Fs_ReadLabel(String filename)
{
int i = 0;
int str_S = 0;
//file.seek(79);
String okuma ="";
//String buf_okuma="";
    LittleFS.begin();
    file = LittleFS.open(filename, "r");
  if(!file){
    Serial.println("Dosya okumada hata var.");
    return;
  }
  Serial.print("Yollanan dosya adi: ");
  Serial.println(filename);



bool Picture = false;
// bool Rem_Read = false;
if(labelLogoChange){      // Label değişti logoyu güncelle
  while(file.available()){

    //Serial.write(file.read());
    okuma += (char)file.read();
      if(okuma.endsWith("DOWNLOAD"))
      {
        Picture =true;
        labelLogoChange = false;
        okuma ="DOWNLOAD";
     }
  if(Picture){
    okuma += (char)file.read();
  }
  }
    if(Picture){
    Serial.print(okuma);
    Serial2.print(okuma); 
    delay(500);
  }

}


file = LittleFS.open(filename, "r");
okuma = "";
int iStr =0;
while (file.available()){
  //okunan[i] = file.read();
  okuma += (char)file.read();
  i++;
  if(okuma.endsWith("DOWNLOAD"))  {
    //okuma.remove((i-8), 8  );
    okuma.replace("DOWNLOAD","");
     break;
     }
  else if(okuma.endsWith("REM DA-")){
      iStr =i;
     }
  else if(okuma.endsWith("REM 1E-")){
      okuma.remove( iStr, i);  
     }
}
    
    okuma.replace("REM DA--------------\r\n","");
    char crap[80];
    for (size_t i = 0; i < 39; i++)
    {
      sprintf(crap , "@%03d" ,i);
      okuma.replace(crap ,"\"" + _varStr[i] + "\"");
    }
Serial.print(okuma);
Serial2.print(okuma);  
Serial.println();


    file.close();
    LittleFS.end();
    Serial.println("PRINT 1,1");
    Serial.print("Dosya boyutuBuffer : ");
    Serial.println(i);
    Serial.print("Satir Baslangic : ");
    Serial.println(str_S);
    Serial2.println("PRINT 1,1"); 
    Serial.println("########################");
    Serial.println();

}

void PluPrint(){
Serial.println("Dizi oku");
for (int i = 0; i < 10; i++)
{
  Serial.println(_PluList[i]);
}
Serial.println();
}


void littleFS_Read::Fs_ReadPlu(int pluNo)
{
  labelLogoChange = true; // Label değişti logoyu güncelle
  String PluRd ;//="";
  LittleFS.begin();
  File file_plu = LittleFS.open("plu.txt", "r");
  if(!file_plu){
    Serial.println("plu.txt Not found");
    return;
  }
 
  // file_plu.seek(100);
  int i=0;
     /*
00001~12 AY UV (UV+EVA~001~000000011111~11111     ~11111~00011111~00011111~00~01~0000~12 AY UV (UV+EVA+AB)                            ~                                                ~                                                ~                                                ~                                                ~                                                ~                                                ~                                                ~                                                ~                                                ~0uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu0~
*/

  while(file_plu.available()){
    PluRd = file_plu.readStringUntil('\n');
    //  dataSplit(PluRd,'~');
    //   pluName(i);
    //   pluCode(i);
    _PluList[i] = PluRd.substring(6, 22);
    _PluCodeList[i] = PluRd.substring(27, 39);
    _LabelList[i] = PluRd.substring(78, 80);
    if(i == pluNo)    {
   _varStr[_0_PluName] = _PluList[i] ;//PluRd.substring(6, 22);
   _varStr[_1_PluCode] = _PluCodeList[i];//PluRd.substring(27, 39);
   _varStr[_2_Origine] = PluRd.substring(40, 50);
   LabNo = PluRd.substring(78, 80).toInt();
    }
  i++;
  yield();
  }

  file_plu.close();
  LittleFS.end();
  Serial.println("PLU Read end");
  PluPrint();
  //sprintf(crap , "@%03d" ,i);
  
  char crap[80];
  sprintf(crap , "%03d" ,LabNo);
  labelName = "RP80VI_" ;
  labelName += crap;
  labelName += ".bin";
  Serial.println(labelName);
}






File file_ini ;
void littleFS_Read::FileCreate(String StrCreate ,String fileName){
   if(!LittleFS.begin()){
     Serial.println("File sistem Problems");

   }
file_ini = LittleFS.open(fileName, "w");
// if(!file_ini)
//   Serial.println("Dosya Acilamadi.........");
  file_ini.print(StrCreate);

 file_ini.close();
}


bool Tab = false;

String littleFS_Read::Fs_IniRead(String FileName){
    LittleFS.begin();
    String str_Iniread ;
      file_ini = LittleFS.open(FileName, "r");
  if(!file_ini){
    Serial.println("net.ini Not found");
    return "net.ini Not found";
  }
  while(file_ini.available()){
   str_Iniread += (char)file_ini.read();
  }
  file_ini.close();
  return str_Iniread;
}

String littleFS_Read::Fs_IniRead(const char* Tabstr ,const char* subTab){
     if(!LittleFS.begin()){
     Serial.println("File sistem Problems");
   }
  String str_Iniread ;
  String SendStr;
  file_ini = LittleFS.open("/net.ini", "r");
  if(!file_ini){
    Serial.println("net.ini Not found");
    FileCreate(_Menu_Start, "/net.ini");
    return "net.ini Not found";
  }
  while(file_ini.available()){
   str_Iniread += (char)file_ini.read();
 
if(str_Iniread.endsWith(Tabstr))  { 
  Tab = true;
    }
    if(str_Iniread.endsWith(subTab) && Tab)  {
      SendStr =file_ini.readStringUntil('\n');
      //Serial.println(SendStr);
      Tab = false;
     }
  yield();
  }


  file_ini.close();
  return SendStr;
}


bool littleFS_Read::Fs_IniWrite(const char* Tabstr ,const char* subTab ,const char* value){
     if(!LittleFS.begin()){
     Serial.println("File sistem Problems");
   }
  String str_Iniread = Fs_IniRead("/net.ini");
  String str_subTab = subTab ;
  str_subTab +=  Fs_IniRead(Tabstr, subTab); //"192.168.31.111";
  String str_value= subTab;
  str_value += value;
  str_Iniread.replace(str_subTab, str_value);
  delay(100);
  FileCreate(str_Iniread,"/net.ini");
  return true;
}


#endif
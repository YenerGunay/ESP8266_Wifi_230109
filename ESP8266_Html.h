/*
Page	Function
/	Menu page.
/wifi	Show WiFi scan results and enter WiFi configuration.(/0wifi noscan)
/wifisave	Save WiFi configuration information and configure device. Needs variables supplied.
http://10.10.101.254/wifi?#p

SSID
Xiaomi_Pasam

Password
aabbccddf2
 Show Password

Static IP
192.168.31.200
 Static gateway
255.255.255.0
 Subnet
192.168.31.1
 Static DNS
8.8.8.8



/param	Parameter page
/info	Information page
/u	OTA Update
/close	Close the captiveportal popup, config portal will remain active
/exit	Exit Config portal, config portal will close
/restart	Reboot the device
/erase	Erase WiFi configuration and reboot device. Device will not reconnect to a network until new WiFi configuration data is entered.
Github https://github.com/tzapu/WiFiManager.
*/


#ifndef _Esp8266_Html
#define _Esp8266_Html

#include <ESP8266WiFi.h>
// #include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>  // Built-in
#include <ESP8266mDNS.h>
#include <WiFiManager.h>  
#include "WiFiClient.h"



 #if defined(AtoUpdate)
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266httpUpdate.h>
#endif

//  #if defined(APMode1)
  #include <ESP8266HTTPUpdateServer.h>
// //https://www.youtube.com/watch?v=iDKVbS1Yb2w
// #include <ESP8266mDNS.h>
// //ağ bilgilerinizi girin
// #ifndef STASSID
// #define STASSID "Xiaomi_Pasam"
// #define STAPSK  "aabbccddf2"
// //#define HOSTdf  "esp8266-webupdate"
// #endif


 const char* host = "Densi_Server_Ap";
// const char* ssid = STASSID;
// const char* password = STAPSK;
// #endif




#include "littleFS_Read.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "CSS.h"
#include "Scale.h"
#include "myShiftDisplay.h"
//#include "FS.h"

myShiftDisplay mydisplay;

struct Settings {
    float f;
    int i;
    char s[20];
    uint32_t ip;
} sett;

littleFS_Read ltFs;
Scale scale;


ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

// Variable to store the HTTP request
String header;

String NetwMode ="0"; // WIFI_STA - WIFI_AP
String NetwSsid ="Densi_AP_Vinc1";
String NetwPasw ="12345678";
String NetwIpNa ="10.10.100.254";
String NetwMask ="255.255.255.0";

String SSIDName ="DENSi_SSID";
String SSIDPasw ="12345678";
String SSIDTcpi ="10.10.100.254";
String SSIDGetw ="10.10.100.1";
String SSIDMask ="255.255.255.0";


//const char* 
bool PortOnOf = 1;
String ServerIp = "10.10.100.254";
int ServerPo = 8899;


// Assign output variables to GPIO pins
class ESP8266_Html
{
private:
public:
  void AP_Mode();
  void setupHTML();
  void ESP8266_Htmlweb();
  static void ESP8266_FactoryMod();
};




void SendHTML_Content(){
  server.sendContent(webpage);
  webpage = "";
}
void SendHTML_Stop(){
  server.sendContent("");
  server.client().stop(); // Stop is needed because no content length was sent
}





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void SendHTML_Header(){
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate"); 
  server.sendHeader("Pragma", "no-cache"); 
  server.sendHeader("Expires", "-1"); 
  server.setContentLength(CONTENT_LENGTH_UNKNOWN); 
  server.send(200, "text/html", ""); // Empty content inhibits Content-length header so we have to close the socket ourselves. 
  append_page_header();
  SendHTML_Content();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void SelectInput(String heading1, String command, String arg_calling_name){
  SendHTML_Header();
  webpage += F("<h3>"); webpage += heading1 + "</h3>"; 
  webpage += F("<FORM action='/"); webpage += command + "' method='post'>"; // Must match the calling argument e.g. '/chart' calls '/chart' after selection but with arguments!
  webpage += F("<input type='text' name='"); webpage += arg_calling_name; webpage += F("' value=''><br>");
  webpage += F("<type='submit' name='"); webpage += arg_calling_name; webpage += F("' value=''><br>");
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ReportFileNotPresent(String target){
  SendHTML_Header();
  webpage += F("<h3>File does not exist</h3>"); 
  webpage += F("<a href='/"); 
 // webpage += target + "'>[Back]</a><br><br>";
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void ReportSDNotPresent(){
//   SendHTML_Header();
//   webpage += F("<h3>No SD Card present</h3>"); 
//   webpage += F("<a href='/'>[Back]</a><br><br>");
//   append_page_footer();
//   SendHTML_Content();
//   SendHTML_Stop();
// }
//String Argument_name , client_Respons;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void HomePage(){
  SendHTML_Header();
 // String IPaddress = WiFi.localIP().toString();
 #if defined(Lcd_7Sehment)    
      webpage += F("<h2>External 7 Seg. LCD</h2>");  
 #endif

  webpage += F("<h3>HOME PAGE</h3>");  
#if defined(FULL)    
  webpage += F("<a href='/download'><button>Download</button></a>");
  webpage += F("<a href='/upload'><button>Upload</button></a>");
  webpage += F("<a href='/dir'><button>Dir</button></a>");
  webpage += F("<a href='/label'><button>Label</button></a>");
  webpage += F("<a href='/plu'><button>Plu</button></a>");
#endif  
  webpage += F("<a href='/wifisetting'><button>Wifi Setting</button></a>");
  webpage += F("<a href='/parametre'><button>Parametre</button></a>");
  webpage += F("<a href='/update'><button>Fireware</button></a>");
  webpage += F("<a href='/ssidscan'><button>SSID Scan</button></a>");
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop(); // Stop is needed because no content length was sent
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Reset(){
  HomePage();
  ESP.reset();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void File_Upload(){
  append_page_header();
  webpage += F("<h3>Select File to Upload</h3>"); 
  webpage += F("<FORM action='/fupload' method='post' enctype='multipart/form-data'>");
  webpage += F("<input class='buttons' style='width:50%' type='file' name='fupload' id = 'fupload' value=''><br>");
  webpage += F("<br><button class='buttons' style='width:10%' type='submit'>Upload File</button><br>");
  //webpage += F("<a href='/'>[Back]</a><br><br>");
  append_page_footer();
  server.send(200, "text/html",webpage);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void SD_file_download(String filename){
  SD_present = true;
  LittleFS.begin();
  //filename ="RP80VI_006.bin";
  Serial.println(SD_present);
  if (SD_present) { 
    File download = LittleFS.open(filename ,"r"); //SD.open("/"+filename);
    Serial.println("Dosya Adi");
    Serial.println(filename);
   Serial.println("Dosya Sonu.");
    if (download) {
      server.sendHeader("Content-Type", "text/text");
      server.sendHeader("Content-Disposition", "attachment; filename="+filename);
      server.sendHeader("Connection", "close");
      server.streamFile(download, "application/octet-stream");
      download.close();
    } else ReportFileNotPresent("download"); 
  } 
  //else ReportSDNotPresent();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void File_Download(){ // This gets called twice, the first pass selects the input, the second pass then processes the command line arguments
  if (server.args() > 0 ) { // Arguments were received
    if (server.hasArg("download")) 
      SD_file_download(server.arg(0));
  }
  else SelectInput("Enter filename to download","download","download");
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ReportCouldNotCreateFile(String target){
  SendHTML_Header();
  webpage += F("<h3>Could Not Create Uploaded File (write-protected?)</h3>"); 
  webpage += F("<a href='/"); webpage += target ; webpage+=F("'>[Back]</a><br><br>");
  append_page_footer();
  SendHTML_Content();
  SendHTML_Stop();
}

void handleFileUpload(){ // upload a new file to the Filing system
  HTTPUpload& uploadfile = server.upload(); // See https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer/srcv
                                            // For further information on 'status' structure, there are other reasons such as a failed transfer that could be used
  if(uploadfile.status == UPLOAD_FILE_START)
  {
    String filename = uploadfile.filename;
    if(!filename.startsWith("/")) 
      filename = "/"+filename;
    Serial.print("Upload File Name: "); 
    Serial.println(filename);
    // SD.remove(filename);                         // Remove a previous version, otherwise data is appended the file again
    // UploadFile = SD.open(filename, FILE_WRITE);  // Open the file for writing in SPIFFS (create it, if doesn't exist)

      if(LittleFS.begin()){
    Serial.println("Dosya islemleri oluşturuluyor");
  }
  else {
    Serial.println("Dosya yazma islemi Hatali");
  }
  file = LittleFS.open(filename ,"w");
//  file.write(uploadfile.buf, uploadfile.currentSize);
    filename = String();
  }
  else if (uploadfile.status == UPLOAD_FILE_WRITE)
  {
    if(file) file.write(uploadfile.buf, uploadfile.currentSize); // Write the received bytes to the file
  } 
  else if (uploadfile.status == UPLOAD_FILE_END)
  {
    if(file)          // If the file was successfully created
    {                                    
      file.close();   // Close the file again
      Serial.print("Upload Size: "); Serial.println(uploadfile.totalSize);
      webpage = "";
      append_page_header();
      webpage += F("<h3>File was successfully uploaded</h3>"); 
      webpage += F("<h2>Uploaded File Name: "); 
      webpage += uploadfile.filename+"</h2>";
      //webpage += F("<h2>File Size: "); webpage += file_size(uploadfile.totalSize) + "</h2><br>"; 
      //webpage += F("<a href='/'>[Back]</a><br><br>");
      append_page_footer();
      server.send(200,"text/html",webpage);
    } 
    else
    {
      ReportCouldNotCreateFile("upload");
    }
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Directory() {
  LittleFS.begin();
  Dir root = LittleFS.openDir("/");//DirName);
  append_page_header();
  webpage += F("<h3>All Upload Files</h3>");
  webpage += F("<table><tr><th>File Name</th><th>File Size</th></tr>");
   File file = root.openFile("r");
   while (root.next())
    {
      webpage += "<tr><td><a href='" + root.fileName() +"'>"+ root.fileName() + "</a><td>" + root.fileSize() + "</td></tr>";
      file.close();
    }
      webpage += F("</table></form><p> Mesaj olaçak</p>");
      append_page_footer();
      server.send(200, "text/html",webpage);
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Label(){
  LittleFS.begin();
  Dir root = LittleFS.openDir("/");//DirName);
  append_page_header();
  webpage += F("<h3>Label Select</h3>");
  webpage += F("<table><tr><th>File Name</th><th>File Size</th><th>Buton</th></tr>");
   File file = root.openFile("r");
   while (root.next())
    {
      if(root.fileName().startsWith("RP80VI_") > 0 )
       {
        webpage += F("<tr><td><form action='label' method='POST'> <input  type='hidden' name='label' value='"); 
        webpage += root.fileName() + "'>" + root.fileName() + "</td><td>" + root.fileSize();
        webpage += F("</td><td><input type='submit' value='Label Select' /></form> </td></tr>");
        file.close();
      }
    }
  webpage += F("</table><p> Mesaj olaçak</p>");
       append_page_footer();
      server.send(200, "text/html",webpage);

     if (server.hasArg("label")== false){ //Check if body received
            server.send(200, "text/html", "Body not received");
            return;
      }
      Serial.println(server.arg("label")); 
      labelName = server.arg("label");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Plu(){
  append_page_header();
  webpage += "<h3>PLU SELECT</h3>";
  webpage += "<table><tr><th>PLU Name</th><th>PLU Code</th><th>Buton</th></tr>";

  int eleman =(sizeof(_PluList)/sizeof(_PluList[0]));
  for (int i = 0; i < eleman; i++)  {
    //String no = i;
    webpage += "<tr><td><form action='plu' method='POST'> <input  type='hidden' name='plu' value='"
            + String(i) + "'>" + _PluList[i] + "</td><td>" +  _PluCodeList[i] //"PLUcode123" //
            + "</td><td><input type='submit' value='Label Select' /></form> </td></tr>";
    //webpage += "<option value='" + _PluList[i] + "'>" + _PluList[i] + "</option>";
  }
  webpage += "</table><p> Mesaj olaçak</p>";
       append_page_footer();
      server.send(200, "text/html",webpage);

     if (server.hasArg("plu")== false){ //Check if body received
            server.send(200, "text/html", "Body not received");
            return;
      }
      PluNo = server.arg("plu").toInt();
      //_varStr[_0_PluName] = server.arg("plu");
      //Serial.println(_varStr[_0_PluName]); 
      _varStr[_0_PluName] = _PluList[PluNo];
      Serial.println(_varStr[_0_PluName]); 
      ltFs.Fs_ReadPlu(PluNo);
}


void UpdateFirmware(){
  append_page_header();
  webpage += F("<h3>Select File to Firmware</h3>"); 
  webpage += F("<FORM action='/update2' method='post' enctype='multipart/form-data'>");
  webpage += F("<input class='buttons' style='width:80%' type='file' accept='.bin,.bin.gz' name='update2'><br>");
  webpage += F("<br><button class='buttons' style='width:10%' type='submit'>Update File</button><br>");
  append_page_footer();
  server.send(200, "text/html",webpage);
}



#if defined(TarihSaat)
#include "RtcTimer.h"
RtcTimer rtc2;
#endif

bool AP_WifiWork_Sel = false;

void WiffiSetting(){
  // SendHTML_Header();
    if(server.args() > 0 ){
    for (uint8_t i = 0; i < server.args(); i++)
    {
       if(server.argName(i) =="wifisetting"){
        Serial.print(i);
        Serial.print("-");
        Serial.println(server.arg(i));
      }
    }

    NetwMode = server.arg(0);
    NetwSsid = server.arg(1);
    NetwPasw = server.arg(2);
    NetwIpNa = server.arg(3);
    NetwMask = server.arg(4);

    SSIDName = server.arg(5);
    SSIDPasw = server.arg(6);
    SSIDTcpi = server.arg(7);
    SSIDGetw = server.arg(8);
    SSIDMask = server.arg(9);
    PortOnOf = server.arg(10) == "0" ? false :true;
    ServerIp = server.arg(11);
    ServerPo = server.arg(12).toInt();

    // Serial.println(PortOnOf);
    // Serial.println(ServerIp);
    // Serial.println(ServerPo);
     ltFs_Rw.Fs_IniWrite("[Ssid]","WifiMode=", server.arg(0).c_str());
     ltFs_Rw.Fs_IniWrite("[Ssid]","NetwSsid=", server.arg(1).c_str());
     ltFs_Rw.Fs_IniWrite("[Ssid]","NetwPasw=", server.arg(2).c_str());
     ltFs_Rw.Fs_IniWrite("[Ssid]","NetwIpNa=", server.arg(3).c_str());
     ltFs_Rw.Fs_IniWrite("[Ssid]","NetwMask=", server.arg(4).c_str());

      ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDName=", server.arg(5).c_str());
      ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDPasw=", server.arg(6).c_str());
      ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDTcpi=", server.arg(7).c_str());
      ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDMask=", server.arg(8).c_str());
      ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDGetw=", server.arg(9).c_str());
      ltFs_Rw.Fs_IniWrite("[Ssid]","ServerOn=", server.arg(10).c_str());
      ltFs_Rw.Fs_IniWrite("[Ssid]","ServerIp=", ServerIp.c_str());
      ltFs_Rw.Fs_IniWrite("[Ssid]","ServerPo=", server.arg(12).c_str());// (const char*)ServerPo);
       //server.send(200, "text/html",webpage);
  }
  append_page_header();
  webpage += F("<h1>Wifi Setting</h1>"); 
  webpage += F("<h2>Wifi Mode Sellect.....'"); 
  webpage += (String)WiFi.RSSI();
  webpage += F("'</h2><form action='/wifisetting' method='POST' enctype='multipart/form-data' style='text-align:left;'>");

  webpage += F("<select name='wifisetting' >");
  webpage += F("<option value='0' selected>WIFI_AP_STA</option>");
  webpage += F("<option value='1'>WIFI_AP</option>");
  webpage += F("<option value='2'>WIFI_STA</option>");
  webpage += F("</select>--Work Mode Select <br>");
// String NetwMode ="0"; // WIFI_STA - WIFI_AP
// String NetwSsid ="Densi_AP_Vinc1";
// String NetwPasw ="12345678";
// String NetwIpNa ="10.10.100.254";
// String NetwMask ="255.255.255.0";
  //webpage += F("<input type='text' name='wifisetting' value='"); webpage +=F("Ap_WifiWork_Mod"); webpage += F("'>--Wifi Work Mode<br>");
  webpage += F("<input type='text' name='wifisetting' value='")+ NetwSsid + F("'>--Network (SSID)<br>");
  webpage += F("<input type='text' name='wifisetting' value='")+ NetwPasw + F("'>--Password<br>");
  webpage += F("<input type='text' name='wifisetting' value='")+ NetwIpNa + F("'>--Ip Adress<br>");
  webpage += F("<input type='text' name='wifisetting' value='")+ NetwMask + F("'>--Mask<br>");
  webpage += F("<h2>STA Mode</h2>"); 
  webpage += F("<input type='text' name='wifisetting' value='"); webpage +=SSIDName; webpage += F("'>--Network Name (SSID)<br>");
  webpage += F("<input type='text' name='wifisetting' value='"); webpage +=SSIDPasw; webpage += F("'>--STA Password<br>");
  webpage += F("<input type='text' name='wifisetting' value='"); webpage +=SSIDTcpi; webpage += F("'>--IP adress<br>");
  webpage += F("<input type='text' name='wifisetting' value='"); webpage +=SSIDMask; webpage += F("'>--Mask<br>");
  webpage += F("<input type='text' name='wifisetting' value='"); webpage +=SSIDGetw; webpage += F("'>--Gate<br>");
  webpage += F("<h2>Socket Connecti Setting</h2>"); 
  webpage += F("<input type='text' name='wifisetting' value='"); webpage +=(String)PortOnOf; webpage += F("'>--Port On Off<br>");
  webpage += F("<input type='text' name='wifisetting' value='"); webpage +=(String)ServerIp; webpage += F("'>--Server IP Adress<br>");
  webpage += F("<input type='text' name='wifisetting' value='"); webpage +=(String)ServerPo; webpage += F("'>--Port<br>");
  webpage += F("<input type='submit' value='Wifi Setting Seve'>");
  webpage += F("</form><br>");
  append_page_footer();

  server.send(200, "text/html",webpage);
}











void SsidScan(){
  // SendHTML_Header();
  int Tnetwork = WiFi.scanNetworks();
  append_page_header();

  
  webpage += F("<h1>Wifi Setting</h1>"); 
  webpage += F("<h2>Wifi Mode Sellect.....'"); 
  webpage += (String)WiFi.RSSI();

  webpage += F("<h2>SSID SCAN 2</h2>");
  for (size_t j = 0; j < Tnetwork; j++)
  {
    int rss =WiFi.RSSI(j);
    webpage +="<div style='text-align:left; '> <a href='#p' onclick='c(this)' data-ssid='" + WiFi.SSID(j) +"'>"+ WiFi.SSID(j) +"</a>";
    webpage +="<div role='img' aria-label='"+ webpage += (String)rss + "%' title='" + (String)rss +"%' class='q q" 
    + (int)(((-100)-rss) / 18 ) + " "+ ((WiFi.encryptionType(j) == ENC_TYPE_NONE)?" ":"l" ) +" '>";
    webpage +="</div> <div class='q h'>"+ webpage += (String)rss +"%</div></div>";
    //webpage +="<div>";
  } 

 //webpage +=F("<form method='POST' action='wifisave'>");
  //webpage += F("'<form action='/wifisetting' method='POST' enctype='multipart/form-data' style='text-align:left;'>");
  webpage += F("<form action='wifisave' method='POST' style='text-align:left;'>");

//  webpage +=F("<label for='s'>SSID</label>");
//  webpage +=F("<input id='s' name='s' maxlength='32' autocorrect='off' autocapitalize='none' placeholder='Densi'><br>");
//  webpage +=F("<label for='p'>Password</label>");
//  webpage +=F("<input id='p' name='p' maxlength='64' type='password' placeholder=''>");
 //webpage +=F("<input type='checkbox' onclick='f()'> Show Password <hr><br>");

//  webpage +=F("<label for='ip'>Static IP</label><br>");
//  webpage +=F("<input id='ip' name='ip' maxlength='15' value='10.10.100.3'>");
//  webpage +=F("<label for='gw'>Static gateway</label><br>");
//  webpage +=F("<input id='gw' name='gw' maxlength='15' value='10.10.100.254'>");
//  webpage +=F("<label for='sn'>Subnet</label> <br>");
//  webpage +=F("<input id='sn' name='sn' maxlength='15' value='255.255.255.0'>");
//  webpage +=F("<label for='dns'>Static DNS</label><br><input id='dns' name='dns' maxlength='152 value='8.8.8.8'>");
 // webpage +=F("<br><br><br><button type='submit'>Save</button> </form>");




  // webpage += F("<h2>SSID</h2>"); 
  //webpage += F("<input type='text' id='s' maxlength='32' autocorrect='off' autocapitalize='none' name='wifisetting' value='"); 
  webpage +=F("<label for='s'>SSID</label>");
  webpage += F("<input id='s' maxlength='32' autocorrect='off' autocapitalize='none' name='s'  placeholder='"); 
  webpage += SSIDName; 
  webpage += F("'><br>");
  //webpage += F("'>--Network Name (SSID)<br>");

 webpage +=F("<label for='p'>Password</label>");
 webpage +=F("<input id='p' name='p' maxlength='64' type='password' placeholder='"); webpage +=SSIDPasw +"'>";
 webpage +=F("<input type='checkbox' onclick='f()'> Show Password <hr><br>");


  //webpage += F("<input type='text' for='p' name='wifisetting' value='"); webpage +=SSIDPasw; webpage += F("'>--STA Password<br>");
  webpage += F("<input type='text' name='wifisave' value='"); webpage +=SSIDTcpi; webpage += F("'>--IP adress<br>");
  webpage += F("<input type='text' name='wifisave' value='"); webpage +=SSIDMask; webpage += F("'>--Mask<br>");
  webpage += F("<input type='text' name='wifisave' value='"); webpage +=SSIDGetw; webpage += F("'>--Gate<br>");

  webpage += F("<input type='submit' value='Wifi Setting Seve'>");
  webpage += F("</form><br>");


  //    webpage += F("<h2>SSID SCAN </h2>");

  // webpage += F("<select name='ssidSelect' >");
  // for (size_t i = 0; i < Tnetwork; i++)
  // {
  //   webpage += "<option value='" + WiFi.SSID(i) + "' " + (SSIDName == WiFi.SSID(i) ? "selected> " : "> ") +
  // (String)i+ " " + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ")"+((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*" ) + "</option>";
  // }
  // webpage += F("</select>--SSID Select <br>");





//  webpage += F("<ul>");
//   for (size_t i = 0; i < Tnetwork; i++)
//   {
//     webpage += F("<li>");
//     webpage += i +1 ;
//     webpage += WiFi.SSID(i);
//     webpage += " (";
//     webpage += WiFi.RSSI(i);
//     webpage += ")";
//     webpage += (WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*";
//     webpage += F("</li>");
//     /* code */
//   }
//    webpage += F("</ul>");




  append_page_footer();



  server.send(200, "text/html",webpage);
}




















void Parametre_Wifi(){

//NetwMode =ltFs.Fs_IniRead("[ApMode]","NetwSsid=").c_str();
NetwSsid =ltFs.Fs_IniRead("[ApMode]","NetwSsid=").c_str();
NetwPasw =ltFs.Fs_IniRead("[ApMode]","NetwPasw=").c_str();
NetwIpNa =ltFs.Fs_IniRead("[ApMode]","NetwIpNa=").c_str();
NetwMask =ltFs.Fs_IniRead("[ApMode]","NetwMask=").c_str();

  SSIDName = ltFs.Fs_IniRead("[Ssid]","SSIDName=").c_str();
  SSIDPasw = ltFs.Fs_IniRead("[Ssid]","SSIDPasw=").c_str();
  SSIDTcpi = ltFs.Fs_IniRead("[Ssid]","SSIDTcpi=").c_str();
  SSIDGetw = ltFs.Fs_IniRead("[Ssid]","SSIDGetw=").c_str();
  SSIDMask = ltFs.Fs_IniRead("[Ssid]","SSIDMask=").c_str();

  PortOnOf = ltFs.Fs_IniRead("[Ssid]","ServerOn=").toInt();
	ServerIp = ltFs.Fs_IniRead("[Ssid]","ServerIp=").c_str();// (const char*)ltFs.Fs_IniRead("[Ssid]","ServerIp=");	
	ServerPo = ltFs.Fs_IniRead("[Ssid]","ServerPo=").toInt();
  
  Serial.println();
  Serial.print(F("Host : "));  Serial.println(ServerIp);
  Serial.print(F("Port : "));  Serial.println(ServerPo);
  //Serial.print(F("SSIDTcpi : "));  Serial.println(SSIDTcpi);

}

void Parametre_Scale(){
String Textmod = "value='No";
#if defined(TarihSaat)
  char time_format[] = "DD/MM/YYYY hh:mm:ss";
  String strDate = rtc2.datetim().toString(time_format);
  //webpage += F("<form action='http://192.168.31.86' method='POST'>"); 
  webpage += F("<form method='POST'  style='text-align:left;'>");
  webpage += F("<h3>PARAMETRE</h3>"); 
  webpage += F("<h2>Date Format: 01/31/2000 22:12:00</h2>"); 
  webpage += "<input type='text' name='Date_Time' value='" + strDate +"'><input type='submit' value='Date Time'>";
  webpage += F("</form><br>");
#endif  
  if(server.args() > 0 ){
    for (uint8_t i = 0; i < server.args(); i++)
    {
#if defined(TarihSaat)      
      if(server.argName(i) =="Date_Time"){
        Serial.println(server.arg(i));
        rtc2.DateTimeSet(server.arg(i));
      }
#endif      
       if(server.argName(i) =="GenarelFormat"){
        Serial.print(i);
        Serial.print("-");
        Serial.println(server.arg(i));        
      }
    }
      Par_TextSize = server.arg(0).toInt();
      Par_Location = server.arg(1).toInt();
      Par_WghtStrt = server.arg(2).toInt();
      Par_WghtStop = server.arg(3).toInt();
      Par_TareStrt = server.arg(4).toInt();
      Par_TareStop = server.arg(5).toInt();
      Par_UnitStrt = server.arg(6).toInt();
      Par_EndChar =  server.arg(7).c_str();

      SerailBouderate1 = server.arg(8).toInt();
      Par_TexMode =  server.arg(9) == "No" ? false : true;
      ReadChar = Par_WghtStop - Par_WghtStrt;

      ltFs_Rw.Fs_IniWrite("[Parametre]","Size=", server.arg(0).c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","Location=", server.arg(1).c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","WeightStart=", server.arg(2).c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","WeightStop=", server.arg(3).c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","TareStart=", server.arg(4).c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","TareStop=", server.arg(5).c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","UnitStart=", server.arg(6).c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","EndChar=", server.arg(7).c_str());
      
      ltFs_Rw.Fs_IniWrite("[Modul]","BaudeRate=", server.arg(8).c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","TextMode=", server.arg(9).c_str());

  }

        if(Par_TexMode){
            Textmod =" value='Yes' checked"; 
        }
        else{
            Textmod = " value='No'"; 
        }
     
     String select = "select";
  append_page_header();
  webpage += F("<h2>General Format.....'"); 
  webpage += Gosterge_html ; 
  webpage += F("'</h2><form method='POST'  style='text-align:left;'>");
  webpage += F("<input type='text' name='GenarelFormat' value='")+ (String)Par_TextSize + F("'>--Text Size<br>");
  webpage += F("<input type='text' name='GenarelFormat' value='")+ (String)Par_Location + F("'>--Location<br>");
  webpage += F("<input type='text' name='GenarelFormat' value='")+ (String)Par_WghtStrt + F("'>--Weight Start<br>");
  webpage += F("<input type='text' name='GenarelFormat' value='")+ (String)Par_WghtStop + F("'>--Weight Stop<br>");
  webpage += F("<input type='text' name='GenarelFormat' value='")+ (String)Par_TareStrt + F("'>--Tare Start<br>");
  webpage += F("<input type='text' name='GenarelFormat' value='")+ (String)Par_TareStop + F("'>--Tare Stop<br>");
  webpage += F("<input type='text' name='GenarelFormat' value='")+ (String)Par_UnitStrt + F("'>--Unit Start<br>");
  webpage += F("<input type='text' name='GenarelFormat' value='")+ (String)Par_EndChar + F("'>--End Char<br><br>");

  webpage += F("<select name='GenarelFormat' >");
  webpage += F("<option value='9600' "); webpage += SerailBouderate1 == 9600 ? "selected" : ""; webpage +=  F(">9600</option>");  // selected>9600</option>");
  webpage += F("<option value='19200' "); webpage += SerailBouderate1 == 19200 ? "selected" : ""; webpage +=  F(">19200</option>");
  webpage += F("<option value='38400' "); webpage += SerailBouderate1 == 38400 ? "selected" : ""; webpage +=  F(">38400</option>");
  webpage += F("<option value='57600' "); webpage += SerailBouderate1 == 57600 ? "selected" : ""; webpage +=  F(">57600</option>");
  webpage += F("<option value='115200' "); webpage += SerailBouderate1 == 115200 ? "selected" : ""; webpage +=  F(">115200</option>");
  webpage += F("</select>--Seri Port Bauderate <br><br>");

  webpage += F("<input type='checkbox' id='Revers' name='GenarelFormat'");  webpage += Textmod;  webpage +=F(">--Text Mode Revers<br><br>");
  webpage += F("<input type='hidden' id='Revers' name='GenarelFormat' value='No' name='GenarelFormat' >");

  webpage += F("<input type='submit' value='Genarel Format Save'>");
  webpage += F("</form><br>");
  append_page_footer();
  server.send(200, "text/html",webpage);
}






WiFiManager wifiManager;
void saveWifiCallback(){
  // // myWiFiManager->setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0)); 

    SSIDName =wifiManager.getWiFiSSID();
    SSIDPasw =wifiManager.getWiFiPass();

    SSIDTcpi = WiFi.localIP().toString();
    SSIDGetw = WiFi.gatewayIP().toString();
    //SSIDMask ="255.255.255.0";

    ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDName=", SSIDName.c_str());
    ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDPasw=", SSIDPasw.c_str());
    ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDTcpi=", SSIDTcpi.c_str());
    //ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDMask=", server.arg(8).c_str());
    ltFs_Rw.Fs_IniWrite("[Ssid]","SSIDGetw=", SSIDGetw.c_str());
}

String getParam(String name){
  //read parameter from server, for customhmtl input
  String value;
  if(wifiManager.server->hasArg(name)) {
    value = wifiManager.server->arg(name);
  }
  return value;
}

void saveParamCallback(){
   // Serial.println("PARAM customfieldid = " + getParam("customfieldid"));
    Serial.println("PARAM textSize = " + getParam("textSize"));
    Serial.println("PARAM Location = " + getParam("Location"));
    Serial.println("PARAM WeightStr = " + getParam("WeightStr"));
    Serial.println("PARAM WeightStp = " + getParam("WeightStp"));
    Serial.println("PARAM EndChar = " + getParam("EndChar"));
    Serial.println("PARAM Baudrate = " + getParam("Baudrate"));
    Serial.println("***************************************");
   // Serial.println(textSize);

      ltFs_Rw.Fs_IniWrite("[Parametre]","Location=", getParam("Location").c_str());;
      ltFs_Rw.Fs_IniWrite("[Parametre]","WeightStart=", getParam("WeightStr").c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","WeightStop=", getParam("WeightStp").c_str());
      ltFs_Rw.Fs_IniWrite("[Parametre]","EndChar=", getParam("EndChar").c_str());
      
      ltFs_Rw.Fs_IniWrite("[Modul]","BaudeRate=", getParam("Baudrate").c_str());

  // strcpy(textSize, custom_TextSize.getValue());
  // // strcpy(mqtt_port, custom_mqtt_port.getValue());
  // // strcpy(api_token, custom_api_token.getValue());
  // Serial.println("The values in the file are: ");
  // Serial.println("\tmqtt_server : " + String(textSize));
}



#if defined(ConfigCallBack)
void handleRoute(){
  Serial.println("[HTTP] handle route2222222222");
  wifiManager.server->send(200, "text/plain", "hello from user code");
}


void bindServerCallback(){
  wifiManager.server->on("/custom",handleRoute); // this is now crashing esp32 for some reason
    Serial.println("[CALLBACK] saveParamCallback bind 6666666666");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.gatewayIP());
  // wm.server->on("/info",handleRoute); // you can override wm!
}

void handlePreOtaUpdateCallback(){
  Update.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("CUSTOM Progress: %u%%\r", (progress / (total / 100)));
  });
}


void saveConfigCallback () {
  Serial.println("Should save config");
 // shouldSaveConfig = true;
}
#endif



void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  mydisplay.showDisplay7S("config", 500, Par_Point);
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}



void my_wifimanager(){

#if defined(ConfigCallBack)
  WiFiManagerParameter custom_html("<p style=\"color:pink;font-weight:Bold;\">This Is Custom HTML</p>"); // only custom html
  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", "", 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", "", 6);
  WiFiManagerParameter custom_token("api_token", "api token", "", 16);
  WiFiManagerParameter custom_tokenb("invalid token", "invalid token", "", 0); // id is invalid, cannot contain spaces
  WiFiManagerParameter custom_ipaddress("input_ip", "input IP", "", 15,"pattern='\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}'"); // custom input attrs (ip mask)
  WiFiManagerParameter custom_input_type("input_pwd", "input pass", "", 15,"type='password'"); // custom input attrs (ip mask)
  const char _customHtml_checkbox[] = "type=\"checkbox\""; 
  WiFiManagerParameter custom_checkbox("my_checkbox", "My Checkbox", "T", 2, _customHtml_checkbox,WFM_LABEL_AFTER);

  const char *bufferStr = R"(
  <!-- INPUT CHOICE -->
  <br/>
  <p>Select Choice</p>
  <input style='display: inline-block;' type='radio' id='choice1' name='program_selection' value='1'>
  <label for='choice1'>Choice1</label><br/>
  <input style='display: inline-block;' type='radio' id='choice2' name='program_selection' value='2'>
  <label for='choice2'>Choice2</label><br/>

  <!-- INPUT SELECT -->
  <br/>
  <label for='input_select'>Label for Input Select</label>
  <select name="input_select" id="input_select" class="button">
  <option value="0">Option 1</option>
  <option value="1" selected>Option 2</option>
  <option value="2">Option 3</option>
  <option value="3">Option 4</option>
  </select>
  )";

WiFiManagerParameter custom_html_inputs(bufferStr);
 IPAddress ip11,gw11,msk11;
 ip11.fromString("192.168.100.1");
 gw11.fromString("192.168.100.100");
 msk11.fromString("255.255.255.0");
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setWebServerCallback(bindServerCallback);
  wifiManager.setSaveConfigCallback(saveWifiCallback);
  wifiManager.setSaveParamsCallback(saveParamCallback);
  wifiManager.setPreOtaUpdateCallback(handlePreOtaUpdateCallback);
  wifiManager.setAPStaticIPConfig(ip11,gw11,msk11);

  // add all your parameters here
  wifiManager.addParameter(&custom_html);
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_token);
  wifiManager.addParameter(&custom_tokenb);
  wifiManager.addParameter(&custom_ipaddress);
  wifiManager.addParameter(&custom_checkbox);
  wifiManager.addParameter(&custom_input_type);
   wifiManager.addParameter(&custom_html_inputs);

  const char* headhtml = "<meta name='color-scheme' content='dark light'><style></style><script></script>";
  wifiManager.setCustomHeadElement(headhtml);

  const char* menuhtml = "<form action='/custom' method='get'><button>Custom</button></form><br/>\n";
  wifiManager.setCustomMenuHTML(menuhtml);

std::vector<const char *> menu = {"wifi","wifinoscan","info","param","custom","close","sep","erase","update","restart","exit"};



wifiManager.setMenu(menu);
#endif


  // const char* headhtml = "<link rel='icon' type='image/png' href='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAADQElEQVRoQ+2YjW0VQQyE7Q6gAkgFkAogFUAqgFQAVACpAKiAUAFQAaECQgWECggVGH1PPrRvn3dv9/YkFOksoUhhfzwz9ngvKrc89JbnLxuA/63gpsCmwCADWwkNEji8fVNgotDM7osI/x777x5l9F6JyB8R4eeVql4P0y8yNsjM7KGIPBORp558T04A+CwiH1UVUItiUQmZ2XMReSEiAFgjAPBeVS96D+sCYGaUx4cFbLfmhSpnqnrZuqEJgJnd8cQplVLciAgX//Cf0ToIeOB9wpmloLQAwpnVmAXgdf6pwjpJIz+XNoeZQQZlODV9vhc1Tuf6owrAk/8qIhFbJH7eI3eEzsvydQEICqBEkZwiALfF70HyHPpqScPV5HFjeFu476SkRA0AzOfy4hYwstj2ZkDgaphE7m6XqnoS7Q0BOPs/sw0kDROzjdXcCMFCNwzIy0EcRcOvBACfh4k0wgOmBX4xjfmk4DKTS31hgNWIKBCI8gdzogTgjYjQWFMw+o9LzJoZ63GUmjWm2wGDc7EvDDOj/1IVMIyD9SUAL0WEhpriRlXv5je5S+U1i2N88zdPuoVkeB+ls4SyxCoP3kVm9jsjpEsBLoOBNC5U9SwpGdakFkviuFP1keblATkTENTYcxkzgxTKOI3jyDxqLkQT87pMA++H3XvJBYtsNbBN6vuXq5S737WqHkW1VgMQNXJ0RshMqbbT33sJ5kpHWymzcJjNTeJIymJZtSQd9NHQHS1vodoFoTMkfbJzpRnLzB2vi6BZAJxWaCr+62BC+jzAxVJb3dmmiLzLwZhZNPE5e880Suo2AZgB8e8idxherqUPnT3brBDTlPxO3Z66rVwIwySXugdNd+5ejhqp/+NmgIwGX3Py3QBmlEi54KlwmjkOytQ+iJrLJj23S4GkOeecg8G091no737qvRRdzE+HLALQoMTBbJgBsCj5RSWUlUVJiZ4SOljb05eLFWgoJ5oY6yTyJp62D39jDANoKKcSocPJD5dQYzlFAFZJflUArgTPZKZwLXAnHmerfJquUkKZEgyzqOb5TuDt1P3nwxobqwPocZA11m4A1mBx5IxNgRH21ti7KbAGiyNn3HoF/gJ0w05A8xclpwAAAABJRU5ErkJggg==' />";
  // //const char* headhtml = "<meta name='color-scheme' content='dark light'><style></style><script></script>";
  // wifiManager.setCustomHeadElement(headhtml);
  char textSize[10];
  //sprintf(textSize, "%04d", Par_TextSize);
    itoa( Par_TextSize , textSize ,10);
 // WiFiManagerParameter custom_html1("<link rel='icon' type='image/png' href='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAADQElEQVRoQ+2YjW0VQQyE7Q6gAkgFkAogFUAqgFQAVACpAKiAUAFQAaECQgWECggVGH1PPrRvn3dv9/YkFOksoUhhfzwz9ngvKrc89JbnLxuA/63gpsCmwCADWwkNEji8fVNgotDM7osI/x777x5l9F6JyB8R4eeVql4P0y8yNsjM7KGIPBORp558T04A+CwiH1UVUItiUQmZ2XMReSEiAFgjAPBeVS96D+sCYGaUx4cFbLfmhSpnqnrZuqEJgJnd8cQplVLciAgX//Cf0ToIeOB9wpmloLQAwpnVmAXgdf6pwjpJIz+XNoeZQQZlODV9vhc1Tuf6owrAk/8qIhFbJH7eI3eEzsvydQEICqBEkZwiALfF70HyHPpqScPV5HFjeFu476SkRA0AzOfy4hYwstj2ZkDgaphE7m6XqnoS7Q0BOPs/sw0kDROzjdXcCMFCNwzIy0EcRcOvBACfh4k0wgOmBX4xjfmk4DKTS31hgNWIKBCI8gdzogTgjYjQWFMw+o9LzJoZ63GUmjWm2wGDc7EvDDOj/1IVMIyD9SUAL0WEhpriRlXv5je5S+U1i2N88zdPuoVkeB+ls4SyxCoP3kVm9jsjpEsBLoOBNC5U9SwpGdakFkviuFP1keblATkTENTYcxkzgxTKOI3jyDxqLkQT87pMA++H3XvJBYtsNbBN6vuXq5S737WqHkW1VgMQNXJ0RshMqbbT33sJ5kpHWymzcJjNTeJIymJZtSQd9NHQHS1vodoFoTMkfbJzpRnLzB2vi6BZAJxWaCr+62BC+jzAxVJb3dmmiLzLwZhZNPE5e880Suo2AZgB8e8idxherqUPnT3brBDTlPxO3Z66rVwIwySXugdNd+5ejhqp/+NmgIwGX3Py3QBmlEi54KlwmjkOytQ+iJrLJj23S4GkOeecg8G091no737qvRRdzE+HLALQoMTBbJgBsCj5RSWUlUVJiZ4SOljb05eLFWgoJ5oY6yTyJp62D39jDANoKKcSocPJD5dQYzlFAFZJflUArgTPZKZwLXAnHmerfJquUkKZEgyzqOb5TuDt1P3nwxobqwPocZA11m4A1mBx5IxNgRH21ti7KbAGiyNn3HoF/gJ0w05A8xclpwAAAABJRU5ErkJggg==' />");
  WiFiManagerParameter custom_html("<p style='color:pink;font-weight:Bold;'>Parametre</p>"); // only custom html
  WiFiManagerParameter custom_TextSize("textSize", "Textsize", textSize, 3);
    itoa( Par_Location , textSize ,10);
  WiFiManagerParameter custom_Location("Location", "Location", textSize ,2);
    itoa( Par_WghtStrt , textSize ,10);
  WiFiManagerParameter custom_WeightStr("WeightStr", "WeightStr", textSize, 2);
    itoa( Par_WghtStop , textSize ,10);
  WiFiManagerParameter custom_WeightStp("WeightStp", "WeightStp", textSize, 2);
  
  WiFiManagerParameter custom_EndChar("EndChar", "EndChar", Par_EndChar.c_str() , 2);
    itoa( SerailBouderate1 , textSize ,10);
  WiFiManagerParameter custom_Baudrate("Baudrate", "Baudrate", textSize , 8);

  // WiFiManagerParameter custom_ipaddress("input_ip", "input IP", "", 15,"pattern='\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}'"); // custom input attrs (ip mask)
  // WiFiManagerParameter custom_input_type("input_pwd", "input pass", "", 15,"type='password'"); // custom input attrs (ip mask)
  // const char _customHtml_checkbox[] = "type=\"checkbox\""; 
  // WiFiManagerParameter custom_checkbox("my_checkbox", "My Checkbox", "T", 2, _customHtml_checkbox,WFM_LABEL_AFTER);

 //new (&custom_field) WiFiManagerParameter("customfieldid", "Custom Field Label", "Custom Field Value", customFieldLength,"placeholder=\"Custom Field Placeholder\" type=\"checkbox\""); // custom html type

  // add all your parameters here
  //wifiManager.addParameter(&custom_html1);
  wifiManager.addParameter(&custom_html);
  wifiManager.addParameter(&custom_TextSize);
  wifiManager.addParameter(&custom_Location);
  wifiManager.addParameter(&custom_WeightStr);
  wifiManager.addParameter(&custom_WeightStp);
  wifiManager.addParameter(&custom_EndChar);
  wifiManager.addParameter(&custom_Baudrate);


  // const char* menu[] = {"wifi","wifinoscan","info","param","close","sep","erase","restart","exit"};
  // wifiManager.setMenu(menu,9); // custom menu array must provide length
  std::vector<const char *> menu = {"wifi","wifinoscan","sep","param","sep","erase","update","restart","exit"};
    wifiManager.setMenu(menu);
    wifiManager.setSaveParamsCallback(saveParamCallback);
    wifiManager.setSaveConfigCallback(saveWifiCallback);
    wifiManager.setAPCallback(configModeCallback);
     
    // wifiManager.setSaveConnect(configModeCallback);




  IPAddress _ip, _gw, _sn, _ip1, _gw1, _sn1, _dns1 ,_NetwIpNa, _NetwMask;
  _ip1.fromString(SSIDTcpi);
  _gw1.fromString(SSIDGetw);
  _sn1.fromString(SSIDMask);
  _dns1.fromString("8.8.8.8");

  wifiManager.setAPStaticIPConfig(_ip, _gw, _sn);
  wifiManager.preloadWiFi(SSIDName , SSIDPasw);
  wifiManager.setSTAStaticIPConfig(_ip1,_gw1,_sn1,_dns1);
  wifiManager.setDarkMode(true);


    //wifiManager.setConfigPortalTimeout(180);
    //wifiManager.setConnectTimeout(60);
    //wifiManager.setTimeout(15);
   // wifiManager.resetSettings();
    if(!wifiManager.autoConnect(NetwSsid.c_str(), NetwPasw.c_str())) {   // .autoConnect
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
  //  ESP.reset();    
  //    wifiManager.setTimeout(180);
    mydisplay.showDisplay7S("delay", 200, Par_Point);
    ESP.restart();
  } 
  //  Serial.println("Exit AP");
  //WiFi.setAutoReconnect(false);

  // WiFi.setAutoReconnect(trTestue);
  //  WiFi.persistent(flase);
  // wifiConectStatus =WiFi.onStationModeGotIP(ConnectTodo);

}


void ESP8266_Html::AP_Mode(){
//https://www.youtube.com/watch?v=XZC6Ucxn4bE

WiFi.mode(WIFI_AP_STA);
delay(1000);
  IPAddress _ip, _gw, _sn, _ip1, _gw1, _sn1, _dns1 ,_NetwIpNa, _NetwMask, _NetwGetw;
  _ip = IPAddress(10, 10, 100, 254);
  _gw = IPAddress(10, 10, 100, 1);
  _sn = IPAddress(255, 255, 255, 0);

if(WiFi.begin(SSIDName,SSIDPasw)) {
      String str = WiFi.localIP().toString();
      //str = str.substring(str.length()-6, str.length());
      Serial.println(str);
      mydisplay.showDisplay7S(str ,100,0);
        clearDisplay();
  }

_NetwIpNa.fromString(NetwIpNa);
_NetwMask.fromString(NetwMask);
  // WiFi.begin(NetwSsid, NetwPasw);
  // WiFi.hostname("CV19Archimede");
 //_dns1.fromString("10.10.101.254");//"8.8.8.8");
  WiFi.softAPConfig(_NetwIpNa, _NetwIpNa, _NetwMask);//, _dns1); 
  //WiFi.setAutoConnect(true);
  WiFi.softAP(NetwSsid, NetwPasw , 2 , 0 ,2 );//, 100);

  // while (WiFi.waitForConnectResult() != WL_CONNECTED) {
  //   WiFi.begin(NetwSsid, NetwPasw);
  //   Serial.println("WiFi failed, retrying.");
  // }
 
  // MDNS.begin(host);
//  httpUpdater.setup(&server);


 // WiFi.add
 // WiFi.softAPIP();
  // dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  // dnsServer.start(DNS_PORT, "*", _dns1);
  // server.on("/", handleRoot);
  // server.begin();
  //MDNS.begin();
 // WiFi.softAPDhcpServer();
  //return;
//   if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
//     Serial.println("STA Failed to configure");
// }
  //wifiManager.resetSettings();
  // //  wifiManager.setConfigPortalTimeout(timeout);
 //  wifiManager.setAPCallback(configModeCallback);

my_wifimanager();


// wifiAbortStatus =WiFi.onStationModeDisconnected(ConnectBreak);
//Serial.println(WiFi.RSSI());

/*

_NetwIpNa.fromString(NetwIpNa);
_NetwMask.fromString(NetwMask);
 //_dns1.fromString("10.10.101.254");//"8.8.8.8");
  IPAddress gateway(10,10,101,1);

  //WiFi.softAPConfig(_NetwIpNa, _NetwIpNa, _NetwMask);//, _dns1); 
  WiFi.softAPConfig(_NetwIpNa, _NetwIpNa, _NetwMask);//, _dns1); 
  
   WiFi.softAP(NetwSsid, NetwPasw, 2, 0, 1 , 100);
   return;
 if( WiFi.softAP(NetwSsid, NetwPasw, 2, 0, 1 , 100)) {
    Serial.print("WiFi.softAPIP() :");
    Serial.println(WiFi.softAPIP());
 }
*/


}


void ESP8266_Html::ESP8266_FactoryMod(){ 
    ltFs.FileCreate(_Menu_Start,"/net.ini");
    mydisplay.showDisplay7S("AP Mod" ,100 , 0);
    WiFi.mode(WIFI_AP);//WIFI_STA);
    wifiManager.resetSettings();
    wifiManager.setConfigPortalTimeout(timeout);
    wifiManager.reboot();
 }




//ESP-86A80E
WiFiClient client ;

void ESP8266_Html::setupHTML(){
Parametre_Wifi();

  AP_Mode();

  server.on("/",         HomePage);

  server.on("/dir",      Directory);
  server.on("/download", File_Download);
  server.on("/upload",   File_Upload);
  server.on("/fupload",  HTTP_POST,[](){ server.send(200);}, handleFileUpload);
#if defined(FULL)
   server.on("/label",    Label);
   server.on("/plu",      Plu);
#endif 
  server.on("/factorymod",    ESP8266_FactoryMod);
   server.on("/parametre",    Parametre_Scale);
   server.on("/wifisetting",  WiffiSetting);
   server.on("/ssidscan",  SsidScan);
   server.on("/espreset",   Reset);
   //server.on("/body",     Plu);   // Kontrol edileçek nasıl çalıştığını anlamadım
   server.on("/update",   UpdateFirmware);
   httpUpdater.setup(&server ,"/update2");
  // server.on("/tennisracket", HTTP_GET, [](AsyncWebServerRequest * request) {
  //   request->send(LittleFS , "/tennisracket.jfif", "image/jfif");
  // });


   server.begin();
  

    client.connect(ServerIp,ServerPo);
 }















int ClientRst;// =0;
int rssCount;
bool WMISBLOCKING    = true; 
void ESP8266_Html::ESP8266_Htmlweb(){
  // if(!WMISBLOCKING){
  //   wifiManager.process();
  // }
  server.handleClient();
    mydisplay.showDisplay7S(Gosterge, 1, Par_Point);
if(PortOnOf) {
  String Oku;

  if(client) {                             // If a new client connects,
    mydisplay.showDisplay7S("Hst Ok", 1, 0);
    mydisplay.show(25);
    Serial.println("Host Ok");
    ClientRst=0;     
    while (client.connected())    {
       ClientRst++;
       server.handleClient();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();  
        Oku += c;
        
          if(c == Par_endChr){
            //if(buf_vinc != Oku && Oku.length() > 5){// && Oku.length() < 11)  {  // Oku da 4 karekter = ise okumaya devam et
            if(Oku.length() > (size_t)(Par_TextSize - 1)){

              //  rssCount++;
              // if(rssCount < 2000)              {
              //    Gosterge = "fi" + (String)WiFi.RSSI();
              // }else if(rssCount > 4000) {
              //   scale.DisplayGeneral(Oku, false);
              //   rssCount=0;
              // }
               // Gosterge = "fi" + (String)WiFi.RSSI();
                scale.DisplayGeneral(Oku, false);
                mydisplay.showDisplay7S(Gosterge, 1, Par_Point);
                Oku="";           
               ClientRst=0; 
             }
          }

       }
      else if ( digitalRead(TRIGGER_PIN_PRINT) == LOW ){
      //ltFs.Fs_ReadLabel(labelName);
             Serial.println(ltFs.Fs_IniRead("/net.ini"));
           Serial.print("Chr :");    Serial.println(Par_endChr);
           delay(100);
           Serial.print("Par_textmode :"); Serial.println(Par_TexMode);
        delay(100);
        }
        else if ( digitalRead(TRIGGER_PIN_FS) == LOW ){
            ESP8266_FactoryMod();
           delay(100);
        }

              //  rssCount++;
              // if(rssCount < 500)              {
              //    Gosterge = "fi" + (String)WiFi.RSSI();
              //    mydisplay.digit7segment(Gosterge, 1, Par_Point);
              // }else if(rssCount >= 500 && rssCount < 1000) {
              //    mydisplay.digit7segment(Gosterge, 1, Par_Point);              
              // }else{
              //   rssCount=0;
              // }

     if(ClientRst >5000){
        client.stop(); 
        Serial.println("Wifi Reset");
        Serial.println(WiFi.RSSI());
        if(client.connect(ServerIp,ServerPo))
          Gosterge = "fi" + (String)WiFi.RSSI();
        
        ClientRst =0;
     }
      
      //mydisplay.show(1);
    }
 }else{
  //mydisplay.digit7segment("Hst No", 200, 0);
   Gosterge = "Hst No";
  Serial.print(".");
  //Serial.print("Host No");
  ClientRst++;
  //Serial.println(ClientRst);
  mydisplay.showDisplay7S("Hst No", 10, 0); 
  if(ClientRst > 250){
    //Serial.print("Host Waiting :")
    mydisplay.showDisplay7S("re Cnc", 500, 0);
    client.connect(ServerIp,ServerPo);
    ClientRst = 0;
  }
 
 }

  }

   
}

/**
//return;
//  WiFiClient client = server1.available();   // Listen for incoming clients
//   if (client) {                             // If a new client connects,
//     Serial.println("New Client.");          // print a message out in the serial port
//     String currentLine = "";                // make a String to hold incoming data from the client
//     while (client.connected()) {            // loop while the client's connected
//       if (client.available()) {             // if there's bytes to read from the client,
//         char c = client.read();             // read a byte, then
//         Serial.write(c);                    // print it out the serial monitor
//         // header += c;
//         // if (c == '\n') {                    // if the byte is a newline character
//         //   // if the current line is blank, you got two newline characters in a row.
//         //   // that's the end of the client HTTP request, so send a response:
//         //   if (currentLine.length() == 0) {
//         //     // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
//         //     // and a content-type so the client knows what's coming, then a blank line:
//         //     client.println("HTTP/1.1 200 OK");
//         //     client.println("Content-type:text/html");
//         //     client.println("Connection: close");
//         //     client.println();
//         //     // turns the GPIOs on and off
//         //     if (header.indexOf("GET /5/on") >= 0) {
//         //       Serial.println("GPIO 5 on");
//         //       output5State = "on";
//         //       digitalWrite(output5, HIGH);
//         //     } else if (header.indexOf("GET /5/off") >= 0) {
//         //       Serial.println("GPIO 5 off");
//         //       output5State = "off";
//         //       digitalWrite(output5, LOW);
//         //     } else if (header.indexOf("GET /4/on") >= 0) {
//         //       Serial.println("GPIO 4 on");
//         //       output4State = "on";
//         //       digitalWrite(output4, HIGH);
//         //     } else if (header.indexOf("GET /4/off") >= 0) {
//         //       Serial.println("GPIO 4 off");
//         //       output4State = "off";
//         //       digitalWrite(output4, LOW);
//         //     }else if (header.indexOf("?") >= 0) {
//         //       //dataConvert(header);
//         //       Serial.println("Port No:");
//         //       //GET /?txtSsid=Xiaomi_Pasam&txtPasw=aabbccddf1&txtTcpi=192.168.31.148&txtPort=8899 HTTP/1.1
//         //       //Xiaomi_Pasam&txtPasw=aabbc
//         //       int strindex = header.indexOf('?');
//         //        int index = header.indexOf(" HTTP/");
//         //        String str =header.substring((strindex + 1) , index);
//         //        Serial.println(str);
//         //        dataConvert(str, '&'); 
//         //        dataConvert(strs[3], '='); 
//         //        SSIDPort = strs[1];
//         //       //SSIDPort = str;
//         //        Serial.println(SSIDPort);
//         //     }
//         //     // append_page_header();
//         //     // append_page_footer();
//         //     // SendHTML_Content();
//         //       // SendHTML_Stop();
//         //     // return;
//         //     // Display the HTML web page
//         //     client.println("<!DOCTYPE html><html>");
//         //     client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
//         //     client.println("<link rel=\"icon\" href=\"data:,\">");
//         //     // CSS to style the on/off buttons 
//         //     // Feel free to change the background-color and font-size attributes to fit your preferences
//         //     client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
//         //     client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
//         //     client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
//         //     client.println(".button2 {background-color: #77878A;}</style></head>");
//         //     // Web Page Heading
//         //     client.println("<body><h1>Densi Web Server</h1>");
//         //     // Display current state, and ON/OFF buttons for GPIO 5  
//         //     client.println("<p>GPIO 5 - State " + output5State + "</p>");
//         //     // If the output5State is off, it displays the ON button       
//         //     if (output5State=="off") {
//         //       client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
//         //     } else {
//         //       client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
//         //     } 
//         //     // Display current state, and ON/OFF buttons for GPIO 4  
//         //     client.println("<p>GPIO 4 - State " + output4State + "</p>");
//         //     // If the output4State is off, it displays the ON button       
//         //     if (output4State=="off") {
//         //       client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
//         //     } else {
//         //       client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
//         //     }
//         //     client.println("<form>");
//         //     client.println("SSID :    <input type=\"text\" id=\"txtSsid\" name=\"txtSsid\" value=\"" + SSIDName + "\"> </br>");
//         //     client.println("Pasword : <input type=\"text\" id=\"txtPasw\" name=\"txtPasw\" value=\"" + SSIDPasw + "\"> </br>");
//         //     client.println("TCPIP :   <input type=\"text\" id=\"txtTcpi\" name=\"txtTcpi\" value=\"" + SSIDTcpi + "\"> </br>");
//         //     client.println("Port :    <input type=\"text\" id=\"txtPort\" name=\"txtPort\" value=\"" + SSIDPort + "\"> </br>");
//         //     client.println("<input type=\"submit\" value=\"Send\">");
//         //     client.println("</form>");
//         //     client.println("</body></html>");
//         //     // The HTTP response ends with another blank line
//         //     client.println();
//         //     // Break out of the while loop
//         //     break;
//         //   } else { // if you got a newline, then clear currentLine
//         //     currentLine = "";
//         //   }
//         // } else if (c != '\r') {  // if you got anything else but a carriage return character,
//         //   currentLine += c;      // add it to the end of the currentLine
//         // }
//       }
//     }
//     // Clear the header variable
//     header = "";
//     // Close the connection
//     client.stop();
//     Serial.println("Client disconnected.");
//     Serial.println("");
//   }
//}

// void ESP8266_Html::dataConvert(String str,char ch)
// {
//   int StringCount = 0;
//   // Split the string into substrings
//   while (str.length() > 0)
//   {
//     int index = str.indexOf(ch);
//     if (index == -1) // No space found
//     {
//       strs[StringCount++] = str;
//       break;
//     }
//     else
//     {
//       strs[StringCount++] = str.substring(0, index);
//       str = str.substring(index+1);
//     }
//   }

//      for (int i = 0; i < StringCount; i++)
//    {
//      Serial.print(i);
//      Serial.print(": ");
//      Serial.print(strs[i]);
//      Serial.println();
//      //delay(50);
//    }
//   // Serial.println("header:");
//   // Serial.println(header);
//   // //GET /?txtSsid=Xiaomi_Pasam&txtPasw=aabbccddf1&txtTcpi=192.168.31.148&txtPort=8899 HTTP/1.1
//   // int index = header.lastIndexOf('&');
//   // Serial.println("index:");
//   // Serial.println(index);
//   // int lenght = header.length();
//   // Serial.println("lenght:");
//   // Serial.println(lenght);
//   // String sub_s = header.substring(index,lenght);
//   // Serial.println("sub_s:");
//   // Serial.println(sub_s);
//   // //output4State = "off";
//   // //digitalWrite(output4, LOW);
// }
*/

#endif
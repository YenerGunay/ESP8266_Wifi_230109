#ifndef _Scale
#define _Scale

// #include "string.h"
 //#include "ShiftDisplay.h"
// #include "CharacterEncoding.h"
//#include "littleFS_Read.h"


littleFS_Read ltFs_Rw;
// #define LOAD 16	//15;
// #define SCLK 4	//5//14;
// #define SDI  0 	//4//13;


int Par_TextSize;//= 0;
int Par_Location;//= 0;
int Par_WghtStrt;//= 0;
int Par_WghtStop;//= 0;
int Par_TareStrt;//= 0;
int Par_TareStop;//= 0;
int Par_UnitStrt;//= 0;
String Par_EndChar;// ="\n";
char Par_endChr; 
bool Par_TexMode;

int Par_Point;
int ReadChar;

int SerailBouderate1;// = 115200;
int SerailBouderate2;// = 115200;

class Scale
{
private:
public:
   // void ScaleView(String);
    void Parametre();
	void DisplayGeneral(String , bool );
};

#define SEGMENT 8
//ShiftDisplay display(LOAD, SCLK, SDI, COMMON_ANODE, SEGMENT);
// enum en_Par_Scale { TextSize, Location , WghtStrt, WghtStop, TareStrt, TareStop, UnitStrt,EndChar};
// enum en_Par_Ssid_ { ssidName, ssidPasw , ssidTcpi, ssidGetw, ssidMask, ssidSeIp, ssidSePo};

void Scale::Parametre(){
   SerailBouderate1 = ltFs_Rw.Fs_IniRead("[Modul]","BaudeRate=").toInt();
   SerailBouderate2 = ltFs_Rw.Fs_IniRead("[Modul]","BaudeRate=").toInt();

	Par_TextSize = ltFs_Rw.Fs_IniRead("[Parametre]","Size=").toInt();
	Par_Location = ltFs_Rw.Fs_IniRead("[Parametre]","Location=").toInt();
	Par_WghtStrt = ltFs_Rw.Fs_IniRead("[Parametre]","WeightStart=").toInt();
	Par_WghtStop = ltFs_Rw.Fs_IniRead("[Parametre]","WeightStop=").toInt();
	Par_TareStrt = ltFs_Rw.Fs_IniRead("[Parametre]","TareStart=").toInt();
	Par_TareStop = ltFs_Rw.Fs_IniRead("[Parametre]","TareStop=").toInt();
	Par_UnitStrt = ltFs_Rw.Fs_IniRead("[Parametre]","UnitStart=").toInt();	
	Par_EndChar = ltFs_Rw.Fs_IniRead("[Parametre]","EndChar=");	
	Par_TexMode = ltFs_Rw.Fs_IniRead("[Parametre]","TextMode=") == "No" ? false : true;	
		// if(Par_EndChar == "n" )
		// 	Par_endChr ='\n' ;
		// else 
		// 	Par_endChr =Par_EndChar[0];
			Par_endChr =Par_EndChar.toInt();

			ReadChar = Par_WghtStop -Par_WghtStrt;
	
}




char *strrev(char *str){
    char c, *front, *back;

    if(!str || !*str)
        return str;
    for(front=str,back=str+strlen(str)-1;front < back;front++,back--){
        c=*front;*front=*back;*back=c;
    }
    return str;
}

String Gosterge ="Densi";
String Gosterge_html;
// int i =0;

int Gosterge_Sifirla =0;

void Scale::DisplayGeneral(String stt, bool seri_send){
	Gosterge_Sifirla = 0;
	stt = stt.substring(Par_WghtStrt , Par_WghtStop);
	int dig_lenght = Par_WghtStop - Par_WghtStrt ;
	Gosterge_html = stt;
	if(Par_endChr == 61 )	{
	stt.replace(".0","");
    stt.replace(":0","01");
    stt.replace(";0","11");
    stt.replace("<0","21");
    stt.replace("=0","31");
    stt.replace(">0","41");
    stt.replace("?0","51");
    stt.replace("@0","61");

		if(seri_send){
		Serial.print("sst :");    	Serial.println(stt);
		}
	char ch_stt[16];
	stt.toCharArray(ch_stt,16);
	stt = strrev(ch_stt);  
	}
    	Par_Point = stt.indexOf('.');
		if(seri_send)		{
			Serial.print("printBuffer_str :");    		Serial.println(stt);
			Serial.print("Point :");    		Serial.println(Par_Point);
		}
		char text[20]={0};
    	float fl = stt.toFloat();
		// sprintf(text, strdeger ,  Par_endChr == '=' ? (fl/10) : fl);
	  	// dtostrf(fl , dig_lenght , ( dig_lenght - (Par_Point + 1 )), text);   //7 digit ok
	  if( Par_endChr == 61){
		sprintf(text, "%8.0f" , fl/10);
	  }
	  else{
	   	dtostrf(fl , dig_lenght ,( Par_Point < 0 ? 0 : ( dig_lenght - (Par_Point + 1)))   , text);
	  }
	  	// Par_Point =  Par_Point - 1 ; // Par_Location;  //2;//Par_Point - (8 - dig_lenght); 
	     Par_Point =   Par_Point - (dig_lenght - 7 ); 
		if(seri_send)		{
			Serial.print("float :");    		Serial.println(text);
		}

		Gosterge = text;
		Gosterge.replace(".","");
	if(seri_send){
		Serial.print("Gosterge :");		Serial.println(Gosterge);	// printBuffer_str2);
	}

    _varStr[38] = Gosterge;
}


/*void Scale::DisplayGeneral(String stt, bool seri_send){
// i++;
// Gosterge ="1234";
// Gosterge +=i;
// if(i >6000) i=0;
// return;
	stt = stt.substring(Par_WghtStrt , Par_WghtStop);
	Gosterge_html =stt;
	if(Par_endChr == '=')	{
	stt.replace(".0","");
    stt.replace(":0","01");
    stt.replace(";0","11");
    stt.replace("<0","21");
    stt.replace("=0","31");
    stt.replace(">0","41");
    stt.replace("?0","51");
    stt.replace("@0","61");

		if(seri_send){
		Serial.print("sst :");
    	Serial.println(stt);
		}
	char ch_stt[16];
	stt.toCharArray(ch_stt,16);
	stt = strrev(ch_stt);  
	}
	
		if(seri_send){
		Serial.print("printBuffer_str :");
    	Serial.println(stt);
		}
    	Par_Point = stt.indexOf('.');
		Par_Point--;
		char text[20]={0};
    	float fl = stt.toFloat();


		const char* strdeger = "%8.2f";   //"%7.0f";
		if(Par_endChr == '=') strdeger = "%8.0f";
		else if(Par_Point == 6)  strdeger = "%8.0f";
		else if(Par_Point == 5)  strdeger = "%8.1f";
	 	else if(Par_Point == 4)  strdeger = "%8.2f";
		else if(Par_Point == 3)  strdeger = "%8.3f";
		else if(Par_Point == 2)  strdeger = "%8.4f";
		else if(Par_Point == 1)  strdeger = "%8.5f";
		else if(Par_Point == 0)  strdeger = "%8.0f";
		//else if(Par_Point == 1)  strdeger = "%8.6f";

		sprintf(text, strdeger ,  Par_endChr == '=' ? (fl/10) : fl);
  		//sprintf(text, strdeger ,  fl);
		if(seri_send)
		{
			Serial.print("6.1f :");
    		Serial.println(text);
		}
		Gosterge = text;
		Gosterge.replace(".","");



	if(seri_send){
		Serial.print("Gosterge :");
		Serial.println(Gosterge);	// printBuffer_str2);
	}

    _varStr[38] = Gosterge;

}




*/



#endif
#ifndef _myShiftDisplay
#define _myShiftDisplay

//#include "Arduino.h"
#include "myCharacterEncoding.h"

// #define LOAD 16	//15;
// #define SCLK 0  //4	//5 //14;
// #define SDI  2  //0 //4 //13;
const int MAX_DISPLAY_SIZE = 8;
const int POV = 1; 
class myShiftDisplay{
    private:
    int _latchPin;
	int _clockPin;
	int _dataPin;
    int _displaySize;
    byte _buffer[MAX_DISPLAY_SIZE];
    int _sectionBegins[MAX_DISPLAY_SIZE];	//MAX_DISPLAY_SIZE]; 
    int _sectionSizes[MAX_DISPLAY_SIZE];		//MAX_DISPLAY_SIZE]; 
    int _sectionCount;
   // void initPins(int latchPin, int clockPin, int dataPin);
    //const char ALIGN_LEFT = 'L';
    //void encodeCharacters(int, const char , byte, int ) ;
    public:
    myShiftDisplay();
    void digit7segmentNumber(String myString);
    void showDisplay7S(String  , unsigned long , int );
    void showDisplay();
    void show(unsigned long );
};

///////////////////////////////////////////////////////////////////////////
//						0		1	2	3	4		5	6	7	8		9	A	B	C		D	E	F
uint8_t digits[16] =   {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,};
uint8_t segs[7] =   { 0x1,0x2,0x4,0x8,0x10,0x20,0x40};//   0x10,0x20,0x1,0x2,0x4,0x8,0x40}; // clockwise, starting with the lowerl eft
//int segs[10] = {192,249,164,176,153,146,130,248,128,144 }; 
uint8_t digitsD[16] ={0xd, 0x79,0x54,0x6d, 0x06}; 



myShiftDisplay::myShiftDisplay(){
    pinMode(LOAD, OUTPUT);
	pinMode(SCLK, OUTPUT);
	pinMode(SDI, OUTPUT);
}


void clearDisplay() {
   // for (int i = 0; i < 9; i++)
   // {
    
	digitalWrite(LOAD, LOW);
    	shiftOut(SDI, SCLK, LSBFIRST, 0);  //MSBFIRST
	shiftOut(SDI, SCLK, LSBFIRST, 0); // both ends of led with same value
	digitalWrite(LOAD, HIGH);
    //delay(1);
    //}

}



// void myShiftDisplay::initPins(int latchPin, int clockPin, int dataPin) {
// 	_latchPin = latchPin;
// 	_clockPin = clockPin;
// 	_dataPin = dataPin;
// 	pinMode(LOAD, OUTPUT);
// 	pinMode(SCLK, OUTPUT);
// 	pinMode(SDI, OUTPUT);
// 	clearDisplay(); // clear asap so junk doesnt show while initiating
// }

    // byte _buffer[8];
    // int _sectionBegins[8];	//MAX_DISPLAY_SIZE]; 
    // int _sectionSizes[8];		//MAX_DISPLAY_SIZE]; 
    // int _sectionCount;
    // //const char ALIGN_LEFT = 'L';





void encodeCharacters(int size, const char input[], byte output[], int dotIndex = -1) {
	for (int i = 0; i < size; i++) {
		char c = input[i];
		
		if (c >= '0' && c <= '9')
			output[i] = NUMBERS[c - '0'];
		else if (c >= 'a' && c <= 'z')
			output[i] = LETTERS[c - 'a'];
		else if (c >= 'A' && c <= 'Z')
			output[i] = LETTERS[c - 'A'];
		else if (c == '-')
			output[i] = MINUS;
		else // space or invalid
			output[i] = BLANK;
	 }
	
	if (dotIndex != -1)
		bitWrite(output[dotIndex], 0, 1);
}

// void modifyBuffer(int beginIndex, int size, byte codes[]) {
// 	for (int i = 0; i < size; i++)
// 	_buffer[i+beginIndex] =  codes[i];
// 		//_buffer[i+beginIndex] = _displayType ? codes[i] : ~codes[i];
// }

// void setAt(int section, int value) {
// 	setAt(section, (long) value); // call long function
// }

// void setAt(int section, long value){//, char alignment) {
// 	if (section >= 0 && section < _sectionCount) { // valid section
// 		// int valueSize = countCharacters(value);
// 		// char originalCharacters[valueSize];
// 		// getCharacters(value, valueSize, originalCharacters);
// 		int sectionSize = _sectionSizes[section];
// 		char formattedCharacters[sectionSize];
// 		//formatCharacters(valueSize, originalCharacters, sectionSize, formattedCharacters, alignment);
// 		byte encodedCharacters[sectionSize];
// 		encodeCharacters(sectionSize, formattedCharacters, encodedCharacters);
// 		modifyBuffer(_sectionBegins[section], sectionSize, encodedCharacters);
// 	}
// }


// void set(int value) {
// 	setAt(0, value);//, alignment);
// }

// void set(long value) {
// 	setAt(0, value);//, alignment);
// }

// void set(double valueReal, int decimalPlaces, char alignment) {
// 	setAt(0, valueReal, decimalPlaces, alignment);
// }
// void set(double valueReal) {
// 	setAt(0, valueReal);
// }
// void set(char value) {
// 	setAt(0, value);
// }
// void set(const char value[]) {
// 	setAt(0, value);//, alignment);
// }
// void set(const String &value) {
// 	setAt(0, value);//, alignment);
// }
unsigned long eskiZaman=0;
unsigned long yeniZaman;

void myShiftDisplay::showDisplay(){
        for (int i = 0; i < _displaySize; i++)    {      
             digitalWrite(LOAD, LOW);
    		  shiftOut(SDI, SCLK, LSBFIRST,_buffer[i]);//NUMBERS[i]); //digitsD[i]);     // "-" Karekter 
              shiftOut(SDI, SCLK, LSBFIRST,INDEXES[i]); //Segmentler
            digitalWrite(LOAD, HIGH);/* code */
     
          //delay(1);
    delayMicroseconds(50);//millis();     
    //delay(POV);//millis();     
 
    }
}

void myShiftDisplay::showDisplay7S(String myString , unsigned long time , int point){

//myString ="0";
//set(myString, ALIGN_LEFT);//, alignment); 
//displaySize = myString.length();
char printBuffer[9];
_displaySize = 8;
const char* strdeger = "%8s";
sprintf(printBuffer, strdeger, myString);

encodeCharacters(MAX_DISPLAY_SIZE, printBuffer , _buffer ,  point + 1);



for (unsigned long j = 0; j < time; j++){

//yeniZaman = millis();
// if(yeniZaman -eskiZaman >  time){

    showDisplay();
    //delay(10);
  //   eskiZaman = yeniZaman;
}
   // delay(2);
    // for (int i = 0; i < 8; i++)    {      
    // 	     digitalWrite(LOAD, LOW);
    // 		  shiftOut(SDI, SCLK, LSBFIRST,_buffer[i]);//NUMBERS[i]); //digitsD[i]);     // "-" Karekter 
    //           shiftOut(SDI, SCLK, LSBFIRST,INDEXES[i]); //Segmentler
    //         digitalWrite(LOAD, HIGH);/* code */
    // delayMicroseconds(10);//millis();     
    // //delay(1);//millis();     
     // }
 //  
//}
//}
clearDisplay();

}

void myShiftDisplay::show(unsigned long time) {

	unsigned long end = millis() + time - (POV * _displaySize); // start + total - last iteration
	while (millis() <= end)
// yeniZaman = millis();
// if(yeniZaman -eskiZaman > 1000){
//      eskiZaman = yeniZaman;
		showDisplay();

//}
	clearDisplay();
}



// void myShiftDisplay::digit7segment_sill(String myString ,int time , int point){
// //set(myString, ALIGN_LEFT);//, alignment); 
// char printBuffer[9];
// const char* strdeger = "%8s";
//    sprintf(printBuffer, strdeger, myString);
// 	//sprintf(printBuffer, "%s", floatBuffer);
// //encodeCharacters(int size, const char input[], byte output[], int dotIndex = -1);
// //String myString2 = "  " + myString;
// encodeCharacters(MAX_DISPLAY_SIZE, printBuffer , _buffer , point);
// for (int j = 0; j < time; j++){
//     for (int i = 0; i < 8; i++)    {      
//     	     digitalWrite(LOAD, LOW);
//     		  shiftOut(SDI, SCLK, LSBFIRST,_buffer[i]);//NUMBERS[i]); //digitsD[i]);     // "-" Karekter 
//               shiftOut(SDI, SCLK, LSBFIRST,INDEXES[i]); //Segmentler
//             digitalWrite(LOAD, HIGH);/* code */
//     delay(1);     
//     }
//    //clearDisplay();
// }
// }


void myShiftDisplay::digit7segmentNumber(String myString){
    bool eksi=false;
        if(myString.substring(0,1) =="-"){
        eksi =true;
        myString.replace("-","");
        }
    int chrInt =myString .length();
    for (int i = 0, j = chrInt-1; i < chrInt; i++){
    if(eksi){
           digitalWrite(LOAD, LOW);
          shiftOut(SDI, SCLK, MSBFIRST,segs[chrInt]);
          shiftOut(SDI, SCLK, MSBFIRST,64);     // "-" Karekter 
          //     shiftOut(dataPin, clockPin, MSBFIRST,128);  Nokta
        digitalWrite(LOAD, HIGH);
    }
        digitalWrite(LOAD, LOW);
          shiftOut(SDI, SCLK, MSBFIRST,0);  // Karartma
        digitalWrite(LOAD, HIGH);
           digitalWrite(LOAD, LOW);
          shiftOut(SDI, SCLK, MSBFIRST,segs[j--]);
          shiftOut(SDI, SCLK, MSBFIRST,digits[myString.substring(i , i+1).toInt()]);     
        digitalWrite(LOAD, HIGH);
    }

  //   digitalWrite(latchPin, LOW);
  //     shiftOut(dataPin, clockPin, MSBFIRST,0);
  //   digitalWrite(latchPin, HIGH);
  // delay(1000);
  //   digitalWrite(latchPin, LOW);
  //     shiftOut(dataPin, clockPin, MSBFIRST,128);  Nokta
  //   digitalWrite(latchPin, HIGH);
  // delay(1000);
}





#endif
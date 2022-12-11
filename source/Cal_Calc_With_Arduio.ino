#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include "HX711.h"
#define calibration_factor 890 // 로드셀 스케일 값 선언 
#define LOADCELL_DOUT_PIN 5
#define LOADCELL_SCK_PIN 4
HX711 scale; //엠프 핀 선언 

int blueTx=2;   //Tx (보내는핀 설정)
int blueRx=3;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString=""; //받는 문자열
unsigned int Read_Value = 0; 
void setup() {
  Serial.begin(9600);   //시리얼모니터 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  mySerial.begin(9600); //블루투스 시리얼 개방
  scale.set_scale(calibration_factor);  //스케일 지정 
  scale.tare();  //스케일 설정
  Serial.println("Readings:"); 
}
 
void loop() {
   while(mySerial.available())  //mySerial에 전송된 값이 있으면
  {
  char myChar = (char)mySerial.read();  //mySerial int 값을 char 형식으로 변환
  myString+=myChar;  
  }
  
  if(!myString.equals(""))  //myString 값이 있다면
  {
  Serial.println(myString);
  int data=myString.toInt();
  double gram=scale.get_units();
  gram=gram*data;
  mySerial.print(gram);    
  mySerial.print("kcal");           // 블루투스에 데이터 전송 .
  myString="";  //myString 변수값 초기화
  }

}

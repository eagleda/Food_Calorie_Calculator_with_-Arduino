# Food_Calorie_Calculator_with_Arduino
아두이노 저울을 이용한 음식 칼로리 계산기 만들기

##Description
FooD_Calorie_Calculator_with_Arduino(이하 CCWA)는 로드셀 센서로 구현한 아두이노 저울이 측정한 음식의 무게와 앱에서 블루투스로 아두이노로 전송한 신호값을 이용하여 음식의 총 칼로리를 계산, 다시 앱으로 전송하여 사용자에게 보여주는 프로그램이다.  
<img width="533" alt="image" src="https://user-images.githubusercontent.com/83822982/206903693-ea2ef9a8-3999-41f3-a909-1b7fa1ea7477.png">  

## How To Start
### Arduino
```c++
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
```
Arduino IDE로 위의 코드(source의 Cal_Calc_With_Arduino 파일)를 작성한 후, 
아래 회로도대로 아두이노 회로르 작성하여 코드를 업로드 한다.
이 때, HX711.h는 Tools ->  Manage Libraries에서 직점 찾아 설치하여야 한다.
<img width="452" alt="image" src="https://user-images.githubusercontent.com/83822982/206904256-f31a8beb-e54e-4207-8ca0-db35baece432.png">

<img width="718" alt="circuit_image" src="https://user-images.githubusercontent.com/83822982/206903658-51b907e5-872c-475d-9567-46dee0a2fc9a.png">
## Reference

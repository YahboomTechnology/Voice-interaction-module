#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial BT(A1, A2);
char speechval[12]={0};
int wi=0;
int speech = 0;

int LED_R = 10;  //LED_R接在arduino上的数字I/O口10
int LED_G = 11;  //LED_G接在arduino上的数字I/O口11
int LED_B = 9;   //LED_B接在arduino上的数字I/O口9

void setup(){
  Serial.begin(9600);
  BT.begin(115200);
  wi=0;
  //初始化RGB三色LED的IO口为输出方式
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop(){

  if (BT.available()) 
  {
     speechval[wi] = BT.read();
     //Serial.println(speechval[wi]);
     //Serial.println(wi);
     if(speechval[wi] == '#' || wi >= 5){
       wi = 0;
     }
     else{
       wi++;
     }
  }
  if(speechval[2] == '0'){
    if(speechval[3] == '9'){
      if(speechval[4] == '5'){
        speech = 95;
        //Serial.println("$A095#");
      }
    }
  }
  if(speech == 95){
      delay(100);
      BT.print("$A045#");
      Serial.println("OK");
	  digitalWrite(LED_R,  HIGH); //点亮红灯
	  digitalWrite(LED_G,  HIGH);  //熄灭绿灯
	  digitalWrite(LED_B,  HIGH);  //熄灭蓝灯
      speech = 0;
      for(int i;i<10;i++){
        speechval[i] = 0;
      }
  }  
}

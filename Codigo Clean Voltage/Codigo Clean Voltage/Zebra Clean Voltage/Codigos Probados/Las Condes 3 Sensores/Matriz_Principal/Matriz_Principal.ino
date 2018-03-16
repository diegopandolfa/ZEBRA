#include <Sprite.h>  
#include <Matrix.h>
#include <Metro.h>
#include <DFPlayer_Mini_Mp3.h> 
#include <LEDFader.h>
#define LED_PIN 3
#define FADE_TIME 4000
const int numChips = 6;
LEDFader led;
SoftwareSerial mp3(5, 4);
Matrix myLeds = Matrix(9,10,11, 6);
uint16_t currentFrame = 0;
bool isPeatonPresent = false;
Metro animationTime = Metro(100);
Metro peatonTime = Metro(15000);
Sprite M1 = Sprite(8, 8,   
B00000000,
B01111110,
B10000001,
B10000001,
B10000001,
B10000001,
B01111110,
B00000000

);

Sprite M2 = Sprite(8, 8,   
B00000000,
B00000000,
B01111111,
B00001000,
B00010100,
B00100010,
B01000001,
B00000000
);

Sprite F0M1 = Sprite(8, 8,   
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111,
B11111111



);

Sprite F0M2 = Sprite(8, 8,   
B01101111,
B00001111,
B00000111,
B00000011,
B00000000,
B00000000,
B00000000,
B00000000





);
Sprite F0M3 = Sprite(8, 8,   
B00000000,
B00000000,
B00011000,
B00011000,
B00110000,
B11100011,
B11111111,
B11111100



);

Sprite F0M4 = Sprite(8, 8,   
B11111111,
B11111111,
B10000000,
B10000000,
B11000000,
B11110000,
B00110000,
B00000000




);
Sprite F0M5 = Sprite(8, 8,   
B00000000,
B00000011,
B00000011,
B00111111,
B11111111,
B11100000,
B10000000,
B00000000



);

Sprite F0M6 = Sprite(8, 8,   
B10000000,
B11000000,
B01110011,
B01111111,
B00001111,
B00000011,
B00000000,
B00000000



);


Sprite F1M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110000,
B11111111,
B11111111



);
Sprite F1M2 = Sprite(8, 8, 
B01101111,
B00000111,
B00000011,
B00000001,
B00000000,
B00000000,
B00000000,
B00000000




);
Sprite F1M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00011000,
B00011000,
B00110000,
B11110111,
B11111111



);

Sprite F1M4 = Sprite(8, 8, 
B11111111,
B11111111,
B11111110,
B11110000,
B00111000,
B00011000,
B00000000,
B00000000



);
Sprite F1M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000011,
B00000011,
B00001111,
B01111110,
B11110000,
B11000000




);
Sprite F1M6 = Sprite(8, 8, 
B11110000,
B11111000,
B00011000,
B00011011,
B00011111,
B00001110,
B00000000,
B00000000



);

Sprite F2M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111



);
Sprite F2M2 = Sprite(8, 8, 
B11111111,
B01100111,
B00000011,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000



);

Sprite F2M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00001100,
B00011100,
B11111111,
B11111111




);

Sprite F2M4 = Sprite(8, 8, 
B11111111,
B11111111,
B11111100,
B00001100,
B00000000,
B00000000,
B00000000,
B00000000



);
Sprite F2M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000011,
B11000011,
B11111111,
B11111111



);
Sprite F2M6 = Sprite(8, 8, 
B11111000,
B00011000,
B00011110,
B00011110,
B00000000,
B00000000,
B00000000,
B00000000



);


Sprite F3M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111



);
Sprite F3M2 = Sprite(8, 8, 
B11111111,
B01100111,
B00000011,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000



);
Sprite F3M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000001,
B00011101,
B11111111,
B11111111


);
Sprite F3M4 = Sprite(8, 8, 
B11111111,
B11111110,
B11110000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000



);
Sprite F3M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B11000000,
B11100000,
B11101100,
B11111111,
B11111011



);
Sprite F3M6 = Sprite(8, 8, 
B11111111,
B00011111,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000



);

Sprite F4M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111



);
Sprite F4M2 = Sprite(8, 8, 
B11111111,
B01101111,
B00000111,
B00000011,
B00000000,
B00000000,
B00000000,
B00000000



);

Sprite F4M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00001101,
B11111111,
B11111111



);
Sprite F4M4 = Sprite(8, 8, 
B11111111,
B11111111,
B11111110,
B11110000,
B11100000,
B00000000,
B00000000,
B00000000



);
Sprite F4M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00001100,
B11101100,
B11111100,
B11111000,
B10000000



);
Sprite F4M6 = Sprite(8, 8, 
B11110000,
B11111011,
B00011111,
B00001111,
B00000110,
B00000000,
B00000000,
B00000000



);

Sprite F5M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111,
B11111111



);
Sprite F5M2 = Sprite(8, 8,
B01101111,
B00001111,
B00000111,
B00000011,
B00000001,
B00000000,
B00000000,
B00000000




);

Sprite F5M3 = Sprite(8, 8,
B00000000,
B00000000,
B00001000,
B00011100,
B01111000,
B11100001,
B11111111,
B11111111



);
Sprite F5M4 = Sprite(8, 8,
B11111111,
B11111111,
B11111110,
B10000000,
B10000000,
B01111000,
B01111000,
B00000000



);
Sprite F5M5 = Sprite(8, 8,
B00000000,
B00000110,
B00000110,
B01111110,
B11111100,
B11000000,
B10000000,
B10000000



);
Sprite F5M6 = Sprite(8, 8,
B11110000,
B11111000,
B00011011,
B00001111,
B00000111,
B00000011,
B00000000,
B00000000



);

Sprite F6M1 = Sprite(8, 8,
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111,
B11111111



);
Sprite F6M2 = Sprite(8, 8,
B01101111,
B00001111,
B00000111,
B00000011,
B00000001,
B00000000,
B00000000,
B00000000



);
Sprite F6M3 = Sprite(8, 8,
B00000000,
B00000000,
B00011000,
B00111000,
B01110000,
B11100001,
B11111111,
B11111111



);
Sprite F6M4 = Sprite(8, 8,
B11111111,
B11111111,
B11111111,
B10000000,
B11000000,
B11111000,
B00111000,
B00000000



);
Sprite F6M5 = Sprite(8, 8,
B00000000,
B00000011,
B00000011,
B01111111,
B11111111,
B11000000,
B10000000,
B00000000



);
Sprite F6M6 = Sprite(8, 8,
B00000000,
B11100000,
B11110000,
B00111011,
B00011111,
B00000111,
B00000011,
B00000000



);

Sprite FSM1 = Sprite(8, 8,
B00000000,
B00000000,
B00000000,
B00000011,
B00000111,
B00001100,
B01101111,
B11111111




);

Sprite FSM2 = Sprite(8, 8,
B11111111,
B11111111,
B01101111,
B00001100,
B00000111,
B00000011,
B00000000,
B00000000



);

Sprite FSM3 = Sprite(8, 8,
B00000000,
B00000000,
B00000000,
B11111000,
B11111000,
B00000000,
B11111111,
B11111111




);

Sprite FSM4 = Sprite(8, 8,
B11111100,
B11111111,
B11111111,
B00000000,
B11111000,
B11111000,
B00000000,
B00000000







);

Sprite FSM5 = Sprite(8, 8,
B00000000,
B00000000,
B00000000,
B00000000,
B00000001,
B00000011,
B11111111,
B11111111




);

Sprite FSM6 = Sprite(8, 8,
B00000000,
B11111111,
B11111111,
B00000011,
B00000001,
B00000000,
B00000000,
B00000000


);

void setup(){
  myLeds.clear();
  Serial.begin(9600);
  mp3.begin(9600);
  mp3_set_serial (mp3);   
  delay(1);                     
  mp3_set_volume (30); 
  myLeds.setBrightness(8); 
  led = LEDFader(LED_PIN);
}
void loop(){
led.update();
 if (peatonTime.check() == 1) {
   isPeatonPresent = false;
   led.fade(0, 2000);
}  
  if(animationTime.check() == 1 && isPeatonPresent == true){
  caminar();      
  }
  
 if (Serial.available() > 0) {
 int inByte = Serial.read();
 switch (inByte) {
        case 'M':
        mp3_play (random(1, 7)); 
        break;
        
        case 'P':
        if(isPeatonPresent == false){
        led.fade(255, FADE_TIME); 
        peatonTime.reset();
        isPeatonPresent = true;
        }
        break;
      
        case 'S':
        stand();
        break;

      case 'C':
      myLeds.clear();
      break;

      case 'O':
      peatonTime.reset();
      break;

      case 'L':
      mp3_set_volume (10); 
      break;

      case 'H':
      mp3_set_volume (30); 
      break;     
    }
  }
}
void caminar(){
 if(currentFrame == 0){
 myLeds.write(40, 0,  F0M1);
 myLeds.write(32, 0,  F0M2);
 myLeds.write(24, 0, F0M3);
 myLeds.write(16, 0, F0M4);
 myLeds.write(8, 0, F0M5);
 myLeds.write(0, 0, F0M6); 
 }
 if(currentFrame == 1){
 myLeds.write(40, 0,  F1M1);
 myLeds.write(32, 0,  F1M2);
 myLeds.write(24, 0, F1M3);
 myLeds.write(16, 0, F1M4);
 myLeds.write(8, 0, F1M5);
 myLeds.write(0, 0, F1M6);
}
 if(currentFrame == 2){
 myLeds.write(40, 0,  F2M1);
 myLeds.write(32, 0,  F2M2);
 myLeds.write(24, 0, F2M3);
 myLeds.write(16, 0, F2M4);
 myLeds.write(8, 0, F2M5);
 myLeds.write(0, 0, F2M6);
}
 if(currentFrame == 3){
 myLeds.write(40, 0,  F3M1);
 myLeds.write(32, 0,  F3M2);
 myLeds.write(24, 0, F3M3);
 myLeds.write(16, 0, F3M4);
 myLeds.write(8, 0, F3M5);
 myLeds.write(0, 0, F3M6);
}
 if(currentFrame == 4){
 myLeds.write(40, 0,  F4M1);
 myLeds.write(32, 0,  F4M2);
 myLeds.write(24, 0, F4M3);
 myLeds.write(16, 0, F4M4);
 myLeds.write(8, 0, F4M5);
 myLeds.write(0, 0, F4M6);
}
 if(currentFrame == 5){
 myLeds.write(40, 0,  F5M1);
 myLeds.write(32, 0,  F5M2);
 myLeds.write(24, 0, F5M3);
 myLeds.write(16, 0, F5M4);
 myLeds.write(8, 0, F5M5);
 myLeds.write(0, 0, F5M6);
     }
 if(currentFrame == 6){
 myLeds.write(40, 0,  F6M1);
 myLeds.write(32, 0,  F6M2);
 myLeds.write(24, 0, F6M3);
 myLeds.write(16, 0, F6M4);
 myLeds.write(8, 0, F6M5);
 myLeds.write(0, 0, F6M6);
}
currentFrame++;
if(currentFrame == 6){
currentFrame = 0; 
}
}

void stand(){
 myLeds.write(40, 0,   FSM1);
 myLeds.write(32, 0,   FSM2);
 myLeds.write(24, 0,  FSM3);
 myLeds.write(16, 0,  FSM4);
 myLeds.write(8, 0,  FSM5);
 myLeds.write(0, 0,  FSM6);
}

void ok(){
 myLeds.write(24, 0,  M1);
 myLeds.write(16, 0,  M2);
}
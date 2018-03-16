include <Adafruit_NeoPixel.h>
#include <Metro.h>
#include <Wire.h>
#include <RTClib.h>
#include <SoftwareSerial.h>  
#include <Sprite.h>  
#include <Matrix.h>
#include <EEPROM.h>
#include <DFPlayer_Mini_Mp3.h> 
#include <Sensor.h>
#include <LEDFader.h>
#define LED_PIN 3 // Pin de iluminacion
#define FADE_TIME 4000
LEDFader led;
SoftwareSerial mp3(11, 12);
Adafruit_NeoPixel cinta = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel corona = Adafruit_NeoPixel(64, 10, NEO_GRB + NEO_KHZ800);
RTC_DS1307 RTC;

//---------------------TIMERS-------------------------------
Metro cintaTime = Metro(22);
Metro peatonTime = Metro(15000);
Metro sensado = Metro(10);
Metro coroOff = Metro(650);
Metro coroOn = Metro(1650);
Metro parpadeoTime = Metro(300);
Metro animationTime = Metro(100);
Metro newcalib = Metro(2000);
//---------------------------------------------------------
int direccion = 0;
int j = 59;
// ---- MATRICES-------------------------
Matrix matriz_1 = Matrix(3,4,5, 6);
Matrix matriz_2 = Matrix(7,8,9, 6);

uint16_t currentFrame = 0;
uint16_t currentFrame_SEC = 0;
uint16_t coroLimit = 0;
//----------------------------------------
int horaDia;
int horaNoche;
int minutoDia;
int minutoNoche;
//----------------SENSORES---------------
Sensor sensor1(0);
Sensor sensor2(1);
Sensor sensor3(2);
Sensor sensor4(3);
//-----------------------------------------
bool isPeatonPresent = false;
bool isNight = false;
uint16_t jumpStart = 1;
uint16_t currentPixel = 0;
uint32_t currentColor;
uint32_t coronaColor;
int calibrationFlag = 2;
int startFlag = 0;
bool estadoParpa = false;
bool activateAnimation = false;

//------------------ANIMACIONES----------------------------------------------
Sprite D0M1 = Sprite(8, 8,   
B00000000,
B00000000,
B00000000,
B00000001,
B00000011,
B00000111,
B00001111,
B01101111



);

Sprite D0M2 = Sprite(8, 8,   
B11111111,
B11111111,
B11110111,
B01100000,
B00000000,
B00000000,
B00000000,
B00000000



);
Sprite D0M3 = Sprite(8, 8,   
B00000000,
B00110000,
B11110000,
B11000000,
B10000000,
B10000000,
B11111111,
B11111111

);

Sprite D0M4 = Sprite(8, 8,   
B11111100,
B11111111,
B11100011,
B00110000,
B00011000,
B00011000,
B00000000,
B00000000


);
Sprite D0M5 = Sprite(8, 8,   
B00000000,
B00000000,
B00000011,
B00001111,
B00111111,
B01110011,
B11100000,
B11000000

);

Sprite D0M6 = Sprite(8, 8,   
B00000000,
B00000000,
B10000000,
B11100000,
B11111111,
B00111111,
B00000011,
B00000011

);


Sprite D1M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000001,
B00000011,
B00000111,
B01101111

);
Sprite D1M2 = Sprite(8, 8, 
B11111111,
B11111111,
B11110000,
B01100000,
B00000000,
B00000000,
B00000000,
B00000000


);
Sprite D1M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00011100,
B00111100,
B11110000,
B11111110,
B11111111,
B11111111

);

Sprite D1M4 = Sprite(8, 8, 
B11111111,
B11110111,
B00110000,
B00011000,
B00011000,
B00000000,
B00000000,
B00000000

);
Sprite D1M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00001110,
B00011111,
B00011011,
B00011000,
B11111000,
B11110000


);
Sprite D1M6 = Sprite(8, 8, 
B11000000,
B11110000,
B01111110,
B00001111,
B00000011,
B00000011,
B00000000,
B00000000

);

Sprite D2M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000011,
B01100111,
B11111111

);
Sprite D2M2 = Sprite(8, 8, 
B11111111,
B11110111,
B01100000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000

);

Sprite D2M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00001100,
B11111100,
B11111111,
B11111111

);

Sprite D2M4 = Sprite(8, 8, 
B11111111,
B11111111,
B00011100,
B00001100,
B00000000,
B00000000,
B00000000,
B00000000

);
Sprite D2M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00011110,
B00011110,
B00011000,
B11111000

);
Sprite D2M6 = Sprite(8, 8, 
B11111111,
B11111111,
B11000011,
B00000011,
B00000000,
B00000000,
B00000000,
B00000000

);


Sprite D3M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000011,
B01100111,
B11111111

);
Sprite D3M2 = Sprite(8, 8, 
B11111111,
B11110111,
B01100000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000

);
Sprite D3M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B11110000,
B11111110,
B11111111

);
Sprite D3M4 = Sprite(8, 8, 
B11111111,
B11111111,
B00011101,
B00000001,
B00000000,
B00000000,
B00000000,
B00000000

);
Sprite D3M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00011111,
B11111111

);
Sprite D3M6 = Sprite(8, 8, 
B11111011,
B11111111,
B11101100,
B11100000,
B11000000,
B00000000,
B00000000,
B00000000

);

Sprite D4M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000011,
B00000111,
B01101111,
B11111111

);
Sprite D4M2 = Sprite(8, 8, 
B11111111,
B11110111,
B01100000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000

);

Sprite D4M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B11100000,
B11110000,
B11111110,
B11111111,
B11111111

);
Sprite D4M4 = Sprite(8, 8, 
B11111111,
B11111111,
B00001101,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000

);
Sprite D4M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000110,
B00001111,
B00011111,
B11111011,
B11110000

);
Sprite D4M6 = Sprite(8, 8, 
B10000000,
B11111000,
B11111100,
B11101100,
B00001100,
B00000000,
B00000000,
B00000000

);

Sprite D5M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000001,
B00000011,
B00000111,
B00001111,
B01101111

);
Sprite D5M2 = Sprite(8, 8,
B11111111,
B11111111,
B11110111,
B01100000,
B00000000,
B00000000,
B00000000,
B00000000

);

Sprite D5M3 = Sprite(8, 8,
B00000000,
B00000000,
B01111000,
B11111000,
B10000000,
B11111110,
B11111111,
B11111111

);
Sprite D5M4 = Sprite(8, 8,
B11111111,
B11111111,
B11100001,
B01111000,
B00011100,
B00001000,
B00000000,
B00000000

);
Sprite D5M5 = Sprite(8, 8,
B00000000,
B00000000,
B00000011,
B00000111,
B00001111,
B00011011,
B11111000,
B11110000

);
Sprite D5M6 = Sprite(8, 8,
B10000000,
B10000000,
B11000000,
B11111100,
B01111110,
B00000110,
B00000110,
B00000000

);

Sprite D6M1 = Sprite(8, 8,
B00000000,
B00000000,
B00000000,
B00000001,
B00000011,
B00000111,
B00001111,
B01101111

);
Sprite D6M2 = Sprite(8, 8,
B11111111,
B11111111,
B11110111,
B01100000,
B00000000,
B00000000,
B00000000,
B00000000

);
Sprite D6M3 = Sprite(8, 8,
B00000000,
B00111000,
B11111000,
B11000000,
B10000000,
B11111111,
B11111111,
B11111111

);
Sprite D6M4 = Sprite(8, 8,
B11111111,
B11111111,
B11100001,
B01110000,
B00111000,
B00011000,
B00000000,
B00000000

);
Sprite D6M5 = Sprite(8, 8,
B00000000,
B00000000,
B00000011,
B00000111,
B00011111,
B00111011,
B11110000,
B11100000

);
Sprite D6M6 = Sprite(8, 8,
B00000000,
B10000000,
B11000000,
B11111111,
B01111111,
B00000011,
B00000011,
B00000000

);

Sprite DSM1 = Sprite(8, 8,
B00000000,
B00000000,
B00000000,
B00000011,
B00000111,
B00001100,
B01101111,
B11111111




);

Sprite DSM2 = Sprite(8, 8,
B11111111,
B11111111,
B01101111,
B00001100,
B00000111,
B00000011,
B00000000,
B00000000



);

Sprite DSM3 = Sprite(8, 8,
B00000000,
B00000000,
B00000000,
B11111000,
B11111000,
B00000000,
B11111111,
B11111111




);

Sprite DSM4 = Sprite(8, 8,
B11111100,
B11111111,
B11111111,
B00000000,
B11111000,
B11111000,
B00000000,
B00000000







);

Sprite DSM5 = Sprite(8, 8,
B00000000,
B00000000,
B00000000,
B00000000,
B00000001,
B00000011,
B11111111,
B11111111




);

Sprite DSM6 = Sprite(8, 8,
B00000000,
B11111111,
B11111111,
B00000011,
B00000001,
B00000000,
B00000000,
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

//--------------------------------------------------------------------------

void saveData(){
int eeAddress = 0;  
sensor1.MinSave = sensor1.Min;
sensor2.MinSave = sensor2.Min;
sensor3.MinSave = sensor3.Min;
sensor4.MinSave = sensor4.Min;
EEPROM.put(eeAddress, sensor1.Min); 
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensor2.Min); 
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensor3.Min); 
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensor4.Min); 
eeAddress += sizeof(int);
sensor1.MaxSave = sensor1.Max; 
sensor2.MaxSave = sensor2.Max;
sensor3.MaxSave = sensor3.Max;
sensor4.MaxSave = sensor4.Max;
EEPROM.put(eeAddress, sensor1.MaxSave);
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensor2.MaxSave);
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensor3.MaxSave);
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensor4.MaxSave);
}

int getData(){
int eeAddress = 0; 
EEPROM.get(eeAddress, sensor1.MinSave);  
sensor1.Min = sensor1.MinSave;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensor2.MinSave);  
sensor2.Min = sensor2.MinSave;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensor3.MinSave);  
sensor3.Min = sensor3.MinSave;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensor4.MinSave);  
sensor4.Min = sensor4.MinSave;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensor1.MaxSave);
sensor1.Max = sensor1.MaxSave;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensor2.MaxSave);
sensor2.Max = sensor2.MaxSave;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensor3.MaxSave);
sensor3.Max = sensor3.MaxSave;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensor4.MaxSave);
sensor4.Max = sensor4.MaxSave;
eeAddress += sizeof(int);
if(sensor1.MinSave > 0 && sensor2.MinSave > 0 && sensor3.MinSave > 0 && sensor4.MinSave > 0){
  calibrationFlag = 0;
  return 1;
} else {
  return 0;
}
}

void calibracionSetup(){ 
    sensor1.Min = 1023;        
    sensor1.Max = 0;
    sensor2.Min = 1023;
    sensor2.Max = 0;    
    sensor3.Min = 1023;
    sensor3.Max = 0;
    sensor4.Min = 1023;
    sensor4.Max = 0; 
    while (millis() < 10000) {
    sensor1.Value = sensor1.Average();
    sensor2.Value = sensor2.Average();
    sensor3.Value = sensor3.Average();
    sensor4.Value = sensor4.Average();
    
    if (sensor1.Value > sensor1.Max) {
      sensor1.Max = sensor1.Value;
    }

    if (sensor1.Value < sensor1.Min) {
      sensor1.Min = sensor1.Value;
    }

        if (sensor2.Value > sensor2.Max) {
      sensor2.Max = sensor2.Value;
    }

    if (sensor2.Value < sensor2.Min) {
      sensor2.Min = sensor2.Value;
    }


    if (sensor3.Value > sensor3.Max) {
      sensor3.Max = sensor3.Value;
    }

    if (sensor3.Value < sensor3.Min) {
      sensor3.Min = sensor3.Value;
    }


    if (sensor4.Value > sensor4.Max) {
      sensor4.Max = sensor4.Value;
    }

    if (sensor4.Value < sensor4.Min) {
      sensor4.Min = sensor4.Value;
    } 
  }
if((sensor1.Max - sensor1.Min) < 260 && (sensor2.Max - sensor2.Min) < 260 && (sensor3.Max - sensor3.Min) < 260 && (sensor4.Max - sensor4.Min) < 260){
sensor1.Min = sensor1.Min - 50;
sensor1.Max = sensor1.Max + 60;
sensor2.Min = sensor2.Min - 50;
sensor2.Max = sensor2.Max + 60;
sensor3.Min = sensor3.Min - 50;
sensor3.Max = sensor3.Max + 60;
sensor4.Min = sensor4.Min - 50;
sensor4.Max = sensor4.Max + 60;
//saveData();
//startFlag = 1;
} else {
  //digitalWrite(transistorPin, HIGH); 
}
}

void setup(){
  Serial.begin(115200); 
  Wire.begin();             
  RTC.begin();
  cinta.begin();
  cinta.show();
  corona.begin();
  corona.show();
  mp3.begin(9600);
  mp3_set_serial (mp3);   
  delay(1);                     
  mp3_set_volume (30); 
  matriz_1.clear();
  matriz_1.setBrightness(8); 
  matriz_2.clear();
  matriz_2.setBrightness(8); 
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
  led = LEDFader(LED_PIN);
  DateTime now = RTC.now(); 
  uint8_t hora = now.hour();
  uint8_t minuto = now.minute();
  uint8_t segundo = now.second();
  uint8_t Dia = now.day();
  uint8_t mes = now.month();
  if(hora > 5 && hora < 20){
  isNight = false;
  cinta.setBrightness(255);
  corona.setBrightness(255);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 } else {
  isNight = true;
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
   if(getData() == 1){
   } else {
   calibracionSetup();
   } 
}

void calibracionTest(){
    sensor1.Min = 1023;        
    sensor1.Max = 0;
    sensor2.Min = 1023;
    sensor2.Max = 0;    
    sensor3.Min = 1023;
    sensor3.Max = 0;
    sensor4.Min = 1023;
    sensor4.Max = 0; 
    calibrationFlag = 2;
    sensor1.Value = sensor1.Average();
    sensor2.Value = sensor2.Average();
    sensor3.Value = sensor3.Average();
    sensor4.Value = sensor4.Average();
    while(newcalib.check() != 1){
    sensor1.Value = sensor1.Average();
    sensor2.Value = sensor2.Average();
    sensor3.Value = sensor3.Average();
    sensor4.Value = sensor4.Average();
    
     if((sensor1.Value < sensor1.MinSec || sensor1.Value > sensor1.MaxSec || sensor2.Value < sensor2.MinSec ||  sensor2.Value > sensor2.MaxSec || sensor3.Value < sensor3.MinSec ||  sensor3.Value > sensor3.MaxSec || sensor4.Value < sensor4.MinSec ||  sensor4.Value > sensor4.MaxSec) && calibrationFlag == 2){
   if(sensor1.Value < 800 || sensor2.Value < 800 || sensor3.Value < 800 || sensor4.Value < 800){
        peaton(); 
    } 
  }  
    if (Serial.available() > 0) {
 int inByte = Serial.read();
 switch (inByte) {
        case 'P':
        if(isNight == true){
       // panel1.print('P');
       // panel2.print('P'); 
        }
        peatonTime.reset();
        isPeatonPresent = true;
        break;
}
  }
     if (sensor1.Value > sensor1.Max) {
      sensor1.Max = sensor1.Value;
    }

    if (sensor1.Value < sensor1.Min) {
      sensor1.Min = sensor1.Value;
    }

        if (sensor2.Value > sensor2.Max) {
      sensor2.Max = sensor2.Value;
    }

    if (sensor2.Value < sensor2.Min) {
      sensor2.Min = sensor2.Value;
    }


    if (sensor3.Value > sensor3.Max) {
      sensor3.Max = sensor3.Value;
    }

    if (sensor3.Value < sensor3.Min) {
      sensor3.Min = sensor3.Value;
    }


    if (sensor4.Value > sensor4.Max) {
      sensor4.Max = sensor4.Value;
    }

    if (sensor4.Value < sensor4.Min) {
      sensor4.Min = sensor4.Value;
    } 
  }
  
if((sensor1.Max - sensor1.Min) < 260 && (sensor2.Max - sensor2.Min) < 260 && (sensor3.Max - sensor3.Min) < 260 && (sensor4.Max - sensor4.Min) < 260){
sensor1.Min = sensor1.Min - 50;
sensor1.Max = sensor1.Max + 60;
sensor2.Min = sensor2.Min - 50;
sensor2.Max = sensor2.Max + 60;
sensor3.Min = sensor3.Min - 50;
sensor3.Max = sensor3.Max + 60;
sensor4.Min = sensor4.Min - 50;
sensor4.Max = sensor4.Max + 60;
startFlag = 1;
//saveData();
calibrationFlag = 0;
} else {
 sensor1.Min = sensor1.MinSave;
 sensor1.Max = sensor1.MaxSave; 
 sensor2.Min = sensor2.MinSave;
 sensor2.Max = sensor2.MaxSave; 
 sensor3.Min = sensor3.MinSave;
 sensor3.Max = sensor3.MaxSave; 
 sensor4.Min = sensor4.MinSave;
 sensor4.Max = sensor4.MaxSave; 
 calibrationFlag = 0;
}
}

void peaton(){
if(isPeatonPresent == false){
peatonTime.reset();
mp3_play (random(1, 7)); 
isPeatonPresent = true;
if(isNight == true){
  Serial.print('N');
  activateAnimation = true; 
  led.fade(255, FADE_TIME);
}
if(isNight == false){
  Serial.print('P');
  activateAnimation = false; 
} 
}
}

void loop(){
  led.update();
  sensor1.Value = sensor1.Average();
  sensor2.Value = sensor2.Average();
  sensor3.Value = sensor3.Average();
  sensor4.Value = sensor4.Average();

    if(peatonTime.check() == 1){
    isPeatonPresent = false;  
    led.fade(0, 2000);
}
  if(sensor1.Average() < sensor1.Min || sensor1.Average() > sensor1.Max || sensor2.Average() < sensor2.Min || sensor2.Average() > sensor2.Max || sensor3.Average() < sensor3.Min || sensor3.Average() > sensor3.Max || sensor4.Average() < sensor4.Min || sensor2.Average() > sensor2.Max && calibrationFlag == 2){
   peaton();
  }
  if(cintaTime.check() == 1 && jumpStart == 1 && isPeatonPresent == false) {
  patronCinta();
 }
  if(sensado.check() == 1 && isPeatonPresent == true) {
  patronCintaSensado();
 }

   if(animationTime.check() == 1 && isPeatonPresent == true && activateAnimation == true){
  caminar();      
  }

  if(parpadeoTime.check() == 1 && isPeatonPresent == true) {
  parpadeo(); 
 }

  if (Serial.available() > 0) {
 int inByte = Serial.read();
 switch (inByte) {
  
        case 'P': 
        peatonTime.reset();
        isPeatonPresent = true;
        if(isNight == true){
        led.fade(255, FADE_TIME); 
        activateAnimation == true;
        }
        break;

        case 'N': 
        peatonTime.reset();
        isPeatonPresent = true;
        led.fade(255, FADE_TIME); 
        activateAnimation == true;
        break;
      
        case 'S':
       coronaOn(); 
       jumpStart = 1;
       stand();
       stand_SEC();
        break;

       case 'W':
       coronaOn();  
       jumpStart = 1;
       break;

      case 'C':
      coronaOff(); 
      matriz_1.clear();
      matriz_2.clear();
      break;

      case 'H':
      isNight = true;
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
      break;

      case 'L':
      saveData();
      coronaOff();
      cintaOff();
    //  digitalWrite(transistorPin, HIGH);   // RESET
      break;

      case 'Z':
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
      break;
        
    }
  }
 
 DateTime now = RTC.now(); 
 uint8_t hora = now.hour();
 uint8_t minuto = now.minute();
 uint8_t segundo = now.second();
 uint8_t Dia = now.day();
 uint8_t mes = now.month();

if(hora == 4 && minuto == 30 && segundo < 10){
  Schedule();
}
 if(hora == horaDia && minuto == minutoDia && segundo < 10){
  isNight = false;
  cinta.setBrightness(255);
  corona.setBrightness(255);
 }
  if(hora == horaNoche && minuto == minutoNoche && segundo < 10){
  isNight = true;
  cinta.setBrightness(78);
  corona.setBrightness(78);
 }
}
void patronCinta(){
if(direccion == 1){
cinta.setPixelColor(currentPixel,currentColor);
cinta.setPixelColor(currentPixel-1,currentColor);
cinta.setPixelColor(currentPixel-2,currentColor);
cinta.setPixelColor(currentPixel-3,currentColor);
cinta.setPixelColor(currentPixel-4,currentColor);
cinta.setPixelColor(j,currentColor);
cinta.setPixelColor(j+1,currentColor);
cinta.setPixelColor(j+2,currentColor);
cinta.setPixelColor(j+3,currentColor);
cinta.setPixelColor(j+4,currentColor);
 } else if (direccion == 0){
cinta.setPixelColor(currentPixel,currentColor);
cinta.setPixelColor(currentPixel+1,currentColor);
cinta.setPixelColor(currentPixel+2,currentColor);
cinta.setPixelColor(currentPixel+3,currentColor);
cinta.setPixelColor(currentPixel+4,currentColor);
cinta.setPixelColor(j,currentColor);
cinta.setPixelColor(j-1,currentColor);
cinta.setPixelColor(j-2,currentColor);
cinta.setPixelColor(j-3,currentColor);
cinta.setPixelColor(j-4,currentColor);
  }
  cinta.show();
  cinta.setPixelColor(currentPixel,0,0,0);
  cinta.setPixelColor(j,0,0,0);
  if(direccion == 1){
  currentPixel--; 
  j++;
  } else if (direccion == 0){
  currentPixel++;
  j--;
  }
  if(currentPixel == 30){
    direccion = 1;
}
 if(currentPixel == 0){
    direccion = 0;
    j = 59;
    jumpStart =  0;
    cintaOff();
}
}

void cintaOff(){
for(int i = 0; i <= 60; i++){
cinta.setPixelColor(i,0,0,0);
}
cinta.show();
}
void patronCintaSensado(){
if(direccion == 1){
cinta.setPixelColor(currentPixel,currentColor);
cinta.setPixelColor(currentPixel-1,currentColor);
cinta.setPixelColor(currentPixel-2,currentColor);
cinta.setPixelColor(currentPixel-3,currentColor);
cinta.setPixelColor(currentPixel-4,currentColor);
cinta.setPixelColor(j,currentColor);
cinta.setPixelColor(j+1,currentColor);
cinta.setPixelColor(j+2,currentColor);
cinta.setPixelColor(j+3,currentColor);
cinta.setPixelColor(j+4,currentColor);
} else if (direccion == 0){
cinta.setPixelColor(currentPixel,currentColor);
cinta.setPixelColor(currentPixel+1,currentColor);
cinta.setPixelColor(currentPixel+2,currentColor);
cinta.setPixelColor(currentPixel+3,currentColor);
cinta.setPixelColor(currentPixel+4,currentColor);
cinta.setPixelColor(j,currentColor);
cinta.setPixelColor(j-1,currentColor);
cinta.setPixelColor(j-2,currentColor);
cinta.setPixelColor(j-3,currentColor);
cinta.setPixelColor(j-4,currentColor);
  }
  cinta.show();
  cinta.setPixelColor(currentPixel,0,0,0);
  cinta.setPixelColor(j,0,0,0);
  if(direccion == 1){
  currentPixel--; 
  j++;
  } else if (direccion == 0){
  currentPixel++;
  j--;
  }
  if(currentPixel == 30){
    direccion = 1;
}
 if(currentPixel == 0){
    direccion = 0;
    j = 59;
    jumpStart =  0;
    cintaOff();
}
}

void Schedule(){
 DateTime now = RTC.now(); 
 uint8_t hora = now.hour();
 uint8_t minuto = now.minute();
 uint8_t segundo = now.second();
 uint8_t Dia = now.day();
 uint8_t mes = now.month();
 //--------- CAMBIOS DIA - NOCHE---------------------------
 if(mes == 1){
 horaDia = 5;
 minutoDia = 14;
 horaNoche = 20;
 minutoNoche = 55;
 }

  if(mes == 2){
 horaDia = 5;
 minutoDia = 54;
 horaNoche = 20;
 minutoNoche = 32;
 }
 
  if(mes == 3){
 horaDia = 6;
 minutoDia = 22;
 horaNoche = 19;
 minutoNoche = 57;
 }

 if(mes == 4){
 horaDia = 6;
 minutoDia = 45;
 horaNoche = 19;
 minutoNoche = 17;
 }

  if(mes == 5){
 horaDia = 7;
 minutoDia = 4;
 horaNoche = 18;
 minutoNoche = 49;
 }


  if(mes == 6){
 horaDia = 7;
 minutoDia = 18;
 horaNoche = 18;
 minutoNoche = 43;
 }


  if(mes == 7){
 horaDia = 7;
 minutoDia = 16;
 horaNoche = 18;
 minutoNoche = 55;
 }


  if(mes == 8){
 horaDia = 6;
 minutoDia = 54;
 horaNoche = 19;
 minutoNoche = 17;
 }


  if(mes == 9){
 horaDia = 6;
 minutoDia = 15;
 horaNoche = 19;
 minutoNoche = 37;
 }

  if(mes == 10){
 horaDia = 5;
 minutoDia = 31;
 horaNoche = 19;
 minutoNoche = 58;
 }

  if(mes == 11){
 horaDia = 4;
 minutoDia = 54;
 horaNoche = 20;
 minutoNoche = 27;
 }

  if(mes == 12){
 horaDia = 4;
 minutoDia = 46;
 horaNoche = 20;
 minutoNoche = 51;
 }
}



void caminar(){
 if(currentFrame == 0){
 matriz_1.write(40, 0,  F0M1);
 matriz_1.write(32, 0,  F0M2);
 matriz_1.write(24, 0, F0M3);
 matriz_1.write(16, 0, F0M4);
 matriz_1.write(8, 0, F0M5);
 matriz_1.write(0, 0, F0M6); 
 }
 if(currentFrame == 1){
 matriz_1.write(40, 0,  F1M1);
 matriz_1.write(32, 0,  F1M2);
 matriz_1.write(24, 0, F1M3);
 matriz_1.write(16, 0, F1M4);
 matriz_1.write(8, 0, F1M5);
 matriz_1.write(0, 0, F1M6);
}
 if(currentFrame == 2){
 matriz_1.write(40, 0,  F2M1);
 matriz_1.write(32, 0,  F2M2);
 matriz_1.write(24, 0, F2M3);
 matriz_1.write(16, 0, F2M4);
 matriz_1.write(8, 0, F2M5);
 matriz_1.write(0, 0, F2M6);
}
 if(currentFrame == 3){
 matriz_1.write(40, 0,  F3M1);
 matriz_1.write(32, 0,  F3M2);
 matriz_1.write(24, 0, F3M3);
 matriz_1.write(16, 0, F3M4);
 matriz_1.write(8, 0, F3M5);
 matriz_1.write(0, 0, F3M6);
}
 if(currentFrame == 4){
 matriz_1.write(40, 0,  F4M1);
 matriz_1.write(32, 0,  F4M2);
 matriz_1.write(24, 0, F4M3);
 matriz_1.write(16, 0, F4M4);
 matriz_1.write(8, 0, F4M5);
 matriz_1.write(0, 0, F4M6);
}
 if(currentFrame == 5){
 matriz_1.write(40, 0,  F5M1);
 matriz_1.write(32, 0,  F5M2);
 matriz_1.write(24, 0, F5M3);
 matriz_1.write(16, 0, F5M4);
 matriz_1.write(8, 0, F5M5);
 matriz_1.write(0, 0, F5M6);
     }
 if(currentFrame == 6){
 matriz_1.write(40, 0,  F6M1);
 matriz_1.write(32, 0,  F6M2);
 matriz_1.write(24, 0, F6M3);
 matriz_1.write(16, 0, F6M4);
 matriz_1.write(8, 0, F6M5);
 matriz_1.write(0, 0, F6M6);
}
currentFrame++;
if(currentFrame == 6){
currentFrame = 0; 
}
}

void stand(){
 matriz_1.write(40, 0,   FSM1);
 matriz_1.write(32, 0,   FSM2);
 matriz_1.write(24, 0,  FSM3);
 matriz_1.write(16, 0,  FSM4);
 matriz_1.write(8, 0,  FSM5);
 matriz_1.write(0, 0,  FSM6);
}

void caminar_SEC(){
 if(currentFrame_SEC == 0){
 matriz_2.write(40, 0,  D0M1);
 matriz_2.write(32, 0,  D0M2);
 matriz_2.write(24, 0, D0M3);
 matriz_2.write(16, 0, D0M4);
 matriz_2.write(8, 0, D0M5);
 matriz_2.write(0, 0, D0M6); 
 }
 if(currentFrame_SEC == 1){
 matriz_2.write(40, 0,  D1M1);
 matriz_2.write(32, 0,  D1M2);
 matriz_2.write(24, 0, D1M3);
 matriz_2.write(16, 0, D1M4);
 matriz_2.write(8, 0, D1M5);
 matriz_2.write(0, 0, D1M6);
}
 if(currentFrame_SEC == 2){
 matriz_2.write(40, 0,  D2M1);
 matriz_2.write(32, 0,  D2M2);
 matriz_2.write(24, 0, D2M3);
 matriz_2.write(16, 0, D2M4);
 matriz_2.write(8, 0, D2M5);
 matriz_2.write(0, 0, D2M6);
}
 if(currentFrame_SEC == 3){
 matriz_2.write(40, 0,  D3M1);
 matriz_2.write(32, 0,  D3M2);
 matriz_2.write(24, 0, D3M3);
 matriz_2.write(16, 0, D3M4);
 matriz_2.write(8, 0, D3M5);
 matriz_2.write(0, 0, D3M6);
}
 if(currentFrame_SEC == 4){
 matriz_2.write(40, 0,  D4M1);
 matriz_2.write(32, 0,  D4M2);
 matriz_2.write(24, 0, D4M3);
 matriz_2.write(16, 0, D4M4);
 matriz_2.write(8, 0, D4M5);
 matriz_2.write(0, 0, D4M6);
}
 if(currentFrame_SEC == 5){
 matriz_2.write(40, 0,  D5M1);
 matriz_2.write(32, 0,  D5M2);
 matriz_2.write(24, 0, D5M3);
 matriz_2.write(16, 0, D5M4);
 matriz_2.write(8, 0, D5M5);
 matriz_2.write(0, 0, D5M6);
     }
 if(currentFrame_SEC == 6){
 matriz_2.write(40, 0,  D6M1);
 matriz_2.write(32, 0,  D6M2);
 matriz_2.write(24, 0, D6M3);
 matriz_2.write(16, 0, D6M4);
 matriz_2.write(8, 0, D6M5);
 matriz_2.write(0, 0, D6M6);
}
currentFrame_SEC++;
if(currentFrame_SEC == 6){
currentFrame_SEC = 0; 
}
}

void stand_SEC(){
 matriz_2.write(40, 0,   DSM1);
 matriz_2.write(32, 0,   DSM2);
 matriz_2.write(24, 0,  DSM3);
 matriz_2.write(16, 0,  DSM4);
 matriz_2.write(8, 0,  DSM5);
 matriz_2.write(0, 0,  DSM6);
 matriz_1.write(40, 0,   DSM1);
 matriz_1.write(32, 0,   DSM2);
 matriz_1.write(24, 0,  DSM3);
 matriz_1.write(16, 0,  DSM4);
 matriz_1.write(8, 0,  DSM5);
 matriz_1.write(0, 0,  DSM6);
}

void parpadeo(){
 estadoParpa = !estadoParpa;
 if(estadoParpa == false){
 coronaOn();
 }
 if(estadoParpa == true){
  coronaOff();
 }
}

void coronaOff(){
for(int i = 0; i <= 64; i++){
corona.setPixelColor(i,0,0,0);
}
corona.show();
}

void coronaOn(){
corona.setPixelColor(0,coronaColor);
corona.setPixelColor(1,0,0,0);
corona.setPixelColor(2,coronaColor);
corona.setPixelColor(3,0,0,0);
corona.setPixelColor(4,coronaColor);
corona.setPixelColor(5,0,0,0);
corona.setPixelColor(6,coronaColor);
corona.setPixelColor(7,0,0,0);
corona.setPixelColor(8,coronaColor);
corona.setPixelColor(9,0,0,0);
corona.setPixelColor(10,coronaColor);
corona.setPixelColor(11,0,0,0);
corona.setPixelColor(12,coronaColor);
corona.setPixelColor(13,0,0,0);
corona.setPixelColor(14,coronaColor);
corona.setPixelColor(15,0,0,0);
corona.setPixelColor(16,coronaColor);
corona.setPixelColor(17,0,0,0);
corona.setPixelColor(18,coronaColor);
corona.setPixelColor(19,0,0,0);
corona.setPixelColor(20,coronaColor);
corona.setPixelColor(21,0,0,0);
corona.setPixelColor(22,coronaColor);
corona.setPixelColor(23,0,0,0);
corona.setPixelColor(24,coronaColor);
corona.setPixelColor(25,0,0,0);
corona.setPixelColor(26,coronaColor);
corona.setPixelColor(27,0,0,0);
corona.setPixelColor(28,coronaColor);
corona.setPixelColor(29,0,0,0);
corona.setPixelColor(30,coronaColor);
corona.setPixelColor(31,0,0,0);
corona.setPixelColor(32,coronaColor);
corona.setPixelColor(33,0,0,0);
corona.setPixelColor(34,coronaColor);
corona.setPixelColor(35,0,0,0);
corona.setPixelColor(36,coronaColor);
corona.setPixelColor(37,0,0,0);
corona.setPixelColor(38,coronaColor);
corona.setPixelColor(39,0,0,0);
corona.setPixelColor(40,coronaColor);
corona.setPixelColor(41,0,0,0);
corona.setPixelColor(42,coronaColor);
corona.setPixelColor(43,0,0,0);
corona.setPixelColor(44,coronaColor);
corona.setPixelColor(45,0,0,0);
corona.setPixelColor(46,coronaColor);
corona.setPixelColor(47,0,0,0);
corona.setPixelColor(48,coronaColor);
corona.setPixelColor(49,0,0,0);
corona.setPixelColor(50,coronaColor);
corona.setPixelColor(51,0,0,0);
corona.setPixelColor(52,coronaColor);
corona.setPixelColor(53,0,0,0);
corona.setPixelColor(54,coronaColor);
corona.setPixelColor(55,0,0,0);
corona.setPixelColor(56,coronaColor);
corona.setPixelColor(57,0,0,0);
corona.setPixelColor(58,coronaColor);
corona.setPixelColor(59,0,0,0);
corona.setPixelColor(60,coronaColor);
corona.setPixelColor(61,0,0,0);
corona.setPixelColor(62,coronaColor);
corona.setPixelColor(63,0,0,0);
corona.setPixelColor(64,coronaColor);
corona.show();
}



////////////////////////////////////////////////////////////////////
//  @company :  CleanVolage                                       //
//  @author : Diego Pandolfa                                      //
//  @date : January 10, 2018                                      //
//  @proyect  : Zebras                                            //
//  @description  : Firmware desarrollado para el zebra TX        //
//                  que envia los mensajes de sincronización      //
////////////////////////////////////////////////////////////////////
//coronas y cintas
//#include <Adafruit_NeoPixel.h>
#include <FastLED.h>
#include <Metro.h>
#include <Wire.h>
#include <RTClib.h>
#include <SoftwareSerial.h>

FASTLED_USING_NAMESPACE
#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64

//Matriz y mp3
#include <Sprite.h>  
#include <Matrix.h>
#include <DFPlayer_Mini_Mp3.h> 
#include <LEDFader.h>

// matrix principal
#define LED_PIN 35 //luminaria
#define FADE_TIME 4000

LEDFader led;
Matrix myLeds = Matrix(2, 3, 4, 6); // matriz 1
Metro animationTime = Metro(100);


RTC_DS1307 RTC;
Metro cintaTime = Metro(22);
Metro coroOff = Metro(650);
Metro coroOn = Metro(1650);
Metro parpadeo = Metro(300);
Metro sensado = Metro(10);
Metro peatonTime = Metro(15000);

const int interrupt_pin_sensor = 12;

//matrix principal
const int numChips = 6;
uint16_t currentFrame = 0;

#define NUM_PIXELS_CINTAS 60
uint32_t currentColor_cintas;
uint32_t coronaColor;
uint16_t currentPixel_cintas_maestro = 0;
int direccion_cintas_maestro = 0;
int j_cintas_maestro = 59; 
int transistorPin_reset_maestro = 11;
uint16_t jumpStart_maestro = 1;
uint16_t coroLimit_maestro = 0;
bool isPeatonPresent = false;
bool isNight = false;
bool estadoParpa_corona = false;

Adafruit_NeoPixel cinta = Adafruit_NeoPixel(NUM_PIXELS_CINTAS, 36, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel corona = Adafruit_NeoPixel(64, 37, NEO_GRB + NEO_KHZ800);

/////////////////matriz principal
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
///////////////////////////

void setup() {
  Serial1.begin(115200);
  while(!Serial1);
  Wire.begin();             
  RTC.begin();
  pinMode(transistorPin_reset_maestro, OUTPUT);
  pinMode(interrupt_pin_sensor, INPUT_PULLUP);/////////////////// <------------------sensor con interrupcion
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_sensor), reset_timer_rutine, FALLING); // cantos de bajada
  if (! RTC.isrunning()) {                       
  Serial1.println("RTC is NOT running!");
  }
  //matriz principal
  myLeds.clear();
  Serial4.begin(9600);
  mp3_set_serial ( Serial4 );   
  delay(1);                     
  mp3_set_volume (30); 
  myLeds.setBrightness(8); 
  led = LEDFader(LED_PIN);
  
  currentColor_cintas = cinta.Color(255,70,0);
  coronaColor = corona.Color(255,70,0);
  currentPixel_cintas_maestro = 0;
  cinta.begin();
  cinta.show();
  corona.begin();
  corona.show();
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
    currentColor_cintas = cinta.Color(255,48,0);
    coronaColor = corona.Color(255,48,0);
  }
  else {
    isNight = true;
    cinta.setBrightness(78);
    corona.setBrightness(78);
    currentColor_cintas = cinta.Color(255,48,0);
    coronaColor = corona.Color(255,48,0);
  }
}

void reset_timer_rutine(){
  peatonTime.reset();
  if(isPeatonPresent == false){
    isPeatonPresent = true;
    if(isNight == true){
      Serial1.print('P');
      mp3_play (random(1, 7));
    }
    if(isNight == false){
      Serial1.print('P');
      mp3_play (random(1, 7));
      led.fade(255, FADE_TIME);
    } 
  }
  else{
    //peatonTime.reset();
    Serial1.print('O');
    
    
  }
}

void loop(){
  DateTime now = RTC.now(); 
  uint8_t hora = now.hour();
  uint8_t minuto = now.minute();
  uint8_t segundo = now.second();
  uint8_t Dia = now.day();
  uint8_t mes = now.month();

 //--------- CAMBIOS DIA - NOCHE---------------------------

  if(mes == 1){
  //---------------DIA------------------------------
    if(hora == 5 && minuto == 14 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 20 && minuto == 55 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 2){
  //---------------DIA------------------------------
    if(hora == 5 && minuto == 54 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 20 && minuto == 32 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 3){
  //---------------DIA------------------------------
    if(hora == 6 && minuto == 22 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 19 && minuto == 57 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 4){
  //---------------DIA------------------------------
    if(hora == 6 && minuto == 45 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 19 && minuto == 17 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 5){
  //---------------DIA------------------------------
    if(hora == 7 && minuto == 4 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 18 && minuto == 49 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 6){
  //---------------DIA------------------------------
    if(hora == 7 && minuto == 18 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 18 && minuto == 43 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 7){
  //---------------DIA------------------------------
    if(hora == 7 && minuto == 16 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 18 && minuto == 55 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 8){
  //---------------DIA------------------------------
    if(hora == 6 && minuto == 54 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 19 && minuto == 17 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 9){
  //---------------DIA------------------------------
    if(hora == 6 && minuto == 15 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 19 && minuto == 37 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 10){
  //---------------DIA------------------------------
    if(hora == 5 && minuto == 31 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 19 && minuto == 58 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

  if(mes == 11){
  //---------------DIA------------------------------
    if(hora == 4 && minuto == 54 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 20 && minuto == 27 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }
  if(mes == 12){
  //---------------DIA------------------------------
    if(hora == 4 && minuto == 46 && segundo < 10){
      isNight = false; 
      Serial1.print('Z'); 
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //----------------NOCHE---------------------------
    if(hora == 20 && minuto == 51 && segundo < 10){
      isNight = true;
      Serial1.print('H');
      cinta.setBrightness(78);
      corona.setBrightness(78);
      currentColor_cintas = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
    }
 //------------------------------------------------
  }

 //------------------HORA DEL RESET------------------------
  if(hora == 4 && minuto == 30 && segundo < 1){
    Serial1.print('L');
    digitalWrite(transistorPin_reset_maestro, HIGH);
  }
  
  if(minuto == 1 && segundo < 1){
    Serial1.print('L');  
    coronaOff();
    cintaOff();
    digitalWrite(transistorPin_reset_maestro, HIGH); 
  }

  if(peatonTime.check() == 1){
    isPeatonPresent = false;  
  }

  //////////////////////////////////// matriz principal
  led.update();
  if (peatonTime.check() == 1) {
    isPeatonPresent = false;
    led.fade(0, 2000);
  }
  if(isNight == true){
    if(animationTime.check() == 1 && isPeatonPresent == true){
      caminar();      
    }
  }
  //////////////////////////////////////////
  
  if(cintaTime.check() == 1 && jumpStart_maestro == 1 && isPeatonPresent == false) {
    patronCinta();
  }
  
  if(sensado.check() == 1 && isPeatonPresent == true) {
    patronCintaSensado();
  }

  if(parpadeo.check() == 1 && isPeatonPresent == true) {
    if(isNight == true){
      parpadeaNoche(); 
    }
    if(isNight == false){
      parpadeaDia(); 
    }
  }
 
  if (coroOn.check() == 1 && isPeatonPresent == false && coroLimit_maestro == 1) {
    if(isNight == true){
      coronaNoche(); 
      
      
      Serial1.print('S');
    }
    if(isNight == false){
      coronaNoche();
      Serial1.print('W');
      
      
    }
    jumpStart_maestro = 1; 
    coroOff.reset();
    coroLimit_maestro = 0;
  }
  if (coroOff.check() == 1 && isPeatonPresent == false && coroLimit_maestro == 0) {
    coronaOff(); 
    
    
    Serial1.print('C');
    coroOn.reset();
    coroLimit_maestro = 1; 
  }
  if (Serial1.available() > 0) {
    int inByte = Serial1.read();
    switch (inByte) {
      case 'P':
        if(isNight == true){
          
           
        }
        peatonTime.reset();
        isPeatonPresent = true;
      break;

      case 'O':
        peatonTime.reset();
        isPeatonPresent = true;
        if(isNight == true){
          
           
        }
      break;
    }
  }
}

void patronCinta(){
  if(direccion_cintas_maestro == 1){
    cinta.setPixelColor(currentPixel_cintas_maestro,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro-1,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro-2,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro-3,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro-4,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro+1,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro+2,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro+3,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro+4,currentColor_cintas);
  }
  else if (direccion_cintas_maestro == 0){
    cinta.setPixelColor(currentPixel_cintas_maestro,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro+1,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro+2,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro+3,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro+4,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro-1,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro-2,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro-3,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro-4,currentColor_cintas);
  }
  cinta.show();
  cinta.setPixelColor(currentPixel_cintas_maestro,0,0,0);
  cinta.setPixelColor(j_cintas_maestro,0,0,0);
  if(direccion_cintas_maestro == 1){
    currentPixel_cintas_maestro--; 
    j_cintas_maestro++;
  }
  else if (direccion_cintas_maestro == 0){
    currentPixel_cintas_maestro++;
    j_cintas_maestro--;
  }
  if(currentPixel_cintas_maestro == 30){
    direccion_cintas_maestro = 1;
  }
  if(currentPixel_cintas_maestro == 0){
    direccion_cintas_maestro = 0;
    j_cintas_maestro = 59;
    jumpStart_maestro =  0;
    cintaOff();
  }
}

void patronCintaSensado(){
  if(direccion_cintas_maestro == 1){
    cinta.setPixelColor(currentPixel_cintas_maestro,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro-1,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro-2,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro-3,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro-4,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro+1,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro+2,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro+3,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro+4,currentColor_cintas);
  }
  else if (direccion_cintas_maestro == 0){
    cinta.setPixelColor(currentPixel_cintas_maestro,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro+1,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro+2,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro+3,currentColor_cintas);
    cinta.setPixelColor(currentPixel_cintas_maestro+4,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro-1,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro-2,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro-3,currentColor_cintas);
    cinta.setPixelColor(j_cintas_maestro-4,currentColor_cintas);
  }
  cinta.show();
  cinta.setPixelColor(currentPixel_cintas_maestro,0,0,0);
  cinta.setPixelColor(j_cintas_maestro,0,0,0);
  if(direccion_cintas_maestro == 1){
    currentPixel_cintas_maestro--; 
    j_cintas_maestro++;
  }
  else if (direccion_cintas_maestro == 0){
    currentPixel_cintas_maestro++;
    j_cintas_maestro--;
  }
  if(currentPixel_cintas_maestro == 30){
    direccion_cintas_maestro = 1;
  }
  if(currentPixel_cintas_maestro == 0){
    direccion_cintas_maestro = 0;
    j_cintas_maestro = 59;
    jumpStart_maestro =  0;
    cintaOff();
  }
}

void cintaOff(){
  for(int i = 0; i <= 60; i++){
    cinta.setPixelColor(i,0,0,0);
  }
  cinta.show();
}

void coronaOn(){
  for(int i = 0; i <= 64; i++){
    corona.setPixelColor(i,coronaColor);
  }
  corona.show();
}

void coronaOff(){
  for(int i = 0; i <= 64; i++){
    corona.setPixelColor(i,0,0,0);
  }
  corona.show();
}

void coronaNoche(){
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

void parpadeaDia(){
  estadoParpa_corona = !estadoParpa_corona;
  if(estadoParpa_corona == false){
    coronaNoche();
  }
  if(estadoParpa_corona == true){
    coronaOff();
  }
}

void parpadeaNoche(){
  estadoParpa_corona = !estadoParpa_corona;
  if(estadoParpa_corona == false){
    coronaNoche();
    stand();
  }
  if(estadoParpa_corona == true){
    coronaOff();
    myLeds.clear();
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

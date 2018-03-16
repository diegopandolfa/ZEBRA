////////////////////////////////////////////////////////////////////
//  @company :  CleanVolage                                       //
//  @author : Diego Pandolfa                                      //
//  @date : January 10, 2018                                      //
//  @proyect  : Zebras                                            //
//  @description  : Firmware desarrollado para el uC que controla //
//                  tanto el panel e1 como el mp3                 //
////////////////////////////////////////////////////////////////////
#include<FastLED.h>
#include<Metro.h>

#include <Sprite.h>  
#include <Matrix.h>

#include <DFPlayer_Mini_Mp3.h> 

#define TIME_STAND_BY_RUTINE 2000
#define TIME_DETECTED_RUTINE 700
#define TIME_PEATON 15000 // 15 segundos

///////////// ----- Macros Cintas ------------///////////////
#define PIN_CINTAS 36
#define NUM_PIX_CINTAS 60
#define FRAME_TIME_CINTAS_STAND_BY 10
#define FRAME_TIME_CINTAS_DETECTED 10
#define FADE_TIME_CINTAS 50
#define HUE_CINTAS 10
///////////////--------Fin Cintas ---------//////////////////

///////////// ----- Macros Coronass ------------///////////////
#define PIN_CORONAS 37
#define NUM_PIX_CORONAS 64
#define FRAME_TIME_CORONAS_STAND_BY 300
#define FRAME_TIME_CORONAS_DETECTED 250
#define HUE_CORONAS 10
bool patron_coronas = false;
bool flag_cintas_fin = false;
///////////////--------Fin Coronas ---------//////////////////

/////////////---- Matriz Principal ----------------////////////
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

Sprite MPF0M1 = Sprite(8, 8,   
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111,
B11111111
);

Sprite MPF0M2 = Sprite(8, 8,   
B01101111,
B00001111,
B00000111,
B00000011,
B00000000,
B00000000,
B00000000,
B00000000
);
Sprite MPF0M3 = Sprite(8, 8,   
B00000000,
B00000000,
B00011000,
B00011000,
B00110000,
B11100011,
B11111111,
B11111100
);

Sprite MPF0M4 = Sprite(8, 8,   
B11111111,
B11111111,
B10000000,
B10000000,
B11000000,
B11110000,
B00110000,
B00000000
);
Sprite MPF0M5 = Sprite(8, 8,   
B00000000,
B00000011,
B00000011,
B00111111,
B11111111,
B11100000,
B10000000,
B00000000
);

Sprite MPF0M6 = Sprite(8, 8,   
B10000000,
B11000000,
B01110011,
B00111111,
B00001111,
B00000011,
B00000000,
B00000000
);


Sprite MPF1M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110000,
B11111111,
B11111111
);
Sprite MPF1M2 = Sprite(8, 8, 
B01101111,
B00000111,
B00000011,
B00000001,
B00000000,
B00000000,
B00000000,
B00000000
);
Sprite MPF1M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00011000,
B00011000,
B00110000,
B11110111,
B11111111
);

Sprite MPF1M4 = Sprite(8, 8, 
B11111111,
B11111111,
B11111110,
B11110000,
B00111000,
B00011000,
B00000000,
B00000000
);
Sprite MPF1M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000011,
B00000011,
B00001111,
B01111110,
B11110000,
B11000000
);
Sprite MPF1M6 = Sprite(8, 8, 
B11110000,
B11111000,
B00011000,
B00011011,
B00011111,
B00001110,
B00000000,
B00000000
);

Sprite MPF2M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111
);
Sprite MPF2M2 = Sprite(8, 8, 
B11111111,
B01100111,
B00000011,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000
);

Sprite MPF2M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00001100,
B00011100,
B11111111,
B11111111
);

Sprite MPF2M4 = Sprite(8, 8, 
B11111111,
B11111111,
B11111100,
B00001100,
B00000000,
B00000000,
B00000000,
B00000000
);

Sprite MPF2M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000011,
B11000011,
B11111111,
B11111111
);

Sprite MPF2M6 = Sprite(8, 8, 
B11111000,
B00011000,
B00011110,
B00011110,
B00000000,
B00000000,
B00000000,
B00000000
);

Sprite MPF3M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111
);

Sprite MPF3M2 = Sprite(8, 8, 
B11111111,
B01100111,
B00000011,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000
);

Sprite MPF3M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000001,
B00011101,
B11111111,
B11111111
);

Sprite MPF3M4 = Sprite(8, 8, 
B11111111,
B11111110,
B11110000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000
);

Sprite MPF3M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B11000000,
B11100000,
B11101100,
B11111111,
B11111011
);

Sprite MPF3M6 = Sprite(8, 8, 
B11111111,
B00011111,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000
);

Sprite MPF4M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111
);

Sprite MPF4M2 = Sprite(8, 8, 
B11111111,
B01101111,
B00000111,
B00000011,
B00000000,
B00000000,
B00000000,
B00000000
);

Sprite MPF4M3 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00001101,
B11111111,
B11111111
);

Sprite MPF4M4 = Sprite(8, 8, 
B11111111,
B11111111,
B11111110,
B11110000,
B11100000,
B00000000,
B00000000,
B00000000
);

Sprite MPF4M5 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00001100,
B11101100,
B11111100,
B11111000,
B10000000
);

Sprite MPF4M6 = Sprite(8, 8, 
B11110000,
B11111011,
B00011111,
B00001111,
B00000110,
B00000000,
B00000000,
B00000000
);

Sprite MPF5M1 = Sprite(8, 8, 
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111,
B11111111
);

Sprite MPF5M2 = Sprite(8, 8,
B01101111,
B00001111,
B00000111,
B00000011,
B00000001,
B00000000,
B00000000,
B00000000
);

Sprite MPF5M3 = Sprite(8, 8,
B00000000,
B00000000,
B00001000,
B00011100,
B01111000,
B11100001,
B11111111,
B11111111
);

Sprite MPF5M4 = Sprite(8, 8,
B11111111,
B11111111,
B11111110,
B10000000,
B10000000,
B01111000,
B01111000,
B00000000
);

Sprite MPF5M5 = Sprite(8, 8,
B00000000,
B00000110,
B00000110,
B01111110,
B11111100,
B11000000,
B10000000,
B10000000
);

Sprite MPF5M6 = Sprite(8, 8,
B11110000,
B11111000,
B00011011,
B00001111,
B00000111,
B00000011,
B00000000,
B00000000
);

Sprite MPF6M1 = Sprite(8, 8,
B00000000,
B00000000,
B00000000,
B00000000,
B01100000,
B11110111,
B11111111,
B11111111
);

Sprite MPF6M2 = Sprite(8, 8,
B01101111,
B00001111,
B00000111,
B00000011,
B00000001,
B00000000,
B00000000,
B00000000
);

Sprite MPF6M3 = Sprite(8, 8,
B00000000,
B00000000,
B00011000,
B00111000,
B01110000,
B11100001,
B11111111,
B11111111
);

Sprite MPF6M4 = Sprite(8, 8,
B11111111,
B11111111,
B11111111,
B10000000,
B11000000,
B11111000,
B00111000,
B00000000
);

Sprite MPF6M5 = Sprite(8, 8,
B00000000,
B00000011,
B00000011,
B01111111,
B11111111,
B11000000,
B10000000,
B00000000
);

Sprite MPF6M6 = Sprite(8, 8,
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
#define MP_DIN 2
#define MP_CLK 3
#define MP_LD 4
#define NUM_CHIPS_MAX 6
#define FRAME_TIME_MATRIX 100

Matrix matrix_principal = Matrix(MP_DIN, MP_CLK, MP_LD, NUM_CHIPS_MAX);
Metro TimeOfFrameMatrix = Metro(FRAME_TIME_MATRIX);
int currentFrameMatrixPrincipal = 0;
/////////////----Fin Matriz Principal -------------////////////

// ---------------- Cintas y Coronas --------------//
CRGBArray<NUM_PIX_CINTAS> cintas;
CRGBArray<NUM_PIX_CORONAS> coronas;

Metro TimeStandByRutine = Metro(TIME_STAND_BY_RUTINE);

Metro TimeOfFrameCintas = Metro(FRAME_TIME_CINTAS_STAND_BY);

Metro TimeOfFrameCoronas = Metro(FRAME_TIME_CORONAS_STAND_BY);

int currentFrameCintas = 0;
//---------------Fin Cintas y Coronas ---------------//

Metro TimeOfPeaton = Metro(TIME_PEATON);

bool time_rutine_stand_by = true;
volatile bool peatonIsPresent = false;

int resetPin = 11; // base de un transistor.
int interrupt_pin_sensor = 12;

void setup() {
  FastLED.addLeds<NEOPIXEL,PIN_CINTAS>(cintas, NUM_PIX_CINTAS);
  FastLED.addLeds<NEOPIXEL,PIN_CORONAS>(coronas, NUM_PIX_CORONAS);
  matrix_principal.clear();
  matrix_principal.setBrightness(8);
  pinMode(resetPin, OUTPUT);
  pinMode(interrupt_pin_sensor, INPUT_PULLUP);/////////////////// <------------------sensor con interrupcion
  attachInterrupt(digitalPinToInterrupt(interrupt_pin_sensor), interruptServiceRoutine, FALLING); // cantos de bajada
}

//----------Rutina de interrupción para el sensor-------//
void interruptServiceRoutine(){
  TimeOfPeaton.reset();
  if(peatonIsPresent == false){
    TimeOfFrameMatrix.reset();
    TimeStandByRutine.reset();
    TimeStandByRutine.interval(TIME_DETECTED_RUTINE);
    peatonIsPresent = true;
  }
}

void loop(){
  if(peatonIsPresent){
    if(TimeOfFrameMatrix.check() == 1){
      patternWalk();
    }
    if(TimeStandByRutine.check() == 1){
      time_rutine_stand_by = true;
    }
    if(TimeOfFrameCintas.check() == 1){
      patternCintas();   
    }
    if(TimeOfFrameCoronas.check() == 1){
      patternCoronasOff();
    }
    if(flag_cintas_fin){
      TimeOfFrameCoronas.reset();
      flag_cintas_fin = false;
      patternCoronasOn();
    }
    if(TimeOfPeaton.check() == 1){
      peatonIsPresent = false;
      TimeStandByRutine.reset();
      TimeStandByRutine.interval(TIME_STAND_BY_RUTINE);
    }
  }
  else{
    if(TimeStandByRutine.check() == 1){
      time_rutine_stand_by = true;
    }
    if(TimeOfFrameCintas.check() == 1){
      patternCintas();   
    }
    if(TimeOfFrameCoronas.check() == 1){
      patternCoronasOff();
      matrix_principal.clear();
    }
    if(flag_cintas_fin){
      TimeOfFrameCoronas.reset();
      flag_cintas_fin = false;
      patternStandBy();
      patternCoronasOn();
    }
  }
  FastLED.show();
}

void patternCintas(){
  if(currentFrameCintas >= NUM_PIX_CINTAS){
    currentFrameCintas = 0;
    time_rutine_stand_by = false;
  }
  cintas.fadeToBlackBy(FADE_TIME_CINTAS);
  if(time_rutine_stand_by){
    if(currentFrameCintas < NUM_PIX_CINTAS/2){
      // let's set an led value
      cintas[currentFrameCintas] = CHSV(HUE_CINTAS,255,255);
    }
    else{
      // let's set an led value
      if(currentFrameCintas == NUM_PIX_CINTAS-2)
        flag_cintas_fin = true;
      cintas[NUM_PIX_CINTAS-1 - currentFrameCintas] = CHSV(HUE_CINTAS,255,255);
    }
    cintas(NUM_PIX_CINTAS/2,NUM_PIX_CINTAS-1) = cintas(NUM_PIX_CINTAS/2 - 1 ,0);
    currentFrameCintas++;
  }
}

void patternCoronasOn(){
  for(int i=0; i<NUM_PIX_CORONAS; i++){
    if(patron_coronas == false){
      if( (i%2) == 0 ){
        coronas[i] = CHSV(HUE_CORONAS,255,255);  
      }
      else{
        coronas[i] = CHSV(HUE_CORONAS,255,0);
      }
    }
    else if(patron_coronas == true){
      if( ((i+1)%2) == 0){
        coronas[i] = CHSV(HUE_CORONAS,255,255); 
      }
      else{
        coronas[i] = CHSV(HUE_CORONAS,255,0);
      }
    }
  }
  patron_coronas = !(patron_coronas);
}

void patternCoronasOff(){
  for(int i=0; i<NUM_PIX_CORONAS; i++){
    coronas[i] = CHSV(HUE_CORONAS,255,0);
  }
}

void patternWalk(){
  if(currentFrameMatrixPrincipal == 0){
    matrix_principal.write(40, 0,  MPF0M1);
    matrix_principal.write(32, 0,  MPF0M2);
    matrix_principal.write(24, 0, MPF0M3);
    matrix_principal.write(16, 0, MPF0M4);
    matrix_principal.write(8, 0, MPF0M5);
    matrix_principal.write(0, 0, MPF0M6); 
  }
  if(currentFrameMatrixPrincipal == 1){
    matrix_principal.write(40, 0,  MPF1M1);
    matrix_principal.write(32, 0,  MPF1M2);
    matrix_principal.write(24, 0, MPF1M3);
    matrix_principal.write(16, 0, MPF1M4);
    matrix_principal.write(8, 0, MPF1M5);
    matrix_principal.write(0, 0, MPF1M6);
  }
  if(currentFrameMatrixPrincipal == 2){
    matrix_principal.write(40, 0,  MPF2M1);
    matrix_principal.write(32, 0,  MPF2M2);
    matrix_principal.write(24, 0, MPF2M3);
    matrix_principal.write(16, 0, MPF2M4);
    matrix_principal.write(8, 0, MPF2M5);
    matrix_principal.write(0, 0, MPF2M6);
  }
  if(currentFrameMatrixPrincipal == 3){
    matrix_principal.write(40, 0,  MPF3M1);
    matrix_principal.write(32, 0,  MPF3M2);
    matrix_principal.write(24, 0, MPF3M3);
    matrix_principal.write(16, 0, MPF3M4);
    matrix_principal.write(8, 0, MPF3M5);
    matrix_principal.write(0, 0, MPF3M6);
  }
  if(currentFrameMatrixPrincipal == 4){
    matrix_principal.write(40, 0,  MPF4M1);
    matrix_principal.write(32, 0,  MPF4M2);
    matrix_principal.write(24, 0, MPF4M3);
    matrix_principal.write(16, 0, MPF4M4);
    matrix_principal.write(8, 0, MPF4M5);
    matrix_principal.write(0, 0, MPF4M6);
  }
  if(currentFrameMatrixPrincipal == 5){
    matrix_principal.write(40, 0,  MPF5M1);
    matrix_principal.write(32, 0,  MPF5M2);
    matrix_principal.write(24, 0, MPF5M3);
    matrix_principal.write(16, 0, MPF5M4);
    matrix_principal.write(8, 0, MPF5M5);
    matrix_principal.write(0, 0, MPF5M6);
  }
  if(currentFrameMatrixPrincipal == 6){
    matrix_principal.write(40, 0,  MPF6M1);
    matrix_principal.write(32, 0,  MPF6M2);
    matrix_principal.write(24, 0, MPF6M3);
    matrix_principal.write(16, 0, MPF6M4);
    matrix_principal.write(8, 0, MPF6M5);
    matrix_principal.write(0, 0, MPF6M6);
  }
  currentFrameMatrixPrincipal++;
  if(currentFrameMatrixPrincipal > 6){
    currentFrameMatrixPrincipal = 0;
  }
}

void patternStandBy(){
  matrix_principal.write(40, 0,   FSM1);
  matrix_principal.write(32, 0,   FSM2);
  matrix_principal.write(24, 0,  FSM3);
  matrix_principal.write(16, 0,  FSM4);
  matrix_principal.write(8, 0,  FSM5);
  matrix_principal.write(0, 0,  FSM6);
}

void patternOK(){
  matrix_principal.write(24, 0,  M1);
  matrix_principal.write(16, 0,  M2);
}

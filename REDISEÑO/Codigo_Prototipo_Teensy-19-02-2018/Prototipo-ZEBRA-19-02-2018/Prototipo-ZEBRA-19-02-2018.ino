#include<FastLED.h>
#include<Metro.h>

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
bool flag_cintas_medio = false;
///////////////--------Fin Coronas ---------//////////////////

CRGBArray<NUM_PIX_CINTAS> cintas;
CRGBArray<NUM_PIX_CORONAS> coronas;

Metro TimeStandByRutine = Metro(TIME_STAND_BY_RUTINE);

Metro TimeOfFrameCintas = Metro(FRAME_TIME_CINTAS_STAND_BY);

Metro TimeOfFrameCoronas = Metro(FRAME_TIME_CORONAS_STAND_BY);

int currentFrameCintas = 0;
bool time_rutine_stand_by = true;

void setup() {
  FastLED.addLeds<NEOPIXEL,PIN_CINTAS>(cintas, NUM_PIX_CINTAS);
  FastLED.addLeds<NEOPIXEL,PIN_CORONAS>(coronas, NUM_PIX_CORONAS);
}

void loop(){
  if(TimeStandByRutine.check() == 1){
    time_rutine_stand_by = true;
  }
  if(TimeOfFrameCintas.check() == 1){
    patternCintas();   
  }
  if(TimeOfFrameCoronas.check() == 1){
    patternCoronasOff();
  }
  if(flag_cintas_medio){
    TimeOfFrameCoronas.reset();
    flag_cintas_medio = false;
    patternCoronasOn();
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
      if(currentFrameCintas == NUM_PIX_CINTAS/2-5)
        flag_cintas_medio = true;
    }
    else{
      // let's set an led value
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

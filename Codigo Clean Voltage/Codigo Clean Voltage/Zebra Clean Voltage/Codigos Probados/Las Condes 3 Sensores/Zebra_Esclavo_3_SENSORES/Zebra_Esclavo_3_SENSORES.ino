#include <Adafruit_NeoPixel.h>
#include <Metro.h>
#include <Wire.h>
#include <RTClib.h>
#include <SoftwareSerial.h>  
#include <EEPROM.h>
const int ANALOG_PIN = A0;
SoftwareSerial panel1(7, 8);
SoftwareSerial panel2(9, 10);
RTC_DS1307 RTC;
Metro cintaTime = Metro(22);
Metro coroOff = Metro(650);
Metro coroOn = Metro(1650);
Metro parpadeo = Metro(300);
Metro sensado = Metro(10);
Metro peatonTime = Metro(15000);
Metro muestreo = Metro(5);
Metro calibration = Metro(10);
Metro resetCalib = Metro(1000);
Metro newcalib = Metro(2000);
Metro boton = Metro(1000);
Metro defaultState = Metro(60000);
#define NUM_PIXELS 60
uint32_t currentColor;
uint32_t coronaColor;
uint16_t currentPixel = 0;
int buttonState = 0; 
const int  buttonPin = 3; 
int direccion = 0;
int j = 59; 
int err = 0;
int transistorPin = 2;
int startFlag = 0;
uint16_t jumpStart = 1;
uint16_t jumpStartS = 0;
uint16_t coroLimit = 0;
bool isPeatonPresent = false;
bool isNight = false;
bool estadoParpa = false;
int calibrationFlag = 0;
int request = 0;
int buttonPushCounter = 0;
//Sensor Variables Readings
int sensorMin = 1023;        
int sensorMax = 0;
int sensorMinS = 1023;   // valor guardado     
int sensorMaxS = 0;      // valor guardado
int sensorValue = 0;  
int sensorMinB = 260;      // respaldo calibracion  
int sensorMaxB = 570;      // respaldo calibracion 


  //Sensor Variables Readings
int sensorMin_TWO = 1023;        
int sensorMax_TWO = 0;
int sensorMinS_TWO = 1023;        
int sensorMaxS_TWO = 0;     
int sensorValue_TWO = 0;  
int sensorMinB_TWO = 260;      
int sensorMaxB_TWO = 570;  


//Sensor Variables Readings
int sensorMin_THREE = 1023;        
int sensorMax_THREE = 0;
int sensorMinS_THREE = 1023;        
int sensorMaxS_THREE = 0;     
int sensorValue_THREE = 0;  
int sensorMinB_THREE = 260;      
int sensorMaxB_THREE = 570;  

Adafruit_NeoPixel cinta = Adafruit_NeoPixel(NUM_PIXELS, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel corona = Adafruit_NeoPixel(64, 5, NEO_GRB + NEO_KHZ800);

void setup() {
  Wire.begin();             
  RTC.begin();
  pinMode(transistorPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  err = 0;
  if (! RTC.isrunning()) {                       
  Serial.println("RTC is NOT running!");
  } 
  Serial.begin(115200); 
  panel1.begin(9600);
  panel2.begin(9600);
  currentColor = cinta.Color(255,70,0);
  coronaColor = corona.Color(255,70,0);
  currentPixel = 0;
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
   // Serial.println("hay datos");
   } else {
   calibracionSetup();
   }
}

int sensorPromedio(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A0);
  }  
  return(suma/n);
}

int sensorPromedio_TWO(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A1);
  }  
  return(suma/n);
}

int sensorPromedio_THREE(int n)
{
  long suma=0;
  for(int i=0;i<n;i++)
  {
    suma=suma+analogRead(A2);
  }  
  return(suma/n);
}

void saveData(){
int eeAddress = 0;  
sensorMinS = sensorMin;
sensorMinS_TWO = sensorMin_TWO;
sensorMin_THREE = sensorMin_THREE;
EEPROM.put(eeAddress, sensorMinS); 
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensorMinS_TWO); 
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensorMinS_THREE); 
eeAddress += sizeof(int);
sensorMaxS = sensorMax; 
sensorMaxS_TWO = sensorMax_TWO;
sensorMaxS_THREE = sensorMax_THREE;
EEPROM.put(eeAddress, sensorMaxS);
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensorMaxS_TWO);
eeAddress += sizeof(int);
EEPROM.put(eeAddress, sensorMaxS_THREE);
}

int getData(){
int eeAddress = 0; 
EEPROM.get(eeAddress, sensorMinS);  
sensorMin = sensorMinS;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensorMinS_TWO); 
sensorMin_TWO = sensorMinS_TWO;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensorMinS_THREE); 
sensorMin_THREE = sensorMinS_THREE;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensorMaxS);
sensorMax = sensorMaxS;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensorMaxS_TWO);
sensorMax_TWO = sensorMaxS_TWO;
eeAddress += sizeof(int);
EEPROM.get(eeAddress, sensorMaxS_THREE);
sensorMax_THREE = sensorMaxS_THREE;
if(sensorMinS > 0 && sensorMinS_TWO > 0 && sensorMinS_THREE > 0){
  calibrationFlag = 0;
  return 1;
} else {
  return 0;
}
}

void calibracionSetup(){ 
    sensorMin = 1023;        
    sensorMax = 0;
    sensorMin_TWO = 1023;        
    sensorMax_TWO = 0;
    sensorMin_THREE = 1023;        
    sensorMax_THREE = 0;
    
    while (millis() < 10000) {
    sensorValue = sensorPromedio(20);
    sensorValue_TWO = sensorPromedio_TWO(20);
    sensorValue_THREE = sensorPromedio_THREE(20);
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

      if (sensorValue_TWO > sensorMax_TWO) {
      sensorMax_TWO = sensorValue_TWO;
    }

      if (sensorValue_THREE > sensorMax_THREE) {
      sensorMax_THREE = sensorValue_THREE;
    }
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }

    if (sensorValue_TWO < sensorMin_TWO) {
      sensorMin_TWO = sensorValue_TWO;
    }

    if (sensorValue_THREE < sensorMin_THREE) {
      sensorMin_THREE = sensorValue_THREE;
    }
  }
if((sensorMax - sensorMin) < 260){
sensorMin = sensorMin - 50;
sensorMax = sensorMax + 60;
sensorMin_TWO = sensorMin_TWO - 50;
sensorMax_TWO = sensorMax_TWO + 60;
sensorMin_THREE = sensorMin_THREE - 50;
sensorMax_THREE = sensorMax_THREE + 60;
saveData();
startFlag = 1;
} else {
  digitalWrite(transistorPin, HIGH); 
}
}

void calibracionTest(){
     coronaOff();
     cintaOff();
     sensorMin = 1023;
     sensorMax = 0;
     sensorMin_TWO  = 1023;
     sensorMax_TWO = 0;
     sensorMin_THREE  = 1023;
     sensorMax_THREE = 0;
     calibrationFlag = 2;
     sensorValue = sensorPromedio(20);
     sensorValue_TWO = sensorPromedio_TWO(20);
     sensorValue_THREE = sensorPromedio_THREE(20);
    while(newcalib.check() != 1){
     sensorValue = sensorPromedio(20);
     sensorValue_TWO = sensorPromedio_TWO(20);
     sensorValue_THREE = sensorPromedio_THREE(20);
     if((sensorValue < sensorMinB || sensorValue > sensorMaxB || sensorValue_TWO > sensorMaxB_TWO || sensorValue_TWO < sensorMinB_TWO|| sensorValue_THREE > sensorMaxB_THREE || sensorValue_THREE < sensorMinB_THREE) && calibrationFlag == 2){
   if(sensorValue < 800 || sensorValue_TWO < 800 || sensorValue_THREE < 800){
        peaton(); 
    } 
  }  
    if (Serial.available() > 0) {
 int inByte = Serial.read();
 switch (inByte) {
        case 'P':
        if(isNight == true){
        panel1.print('P');
        panel2.print('P'); 
        }
        peatonTime.reset();
        isPeatonPresent = true;
        break;
}
  }
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

        if (sensorValue_TWO > sensorMax_TWO) {
      sensorMax_TWO = sensorValue_TWO;
    }

        if (sensorValue_THREE > sensorMax_THREE) {
      sensorMax_THREE = sensorValue_THREE;
    }
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }

    if (sensorValue_TWO < sensorMin_TWO) {
      sensorMin_TWO = sensorValue_TWO;
    }

    if (sensorValue_THREE < sensorMin_THREE) {
      sensorMin_THREE = sensorValue_THREE;
    }
  }
if((sensorMax - sensorMin) < 260){
sensorMin = sensorMin - 50;
sensorMax = sensorMax + 60;
sensorMin_TWO = sensorMin_TWO - 50;
sensorMax_TWO = sensorMax_TWO + 60;
sensorMin_THREE = sensorMin_THREE - 50;
sensorMax_THREE = sensorMax_THREE + 60;
startFlag = 1;
saveData();
calibrationFlag = 0;
} else {
 sensorMin = sensorMinB;
 sensorMax = sensorMaxB; 
 sensorMin_TWO = sensorMinB_TWO;
 sensorMax_TWO = sensorMaxB_TWO; 
 sensorMin_THREE = sensorMinB_THREE;
 sensorMax_THREE = sensorMaxB_THREE; 
 calibrationFlag = 0;
}
}

void peaton(){
if(isPeatonPresent == false){
peatonTime.reset();
isPeatonPresent = true;
if(isNight == true){
  panel1.print('M');
  panel1.print('P');
  panel2.print('P');
  Serial.print('P');
}
if(isNight == false){
  panel1.print('M');
  panel2.print('M');
  Serial.print('P');
} 
}
}
void loop(){
 sensorValue = sensorPromedio(20);
 sensorValue_TWO = sensorPromedio_TWO(20);
 sensorValue_THREE = sensorPromedio_THREE(20);
 buttonState = digitalRead(buttonPin);
 if(buttonState == HIGH){
 if(boton.check() == 1){
 buttonPushCounter++; 
 }
 }
 if(buttonPushCounter == 5){
    for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  digitalWrite(transistorPin, HIGH); 
 }
 
if((sensorValue < sensorMin || sensorValue > sensorMax || sensorValue_TWO > sensorMax_TWO || sensorValue_TWO < sensorMin_TWO || sensorValue_THREE > sensorMax_THREE || sensorValue_THREE < sensorMin_THREE) && calibrationFlag == 0){
     if(sensorValue < 800 || sensorValue_TWO < 800 || sensorValue_THREE < 800){
         peaton(); 
     } 
}
     if((sensorValue < sensorMinB || sensorValue > sensorMaxB || sensorValue_TWO > sensorMaxB_TWO || sensorValue_TWO < sensorMinB_TWO|| sensorValue_THREE > sensorMaxB_THREE || sensorValue_THREE < sensorMinB_THREE) && calibrationFlag == 2){
   if(sensorValue < 800 || sensorValue_TWO < 800 || sensorValue_THREE < 800){
        peaton(); 
    } 
  }

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
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 20 && minuto == 55 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 2){
  //---------------DIA------------------------------
  if(hora == 5 && minuto == 54 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 20 && minuto == 32 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 3){
  //---------------DIA------------------------------
  if(hora == 6 && minuto == 22 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 19 && minuto == 57 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 4){
  //---------------DIA------------------------------
  if(hora == 6 && minuto == 45 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 19 && minuto == 17 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 5){
  //---------------DIA------------------------------
  if(hora == 7 && minuto == 4 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 18 && minuto == 49 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 6){
  //---------------DIA------------------------------
  if(hora == 7 && minuto == 18 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 18 && minuto == 43 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 7){
  //---------------DIA------------------------------
  if(hora == 7 && minuto == 16 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 18 && minuto == 55 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 8){
  //---------------DIA------------------------------
  if(hora == 6 && minuto == 54 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 19 && minuto == 17 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 9){
  //---------------DIA------------------------------
  if(hora == 6 && minuto == 15 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 19 && minuto == 37 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 10){
  //---------------DIA------------------------------
  if(hora == 5 && minuto == 31 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 19 && minuto == 58 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 11){
  //---------------DIA------------------------------
  if(hora == 4 && minuto == 54 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 20 && minuto == 27 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }

  if(mes == 12){
  //---------------DIA------------------------------
  if(hora == 4 && minuto == 46 && segundo < 10){
 isNight = false; 
 Serial.print('Z'); 
 cinta.setBrightness(255);
 corona.setBrightness(255);
 currentColor = cinta.Color(255,48,0);
 coronaColor = corona.Color(255,48,0);
 }
 //----------------NOCHE---------------------------
 if(hora == 20 && minuto == 51 && segundo < 10){
  isNight = true;
  Serial.print('H');
  cinta.setBrightness(78);
  corona.setBrightness(78);
  currentColor = cinta.Color(255,48,0);
  coronaColor = corona.Color(255,48,0);
 }
 //------------------------------------------------
 }
  if( (minuto == 0 && segundo < 1) || (minuto == 15 && segundo < 1) || (minuto == 30 && segundo < 1) || (minuto == 45 && segundo < 1)){
  if(sensorValue > sensorMin || sensorValue < sensorMax){
   sensorMinB = sensorMin; 
   sensorMaxB = sensorMax;
   newcalib.reset();
   calibracionTest();
  }
 }

  if(defaultState.check() == 1){
   cintaOff();
   coronaOff();
  }

  if(peatonTime.check() == 1){
    isPeatonPresent = false;  
}

 if (Serial.available() > 0) {
 int inByte = Serial.read();
 switch (inByte) {
        case 'P': 
        peatonTime.reset();
        isPeatonPresent = true;
        break;

        case 'N': 
        peatonTime.reset();
        isPeatonPresent = true;
        panel1.print('P');
        panel2.print('P'); 
        break;
      
        case 'S':
       coronaNoche(); 
       jumpStart = 1;
       panel1.print('S');
       panel2.print('S');
        break;

       case 'W':
       coronaNoche();  
       jumpStart = 1;
       break;

      case 'C':
      coronaOff(); 
      panel1.print('C');
      panel2.print('C');
      defaultState.reset();
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
      digitalWrite(transistorPin, HIGH); 
      break;

      case 'Z':
      cinta.setBrightness(255);
      corona.setBrightness(255);
      currentColor = cinta.Color(255,48,0);
      coronaColor = corona.Color(255,48,0);
      break;
        
    }
  }

  if(cintaTime.check() == 1 && jumpStart == 1 && isPeatonPresent == false) {
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
    jumpStart = 0;
    cintaOff();
}
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
 estadoParpa = !estadoParpa;
 if(estadoParpa == false){
 coronaNoche();
 }
 if(estadoParpa == true){
  coronaOff();
 }
}

void parpadeaNoche(){
 estadoParpa = !estadoParpa;
 if(estadoParpa == false){
 coronaNoche();
 }
 if(estadoParpa == true){
  coronaOff();
 }
}

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel corona = Adafruit_NeoPixel(64,5, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  corona.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i =0; i<64; i++){
    corona.setPixelColor(i,corona.Color(0,0,255));
  corona.show();
    delay(100);
  }
  for(int i =0; i<64; i++){
    corona.setPixelColor(i,corona.Color(255,0,0));
  corona.show();
    delay(100);
  }
  for(int i =0; i<64; i++){
    corona.setPixelColor(i,corona.Color(0,255,0));
  corona.show();
    delay(100);
  }
  for(int i =0; i<64; i++){
    corona.setPixelColor(i,corona.Color(255,50,0));
  corona.show();
    delay(100);
  }
}

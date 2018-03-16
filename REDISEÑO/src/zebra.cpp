//////////////////////////////////////////////////////////////////////////
//																		//
//	@Company		:	Tectronix SpA.									//
//	@Client			:	Clean Voltage									//
//	@Proyect		:	Zebra											//
//	@author			:	Diego Pandolfa									//
//	@date			:	January, 2018									//
//	@version		:	2.0												//
//	@description	:	Firmware developed for Proyect Zebra			//
//																		//
//////////////////////////////////////////////////////////////////////////
#include "zebra.h"
#include <Matrix.h>
#include <Sprite.h>
#include <Adafruit_NeoPixel.h>
#include <Metro.h>
#include <Wire.h>
#include <RTClib.h>
#include <DFPlayer_Mini_Mp3.h> 
#include <LEDFader.h>

Zebra::Zebra(){
	global_state = 0;
	flag_day = 0;
	time = 0;
	num_pedestrian = 0;
	flag_pedestrian = 0;
}

Zebra::~Zebra(){

}

int Zebra::init(void){
	Serial.begin(115200);
	while(!Serial);
	Serial1.begin(115200);
	while(!Serial1);
	Serial2.begin(115200);
	while(!Serial2);
	Serial3.begin(115200);
	while(!Serial3);
	Serial4.begin(115200);
	while(!Serial4);
	Serial5.begin(115200);
	while(!Serial5);
	Serial6.begin(115200);
	while(!Serial6);

	global_state = 0;
	flag_day = 0;
	time = 0;
	num_pedestrian = 0;
	flag_pedestrian = 0;
	return 0;
}

int Zebra::sendReportToServer(void){
	return 0;
}

int Zebra::globalStateMachine(void){

	return 0;
}

int Zebra::setGlobalState(int state){
	if(state != 0){
		global_state = state;
		return 0;
	}
	else{
		global_state = global_state;
		return -1;
	}
}

int Zebra::getTemperature(void){
	return 0;
}

int Zebra::setDay(void){
	return 0;
}

int Zebra::setNight(void){
	return 0;
}

int Zebra::playRecomendation(void){
	return 0;
}

int Zebra::turnOnLight(void){
	return 0;
}

int Zebra::turnOffLight(void){
	return 0;
}

int Zebra::rgbTapeLowRutine(void){
	return 0;
}

int Zebra::rgbTapeHighRutine(void){
	return 0;
}

int Zebra::rgbCrownLowRoutine(void){
	return 0;
}

int Zebra::rgbCrownHighRoutine(void){
	return 0;
}

int Zebra::rgbStandbyPedestrian(void){
	return 0;
}

int Zebra::rgbWalkPedestrian(void){
	return 0;
}












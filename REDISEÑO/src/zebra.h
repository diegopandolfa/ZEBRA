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
#include "Arduino.h"

#define IDLE 		0
#define SETUP 		1
#define STANDBY 	2
#define WALK 		3

class Zebra{
public:
	Zebra();
	~Zebra();
	int init(void);
	int sendReportToServer(void);
	int globalStateMachine(void);
	int setGlobalState(int state);
	int getTemperature(void);
	int setDay(void);
	int setNight(void);
	int playRecomendation(void);
	int turnOnLight(void);
	int turnOffLight(void);
	int rgbTapeLowRutine(void);
	int rgbTapeHighRutine(void);
	int rgbCrownLowRoutine(void);
	int rgbCrownHighRoutine(void);
	int rgbStandbyPedestrian(void);
	int rgbWalkPedestrian(void);
private:
	int global_state;
	int flag_day;
	int time;
	int num_pedestrian;
	int flag_pedestrian;
};

//============================================================================
// Name        : WeatherStation.cpp
// Author      : Lars Klassen
// Version     :
// Copyright   : Lars Klassen
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <signal.h>
#include "OregonScientific.h"
#include "MySQLConnection.h"
#include "RcOok.h"

#ifdef __arm__
#include <wiringPi.h>
#endif

using namespace std;

RcOok ook;
volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}

void handleInterrupt() {
	static unsigned int duration;

#ifdef __arm__
	static unsigned long lastTime;
	long time = micros();
	duration = time - lastTime;
	lastTime = time;
#endif
	uint16_t width = (unsigned short int) duration;

	ook.nextPulse(width);
}

int main() {

	MySQLConnection *con = new MySQLConnection();

#ifdef __arm__
	wiringPiSetup();
	wiringPiISR(0, INT_EDGE_BOTH, &handleInterrupt);

	signal(SIGINT, inthand);
	while(!stop) {
		uint8_t total_bits = 0;
		uint8_t data[OOK_MAX_DATA_LEN];
		ook.getLastData(data, total_bits);
		if(total_bits > 0) {
			OregonScientific os(data, total_bits);

			cout << "GOT " << os.getHexValue() << endl;

			con->insertWeatherData(
					os.getHexValue()
					, os.isValid()
					, os.getModelName()
					, os.getLowBattery()
					, os.getFirstValue()
					, os.getSecondValue());
		}

		sleep(1);
	}

	delete con;

#else
	uint8_t test_data[] = {0xCA, 0x48, 0x14, 0xD3, 0x80, 0x25, 0xC0, 0x73, 0x0};
	OregonScientific* s = new OregonScientific(test_data, 68);

	con->insertWeatherData(s->getHexValue(), s->isValid(), s->getModelName(), s->getLowBattery(), s->getFirstValue());

	delete s;
	delete con;
#endif

	return 0;
}

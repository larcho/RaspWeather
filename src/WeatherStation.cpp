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
#include "OregonScientific.h"
#include "MySQLConnection.h"
#include "RcOok.h"

using namespace std;

int main() {

	/*
	uint8_t test_data[] = {0xCA, 0x48, 0x14, 0xD3, 0x80, 0x25, 0xC0, 0x73, 0x0};

	OregonScientific* s = new OregonScientific(test_data, 68);
	stringstream ss;
	ss << hex << uppercase;

	for(int i = 0; i < sizeof test_data; i++) {
		ss << (uint16_t)test_data[i];
	}
	string rawValue = ss.str();

	MySQLConnection *con = new MySQLConnection();

	con->insertWeatherData(rawValue, s->getModelName(), s->getLowBattery(), s->getFirstValue());

	delete s;
	delete con;
	*/

	RcOok *ook = new RcOok(0);
	MySQLConnection *con = new MySQLConnection();

	for(;;) {
		uint8_t total_bits = 0;
		uint8_t * data = ook->getLastData(total_bits);
		if(total_bits > 0) {
			OregonScientific os(data, total_bits);

			stringstream ss;
			ss << hex << uppercase;

			for(int i = 0; i < (int)ceil(total_bits / 8); i++) {
				ss << (uint16_t)data[i];
			}
			string rawValue = ss.str();

			con->insertWeatherData(rawValue, os.getModelName(), os.getLowBattery(), os.getFirstValue());

		}
	}

	delete ook;
	delete con;

	return 0;
}

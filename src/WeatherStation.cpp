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
using namespace std;

int main() {

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

	return 0;
}

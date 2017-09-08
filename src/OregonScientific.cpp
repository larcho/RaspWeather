/*
 * OregonScientific.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: larcho
 */

#include "OregonScientific.h"
#include <math.h>

OregonScientific::OregonScientific(const uint8_t data[], const int bitcount):
shifted_data(new uint8_t[(int)ceil(bitcount / 8.0f)])
{
	//Tiene que haber al menos un 4 bits de sync, uno de checksum y otro de crc
	if(bitcount < 3 * 8) {
		return;
	}


	for(uint8_t i = 0; i < (int)ceil(bitcount / 8.0f); ++i) {
		this->shifted_data[i] = data[i] << 4 | data[i] >> 4;
	}

	uint8_t checksum = 0x0;

	for(uint8_t i = bitcount - 16; i < bitcount - 8; i += 4) {
		uint8_t index = i >> 3;
		if(i % 8 == 0) {
			checksum |= data[index] << 4;
		} else {
			checksum |= data[index] >> 4;
		}
	}

	uint8_t sum = 0x0;

	for(uint8_t i = 4; i < bitcount - 16; i += 4) {
		uint8_t index = i >> 3;
		if(i % 8 == 0) {
			sum += this->shifted_data[index] >> 4;
		} else {
			sum += this->shifted_data[index] & 0xF;
		}
	}

	if(checksum == sum) {
		this->valid = true;
	}
}

OregonScientific::~OregonScientific() {
	// TODO Auto-generated destructor stub
	delete [] shifted_data;
}

bool OregonScientific::isValid() {
	return this->valid;
}

uint16_t OregonScientific::getModel() {
	if(this->valid) {
		return (uint16_t)this->shifted_data[0] << 12 | (uint16_t)this->shifted_data[1] << 4 | (uint16_t)this->shifted_data[2] >> 4;
	} else {
		return 0x0;
	}

}

string OregonScientific::getModelName() {
	switch(this->getModel()) {
	case 0xC844:
		return "THN802";
	case 0x2914:
		return "PCR800";
	default:
		return "UNKNOWN";
	}
}

bool OregonScientific::getLowBattery() {
	if(this->valid) {
		return this->shifted_data[4] >> 4;
	} else {
		return false;
	}
}

float OregonScientific::getFirstValue() {
	if(this->valid) {
		uint8_t a = this->shifted_data[5] & 0xF;
		uint8_t b = this->shifted_data[5] >> 4;
		uint8_t c = this->shifted_data[4] & 0xF;

		return ((float)a * 10.0) + (float)b + ((float)c * 0.1);
	} else {
		return 0;
	}
}

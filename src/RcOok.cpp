/*
 * RcOok.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: larcho
 */

#include "RcOok.h"
#include <stdio.h>

RcOok::RcOok():
total_bits(0),
flip(0),
state(UNKNOWN),
pos(0),
last_totalbits(0)
{

}

RcOok::~RcOok() {
	// TODO Auto-generated destructor stub
}

void RcOok::nextPulse(const uint16_t width) {

	if (200 <= width && width < 1200) {
		uint8_t w = width >= 700;
		switch (state) {
		case UNKNOWN:
			if (w == 0)
				++flip;
			else if (32 <= flip) {
				flip = 1;
				manchester(1);
			} else
				resetDecoder();
			break;
			case OK:
				if (w == 0)
					state = T0;
				else
					manchester(1);
				break;
				case T0:
					if (w == 0)
						manchester(0);
					else
						resetDecoder();
					break;
		}
	} else {
		resetDecoder();
	}
}

void RcOok::gotBit(const char value) {
	data[pos] = (data[pos] >> 1) | (value ? 0x80 : 00);
	total_bits++;
	pos = total_bits >> 3;
	if (pos >= sizeof data) {
		resetDecoder();
		return;
	}
	state = OK;
}

void RcOok::resetDecoder () {
	if(total_bits > 0) {
		for(uint8_t i = 0; i < sizeof last_data; i++) {
			last_data[i] = data[i];
		}
		last_totalbits = total_bits;
	}

	total_bits = pos = flip = 0;
	state = UNKNOWN;
}

void RcOok::manchester (char value) {
	flip ^= value;
	gotBit(flip);
}

void RcOok::getLastData(uint8_t *data, uint8_t &bits)
{
	for(int i = 0; i < OOK_MAX_DATA_LEN; i++) {
		data[i] = last_data[i];
	}

	bits = last_totalbits;
	last_totalbits = 0;
}

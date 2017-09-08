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
	// TODO Auto-generated constructor stub

}

RcOok::~RcOok() {
	// TODO Auto-generated destructor stub
}

void RcOok::handleInterrupt() {

	static unsigned int duration;
	static unsigned long lastTime;

	//long time = micros();
	//duration = time - lastTime;
	//lastTime = time;
	uint16_t width = (unsigned short int) duration;

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

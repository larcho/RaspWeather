/*
 * RcOok.h
 *
 *  Created on: Sep 8, 2017
 *      Author: larcho
 */

#ifndef RCOOK_H_
#define RCOOK_H_

#define OOK_MAX_DATA_LEN 25

#include <stdlib.h>
#include <stdint.h>

class RcOok {
public:

	enum { UNKNOWN, T0, OK, DONE };

	RcOok();
	virtual ~RcOok();
	void nextPulse(const uint16_t width);
	void getLastData(uint8_t *data, uint8_t &bits);

private:
	void gotBit(const char value);
	void resetDecoder();
	void manchester(char value);

	uint8_t total_bits, flip, state, pos, data[OOK_MAX_DATA_LEN];
	uint8_t last_totalbits, last_data[OOK_MAX_DATA_LEN];
};

#endif /* RCOOK_H_ */

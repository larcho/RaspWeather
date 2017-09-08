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

class RcOok {
public:

	enum { UNKNOWN, T0, OK, DONE };

	RcOok();
	virtual ~RcOok();

private:
	void handleInterrupt();
	void gotBit(const char value);
	void resetDecoder();
	void manchester(char value);

	uint8_t total_bits, flip, state, pos, data[OOK_MAX_DATA_LEN];
	uint8_t last_totalbits, last_data[OOK_MAX_DATA_LEN];
};

#endif /* RCOOK_H_ */

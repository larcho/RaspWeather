/*
 * OregonScientific.h
 *
 *  Created on: Sep 7, 2017
 *      Author: larcho
 */

#ifndef OREGONSCIENTIFIC_H_
#define OREGONSCIENTIFIC_H_

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class OregonScientific {
public:
	OregonScientific(const uint8_t data[], const int bitcount);
	bool isValid();

	uint16_t getModel();
	string getModelName();
	bool getLowBattery();
	float getFirstValue();

	virtual ~OregonScientific();

private:
	uint8_t *shifted_data;
	bool valid;

};

#endif /* OREGONSCIENTIFIC_H_ */

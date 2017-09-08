/*
 * MySQLConnection.h
 *
 *  Created on: Sep 8, 2017
 *      Author: larcho
 */

#ifndef MYSQLCONNECTION_H_
#define MYSQLCONNECTION_H_

#define HOST "unix:///tmp/mysql.sock"
#define USER "root"
#define PASSWD ""

#include "mysql_connection.h"
#include <string>

using namespace std;

class MySQLConnection {
public:
	MySQLConnection();
	virtual ~MySQLConnection();

	void insertWeatherData(
			const string &rawValue
			, const string &deviceModel
			, const bool battery
			, const float value1
			, const float value2 = 0.0f);

private:
	sql::Connection *con;
};

#endif /* MYSQLCONNECTION_H_ */

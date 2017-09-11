/*
 * MySQLConnection.h
 *
 *  Created on: Sep 8, 2017
 *      Author: larcho
 */

#ifndef MYSQLCONNECTION_H_
#define MYSQLCONNECTION_H_

#define HOST "unix:///var/run/mysqld/mysqld.sock"
#define USER "root"
#define PASSWD "root"

#include "mysql_connection.h"
#include <string>

using namespace std;

class MySQLConnection {
public:
	MySQLConnection();
	virtual ~MySQLConnection();

	void insertWeatherData(
			const string &rawValue
			, const bool isValid
			, const string &deviceModel
			, const bool battery
			, const float value1
			, const float value2 = 0.0f);

private:
	sql::Connection *con;
};

#endif /* MYSQLCONNECTION_H_ */

/*
 * MySQLConnection.cpp
 *
 *  Created on: Sep 8, 2017
 *      Author: larcho
 */

#include "MySQLConnection.h"

#include <stdlib.h>
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

MySQLConnection::MySQLConnection() {
	try {
		sql::Driver *driver = get_driver_instance();
		this->con = driver->connect(HOST, USER, PASSWD);
		this->con->setSchema("weather");
	} catch (sql::SQLException &e) {
		cout << "# MySQL Error: " << e.what() << "\n";
	}
}

MySQLConnection::~MySQLConnection() {
	if(this->con != NULL && !this->con->isClosed()) {
		this->con->close();
	}
	delete this->con;
}

void MySQLConnection::insertWeatherData(
		const string &rawValue
		, const bool isValid
		, const string &deviceModel
		, const bool battery
		, const float value1
		, const float value2)
{
	sql::PreparedStatement *stmt = this->con->prepareStatement("INSERT INTO oregon VALUES (NULL, ?, ?, ?, ?, ?, ?, NOW())");
	stmt->setString(1, rawValue);
	stmt->setBoolean(2, isValid);
	stmt->setString(3, deviceModel);
	stmt->setBoolean(4, battery);
	stmt->setDouble(5, value1);
	stmt->setDouble(6, value2);

	stmt->execute();

	delete stmt;
}

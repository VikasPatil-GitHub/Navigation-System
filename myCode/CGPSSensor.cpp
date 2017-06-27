/*
 * CGPSSensor.cpp
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */

#include "CGPSSensor.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
/* CGPSSensor constructor method definition
 * Initializes the class members with the given values
 *
 * PARAMETERS: NONE
 *
 * RETURN: NONE
 * */

CGPSSensor::CGPSSensor()
{

}

/* CGPSSensor::getCurrentPosition() method definition
 * Returns a Waypoint of the current location after getting the latitude and longitude from the user
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: (CWaypoint) - Waypoint of the current location
 * */
CWaypoint CGPSSensor::getCurrentPosition()
{

	double latitude = 0, longitude = 0;
	string mystr1, mystr2;

	/* Get the latitude from user */
	cout << "Enter latitude in decimal format (Ex: 49.8783): ";
	getline(cin,mystr1);
	stringstream(mystr1) >> latitude;

	/* Get the longitude from user */
	cout << endl << "Enter longitude in decimal format (Ex: 8.6595): ";
	getline(cin,mystr2);
	stringstream(mystr2) >> longitude;
	cout << endl;

	CWaypoint Wp1("Current position", latitude, longitude);

	return Wp1;
}

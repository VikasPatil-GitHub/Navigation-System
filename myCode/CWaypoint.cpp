/*
 * CWaypoint.cpp
 *
 *  Created on: 03-Nov-2015
 *      Author: Vikas Patil
 */
#include <iostream>
#include <cmath>
#include "string.h"

using namespace std;
#include "CString.h"
using namespace myIO;
#include "CWaypoint.h"
/* CWaypoint constructor method definition
 * Initializes the class members with the given values
 *
 * PARAMETERS: 	(string) name - Name of the class
 * 				(double) latitude - Latitude of a location
 * 				(double) longitude - Longitude of a location
 *
 * RETURN: NONE
 * */


/* TODO Answer to question c) of section 1.1 CWaypoint: A first class */
CWaypoint::CWaypoint(string name, double latitude, double longitude)
{
	/* Initialize the members using set() method*/
	set(name, latitude, longitude);
	/* TODO Answer to question c) of section 1.1 CWaypoint: A first class */
#ifdef SHOWADDRESS
	/* Printing the address of the class with name*/
	cout << "Object '" << m_name << "' is created" << endl;
	cout << "Latitude: " << m_latitude << endl;
	cout << "Longitude: " << m_longitude << endl << endl;

	/* Printing the class members value, address and size occupied*/
	cout << "Object member m_name with value '" << m_name << "' is created at " << &m_name << endl << "Data occupied by m_name is: " << sizeof(m_name) <<  endl;
	cout << "Object member m_latitude with value " << m_latitude << " is created at " << &m_latitude << endl << "Data occupied by m_latitude is: " << sizeof(m_latitude) <<  endl;
	cout << "Object member m_longitude with value " << m_longitude << " is created at " << &m_longitude << endl << "Data occupied by m_longitude is: " << sizeof(m_longitude) <<  endl << endl;
#endif

}

/* CWaypoint destructor method definition
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: NONE
 * */
CWaypoint::~CWaypoint()
{
}

/* CWaypoint::set() method definition
	 * Sets the name, latitude and longitude for a Waypoint if range check passes else sets to 0
	 *
	 * PARAMETERS: 	(string) name - Name of the Waypoint
	 * 				(double) latitude - Latitude
	 * 				(double) longitude - Longitude
	 *
	 * RETURN: NONE
	 * */
void CWaypoint::set(string name, double latitude, double longitude)
{
	m_name = name;
	m_latitude = 0;
	m_longitude = 0;

	/* Check if the given latitude is valid*/
	if((latitude >= LATITUDE_MIN) and (latitude <= LATITUDE_MAX))
	{
		/* If yes set the given value*/
		m_latitude = latitude;
	}
	/* Check if the given longitude is valid*/
	if((longitude >= LONGITUDE_MIN) and (longitude <= LONGITUDE_MAX))
	{
		/* If yes set the given value*/
		m_longitude = longitude;
	}

	return;
}

/* CWaypoint::print() method definition
 * Prints the latitude and longitude of any given city based on the given format
 * Format 1 (1) - Decimal format
 * Format 2 (2) - Deg mm ss format
 *
 * PARAMETERS: 	(int) format - Printing format
 *
 * RETURN: NONE
 * */
/* TODO Answer to question e) of section 1.1 CWaypoint: A first class */
void CWaypoint::print(int format) const
{
	int lat_deg = 0, long_deg = 0, lat_mm = 0, long_mm = 0;
	double lat_ss = 0, long_ss = 0;
	/* Check for format type*/
	if(format == PRINT_DECIMALFORMAT)
	{
		/* Print in decimal form*/
		cout << m_name << " on " << m_latitude << " and " << m_longitude << endl;
	}
	else if(format == PRINT_DEGMMSSFORMAT)
	{
		/* Convert latitude in decimal form to deg mm ss form*/
		transformLatitude2degmmss(lat_deg, lat_mm, lat_ss);
		/* Convert longitude in decimal form to deg mm ss form*/
		transformLongitude2degmmss(long_deg, long_mm, long_ss);
		/* Print in deg mm ss format*/
		cout << m_name << " on " << lat_deg << "deg " << lat_mm << "min " << lat_ss << "s"
			<<  " and " << long_deg << "deg " << long_mm << "min " << long_ss << "s"<< endl << endl;
	}
	else
	{
		cout << "ERROR: Invalid format requested" << endl;
	}
	return;
}

/* CWaypoint::getName() method definition
 * Returns the name of the requested object
 *
 * PARAMETERS: NONE
 *
 * RETURN: (string) m_name - Name of the location
 * */

/* TODO Answer to question g) of section 1.1 CWaypoint: A first class */
string CWaypoint::getName() const
{
	return m_name;
}

/* CWaypoint::getLatitude() method definition
 * Returns the latitude of the requested location
 *
 * PARAMETERS: NONE
 *
 * RETURN: (double) m_latitude - Latitude of the location
 * */

/* TODO Answer to question g) of section 1.1 CWaypoint: A first class */
double CWaypoint::getLatitude() const
{
	return m_latitude;
}

/* CWaypoint::getLongitude() method definition
 * Returns the longitude of the requested location
 *
 * PARAMETERS: NONE
 *
 * RETURN: (double) m_longitude - Longitude of the location
 * */

/* TODO Answer to question g) of section 1.1 CWaypoint: A first class */
double CWaypoint::getLongitude() const
{
	return m_longitude;
}


/* CWaypoint::transformLatitude2degmmss() method definition
 * Convert the latitude from decimal to deg mm ss form
 *
 * PARAMETERS: 	(int &) deg - Referenced degree variable
 * 				(int &) mm - Referenced mm variable
 * 				(double &) ss - Referenced ss variable
 *
 * RETURN: NONE
 * */

/* TODO Answer to question e) of section 1.1 CWaypoint: A first class */
void CWaypoint::transformLatitude2degmmss(int& deg, int& mm, double& ss) const
{
	double loc_latitude = m_latitude;
	double loc_latfrac = 0, loc_latint = 0;

	loc_latfrac = modf(loc_latitude, &loc_latint);

	deg = loc_latitude;
	mm = (loc_latfrac * SEC) / MIN;
	ss = (loc_latfrac * SEC) - (mm * MIN);

	return;
}

/* CWaypoint::transformLongitude2degmmss() method definition
 * Convert the longitude from decimal to deg mm ss form
 *
 * PARAMETERS: 	(int &) deg - Referenced degree variable
 * 				(int &) mm - Referenced mm variable
 * 				(double &) ss - Referenced ss variable
 *
 * RETURN: NONE
 * */

/* TODO Answer to question e) of section 1.1 CWaypoint: A first class */
void CWaypoint::transformLongitude2degmmss(int& deg, int& mm, double& ss) const
{
	double loc_longitude = m_longitude;
	double loc_longfrac = 0, loc_longint = 0;

	loc_longfrac = modf(loc_longitude, &loc_longint);

	deg = loc_longitude;
	mm = (loc_longfrac * MIN);
	ss = (loc_longfrac * SEC) - (mm * MIN);

	return;
}

/* operator<<() overloaded method definition
 * Overloads the << operator
 *
 * PARAMETERS:  (ostream&) out - Print waypoint
 * 				(CWaypoint&) wp - Waypoint to be overloaded
 *
 * RETURN: (ostream&) out - Print waypoint
 * */
std::ostream& operator<<(std::ostream& out, const CWaypoint& wp)
{
	out << "------Waypoint------"<<endl;
	wp.print(PRINT_DEGMMSSFORMAT);

	return out;
}

/* CWaypoint::toString() method definition
 * Returns the combined attributes in string form
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: (string) str - string containing the combined attributes
 * */
std::string CWaypoint::toString() const
{
	string str;
	str = m_name+DELIMINATOR+CString::double2String(m_latitude)+DELIMINATOR+CString::double2String(m_longitude);
	return str;
}


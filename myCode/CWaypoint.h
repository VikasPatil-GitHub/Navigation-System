/*
 * CWaypoint.h
 *
 *  Created on: 03-Nov-2015
 *      Author: Vikas Patil
 */

#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_

#include <string>
#include <iostream>

/* Macros*/
/* Valid min and max values of latitude*/
#define LATITUDE_MIN -90
#define LATITUDE_MAX 90

/* Valid min and max values of longitude*/
#define LONGITUDE_MIN -180
#define LONGITUDE_MAX 180

/* Macros for minutes and seconds used for conversion of degress into min and sec*/
#define MIN 60
#define SEC 3600

/* TODO Answer to question c) of section 1.1 CWaypoint: A first class*/
/* Macro to enable or disable verbose mode*/
//#define SHOWADDRESS

/* Macros for printing latitudes and longitudes in decimal or deg mm ss format*/
/* TODO Answer to question f) of section 1.1 CWaypoint: A first class */
/* CWaypoint.h is the best file to define these macros as we include this header file in all other .cpp files where CWaypoint class is used */
#define DEGREE 1
#define MMSS 2

#define PRINT_DECIMALFORMAT DEGREE
#define PRINT_DEGMMSSFORMAT MMSS

/* Macro for Earth radius in Km*/
#define EARTH_RADIUS 6378

/* Macro for PI and Angle to radians conversion*/
#define PI 3.1415926
#define ANGLETORAD (PI/180)

#define DELIMINATOR ";"
/* TODO Answer to question a) of section 1.1 CWaypoint: A first class*/
/* Class CWaypoint declaration*/
class CWaypoint
{
protected:
	std::string m_name;
	double m_latitude;
	double m_longitude;
public:
	/* CWaypoint constructor method definition
	 * Initializes the class members with the given values
	 *
	 * PARAMETERS: 	(string) name - Name of the class
	 * 				(double) latitude - Latitude of a location
	 * 				(double) longitude - Longitude of a location
	 *
	 * RETURN: NONE
	 * */
	CWaypoint(std::string name = "Wp Undefined Location", double latitude = 0, double longitude = 0);
	/* CWaypoint destructor method definition
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: NONE
	 * */
	virtual ~CWaypoint();
	/* CWaypoint::set() method definition
	 * Sets the name, latitude and longitude for a Waypoint if range check passes else sets to 0
	 *
	 * PARAMETERS: 	(string) name - Name of the Waypoint
	 * 				(double) latitude - Latitude
	 * 				(double) longitude - Longitude
	 *
	 * RETURN: NONE
	 * */
	void set(std::string name, double latitude, double longitude);
	/* CWaypoint::getName() method definition
	 * Returns the name of the requested object
	 *
	 * PARAMETERS: NONE
	 *
	 * RETURN: (string) m_name - Name of the location
	 * */
	std::string getName() const;
	/* CWaypoint::getLatitude() method definition
	 * Returns the latitude of the requested location
	 *
	 * PARAMETERS: NONE
	 *
	 * RETURN: (double) m_latitude - Latitude of the location
	 * */
	double getLatitude() const;
	/* CWaypoint::getLongitude() method definition
	 * Returns the longitude of the requested location
	 *
	 * PARAMETERS: NONE
	 *
	 * RETURN: (double) m_longitude - Longitude of the location
	 * */
	double getLongitude() const;
	/* CWaypoint::print() method definition
	 * Prints the latitude and longitude of any given city based on the given format
	 * Format 1 (1) - Decimal format
	 * Format 2 (2) - Deg mm ss format
	 *
	 * PARAMETERS: 	(int) format - Printing format
	 *
	 * RETURN: NONE
	 * */
	virtual void print(int format) const;
	/* CWaypoint::toString() method definition
	 * Returns the combined attributes in string form
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: (string) str - string containing the combined attributes
	 * */
	std::string toString() const;
	/* operator<<() overloaded method definition
	 * Overloads the << operator
	 *
	 * PARAMETERS:  (ostream&) out - Print waypoint
	 * 				(CWaypoint&) wp - Waypoint to be overloaded
	 *
	 * RETURN: (ostream&) out - Print waypoint
	 * */
	friend std::ostream& operator<<(std::ostream& out, const CWaypoint& wp);
private:
	/* CWaypoint::transformLongitude2degmmss() method definition
	 * Convert the longitude from decimal to deg mm ss form
	 *
	 * PARAMETERS: 	(int &) deg - Referenced degree variable
	 * 				(int &) mm - Referenced mm variable
	 * 				(double &) ss - Referenced ss variable
	 *
	 * RETURN: NONE
	 * */
	void transformLongitude2degmmss(int& deg, int& mm, double& ss) const;
	/* CWaypoint::transformLatitude2degmmss() method definition
	 * Convert the latitude from decimal to deg mm ss form
	 *
	 * PARAMETERS: 	(int &) deg - Referenced degree variable
	 * 				(int &) mm - Referenced mm variable
	 * 				(double &) ss - Referenced ss variable
	 *
	 * RETURN: NONE
	 * */
	void transformLatitude2degmmss(int& deg, int& mm, double& ss) const;
};

#endif /* CWAYPOINT_H_ */

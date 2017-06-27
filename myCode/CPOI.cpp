/*
 * CPOI.cpp
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */

#include "CPOI.h"
#include <iostream>

using namespace std;
#include "CString.h"
using namespace myIO;

/* Macro to print the type of location */
#define  TYPE (	(m_type == STREET)? "Street": 						\
				(m_type == SUPERMARKET) ? "Super market" : 			\
				(m_type == GASSTATION) ? "Gas station" : 			\
				(m_type == PHARMACY) ?  "Pharmacy" : 				\
				(m_type == PUBSANDBARS) ?  "Pubs and Bars" :		\
				(m_type == ATM) ?  "ATM" :							\
				(m_type == BUSSTOP) ?  "Bus Stop" :					\
				(m_type == POSTOFFICE) ?  "Post office" :			\
				(m_type == RAILWAYSTATION) ?  "Railway Station" :	\
				(m_type == RESTAURANT) ?  "Restaurant" : 			\
				"Undefined"\
				)


/* CPOI constructor method definition
 * Initializes the class members with the given values
 *
 * PARAMETERS: 	(t_poi) type - Type of location
 * 				(string) name - Name of the location
 * 				(string) description - Description of the location
 * 				(double) latitude - Latitude of the location
 * 				(double) longitude - Longitude of the location
 * RETURN: NONE
 * */

CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude)
{
	/* Call CWaypoint set() function */
	set(name, latitude, longitude);
//	CWaypoint(name,latitude,longitude);
	m_type = type;
	m_description = description;
}

/* CPOI::print() method definition
 * Prints the POI details
 *
 * PARAMETERS: 	(int) format - DECIMAL or DEGMMSS format
 *
 * RETURN: NONE
 * */
void CPOI::print(int format) const
{
	cout << TYPE << ": " << m_description << endl;
	CWaypoint::print(format);
}

/* operator<<() overloaded operator << method definition
 * Operator overloaded function to print the CPOI
 *
 * PARAMETERS: 	(ostream&) out - POI print
 * 				(CPOI&) poi - Referenced POI to be printed
 *
 * RETURN: (ostream&) - POI print
 * */
std::ostream& operator<<(std::ostream& out, const CPOI& poi)
{
	out << "----Point of Interest----" << endl;
	poi.print(PRINT_DEGMMSSFORMAT);
	return out;
}

/* CPOI::toStringPoi() method definition
 * Returns the combined attributes in string form
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: (string) str - string containing the combined attributes
 * */
std::string CPOI::toStringPoi() const
{
	string str;
	str = string(TYPE)+DELIMINATOR_POI+m_name+DELIMINATOR_POI+m_description+DELIMINATOR_POI+CString::double2String(m_latitude)+DELIMINATOR_POI+CString::double2String(m_longitude);
	return str;
}

t_poi CPOI::getType() const
{
	return m_type;
}

std::string CPOI::getDescription() const
{
	return m_description;
}

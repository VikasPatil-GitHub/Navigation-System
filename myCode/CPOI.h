/*
 * CPOI.h
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */

#ifndef CPOI_H_
#define CPOI_H_

#include <string>
#include <iostream>
#include "CWaypoint.h"

#define DELIMINATOR_POI ";"
/* Enumerator to define the types of POIs */
enum t_poi
{
	UNDEFINED,
	STREET,
	SUPERMARKET,
	GASSTATION,
	PHARMACY,
	PUBSANDBARS,
	ATM,
	POSTOFFICE,
	BUSSTOP,
	RAILWAYSTATION,
	RESTAURANT,
	Supermarket,
	Museum,
	Restaurant,
	Bank,
	Stadium
};

/* Class CPOI declaration*/
class CPOI: public CWaypoint
{
	/* operator<<() overloaded operator << method definition
	 * Operator overloaded function to print the CPOI
	 *
	 * PARAMETERS: 	(ostream&) out - POI print
	 * 				(CPOI&) poi - Referenced POI to be printed
	 *
	 * RETURN: (ostream&) - POI print
	 * */
	friend std::ostream& operator<<(std::ostream& out, const CPOI& poi);
private:
	std::string m_description;
    /**@link dependency*/
    t_poi m_type;
public:
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
	CPOI(t_poi type = UNDEFINED, std::string name = "POI Undefined location", std::string description = "No description", double latitude = 0, double longitude = 0);
	/* CPOI::print() method definition
	 * Prints the POI details
	 *
	 * PARAMETERS: 	(int) format - DECIMAL or DEGMMSS format
	 *
	 * RETURN: NONE
	 * */
	void print(int format) const;
	/* CPOI::toStringPoi() method definition
	 * Returns the combined attributes in string form
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: (string) str - string containing the combined attributes
	 * */
	std::string toStringPoi() const;
	t_poi getType() const;
	std::string getDescription() const;
};

#endif /* CPOI_H_ */

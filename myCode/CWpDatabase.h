/*
 *
 * CWpDatabase.h
 *
 *  Created on: 04-Dec-2015
 *      Author: Vikas Patil
 */



#ifndef CWPDATABASE_H_
#define CWPDATABASE_H_


#include <map>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <string>
#include "CWaypoint.h"
#include "CFileIO.h"
#include "CDatabaseTemplate.h"

class CWpDatabase:public CDatabaseTemplate<std::string,CWaypoint>
{
public:
	/* CWpDatabase constructor method definition
	 * Initializes the class members with the given values
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: NONE
	 * */
	CWpDatabase();
	/* CWpDatabase::addWaypoint() method definition
	 * Adds Waypoint to the database
	 *
	 * PARAMETERS: 	(CWaypoint&) wp - Referenced Waypoint to be added
	 *
	 * RETURN: NONE
	 * */
    void addWaypoint(const CWaypoint& wp);
    /* CWpDatabase::getPointerToWaypoint() method definition
	 * Returns the address of the Waypoint object of the given name
	 *
	 * PARAMETERS: 	(string) name - Name of the Waypoint
	 *
	 * RETURN: (CWaypoint *) Address of the matched Waypoint
	 * */
    const CWaypoint* getPointerToWaypoint(std::string name);
    std::map<std::string,CWaypoint>::iterator getFirstWp(void);
    std::map<std::string,CWaypoint>::iterator getLastWp(void);
    void clearWpDB(void);
};

#endif /* CWPDATABASE_H_ */

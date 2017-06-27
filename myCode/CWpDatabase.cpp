/*
 * CWpDatabase.cpp
 *
 *  Created on: 04-Dec-2015
 *      Author: Vikas Patil
 */


#include <iostream>
#include "CWpDatabase.h"
#include "CWaypoint.h"
using namespace std;
#include "CString.h"
using namespace myIO;

/* CWpDatabase constructor method definition
 * Initializes the class members with the given values
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: NONE
 * */
CWpDatabase::CWpDatabase()
{
}

/* CWpDatabase::addWaypoint() method definition
 * Adds Waypoint to the database
 *
 * PARAMETERS: 	(CWaypoint&) wp - Referenced Waypoint to be added
 *
 * RETURN: NONE
 * */
void CWpDatabase::addWaypoint(const CWaypoint& wp)
{
	CDatabaseTemplate::addObject(wp);
}

/* CWpDatabase::getPointerToWaypoint() method definition
 * Returns the address of the Waypoint object of the given name
 *
 * PARAMETERS: 	(string) name - Name of the Waypoint
 *
 * RETURN: (CWaypoint *) Address of the matched Waypoint
 * */
const CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	return CDatabaseTemplate::getPointerToObject(name);
}

std::map<std::string, CWaypoint>::iterator CWpDatabase::getFirstWp(void)
{
	return CDatabaseTemplate::getFirstObject();
}

std::map<std::string, CWaypoint>::iterator CWpDatabase::getLastWp(void)
{
	return CDatabaseTemplate::getLastObject();
}

void CWpDatabase::clearWpDB(void)
{
	CDatabaseTemplate::clearDB();
}

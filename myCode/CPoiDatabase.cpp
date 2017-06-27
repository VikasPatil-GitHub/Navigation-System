/*
 * CPoiDatabase.cpp
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */

#include "CPoiDatabase.h"
#include "iostream"
#include "string.h"

using namespace std;
#include "CString.h"
using namespace myIO;

/* CPoiDatabase constructor method definition
 * Initializes the class members with the given values
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: NONE
 * */
CPoiDatabase::CPoiDatabase()
{
}

/* CPoiDatabase::addPoi method definition
 * Adds POI to the database
 *
 * PARAMETERS: 	(CPOI) poi - Referenced POI to be added
 *
 * RETURN: NONE
 * */

void CPoiDatabase::addPoi(const CPOI& poi)
{
	CDatabaseTemplate::addObject(poi);
}

/* CPoiDatabase::getPointerToPoi method definition
 * Returns the address of the POI object of the given name
 *
 * PARAMETERS: 	(string) name - Name of the location
 *
 * RETURN: (CPOI *) Address of the matched POI
 * */
const CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	return CDatabaseTemplate::getPointerToObject(name);
}

std::map<std::string, CPOI>::iterator CPoiDatabase::getFirstPoi(void)
{
	return CDatabaseTemplate::getFirstObject();
}

std::map<std::string, CPOI>::iterator CPoiDatabase::getLastPoi(void)
{
	return CDatabaseTemplate::getLastObject();
}

void CPoiDatabase::clearPOIDB(void)
{
	CDatabaseTemplate::clearDB();
}


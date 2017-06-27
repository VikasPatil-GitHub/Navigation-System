/*
 * CPoiDatabase.h
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */

#ifndef CPOIDATABASE_H_
#define CPOIDATABASE_H_


#include <map>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <string>
#include "CPOI.h"
#include "CFileIO.h"
#include "CDatabaseTemplate.h"

/* Class CPoiDatabase declaration*/
class CPoiDatabase: public CDatabaseTemplate<std::string,CPOI>
{
public:
	/* CPoiDatabase constructor method definition
	 * Initializes the class members with the given values
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: NONE
	 * */
	CPoiDatabase();
	/* CPoiDatabase::addPoi() method definition
	 * Adds POI to the database
	 *
	 * PARAMETERS: 	(CPOI&) poi - Referenced POI to be added
	 *
	 * RETURN: NONE
	 * */
	void addPoi(const CPOI& poi);
	/* CPoiDatabase::getPointerToPoi() method definition
	 * Returns the address of the POI object of the given name
	 *
	 * PARAMETERS: 	(string) name - Name of the location
	 *
	 * RETURN: (CPOI *) Address of the matched POI
	 * */
	const CPOI* getPointerToPoi(std::string name);
	std::map<std::string, CPOI>::iterator getFirstPoi(void);
	std::map<std::string, CPOI>::iterator getLastPoi(void);
	void clearPOIDB(void);
};

#endif /* CPOIDATABASE_H_ */

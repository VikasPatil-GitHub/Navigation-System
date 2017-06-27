/*
 * CPersistentStorage.h
 *
 *  Created on: 07-Dec-2015
 *      Author: Vikas Patil
 */

#ifndef CPERSISTENTSTORAGE_H_
#define CPERSISTENTSTORAGE_H_

#include <string>
#include "CWpDatabase.h"
#include "CPoiDatabase.h"


class CPersistentStorage
{
public:
	/* CPersistentStorage destructor method definition
	 *
	 * PARAMETERS: NONE
	 *
	 * RETURN: NONE
	 * */
	virtual ~CPersistentStorage();
	/* CPersistentStorage::setMediaName() method definition
	 * Sets the name of the media to be used for persistent storage
	 *
	 * PARAMETERS: (string) name - Name of the media file to be used
	 *
	 * RETURN: NONE
	 * */
	virtual void setMediaName(std::string name) = 0;
	/* CPersistentStorage::writeData() method definition
	 * Write the data to the persistent storage
	 *
	 * PARAMETERS: 	(CWpDatabase&) waypointDB - Database with waypoints
	 * 				(CPoiDatabase&) poiDB - Database with POIs
	 *
	 * RETURN: (bool) - TRUE if the data could be saved successfully
	 * */
	virtual bool writeData(const CWpDatabase& waypointDB, const CPoiDatabase& poiDB) = 0;
	/*
	 * The mode to be used when reading the data bases (see readData)
	 * */
	enum MergeMode{ MERGE, REPLACE};
	/* CPersistentStorage::readData() method definition
	 * Fill the databases with the data from persistent storage. If merge mode is MERGE, the content in the
	 * persistent storage will be merged with any content already existing in the databases. If merge mode is REPLACE
	 * already existing content will be removed before inserting the content from the persistence storage
	 *
	 * PARAMETERS: 	(CWpDatabase&) waypointDB - Database with waypoints
	 * 				(CPoiDatabase&) poiDB - Database with POIs
	 * 				(MergeMode) mode - REPLACE or MERGE
	 *
	 * RETURN: (bool) - TRUE if the data could be read successfully
	 * */
	virtual bool readData(CWpDatabase& waypointDB, CPoiDatabase& poiDB, MergeMode mode) = 0;
};

inline CPersistentStorage::~CPersistentStorage()
{
}

#endif /* CPERSISTENTSTORAGE_H_ */

/*
 * CPersistenceComp.h
 *
 *  Created on: 10-Dec-2015
 *      Author: Vikas Patil
 */

#ifndef CPERSISTENCECOMP_H_
#define CPERSISTENCECOMP_H_

#include "CPersistentStorage.h"

class CPersistenceComp : public CPersistentStorage
{
private:
	std::string m_filenameWpDB;
	std::string m_filenamePoiDB;
	std::string m_readMode;
	CPoiDatabase* m_pPoiDB;
	CWpDatabase* m_pWpDB;
public:
	/* CPersistenceComp constructor method definition
	 *
	 * PARAMETERS: NONE
	 *
	 * RETURN: NONE
	 * */
	CPersistenceComp();
	/* CPersistentStorage::writeData() method definition
	 * Write the data to the persistent storage
	 *
	 * PARAMETERS: 	(CWpDatabase&) waypointDB - Database with waypoints
	 * 				(CPoiDatabase&) poiDB - Database with POIs
	 *
	 * RETURN: (bool) - TRUE if the data could be saved successfully
	 * */
	bool writeData(const CWpDatabase& waypointDB, const CPoiDatabase& poiDB);
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
	bool readData(CWpDatabase& waypointDB, CPoiDatabase& poiDB, MergeMode mode);
	/* CPersistentStorage::setMediaName() method definition
	 * Sets the name of the media to be used for persistent storage
	 *
	 * PARAMETERS: (string) name - Name of the media file to be used
	 *
	 * RETURN: NONE
	 * */
	void setMediaName(std::string name);
	void connectToPoiDB(CPoiDatabase* pPoiDB);
	void connectToWpDB(CWpDatabase* pWpDB);
};

#endif /* CPERSISTENCECOMP_H_ */

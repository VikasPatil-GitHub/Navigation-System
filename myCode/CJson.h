/*
 * CJson.h
 *
 *  Created on: 05-Jan-2016
 *      Author: Vikas Patil
 */

#ifndef CJSON_H_
#define CJSON_H_

#include <string>
#include "CPersistentStorage.h"
#include "CJsonScanner.h"

enum parse_state{
	IDLE,
	WAIT_DBNAME,
	WAIT_NAMESEP,
	WAIT_BEGINARRAY,
	WAIT_BEGINOBJECT,
	WAIT_ATTRNAME,
	WAIT_ATTRVALUE,
	WAIT_VALUESEP,
	WAIT_ENDOBJECT,
	WAIT_ENDARRAY
};

class CJson: public CPersistentStorage
{
	std::string m_filenameJson;
	std::string m_readMode;
	CPoiDatabase* m_pPoiDB;
	CWpDatabase* m_pWpDB;
	parse_state m_state;
	parse_state m_oldstate;

public:
	/* CJson constructor method definition
	 *
	 * PARAMETERS: NONE
	 *
	 * RETURN: NONE
	 * */
	CJson();
	/* CJson::writeData() method definition
	 * Write the data to the persistent storage
	 *
	 * PARAMETERS: 	(CWpDatabase&) waypointDB - Database with waypoints
	 * 				(CPoiDatabase&) poiDB - Database with POIs
	 *
	 * RETURN: (bool) - TRUE if the data could be saved successfully
	 * */
	bool writeData(const CWpDatabase& waypointDB, const CPoiDatabase& poiDB);
	/* CJson::readData() method definition
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
	/* CJson::setMediaName() method definition
	 * Sets the name of the media to be used for persistent storage
	 *
	 * PARAMETERS: (string) name - Name of the media file to be used
	 *
	 * RETURN: NONE
	 * */
	void setMediaName(std::string name);
	/* CJson::connectToPoiDB() method definition
	 * Connects to POI database
	 *
	 * PARAMETERS: (string) name - Name of the media file to be used
	 *
	 * RETURN: NONE
	 * */
	void connectToPoiDB(CPoiDatabase* pPoiDB);
	/* CJson::connectToWpDB() method definition
	 * Connects to Waypoint database
	 *
	 * PARAMETERS: (string) name - Name of the media file to be used
	 *
	 * RETURN: NONE
	 * */
	void connectToWpDB(CWpDatabase* pWpDB);
};

#endif /* CJSON_H_ */

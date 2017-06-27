/*
 * CPersistenceComp.cpp
 *
 *  Created on: 10-Dec-2015
 *      Author: Vikas Patil
 */

#include <string>
using namespace std;
#include "CPersistenceComp.h"
#include "CFileIO.h"
#include "CString.h"
using namespace myIO;

#define  TYPE_REV(str) ((str =="Street")? STREET: 						\
						(str =="Super market")? SUPERMARKET: 			\
						(str =="Gas station")? GASSTATION: 				\
						(str =="Pharmacy")? PHARMACY: 					\
						(str =="Pubs and Bars")? PUBSANDBARS: 			\
						(str =="ATM")? ATM: 							\
						(str =="Bus Stop")? BUSSTOP: 					\
						(str =="Post office")? POSTOFFICE: 				\
						(str =="Railway Station")? RAILWAYSTATION: 		\
						(str =="Restaurant")? RESTAURANT: 				\
					UNDEFINED\
				)
/* CPersistenceComp constructor method definition
 *
 * PARAMETERS: NONE
 *
 * RETURN: NONE
 * */
CPersistenceComp::CPersistenceComp()
{
	// TODO Auto-generated constructor stub
	m_filenamePoiDB = "";
	m_filenameWpDB = "";
	m_readMode = "";
	m_pPoiDB = NULL;
	m_pWpDB = NULL;
}

/* CPersistentStorage::writeData() method definition
 * Write the data to the persistent storage
 *
 * PARAMETERS: 	(CWpDatabase&) waypointDB - Database with waypoints
 * 				(CPoiDatabase&) poiDB - Database with POIs
 *
 * RETURN: (bool) - TRUE if the data could be saved successfully
 * */
bool CPersistenceComp::writeData(const CWpDatabase& waypointDB,
		const CPoiDatabase& poiDB)
{
	CFileIO myFile;

	myFile.openFile(m_filenamePoiDB,OUT);


	for (map<string,CPOI>::const_iterator itr = m_pPoiDB->getFirstPoi();
		 itr != m_pPoiDB->getLastPoi(); itr++)
	{
		myFile.writeLine(itr->second.toStringPoi());
	}
	myFile.closeFile();

	cout << "Saved POI database to file" << endl;

	myFile.openFile(m_filenameWpDB,OUT);

	for (map<string,CWaypoint>::const_iterator itr = m_pWpDB->getFirstWp();
		 itr != m_pWpDB->getLastWp(); itr++)
	{
		myFile.writeLine(itr->second.toString());
	}
	myFile.closeFile();

	cout << "Saved Waypoint database to file" << endl;

	return true;
}

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
bool CPersistenceComp::readData(CWpDatabase& waypointDB, CPoiDatabase& poiDB,
		MergeMode mode)
{

	string s,s_orig;
	string name_s,description_s,type_s,latitude_s,longitude_s;
	double latitude,longitude;
	t_poi type_t;
	CFileIO myFile;
	CPOI myPoi;
	CWaypoint myWp;
	unsigned int count = 0;
	bool ret;

	if(mode == MERGE)
	{
		m_readMode = "MERGE";
		ret = false;
	}
	else
	{
		m_readMode = "REPLACE";
		ret = true;
	}

	myFile.openFile(m_filenamePoiDB,IN);

	cout << "Reading from file: " << m_filenamePoiDB << endl;

	if(m_readMode == "REPLACE")
	{
		m_pPoiDB->clearPOIDB();
	}
	while (myFile.readLine(s))
	{
		count++;
		//add is only executed if length > 0
		if (s.length() > 0)
		{
			s_orig = s;
			type_s = CString::cutLeft(s,DELIMINATOR_POI);
			type_t = TYPE_REV(type_s);
			name_s = CString::cutLeft(s,DELIMINATOR_POI);
			description_s = CString::cutLeft(s,DELIMINATOR_POI);
			latitude_s = CString::cutLeft(s,DELIMINATOR_POI);
			latitude = CString::string2double(latitude_s,count);
			longitude_s = CString::cutLeft(s,DELIMINATOR_POI);
			longitude = CString::string2double(longitude_s,count);
			if((name_s == "") or (type_s == "") or (description_s == "") or (latitude_s == "") or (longitude_s == ""))
			{
				cout << "ERROR: Too few fields in line" << count << ": " << s_orig << endl;
			}
			else if((latitude == 0) or (longitude == 0))
			{
				/* Do nothing */
				/* Error printing is handled in CString */
			}
			else
			{
				myPoi = CPOI(type_t,name_s,description_s,latitude,longitude);
				m_pPoiDB->addPoi(myPoi);
			}
		}
		else
		{
			cout << "ERROR: Too few fields in line" << count << ": " << s << endl;
		}
	}

	myFile.closeFile();
	cout << "Finished reading from " << m_filenamePoiDB << endl;

	count = 0;

	myFile.openFile(m_filenameWpDB,IN);

	cout << "Reading from file: " << m_filenameWpDB << endl;
	if(m_readMode == "REPLACE")
	{
		m_pWpDB->clearWpDB();
	}

	while (myFile.readLine(s))
	{
		count++;
		//add is only executed if length > 0
		if (s.length() > 0)
		{
			s_orig =s;
			name_s = CString::cutLeft(s,DELIMINATOR);
			latitude_s = CString::cutLeft(s,DELIMINATOR);
			latitude = CString::string2double(latitude_s, count);
			longitude_s = CString::cutLeft(s,DELIMINATOR);
			longitude = CString::string2double(longitude_s,count);
			if((name_s == "") or (latitude_s == "") or (longitude_s == ""))
			{
				cout << "ERROR: Too few fields in line" << count << ": " << s_orig << endl;
			}
			else if((latitude == 0) or (longitude == 0))
			{
				/* Do nothing */
				/* Error printing is handled in CString */
			}
			else
			{
				myWp = CWaypoint(name_s,latitude,longitude);
				m_pWpDB->addWaypoint(myWp);
			}
		}
		else
		{
				cout << "ERROR: Too few fields in line" << count << ": " << s << endl;
		}
	}
	myFile.closeFile();
	cout << "Finished reading from " << m_filenameWpDB << endl;
	return ret;
}

/* CPersistentStorage::setMediaName() method definition
 * Sets the name of the media to be used for persistent storage
 *
 * PARAMETERS: (string) name - Name of the media file to be used
 *
 * RETURN: NONE
 * */
void CPersistenceComp::setMediaName(std::string name)
{
	m_filenamePoiDB = name + "-poi.txt";
	m_filenameWpDB = name + "-wp.txt";
}

void CPersistenceComp::connectToPoiDB(CPoiDatabase* pPoiDB)
{
	/* Check if database address is not NULL */
	if(pPoiDB != NULL)
	{
		/* Assign address of database to the pointer variable */
		m_pPoiDB = pPoiDB;
	}
	else
		/* Database address is NULL */
	{
		/* Print error message */
		cout << "ERROR: Connection to CPOI database failed!!" << endl;
	}
}

void CPersistenceComp::connectToWpDB(CWpDatabase* pWpDB)
{
	/* Check if database address is not NULL */
	if(pWpDB != NULL)
	{
		/* Assign address of database to the pointer variable */
		m_pWpDB = pWpDB;
	}
	else
		/* Database address is NULL */
	{
		/* Print error message */
		cout << "ERROR: Connection to Waypoint database failed!!" << endl;
	}
}

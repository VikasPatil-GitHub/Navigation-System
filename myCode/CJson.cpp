/*
 * CJson.cpp
 *
 *  Created on: 05-Jan-2016
 *      Author: Vikas Patil
 */

#include <string>
using namespace std;

#include "CFileIO.h"
#include "CString.h"
using namespace myIO;
#include "CJsonScanner.h"
#include "CJsonToken.h"
using namespace APT;
#include "CJson.h"

#define NAMESEPARATOR ":"

#define  TYPE_REV1(str) ((str =="Street")? STREET: 						\
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

CJson::CJson()
{
	// TODO Auto-generated constructor stub
	m_filenameJson = "";
	m_pPoiDB = NULL;
	m_pWpDB = NULL;
	m_readMode = "";
	m_state = IDLE;
	m_oldstate = IDLE;
}

/* CJson::writeData() method definition
 * Write the data to the persistent storage
 *
 * PARAMETERS: 	(CWpDatabase&) waypointDB - Database with waypoints
 * 				(CPoiDatabase&) poiDB - Database with POIs
 *
 * RETURN: (bool) - TRUE if the data could be saved successfully
 * */
bool CJson::writeData(const CWpDatabase& waypointDB,
		const CPoiDatabase& poiDB)
{
	CFileIO myFile;
	string str, type_s, name_s, description_s, latitude_s, longitude_s;

	myFile.openFile(m_filenameJson,OUT);

	myFile.writeLine("{");
	myFile.writeLine("\t\"waypoints\": [");

	for (map<string,CWaypoint>::iterator itr = m_pWpDB->getFirstWp();
		 itr != m_pWpDB->getLastWp(); itr++)
	{

		myFile.writeLine("\t  {");
		str = itr->second.toString();

		name_s = CString::cutLeft(str,DELIMINATOR_POI);
		latitude_s = CString::cutLeft(str,DELIMINATOR_POI);
		longitude_s = CString::cutLeft(str,DELIMINATOR_POI);

		myFile.writeLineWoNext("\t    \"name\": ");
		myFile.writeLine("\""+name_s+"\",");


		myFile.writeLineWoNext("\t    \"latitude\": ");
		myFile.writeLine(latitude_s+",");


		myFile.writeLineWoNext("\t    \"longitude\": ");
		myFile.writeLine(longitude_s);

		if(itr == --(m_pWpDB->getLastWp()))
		{
			myFile.writeLine("\t  }");
		}
		else
		{
			myFile.writeLine("\t  },");
		}

	}
	myFile.writeLine("\t],");
	myFile.writeLine("\t\"pois\": [");
	cout << "Saved Waypoint database to file" << endl;

	for (map<string,CPOI>::iterator itr = m_pPoiDB->getFirstPoi();
		 itr != m_pPoiDB->getLastPoi(); itr++)
	{
		myFile.writeLine("\t  {");
		str = itr->second.toStringPoi();

		type_s = CString::cutLeft(str,DELIMINATOR_POI);
		name_s = CString::cutLeft(str,DELIMINATOR_POI);
		description_s = CString::cutLeft(str,DELIMINATOR_POI);
		latitude_s = CString::cutLeft(str,DELIMINATOR_POI);
		longitude_s = CString::cutLeft(str,DELIMINATOR_POI);

		myFile.writeLineWoNext("\t    \"name\": ");
		myFile.writeLine("\""+name_s+"\",");


		myFile.writeLineWoNext("\t    \"latitude\": ");
		myFile.writeLine(latitude_s+",");


		myFile.writeLineWoNext("\t    \"longitude\": ");
		myFile.writeLine(longitude_s+',');


		myFile.writeLineWoNext("\t    \"type\": ");
		myFile.writeLine("\""+type_s+"\",");


		myFile.writeLineWoNext("\t    \"description\": ");
		myFile.writeLine("\""+description_s+"\"");

		if(itr == --(m_pPoiDB->getLastPoi()))
		{
			myFile.writeLine("\t  }");
		}
		else
		{
			myFile.writeLine("\t  },");
		}
	}
	myFile.writeLine("\t]");
	myFile.writeLine("}");
	myFile.closeFile();

	cout << "Saved POI database to file" << endl;

	return true;
}

bool CJson::readData(CWpDatabase& waypointDB, CPoiDatabase& poiDB,
		MergeMode mode)
{
	unsigned int cnt = 0, wp_count=0, poi_count = 0;
	t_poi type;
	string DB_name, Attr_name, Attr_value, name_s, description_s;
	double latitude, longitude;
	fstream myFile;
	myFile.open(m_filenameJson.c_str(),fstream::in);
	myFile.seekg(0, ios::beg);

	CJsonScanner m_JsonScanner(myFile);
	CJsonToken* m_JsonToken;

	bool ret;

	if(mode == MERGE)
	{
		ret = false;
	}
	else
	{
		m_pPoiDB->clearPOIDB();
		m_pWpDB->clearWpDB();
		ret = true;
	}

	bool end = false, flag_endarray = false, flag_endobject = false;
	while(!end)
	{
		try
		{
			switch(m_state)
			{
			case IDLE:
				m_JsonToken = m_JsonScanner.nextToken();
				if(m_JsonToken->getType() == CJsonToken::BEGIN_OBJECT)
				{
					m_state = WAIT_DBNAME;
					m_oldstate = IDLE;
				}
				else
				{
					cout << "ERROR: JSon file format is wrong! Expected Begin object Token in line: " << m_JsonScanner.scannedLine() << endl;
				}
				break;
			case WAIT_DBNAME:
				m_JsonToken = m_JsonScanner.nextToken();
				if(m_JsonToken->getType() == CJsonToken::STRING)
				{
					m_state = WAIT_NAMESEP;
					m_oldstate = WAIT_DBNAME;
					DB_name = m_JsonToken->str();
				}
				else
				{
					cout << "ERROR: JSon file format is wrong! Expected string indicating Database name in line: " << m_JsonScanner.scannedLine() << endl;
				}
				break;
			case WAIT_NAMESEP:
				m_JsonToken = m_JsonScanner.nextToken();
				if(m_JsonToken->getType() == CJsonToken::NAME_SEPARATOR)
				{
					if(m_oldstate == WAIT_ATTRNAME)
					{
						m_state = WAIT_ATTRVALUE;
					}
					else if(m_oldstate == WAIT_DBNAME)
					{
						m_state = WAIT_BEGINARRAY;
					}
					m_oldstate = WAIT_NAMESEP;
				}
				else
				{
					cout << "ERROR: JSon file format is wrong! Expected Name separator in line: " << m_JsonScanner.scannedLine() << endl;
				}
				break;
			case WAIT_BEGINARRAY:
				m_JsonToken = m_JsonScanner.nextToken();
				if(m_JsonToken->getType() == CJsonToken::BEGIN_ARRAY)
				{
					m_state = WAIT_BEGINOBJECT;
					m_oldstate = WAIT_BEGINARRAY;
				}
				else
				{
					cout << "ERROR: JSon file format is wrong! Expected Begin array in line: " << m_JsonScanner.scannedLine() << endl;
				}
				break;
			case WAIT_BEGINOBJECT:
				m_JsonToken = m_JsonScanner.nextToken();
				if(m_JsonToken->getType() == CJsonToken::BEGIN_OBJECT)
				{
					m_state = WAIT_ATTRNAME;
					m_oldstate = WAIT_BEGINOBJECT;
				}
				else
				{
					cout << "ERROR: JSon file format is wrong! Expected Begin object in line: " << m_JsonScanner.scannedLine() << endl;
				}
				break;
			case WAIT_ATTRNAME:
				m_JsonToken = m_JsonScanner.nextToken();
				if(m_JsonToken->getType() == CJsonToken::STRING)
				{
					m_state = WAIT_NAMESEP;
					m_oldstate = WAIT_ATTRNAME;
					Attr_name = m_JsonToken->str();

					if((CString::contains(Attr_name,"name")) or \
						(CString::contains(Attr_name,"latitude")) or \
						(CString::contains(Attr_name,"longitude")) or \
						((CString::contains(Attr_name,"type")) and (CString::contains(DB_name,"pois"))) or \
						((CString::contains(Attr_name,"description")) and (CString::contains(DB_name,"pois")))
						)
					{
						if(CString::contains(DB_name,"waypoints"))
						{
							wp_count++;
						}
						else if(CString::contains(DB_name,"pois"))
						{
							poi_count++;
						}
						Attr_name = CString::cutRight(Attr_name,NAMESEPARATOR);
					}
					else
					{
						cout << "ERROR: JSon file format is wrong! Unexpected attribute name in line: " << m_JsonScanner.scannedLine() << endl;
					}
				}
				else
				{
					cout << "ERROR: JSon file format is wrong! Expecting string representing the attribute name in line: " << m_JsonScanner.scannedLine() << endl;
				}
				break;
			case WAIT_ATTRVALUE:
				m_JsonToken = m_JsonScanner.nextToken();
				if(m_JsonToken->getType() == CJsonToken::STRING)
				{
					if((Attr_name == "name") or (((Attr_name == "type") or (Attr_name == "description")) and (CString::contains(DB_name,"pois"))))
					{
						if((wp_count == 3) or (poi_count == 5))
						{
							if(wp_count == 3)
							{
								m_pWpDB->addWaypoint(CWaypoint(name_s, latitude, longitude));
								wp_count = 0;
							}
							else if(poi_count == 5)
							{
								m_pPoiDB->addPoi(CPOI(type,name_s,description_s,latitude,longitude));
								poi_count = 0;
							}
							m_state = WAIT_ENDOBJECT;
						}
						else
						{
							m_state = WAIT_VALUESEP;
						}
						m_oldstate = WAIT_ATTRVALUE;
						Attr_value = m_JsonToken->str();
						if(Attr_name == "name")
						{
							name_s = CString::cutRight(Attr_value,NAMESEPARATOR);
//							cout << "Name: " << name_s << endl;
						}
						else if((CString::contains(DB_name,"pois")) and (Attr_name == "type"))
						{
							type = TYPE_REV1(CString::cutRight(Attr_value,NAMESEPARATOR));
//							cout << "Type: " << type << endl;
						}
						else if((CString::contains(DB_name,"pois")) and (Attr_name == "description"))
						{
							description_s = CString::cutRight(Attr_value,NAMESEPARATOR);
//							cout << "Description: " << description_s << endl;
						}
					}
					else
					{
						cout << "ERROR: JSon file format is wrong! Expecting string representing the attribute value in line: " << m_JsonScanner.scannedLine() << endl;
					}
				}
				else if(m_JsonToken->getType() == CJsonToken::NUMBER)
				{
					if((Attr_name == "latitude") or (Attr_name == "longitude"))
					{
						if((wp_count == 3) or (poi_count == 5))
						{
							if(wp_count == 3)
							{
								m_pWpDB->addWaypoint(CWaypoint(name_s, latitude, longitude));
								wp_count = 0;
							}
							else if(poi_count == 5)
							{
								m_pPoiDB->addPoi(CPOI(type,name_s,description_s,latitude,longitude));
								poi_count = 0;
							}
							m_state = WAIT_ENDOBJECT;
						}
						else
						{
							m_state = WAIT_VALUESEP;
						}
						m_oldstate = WAIT_ATTRVALUE;
						Attr_value = m_JsonToken->str();
						Attr_value = CString::cutRight(Attr_value,NAMESEPARATOR);
						if(Attr_name == "latitude")
						{
							latitude = CString::string2double(Attr_value,cnt);
//							cout << "Latitude: " << latitude << endl;
						}
						else
						{
							longitude = CString::string2double(Attr_value,cnt);
//							cout << "Longitude: " << longitude << endl;
						}
					}
					else
					{
						cout << "ERROR: JSon file format is wrong! Expecting number representing the attribute value in line: " << m_JsonScanner.scannedLine() << endl;
					}
				}
				else
				{
					cout << "ERROR: JSon file format is wrong! Expecting string or number representing the attribute value in line: " << m_JsonScanner.scannedLine() << endl;
				}
				break;
			case WAIT_VALUESEP:
				m_JsonToken = m_JsonScanner.nextToken();
				if(m_JsonToken->getType() == CJsonToken::VALUE_SEPARATOR)
				{

					if(m_oldstate == WAIT_ATTRVALUE)
					{
						m_state = WAIT_ATTRNAME;
					}
					else if(m_oldstate == WAIT_ENDARRAY)
					{
						m_state = WAIT_DBNAME;
					}
					else
					{
						m_state = WAIT_BEGINOBJECT;
					}
					m_oldstate = WAIT_VALUESEP;
				}
				else
				{
					if(m_JsonToken->getType() == CJsonToken::END_OBJECT)
					{
						m_state = WAIT_ENDOBJECT;
						m_oldstate = WAIT_ENDARRAY;
						flag_endobject = true;
					}
					else if(m_JsonToken->getType() == CJsonToken::END_ARRAY)
					{
						m_state = WAIT_ENDARRAY;
						m_oldstate = WAIT_VALUESEP;
						flag_endarray = true;
					}
					else
					{
						cout << "ERROR: JSon file format is wrong! Expecting value separator in line: " << m_JsonScanner.scannedLine() << endl;
					}
				}
				break;
			case WAIT_ENDOBJECT:
				if(!flag_endobject)
				{
					m_JsonToken = m_JsonScanner.nextToken();
				}
				if(m_JsonToken->getType() == CJsonToken::END_OBJECT)
				{
					if(m_oldstate == WAIT_ENDARRAY)
					{
						end = true;
						cout << "Finished parsing Json file" << endl;
					}
					else
					{
						m_state = WAIT_VALUESEP;
					}
					m_oldstate = WAIT_ENDOBJECT;
				}
				else
				{
					cout << "ERROR: JSon file format is wrong! Expecting end object in line: " << m_JsonScanner.scannedLine() << endl;
				}

				break;
			case WAIT_ENDARRAY:
				if(!flag_endarray)
				{
					m_JsonToken = m_JsonScanner.nextToken();
				}
				if(m_JsonToken->getType() == CJsonToken::END_ARRAY)
				{
					m_state = WAIT_VALUESEP;
					m_oldstate = WAIT_ENDARRAY;
				}
				else
				{
					cout << "ERROR: JSon file format is wrong! Expecting end array in line: " << m_JsonScanner.scannedLine() << endl;
				}

				break;
			default:
				break;
			}
		}
		catch(const char* error)
		{
			cout << "Invalid character " << error << " at line no: " << m_JsonScanner.scannedLine() << endl;
		}
	}

	return ret;
}

void CJson::setMediaName(std::string name)
{
	m_filenameJson = name + "-JsonDB.txt";
}

void CJson::connectToPoiDB(CPoiDatabase* pPoiDB)
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

void CJson::connectToWpDB(CWpDatabase* pWpDB)
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

/*
 * CRoute.cpp
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */


#include "CRoute.h"
#include <iostream>
using namespace std;

/* CRoute constructor method definition
 * Initializes the class members with the given values
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: NONE
 * */
CRoute::CRoute()
{
	m_pPoiDatabase = NULL;
	m_pWpDatabase = NULL;
	m_numPOI = 0;
	m_numWp = 0;
}

/* CRoute copy constructor method definition
 * Copies the class members with the passed class member values
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: NONE
 * */
CRoute::CRoute(const CRoute& orig):m_pRoute(orig.m_pRoute)
{
	m_pPoiDatabase = orig.m_pPoiDatabase;
	m_pWpDatabase = orig.m_pWpDatabase;
	m_numPOI = orig.m_numPOI;
	m_numWp = orig.m_numWp;
}

/* CRoute destructor method definition
 *
 * PARAMETERS: NONE
 *
 * RETURN: NONE
 * */
CRoute::~CRoute()
{

}

/* CRoute::connectToPoiDatabase() method definition
 * Connects the CRoute to CNavigation system database
 *
 * PARAMETERS: 	(CPoiDatabase*) pPoiDB - Pointer variable holding the address of the database
 *
 * RETURN: NONE
 * */
void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	/* Check if database address is not NULL */
	if(pPoiDB != NULL)
	{
		/* Assign address of database to the pointer variable */
		m_pPoiDatabase = pPoiDB;
	}
	else
		/* Database address is NULL */
	{
		/* Print error message */
		cout << "ERROR: Connection to CPOI database failed!!" << endl;
	}

}

/* CRoute::addWaypoint() method definition
 * Adds the Waypoint to the route
 *
 * PARAMETERS: 	(string) name - Name of the Waypoint to be added
 *
 * RETURN: NONE
 * */
void CRoute::addWaypoint(std::string name)
{
	if(m_pWpDatabase != NULL)
	{
		if(m_pWpDatabase->getPointerToWaypoint(name) != NULL)
		{
			m_pRoute.push_back(m_pWpDatabase->getPointerToWaypoint(name));
			m_numWp++;
		}
		else
		{
			cout << "ERROR: Couldn't add Waypoint in the Route!! Waypoint not found in database" << endl;
		}
	}
	else
	{
		cout << "ERROR: Connection to Waypoint database is either not done or failed!!" << endl;
	}
}

/* CRoute::addPoi() method definition
 * Adds the POI to the route after the given Waypoint
 *
 * PARAMETERS: 	(string) namePoi - Name of the POI to be added
 * 				(string) afterWp - Name of the Waypoint after which POI will be added
 *
 * RETURN: NONE
 * */
void CRoute::addPoi(std::string namePoi, std::string afterWp)
{

	if(m_pPoiDatabase != NULL)
	{
		if(m_pPoiDatabase->getPointerToPoi(namePoi) != NULL)
		{
			for(list<const CWaypoint*>::reverse_iterator i=m_pRoute.rbegin(); i != m_pRoute.rend(); ++i)
			{
				if((*i)->getName() == afterWp)
				{
					m_pRoute.insert(i.base(),m_pPoiDatabase->getPointerToPoi(namePoi));
					m_numPOI++;
					break;
				}
				else
				{
//					if(!(i.base() == m_pRoute.end()))
//					{
						cout << "ERROR: POI addition to route failed! Waypoint not found in Route!" <<endl;
//					}
				}
			}
		}
		else
		{
			cout << "ERROR: POI addition to route failed! POI not found in database!" <<endl;
		}
	}
	else
	{
		cout << "Connection to database failed!!" << endl;
	}
}

/* CRoute::connectToWpDatabase() method definition
 * Connects the CRoute to CWpDatabase system database
 *
 * PARAMETERS: 	(CWpDatabase*) pWpDB - Pointer variable holding the address of the Waypoint database
 *
 * RETURN: NONE
 * */
void CRoute::connectToWpDatabase(CWpDatabase* pWpDB)
{
	/* Check if database address is not NULL */
	if(pWpDB != NULL)
	{
		/* Assign address of database to the pointer variable */
		m_pWpDatabase = pWpDB;
	}
	else
		/* Database address is NULL */
	{
		/* Print error message */
		cout << "ERROR: Connection to Waypoint database failed!!" << endl;
	}
}

/* CRoute::print() method definition
 * Prints all the waypoints and POIs of the route
 *
 * PARAMETERS: NONE
 *
 * RETURN: NONE
 * */
void CRoute::print()
{
	cout << "Our route has " << m_numWp << " Waypoints and " << m_numPOI << " Point of Interests" << endl <<endl;
	 /* all Waypoints*/
	 /*Check if pointer has valid address and some Waypoints are added*/
	if(!m_pRoute.empty())
	{
		for(list<const CWaypoint*>::iterator it=m_pRoute.begin(); it!=m_pRoute.end();it++)
		{
			if(NULL != dynamic_cast<const CPOI*> (*it))
				cout << *dynamic_cast<const CPOI*> (*it) << endl;
			else
				cout << (*(*it))  << endl;
		}
	}
	else
	{
		cout << "No entries found in Database!" << endl;
	}
}

/* operator+=() overloaded operator "+=" method definition
 * Searches for the given Waypoint/POI and adds the same at the end, if both are found Waypoint is added first
 * and POI will be added later
 *
 * PARAMETERS: (string) name - Name of the Waypoint/POI to be added
 *
 * RETURN: NONE
 * */
CRoute& CRoute::operator+=(std::string name)
{
	if(NULL != m_pWpDatabase->getPointerToWaypoint(name))
	{
		addWaypoint(name);
		if(NULL != m_pPoiDatabase->getPointerToPoi(name))
		{
			addPoi(name,name);
		}
	}
	else
	{
		if(NULL != m_pPoiDatabase->getPointerToPoi(name))
		{
			cout << "Waypoint not found in database, POI will be added in the end if found in Database" << endl;
			m_pRoute.push_back(m_pPoiDatabase->getPointerToPoi(name));
			m_numPOI++;
		}
		else
		{
			cout << "POI not found in database" << endl;
		}
	}
	return (*this);
}


void CRoute::clearRoute()
{
	m_numPOI = 0;
	m_numWp = 0;
	m_pRoute.clear();
}

const std::list<const CWaypoint*> CRoute::getRoute()
{
	return m_pRoute;
}
/* operator=() overloaded operator "=" method definition
 * Copies the passed route to the existing route
 *
 * PARAMETERS: (CRoute) r1 - Route to be concatenated to the existing route
 *
 * RETURN: (CRoute) - Returns the final route
 * */
CRoute& CRoute::operator=(const CRoute& r2)
{
	m_numPOI = r2.m_numPOI;
	m_numWp = r2.m_numWp;
	m_pPoiDatabase = r2.m_pPoiDatabase;
	m_pWpDatabase = r2.m_pWpDatabase;
	m_pRoute.assign(r2.m_pRoute.begin(),r2.m_pRoute.end());
	return *this;
}

CRoute operator+(CRoute& c1, CRoute& c2)
{
	CRoute result;
	if((c1.m_pPoiDatabase == c2.m_pPoiDatabase) and (c1.m_pWpDatabase == c2.m_pWpDatabase))
	{
		for(list<const CWaypoint *>::iterator it1 = c1.m_pRoute.begin(); it1!=c1.m_pRoute.end();it1++)
		{
			if(NULL != dynamic_cast<const CPOI*> (*it1))
			{
				++result.m_numPOI;
			}
			else
			{
				++result.m_numWp;
			}
		}
		for(list<const CWaypoint *>::iterator it2 = c2.m_pRoute.begin(); it2 != c2.m_pRoute.end(); it2++)
		{
			if(NULL != dynamic_cast<const CPOI*> (*it2))
			{
				++result.m_numPOI;
			}
			else
			{
				++result.m_numWp;
			}
		}
		result.m_pRoute.insert(result.m_pRoute.end(),c1.m_pRoute.begin(),c1.m_pRoute.end());
		result.m_pRoute.insert(result.m_pRoute.end(),c2.m_pRoute.begin(),c2.m_pRoute.end());
		result.m_pPoiDatabase = c1.m_pPoiDatabase;
		result.m_pWpDatabase = c1.m_pWpDatabase;
	}
	else
	{
		cout << "ERROR: Routes to be added are not connected to same Waypoint and POI databases!" << endl;
	}
	return result;
}

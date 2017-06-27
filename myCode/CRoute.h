/*
 * CRoute.h
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */

#ifndef CROUTE_H_
#define CROUTE_H_

#include <string>
#include <list>
#include <iterator>
#include <algorithm>
#include <numeric>

#include "CWaypoint.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"



/* Class CRoute declaration*/
class CRoute
{
	/* operator+() overloaded operator "+" method definition
	 * Concatenates the given route to the existing route
	 *
	 * PARAMETERS: (CRoute) r1 - Route to be concatenated to the existing route
	 *
	 * RETURN: (CRoute) - Returns the final route
	 * */
	friend CRoute operator+(CRoute& c1, CRoute& c2);
private:
	unsigned int m_numWp;
	unsigned int m_numPOI;
    /**
     * @clientCardinality 1 
     */
	std::list<const CWaypoint *> m_pRoute;
    /**
     * @clientCardinality 1 
     */
	CPoiDatabase* m_pPoiDatabase;
    /**
     * @clientCardinality 1 
     */
	CWpDatabase* m_pWpDatabase;
public:
	/* CRoute constructor method definition
	 * Initializes the class members with the given values
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: NONE
	 * */
	CRoute();
	/* CRoute copy constructor method definition
	 * Initializes the class members with the given values
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: NONE
	 * */
	CRoute(const CRoute& orig);
	/* CRoute destructor method definition
	 *
	 * PARAMETERS: NONE
	 *
	 * RETURN: NONE
	 * */
	~CRoute();
	/* CRoute::connectToPoiDatabase() method definition
	 * Connects the CRoute to CPoiDatabase system database
	 *
	 * PARAMETERS: 	(CPoiDatabase*) pPoiDB - Pointer variable holding the address of the POI database
	 *
	 * RETURN: NONE
	 * */
	void connectToPoiDatabase(CPoiDatabase* pPoiDB);
	/* CRoute::connectToWpDatabase() method definition
	 * Connects the CRoute to CWpDatabase system database
	 *
	 * PARAMETERS: 	(CWpDatabase*) pWpDB - Pointer variable holding the address of the Waypoint database
	 *
	 * RETURN: NONE
	 * */
	void connectToWpDatabase(CWpDatabase* pWpDB);
	/* CRoute::addWaypoint() method definition
	 * Adds the Waypoint to the route
	 *
	 * PARAMETERS: 	(string) name - Name of the Waypoint to be added
	 *
	 * RETURN: NONE
	 * */
	void addWaypoint(std::string name);
	/* CRoute::addPoi() method definition
	 * Adds the POI to the route after the given Waypoint
	 *
	 * PARAMETERS: 	(string) namePoi - Name of the POI to be added
	 * 				(string) afterWp - Name of the Waypoint after which POI will be added
	 *
	 * RETURN: NONE
	 * */
	void addPoi(std::string namePoi, std::string afterWp);
	/* CRoute::print() method definition
	 * Prints all the waypoints and POIs of the route
	 *
	 * PARAMETERS: NONE
	 *
	 * RETURN: NONE
	 * */
	void print();
	void clearRoute();
	const std::list<const CWaypoint*> getRoute();
	/* operator+=() overloaded operator "+=" method definition
	 * Searches for the given Waypoint/POI and adds the same at the end, if both are found Waypoint is added first
	 * and POI will be added later
	 *
	 * PARAMETERS: (string) name - Name of the Waypoint/POI to be added
	 *
	 * RETURN: NONE
	 * */
	CRoute& operator+=(std::string name);
	/* operator=() overloaded operator "=" method definition
	 * Copies the passed route to the existing route
	 *
	 * PARAMETERS: (CRoute) r1 - Route to be concatenated to the existing route
	 *
	 * RETURN: (CRoute) - Returns the final route
	 * */
	CRoute& operator=(const CRoute&);
};

#endif /* CROUTE_H_ */

/*
 * CNavigationSystem.h
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */

#ifndef CNAVIGATIONSYSTEM_H_
#define CNAVIGATIONSYSTEM_H_

#include "CGPSSensor.h"
#include "CRoute.h"
#include "CWpDatabase.h"
#include "CPersistenceComp.h"
#include "CJson.h"

/* Macros for max Waypoints and POIs in a route */
#define ROUTE_MAXWP		2
#define ROUTE_MAXPOI	8


/* Class CNavigationSystem declaration*/
class CNavigationSystem
{
private:
    /**
     * @link aggregationByValue 
     * @clientCardinality 1
     * @supplierCardinality 1
     */
	CGPSSensor m_GPSSensor;
    /**
     * @link aggregationByValue 
     * @clientCardinality 1
     * @supplierCardinality 1
     */
	CRoute m_route;
    /**
     * @link aggregationByValue
     * @clientCardinality 1
     * @supplierCardinality 1 
     */
	CRoute temp_route;
    /**
     * @link aggregationByValue 
     * @supplierCardinality 1
     * @clientCardinality 1
     */
	CPoiDatabase m_PoiDatabase;
    /**
     * @link aggregationByValue
     * @clientCardinality 1
     * @supplierCardinality 1 
     */
    CWpDatabase m_WpDatabase;
    /**
     * @link aggregationByValue
     * @clientCardinality 1
     * @supplierCardinality 1 
     */
    CPersistenceComp m_PerComp;
    CJson m_Json;
    /* CNavigationSystem::enterRoute() method definition
     * Creates the route
     *
     * PARAMETERS: 	NONE
     *
     * RETURN: NONE
     * */
	void enterRoute();
	/* CNavigationSystem::printRoute() method definition
	 * Prints the entire route
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: NONE
	 * */
	void printRoute();
public:
	/* CNavigationSystem constructor method definition
	 * Initializes the class members with the given values
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: NONE
	 * */
	CNavigationSystem();
	/* CNavigationSystem::run() method definition
	 * Run program to create the route, print the route and calculates and prints the distance between
	 * current position and nearest POI
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: NONE
	 * */
	void run();
};

#endif /* CNAVIGATIONSYSTEM_H_ */

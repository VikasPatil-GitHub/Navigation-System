/*
 * CNavigationSystem.cpp
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */

#include "CNavigationSystem.h"
#include <iostream>

using namespace std;
/* CNavigationSystem constructor method definition
 * Initializes the class members with the given values
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: NONE
 * */
CNavigationSystem::CNavigationSystem()
{

}

/* CNavigationSystem::enterRoute() method definition
 * Creates the route
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: NONE
 * */
void CNavigationSystem::enterRoute()
{
	bool result=false;

	//	Connect to POI Database
	m_route.connectToPoiDatabase(&m_PoiDatabase);
	temp_route.connectToPoiDatabase(&m_PoiDatabase);


	//	Connect to Waypoint Database
	m_route.connectToWpDatabase(&m_WpDatabase);
	temp_route.connectToWpDatabase(&m_WpDatabase);

	//	 Create Waypoints
	CWaypoint Wp_Home("Quartier 56, Dieburg", 49.9053, 8.8607);
	CWaypoint Wp_Univ("h_da, Darmstadt", 49.8664, 8.6333);
	CWaypoint Wp_mid("middle", 49.7646, 8.7664);
	CWaypoint Wp_Penny("PENNY-markt discounter", 49.8978, 8.8426);
	CWaypoint Wp_dieburg("dieburg", 87, 91);


	//	Create POIs
	CPOI POI1(SUPERMARKET, "Edeka Aktiv Markt", "Nearest super market to home", 49.8964, 8.8288);
	CPOI POI2(BUSSTOP, "Dieburg Hochschule Nord", "Nearest bus stop to home", 49.9024, 8.8542);
	CPOI POI3(RAILWAYSTATION, "Dieburg Bahnhof", "Dieburg Railway station", 49.9034, 8.8405);
	CPOI POI4(SUPERMARKET, "PENNY-markt discounter", "Best super market near home", 49.8978, 8.8426);
	CPOI POI5(PUBSANDBARS, "Irish Pub", "Nearest pub to college", 49.8783, 8.6595);


	//	 Add Waypoints to route
//	m_WpDatabase.addWaypoint(Wp_Home);
//	m_WpDatabase.addWaypoint(Wp_Univ);
//	m_WpDatabase.addWaypoint(Wp_mid);
//	m_WpDatabase.addWaypoint(Wp_Penny);
//	m_WpDatabase.addWaypoint(Wp_dieburg);

	//	 Add POIs to Database

//	m_PoiDatabase.addPoi(POI1);
//	m_PoiDatabase.addPoi(POI2);
//	m_PoiDatabase.addPoi(POI3);
//	m_PoiDatabase.addPoi(POI4);
//	m_PoiDatabase.addPoi(POI5);

//	m_PerComp.setMediaName("File");
//	m_PerComp.writeData(m_WpDatabase,m_PoiDatabase);
//	m_PerComp.readData(m_WpDatabase,m_PoiDatabase,CPersistentStorage::MERGE);

	m_Json.setMediaName("Write");
	m_Json.connectToPoiDB(&m_PoiDatabase);
	m_Json.connectToWpDB(&m_WpDatabase);
//	m_Json.writeData(m_WpDatabase,m_PoiDatabase);
	result = m_Json.readData(m_WpDatabase,m_PoiDatabase,CPersistentStorage::REPLACE);
	if(result)
	{
		m_route.clearRoute();
	}


	//	Add Waypoints to Route
	m_route.addWaypoint("Quartier 56, Dieburg");
	m_route.addWaypoint("h_da, Darmstadt");
	temp_route.addWaypoint("middle");



	//	Add POIs to Route
	m_route.addPoi("Edeka Aktiv Markt","Quartier 56, Dieburg");
	m_route.addPoi("Dieburg Hochschule Nord","h_da, Darmstadt");
	temp_route.addPoi("Dieburg Bahnhof","middle");

	cout << "==============" << endl;
	cout << "Test operatotr+=" << endl;
	cout << "==============" << endl;
	cout << "m_route print before operator+=" << endl;
	cout << "==============" << endl;
//	m_route.print();
	cout << "===============" << endl;
	cout << "temp_route print before operator+=" << endl;
	cout << "===============" << endl;
//	temp_route.print();
	// Add POI and/or Waypoint to Route using the overloaded operator +=
	m_route += "PENNY-markt discounter";
	cout << "==============" << endl;
	cout << "m_route print after operator+=" << endl;
	cout << "==============" << endl;
//	m_route.print();
	cout << "===============" << endl;
	cout << "temp_route print after operator+= - empty" << endl;
	cout << "===============" << endl;
//	temp_route.print();

	// Add two routes using overloaded operator +
	temp_route.addWaypoint("dieburg");
	temp_route.addPoi("Irish Pub","dieburg");
	cout << "==============" << endl;
	cout << "Test operator+" << endl;
	cout << "==============" << endl;
	cout << "m_route print before operator+" << endl;
	cout << "==============" << endl;
//	m_route.print();
	cout << "===============" << endl;
	cout << "temp_route print before operator+" << endl;
	cout << "===============" << endl;
//	temp_route.print();
	m_route = m_route + temp_route;
	cout << "==============" << endl;
	cout << "m_route print after operator+ operation" << endl;
	cout << "==============" << endl;
//	m_route.print();
	cout << "==============" << endl;
	cout << "temp_route print after operator+ operation - No change" << endl;
	cout << "==============" << endl;
//	temp_route.print();

	// Copy route using operator=
	cout << "==============" << endl;
	cout << "Test operator=" << endl;
	cout << "==============" << endl;
	cout << "m_route print before operator=" << endl;
	cout << "==============" << endl;
//	m_route.print();
	cout << "===============" << endl;
	cout << "temp_route print before operator=" << endl;
	cout << "===============" << endl;
//	temp_route.print();
//	temp_route = m_route;
	cout << "==============" << endl;
	cout << "m_route print after operator=" << endl;
	cout << "==============" << endl;
//	m_route.print();
	cout << "===============" << endl;
	cout << "temp_route print after operator=" << endl;
	cout << "===============" << endl;
//	temp_route.print();
//	m_route = m_route + temp_route;
	cout << "==============" << endl;
	cout << "m_route print after changing m_route" << endl;
	cout << "==============" << endl;
//	m_route.print();
	cout << "===============" << endl;
	cout << "temp_route print after changing m_route - No change" << endl;
	cout << "===============" << endl;
//	temp_route.print();

	cout << "==============" << endl;
	cout << "Test copy constructor" << endl;
	cout << "==============" << endl;
	cout << "m_route print before copy constructor" << endl;
	cout << "==============" << endl;
//	m_route.print();
//	CRoute new_route(m_route);
	cout << "==============" << endl;
	cout << "m_route print after copy constructor" << endl;
	cout << "==============" << endl;
//	m_route.print();
	cout << "===============" << endl;
	cout << "new_route print after copy constructor" << endl;
	cout << "===============" << endl;
//	new_route.print();
//	m_route = m_route + temp_route;
	cout << "==============" << endl;
	cout << "m_route print after copy constructor" << endl;
	cout << "==============" << endl;
//	m_route.print();
	cout << "===============" << endl;
	cout << "new_route print after copy constructor" << endl;
	cout << "===============" << endl;
//	new_route.print();

}

/* CNavigationSystem::printRoute() method definition
 * Prints the entire route
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: NONE
 * */
void CNavigationSystem::printRoute()
{
	m_route.print();
}


/* CNavigationSystem::run() method definition
 * Run program to create the route, print the route and calculates and prints the distance between
 * current position and nearest POI
 *
 * PARAMETERS: 	NONE
 *
 * RETURN: NONE
 * */
void CNavigationSystem::run()
{
	cout << "==============" << endl;
	cout << "Creating route" << endl;
	cout << "==============" << endl;
	enterRoute();
	cout << "==============" << endl;
	cout << "Printing route" << endl;
	cout << "==============" << endl;
	printRoute();

}

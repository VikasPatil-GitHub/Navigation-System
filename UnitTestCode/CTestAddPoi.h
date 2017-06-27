/*
 * CTestAddPoi.h
 *
 *  Created on: 21-Jan-2016
 *      Author: Vikas Patil
 */

#ifndef CTESTADDPOI_H_
#define CTESTADDPOI_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CPoiDatabase.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CRoute.h"

class CTestAddPoi: public CppUnit::TestFixture {
private:
	CRoute m_Route;
	CPoiDatabase m_PoiDatabase;
	CWpDatabase m_WpDatabase;
	CWaypoint m_Waypoint;
	CPOI m_POI;
public:

	void setUp()
	{
		m_Waypoint = CWaypoint("Quartier 56, Dieburg", 49.9053, 8.8607);
		m_POI = CPOI(SUPERMARKET, "Edeka Aktiv Markt", "Nearest super market to home", 49.8964, 8.8288);
	}

	void testFailCaseInvalidPoiDB()
	{
		cout << endl << "========================================" << endl;
		cout << "Add POI to route  CRoute::addPoi( ) test" << endl;
		cout << "========================================" << endl;
		CPPUNIT_API(m_Route.connectToPoiDatabase(NULL));
		CPPUNIT_API(m_Route.addPoi("Edeka Aktiv Markt","Quartier 56, Dieburg"));
		CPPUNIT_ASSERT(m_Route.getRoute().empty());
	}

	void testFailCasePoiNotInDB()
	{
		CPPUNIT_API(m_Route.connectToPoiDatabase(&m_PoiDatabase));
		CPPUNIT_API(m_Route.addPoi("Edeka Aktiv Markt","Quartier 56, Dieburg"));
		CPPUNIT_ASSERT(m_Route.getRoute().empty());
	}

	void testFailCaseWpNotInRoute()
	{
		CPPUNIT_API(m_WpDatabase.addWaypoint(m_Waypoint));
		CPPUNIT_API(m_PoiDatabase.addPoi(m_POI));
		CPPUNIT_API(m_Route.connectToPoiDatabase(&m_PoiDatabase));
		CPPUNIT_API(m_Route.connectToWpDatabase(&m_WpDatabase));
		CPPUNIT_API(m_Route.addWaypoint("Quartier 56, Dieburg"));
		CPPUNIT_API(m_Route.addPoi("Edeka Aktiv Markt","Quartier 56, Dieburg1"));
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		CPPUNIT_ASSERT(49.9053 == (*it)->getLatitude());
		CPPUNIT_ASSERT(8.8607 == (*it)->getLongitude());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
	}
	void testPassCaseWpInRoute()
	{
		CPPUNIT_API(m_WpDatabase.addWaypoint(m_Waypoint));
		CPPUNIT_API(m_PoiDatabase.addPoi(m_POI));
		CPPUNIT_API(m_Route.connectToPoiDatabase(&m_PoiDatabase));
		CPPUNIT_API(m_Route.connectToWpDatabase(&m_WpDatabase));
		CPPUNIT_API(m_Route.addWaypoint("Quartier 56, Dieburg"));
		CPPUNIT_API(m_Route.addPoi("Edeka Aktiv Markt","Quartier 56, Dieburg"));
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		CPPUNIT_ASSERT(49.9053 == (*it)->getLatitude());
		CPPUNIT_ASSERT(8.8607 == (*it)->getLongitude());
		advance(it,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it)->getName());
		CPPUNIT_ASSERT(49.8964 == (*it)->getLatitude());
		CPPUNIT_ASSERT(8.8288 == (*it)->getLongitude());
		CPPUNIT_ASSERT(SUPERMARKET == dynamic_cast<const CPOI*> (*it)->getType());
		CPPUNIT_ASSERT("Nearest super market to home" == dynamic_cast<const CPOI*> (*it)->getDescription());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
	}

	void testRoutePrint()
	{
		CPPUNIT_ASSERT(m_Route.getRoute().empty());
		m_Route.print();
		CPPUNIT_API(m_WpDatabase.addWaypoint(m_Waypoint));
		CPPUNIT_API(m_PoiDatabase.addPoi(m_POI));
		CPPUNIT_API(m_Route.connectToPoiDatabase(&m_PoiDatabase));
		CPPUNIT_API(m_Route.connectToWpDatabase(&m_WpDatabase));
		CPPUNIT_API(m_Route.addWaypoint("Quartier 56, Dieburg"));
		CPPUNIT_API(m_Route.addPoi("Edeka Aktiv Markt","Quartier 56, Dieburg"));
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		CPPUNIT_ASSERT(49.9053 == (*it)->getLatitude());
		CPPUNIT_ASSERT(8.8607 == (*it)->getLongitude());
		advance(it,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it)->getName());
		CPPUNIT_ASSERT(49.8964 == (*it)->getLatitude());
		CPPUNIT_ASSERT(8.8288 == (*it)->getLongitude());
		CPPUNIT_ASSERT(SUPERMARKET == dynamic_cast<const CPOI*> (*it)->getType());
		CPPUNIT_ASSERT("Nearest super market to home" == dynamic_cast<const CPOI*> (*it)->getDescription());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
		m_Route.print();
	}



	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Add POI to route  CRoute::addPoi( ) test");
		suite->addTest(new CppUnit::TestCaller<CTestAddPoi>
				 ("Test adding POI with invalid POI database", &CTestAddPoi::testFailCaseInvalidPoiDB));
		suite->addTest(new CppUnit::TestCaller<CTestAddPoi>
				 ("Test adding valid POI to the route with POI not added in database", &CTestAddPoi::testFailCasePoiNotInDB));
		suite->addTest(new CppUnit::TestCaller<CTestAddPoi>
				 ("Test adding POI with Waypoint not in route", &CTestAddPoi::testFailCaseWpNotInRoute));
		suite->addTest(new CppUnit::TestCaller<CTestAddPoi>
				 ("Test adding POI - Pass case", &CTestAddPoi::testPassCaseWpInRoute));
		suite->addTest(new CppUnit::TestCaller<CTestAddPoi>
				 ("Test route print", &CTestAddPoi::testRoutePrint));
		return suite;
	}
};




#endif /* CTESTADDPOI_H_ */

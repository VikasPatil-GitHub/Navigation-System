/*
 * CTestOperatorOverloading.h
 *
 *  Created on: 22-Jan-2016
 *      Author: Vikas Patil
 */

#ifndef CTESTOPERATOROVERLOADING_H_
#define CTESTOPERATOROVERLOADING_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CPoiDatabase.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CRoute.h"

class CTestOperatorOverloading: public CppUnit::TestFixture {
private:
	CRoute m_Route, m_Route2;
	CPoiDatabase m_PoiDatabase,m_PoiDatabase2;
	CWpDatabase m_WpDatabase,m_WpDatabase2;
	CWaypoint m_Waypoint, m_Waypoint2;
	CPOI m_POI, m_POI2, m_POI3;
public:

	void setUp()
	{
		m_Waypoint = CWaypoint("Quartier 56, Dieburg", 49.9053, 8.8607);
		m_Waypoint2 = CWaypoint("PENNY-markt discounter", 49.8978, 8.8426);
		m_POI = CPOI(SUPERMARKET, "Edeka Aktiv Markt", "Nearest super market to home", 49.8964, 8.8288);
		m_POI2 = CPOI (SUPERMARKET, "PENNY-markt discounter", "Best super market near home", 49.8978, 8.8426);
		m_POI3 = CPOI (BUSSTOP, "Dieburg Hochschule Nord", "Nearest bus stop to home", 49.9024, 8.8542);
		CPPUNIT_API(m_WpDatabase.addWaypoint(m_Waypoint));
		CPPUNIT_API(m_PoiDatabase.addPoi(m_POI));
		CPPUNIT_API(m_WpDatabase.addWaypoint(m_Waypoint2));
		CPPUNIT_API(m_PoiDatabase.addPoi(m_POI2));
		CPPUNIT_API(m_Route.connectToPoiDatabase(&m_PoiDatabase));
		CPPUNIT_API(m_Route.connectToWpDatabase(&m_WpDatabase));
		CPPUNIT_API(m_Route2.connectToPoiDatabase(&m_PoiDatabase));
		CPPUNIT_API(m_Route2.connectToWpDatabase(&m_WpDatabase));
		CPPUNIT_API(m_Route.addWaypoint("Quartier 56, Dieburg"));
		CPPUNIT_API(m_Route.addPoi("Edeka Aktiv Markt","Quartier 56, Dieburg"));
	}

	void testfailOperatorPlusEqualOnlyPOI()
	{
		cout << endl << "===========================" << endl;
		cout << "Operator+= overloading test" << endl;
		cout << "===========================" << endl;
		CPPUNIT_API(m_Route += "Dieburg Hochschule Nord");
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
	}

	void testPassOperatorPlusEqualOnlyPOI()
	{
		CPPUNIT_API(m_PoiDatabase.addPoi(m_POI3));
		CPPUNIT_API(m_Route += "Dieburg Hochschule Nord");
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("Dieburg Hochschule Nord" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
	}

	void testPassOperatorPlusEqualBothPOIWp()
	{
		CPPUNIT_API(m_Route += "PENNY-markt discounter");
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("PENNY-markt discounter" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("PENNY-markt discounter" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
	}

	void testPassOperatorEqual()
	{
		CPPUNIT_API(m_Route2 = m_Route);
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
		list<const CWaypoint*> newList2;
		newList2 = m_Route2.getRoute();
		list<const CWaypoint*>::const_iterator it2 = newList2.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it2)->getName());
		advance(it2,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it2)->getName());
		advance(it2,1);
		CPPUNIT_ASSERT(it2 == newList2.end());
		CPPUNIT_API(m_Route += "PENNY-markt discounter");
		list<const CWaypoint*> newList3;
		newList3 = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it3 = newList3.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it3)->getName());
		advance(it3,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it3)->getName());
		advance(it3,1);
		CPPUNIT_ASSERT("PENNY-markt discounter" == (*it3)->getName());
		advance(it3,1);
		CPPUNIT_ASSERT("PENNY-markt discounter" == (*it3)->getName());
		advance(it3,1);
		CPPUNIT_ASSERT(it3 == newList3.end());
		list<const CWaypoint*> newList4;
		newList4 = m_Route2.getRoute();
		list<const CWaypoint*>::const_iterator it4 = newList4.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it4)->getName());
		advance(it4,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it4)->getName());
		advance(it4,1);
		CPPUNIT_ASSERT(it4 == newList4.end());
	}

	void testFailOperatorPlus()
	{
		CPPUNIT_API(m_Route2.connectToPoiDatabase(&m_PoiDatabase2));
		CPPUNIT_API(m_Route2.connectToWpDatabase(&m_WpDatabase2));
		CPPUNIT_API(m_Route = m_Route + m_Route2);
		CPPUNIT_ASSERT(m_Route.getRoute().empty());
		CPPUNIT_ASSERT(m_Route2.getRoute().empty());
	}

	void testPassOperatorPlus()
	{
		CPPUNIT_API(m_Route2.addWaypoint("PENNY-markt discounter"));
		CPPUNIT_API(m_Route2.addPoi("PENNY-markt discounter","PENNY-markt discounter"));
		CPPUNIT_API(m_Route = m_Route + m_Route2);
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("PENNY-markt discounter" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("PENNY-markt discounter" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
		list<const CWaypoint*> newList2;
		newList2 = m_Route2.getRoute();
		list<const CWaypoint*>::const_iterator it2 = newList2.begin();
		CPPUNIT_ASSERT("PENNY-markt discounter" == (*it2)->getName());
		advance(it2,1);
		CPPUNIT_ASSERT("PENNY-markt discounter" == (*it2)->getName());
		advance(it2,1);
		CPPUNIT_ASSERT(it2 == newList2.end());
	}

	void testCopyConstructor()
	{
		CRoute new_Route(m_Route);
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
		list<const CWaypoint*> newList2;
		newList2 = new_Route.getRoute();
		list<const CWaypoint*>::const_iterator it2 = newList2.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it2)->getName());
		advance(it2,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it2)->getName());
		advance(it2,1);
		CPPUNIT_ASSERT(it2 == newList2.end());
	}

	void testClearRoute()
	{
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT("Edeka Aktiv Markt" == (*it)->getName());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
		m_Route.clearRoute();
		CPPUNIT_ASSERT(m_Route.getRoute().empty());
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Operator+= overloading test");
		suite->addTest(new CppUnit::TestCaller<CTestOperatorOverloading>
				 ("Test Operator+= overloading add only POI - Fail", &CTestOperatorOverloading::testfailOperatorPlusEqualOnlyPOI));
		suite->addTest(new CppUnit::TestCaller<CTestOperatorOverloading>
				 ("Test Operator+= overloading add only POI - Pass", &CTestOperatorOverloading::testPassOperatorPlusEqualOnlyPOI));
		suite->addTest(new CppUnit::TestCaller<CTestOperatorOverloading>
				 ("Test Operator+= overloading add both POI and Waypoint", &CTestOperatorOverloading::testPassOperatorPlusEqualBothPOIWp));
		suite->addTest(new CppUnit::TestCaller<CTestOperatorOverloading>
				 ("Test Operator= overloading", &CTestOperatorOverloading::testPassOperatorEqual));
		suite->addTest(new CppUnit::TestCaller<CTestOperatorOverloading>
				 ("Test Operator+ overloading - Fail", &CTestOperatorOverloading::testFailOperatorPlus));
		suite->addTest(new CppUnit::TestCaller<CTestOperatorOverloading>
				 ("Test Operator= overloading - Pass", &CTestOperatorOverloading::testPassOperatorPlus));
		suite->addTest(new CppUnit::TestCaller<CTestOperatorOverloading>
				 ("Test Operator= overloading - Pass", &CTestOperatorOverloading::testCopyConstructor));
		suite->addTest(new CppUnit::TestCaller<CTestOperatorOverloading>
				 ("Test clear route - Pass", &CTestOperatorOverloading::testClearRoute));
		return suite;
	}
};



#endif /* CTESTOPERATOROVERLOADING_H_ */

/*
 * CTestAddWaypoint.h
 *
 *  Created on: 21-Jan-2016
 *      Author: Vikas Patil
 */

#ifndef CTESTADDWAYPOINT_H_
#define CTESTADDWAYPOINT_H_

#include <string>

using namespace std;

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "../myCode/CWpDatabase.h"
#include "../myCode/CRoute.h"

class CTestAddWaypoint: public CppUnit::TestFixture {
private:
	CRoute m_Route;
	CWpDatabase m_WpDatabase;
	CWaypoint m_Waypoint;
public:

	void setUp()
	{
		m_Waypoint = CWaypoint("Quartier 56, Dieburg", 49.9053, 8.8607);
	}

	void testInvalidWp()
	{
		cout << endl << "==================================================" << endl;
		cout << "Add Waypoint to route  CRoute::addWaypoint( ) test" << endl;
		cout << "==================================================" << endl;
		CPPUNIT_API(m_Route.connectToWpDatabase(&m_WpDatabase));
		CPPUNIT_API(m_Route.addWaypoint("Quartier 56, Dieburg"));
		CPPUNIT_ASSERT(m_Route.getRoute().empty());
	}
	void testValidWp()
	{
		CPPUNIT_API(m_WpDatabase.addWaypoint(m_Waypoint));
		CPPUNIT_API(m_Route.connectToWpDatabase(&m_WpDatabase));
		CPPUNIT_API(m_Route.addWaypoint("Quartier 56, Dieburg"));
		list<const CWaypoint*> newList;
		newList = m_Route.getRoute();
		list<const CWaypoint*>::const_iterator it = newList.begin();
		CPPUNIT_ASSERT("Quartier 56, Dieburg" == (*it)->getName());
		CPPUNIT_ASSERT(49.9053 == (*it)->getLatitude());
		CPPUNIT_ASSERT(8.8607 == (*it)->getLongitude());
		advance(it,1);
		CPPUNIT_ASSERT(it == newList.end());
	}

	void testInvalidWpDBAddress()
	{
		CPPUNIT_API(m_Route.connectToWpDatabase(NULL));
		CPPUNIT_API(m_Route.addWaypoint("Quartier 56, Dieburg"));
		CPPUNIT_ASSERT(m_Route.getRoute().empty());
	}



	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Add Waypoint to route  CRoute::addWaypoint( ) test");
		suite->addTest(new CppUnit::TestCaller<CTestAddWaypoint>
				 ("Test adding invalid Waypoint to the route", &CTestAddWaypoint::testInvalidWp));
		suite->addTest(new CppUnit::TestCaller<CTestAddWaypoint>
				 ("Test adding valid Waypoint to the route", &CTestAddWaypoint::testValidWp));
		suite->addTest(new CppUnit::TestCaller<CTestAddWaypoint>
				 ("Test adding Waypoint with Invalid Address", &CTestAddWaypoint::testInvalidWpDBAddress));
		return suite;
	}
};



#endif /* CTESTADDWAYPOINT_H_ */

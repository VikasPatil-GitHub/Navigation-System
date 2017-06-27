/*
 * main.cpp
 *
 *  Created on: 20-Jan-2016
 *      Author: Vikas Patil
 */

#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>

using namespace std;

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CTestAddPoi.h"
#include "CTestAddWaypoint.h"
#include "CTestOperatorOverloading.h"

using namespace CppUnit;

int main (void)
{
    // TODO: Fügen Sie ab hier Ihren Programmcode ein
	cout << "Unit Test gestarted." << endl << endl;
	TextUi::TestRunner runner;
	runner.addTest(CTestAddPoi::suite());
	runner.addTest(CTestAddWaypoint::suite());
	runner.addTest(CTestOperatorOverloading::suite());
	runner.run();
	return 0;
}




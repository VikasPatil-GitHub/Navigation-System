/*
 * CGPSSensor.h
 *
 *  Created on: 06-Nov-2015
 *      Author: Vikas Patil
 */

#ifndef CGPSSENSOR_H_
#define CGPSSENSOR_H_

#include "CWaypoint.h"

/* Class CGPSSensor declaration*/

class CGPSSensor
{
public:
	/* CGPSSensor constructor method definition
	 * Initializes the class members with the given values
	 *
	 * PARAMETERS: NONE
	 *
	 * RETURN: NONE
	 * */
	CGPSSensor();
	/* CGPSSensor::getCurrentPosition() method definition
	 * Returns a Waypoint of the current location after getting the latitude and longitude from the user
	 *
	 * PARAMETERS: 	NONE
	 *
	 * RETURN: (CWaypoint) - Waypoint of the current location
	 * */
	CWaypoint getCurrentPosition();
};

#endif /* CGPSSENSOR_H_ */

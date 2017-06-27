/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        :
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CSTRINGIO_H
#define CSTRINGIO_H



#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>

namespace myIO
{


/**
 * Variant2: C-like functions. As no member attribute access is required, the functions
 * are declared static. 
 */
class CString
{
public:
    /**
     * Returns a substring without leading and trailing characters, defined by the parameter t. 
	 * t usually is a whitespace character. 
     */
	static std::string trim(const std::string& source,
							 const std::string& t = " ");

    /**
     * Returns only digit characters of the string 
     */
	static std::string getDigits(const std::string& source, unsigned int count);

    /**
     * Gets all digits from a string and returns it into an integer. 
     */
	static double string2double(const std::string& source, unsigned int count);
   
	/**
     * Turns an integer into a string
     */
	static std::string double2String(double value);
    /**
     * Returns true if the substring exists 
     */
	static bool contains(const std::string& source, const std::string& sub);

    /**
     * Returns the left substring until the character provided by the parameter t. 
	 * Original string contains the right hand substring. 
     */
	static std::string cutLeft(std::string& source,
			                     const std::string& t = " ");
	static std::string cutRight(std::string& source,
				                     const std::string& t = " ");

};
/********************
**  CLASS END
*********************/
}; //namespace
#endif /* CSTRINGIO_H */

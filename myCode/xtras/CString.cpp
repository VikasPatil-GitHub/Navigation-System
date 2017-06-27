/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        :
* Author          :
* Description     :
*
*
****************************************************************************/


#include "CString.h"
#include "stdlib.h"
using namespace std;

namespace myIO {



/**
 * Variant2: C-like functions. As no member attribute access is required, the functions are declared static. 
 */
string CString::trim(const string& source, const string& t)
{	
	string result = source;
	result.erase( result.find_last_not_of(t));
	result.erase( 0, result.find_first_not_of(t));
	return result;
}

/**
 * Returns only digit characters of the string 
 */
string CString::getDigits(const string& source, unsigned int count)
{
	string result = "";
	
	for (size_t i=0; i<source.length();i++)
	{
		char d = source[i];
		if ((d >= '0' && d <= '9') || (d == '.'))
		{
			result += d;
		}
		else
		{
			result = "";
			if(contains(source,string(",")))
			{
				cout << "ERROR: Latitude or Longitude contains ',' in line" << count << ": " << source << endl;
			}
			else
			{
				cout << "ERROR: Latitude or Longitude contains special characters in line" << count << ": " << source << endl;
			}
			break;
		}
	}

	return result;
}

/**
 * Gets all digits from a string and returns it into an double.
 */
double CString::string2double(const string& source, unsigned int count)
{
	//Use stringstream to convert the data

	double digits = 0;
	istringstream instr;
	
	//Strip all none digits from the input string
	string onlydigits = getDigits(source,count);
	
	//Convert the string into a stream
	instr.str(onlydigits);
	
	//Store the stream content in an double variable
	instr >> digits;
	
	return digits;
}

string CString::double2String(double value)
{
	//Use a stringstream to convert a double into a string;

	stringstream iostr;
	string str;
	
	// Read the value into the outstream
	iostr << value;
	iostr >> str;

	return str;
}

/**
 * Returns true if the substring exists 
 */
bool CString::contains(const string& source, const string& sub)
{
	return (source.find(sub)!=string::npos);
}

/**
 * Returns the left substring until the character provided by the parameter t. Original string contains the right hand substring. 
 */
string CString::cutLeft(string& source, const string& t)
{
	string str = source;
	size_t pos = str.find(t);
	if (pos != string::npos)
	{
		str = str.substr(0,pos);
		source.erase(0,pos+1);
	}
	
	return str;
}


string CString::cutRight(string& source, const string& t)
{
	string str = source;
	size_t pos = str.find(t);
	if (pos != string::npos)
	{
		str = str.substr(pos+2,string::npos);
//		source.erase(0,pos+1);
	}

	return str;
}

} // namespace

/*
 * CDatabaseTemplate.h
 *
 *  Created on: 07-Jan-2016
 *      Author: Vikas Patil
 */

#ifndef CDATABASETEMPLATE_H_
#define CDATABASETEMPLATE_H_

#include <map>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <string>
#include <iostream>
#include "CPOI.h"


template<class K,class T>
class CDatabaseTemplate
{
private:
	std::map<K,T> m_DB;
public:
	CDatabaseTemplate();
	void addObject(const T& Obj);
	T* getPointerToObject(K key);
	typename std::map<K, T>::iterator getFirstObject(void);
	typename std::map<K, T>::iterator getLastObject(void);
	void clearDB(void);
};

template<class K, class T>
inline CDatabaseTemplate<K, T>::CDatabaseTemplate()
{
}

template<class K, class T>
inline void CDatabaseTemplate<K, T>::addObject(const T& Obj)
{
	std::pair<typename std::map<K,T>::iterator,bool> ret;

	ret = m_DB.insert(std::pair<K,T>(Obj.getName(), Obj));
	if(ret.second == 0)
	{
		std::cout << "Requested POI already exists in the database" << std::endl;
	}
}

template<class K, class T>
inline T* CDatabaseTemplate<K, T>::getPointerToObject(K key)
{
	typename std::map<K, T>::iterator i;
	i = m_DB.find(key);
	if (i != m_DB.end())
		return &i->second;

	/* Return NULL */
	return NULL;
}

template<class K, class T>
inline typename std::map<K, T>::iterator CDatabaseTemplate<K, T>::getFirstObject(void)
{
	typename std::map<K, T>::iterator i;
	i = m_DB.begin();
	return i;
}

template<class K, class T>
inline typename std::map<K, T>::iterator CDatabaseTemplate<K, T>::getLastObject(void)
{
	typename std::map<K, T>::iterator i;
	i = m_DB.end();
	return i;
}

template<class K, class T>
inline void CDatabaseTemplate<K, T>::clearDB(void)
{
	std::cout << "Clearing POI Database" << std::endl;
	m_DB.clear();
}

#endif /* CDATABASETEMPLATE_H_ */

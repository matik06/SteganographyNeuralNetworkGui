/*
 * Singleton.cpp
 *
 *  Created on: 2009-11-29
 *      Author: matik
 */

#include "Singleton.h"

Singleton::Singleton()
{

}

Singleton::~Singleton()
{
	delete[]weights;
}

Singleton & dataSettings()
{
	static Singleton dataSettings;
	return dataSettings;
}

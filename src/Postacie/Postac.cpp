/*
 * Postac.cpp
 *
 *  Created on: 13-02-2015
 *      Author: przemo
 */

#include "Postac.h"

Postac::Postac() :Obiekt()
{

}

void Postac::ustawFabrykePociskow(FabrykaPociskow *fp)
{
	fabrykaPociskow=fp;
}

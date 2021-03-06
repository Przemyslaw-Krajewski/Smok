/*
 * Zaslona.cpp
 *
 *  Created on: 27-09-2016
 *      Author: przemo
 */

#include "Zaslona.h"

Zaslona::Zaslona(Punkt p) : Przedmiot()
{
	pozycja=p;
	zycie=500;
	ulepszona=false;
	wyznaczPrzestrzenKolizji();
	wyznaczKlatkeAnimacji();
	ozdoba=0;
}

Zaslona::~Zaslona()
{

}

void Zaslona::wyznaczPrzestrzenKolizji()
{
	if(ozdoba == 0)
	{
		if(ulepszona)
		{
			Wymiary wymiary = Wymiary(230,60);
			std::vector<ProstokatKolizji> prostokaty;
			prostokaty.clear();

			prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(0,-20),wymiary));
			ustawPrzestrzenKolizji(prostokaty);
		}
		else
		{
			Wymiary wymiary = Wymiary(230,30);
			std::vector<ProstokatKolizji> prostokaty;
			prostokaty.clear();

			prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(0,20),wymiary));
			ustawPrzestrzenKolizji(prostokaty);
		}
	}
	else
	{
		std::vector<ProstokatKolizji> prostokaty;
		prostokaty.clear();
		ustawPrzestrzenKolizji(prostokaty);
	}
}

void Zaslona::wyznaczKolejnyStan()
{
	if(zycie<0)
	{
		zycie=0;
		przestrzenKolizji.wyczyscFigury();
		zniszcz();
	}
}

void Zaslona::wyznaczKlatkeAnimacji()
{
	if(ozdoba == 0)
	{
		if(zycie > 375) klatkaAnimacji.x = 1;
		else if (zycie > 250) klatkaAnimacji.x = 2;
		else if (zycie > 125) klatkaAnimacji.x = 3;
		else klatkaAnimacji.x = 4;

		if(ulepszona) klatkaAnimacji.y = 1;
		else klatkaAnimacji.y=0;
	}
	else
	{
		klatkaAnimacji.y=2;
		klatkaAnimacji.x=ozdoba-1;
	}
}

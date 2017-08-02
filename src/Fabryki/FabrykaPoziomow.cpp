/*
 * FabrykaPoziomow.cpp
 *
 *  Created on: 27 maj 2017
 *      Author: przemo
 */

#include "FabrykaPoziomow.h"

FabrykaPoziomow* FabrykaPoziomow::ptr=0;

FabrykaPoziomow* FabrykaPoziomow::zwrocInstancje()
{
	if(!ptr) ptr= new FabrykaPoziomow();
	return ptr;
}

FabrykaPoziomow::FabrykaPoziomow()
{
	smok=0;
}

FabrykaPoziomow::~FabrykaPoziomow()
{
	delete ptr;
}

void FabrykaPoziomow::stworzPoziom(int numer)
{
	double poziomZiemi = 130;
	if(numer==1) //################################ POZIOM 1: OBLAWA ###############################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(2000,0),Punkt(12000,1800));
		smok->ustawPozycje(Punkt(7000,100));
		smok->ustawCzyZwroconyWPrawo(false);

		for(int i=0;i<6;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(6000+odchylenie,poziomZiemi),0);
		}

		for(int i=0;i<6;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(8000+odchylenie,poziomZiemi),0);
		}
	}
	else if(numer==2) //################################ POZIOM 2: OBLAWA CZ.2 ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(5000,0),Punkt(15000,1500));
		smok->ustawPozycje(Punkt(10800,100));
		smok->ustawCzyZwroconyWPrawo(false);

		for(int i=0;i<8;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(9700+odchylenie,poziomZiemi),1);
		}

		for(int i=0;i<8;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(8400+odchylenie,poziomZiemi),1);
		}

		for(int i=0;i<12;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(8400+odchylenie,poziomZiemi),1);
		}

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(8200,poziomZiemi),1);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::jaskinia,Punkt(10400,0));
	}
	else if(numer==3) //################################ POZIOM 3: WYGNANIE ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(5000,0),Punkt(12000,4000));
		smok->ustawPozycje(Punkt(4000,100));
		smok->ustawCzyZwroconyWPrawo(true);

		for(int i=0;i<12;i++)
		{
			int odchylenie = rand() % 100-50;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(10400+odchylenie,poziomZiemi+1600),2);
		}
		for(int i=0;i<25;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(9000+odchylenie,poziomZiemi),2);
		}
		for(int i=0;i<10;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(9000+odchylenie,poziomZiemi),0);
		}

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(10400,0));
	}
	else if(numer==4) //################################ POZIOM 4: GLOD ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(5000,0),Punkt(14000,5000));
		smok->ustawPozycje(Punkt(4000,100));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(8000,0));

		//Ludzie na murze
		for(int i=0;i<4;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(8000,poziomZiemi+800),2);
		}

		//Ludzie pod zaslonami
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(9500,0));
		for(int i=0;i<3;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(9500,poziomZiemi),2);
		}
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(10500,0));
		for(int i=0;i<3;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(10500,poziomZiemi),2);
		}

		//Wolnobiegajacy ludzie
		for(int i=0;i<3;i++)
		{
			int odchylenie = i*150;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(8600+odchylenie,poziomZiemi),0);
		}
		for(int i=0;i<3;i++)
		{
			int odchylenie = i*150;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(9850+odchylenie,poziomZiemi),0);
		}
		for(int i=0;i<3;i++)
		{
			int odchylenie = i*150;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(11000+odchylenie,poziomZiemi),0);
		}

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::bwysokaWieza,Punkt(12000,0));
	}
	else if(numer==5) //################################ POZIOM 5: NAPAD ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(2000,0),Punkt(12000,1800));
		smok->ustawPozycje(Punkt(3500,400));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(3000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(8000,0));


		for(int i=0;i<32;i++)
		{
			int odchylenie = rand() % 4000-2000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::poborowyLucznik,Punkt(6000+odchylenie,poziomZiemi),0);
		}
	}
	else if(numer==6) //################################ POZIOM 6: PRZYSIEGA ZEMSTY ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(4000,0),Punkt(10500,4000));
		smok->ustawPozycje(Punkt(10000,1700));
		smok->ustawCzyZwroconyWPrawo(false);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(10000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(5000,0));


		for(int i=0;i<15;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7500+odchylenie,poziomZiemi),2);
		}
		for(int i=0;i<15;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(5000+odchylenie,poziomZiemi+500),2);
		}

	}
	else if(numer==7) //################################ POZIOM 7: OBLEZENIE ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(10000,4000));
		smok->ustawPozycje(Punkt(4000,200));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(5000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniMur,Punkt(9000,0));

		//Wieza
		for(int i=0;i<4;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(5000+odchylenie,poziomZiemi+800),2,false);
		}
		for(int i=0;i<3;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(5000+odchylenie,poziomZiemi+800),3,false);
		}

		//Ziemia
		for(int i=0;i<6;i++)
		{
			int odchylenie = rand() % 2000-1000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(6500+odchylenie,poziomZiemi),2,false);
		}

		//Mur
		for(int i=0;i<2;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(8300+odchylenie,poziomZiemi+500),3,false);
		}
		for(int i=0;i<10;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(9300+odchylenie,poziomZiemi+500),2,false);
		}
	}
	else if(numer==8) //################################ POZIOM 8: OBLEZENIE CZ.2 ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(15000,4000));
		smok->ustawPozycje(Punkt(3000,300));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::malyMur,Punkt(6000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::malyMur,Punkt(9000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7200,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7500,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7800,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(10000,0));

		//Mur
		for(int i=0;i<2;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(6300+odchylenie,poziomZiemi+300),3,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(9000+odchylenie,poziomZiemi+300),3,false);
		}
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(9300,poziomZiemi+378),0,false);

		//Ziemia
		for(int i=0;i<2;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7200,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7500,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7800,poziomZiemi),2,false);
		}

		//Wieza
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(10000,poziomZiemi+1580),3,false);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(10000,poziomZiemi+1580),3,false);
		for(int i=0;i<3;i++)
		{
			int odchylenie = rand() % 200-100;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(10000+odchylenie,poziomZiemi+1580),2,false);
		}
	}
	else if(numer==9) //################################ POZIOM 9: ZEMSTA ##########################################
	{
		smok->ustawWymiaryManewruSmoka(Punkt(3000,0),Punkt(15000,4000));
		smok->ustawPozycje(Punkt(3500,200));
		smok->ustawCzyZwroconyWPrawo(true);

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::sredniaWieza,Punkt(6000,0));

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::malyMur,Punkt(12000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::malyMur,Punkt(10000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::bmalyMur,Punkt(11660,540));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::niskaWieza,Punkt(11000,0));

		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::bduzyMur,Punkt(13890,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::bduzyMur,Punkt(12090,1320));

		//1st wieza
		for(int i=0;i<6;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(6000,poziomZiemi+1580),2,false);
		}

		//pod murem
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(6500,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(7500,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(8000,0));
		FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::zaslona,Punkt(8500,0));
		for(int i=0;i<6;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(6500,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7000,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(7500,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(8000,poziomZiemi),2,false);
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(8500,poziomZiemi),2,false);
		}


		//mur
		for(int i=0;i<8;i++)
		{
			int odchylenie = rand() % 1000-500;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(10000+odchylenie,poziomZiemi+400),3,false);
		}
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(10600,375+poziomZiemi),0,false);


		//2nd wieza
		for(int i=0;i<4;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::zawodowyLucznik,Punkt(11000,poziomZiemi+800),2,false);
		}
		for(int i=0;i<3;i++)
		{
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(11000,poziomZiemi+800),3,false);
		}

		//wneka
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(11700,795+poziomZiemi),0,false);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(11500,400+poziomZiemi),4,false);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(13000,poziomZiemi+400),1,false);
		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::rycerz,Punkt(13000,poziomZiemi+400),1,false);
	}
	else if(numer==101)
	{
		smok->ustawPozycje(Punkt(2000,100));
		smok->ustawPoziom(4);
		smok->ustawWymiaryManewruSmoka(Punkt(1000,0),Punkt(30000,3000));

		FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::balista,Punkt(3000,poziomZiemi+100),0,false);


	}
	else if(numer==102)
	{
		smok->ustawPozycje(Punkt(1000,100));
		smok->ustawWymiaryManewruSmoka(Punkt(1000,0),Punkt(30000,3000));
		for(int i=0;i<200;i++)
		{
			int x = rand()%30000+5000;
			FabrykaLudzi::zwrocInstancje()->stworzCzlowieka(FabrykaLudzi::krzyzowiec,Punkt(x,130),0);
		}
	}
}

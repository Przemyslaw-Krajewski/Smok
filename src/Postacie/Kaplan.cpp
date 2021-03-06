/*
 * Kaplan.cpp
 *
 *  Created on: 16-01-2017
 *      Author: przemo
 */

#include "Kaplan.h"

Kaplan::Kaplan(): Postac() {
	stan=stoi;

	zwroconyWPrawo=true;
	zycie=30;
	obrazenia=5;

	stanChodu=0;
	stanRzucaniaZaklec=0;

	tarcza=0;
	pomocnikCelowania.ustawParametry(parametry.predkoscPocisku*2,0);
}

//#####################################################################################################
//Podfunkcje Przeliczanie
//#####################################################################################################
void Kaplan::wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka)
{
	if(!zniszczony)
	{
		StanKaplana staryStan=stan;
		if (klawiatura->czyWcisnietoPrawo() && !przeszkodaPoPrawej)
		{
			zwroconyWPrawo=true;
			stan = idzie;

			stanChodu ++;

			if(stanChodu>=parametry.predkoscAnimacjiChodu*parametry.iloscKlatekAnimacjiChodu) stanChodu=0;
			pozycja.x+=parametry.predkoscChodu;
			stanRzucaniaZaklec=-1;
		}
		else if (klawiatura->czyWcisnietoLewo() && !przeszkodaPoLewej)
		{
			zwroconyWPrawo=false;
			stan = idzie;

			stanChodu ++;

			if(stanChodu>=parametry.predkoscAnimacjiChodu*parametry.iloscKlatekAnimacjiChodu) stanChodu=0;
			pozycja.x-=parametry.predkoscChodu;
			stanRzucaniaZaklec=-1;
		}
		else if(myszka->zwrocLPM())
		{
			//Pocisk samonaprowadzajacy
			stan = zaklecieKierowany;
			if(staryStan!=stan) stanRzucaniaZaklec=0;
			stanChodu=0;
			stanRzucaniaZaklec++;

			if(stanRzucaniaZaklec>parametry.czasRzucaniaKierowanegoPocisku)
			{
				stanRzucaniaZaklec=0;

				double kat = atan2((myszka->zwrocX()),(myszka->zwrocY()))-1.57;
				Punkt p;
				p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
				p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
				Punkt v;
				v.x=parametry.predkoscPocisku*cos(kat);
				v.y=parametry.predkoscPocisku*sin(kat);
				if(kat>6.28) kat-=6.28;
				FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::pociskKierowany,p,v,parametry.czasTrwaniaPocisku,kat,parametry.obrazeniaKierowanegoPocisku,cel);
			}
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(0))
		{
			// Pocisk kasetowy
			stan = zaklecieKasetowy;
			if(staryStan!=stan) stanRzucaniaZaklec=0;
			stanChodu=0;
			stanRzucaniaZaklec++;

				if(stanRzucaniaZaklec>parametry.czasRzucaniaKasetowegoPocisku)
				{
					stanRzucaniaZaklec=0;

					double kat = atan2((myszka->zwrocX()),(myszka->zwrocY()))-1.57;
					Punkt p;
					p.x=pozycja.x+(parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y+(parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					v.x=1.5*parametry.predkoscPocisku*2*cos(kat);
					v.y=1.5*parametry.predkoscPocisku*2*sin(kat);
					if(kat>6.28) kat-=6.28;
					FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::pociskKasetowy,p,v,parametry.czasTrwaniaPocisku,kat,parametry.obrazeniaKasetowegoPocisku,cel);
				}
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(1) && najblizszyKompan!=0)
		{
			// Tarcza personalna
			stan = tarczaPersonalna;
			if(staryStan!=stan) stanRzucaniaZaklec=0;
			stanChodu=0;
			stanRzucaniaZaklec++;

			if(stanRzucaniaZaklec>parametry.czasRzucaniaPersonalnejTarczy)
			{
				stanRzucaniaZaklec=0;
				FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::tarczaPersonalna,Punkt(),najblizszyKompan);
				najblizszyKompan->ustawCzyPosiadaTarcze(true);
			}
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(2))
		{
			//Tarcza Obszarowa
			stan = tarczaObszarowa;
			if(staryStan!=stan) stanRzucaniaZaklec=0;
			stanChodu=0;
			stanRzucaniaZaklec++;

			if(stanRzucaniaZaklec>=parametry.czasRzucaniaObszarowejTarczy)
			{
				stanRzucaniaZaklec=0;
				if(tarcza==0)
					tarcza=FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::tarczaObszarowa,pozycja);
			}
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(3) && !czyPosiadaTarcze())
		{
			// Tarcza personalna na siebie
			stan = tarczaPersonalna;
			if(staryStan!=stan) stanRzucaniaZaklec=0;
			stanRzucaniaZaklec++;

			if(stanRzucaniaZaklec>parametry.czasRzucaniaPersonalnejTarczy)
			{
				stanRzucaniaZaklec=0;
				FabrykaPrzedmiotow::zwrocInstancje()->stworzPrzedmiot(FabrykaPrzedmiotow::tarczaPersonalna,Punkt(),this);
			}
		}
		else if(klawiatura->czyWcisnietoKlawiszFunkcyjny(4))
		{
			// Seria strzal
			stan = seriaPociskow;
			if(staryStan!=stan) stanRzucaniaZaklec=0;
			stanChodu=0;
			stanRzucaniaZaklec++;

			if(stanRzucaniaZaklec>parametry.czasRzucaniaSeriiPociskow)
			{
				stanRzucaniaZaklec=0;

				for(int i=0;i<100;i++)
				{
					double kat = atan2((myszka->zwrocX()),(myszka->zwrocY()))-1.57;
					kat=-kat+((double)(rand()%100)/100)*M_PI*2;
					Punkt p;
					p.x=pozycja.x + (parametry.minimalnaOdleglosc)*cos(kat);
					p.y=pozycja.y + (parametry.minimalnaOdleglosc)*sin(kat);
					Punkt v;
					double vr = rand()%10;
					v.x=(parametry.predkoscPocisku - vr)*cos(kat);
					v.y=(parametry.predkoscPocisku - vr)*sin(kat);
					if(kat>6.28) kat-=6.28;
					FabrykaPociskow::zwrocInstancje()->stworzPocisk(FabrykaPociskow::pociskKierowany,p,v,parametry.czasTrwaniaPocisku,kat,parametry.obrazeniaPociskuZSerii,cel);
				}
			}
		}
		else
		{
			stan = stoi;
			stanChodu=0;
			stanRzucaniaZaklec=0;
		}

		//Zycie
		if(zycie<=0) zniszcz();

		//Zaklecia
		if(stanRzucaniaZaklec<0) stanRzucaniaZaklec=0;

		//pozycja Y
		if(pozycja.y<=parametry.wysokosc+parametryObiektow.poziomZiemi)
		{
			pozycja.y=parametry.wysokosc+parametryObiektow.poziomZiemi;
			naZiemi=true;
		}
		if(!naZiemi)
		{
			pozycja.y-=10;
		}

		//Przeszkody terenowe
		naZiemi=false;
		przeszkodaPoPrawej=false;
		przeszkodaPoLewej=false;

		//Tarcza
		if(tarcza!=0)
		{
			if(tarcza->czyZniszczony())
			{
				tarcza->usun();
				tarcza=0;
			}
			else if(stan!=tarczaObszarowa)
			{
				tarcza->zniszcz();
			}
		}
	}
	else
	{
		stan = umiera;
		if(tarcza) tarcza->usun();
		std::vector<OkragKolizji> p;
		ustawPrzestrzenKolizji(p);
	}
}

std::pair<Klawiatura,Myszka> Kaplan::wyznaczSterowanie()
{
	int maxOdleglosc=10000;
	int minOdleglosc=10000;
	int odleglosc=10000;

	Punkt pozycjaCelu = cel->zwrocPozycjeCelu();

	Klawiatura k;
	Myszka m;

	if(cel->czyZniszczony())
	{
		return std::pair<Klawiatura,Myszka>(k,m);
	}

	if(typZachowania==0) //Mnich
	{
		double progOdleglosci1 = 3000;
		double progOdleglosci2 = 1200;

		if(fabs(pozycjaCelu.x-pozycja.x)<progOdleglosci2)
		{
			//Tarcza obszarowa
			k.ustawWcisnietoKlawiszFunkcyjny(true,2);
		}
		else if(fabs(pozycjaCelu.x-pozycja.x)>progOdleglosci1)
		{
			//Tarcza personalna
			k.ustawWcisnietoKlawiszFunkcyjny(true,1);
		}
		else if(pozycjaCelu.x<pozycja.x && zwroconyWPrawo==true)
		{
			k.ustawWcisnietoLewo(true);
		}
		else if(pozycjaCelu.x>pozycja.x && zwroconyWPrawo==false)
		{
			k.ustawWcisnietoPrawo(true);
		}
		else if(fabs(pozycjaCelu.x-pozycja.x)>progOdleglosci2 && fabs(pozycjaCelu.x-pozycja.x)<progOdleglosci1)
		{
			m.ustawLPM(true);

			Punkt poprawka = (*(cel->zwrocPrzestrzenKolizji()->zwrocOkregi()))[0].zwrocPozycjeWzgledemObiektu();
			poprawka.y=-poprawka.y+10;
			poprawka.x=-poprawka.x;
			if(cel->czyZwroconyWPrawo()) poprawka.x+=30;
			else poprawka.x-=30;

			pomocnikCelowania.wyznaczKatStrzalu(Punkt(pozycja.x-pozycjaCelu.x,pozycja.y-pozycjaCelu.y)+poprawka,cel->zwrocPredkosc());
			double kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
			m.ustawX(1000*cos(kat));
			m.ustawY(1000*sin(kat));
		}
	}
	else if(typZachowania==1) // StacjonarnyKaplan
	{
		double progOdleglosci = 12000;

		if(pozycjaCelu.x<pozycja.x && zwroconyWPrawo==true && stanRzucaniaZaklec<2)
		{
			k.ustawWcisnietoLewo(true);
		}
		else if(pozycjaCelu.x>pozycja.x && zwroconyWPrawo==false && stanRzucaniaZaklec<2)
		{
			k.ustawWcisnietoPrawo(true);
		}
		else if(fabs(pozycjaCelu.x-pozycja.x)<progOdleglosci)
		{
			k.ustawWcisnietoKlawiszFunkcyjny(true,0);

			Punkt poprawka = (*(cel->zwrocPrzestrzenKolizji()->zwrocOkregi()))[0].zwrocPozycjeWzgledemObiektu();
			poprawka.y=-poprawka.y+10;
			poprawka.x=-poprawka.x;
			if(cel->czyZwroconyWPrawo()) poprawka.x+=30;
			else poprawka.x-=30;

			pomocnikCelowania.wyznaczKatStrzalu(Punkt(pozycja.x-pozycjaCelu.x,pozycja.y-pozycjaCelu.y)+poprawka,cel->zwrocPredkosc());
			double kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
			pomocnikCelowania.resetCelowania();
			m.ustawX(1000*cos(kat));
			m.ustawY(1000*sin(kat));
		}
	}
	if(typZachowania==2) //Kaplan
	{
		double progOdleglosci1 = 8000;
		double progOdleglosci2 = 1200;

		if(fabs(pozycjaCelu.x-pozycja.x)<progOdleglosci2)
		{
			//Tarcza obszarowa
			k.ustawWcisnietoKlawiszFunkcyjny(true,2);
		}
		else if(fabs(pozycjaCelu.x-pozycja.x)>progOdleglosci1 && !maTarcze)
		{
			//Tarcza personalna
			k.ustawWcisnietoKlawiszFunkcyjny(true,1);
		}
		else if(pozycjaCelu.x<pozycja.x && zwroconyWPrawo==true)
		{
			k.ustawWcisnietoLewo(true);
		}
		else if(pozycjaCelu.x>pozycja.x && zwroconyWPrawo==false)
		{
			k.ustawWcisnietoPrawo(true);
		}
		else if(fabs(pozycjaCelu.x-pozycja.x)>progOdleglosci2 && fabs(pozycjaCelu.x-pozycja.x)<progOdleglosci1)
		{
			if(stanRzucaniaZaklec == 0) rzucaneZaklecie = -1;
			Punkt v2 = cel->zwrocPredkosc();
			Punkt dP = pozycja-pozycjaCelu;

			if( (rand() % 2 == 0 && rzucaneZaklecie == -1) || rzucaneZaklecie == 1)
			{
				rzucaneZaklecie = 1;
				k.ustawWcisnietoKlawiszFunkcyjny(true,0);
			}
			else if(rzucaneZaklecie != 1)
			{
				rzucaneZaklecie = 2;
				m.ustawLPM(true);
			}

			Punkt poprawka = (*(cel->zwrocPrzestrzenKolizji()->zwrocOkregi()))[0].zwrocPozycjeWzgledemObiektu();
			poprawka.y=-poprawka.y+10;
			poprawka.x=-poprawka.x;
			if(cel->czyZwroconyWPrawo()) poprawka.x+=30;
			else poprawka.x-=30;

			pomocnikCelowania.wyznaczKatStrzalu(dP+poprawka,v2);
			double kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
			m.ustawX(1000*cos(kat));
			m.ustawY(1000*sin(kat));
		}
	}
	else if (typZachowania == 3) // Glowa
	{
		double progOdleglosci2 = 1700;

		if(stareZycie>zycie) uruchomienieOslony = true;
		if(fabs(pozycjaCelu.x-pozycja.x)>progOdleglosci2) uruchomienieOslony = false;
		stareZycie = zycie;

		if(uruchomienieOslony)
		{
			//Tarcza obszarowa
			k.ustawWcisnietoKlawiszFunkcyjny(true,2);
		}
		else if(fabs(pozycjaCelu.x-pozycja.x)>progOdleglosci2 && !czyPosiadaTarcze())
		{
			//Tarcza personalna
			k.ustawWcisnietoKlawiszFunkcyjny(true,3);
		}
		else if(pozycjaCelu.x<pozycja.x && zwroconyWPrawo==true)
		{
			k.ustawWcisnietoLewo(true);
		}
		else if(pozycjaCelu.x>pozycja.x && zwroconyWPrawo==false)
		{
			k.ustawWcisnietoPrawo(true);
		}
		else if(fabs(pozycjaCelu.x-pozycja.x)<progOdleglosci2 || !maTarcze)
		{
			if(stanRzucaniaZaklec == 0) rzucaneZaklecie = -1;
			Punkt v2 = cel->zwrocPredkosc();
			Punkt dP = pozycja-pozycjaCelu;

			if( (rand() % 3 < 2 && rzucaneZaklecie == -1) || rzucaneZaklecie == 1)
			{
				rzucaneZaklecie = 1;
				k.ustawWcisnietoKlawiszFunkcyjny(true,0);
			}
			else if(rzucaneZaklecie != 1)
			{
				rzucaneZaklecie = 2;
				m.ustawLPM(true);
			}

			Punkt poprawka = (*(cel->zwrocPrzestrzenKolizji()->zwrocOkregi()))[0].zwrocPozycjeWzgledemObiektu();
			poprawka.y=-poprawka.y+10;
			poprawka.x=-poprawka.x;
			if(cel->czyZwroconyWPrawo()) poprawka.x+=30;
			else poprawka.x-=30;

			pomocnikCelowania.wyznaczKatStrzalu(dP+poprawka,v2);
			double kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
			m.ustawX(1000*cos(kat));
			m.ustawY(1000*sin(kat));
		}
		else
		{
			if(stanRzucaniaZaklec == 0) rzucaneZaklecie = -1;
			Punkt v2 = cel->zwrocPredkosc();
			Punkt dP = pozycja-pozycjaCelu;

			k.ustawWcisnietoKlawiszFunkcyjny(true,4);

			Punkt poprawka = (*(cel->zwrocPrzestrzenKolizji()->zwrocOkregi()))[0].zwrocPozycjeWzgledemObiektu();
			poprawka.y=-poprawka.y+10;
			poprawka.x=-poprawka.x;
			if(cel->czyZwroconyWPrawo()) poprawka.x+=30;
			else poprawka.x-=30;

			pomocnikCelowania.wyznaczKatStrzalu(dP+poprawka,v2);
			double kat = pomocnikCelowania.zwrocKat(PomocnikCelowania::katWprost);
			m.ustawX(1000*cos(kat));
			m.ustawY(1000*sin(kat));
		}
	}

	return std::pair<Klawiatura,Myszka>(k,m);
}

//#####################################################################################################
//Podfunkcje Ruch
//#####################################################################################################

//#####################################################################################################
//Podfunkcje Kolizje
//#####################################################################################################
void Kaplan::wyznaczPrzestrzenKolizji()
{
	double rozmiarKlatki=40;
	std::vector<OkragKolizji> okregi;
	okregi.clear();
	std::vector<ProstokatKolizji> prostokaty;
	prostokaty.clear();

	prostokaty.push_back(ProstokatKolizji(&pozycja,&predkosc,Punkt(),100));
	ustawPrzestrzenKolizji(prostokaty);

	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(40-rozmiarKlatki,-15+rozmiarKlatki),10));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(40-rozmiarKlatki,-35+rozmiarKlatki),14));
	okregi.push_back(OkragKolizji(&pozycja,&predkosc,Punkt(40-rozmiarKlatki,-60+rozmiarKlatki),14));
	ustawPrzestrzenKolizji(okregi);
}

//#####################################################################################################
//Podfunkcje Grafika
//#####################################################################################################
void Kaplan::wyznaczKlatkeAnimacji()
{
	switch(stan)
	{
		case stoi:
			klatkaAnimacji=Punkt(0,0);
			break;
		case idzie:
			klatkaAnimacji.x=1;
			klatkaAnimacji.y=stanChodu/((int)(parametry.predkoscAnimacjiChodu));
			break;
		case zaklecieKierowany:
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=stanRzucaniaZaklec/(1+parametry.czasRzucaniaKierowanegoPocisku/3);
			break;
		case zaklecieKasetowy:
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=stanRzucaniaZaklec/(1+parametry.czasRzucaniaKasetowegoPocisku/3);
			break;
		case seriaPociskow:
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=stanRzucaniaZaklec/(1+parametry.czasRzucaniaSeriiPociskow/3);
			break;
		case tarczaPersonalna:
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=stanRzucaniaZaklec/(1+parametry.czasRzucaniaPersonalnejTarczy/3);
			break;
		case tarczaObszarowa:
			klatkaAnimacji.x=0;
			klatkaAnimacji.y=stanRzucaniaZaklec/(1+parametry.czasRzucaniaObszarowejTarczy/3);
			if(tarcza != 0) klatkaAnimacji.y = 2;
			break;
		case umiera:
			if(klatkaAnimacji.x!=0 || klatkaAnimacji.y<2)
			{
				klatkaAnimacji.x=0;
				klatkaAnimacji.y=2;
			}
			else if(klatkaAnimacji.y<7)
				klatkaAnimacji.y+=0.3;
			else
				klatkaAnimacji.y+=0.1;
			if (klatkaAnimacji.x==0 && klatkaAnimacji.y>=8) usun();
			break;
		default:
			klatkaAnimacji=Punkt();
	}
}

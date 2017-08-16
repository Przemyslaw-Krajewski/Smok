/*
 * Kaplan.h
 *
 *  Created on: 16-01-2017
 *      Author: przemo
 */

#ifndef SRC_POSTACIE_KAPLAN_H_
#define SRC_POSTACIE_KAPLAN_H_

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <utility>

#include "Postac.h"
#include "PomocnikCelowania.h"

struct ParametryKaplana
{
	double wysokosc;

	int predkoscAnimacjiChodu;
	int iloscKlatekAnimacjiChodu;
	int predkoscAnimacjiRzucaniaZaklec;

	double predkoscChodu;
	double minimalnaOdleglosc;

	double czasRzucaniaKierowanegoPocisku;
	double czasRzucaniaKasetowegoPocisku;
	double czasRzucaniaPersonalnejTarczy;
	double czasRzucaniaObszarowejTarczy;

	double czasTrwaniaPocisku;

	double predkoscPocisku;

	double maxZycia;
	double obrazeniaKierowanegoPocisku;
	double obrazeniaKasetowegoPocisku;

	ParametryKaplana()
	{
		wysokosc=50;

		predkoscAnimacjiChodu=6;
		iloscKlatekAnimacjiChodu=8;
		predkoscAnimacjiRzucaniaZaklec=30;

		predkoscChodu=0.8;
		minimalnaOdleglosc=30;


		czasRzucaniaKierowanegoPocisku=50;
		czasRzucaniaKasetowegoPocisku=0;
		czasRzucaniaPersonalnejTarczy=150;
		czasRzucaniaObszarowejTarczy=50;

		czasTrwaniaPocisku=1000;

		predkoscPocisku=15;

		maxZycia=10;
		obrazeniaKierowanegoPocisku=5;
		obrazeniaKasetowegoPocisku=5;
	}
};

class Kaplan: public Postac
{
public:
	enum StanKaplana {stoi, idzie, umiera, zaklecieKierowany, zaklecieKasetowy, tarczaPersonalna, tarczaObszarowa};

	Kaplan();

	virtual void wyznaczKolejnyStan(Klawiatura *klawiatura, Myszka *myszka);
	virtual void wyznaczKlatkeAnimacji();
	virtual void wyznaczPrzestrzenKolizji();

	std::pair<Klawiatura,Myszka> wyznaczSterowanie();

	void ustawParametry(ParametryKaplana p)
	{
		zycie=p.maxZycia;
		parametry=p;
		pomocnikCelowania.ustawParametry(parametry.predkoscPocisku,0);
	}

	ParametryKaplana parametry;
	StanKaplana stan;

private:
	int stanChodu;
	int stanRzucaniaZaklec;

	PomocnikCelowania pomocnikCelowania;

	Obiekt* tarcza;


};

#endif /* SRC_POSTACIE_KAPLAN_H_ */

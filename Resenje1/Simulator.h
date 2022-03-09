#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "CvorGrafa.h"

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

class Simulator {
public:
	Simulator();
	~Simulator();

	void ucitajStajalista(const string& putanja_fajla);
	void ucitajLinije(const string& putanja_fajla);

	void kreirajGraf();

	void infoStajalista();
	void infoLinije();
	void statistika();

	void biloKojaPutanja();
	void putanjaSaNajmanjeStajalista();
	void putanjaSaNajmanjePresedanja();

	int uzmiBrojStajalista();
	void dodajVezu(int prvi, int drugi);

private:
	vector<Stajaliste*> sva_stajalista_;
	vector<Linija*> sve_linije_;

	vector<CvorGrafa*> graf_;
	vector<vector<int>> veze_;

	vector<int> prethodni_;
	vector<int> distanca_;
	vector<string> linije_;

	Stajaliste* pronadjiStajaliste(int sifra_stajalista);
	Linija* pronadjiLiniju(string oznaka_linije);
	CvorGrafa* pronadjiCvor(int sifra_stajalista);

	int pozicijaLinije(Linija* linija, vector<Linija*> niz);
	void sortiraj(vector<Linija*> niz);
	int pronadjiMojuSifru(int sifra_stajalista);
	int pronadjiSifruStajalista(int moja_sifra);
	void dodajLinijuVeze(int odrediste);

	bool BFS(int pocetak, int kraj, int n);
};


#endif // !SIMULATOR_H

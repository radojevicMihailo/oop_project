#ifndef STAJALISTE_H
#define STAJALISTE_H

#include <iostream>
#include <string>
using namespace std;

class Stajaliste {
public:
	Stajaliste(string red, int moja_sifra);

	int uzmiSifruStajalista();
	string uzmiNazivStajalista();
	int uzmiMojuSifru();

private:
	int sifra_stajalista_;
	string  naziv_stajalista_;
	int moja_sifra_;
};

#endif // !STAJALISTE_H

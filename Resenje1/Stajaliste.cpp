#include "Stajaliste.h"

Stajaliste::Stajaliste(string red, int moja_sifra) : moja_sifra_(moja_sifra) {
	int i = red.find_first_of(' ');
	sifra_stajalista_ = stoi(red.substr(0, i));
	naziv_stajalista_ = red.substr(i + 1, red.length() - i - 1);
}

int Stajaliste::uzmiSifruStajalista() {
	return sifra_stajalista_;
}

string Stajaliste::uzmiNazivStajalista() {
	return naziv_stajalista_;
}

int Stajaliste::uzmiMojuSifru() {
	return moja_sifra_;
}

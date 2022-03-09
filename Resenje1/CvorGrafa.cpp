#include "CvorGrafa.h"

CvorGrafa::CvorGrafa(Stajaliste* stajaliste) : stajaliste_(stajaliste) {}

CvorGrafa::~CvorGrafa() {
	delete stajaliste_;
	for (int i = 0; i < prolazne_linije_.size(); i++) {
		delete prolazne_linije_[i];
	}
	for (int i = 0; i < ulazna_stajalista_.size(); i++) {
		delete ulazna_stajalista_[i];
	}
	for (int i = 0; i < izlazna_stajalista_.size(); i++) {
		delete izlazna_stajalista_[i];
	}
}

void CvorGrafa::dodajLiniju(Linija* linija) {
	bool ubacen = false;
	if (prolazne_linije_.size() == 0) {
		prolazne_linije_.push_back(linija);
		ubacen = true;
	}
	else {
		for (int i = 0; i < prolazne_linije_.size(); i++) {
			if (prolazne_linije_[i]->uzmiOznakuLinije().compare(linija->uzmiOznakuLinije()) > 0) {
				prolazne_linije_.insert(prolazne_linije_.begin() + i, linija);
				ubacen = true;
				break;
			}
		}
	}
	if (!ubacen) {
		prolazne_linije_.push_back(linija);
	}
}

void CvorGrafa::dodajUlaz(Stajaliste* stajaliste) {
	if (pozicijaStajalista(stajaliste, ulazna_stajalista_) == -1) {
		ulazna_stajalista_.push_back(stajaliste);
	}
}

void CvorGrafa::dodajIzlaz(Stajaliste* stajaliste) {
	if (pozicijaStajalista(stajaliste, izlazna_stajalista_) == -1) {
		izlazna_stajalista_.push_back(stajaliste);
	}
}

Stajaliste* CvorGrafa::uzmiStajaliste() {
	return stajaliste_;
}

Linija* CvorGrafa::uzmiLiniju(int poz) {
	if (prolazne_linije_.size() == 0) {
		return nullptr;
	}
	else {
		return prolazne_linije_[poz];
	}
}

Stajaliste* CvorGrafa::uzmiUlaznoStajaliste(int poz) {
	if (ulazna_stajalista_.size() == 0) {
		return nullptr;
	}
	else {
		return ulazna_stajalista_[poz];
	}
}

Stajaliste* CvorGrafa::uzmiIzlaznoStajaliste(int poz) {
	if (izlazna_stajalista_.size() == 0) {
		return nullptr;
	}
	else {
		return izlazna_stajalista_[poz];
	}
}

int CvorGrafa::uzmiBrojProlaznihLinija() {
	return prolazne_linije_.size();
}

int CvorGrafa::uzmiBrojUlaznihStajalista() {
	return ulazna_stajalista_.size();
}

int CvorGrafa::uzmiBrojIzlaznihStajalista() {
	return izlazna_stajalista_.size();
}

int CvorGrafa::pozicijaStajalista(Stajaliste* stajaliste, vector<Stajaliste*> niz) {
	for (int i = 0; i < niz.size(); i++) {
		if (stajaliste->uzmiSifruStajalista() == niz[i]->uzmiSifruStajalista()) {
			return i;
		}
	}
	return -1;
}
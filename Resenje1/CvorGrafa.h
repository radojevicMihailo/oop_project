#ifndef CVOR_GRAFA_H
#define CVOR_GRAFA_H

#include "Stajaliste.h"
#include "Linija.h";

#include <vector>
using namespace std;

class CvorGrafa {
public:
	CvorGrafa(Stajaliste* stajaliste);
	~CvorGrafa();

	void dodajLiniju(Linija* linija);
	void dodajUlaz(Stajaliste* stajaliste);
	void dodajIzlaz(Stajaliste* stajaliste);

	Stajaliste* uzmiStajaliste();
	Linija* uzmiLiniju(int poz);
	Stajaliste* uzmiUlaznoStajaliste(int poz);
	Stajaliste* uzmiIzlaznoStajaliste(int poz);

	int uzmiBrojProlaznihLinija();
	int uzmiBrojUlaznihStajalista();
	int uzmiBrojIzlaznihStajalista();

private:
	Stajaliste* stajaliste_;
	vector<Linija*> prolazne_linije_;
	vector<Stajaliste*> ulazna_stajalista_; 
	vector<Stajaliste*> izlazna_stajalista_;

	int pozicijaStajalista(Stajaliste* stajaliste, vector<Stajaliste*> niz);
};


#endif // !CVOR_GRAFA_H

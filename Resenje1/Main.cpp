#include "Simulator.h"

#include <iostream>
using namespace std;

int  main() {

	int ulaz1 = -1;
	while (ulaz1 != 0) {

		Simulator* simulator = new Simulator();

		cout << "Dobrodosli u simulator mreze gradskog prevoza. Molimo Vas, odaberite opciju:" << endl;
		cout << "1. Ucitavanje podataka o mrezi gradskog prevoza" << endl;
		cout << "0. Kraj rada" << endl;

		cin >> ulaz1;
		string fajl_stajalista, fajl_linije;

		switch (ulaz1) {
		case 0:
			cout << "Kraj rada simulatora mreze gradskog prevoza. Dovidjenja." << endl;
			delete simulator;
			return 0;
		case 1:
			cout << "Molimo Vas, unesite putanju do fajla sa stajalistima:" << endl;
			cin >> fajl_stajalista;
			simulator->ucitajStajalista(fajl_stajalista);
			cout << "Molimo Vas, unesite putanju do fajla sa linijama gradskog prevoza:" << endl;
			cin >> fajl_linije;
			simulator->ucitajLinije(fajl_linije);
			break;
		}

		simulator->kreirajGraf();

		int ulaz2 = -1;
		while (ulaz2 != 0) {

			cout << "Mreza gradskog prevoza je uspesno ucitana. Molimo Vas, odaberite opciju:" << endl;
			cout << "1. Prikaz informacija o stajalistu" << endl;
			cout << "2. Prikaz osnovnih informacija o liniji gradskog prevoza" << endl;
			cout << "3. Prikaz statistickih informacija o liniji gradskog prevoza" << endl;
			cout << "4. Pronalazak putanje izmedju dva stajalista" << endl;
			cout << "0. Kraj rada" << endl;

			cin >> ulaz2;

			switch (ulaz2) {
			case 0:
				cout << "Kraj rada simulatora mreze gradskog prevoza. Dovidjenja." << endl;
				break;
			case 1:
				simulator->infoStajalista();
				break;
			case 2:
				simulator->infoLinije();
				break;
			case 3:
				simulator->statistika();
				break;
			case 4:
				simulator->biloKojaPutanja();
				break;
			}
		}
	}
}
#ifndef LINIJA_H
#define LINIJA_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Linija {
public:
	Linija(string red);

	string uzmiOznakuLinije();
	int uzmiIzSmeraA(int poz);
	int uzmiIzSmeraB(int poz);

	int uzmiVelicinuSmeraA();
	int uzmiVelicinuSmeraB();

private:
	string oznaka_linije_;
	vector<int> smer_A_;
	vector<int> smer_B_;
};

#endif // !LINIJA_H

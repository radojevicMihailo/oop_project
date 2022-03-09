#include "Linija.h"

Linija::Linija(string red) {
	int i = red.find(' ');
	oznaka_linije_ = red.substr(0, i);
	int j = red.find('#');
	i = i + 1;
	int k = i, s;
	while (i < j) {
		k = red.find(' ', i);
		if (k < j) {
			s = stoi(red.substr(i, (k - i)));
			i = k + 1;
		}
		else {
			s = stoi(red.substr(i, (j - i)));
			i = j + 1;
		}
		smer_A_.push_back(s);
	}
	while (i < red.length()) {
		if (k != -1) {
			s = stoi(red.substr(i, (k - i)));
			i = k + 1;
			k = red.find(' ', i);
		}
		else {
			s = stoi(red.substr(i, (red.length())));
			i = red.length() + 1;
		}
		smer_B_.push_back(s);
	}
}

string Linija::uzmiOznakuLinije() {
	return oznaka_linije_;
}

int Linija::uzmiIzSmeraA(int poz) {
	if (smer_A_.size() == 0) {
		return -1;
	}
	else {
		return smer_A_[poz];
	}
}

int Linija::uzmiIzSmeraB(int poz) {
	if (smer_B_.size() == 0) {
		return -1;
	}
	else {
		return smer_B_[poz];
	}
}

int Linija::uzmiVelicinuSmeraA() {
	return smer_A_.size();
}

int Linija::uzmiVelicinuSmeraB() {
	return smer_B_.size();
}

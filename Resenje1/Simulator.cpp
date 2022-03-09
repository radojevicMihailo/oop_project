#include "Simulator.h"

Simulator::Simulator() {}

Simulator::~Simulator() {
	for (int i = 0; i < sva_stajalista_.size(); i++) {
		delete sva_stajalista_[i];
	}
	for (int i = 0; i < sve_linije_.size(); i++) {
		delete sve_linije_[i];
	}

}

void Simulator::ucitajStajalista(const string& putanja_fajla) {
	fstream ulazni_fajl(putanja_fajla, ios::in);

	int moja_sifra = 0;
	while (ulazni_fajl.peek() != EOF) {
		string red;
		getline(ulazni_fajl, red);
		Stajaliste* novo_stajaliste = new Stajaliste(red, moja_sifra);
		sva_stajalista_.push_back(novo_stajaliste);
		moja_sifra++;	
	}

	ulazni_fajl.close();
}

void Simulator::ucitajLinije(const string& putanja_fajla) {
	fstream ulazni_fajl(putanja_fajla, ios::in);

	while (ulazni_fajl.peek() != EOF) {
		string red;
		getline(ulazni_fajl, red);
		Linija* nova_linija = new Linija(red);
		sve_linije_.push_back(nova_linija);
	}

	ulazni_fajl.close();
}

void Simulator::kreirajGraf() {
	for (int i = 0; i < sva_stajalista_.size(); i++) {
		CvorGrafa* novi_cvor = new CvorGrafa(sva_stajalista_[i]);
		for (int j = 0; j < sve_linije_.size(); j++) {
			bool dodata = false;
			for (int k = 0; k < sve_linije_[j]->uzmiVelicinuSmeraA(); k++) {
				if (sva_stajalista_[i]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraA(k)) {
					novi_cvor->dodajLiniju(sve_linije_[j]);
					dodata = true;
					if (k == 0) {
						for (int l = 0; l < sva_stajalista_.size(); l++) {
							if (sva_stajalista_[l]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraA(k + 1)) {
								novi_cvor->dodajIzlaz(sva_stajalista_[l]);
							}
						}
					}
					else if (k == (sve_linije_[j]->uzmiVelicinuSmeraA() - 1)) {
						for (int l = 0; l < sva_stajalista_.size(); l++) {
							if (sva_stajalista_[l]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraA(k - 1)) {
								novi_cvor->dodajUlaz(sva_stajalista_[l]);
							}
						}
					}
					else {
						for (int l = 0; l < sva_stajalista_.size(); l++) {
							if (sva_stajalista_[l]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraA(k - 1)) {
								novi_cvor->dodajUlaz(sva_stajalista_[l]);
							}
							else if (sva_stajalista_[l]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraA(k + 1)) {
								novi_cvor->dodajIzlaz(sva_stajalista_[l]);
							}
						}
					}
				}
			}
			for (int k = 0; k < sve_linije_[j]->uzmiVelicinuSmeraB(); k++) {
				if (sva_stajalista_[i]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraB(k)) {
					if (!dodata) {
						novi_cvor->dodajLiniju(sve_linije_[j]);
					}
					if (k == 0) {
						for (int l = 0; l < sva_stajalista_.size(); l++) {
							if (sva_stajalista_[l]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraB(k + 1)) {
								novi_cvor->dodajIzlaz(sva_stajalista_[l]);
							}
						}
					}
					else if (k == (sve_linije_[j]->uzmiVelicinuSmeraB() - 1)) {
						for (int l = 0; l < sva_stajalista_.size(); l++) {
							if (sva_stajalista_[l]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraB(k - 1)) {
								novi_cvor->dodajUlaz(sva_stajalista_[l]);
							}
						}
					}
					else {
						for (int l = 0; l < sva_stajalista_.size(); l++) {
							if (sva_stajalista_[l]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraB(k - 1)) {
								novi_cvor->dodajUlaz(sva_stajalista_[l]);
							}
							else if (sva_stajalista_[l]->uzmiSifruStajalista() == sve_linije_[j]->uzmiIzSmeraB(k + 1)) {
								novi_cvor->dodajIzlaz(sva_stajalista_[l]);
							}
						}
					}
				}
			}
		}
		graf_.push_back(novi_cvor);
	}
}

void Simulator::infoStajalista() {
	int sifra_stajalista;
	cout << "Molimo Vas, unesite sifru stajalista cije osnovne informacije zelite da prikazete." << endl;
	cin >> sifra_stajalista;

	string ime_fajla = "stajaliste_" + to_string(sifra_stajalista) + ".txt";
	fstream izlaz("stajaliste_" + to_string(sifra_stajalista) + ".txt", ios::out);

	for (int i = 0; i < graf_.size(); i++) {
		if (sifra_stajalista == graf_[i]->uzmiStajaliste()->uzmiSifruStajalista()) {
			izlaz << graf_[i]->uzmiStajaliste()->uzmiSifruStajalista() << " " << graf_[i]->uzmiStajaliste()->uzmiNazivStajalista() << " [";
			for (int j = 0; j < graf_[i]->uzmiBrojProlaznihLinija()-1; j++) {
				izlaz << graf_[i]->uzmiLiniju(j)->uzmiOznakuLinije() << " ";
			}
			izlaz << graf_[i]->uzmiLiniju(graf_[i]->uzmiBrojProlaznihLinija() - 1)->uzmiOznakuLinije() << "]";
			break;
		}
	}

	cout << "Generisan je fajl stajaliste_" << sifra_stajalista << ".txt sa osnovnim informacijama o stajalistu " << sifra_stajalista << "." << endl;
	izlaz.close();
}

void Simulator::infoLinije() {
	string oznaka_linije;
	cout << "Molimo Vas, unesite oznaku linije cije osnovne informacije zelite da prikazete." << endl;
	cin >> oznaka_linije;

	fstream izlaz("linija_" + oznaka_linije + ".txt", ios::out);

	for (int i = 0; i < sve_linije_.size(); i++) {
		if (sve_linije_[i]->uzmiOznakuLinije() == oznaka_linije) {
			Stajaliste* pocetno = pronadjiStajaliste(sve_linije_[i]->uzmiIzSmeraA(0));
			Stajaliste* krajnje = pronadjiStajaliste(sve_linije_[i]->uzmiIzSmeraA(sve_linije_[i]->uzmiVelicinuSmeraA() - 1));
			izlaz << oznaka_linije << " " << pocetno->uzmiNazivStajalista() << "->" << krajnje->uzmiNazivStajalista() << endl;;
			Stajaliste* ispis;
			for (int j = 0; j < sve_linije_[i]->uzmiVelicinuSmeraA(); j++) {
				ispis = pronadjiStajaliste(sve_linije_[i]->uzmiIzSmeraA(j));
				izlaz << ispis->uzmiSifruStajalista() << " " << ispis->uzmiNazivStajalista() << endl;
			}
			for (int j = 0; j < sve_linije_[i]->uzmiVelicinuSmeraB() - 1; j++) {
				ispis = pronadjiStajaliste(sve_linije_[i]->uzmiIzSmeraB(j));
				izlaz << ispis->uzmiSifruStajalista() << " " << ispis->uzmiNazivStajalista() << endl;
			}
			ispis = pronadjiStajaliste(sve_linije_[i]->uzmiIzSmeraB(sve_linije_[i]->uzmiVelicinuSmeraB() - 1));
			izlaz << ispis->uzmiSifruStajalista() << " " << ispis->uzmiNazivStajalista();
		}
	}

	cout << "Generisan je fajl linija_" << oznaka_linije << ".txt sa osnovnim informacijama o liniji " << oznaka_linije << "." << endl;
	izlaz.close();
}

void Simulator::statistika() {
	string oznaka_linije;
	cout << "Molimo Vas, unesite oznaku linije cije statisticke informacije zelite da prikazete." << endl;
	cin >> oznaka_linije;

	fstream izlaz("statistika_" + oznaka_linije + ".txt", ios::out);
	izlaz << oznaka_linije << endl;

	Linija* linija = pronadjiLiniju(oznaka_linije);
	vector<int> broj_zajednickih_stanica;
	vector<Linija*> sa_zajednickim_stanicama;

	for (int i = 0; i < linija->uzmiVelicinuSmeraA(); i++) {  // za smer A
		CvorGrafa* cvor = pronadjiCvor(linija->uzmiIzSmeraA(i));
		for (int j = 0; j < cvor->uzmiBrojProlaznihLinija(); j++) {
			if (cvor->uzmiLiniju(j)->uzmiOznakuLinije() != oznaka_linije) {
				int pom = pozicijaLinije(cvor->uzmiLiniju(j), sa_zajednickim_stanicama);
				if (pom == -1) {
					sa_zajednickim_stanicama.push_back(cvor->uzmiLiniju(j));
					broj_zajednickih_stanica.push_back(1);
				}
				else {
					broj_zajednickih_stanica[pom]++;
				}
			}
		}
	}
	for (int i = 0; i < linija->uzmiVelicinuSmeraB(); i++) {  // za smer B
		CvorGrafa* cvor = pronadjiCvor(linija->uzmiIzSmeraB(i));
		for (int j = 0; j < cvor->uzmiBrojProlaznihLinija(); j++) {
			if (cvor->uzmiLiniju(j)->uzmiOznakuLinije() != oznaka_linije) {
				int pom = pozicijaLinije(cvor->uzmiLiniju(j), sa_zajednickim_stanicama);
				if (pom == -1) {
					sa_zajednickim_stanicama.push_back(cvor->uzmiLiniju(j));
					broj_zajednickih_stanica.push_back(1);
				}
				else {
					broj_zajednickih_stanica[pom]++;
				}
			}
		}
	}

	string maks_str = "";
	int maks = 0, br_maks = 0;
	for (int i = 0; i < broj_zajednickih_stanica.size(); i++) {
		if (broj_zajednickih_stanica[i] == maks) {
			br_maks++;
		}
		else if (broj_zajednickih_stanica[i] > maks) {
			maks = broj_zajednickih_stanica[i];
			br_maks = 1;
		}
	}
	if (br_maks == 1) {
		for (int i = 0; i < broj_zajednickih_stanica.size(); i++) {
			if (broj_zajednickih_stanica[i] == maks) {
				maks_str = sa_zajednickim_stanicama[i]->uzmiOznakuLinije();
				break;
			}
		}
	}
	else {
		int pok;
		for (int i = 0; i < broj_zajednickih_stanica.size(); i++) {
			if (br_maks == 1) {
				pok = i;
				break;
			}
			if (broj_zajednickih_stanica[i] == maks) {
				maks_str = maks_str + sa_zajednickim_stanicama[i]->uzmiOznakuLinije() + ", ";
				br_maks--;
			}
		}
		for (int i = pok; i < broj_zajednickih_stanica.size(); i++) {
			if (broj_zajednickih_stanica[i] == maks) {
				maks_str = maks_str + sa_zajednickim_stanicama[i]->uzmiOznakuLinije();
				break;
			}
		}
	}
	sortiraj(sa_zajednickim_stanicama);
	for (int i = 0; i < sa_zajednickim_stanicama.size(); i++) {
		izlaz << sa_zajednickim_stanicama[i]->uzmiOznakuLinije() << " ";
	}
	izlaz << endl;
	izlaz << maks_str;

	cout << "Generisan je fajl statistika_" << oznaka_linije << ".txt sa statistickim informacijama o liniji " << oznaka_linije << "." << endl;
	izlaz.close();
}

void Simulator::biloKojaPutanja() {
	int pocetak, kraj;
	cout << "Molimo Vas, unesite sifru pocetnog i krajnjeg stajalista izmedju kojih zelite da se generise putanja." << endl;
	cin >> pocetak;
	cin >> kraj;

	fstream izlaz("putanja_" + to_string(pocetak) + "_" + to_string(kraj) + ".txt", ios::out);
	int n = graf_.size();
	for (int i = 0; i < n; i++) {
		vector<int> pom;
		for (int j = 0; j < graf_[i]->uzmiBrojIzlaznihStajalista(); j++) {
			pom.push_back(-1);
		}
		veze_.push_back(pom);
	}
	//kreiranje veza izmedju stajalista
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < graf_[i]->uzmiBrojIzlaznihStajalista(); j++) {
			dodajVezu(graf_[i]->uzmiStajaliste()->uzmiMojuSifru(), graf_[i]->uzmiIzlaznoStajaliste(j)->uzmiMojuSifru());
		}
	}
	for (int i = 0; i < n; i++) {
		distanca_.push_back(INT_MAX);
		prethodni_.push_back(-1);
		linije_.push_back("");
	}

	int moj_pocetak = pronadjiMojuSifru(pocetak);
	int moj_kraj = pronadjiMojuSifru(kraj);
	bool nadjen = BFS(moj_pocetak, moj_kraj, n);

	for (int i = 0; i < linije_.size(); i++) {
		cout << linije_[i] << endl;
	}

	// kreiranje putanje
	vector<int> putanja;
	int korak = moj_kraj;
	putanja.push_back(korak);
	while (prethodni_[korak] != -1) {
		putanja.push_back(prethodni_[korak]);
		korak = prethodni_[korak];
	}

	for (int i = 0; i < putanja.size(); i++) {
		cout << putanja[i] << " ";
	}
	cout << endl;

	int br = putanja.size() - 2;
	izlaz << "->" << linije_[putanja[br]] << endl;
	izlaz << pronadjiSifruStajalista(putanja[br + 1]) << " " << pronadjiSifruStajalista(putanja[br]);
	br = br - 1;
	while (br >= 0) {
		if (linije_[putanja[br]] != linije_[putanja[br + 1]]) {
			izlaz << endl << linije_[putanja[br + 1]] << "->" << linije_[putanja[br]] << endl;
			izlaz << pronadjiSifruStajalista(putanja[br + 1]) << " " << pronadjiSifruStajalista(putanja[br]);
		}
		else {
			izlaz << " " << pronadjiSifruStajalista(putanja[br]);
		}
		br--;
	}
	
	cout << "Generisan je fajl putanja_" << pocetak << "_" << kraj << ".txt sa putanjom izmedju stajalista " << pocetak << " i " << kraj << "." << endl;
	izlaz.close();
}

void Simulator::putanjaSaNajmanjeStajalista() {
	int pocetak, kraj;
	cout << "Molimo Vas, unesite sifru pocetnog i krajnjeg stajalista izmedju kojih zelite da se generise putanja." << endl;
	cin >> pocetak;
	cin >> kraj;

	fstream izlaz("putanja_" + to_string(pocetak) + "_" + to_string(kraj) + ".txt", ios::out);
	int n = graf_.size();
	for (int i = 0; i < n; i++) {
		vector<int> pom;
		for (int j = 0; j < graf_[i]->uzmiBrojIzlaznihStajalista(); j++) {
			pom.push_back(-1);
		}
		veze_.push_back(pom);
	}
	//kreiranje veza izmedju stajalista
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < graf_[i]->uzmiBrojIzlaznihStajalista(); j++) {
			dodajVezu(graf_[i]->uzmiStajaliste()->uzmiMojuSifru(), graf_[i]->uzmiIzlaznoStajaliste(j)->uzmiMojuSifru());
		}
	}
	for (int i = 0; i < n; i++) {
		distanca_.push_back(INT_MAX);
		prethodni_.push_back(-1);
		linije_.push_back("");
	}

	int moj_pocetak = pronadjiMojuSifru(pocetak);
	int moj_kraj = pronadjiMojuSifru(kraj);
	bool nadjen = BFS(moj_pocetak, moj_kraj, n);

	// kreiranje putanje
	vector<int> putanja;
	int korak = moj_kraj;
	putanja.push_back(korak);
	while (prethodni_[korak] != -1) {
		putanja.push_back(prethodni_[korak]);
		korak = prethodni_[korak];
	}

	int br = putanja.size() - 2;
	izlaz << "->" << linije_[putanja[br]] << endl;
	izlaz << pronadjiSifruStajalista(putanja[br + 1]) << " " << pronadjiSifruStajalista(putanja[br]);
	br = br - 1;
	while (br >= 0) {
		if (linije_[putanja[br]] != linije_[putanja[br + 1]]) {
			izlaz << endl << linije_[putanja[br + 1]] << "->" << linije_[putanja[br]] << endl;
			izlaz << pronadjiSifruStajalista(putanja[br + 1]) << " " << pronadjiSifruStajalista(putanja[br]);
		}
		else {
			izlaz << " " << pronadjiSifruStajalista(putanja[br]);
		}
		br--;
	}

	cout << "Generisan je fajl putanja_" << pocetak << "_" << kraj << ".txt sa putanjom izmedju stajalista " << pocetak << " i " << kraj << "." << endl;
	izlaz.close();
}

void Simulator::putanjaSaNajmanjePresedanja() {
	int pocetak, kraj;
	cout << "Molimo Vas, unesite sifru pocetnog i krajnjeg stajalista izmedju kojih zelite da se generise putanja." << endl;
	cin >> pocetak;
	cin >> kraj;

	fstream izlaz("putanja_" + to_string(pocetak) + "_" + to_string(kraj) + ".txt", ios::out);

	vector<int> presedanja;
	vector<int> putanja;
	for (int i = 0; i < sva_stajalista_.size(); i++) {
		presedanja.push_back(0);
	}
	CvorGrafa* cvor = pronadjiCvor(pocetak);
	vector<string> linije;
	for (int i = 0; i < cvor->uzmiBrojProlaznihLinija(); i++) {
		Linija* linija = cvor->uzmiLiniju(i);
		for (int j = 0; j < linija->uzmiVelicinuSmeraA(); j++) {
			presedanja[pronadjiMojuSifru(linija->uzmiIzSmeraA(j))] = 1;
			if (linija->uzmiIzSmeraA(j) == kraj) {
				izlaz << "->" << linija->uzmiOznakuLinije() << endl;
				for (int k = 0; k <= j; k++) {
					
				}
			}
		}
	}
	for (int i = 0; i < sva_stajalista_.size(); i++) {
		if(presedanja[i]==0) {}
	}

	cout << "Generisan je fajl putanja_" << pocetak << "_" << kraj << ".txt sa putanjom izmedju stajalista " << pocetak << " i " << kraj << "." << endl;
	izlaz.close();
}

int Simulator::uzmiBrojStajalista(){
	return graf_.size();
}

void Simulator::dodajVezu(int prvi, int drugi) {
	if (veze_[prvi][0] == -1) {
		while (veze_[prvi].size() > 0) {
			veze_[prvi].pop_back();
		}
	}
	veze_[prvi].push_back(drugi);
}

Stajaliste* Simulator::pronadjiStajaliste(int sifra_stajalista) {
	bool vratio = false;
	for (int i = 0; i < sva_stajalista_.size(); i++) {
		if (sva_stajalista_[i]->uzmiSifruStajalista() == sifra_stajalista) {
			vratio = true;
			return sva_stajalista_[i];
		}
	}
	if (!vratio) {
		return nullptr;
	}
}

Linija* Simulator::pronadjiLiniju(string oznaka_linije) {
	bool vratio = false;
	for (int i = 0; i < sve_linije_.size(); i++) {
		if (sve_linije_[i]->uzmiOznakuLinije() == oznaka_linije) {
			vratio = true;
			return sve_linije_[i];
		}
	}
	if (!vratio) {
		return nullptr;
	}
}

CvorGrafa* Simulator::pronadjiCvor(int sifra_stajalista) {
	bool vratio = false;
	for (int i = 0; i < graf_.size(); i++) {
		if (graf_[i]->uzmiStajaliste()->uzmiSifruStajalista() == sifra_stajalista) {
			vratio = true;
			return graf_[i];
		}
	}
	if (!vratio) {
		return nullptr;
	}
}

int Simulator::pozicijaLinije(Linija* linija, vector<Linija*> niz) {
	for (int i = 0; i < niz.size(); i++) {
		if (linija->uzmiOznakuLinije() == niz[i]->uzmiOznakuLinije()) {
			return i;
		}
	}
	return -1;
}

void Simulator::sortiraj(vector<Linija*> niz) {
	for (int i = 0; i < niz.size() - 1; i++) {
		for (int j = i + 1; j < niz.size(); j++) {
			if (niz[i]->uzmiOznakuLinije().compare(niz[j]->uzmiOznakuLinije()) > 0) {
				Linija* pom = niz[i];
				niz[i] = niz[j];
				niz[j] = pom;
			}
		}
	}
}

int Simulator::pronadjiMojuSifru(int sifra_stajalista) {
	for (int i = 0; i < sva_stajalista_.size(); i++) {
		if (sva_stajalista_[i]->uzmiSifruStajalista() == sifra_stajalista) {
			return sva_stajalista_[i]->uzmiMojuSifru();
		}
	}
}

int Simulator::pronadjiSifruStajalista(int moja_sifra) {
	for (int i = 0; i < sva_stajalista_.size(); i++) {
		if (sva_stajalista_[i]->uzmiMojuSifru() == moja_sifra) {
			return sva_stajalista_[i]->uzmiSifruStajalista();
		}
	}
}

void Simulator::dodajLinijuVeze(int odrediste) {
	bool dodata = false;
	if (linije_[prethodni_[odrediste]] == "") {
		cout << "usao if" << endl;
		CvorGrafa* cvor = pronadjiCvor(pronadjiSifruStajalista(odrediste));
		for (int i = 0; i < cvor->uzmiBrojProlaznihLinija(); i++) {
			Linija* test = cvor->uzmiLiniju(i);
			cout << test->uzmiOznakuLinije() << endl;
			for (int i = 1; i < test->uzmiVelicinuSmeraA(); i++) {
				if (test->uzmiIzSmeraA(i) == pronadjiSifruStajalista(odrediste) && test->uzmiIzSmeraA(i - 1) == pronadjiSifruStajalista(prethodni_[odrediste])) {
					linije_[odrediste] = test->uzmiOznakuLinije();
					cout << "smer A " << odrediste << " " << linije_[odrediste] << endl;
					dodata = true;
					break;
				}
			}
			if (dodata) break;
			for (int i = 1; i < test->uzmiVelicinuSmeraB(); i++) {
				if (test->uzmiIzSmeraB(i) == pronadjiSifruStajalista(odrediste) && test->uzmiIzSmeraB(i - 1) == pronadjiSifruStajalista(prethodni_[odrediste])) {
					linije_[odrediste] = test->uzmiOznakuLinije();
					cout << "smer B " << odrediste << " " << linije_[odrediste] << endl;
					dodata = true;
					break;
				}
			}
			if (dodata) break;
		}
	}
	else {
		cout << "usao else" << endl;
		CvorGrafa* cvor = pronadjiCvor(pronadjiSifruStajalista(odrediste));
		for (int i = 0; i < cvor->uzmiBrojProlaznihLinija(); i++) {
			Linija* test = cvor->uzmiLiniju(i);
			cout << test->uzmiOznakuLinije() << endl;
			if (test->uzmiOznakuLinije() == linije_[prethodni_[odrediste]]) {
				linije_[odrediste] = linije_[prethodni_[odrediste]];
				cout << "kao prethodna " << odrediste << " " << linije_[odrediste] << endl;
				dodata = true;
				break;
			}
		}
		if (!dodata) {
			for (int i = 0; i < cvor->uzmiBrojProlaznihLinija(); i++) {
				Linija* test = cvor->uzmiLiniju(i);
				cout << test->uzmiOznakuLinije() << endl;
				for (int i = 1; i < test->uzmiVelicinuSmeraA(); i++) {
					if (test->uzmiIzSmeraA(i) == pronadjiSifruStajalista(odrediste) && test->uzmiIzSmeraA(i - 1)) {
						linije_[odrediste] = test->uzmiOznakuLinije();
						cout << "smer A " << odrediste << " " << linije_[odrediste] << endl;
						dodata = true;
						break;
					}
				}
				if (dodata) break;
				for (int i = 1; i < test->uzmiVelicinuSmeraB(); i++) {
					if (test->uzmiIzSmeraB(i) == odrediste && test->uzmiIzSmeraB(i - 1)) {
						linije_[odrediste] = test->uzmiOznakuLinije();
						cout << "smer B " << odrediste << " " << linije_[odrediste] << endl;
						dodata = true;
						break;
					}
				}
				if (dodata) break;
			}
		}
	}
}

bool Simulator::BFS(int pocetak, int kraj, int n) {
	list<int> red;
	vector<bool> posecen;

	for (int i = 0; i < n; i++) {
		posecen.push_back(false);
		distanca_[i] = INT_MAX;
		prethodni_[i] = -1;
	}

	posecen[pocetak] = true;
	distanca_[pocetak] = 0;
	red.push_back(pocetak);

	while (!red.empty()) {
		int u = red.front();
		red.pop_front();
		for (int i = 0; i < veze_[u].size(); i++) {
			if (posecen[veze_[u][i]] == false) {
				posecen[veze_[u][i]] = true;
				distanca_[veze_[u][i]] = distanca_[u] + 1;
				prethodni_[veze_[u][i]] = u;
				dodajLinijuVeze(veze_[u][i]);
				red.push_back(veze_[u][i]);

				if (veze_[u][i] == kraj) {
					return true;
				}
			}
		}
	}
	return false;
}

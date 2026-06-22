#include <iostream>
#include <vector>
#include <string>
#include <algorithm> //za obrtanje redosljeda cifara ID-a u GenerisiID
#include <regex>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;
const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI METODA (SVE ISTO VAZI I ZA FUNKCIJE), TE BROJ ITIP PARAMETARA MORAJU BITI IDENTICNI "
"ONIMA KOJI SU KORISTENI U TESTNOM CODE - U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. "
"OSTALE POMOCNE METODE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U METODAMA U KOJIMA JE TO NAZNACENO.\n"
"6. SVE METODE POZVANE U MAIN-U ZADATKA TREBAJU POSTOJATI. UKOLIKO NISTE ZADOVOLJNI IMPLEMENTACIJOM "
"POTREBNO JE DA IMPLEMENTIRATE BAREM TIJELO TIH METODA (METODA MOZE BITI PRAZNA), "
"A AKO METODA TREBA VRATITI NEKI PODATAK ONDA MOZETE VRATITI BILO KOJU TJ.ZELJENU VRIJEDNOST ZAHTIJEVANOG TIPA.!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRAJTE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA npr.IB150051.docx)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11.ZA POTREBE TESTIRANJA, U MAIN-U, BUDITE SLOBODNI DODATI TESTNIH PODATAKA(POZIVA METODA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12.ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022 I RJESENJE TESTIRAJTE U OBA MODA(F5 i Ctrl + F5)!\n"
"13.NA KRAJU ISPITA PROVJERITE DA LI STE RJEÅ ENJE KOPIRALI U ADEKVATAN FOLDER NA FTP SERVERU\n"
"-------------------------------------------------------------------------------\n";
const char* crt = "\n-------------------------------------------\n";
enum Drzava {
	ENGLESKA, SPANIJA, HOLANDIJA, FRANCUSKA, BOSNA_I_HERCEGOVINA
};

ostream& operator <<(ostream& COUT, Drzava drzava) {
	switch (drzava) {
	case ENGLESKA:
		COUT << "ENGLESKA";
		break;
	case SPANIJA:
		COUT << "SPANIJA";
		break;
	case HOLANDIJA:
		COUT << "HOLANDIJA";
		break;
	case FRANCUSKA:
		COUT << "FRANCUSKA";
		break;
	case BOSNA_I_HERCEGOVINA:
		COUT << "BOSNA I HERCEGOVINA";
		break;
	}
	return COUT;
}

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	if (dealociraj)
		delete[]sadrzaj;
	return temp;
}


string GenerisiID(string imePrezime, int id) {
	string sifra="";
	int prezimeIndeks = imePrezime.find(' ') + 1;
	sifra += toupper(imePrezime[0]);
	if (id < 10)sifra += "000";
	else if (id < 100)sifra += "00";
	else if (id < 1000)sifra += "0";
	sifra += toupper(imePrezime[prezimeIndeks]);

	string brojString = to_string(id);
	reverse(brojString.begin(), brojString.end());
	sifra += brojString;
	return sifra;
}

bool ValidirajID(string id) {
	return regex_match(id, regex("[A-Z]000[A-Z][0-9]")) ||
		regex_match(id, regex("[A-Z]00[A-Z][0-9]{2}")) ||
		regex_match(id, regex("[A-Z]0[A-Z][0-9]{3}")) ||
		regex_match(id, regex("[A-Z]{2}[0-9]{4}"));
}

template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max];
	T2 _elementi2[max];
	int* _trenutno;
public:
	Kolekcija() {
		_trenutno = new int(0);
	}
	~Kolekcija() {
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	const T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
	const T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) <<
			endl;
		return COUT;
	}
	Kolekcija(const Kolekcija& obj) {
		_trenutno = new int(*obj._trenutno);
		for (int i = 0; i < *obj._trenutno; i++) {
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}
	}
	Kolekcija& operator =(const Kolekcija& obj) {
		if (this != &obj) {
			delete _trenutno; _trenutno = nullptr;
			_trenutno = new int(*obj._trenutno);
			for (int i = 0; i < *obj._trenutno; i++) {
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];
			}
		}return *this;
	}
	void AddElement(const T1& el1, const T2& el2) {
		_elementi1[getTrenutno()] = el1;
		_elementi2[getTrenutno()] = el2;
		(*_trenutno)++;
	}
	Kolekcija& InsertAt(const T1& el1, const T2& el2, const int& lokacija) {
		for (int i = *_trenutno; i > lokacija; i--) {
			_elementi1[i] = _elementi1[i - 1];
			_elementi2[i] = _elementi2[i - 1];
		}
		_elementi1[lokacija] = el1;
		_elementi2[lokacija] = el2;
		(*_trenutno)++;
		return *this;
	}
	Kolekcija RemoveRange(const int& start, const int& end) {
		if (start<0 || end >= *_trenutno || start>end)
			throw exception("Opseg za uklanjanje elemenata nije validan!\n");
		int brojElemenata = end - start + 1;

		Kolekcija novaKolekcija;
		for (int i = start; i <= end; i++) {
			novaKolekcija.AddElement(getElement1(i), getElement2(i));
		}
		for (int i = end + 1; i < *_trenutno; i++) { //preostale elemente u *this pomjeramo ULIJEVO
			_elementi1[i - brojElemenata] = _elementi1[i];
			_elementi2[i - brojElemenata] = _elementi2[i];
		}
		(*_trenutno) -= brojElemenata;
		return novaKolekcija;
	}
};
class Vrijeme {
	int* _sat, * _minuta, * _sekunda;
public:
	Vrijeme(int sat = 10, int minuta = 0, int sekunda = 0) {
		_sat = new int(sat);
		_minuta = new int(minuta);
		_sekunda = new int(sekunda);
	}
	~Vrijeme() {
		delete _sat; _sat = nullptr;
		delete _minuta; _minuta = nullptr;
		delete _sekunda; _sekunda = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const Vrijeme& obj) {
		COUT << *obj._sat << ":" << *obj._minuta << ":" << *obj._sekunda;
		return COUT;
	}
	int GetSate()const { return *_sat; }
	int GetMinute()const { return *_minuta; }
	int GetSekunde()const { return *_sekunda; }

	Vrijeme(const Vrijeme& obj) {
		_sat = new int(*obj._sat);
		_minuta = new int(*obj._minuta);
		_sekunda = new int(*obj._sekunda);
	}
	Vrijeme& operator=(const Vrijeme& obj) {
		if (this != &obj) {
			delete _sat; _sat = nullptr;
			delete _minuta; _minuta = nullptr;
			delete _sekunda; _sekunda = nullptr;
			_sat = new int(*obj._sat);
			_minuta = new int(*obj._minuta);
			_sekunda = new int(*obj._sekunda);
		}return *this;
	}
	bool operator ==(const Vrijeme& obj)const {
		return GetSate() == obj.GetSate() &&
			GetMinute() == obj.GetMinute() &&
			GetSekunde() == obj.GetSekunde();

	}
};
class Pogodak {
	Vrijeme* _vrijemePogotka;
	char* _napomena;
public:
	Pogodak(Vrijeme vrijeme, const char* napomena) {
		_napomena = GetNizKaraktera(napomena);
		_vrijemePogotka = new Vrijeme(vrijeme);
	}
	~Pogodak() {
		delete[] _napomena; _napomena = nullptr;
		delete _vrijemePogotka; _vrijemePogotka = nullptr;
	}
	Vrijeme GetVrijemePogotka()const { return *_vrijemePogotka; }
	char* GetNapomena() { return _napomena; }
	const char* GetNapomena() const{ return _napomena; }
	friend ostream& operator<< (ostream& COUT, const Pogodak& obj) {
		COUT << *obj._vrijemePogotka << " -> " << obj._napomena;
		return COUT;
	}
	Pogodak(const Pogodak& obj) {
		_vrijemePogotka = new Vrijeme{ *obj._vrijemePogotka };
		_napomena = GetNizKaraktera(obj._napomena);
	}
	Pogodak& operator = (const Pogodak& obj){
		if (this != &obj) {
			delete[] _napomena; _napomena = nullptr;
			delete _vrijemePogotka; _vrijemePogotka = nullptr;
			_vrijemePogotka = new Vrijeme{ *obj._vrijemePogotka };
			_napomena = GetNizKaraktera(obj._napomena);
		}return *this;
	}
	bool operator==(const Pogodak& obj)const {
		return strcmp(GetNapomena() ,obj.GetNapomena())==0 &&
			GetVrijemePogotka() == obj.GetVrijemePogotka();
	}
};
class Igrac {
	static int _id;
	char* _ID; // za inicijalizaciju _ID-a iskoristiti funkciju GenerisiID tj.atributa _imePrezime(inicijala imena i prezimena) i statickog clana _id
	char* _imePrezime;
	vector<Pogodak*> _pogoci;
public:
	Igrac(const char* imePrezime) {
		_imePrezime = GetNizKaraktera(imePrezime);
		_ID = GetNizKaraktera( GenerisiID(_imePrezime, _id++).c_str());
	}
	~Igrac() {
		delete[]_ID; _ID = nullptr;
		delete[]_imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _pogoci.size(); i++) {
			delete _pogoci[i];
			_pogoci[i] = nullptr;
		}
		_pogoci.clear();
	}
	char* GetImePrezime() { return _imePrezime; }
	char* GetID() { return _ID; }
	const char* GetID()const { return _ID; }
	vector<Pogodak*>& GetPogoci() { return _pogoci; }
	friend ostream& operator<< (ostream& COUT, Igrac& obj) {
		COUT << obj._ID << " -> " << obj._imePrezime;
		for (size_t i = 0; i < obj._pogoci.size(); i++)
			COUT << *obj._pogoci[i] << endl;
		return COUT;
	}
	Igrac(const Igrac& obj) {
		_imePrezime = GetNizKaraktera(obj._imePrezime);
		_ID = GetNizKaraktera(obj._ID);
		for (size_t i = 0; i < obj._pogoci.size(); i++) {
			_pogoci.push_back(new Pogodak{ *obj._pogoci[i] });
		}
	}
	Igrac& operator =(const Igrac& obj) {
		if (this != &obj) {
			delete[]_ID; _ID = nullptr;
			delete[]_imePrezime; _imePrezime = nullptr;
			for (size_t i = 0; i < _pogoci.size(); i++) {
				delete _pogoci[i];
				_pogoci[i] = nullptr;
			}
			_pogoci.clear();
			_imePrezime = GetNizKaraktera(obj._imePrezime);
			_ID = GetNizKaraktera(obj._ID);
			for (size_t i = 0; i < obj._pogoci.size(); i++) {
				_pogoci.push_back(new Pogodak{ *obj._pogoci[i] });
			}

		}return *this;
	}
};
int Igrac::_id = 1;
class Reprezentacija {
	Drzava _drzava;
	vector<Igrac> _igraci;
public:
	Reprezentacija(Drzava drzava = BOSNA_I_HERCEGOVINA) {
		_drzava = drzava;
	}
	Drzava GetDrzava() const{ return _drzava; }
	vector<Igrac>& GetIgraci() { return _igraci; }
	const vector<Igrac>& GetIgraci()const { return _igraci; }

	void AddIgrac(const Igrac& igrac) {
		for (Igrac& player : GetIgraci())
			if (strcmp(player.GetID(), igrac.GetID()) == 0)
				throw exception("Dodavanje duplih igraca nije moguce!\n");
		_igraci.push_back(igrac);
	}
	bool operator ==(const Reprezentacija& obj)const {
		return GetDrzava() == obj.GetDrzava();
	}
};
mutex mtx;//globalni mutex za slanje email-a
class Prventstvo {
	Kolekcija<Reprezentacija, Reprezentacija, 20> _utakmice;
public:
	Kolekcija<Reprezentacija, Reprezentacija, 20>& GetUtakmice() {
		return _utakmice;
	}
	void AddUtakmicu(const Reprezentacija& rep1, const Reprezentacija& rep2) {
		for (int i = 0; i < _utakmice.getTrenutno(); i++) {
			if (_utakmice.getElement1(i) == rep1 &&
				_utakmice.getElement2(i) == rep2)
				throw exception("Dodavanje duplih susreta nije moguce!\n");
		}
		_utakmice.AddElement(rep1, rep2);
	}
	bool AddPogodak(Drzava drzavaDomacina, Drzava drzavaGosta, const string& identifikator, const Pogodak& pogodak) {
		for (int i = 0; i < _utakmice.getTrenutno(); i++) {
			Reprezentacija& repDomacina = _utakmice.getElement1(i);
			Reprezentacija& repGosta = _utakmice.getElement2(i);

			if (repDomacina.GetDrzava() == drzavaDomacina && repGosta.GetDrzava() == drzavaGosta ||
				repDomacina.GetDrzava() == drzavaGosta && repGosta.GetDrzava() == drzavaDomacina) {
				Reprezentacija* ucesnici[] = {&repDomacina,&repGosta};

				for (int j = 0; j < 2; j++) { //provjeravamo oba tima, samo unutar jedne petlje.
					for (size_t k = 0; k < ucesnici[j]->GetIgraci().size(); k++) { //indeks j=0 domaci, indeks j=1 gostujuci tim
						Igrac& trenutniIgrac = ucesnici[j]->GetIgraci()[k];

						if ((identifikator == trenutniIgrac.GetImePrezime()) || (identifikator == trenutniIgrac.GetID())) {
							for (size_t l = 0; l < trenutniIgrac.GetPogoci().size();l++) {
								if (pogodak == *trenutniIgrac.GetPogoci()[l]) {
									return false; //dupliranje pogodaka nije dozvoljeno
								}
							}
							trenutniIgrac.GetPogoci().push_back(new Pogodak{ pogodak });

							//priprema podataka za email
							int rednibrojPogotka = trenutniIgrac.GetPogoci().size();
							string imeStrijelca = trenutniIgrac.GetImePrezime();
							int goloviDomacina = 0; int goloviGosta = 0;
							vector<string>emailoviZaSlanje;
							Vrijeme vrijemePogotka = pogodak.GetVrijemePogotka();

							for (size_t p = 0; p < repDomacina.GetIgraci().size();p++) {
								goloviDomacina+=repDomacina.GetIgraci()[p].GetPogoci().size();
								emailoviZaSlanje.push_back(repDomacina.GetIgraci()[p].GetID());
							}
							for (size_t p = 0; p < repGosta.GetIgraci().size(); p++) {
								goloviGosta += repGosta.GetIgraci()[p].GetPogoci().size();
								emailoviZaSlanje.push_back(repGosta.GetIgraci()[p].GetID());
							}
							thread t([=]() {
								mtx.lock();
								for (int r = 0; r < emailoviZaSlanje.size(); r++) {
									
									cout << "\nTo: " << emailoviZaSlanje[r] << "@euro2024.com\n";
									cout << "From: info@euro2024.com\n";
									cout << "Subject: Informacija\n";
									cout << "Postovani,\n";
									cout << "U " << vrijemePogotka << " sati igrac " << imeStrijelca
										<< " je zabiljezio svoj " << rednibrojPogotka << " pogodak na ovoj utakmici.\n";
									cout << "Trenutni rezultat je:\n";
									cout << drzavaDomacina << " " << goloviDomacina << " : " << goloviGosta << " " << drzavaGosta << endl;
									cout << "Puno srece u nastavku susreta.\n";
									cout << "Neka bolji tim pobijedi.\n";
									cout << "-------------------------------------------\n";
									this_thread::sleep_for(chrono::seconds(2));
								}
								mtx.unlock();
								});
							t.join();
							return true;

						}
					
					}
				}
				return false; //nema igraca kojem zelimo dodati pogodak
			}
		}
		return false; //nema utakmice kojoj zelimo dodati pogodak
	}
	friend ostream& operator<<(ostream& COUT, Prventstvo& obj) {
		for (int i = 0; i < obj._utakmice.getTrenutno(); i++) {
			Reprezentacija& r1 = obj._utakmice.getElement1(i);
			Reprezentacija& r2 = obj._utakmice.getElement2(i);

			vector<string> strijelci1, strijelci2;
			for (auto& igrac : r1.GetIgraci())
				for (size_t p = 0; p < igrac.GetPogoci().size(); p++) strijelci1.push_back(igrac.GetImePrezime());

			for (auto& igrac : r2.GetIgraci())
				for (size_t p = 0; p < igrac.GetPogoci().size(); p++) strijelci2.push_back(igrac.GetImePrezime());

			COUT << "\n-------------------------------------------\n";
			COUT << "(" << strijelci1.size() << ") " << r1.GetDrzava() << " : " << r2.GetDrzava() << " (" << strijelci2.size() << ")\n";
			COUT << "-------------------------------------------\n";

			size_t maxScorers = max(strijelci1.size(), strijelci2.size());
			for (size_t j = 0; j < maxScorers; j++) {
				if (j < strijelci1.size()) COUT << strijelci1[j];
				else COUT << string(15, ' ');

				COUT << " ";

				if (j < strijelci2.size()) COUT << strijelci2[j];
				COUT << endl;
			}
			COUT << "-------------------------------------------\n";
		}
		return COUT;
	}
	vector<Igrac*> operator()(int minPogodaka) {
		vector<Igrac*> rezultat;
		for (int i = 0; i < _utakmice.getTrenutno(); i++) {
			Reprezentacija* ucesnici[] = { &_utakmice.getElement1(i), &_utakmice.getElement2(i) };
			for (int j = 0; j < 2; j++) {
				for (size_t k = 0; k < ucesnici[j]->GetIgraci().size(); k++) {
					if (ucesnici[j]->GetIgraci()[k].GetPogoci().size() >= minPogodaka) {
						rezultat.push_back(&ucesnici[j]->GetIgraci()[k]);
					}
				}
			}
		}
		return rezultat;
	}
};
const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite osnovne preduslove koji moraju biti ispunjeni da bi se realizovao polimorfizam(navesti kratki primjer) ? \n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite razloge koristenja kljucnih rijeci abstract i ciste virtualne metode, te razlike izmedju njih ? \n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
void main() {
	
	/*
	Globalna funkcija GenerisiID vraca ID igraca na osnovu vrijednosti
   proslijedjenih parametara. Funkcija generise
	ID sa maksimalno 4 cifre, ne racunajuci inicijale tj. prva slova
   imena i prezimena.
	Podrazumijeva se da ce uvijek biti proslijedjene validne
   vrijednosti parametara. Ukoliko se proslijede
	mala pocetna slova imena ili prezimena, potrebno ih je
   konvertovati u velika.
	U okviru generisanog ID-a, proslijedjena cjelobrojna vrijednost
   treba biti u obrnutom redoslijedu cifara.
	*/
	cout << GenerisiID("Denis Music", 3) << endl;//treba vratiti D000M3
	cout << GenerisiID("Jasmin Azemovic", 14) << endl;//treba vratiti J00A41
	cout << GenerisiID("Goran Skondric", 156) << endl;//treba vratiti G0S651
	cout << GenerisiID("emina junuz", 1798) << endl;//treba vratiti EJ8971

	//Za validaciju ID-a koristiti funkciju ValidirajID koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajID("D000M3"))
		cout << "ID VALIDAN" << endl;
	if (ValidirajID("J00A41"))
		cout << "ID VALIDAN" << endl;
	if (!ValidirajID("G00S651"))
		cout << "ID NIJE VALIDAN" << endl;
	if (!ValidirajID("Ej8971"))
		cout << "ID NIJE VALIDAN" << endl;
	int kolekcijaTestSize = 9;
	Kolekcija<int, int, 10> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);//dodaje vrijednosti u kolekciju
	cout << kolekcija1 << crt;
	///* metoda InsertAt treba da doda vrijednosti prvog i drugog
 //  parametra na lokaciju koja je definisana trecim parametrom. Povratna
 //  vrijednost metode
	//je objekat (pozivaoc metode, u konkretnom slucaju objekat
 //  kolekcija1) u okviru koga su, na definisanu lokaciju, dodati
 //  zahtijevani parametri.
	//Nakon izvrsenja metode InsertAt, oba objekta, kolekcija1 i
 //  kolekcija2, bi trebali posjedovati sljedeci sadrzaj:
	//10 10
	//0 0
	//1 1
	//2 2
	//* ....
	//*/
	Kolekcija<int, int, 10> kolekcija2 = kolekcija1.InsertAt(10, 10, 0);
	cout << kolekcija2 << crt;
	///*Metoda RemoveRange prihvata lokacija OD i DO, te u tom opsegu
 //  uklanja sve elemente iz kolekcije. U slucaju da zahtijevani opseg ne
 //  postoji u kolekciji
	//metoda treba baciti izuzetak. Na kraju, metoda treba da vrati
 //  pokazivac na novi objekat tipa kolekcija koji sadrzi samo uklonjene
 //  elemente*/

 //  // Not the professor here, ovdje ne treba vratiti pokazivac, 
 //  // to je izgleda greska tokom pravljenja postavke za ispit ostala
	Kolekcija<int, int, 10> kolekcija3 = kolekcija1.RemoveRange(1, 3);
	cout << kolekcija3 << endl;
	cout << kolekcija1 << crt;
	/*kolekcija3 bi trebala sadrzavati sljedece elemente:
	0 0
	1 1
	2 2
	dok bi kolekcija1 trebala sadrzavati sljedece elemente:
	10 10
	3 3
	4 4
	......
	*/
	kolekcija1 = kolekcija3;
	cout << kolekcija1;
	Vrijeme
		prviPogodak201633(20, 16, 33),
		drugiPogodak202319(20, 23, 19),
		treciPogodak205108(20, 51, 8),
		cetvrtiPogodak210654(21, 6, 54);
	Igrac denis("Denis Music"), jasmin("Jasmin Azemovic"),
		goran("Goran Skondric"), adil("Adil Joldic");

	if (strcmp(denis.GetID(), "D000M1") == 0 && strcmp(jasmin.GetID(), "J000A2") == 0)
		cout << "ID se uspjesno generise!" << endl;
	Pogodak prviPogodak(prviPogodak201633, "podaci o prvom pogotku"),
		drugiPogodak(drugiPogodak202319, "podaci o drugom pogotku"),
		treciPogodak(treciPogodak205108, "podaci o trecem pogotku"),
		cetvrtiPogodak(cetvrtiPogodak210654, "podaci o cetvrtom pogotku");
	Reprezentacija BIH(BOSNA_I_HERCEGOVINA), ENG(ENGLESKA);
	BIH.AddIgrac(denis);
	BIH.AddIgrac(jasmin);
	ENG.AddIgrac(goran);
	ENG.AddIgrac(adil);
	try
	{
		BIH.AddIgrac(denis);//onemoguciti dodavanje istih igraca - provjeravati ID
	}
	catch (exception& obj)
	{
		cout << obj.what();
	}
	Prventstvo euro2024;
	euro2024.AddUtakmicu(BIH, ENG);
	try
	{
		euro2024.AddUtakmicu(BIH, ENG);//onemoguciti ponovne susrete drzava tokom istog prvenstva
	}
	catch (exception& obj)
	{
		cout << obj.what();
	}
	////omoguciti dodavanje pogotka po ID-u ili imenu i prezimenu
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "D000M1", prviPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//onemoguciti dodavanje istih pogodaka
	if (!euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Denis Music", prviPogodak))
		cout << "Pogodak NIJE uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "J000A2", drugiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Jasmin Azemovic", treciPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Goran Skondric", cetvrtiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	////nakon svakog evidentiranog pogotka, svim igracima te utakmice (pod pretpostavkom da su validne email adrese sa ID - ovima igraca),
	////u zasebnom thread-u, poslati email. u razmaku od 2 sekunde, sa sljedecim sadrzajem :
	///*
	//To: D000M1@euro2024.com
	//From: info@euro2024.com
	//Subject: Informacija
	//Postovani,
	//U 20:35:16 sati igrac Jasmin Azemovic je zabiljezio svoj 1
 //  pogodak na ovoj utakmici.
	//Trenutni rezultat je:
	//BOSNA_I_HERCEGOVINA 2 : 0 ENGLESKA
	//Puno srece u nastavku susreta.
	//Neka bolji tim pobijedi.
	//*/
	////ispisuje detaljnije informacije o susretu, kako je navedeno u narednom ispisu
	cout << euro2024;
	///*
	//-------------------------------------------
	//(3) BOSNA_I_HERCEGOVINA : ENGLESKA (1)
	//-------------------------------------------
	//Denis Music Goran Skondric
	//Jasmin Azemovic
	//Jasmin Azemovic
	//-------------------------------------------
	//*/
	////vraca sve igrace koji su na takmicenju postigli broj pogodaka koji je veci ili jednak proslijedjenoj vrijednosti
	vector<Igrac*> igraci = euro2024(2);
	for (size_t i = 0; i < igraci.size(); i++)
		cout << igraci[i]->GetImePrezime() << endl;

	cin.get();
	system("pause>0");
}

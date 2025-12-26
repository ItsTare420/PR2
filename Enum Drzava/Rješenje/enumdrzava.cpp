#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <chrono>
#include <thread>
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
"13.NA KRAJU ISPITA PROVJERITE DA LI STE RJESENJE KOPIRALI U ADEKVATAN FOLDER NA FTP SERVERU\n"
"-------------------------------------------------------------------------------\n";
const char* crt = "\n-------------------------------------------\n";
enum Drzava {
	ENGLESKA, SPANIJA, HOLANDIJA, FRANCUSKA, BOSNA_I_HERCEGOVINA
};

ostream& operator <<(ostream& os, Drzava drzava) {
	switch (drzava) {
	case ENGLESKA:
		cout << "ENGLESKA" ;
		break;
	case SPANIJA:
		cout << "SPANIJA" ;
		break;
	case HOLANDIJA:
		cout << "HOLANDIJA" ;
		break;
	case FRANCUSKA:
		cout << "FRANCUSKA" ;
		break;
	case BOSNA_I_HERCEGOVINA:
		cout << "BOSNA_I_HERCEGOVINA";
		break;
	default:
		cout << "Drzava ne postoji!";
		break;
	}
	return os;
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

cout << GenerisiID("Denis Music", 3) << endl;//treba vratiti D000M3
cout << GenerisiID("Jasmin Azemovic", 14) << endl;//treba vratiti J00A41
cout << GenerisiID("Goran Skondric", 156) << endl;//treba vratiti G0S651
cout << GenerisiID("emina junuz", 1798) << endl;//treba vratiti EJ8971
*/

char* GenerisiID(string imePrezime, int broj) {
	string id;
	id += toupper(imePrezime[0]);
	if (broj < 10)id += "000";
	else if (broj < 100)id += "00";
	else if (broj < 1000)id += "0";
	int prezimeIndeks = imePrezime.find(" ") + 1;
	id += toupper(imePrezime[prezimeIndeks]);
	string obrnutBroj = to_string(broj);
	reverse(obrnutBroj.begin(), obrnutBroj.end());
	id += obrnutBroj;
	return GetNizKaraktera(id.c_str());
}

bool ValidirajID(string ID) {
	return regex_match(ID, regex("[A-Z]000[A-Z][1-9]")) ||
		regex_match(ID, regex("[A-Z]00[A-Z][1-9]{2}")) ||
		regex_match(ID, regex("[A-Z]0[A-Z][1-9]{3}")) ||
		regex_match(ID, regex("[A-Z][A-Z][1-9]{4}"));
}

template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max];
	T2 _elementi2[max];
	int* _trenutno;
public:
	Kolekcija() {
		_trenutno = new int{ 0 };
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
		_trenutno = new int{ *obj._trenutno };
		for (int i = 0; i < obj.getTrenutno(); i++) {
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}
	}
	Kolekcija& operator =(const Kolekcija& obj) {
		if (this != &obj) {

			*_trenutno = *obj._trenutno ;
			for (int i = 0; i < obj.getTrenutno(); i++) {
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
	Kolekcija InsertAt(const T1& el1, const T2& el2, const int& lokacija) {
		Kolekcija novaKolekcija{};
		for (int i = 0; i < lokacija; i++) {
			novaKolekcija.AddElement(getElement1(i), getElement2(i));
		}
		novaKolekcija.AddElement(el1,el2);
		for (int i = lokacija; i <getTrenutno(); i++) {
			novaKolekcija.AddElement(getElement1(i), getElement2(i));
		}
		*this = novaKolekcija;
		return novaKolekcija;
	}
	Kolekcija RemoveRange(const int& start, const int& end) {
		if (start<0 || end>getTrenutno())
			throw exception("Opseg za uklanjanje elemenata nije validan!\n");
		Kolekcija novaKolekcija{};
		Kolekcija staraKolekcija{};
		for (int i = 0; i < getTrenutno(); i++) {
			if (i >= start && i <= end)
				novaKolekcija.AddElement(getElement1(i), getElement2(i));
			else staraKolekcija.AddElement(getElement1(i), getElement2(i));
		}
		*this = staraKolekcija;
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
	Vrijeme& operator =(const Vrijeme& obj) {
		if (this != &obj) {
			delete _sat; _sat = nullptr;
			delete _minuta; _minuta = nullptr;
			delete _sekunda; _sekunda = nullptr;
			_sat = new int(*obj._sat);
			_minuta = new int(*obj._minuta);
			_sekunda = new int(*obj._sekunda);
		}return *this;
	}
	int SatToInt()const {
		return GetSate() * 3600 + GetMinute() * 60 + GetSekunde();
	}
	bool operator ==(const Vrijeme& obj)const {
		return GetSate() == obj.GetSate();
	}
	bool operator !=(const Vrijeme& obj)const {
		return GetSate() != obj.GetSate();
	}
	bool operator <(const Vrijeme& obj)const {
		return GetSate() < obj.GetSate();
	}
	bool operator >(const Vrijeme& obj)const {
		return GetSate() > obj.GetSate();
	}
	bool operator <=(const Vrijeme& obj)const {
		return GetSate() <= obj.GetSate();
	}
	bool operator >=(const Vrijeme& obj)const {
		return GetSate() == obj.GetSate();
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
	Vrijeme GetVrijemePogotka() { return *_vrijemePogotka; }
	char* GetNapomena() { return _napomena; }
	Vrijeme GetVrijemePogotka()const { return *_vrijemePogotka; }
	char* GetNapomena()const { return _napomena; }
	friend ostream& operator<< (ostream& COUT, const Pogodak& obj) {
		COUT << *obj._vrijemePogotka << " -> " << obj._napomena;
		return COUT;
	}
	Pogodak(const Pogodak& obj) {
		_vrijemePogotka = new Vrijeme{ *obj._vrijemePogotka };
		_napomena = GetNizKaraktera(obj._napomena);
	}
	Pogodak& operator =(const Pogodak& obj) {
		if (this != &obj) {
			delete[] _napomena; _napomena = nullptr;
			delete _vrijemePogotka; _vrijemePogotka = nullptr;
			_vrijemePogotka = new Vrijeme{ *obj._vrijemePogotka };
			_napomena = GetNizKaraktera(obj._napomena);
		}return *this;
	}
	bool operator ==(const Pogodak& obj) const {
		return GetVrijemePogotka() == obj.GetVrijemePogotka()
			&& string(GetNapomena()) == obj.GetNapomena();
	}
	bool operator !=(const Pogodak& obj)const {
		return !(*this == obj);
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
		_ID = GenerisiID(_imePrezime, _id++);
	}
	~Igrac() {
		delete[]_ID; _ID = nullptr;
		delete[]_imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _pogoci.size(); i++) {
			delete _pogoci[i];
			_pogoci[i] = nullptr;
		}
	}
	char* GetImePrezime() { return _imePrezime; }
	char* GetID() { return _ID; }
	vector<Pogodak*>& GetPogoci() { return _pogoci; }
	char* GetImePrezime()const { return _imePrezime; }
	char* GetID() const{ return _ID; }
	const vector<Pogodak*>& GetPogoci() const{ return _pogoci; }
	friend ostream& operator<< (ostream& COUT, Igrac& obj) {
		COUT << obj._ID << " -> " << obj._imePrezime;
		for (size_t i = 0; i < obj._pogoci.size(); i++)
			cout << *obj._pogoci[i] << endl;
		return COUT;
	}
	Igrac(const Igrac& obj) {
		_ID = GetNizKaraktera(obj._ID);
		_imePrezime = GetNizKaraktera(obj._imePrezime);
		for (size_t i = 0; i < obj._pogoci.size(); i++) {
			_pogoci.push_back(new Pogodak(*obj._pogoci[i]));
		}
	}
	bool operator ==(const Igrac& obj)const{
		return strcmp(GetID(), obj.GetID()) == 0;
	}

	bool operator !=(const Igrac& obj)const {
		return !(*this == obj);
	}
	bool daLiJePogodakDodan(const Pogodak& pogodak)const {
		for (const auto& pogodakk : GetPogoci()) {
			if (pogodak == *pogodakk) return true;
		}
		return false;
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
	~Reprezentacija(){}

	Drzava GetDrzava() { return _drzava; }
	vector<Igrac>& GetIgraci() { return _igraci; }
	Drzava GetDrzava() const{ return _drzava; }
	const vector<Igrac>& GetIgraci()const { return _igraci; }

	Reprezentacija(const Reprezentacija& obj) {
		_drzava = obj._drzava;
		_igraci = obj._igraci;
	}
	Reprezentacija& operator =(const Reprezentacija& obj) {
		if (this != &obj) {
			_drzava = obj._drzava;
			_igraci = obj._igraci;
		}return *this;
	}
	bool operator ==(const Reprezentacija& obj)const {
		return GetDrzava() == obj.GetDrzava() &&
			GetIgraci() == obj.GetIgraci();
	}
	bool operator !=(const Reprezentacija& obj)const {
		return !(*this == obj);
	}
	bool daLiJeIgracVecDodan(const Igrac& igracZaPretragu) const{
		for (const Igrac& igrac : GetIgraci()) {
			if (igrac == igracZaPretragu)return true;
		}
		return false;
	}

	void AddIgrac(const Igrac& igrac) {
		if (daLiJeIgracVecDodan(igrac))
			throw exception("Dodavanje duplih igraca nije moguce!\n");
		_igraci.push_back(igrac);
	}
	Igrac* findIgrac(const string& identifikator){
		for (auto& igrac : GetIgraci()) {
			if ((strcmp(igrac.GetID(), identifikator.c_str()) == 0)
				|| (strcmp(igrac.GetImePrezime(), identifikator.c_str()) == 0))
				return &igrac;
		}
		return nullptr;
	}
};
class Prventstvo {
	Kolekcija<Reprezentacija*, Reprezentacija*, 20> _utakmice;
public:
	Kolekcija<Reprezentacija*, Reprezentacija*, 20>& GetUtakmice() {
		return _utakmice;
	}
	const Kolekcija<Reprezentacija*, Reprezentacija*, 20>& GetUtakmice()const {
		return _utakmice;
	}
	bool jeLiSusretVecDodan(const Reprezentacija& rep1, const Reprezentacija& rep2) {
		for (int i = 0; i < GetUtakmice().getTrenutno(); i++) {
			if ((*_utakmice.getElement1(i)==rep1 && *_utakmice.getElement2(i) == rep2)
				||((*_utakmice.getElement2(i) == rep1 && *_utakmice.getElement1(i) == rep2)))
				return true;
		}
		return false;
	}
	void AddUtakmicu(const Reprezentacija& rep1, const Reprezentacija& rep2) {
		if (jeLiSusretVecDodan(rep1, rep2))
			throw exception("Dodavanje istih susreta nije moguce!\n");
		_utakmice.AddElement(new Reprezentacija{ rep1 }, new Reprezentacija{ rep2 });
	}
	void SaljiEmail(Reprezentacija* rep1, Reprezentacija* rep2, Igrac* strijelac, int redniBroj, Pogodak pogodak) {
		int goloviDomacina = 0;
		for (auto& igrac : rep1->GetIgraci()) {
			goloviDomacina += igrac.GetPogoci().size();
		}
		int goloviGosta = 0;
		for (auto& igracc : rep2->GetIgraci()) {
			goloviGosta += igracc.GetPogoci().size();
		}

		vector<Igrac>sviIgraci = rep1->GetIgraci();
		vector<Igrac> igraciGosta = rep2->GetIgraci();
		sviIgraci.insert(sviIgraci.end(), igraciGosta.begin(), igraciGosta.end());

		for (const auto& primalac : sviIgraci) {
			this_thread::sleep_for(chrono::seconds(2));
			cout << "\nTo: " << primalac.GetID() << "@euro2024.com" << endl;
			cout << "From: info@euro2024.com"<<endl;
			cout << "Subject: Informacija" << endl;
			cout << "Postovani," << endl;
			cout << "U " << pogodak.GetVrijemePogotka() << " sati igrac " << strijelac->GetImePrezime() <<
				" je zabiljezio svoj " << redniBroj << "." << endl;
			cout << "pogodak na ovoj utakmici." << endl;
			cout << "Trenutni rezultat je:" << endl;
			cout << rep1->GetDrzava() << " " << goloviDomacina << " : " << goloviGosta 
				<< " " << rep2->GetDrzava() << endl;
			cout << "Puno srece u nastavku ovog susreta" << endl;
			cout << "Neka bolji tim pobijedi\n" << endl;
		}
	}


	bool AddPogodak(const Drzava& drzava1, const Drzava& drzava2,
		const string& identifikator, const Pogodak& pogodak) {
		Reprezentacija* domacaRepka = nullptr;
		Reprezentacija* gostujucaRepka = nullptr;

		for (int i = 0; i < GetUtakmice().getTrenutno(); i++) {
			Reprezentacija* r1 = GetUtakmice().getElement1(i);
			Reprezentacija* r2 = GetUtakmice().getElement2(i);

			if (r1->GetDrzava() == drzava1 && r2->GetDrzava() == drzava2) {
				domacaRepka = r1; gostujucaRepka = r2;
				break;
			}
				
			else if ((r2->GetDrzava() == drzava1 && r1->GetDrzava() == drzava2)) {
				domacaRepka = r2; gostujucaRepka = r1;
				break;
			}
		}
		if (domacaRepka == nullptr)return false;

		Igrac* strijelac = domacaRepka->findIgrac(identifikator);
		if (strijelac == nullptr) {
			strijelac = gostujucaRepka->findIgrac(identifikator);
		}
		if (strijelac == nullptr) return false;

		if (strijelac->daLiJePogodakDodan(pogodak))return false;

		strijelac->GetPogoci().push_back(new Pogodak{ pogodak });
		int redniBroj = strijelac->GetPogoci().size();

		thread t(&Prventstvo::SaljiEmail, this, domacaRepka, gostujucaRepka, strijelac, redniBroj, pogodak);
		t.join();
		return true;
	}
	friend ostream& operator <<(ostream& os,const Prventstvo& obj) {
		for (int i = 0; i < obj.GetUtakmice().getTrenutno(); i++) {
			Reprezentacija* r1 = obj.GetUtakmice().getElement1(i);
			Reprezentacija* r2 = obj.GetUtakmice().getElement2(i);
			vector<string> domaciStrijelci;
			for (const auto& igrac : r1->GetIgraci()) {
				for (size_t j = 0; j < igrac.GetPogoci().size(); j++) {
					domaciStrijelci.push_back(igrac.GetImePrezime());
				}
				
			}
			vector<string> gostujuciStrijelci;
			for (const auto& igracc : r2->GetIgraci()) {
				for (size_t j = 0; j < igracc.GetPogoci().size(); j++){
					gostujuciStrijelci.push_back(igracc.GetImePrezime());
				}
				
			}

			os << "-------------------------------------------" << endl;
			os << "(" << domaciStrijelci.size() << ") " << r1->GetDrzava() << " : " << r2->GetDrzava()
				<< " (" << gostujuciStrijelci.size() << ")" << endl;
			os << "-------------------------------------------" << endl;

			int maxRedova = 0;
			if (domaciStrijelci.size() > gostujuciStrijelci.size()) {
				maxRedova = domaciStrijelci.size();
			}
				
			else {
				maxRedova = gostujuciStrijelci.size();
			} 

			for (int k = 0; k < maxRedova; k++) {
				if (k < domaciStrijelci.size()) {
					os << domaciStrijelci[k] << " ";
				}
					
				else {
					os << "                        " << endl;
				} 
				if (k< gostujuciStrijelci.size()) {
					os << gostujuciStrijelci[k] << " ";
				}
					
				os << endl;
			}
			os << "-------------------------------------------" << endl;
		}
		
		return os;
	}
	vector<Igrac*> operator ()(int brojPogodaka) {
		vector<Igrac*> strijelci;
		for (int i = 0; i < GetUtakmice().getTrenutno(); i++) {
			Reprezentacija* r1 = GetUtakmice().getElement1(i);
			Reprezentacija* r2 = GetUtakmice().getElement2(i);

			for ( auto& igrac : r1->GetIgraci()) {
				if (igrac.GetPogoci().size() >= brojPogodaka) {
					strijelci.push_back(&igrac );
				}
			}
			for (auto& igracc : r2->GetIgraci()) {
				if (igracc.GetPogoci().size() >= brojPogodaka) {
					strijelci.push_back(&igracc );
				}
			}
		}
		return strijelci;
	}
};

const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Objasnite tipove nasljedivanja \n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Objasnite lambda funkcije? \n";
	return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {
	cout << PORUKA;
	cin.get();
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();
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
	//omoguciti dodavanje pogotka po ID-u ili imenu i prezimenu
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

#include <iostream>
#include <string>

using namespace std;

class Osoba {
    private:
        string meno;
        string adresa;
    public:
        Osoba();
        Osoba(string meno, string adresa);
        string getMeno();
        string getAddress();
};
Osoba::Osoba() {}
Osoba::Osoba(string meno, string adresa) {
    this->meno = meno;
    this->adresa = adresa;
}

string Osoba::getMeno() {
    return this->meno;
}

string Osoba::getAddress() {
    return this->adresa;
}

class PolozkaFaktury {              // deklarace Polozky
    private: 
        string nazev;
        int pocet;
        double cena;
    public:
        PolozkaFaktury(string nazev, int pocet, double cena);
        ~PolozkaFaktury();
        // PolozkaFaktury();
        double getCenaTotal();
};

double PolozkaFaktury::getCenaTotal() {
    return this->cena * this->pocet;
}
PolozkaFaktury::PolozkaFaktury(string nazev, int pocet, double cena) {          // Konstruktor
    this->nazev = nazev;
    this->pocet = pocet;
    this->cena = cena;
}
// PolozkaFaktury::PolozkaFaktury() {}
PolozkaFaktury::~PolozkaFaktury() {}

class Faktura {
    private:
        int cislo;
        Osoba osoba;
        PolozkaFaktury **polozky;
        int pocetPolozek;
    public:
        Faktura(int cislo, Osoba osoba, PolozkaFaktury **polozky);
        ~Faktura();
        double spocitajCenu();
        PolozkaFaktury* PridajPolozku(string nazev, int pocet, double cena);
        string getMeno();
        string getAddress();
};
double Faktura::spocitajCenu() {
    double suma = 0;
    for (size_t p = 0; p < pocetPolozek; p++) {
        suma += this->polozky[p]->getCenaTotal();
    }
    return suma;
}

Faktura::Faktura(int cislo, Osoba osoba, PolozkaFaktury **polozky ) {
    this->cislo = cislo;
    this->osoba = osoba;
    this->polozky = polozky;
    this->pocetPolozek = 0;

}
Faktura::~Faktura() {
    for (int i = 0; i < pocetPolozek; i++) delete polozky[i];
    delete[] polozky;

}

PolozkaFaktury* Faktura::PridajPolozku(string nazev, int pocet, double cena) {
    PolozkaFaktury *newObject = new PolozkaFaktury(nazev, pocet, cena);
    this -> polozky[this->pocetPolozek]=newObject;
    this -> pocetPolozek += 1;
    return newObject;
}
string Faktura::getMeno() {
    return osoba.getMeno();
}
string Faktura::getAddress() {
    return osoba.getAddress();
}

int main() {
    Osoba osoba("Tomas", "Roznov");
    PolozkaFaktury **polozky = new PolozkaFaktury*[5];
    // polozky[0] = new PolozkaFaktury("vruty", 20, 3);
    // polozky[1] = new PolozkaFaktury("hmozdinky", 54, 2);
    // polozky[2] = new PolozkaFaktury("matky", 100, 0.5);

    Faktura *bill = new Faktura(1, osoba, polozky);
    
    bill -> PridajPolozku("cement", 8, 12);
    cout << bill->spocitajCenu() << endl;

    bill -> PridajPolozku("vruty", 20, 3);
    cout << bill->spocitajCenu() << endl;

    bill -> PridajPolozku("hmozdinky", 54, 2);
    cout << bill->spocitajCenu() << endl;

    bill -> PridajPolozku("matky", 100, 0.5);
    cout << bill->spocitajCenu() << endl;
    
    cout << bill->getMeno() << endl;
    cout << bill->getAddress() << endl;

    delete bill;

    return 0;
}
#include <iostream>
#include <string>

using namespace std;


class PolozkaObjednavky {
    private:
        string produkt;
        double cena;
    public:
        PolozkaObjednavky(string produkt, double cena);
        string GetProduct();
};

class Objednavka {
    private:
        int cislo;
        string datum;
        PolozkaObjednavky **polozky;
        int pocetPolozek;
    public:
    Objednavka(int cislo, string datum, int n);
    ~Objednavka();
    PolozkaObjednavky* PridajPolozku(string produkt, double cena);
    int getCislo();
    string getDatum();
    int getPocetPolozek();
    PolozkaObjednavky* SearchObject(string p);

};
int Objednavka::getPocetPolozek() {
    return this->pocetPolozek;
}
string PolozkaObjednavky::GetProduct() {
    return this->produkt;
}

PolozkaObjednavky* Objednavka::SearchObject(string p) {
    for (int i =0 ; i < this->pocetPolozek; i++) {
        if (this->polozky[i]->GetProduct() == p) {
            return this->polozky[i];
        }
    }
    return nullptr;
}

Objednavka::Objednavka(int cislo, string datum, int n) {
    this->polozky = new PolozkaObjednavky*[n];
    this->cislo = cislo;
    this->datum = datum;
    this->pocetPolozek = 0;
}

Objednavka::~Objednavka() {
    for (int i = 0; i < this->pocetPolozek; i++) {
        delete this->polozky[i];
    }
    delete[] this->polozky;
}
PolozkaObjednavky* Objednavka::PridajPolozku(string produkt, double cena) {
    PolozkaObjednavky *newObject = new PolozkaObjednavky(produkt, cena);
    this -> polozky[this->pocetPolozek]=newObject;
    this -> pocetPolozek += 1;
    return newObject;
}
int Objednavka::getCislo() {
    return this->cislo;
}
string Objednavka::getDatum() {
    return this->datum;
}

PolozkaObjednavky::PolozkaObjednavky(string produkt, double cena) {
    this->produkt = produkt;
    this->cena = cena;
}

int main() {
    int N = 5;
    Objednavka *objednavka = new Objednavka(1, "2024-06-01", N);
    objednavka->PridajPolozku("vruty", 3);
    objednavka->PridajPolozku("hmozdinky", 2);

    cout << "Objednavka cislo: " << objednavka->getCislo() << endl;
    cout << "Datum objednavky: " << objednavka->getDatum() << endl;
    cout << "Pocet polozek: " << objednavka->getPocetPolozek() << endl; 
    
    PolozkaObjednavky* polozka = objednavka->SearchObject("vruty");
    if (polozka != nullptr) {
        cout << "Nalezena polozka: " << polozka->GetProduct() << endl;
    }

    delete objednavka;

    return 0;
}
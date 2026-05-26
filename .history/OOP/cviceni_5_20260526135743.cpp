#include <iostream>
#include <string>
using namespace std;

// Base class
class Auto {
protected:
    string znacka;
    int rok;
    double hmotnost; // kg

public:
    Auto(string z, int r, double h) : znacka(z), rok(r), hmotnost(h) {}
    virtual ~Auto() = default;

    virtual string typ() const { return "Auto"; }

    // spoločné správanie
    virtual double spotreba() const {             
        return 5.0 + 0.0015 * hmotnost;
    }

    virtual void info() const {                    // stručný výpis
        cout << typ() << ": " << znacka << " (" << rok << "), "
             << "hmotnost=" << hmotnost << "kg, "
             << "spotreba=" << spotreba() << " l/100\n";
    }
};

// Derived: Osobní auto (rozšírenie stavu + zmena správania)
class OsobniAuto : public Auto {
    int sedadla;

public:
    OsobniAuto(string z, int r, double h, int s)
        : Auto(z, r, h), sedadla(s) {}

    string typ() const override { return "OsobniAuto"; }

    double spotreba() const override {    // Odvíja sa od poctu sedadiel
        return Auto::spotreba() + 0.15 * (sedadla - 2);
    }

    void info() const override {
        Auto::info();
        cout << "  sedadla=" << sedadla << "\n";
    }
};

// Derived: Nákladní auto (rozšírenie stavu + zmena správania)
class NakladniAuto : public Auto {
    double nosnost; // kg

public:
    NakladniAuto(string z, int r, double h, double n)
        : Auto(z, r, h), nosnost(n) {}

    string typ() const override { return "NakladniAuto"; }

    double spotreba() const override {             // vyššia podľa nosnosti
        return Auto::spotreba() + 3.0 + 0.001 * nosnost;
    }

    void info() const override {
        Auto::info();
        cout << "  nosnost=" << nosnost << "kg\n";
    }
};

int main() {
    // Polymorfizmus: pole ukazovateľov na predka (zastupiteľnosť)
    Auto* garaz[2];
    garaz[0] = new OsobniAuto("Skoda Octavia", 2020, 1350, 5);
    garaz[1] = new NakladniAuto("MAN TGX", 2019, 8000, 18000);

    for (int i = 0; i < 2; i++)
        garaz[i]->info(); // volá správnu override verziu

    for (int i = 0; i < 2; i++)
        delete garaz[i];

    return 0;
}
#include <iostream>
#include <string>
using namespace std;

class Email {                                // Deklarácia triedy
    private:
        string address;
    public:
        Email(string address);
        string getAddress();
};

Email::Email(string address) {           // Definicia (implementácia) triedy
    this->address = address;
}

string Email::getAddress() {
    return this->address;
}

class Osoba {
    private:
        string meno;
        string priezvisko;
    public:
        Osoba(string meno, string priezvisko);
        string getMeno();
        string getPriezvisko();
};
Osoba::Osoba(string meno, string priezvisko) {
    this->meno = meno;
    this->priezvisko = priezvisko;
}

string Osoba::getMeno() {
    return this->meno;
}

string Osoba::getPriezvisko() {
    return this->priezvisko;
}

class Document {
    private:
        string title;
    public:
        Document(string title);
        string getTitle();
};
Document::Document(string title) {
    this->title = title;
}
string Document::getTitle() {
    return this->title;
}

int main() {                                    // Použitie triedy
    
    Email *e2 = new Email("tomas.porubsky@gmail.com");
    cout << "Address: " << e2->getAddress() << endl;
    delete e2;

    Osoba *o1 = new Osoba("Tomas", "Porubsky");
    cout << "Name: " << o1->getMeno() << " " << o1->getPriezvisko() << endl;
    delete o1;

    Document *d1 = new Document("C++ beningings");
    cout<< "Title: " << d1->getTitle() << endl;
    delete d1;

    getchar();                                  // Čakanie na stlačenie klávesy pred ukončením programu
    return 0;
}
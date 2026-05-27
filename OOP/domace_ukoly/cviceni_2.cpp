#include <iostream>
#include <string>

using namespace std;

class KeyValue {                                // Deklarácia triedy
    private:
        int key;
        double value;
    public:
        KeyValue(int k, double v);
        int getKey();
        double getValue();

};

KeyValue::KeyValue(int k, double v) {
    this->key = k;
    this->value = v;
}

int KeyValue::getKey() {
    return this->key;
}

double KeyValue::getValue() {
    return this->value;
}


class Osoba {
    private:
        string meno;
        string priezvisko;
    public:
        Osoba(string meno, string priezvisko);
        string getMeno();
        string getAddress();
};
Osoba::Osoba(string meno, string priezvisko) {
    this->meno = meno;
    this->priezvisko = priezvisko;
}

string Osoba::getMeno() {
    return this->meno;
}

string Osoba::getAddress() {
    return this->priezvisko;
}

class KeyValues {
    private:
        KeyValue** keyValues;
        int count;
    public:
        KeyValues(int n);
        ~KeyValues();
        KeyValue* CreateObject(int k, double v);
        KeyValue* SearchObject(int key);
        KeyValue* RemoveObject(int key);
        int Count();
};

KeyValues::KeyValues(int n) {
    this -> keyValues = new KeyValue*[n];
    this->count=0;
}
KeyValues::~KeyValues() {
    for (int i = 0; i < this->count; i++) {
        delete this->keyValues[i];
    }
    delete[] this->keyValues;
}
KeyValue* KeyValues::CreateObject(int k, double v) {
    KeyValue *newObject = new KeyValue(k,v);
    this -> keyValues[this->count]=newObject;
    this -> count += 1;
    return newObject;
}
KeyValue* KeyValues::SearchObject(int k) {
    for (int i = 0; i < this ->count; i++) {
        if (this->keyValues[i]->getKey()==k) {
            return this->keyValues[i];
        }
    }
    return nullptr;
}
int KeyValues::Count() {
    return this->count;
}

KeyValue* KeyValues::RemoveObject(int key) {
    delete keyValues[key];
    return this->keyValues[key];
}

int main() {
    int N = 5;
    KeyValues* myKeyValues = new KeyValues(N);
    KeyValue* myKeyValue = myKeyValues->CreateObject(0,0.5);
    cout << myKeyValue->getValue() <<endl;

    for (int i = 1; i <N; i++) {
        myKeyValues ->CreateObject(i, i+0.5);
    }
    cout << myKeyValues->SearchObject(2)->getValue() << endl;
    myKeyValues->RemoveObject(2);
    cout << myKeyValues->SearchObject(2)->getValue() << endl;
    return 0;
}
#include <iostream>
#include <string>

using namespace std;

class KeyValue {                                // Deklarácia triedy
    private:
        int key;
        double value;
        KeyValue *next;                         // Ukazovateľ na ďalší objekt (pre prípad spojového zoznamu)
    public:
        KeyValue(int k, double v);
        int getKey();
        double getValue();
        KeyValue *getNext();                        // Getter pre ukazovateľ na ďalší objekt
        KeyValue *CreateNext( int k, double v);     // Pointer na funkciu, ktorá vytvorí nový objekt a nastaví ho ako ďalší
        ~KeyValue();
};

KeyValue::KeyValue(int k, double v) {           // Definicia (implementácia) triedy
    this->key = k;
    this->value = v;
    this->next = nullptr;                        // Inicializácia ukazovateľa na ďalší objekt na nullptr   
}

int KeyValue::getKey() {
    return this->key;
}

double KeyValue::getValue() {
    return this->value;
}

KeyValue *KeyValue::getNext() {
    return this->next;
}
KeyValue *KeyValue::CreateNext(int k, double v) {
    this->next = new KeyValue(k, v);             // Vytvorenie nového objektu a nastavenie ukazovateľa na něj
    return this->next;                          // Vrátí ukazovateľ na nový objekt
}

KeyValue::~KeyValue() {                                  // Destruktor pro uvolnění paměti
    if (this->next != nullptr) {
        delete this->next;
        this->next = nullptr;                        // Nastavení ukazovatele na další objekt na nullptr po uvolnění paměti
    }
}

int main() {
    KeyValue *head = new KeyValue(1, 1.5);
    KeyValue *current = head;

    // vytvoříme třeba 1000 prvků
    for (int i = 2; i <= 1000; i++) {
        current = current->CreateNext(i, i * 1.1);
    }

    // projdeme a vypíšeme všechny klíče
    current = head;
    while (current != nullptr) {
        cout << current->getKey() << endl;
        current = current->getNext();
    }

    // smažeme celý seznam (rekurzivně přes destruktor)
    delete head;

    return 0;
}


    // KeyValue kv1(1, 3.14);
    // cout << "Key: " << kv1.getKey() << ", Value: " << kv1.getValue() << endl;
    
    // KeyValue *kv2 = new KeyValue(2, 2.718);
    // cout << "Key: " << kv2->getKey() << ", Value: " << kv2->getValue() << endl;
    // delete kv2;

    // getchar();                                  // Čakanie na stlačenie klávesy pred ukončením programu
    // return 0;
// }
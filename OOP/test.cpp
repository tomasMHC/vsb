#include <iostream>
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

KeyValue::KeyValue(int k, double v) {           // Definicia (implementácia) triedy
    this->key = k;
    this->value = v;
}

int KeyValue::getKey() {
    return this->key;
}

double KeyValue::getValue() {
    return this->value;
}

int main() {                                    // Použitie triedy
    KeyValue kv1(1, 3.14);
    cout << "Key: " << kv1.getKey() << ", Value: " << kv1.getValue() << endl;
    
    KeyValue *kv2 = new KeyValue(2, 2.718);
    cout << "Key: " << kv2->getKey() << ", Value: " << kv2->getValue() << endl;
    delete kv2;

    getchar();                                  // Čakanie na stlačenie klávesy pred ukončením programu
    return 0;
}
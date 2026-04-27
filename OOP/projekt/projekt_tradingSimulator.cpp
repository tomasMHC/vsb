#include <iostream>
#include <string>
// #include "projekt_tradingSimulator.h"
using namespace std;

class Instrument {
    protected:
        string name;
        string symbol;
        double price;

    public:
        virtual ~Instrument() = default;  
        string getName();
        double getPrice();
        string getSymbol();

        virtual string getType() const = 0;                       
        virtual void updatePrice(double p) = 0;                 // abstraktne metody - musia být implementované v dědičných třídách
        virtual double calculateFee() const = 0;                  // pretizena metoda
};
string Instrument::getSymbol() {
    return this->symbol;
}
string Instrument::getName() {
    return this->name;
}
double Instrument::getPrice() {
    return this->price;
}


class Stock : public Instrument {
    private:
        double dividend;
    public:
        Stock(string n, double p, double d);
        double getDividend();
        void updatePrice(double p);
        double calculateFee() const;
        string getType() const;
};
Stock::Stock(string n, double p, double d) {
    this->name = n;
    this->price = p;
    this->dividend = d;
}
double Stock::getDividend() {
    return this->dividend;
}
double Stock::calculateFee() const {
    return this->price * 0.001;
}
string Stock::getType() const {
    return "Stock";
}
void Stock::updatePrice(double p) {
    this->price = p;
}

class Option: public Instrument {
    protected:
        double strikePrice;
        double underlyingPrice;
        int daysToExp;
        double premium;

    public:
        Option(string n, double p);
        double getStrikePrice();
        string getExpirationDate();
        double calculateFee() const;
        Stock* getUnderlying();
        virtual string getType() const = 0;
        virtual void updatePrice(double p) = 0;

};
Option::Option(string n, double p) {
    this->name = n;
    this->price = p;
}
double Option::getStrikePrice() {
    return this->strikePrice;
}
double Option::calculateFee() const {
    return this->price * 0.01;
}


class OptionCall: public Option {
    public:
        OptionCall(string n, double p, string expDate, double strikePrice);
        double intrinsicValue();
        void updatePrice(double p);
        string getType() const;

};
OptionCall::OptionCall(string n, double p, string expDate, double strikePrice) : Option(n, p) {
    this->strikePrice = strikePrice;
    this->daysToExp = 30;                   
    this->premium = 0.05 * p; 
}
class OptionPut: public Option {
    public:
        OptionPut(string n, double p, string expDate, double strikePrice);
        double intrinsicValue();
        void updatePrice(double p);
        string getType() const;
};
OptionPut::OptionPut(string n, double p, string expDate, double strikePrice) : Option(n, p) {
    this->strikePrice = strikePrice;
    this->daysToExp = 30;                   
    this->premium = 0.05 * p; 
}
double OptionCall::intrinsicValue() {
    return max(0.0, this->underlyingPrice - this->strikePrice);
}
double OptionPut::intrinsicValue() {
    return max(0.0, this->strikePrice - this->underlyingPrice);
}
string OptionCall::getType() const {
    return "OptionCall";
}
string OptionPut::getType() const {
    return "OptionPut";
}
void OptionCall::updatePrice(double p) {
    this->price = p;
}
void OptionPut::updatePrice(double p) {
    this->price = p;
}

class Order {
    private:
        Instrument* instrument;
        double quantity;
        double price;

    public:
        Order(Instrument* i, double q, double p);
        Instrument* getInstrument() const;
        double getQuantity() const;
        double getPrice() const;
        virtual string getType() const = 0;
};

Order::Order(Instrument* i, double q, double p) {
    this->instrument = i;
    this->quantity = q;
    this->price = p;
}

Instrument* Order::getInstrument() const {
    return this->instrument;
}
double Order::getQuantity() const {
    return this->quantity;
}
double Order::getPrice() const {
    return this->price;
}

class Sell: public Order {
    public:
        Sell(Instrument* i, double q, double p);
        string getType() const;

};

class Buy: public Order {
    public:
        Buy(Instrument* i, double q, double p);
        string getType() const;
};

Sell::Sell(Instrument* i, double q, double p) : Order(i, q, p) {}
Buy::Buy(Instrument* i, double q, double p) : Order(i, q, p) {}

string Sell::getType() const {
    return "Sell";
}
string Buy::getType() const {
    return "Buy";
}
class Market;

class Client {             
    private:
        int code;
        string name;
        Market** markets;
        int marketsCount;
    public:
        Client(int c, string n);
        int getCode();
        string getName();
        void addMarket(Market* m);
};
Client::Client(int c, string n) {          
    this->code = c;
    this->name = n;
    this->markets = new Market*[10];  // Assuming a maximum of 10 markets
    this->marketsCount = 0;
}
int Client::getCode() {
    return this->code;
}
string Client::getName() {
    return this->name;
}
void Client::addMarket(Market* m) {
    if (marketsCount < 10) {
        this->markets[this->marketsCount] = m;
        this->marketsCount += 1;
    }
}


class Position {
    private: 
        Instrument* instrument;
        double quantity;
    public:
        Position(Instrument* i, double q);
        Instrument* getInstrument();
        double getQuantity();
};

class Portfolio {
    private:
        Client* owner;
        Order** orders;
        int ordersCount;
        Position** positions;
        int positionsCount;
        double totalValue;
        double cash;
    public:
        Portfolio(Client* o, string );
        ~Portfolio();
        Client* getOwner();
        int getOrdersCount();
        int getPositionsCount();
        void addPosition(Position* p);
        Instrument* searchObject();
};  

class Market {
    private:
        string name;
        Instrument** instruments;
        int instrumentCount;
        Client** traders;
        int tradersCount;
    public:
        Market(string n, int i, int t);
        ~Market();

        string getName();
        Instrument** getInstruments();
        int getInstrumentsCount();
        Client** getTraders();
        int getTradersCount();
        Order* addSell(Sell* o, Market* m, Client* c);
        Order* addBuy(Buy* o, Market* m, Client* c);

        Instrument* addInstrument(string type, string n, double p, string expDate, double strikePrice);
        Instrument* addInstrument(string type, string n, double p, double d);
        Instrument* addInstrument(string type, string n, double p);
        Client* addTrader(string t);
        void printTraders();
        void printInstruments();
};


Market::Market(string n, int i, int t) {
    this->name = n;
    this->instruments = new Instrument*[i];
    this->instrumentCount = 0;
    this->traders = new Client*[t];
    this->tradersCount = 0;
}

Market::~Market() {
    for (int i = 0; i < instrumentCount; i++) delete instruments[i];
    delete[] instruments;

    for (int i = 0; i < tradersCount; i++) delete traders[i];
    delete[] traders;
}
string Market::getName() {
    return this->name;
}
Instrument** Market::getInstruments() {
    return this->instruments;
}
int Market::getInstrumentsCount() {
    return this->instrumentCount;
}

Instrument* Market::addInstrument(string type, string n, double p) {
    if (type == "Stock") {
        Stock *newObject = new Stock(n, p, 0);
        this->instruments[this->instrumentCount] = newObject;
        this->instrumentCount += 1;
        return newObject;
    }
    return nullptr;
}

Instrument* Market::addInstrument(string type, string n, double p, double d) {
    if (type == "Stock") {
        Stock *newObject = new Stock(n, p, d);
        this->instruments[this->instrumentCount] = newObject;
        this->instrumentCount += 1;
        return newObject;
    }
    return nullptr;
}

Instrument* Market::addInstrument(string type,string n, double p, string expDate, double strikePrice) {
    if (type == "OptionCall") {
        OptionCall *newObject = new OptionCall(n, p, expDate, strikePrice);
        this->instruments[this->instrumentCount] = newObject;
        this->instrumentCount += 1;
        return newObject;
    } else if (type == "OptionPut") {
        OptionPut *newObject = new OptionPut(n, p, expDate, strikePrice); 
        this->instruments[this->instrumentCount] = newObject;
        this->instrumentCount += 1;
        return newObject;
    }
    return nullptr;
}
Client* Market::addTrader(string t) {
    Client *newObject = new Client(tradersCount, t);
    this->traders[this->tradersCount] = newObject;
    this->tradersCount += 1;
    newObject->addMarket(this);
    return newObject;
}
Client** Market::getTraders() {
    return this->traders;
}
int Market::getTradersCount() {
    return this->tradersCount;
}
Order* Market::addSell(Sell* o, Market* m, Client* c) {
    // Implement order processing logic here
    cout << "Processing Sell order on market " << m->getName() << ": " << o->getQuantity() << " of " << o->getInstrument()->getName() << " at price " << o->getPrice() << endl;
    return o;
}
Order* Market::addBuy(Buy* o, Market* m, Client* c) {
    // Implement order processing logic here

    cout << "Processing Buy order on market " << m->getName() << ": " << o->getQuantity() << " of " << o->getInstrument()->getName() << " at price " << o->getPrice() << endl;
    return o;
}
void Market::printTraders() {
    cout << "Traders in " << this->name << ":" << endl;
    for (int i = 0; i < this->tradersCount; i++) {
        cout << " - " << this->traders[i]->getName() << endl;
    }
}
void Market::printInstruments() {
    cout << "Instruments in " << this->name << ":" << endl;
    for (int i = 0; i < this->instrumentCount; i++) {
        cout << " - " << this->instruments[i]->getType() << ": " << this->instruments[i]->getName() << " (" << this->instruments[i]->getPrice() << ")" << endl;
    }
}

int main() {
    Market* market1 = new Market("NASDAQ", 10, 10);
        market1->addInstrument("Stock", "AAPL", 150.0, 0.5);
        market1->addInstrument("OptionCall", "AAPL Call", 5.0, "2024-12-31", 160.0);
        market1->addTrader("Tomas");
        market1->addTrader("Betka");

    Market* market2 = new Market("BCPPX Praha", 10, 10);
        market2->addInstrument("Stock", "ČEZ", 100.0, 0.3);
        market2->addInstrument("OptionPut", "ČEZ Put", 3.0, "2024-12-31", 90.0);
        market2->addTrader("Jirka");
        market2->addTrader("Petr");
        
        cout << "Market: " << market1->getName() << endl;
        market1->printInstruments();
        market1->printTraders();

        cout << "Market2: " << market2->getName() << endl;
        market2->printTraders();
        market2->printInstruments();

        market1->addSell(new Sell(market1->getInstruments()[0], 10, 150.0), market1, market1->getTraders()[0]);
        market1->addBuy(new Buy(market1->getInstruments()[0], 5, 150.0), market1, market1->getTraders()[1]);


    market1->getInstruments()[0]->updatePrice(155.0);
    cout << "Updated price of AAPL: " << market1->getInstruments()[0]->getPrice() << endl;
    return 0;
}
#include <iostream>
#include <string>

using namespace std;

class Instrument {
    protected:
        string name;
        string symbol;
        double price;
    public:
        string getName();
        double getPrice();
        string getSymbol();
                                                                  // abstraktne metody - musia být implementované v dědičných třídách
        virtual void updatePrice(double p) = 0;
        virtual void createInstrument(string s, double p) = 0;
        virtual Instrument* searchObject() = 0;
        virtual string getType() const = 0;                       // polymorfne rozlisenie tpyu 
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
    public:
        Stock(string n, double p);
        double getDividend();
};
Stock::Stock(string n, double p) {
    this->name = n;
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
};

class OptionCall: public Option {
    public:
        OptionCall(string n, double p, string expDate);

        double intrinsicValue();
        string getType();
};
class OptionPut: public Option {
    public:
        OptionPut(string n, double p, string expDate);
        double intrinsicValue();
        string getType();
};

class Order {
    private:
        string type;
        Instrument* instrument;
        double quantity;
        double price;

    public:
        Order(string t, Instrument* i, double q, double p);
        string getType();
        Instrument* getInstrument();
        double getQuantity();
        double getPrice();
};
class Sell: public Order {
    public:
        Sell(Instrument* i, double q, double p);
};
class Buy: public Order {
    public:
        Buy(Instrument* i, double q, double p);
};

class Client {             
    private:
        int code;
        string name;
    public:
        Client(int c, string n);
        int getCode();
        string getName();
};
Client::Client(int c, string n) {          
    this->code = c;
    this->name = n;
}
int Client::getCode() {
    return this->code;
}
string Client::getName() {
    return this->name;
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
        void addOrder(Order* o);
        int getPositionsCount();
        void addPosition(Position* p);
};  

class Market {
    private:
        string name;
        Stock** stocks;
        Option** options;
        int stocksCount;
        int optionsCount;
        Client** traders;
        int tradersCount;
    public:
        Market(string n, int s, int t);
        ~Market();

        string getName();
        string* getStocks();
        int getStocksCount();
        string* getTraders();
        int getTradersCount();

        Instrument* addInstrument(string type, string n, double p, string expDate, double strikePrice);
        Instrument* addInstrument(string type, string n, double p);

        void addTrader(string t);
};


Market::Market(string n, int s, int t) {
    this->name = n;
    this->stocks = new Stock*[s];
    this->stocksCount = 0;
    this->options = new Option*[s];
    this->optionsCount = 0;

    this->traders = new Client*[t];
    this->tradersCount = 0;
}

Market::~Market() {
    for (int i = 0; i < stocksCount; i++) delete stocks[i];
    delete[] stocks;

    for (int i = 0; i < optionsCount; i++) delete options[i];
    delete[] options;

    for (int i = 0; i < tradersCount; i++) delete traders[i];
    delete[] traders;
}
Instrument* Market::addInstrument(string type, string n, double p, string expDate, double strikePrice) {
    if (type == "Stock") {
        Stock *newObject = new Stock(n, p);
        this->stocks[this->stocksCount] = newObject;
        this->stocksCount += 1;
        return newObject;
    } else if (type == "OptionCall") {
        OptionCall *newObject = new OptionCall(n, p, expDate, strikePrice);
        this->options[this->optionsCount] = newObject;
        this->optionsCount += 1;
        return newObject;
    } else if (type == "OptionPut") {
        OptionPut *newObject = new OptionPut(n, p, expDate, strikePrice); 
        this->options[this->optionsCount] = newObject;
        this->optionsCount += 1;
        return newObject;
    }
    return nullptr;
}




int main() {


    return 0;
}
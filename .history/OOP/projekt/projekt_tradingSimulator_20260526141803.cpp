#include <iostream>
#include <iomanip>

#include <string>
#include <format>
#include <bits/stdc++.h>
// #include "projekt_tradingSimulator.h"
using namespace std;


class Instrument {                                              // Trieda Instrument je abstraktná, pretože obsahuje čistě virtuální metody getType(), updatePrice() a calculateFee().
    protected:                                                  // Instrument má dve dedičné triedy - Stock a Option. Option má dve dedičné triedy - OptionCall a OptionPut.
        string name;
        string symbol;
        double price;

    public:
        virtual ~Instrument() = default;  
        string getName();
        double getPrice();
        string getSymbol();

        virtual string getType() = 0;                       
        virtual void updatePrice(double p) = 0;                 // abstraktne metody - musia být implementované v dědičných třídách
        virtual double calculateFee() {return price * 0.1};                  // pretizena metoda
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
        Stock(string n, double p);
        double getDividend();
        void updatePrice(double p);
        string getType();
};
Stock::Stock(string n, double p, double d) {
    this->name = n;
    this->price = p;
    this->dividend = d;
}
Stock::Stock(string n, double p) {
    this->name = n;
    this->price = p;
}
double Stock::getDividend() {
    return this->dividend;
}
double Stock::calculateFee() {
    return this->price * 0.01;
}
string Stock::getType() {
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
        Stock* underlyingStock;
        string expirationDate;
    public:
        Option(string n, double p, Stock* underlying);
        virtual ~Option();
        virtual double getStrikePrice() = 0;
        virtual string getExpirationDate()  = 0;
        virtual string getType() = 0;
        virtual void updatePrice(double p) = 0;
        virtual double getStrike() = 0;
};
Option::Option(string n, double p, Stock* underlying) {
    this->underlyingStock = underlying;
    this->name = n;
    this->price = p;
}
Option::~Option() {
    // No dynamic memory to clean up in this base class
}

class OptionCall: public Option {
    public:
        OptionCall(string n, double p, string expDate, double strikePrice, Stock* underlying);
        double intrinsicValue();
         void updatePrice(double p);
         string getType();
         double getStrike();
         double getStrikePrice();
         string getExpirationDate();
         double calculateFee() override { return price * 0.05;;
};


OptionCall::OptionCall(string n, double p, string expDate, double strikePrice, Stock* underlying) : Option(n, p, underlying) {
    this->strikePrice = strikePrice;
    this->daysToExp = 30;                   
    this->premium = 0.15 * p; 
    this->underlyingPrice = underlying->getPrice();
    this->expirationDate = expDate;
}
string OptionCall::getType() {
    return "OptionCall";
}
double OptionCall::getStrike() {
    return this->strikePrice;
}
double OptionCall::calculateFee() {
    return (price * 0.05);
}
double OptionCall::getStrikePrice() {
    return strikePrice;
}
string OptionCall::getExpirationDate() {
    return expirationDate;
}


class OptionPut : public Option {
public:
    OptionPut(string n, double p, string expDate, double strikePrice, Stock* underlying);

    double intrinsicValue();
    void updatePrice(double p) override;
    string getType() override;

    double getStrike() override { return strikePrice; }
    double getStrikePrice() override { return strikePrice; }
    string getExpirationDate() override { return expirationDate; }
    double calculateFee() override { return price * 0.05; }
};

OptionPut::OptionPut(string n, double p, string expDate, double strikePrice, Stock* underlying) : Option(n, p, underlying) {
    this->strikePrice = strikePrice;
    this->daysToExp = 30;                   
    this->premium = 0.10 * p; 
    this->underlyingPrice = underlying->getPrice();
    this->expirationDate = expDate;
}
string OptionPut::getType() {
    return "OptionPut";
}
double OptionCall::intrinsicValue() {
    return max(0.0, this->underlyingPrice - this->strikePrice);
}
double OptionPut::intrinsicValue() {
    return max(0.0, this->strikePrice - this->underlyingPrice);
}

void OptionCall::updatePrice(double p) {
    double underlyingPrice = underlyingStock->getPrice();
    this->price = max(0.0, underlyingPrice - strikePrice+ premium - daysToExp*0.1) ;
}
void OptionPut::updatePrice(double p) {
    double underlyingPrice = underlyingStock->getPrice();
    this->price = max(0.0, strikePrice - underlyingPrice+ premium + daysToExp*0.1) ;
}

class Order {                                                       // Trieda Order je čisto abstraktná, pretože má čistě virtuálnu metodu getType(), ktorá je implementovaná v dědičných třídách Sell a Buy
    private:                                                        // Order má dve dedičné triedy - Sell a Buy.
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

class Position {
    private: 
        Instrument* instrument;
        double quantity;
    public:
        Position(Instrument* i, double q);
        Instrument* getInstrument();
        double getQuantity();
        void addQuantity(double q);
        void reduceQuantity(double q);
        double getValue();
};

Position::Position(Instrument* i, double q) {
    this->instrument = i;
    this->quantity = q;
}
Instrument* Position::getInstrument() {
    return this->instrument;
}
double Position::getQuantity() {
    return this->quantity;
}
double Position::getValue() {
    return this->instrument->getPrice() * this->quantity;
}
void Position::addQuantity(double q) {
    this->quantity += q;
}
void Position::reduceQuantity(double q) {
    this->quantity -= q;
}

class Market;
class Portfolio;
class Client;

class Portfolio {
    private:
        Client* owner;
        Position** positions;
        int positionsCount;
        Order** orders;
        int ordersCount;
        double cash;

    public:
        Portfolio(Client* o);
        ~Portfolio();
        Client* getOwner() const;
        int getPositionsCount() const;
        int getOrdersCount() const;
        Position* findPosition(Instrument* inst) const;
        Order** getOrders() const;
        // void applyOrder(Order* o);

        double getTotalValue() const;
        double getTotalValue(const string& type) const;

        void printPortfolio() const;
        double getCash() const {return cash;}
        void setCash(double c) {cash = c;}
        void addOrder(Order* o);
        void addPosition(Instrument* inst, int q);
        void removePosition(Position* p);
    };
    
    void Portfolio::addPosition(Instrument* i, int q){
        positions[positionsCount++]=new Position(i, q);
    }

    void Portfolio::removePosition(Position* p) {
    int index = -1;
    // find index
    for (int i = 0; i < this->positionsCount; i++) {
        if (this->positions[i] == p) {
            index = i;
            break;
        }
    }
    if (index == -1) return; // not found
    delete this->positions[index]; // free memory
    // shift left
    for (int i = index; i < positionsCount - 1; i++) {
        positions[i] = positions[i + 1];
    }
    positionsCount--;
}


    void Portfolio::addOrder(Order* o) {
        orders[ordersCount++]=o;
    }
    Portfolio::Portfolio(Client* o) {
        this->owner = o;
        this->positions = new Position*[100];  // Assuming a maximum of 100 positions
        this->positionsCount = 0;
        this->orders = new Order*[100];  // Assuming a maximum of 100 orders
        this->ordersCount = 0;
        this->cash = 100000.0;  // Initial cash balance
    }
    Portfolio::~Portfolio() {
        for (int i = 0; i < positionsCount; i++) delete positions[i];
        delete[] positions;

        for (int i = 0; i < ordersCount; i++) delete orders[i];
        delete[] orders;
    }

    // Nájde pozíciu podľa instrumentu
    Position* Portfolio::findPosition(Instrument* inst) const {
        for (int i = 0; i < positionsCount; i++) {
            if (positions[i]->getInstrument() == inst)
                return positions[i];
        }
        return nullptr;
    }

    // // Pridanie alebo aktualizácia pozície
    // void Portfolio::applyOrder(Order* o) {
    //     orders[ordersCount++] = o;

    //     Position* pos = findPosition(o->getInstrument());

    //     if (o->getType() == "Buy") {
    //         if (pos == nullptr) {
    //             positions[positionsCount++] = new Position(o->getInstrument(), o->getQuantity());
    //         } else {
    //             pos->addQuantity(o->getQuantity());
                
    //         }
    //     this->cash = this->cash - o->getQuantity() * o->getPrice() - o->getInstrument()->calculateFee();  // Snížení hotovosti při nákupu
    //     }
    //     else if (o->getType() == "Sell") {
    //         if (pos != nullptr) {
    //             pos->reduceQuantity(o->getQuantity());
    //             this->cash = this->cash + o->getQuantity() * o->getPrice() - o->getInstrument()->calculateFee();  // Zvýšení hotovosti při prodeji
    //             if (pos->getQuantity() <= 0) {
    //                 for (int i = 0; i <positionsCount; i++) {
    //                     positions[i] = positions[i+1];
    //                 }
    //                 positionsCount--;
    //             }
    //         }
    //     }
    // }

    double Portfolio::getTotalValue() const {
        double total = cash;
        for (int i = 0; i < positionsCount; i++) {
            total += positions[i]->getValue();
        }
        return total;
    }

    double Portfolio::getTotalValue(const string& type) const {
        double total = 0.0;
        for (int i = 0; i < positionsCount; i++) {
            if (positions[i]->getInstrument()->getType() == type) {
                total += positions[i]->getValue();
            }
        }
        return total;
    }

    Order** Portfolio::getOrders() const {
        return this->orders;
    }
    
    int Portfolio::getOrdersCount() const {
        return this->ordersCount;
    }

    Client* Portfolio::getOwner() const {
        return this->owner;
    }



class Client {             
    private:
        int code;
        string name;
        Market** markets;
        int marketsCount;
        Portfolio* portfolio;
    public:
        Client(int c, string n);
        int getCode();
        string getName();
        void addMarket(Market* m);
        Portfolio* getPortfolio() const;
        Order* buy(string i, int q, Market* m);
        Order* sell(string i, int q, Market* m);
        // Order* buy(const string i, int q, double strikePrice, Market* m);
        // Order* sell(const string i, int q, double strikePrice, Market* m );
    };
    Client::Client(int c, string n) {          
        this->code = c;
        this->name = n;
        this->markets = new Market*[10];  // Assuming a maximum of 10 markets
        this->marketsCount = 0;
        this->portfolio = new Portfolio(this);}

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


    Portfolio* Client::getPortfolio() const {
        return this->portfolio;
    }


    void Portfolio::printPortfolio() const {
        cout << "----------------------------------------" << endl;
        cout << "Portfolio of " << owner->getName() << ":" << endl;
        for (int i = 0; i < positionsCount; i++) {
            cout << " - " << positions[i]->getInstrument()->getName() << ": " << positions[i]->getQuantity() << " units, Value: " << positions[i]->getValue() << endl;
        }
        cout << "Total Portfolio Value: " << getTotalValue() << endl;
        cout << "----------------------------------------" << endl;
    }


class Market {                                                  // Trieda Market používa pretazene metody addInstrument() pre pridanie rôznych typov inštrumentov
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

        Instrument* addOptionCall(string n, double p, string expDate, double strikePrice, Stock* underlying);
        Instrument* addOptionPut(string n, double p, string expDate, double strikePrice, Stock* underlying);
        Instrument* addStock(string n, double p, double d);
        Instrument* addStock(string n, double p);
        Client* addTrader(string t);
        void printTraders();
        void printStocks();
        void printOptions();
        void generateOptionsForStock(Stock* s);
        Instrument* findInstrumentByName(string name) const {
            for (int i = 0; i < instrumentCount; i++) {
                if (instruments[i]->getName() == name) {
                    return instruments[i];
                }
            }
            return nullptr;
        }
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

Instrument* Market::addStock(string n, double p) {
    Stock *newObject = new Stock(n, p, 0);
    this->instruments[this->instrumentCount] = newObject;
    this->instrumentCount += 1;
    generateOptionsForStock(newObject);
    return newObject;
}

Instrument* Market::addStock(string n, double p, double d) {
    Stock *newObject = new Stock(n, p, d);
    this->instruments[this->instrumentCount] = newObject;
    this->instrumentCount += 1;
    generateOptionsForStock(newObject);
    return newObject;
}

Instrument* Market::addOptionCall(string n, double p, string expDate, double strikePrice, Stock* underlying) {
    OptionCall *newObject = new OptionCall(n, p, expDate, strikePrice, underlying);
    this->instruments[this->instrumentCount] = newObject;
    this->instrumentCount += 1;
    return newObject;
}

Instrument* Market::addOptionPut(string n, double p, string expDate, double strikePrice, Stock* underlying) {
    OptionPut *newObject = new OptionPut(n, p, expDate, strikePrice, underlying);
    this->instruments[this->instrumentCount] = newObject;
    this->instrumentCount += 1;
    return newObject;
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
// Order* Market::addSell(const string& instrumentName, double q, double p, Client* c) {
//     Instrument* inst = findInstrumentByName(instrumentName);
//     if (!inst) {
//         cout << "Instrument " << instrumentName << " not found!" << endl;
//         return nullptr;
//     }
//     Order* o = new Sell(inst, q, p);
//     c->getPortfolio()->applyOrder(o);
//     cout << "Processing Sell order on market " << name
//          << ": " << q << " of " << inst->getName()
//          << " at price " << p << ", Fee: " << o->getInstrument()->calculateFee() * q << endl;
//     return o;
// }

// Order* Market::addBuy(const string& instrumentName, double q, double p, Client* c) {
//     Instrument* inst = findInstrumentByName(instrumentName);
//     if (!inst) {
//         cout << "Instrument " << instrumentName << " not found!" << endl;
//         return nullptr;
//     }
//     Order* o = new Buy(inst, q, p);
//     c->getPortfolio()->getOrders()[c->getPortfolio()->getOrdersCount()] = o;                                     // Uloží objednávku do portfolia klienta
//     c->getPortfolio()->applyOrder(o);

//     cout << "Processing Buy order on market " << name
//          << ": " << q << " of " << inst->getName()
//          << " at price " << p << ", Fee: " << o->getInstrument()->calculateFee() * q << endl;                   // Late binding - calculateFee() se volá pre konkrétny typ instrumentu (Stock, OptionCall, OptionPut)

//     return o;
// }


    Order* Client::buy(string i, int qty, Market* m) {
        Instrument* inst = m->findInstrumentByName(i);
        if (!inst) {
            cout << "Instrument " << i << " not found!\n";
            return nullptr;
        }

        double price = inst->getPrice();
        double fee = inst->calculateFee();
        double totalCost = qty * price + fee;

        if (portfolio->getCash() < totalCost) {
            cout << "Not enough cash!\n";
            return nullptr;
        }

        Order* o = new Buy(inst, qty, price);
        portfolio->addOrder(o);

        Position* pos = portfolio->findPosition(inst);
        if (!pos) portfolio->addPosition(inst,qty);
        else pos->addQuantity(qty);

        portfolio->setCash(portfolio->getCash() - totalCost);

        cout << "Client " << this->name << " BUY " << qty << " of " << inst->getName()
            << " at " << price << " (fee " << fee << ")\n";

        return o;
    }

    Order* Client::sell(string i, int qty, Market* m) {
        Instrument* inst = m->findInstrumentByName(i);
        if (!inst) {
            cout << "Instrument " << i << " not found!\n";
            return nullptr;
        }

        Position* pos = portfolio->findPosition(inst);
        if (!pos || pos->getQuantity() < qty) {
            cout << "Not enough quantity to sell!\n";
            return nullptr;
        }

        double price = inst->getPrice();
        double fee = inst->calculateFee();
        double totalGain = qty * price - fee;

        Order* o = new Sell(inst, qty, price);
        portfolio->addOrder(o);

        pos->reduceQuantity(qty);
        if (pos->getQuantity() == 0)
            portfolio->removePosition(pos);

        portfolio->setCash(portfolio->getCash() + totalGain);

        cout << "Client " << this->name << " SELL " << qty << " of " << inst->getName()
            << " at " << price << " (fee " << fee << ")\n";

        return o;
    }


    // Order* Client::buy(string i, int q, double strikePrice, Market* m) {
    //     Instrument* inst = m->findInstrumentByName(i);
    //     if (!inst) {
    //         cout << "Instrument " << i << " not found!" << endl;
    //         return nullptr;
    //     }
    //     Order* o = new Buy(inst, q, inst->getPrice());
    //     this->portfolio->applyOrder(o);

    //     cout << "Client " << this->name << " BUY " << q << " of " << i
    //         << " at price " << inst->getPrice()
    //         << ", Fee: " << inst->calculateFee() * q << endl;

    //     return o;
    //     }
    // Order* Client::sell(string i, int q, double strikePrice, Market* m) {
    //     Instrument* inst = m->findInstrumentByName(i);
    //     if (!inst) {
    //         cout << "Instrument " << i << " not found!" << endl;
    //         return nullptr;
    //     }
    //     Order* o = new Sell(inst, q, inst->getPrice());
    //     this->portfolio->applyOrder(o);

    //     cout << "Client " << this->name << " BUY " << q << " of " << i
    //         << " at price " << inst->getPrice()
    //         << ", Fee: " << inst->calculateFee() * q << endl;

    //     return o;
    // }




void Market::generateOptionsForStock(Stock* s) {
    double price = s->getPrice();

    double strikes[] = { price - 10, price, price + 10 };

    for (double strike : strikes) {
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(1) << strike;
        addOptionCall(s->getName() + std::string("_Call"), s->getPrice(), "2024-12-31", strike,s)->updatePrice(s->getPrice());  // Initial price calculation based on the underlying stock
        addOptionPut(s->getName() + std::string("_Put"),  s->getPrice(), "2024-12-31", strike,s)->updatePrice(s->getPrice());
    }
}

void Market::printTraders() {
    cout << "List of Traders: " << this->name << ":" << endl;
    for (int i = 0; i < this->tradersCount; i++) {
        cout << " - " << this->traders[i]->getName() << endl;
    }
}
void Market::printStocks() {
    cout << "List of Stocks: " << this->name << ":" << endl;
    for (int i = 0; i < this->instrumentCount; i++) {
        if (this->instruments[i]->getType() == "Stock") {
            cout << " - " << this->instruments[i]->getType() << ": " << this->instruments[i]->getName() << ",   Price: " << this->instruments[i]->getPrice() << endl;
        }
    }
}
void Market::printOptions() {
    cout << "List of Options: " << this->name << ":" << endl;

    for (int i = 0; i < instrumentCount; i++) {
        string t = instruments[i]->getType();

        if (t == "OptionCall") {
            OptionCall* opt = (OptionCall*) instruments[i];   // bezpečné, lebo typ sme overili
            cout << " - OptionCall: " << opt->getName()
                 << ", Strike: " << opt->getStrike()
                 << ", Price: " << opt->getPrice()
                 << ", Expiration: " << opt->getExpirationDate()
                 << endl;
        }

        if (t == "OptionPut") {
            OptionPut* opt = (OptionPut*) instruments[i];
            cout << " - OptionPut: " << opt->getName()
                 << ", Strike: " << opt->getStrike()
                 << ", Price: " << opt->getPrice()
                 << ", Expiration: " << opt->getExpirationDate()
                 << endl;
        }
    }
}


int main() {
    std::vector<string> tickers_US= {"AAPL", "GOOGL", "MSFT", "TSLA", "META"};
    std::vector<string> tickers_US_div = {"BRKB", "AMZN", "BA", "ZOOM", "KO"};
    std::vector<float> dividends = {4,6,12,10,2};
    std::vector<double> prices_US = {150,280,300,140,350};
    
    Market* market1 = new Market("NASDAQ", 100, 10);

    Client* tomas = market1->addTrader("Tomas");
    Client* betka = market1->addTrader("Betka");
    
    for (int i = 0; i < tickers_US.size(); i++) {                       // ukazka pretizenej metody addStock
        market1->addStock(tickers_US[i], prices_US[i]);
        market1->addStock(tickers_US_div[i], prices_US[i]*1.5, dividends[i]);
    }

    cout << "Market1: " << market1->getName() << endl;
    market1->printStocks();

    
    betka->getPortfolio()->printPortfolio();
    tomas->getPortfolio()->printPortfolio();

    tomas->buy("AAPL", 10, market1);
    tomas->buy("MSFT", 7, market1);

    market1->findInstrumentByName("AAPL")->updatePrice(170.0);
    market1->findInstrumentByName("MSFT")->updatePrice(320.0);

    cout << "Updated price of AAPL: " << market1->findInstrumentByName("AAPL")->getPrice() << endl;
    cout << "Updated price of MSFT: " << market1->findInstrumentByName("MSFT")->getPrice() << endl;

    tomas->sell("MSFT", 4, market1);
    tomas->sell("AAPL", 3, market1);

    tomas->getPortfolio()->printPortfolio();

    cout << "Total value of Stock (Trader 1: " << tomas->getName() << "): " << tomas->getPortfolio()->getTotalValue("Stock") << endl;
    cout << "Total value of Stock (Trader 2: " << betka->getName() << "): " << betka->getPortfolio()->getTotalValue("Stock") << endl;


    tomas->getPortfolio()->printPortfolio();
    betka->getPortfolio()->printPortfolio(); 

    // tomas->buy("META_Call", 1, 350, market1);
    
    // cout << "Options after price update:" << endl;
    market1->printOptions();

    // for (int i = 0; i < market1->getInstrumentsCount(); i++) {
    //     if (market1->getInstruments()[i]->getType() == "OptionCall") {
    //         market1->getInstruments()[i]->updatePrice(market1->getInstruments()[0]->getPrice());
    //         cout << "Updated price of " << market1->getInstruments()[i]->getName() << ": " << market1->getInstruments()[i]->getStrike() << "  " << market1->getInstruments()[i]->getPrice() << endl;
    //     }
    // }

    return 0;
}
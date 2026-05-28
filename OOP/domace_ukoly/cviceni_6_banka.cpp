#include <iostream>
#include <string>

using namespace std;

class Client {                  // deklarace
    private:
        int code;
        string name;
    public:
        Client(int c, string n);
        int getCode();
        string getName();

};
Client::Client(int c, string n) {          // Konstruktor
    this->code = c;
    this->name = n;
}
int Client::getCode() {
    return this->code;
}
string Client::getName() {
    return this->name;
}

class Account {
    private:
        int number;
        double interestRate;
        static double defaultIR;
    protected:
        double balance;

        Client* owner;
        Client* partner;
    public:
        Account(int n, Client *c);
        Account(int n, Client *c, double ir);

        static void setDefaultIR(double defaultIR);
        static double getDefaultIR();

        int getNumber();
        double getBalance();
        double getInterestRate();
        Client *getOwner();
        Client *getPartner();
        
        void Deposit(double a);
        bool Withdraw(double a);
        void AddInterest();
        bool canWithdraw(double a);
};

Account::Account(int n, Client *c) {
    this->number = n;
    this->owner = c;
    this->partner = nullptr;
    this->balance = 0;
    this->interestRate = defaultIR;
}
Account::Account(int n, Client *c, double ir) {
    this->number = n;
    this->owner = c;
    this->partner = nullptr;
    this->balance = 0;
    this->interestRate = ir;
}
// Account::Account(int n, Client *c, Client *p) {          // Ucty s partnerom
//     this->number = n;
//     this->owner = c;
//     this->partner = p;
//     this->balance = 0;
//     this->interestRate = defaultIR;

// }
// Account::Account(int n, Client *c, Client *p, double ir) {
//     this->number = n;
//     this->owner = c;
//     this->partner = p;
//     this->balance = 0;
//     this->interestRate = ir;
// }
int Account::getNumber() {
    return this->number;
}
double Account::getBalance() {
    return this->balance;
}
double Account::getInterestRate() {
    return this->interestRate;
}
Client* Account::getOwner() {
    return this->owner;
}
Client* Account::getPartner() {
    return this->partner;
}
bool Account::canWithdraw(double a) {
    return this->balance >= a;
}
void Account::Deposit(double a) {
    this->balance += a;
}
bool Account::Withdraw(double a) {
    if (this->canWithdraw(a)) {
        this->balance -= a;
        return true;
    }
    return false;
}
void Account::AddInterest() {
    this->balance += this->balance * this->interestRate;
}

double Account::defaultIR = 0.01;   // default pre všetky účty

void Account::setDefaultIR(double ir) {
    defaultIR = ir;
}

double Account::getDefaultIR() {
    return defaultIR;
}


class CreditAccount : public Account {
    private: 
        double credit;
    public:
        CreditAccount(int n, Client *o, double c);
        CreditAccount(int n, Client *o, double ir, double c);
        bool canWithdraw(double a);
        bool Withdraw(double a);
};

bool CreditAccount::canWithdraw(double a){
    return (this->getBalance() + this->credit >= a);
}

CreditAccount::CreditAccount(int n, Client *o, double c) : Account(n, o) {
    this->credit=c;
}
CreditAccount::CreditAccount(int n, Client *o, double ir, double c) : Account(n, o, ir) {
    this->credit=c;
}
bool CreditAccount::Withdraw(double a) {
    bool success = false;
    if (this->canWithdraw(a)) {
        this->balance -= a;
        success = true;
    }
    return success;
}


class PartnerAccount : public Account {
    private:
        Client* partner;
    public:
        PartnerAccount(int n, Client* o, Client* p);
        PartnerAccount(int n, Client* o, Client* p, double ir);
        Client* getPartner();
};

PartnerAccount::PartnerAccount(int n, Client* o, Client* p) : Account(n, o) {
    this->partner = p;
}
PartnerAccount::PartnerAccount(int n, Client* o, Client* p, double ir) : Account( n, o, ir) {
    this->partner = p;
}
Client* PartnerAccount::getPartner() {
    return this->partner;
}


// class Bank {
//     private:
//         Client** clients;
//         int clientsCount;
//         Account** accounts;
//         int accountsCount;
//     public:
//         Bank(int c, int a);
//         ~Bank();

//         Client* getClient(int c);
//         Account* getAccount(int a);
        
//         Client* createClient(int c, string n);
//         Account* createAccount(int n, Client* c);
//         Account* createAccount(int n, Client *c, double ir);
//         Account* createAccount(int n, Client *c, Client *p);
//         Account* createAccount(int n, Client *c, Client *p, double ir);
//         int getClientsCount();
        
//         void addInterest();
// };

// Bank::Bank(int c, int a) {
//     clients = new Client*[c];
//     accounts = new Account*[a];
//     clientsCount = 0;
//     accountsCount = 0;
// }
// Bank::~Bank() {
//     for (int i = 0; i < clientsCount; i++) delete clients[i];
//     delete[] clients;

//     for (int i = 0; i < accountsCount; i++) delete accounts[i];
//     delete[] accounts;
// }
// Client* Bank::getClient(int c) {
//     return this->clients[c];
// }
// Account* Bank::getAccount(int a) {
//     return this->accounts[a];
// }
// Client* Bank::createClient(int c, string n) {
//     Client *newObject = new Client(c, n);
//     this->clients[this->clientsCount] = newObject;
//     this->clientsCount += 1;
//     return newObject;
// }
// Account* Bank::createAccount(int n, Client *c) {
//     Account *newObject = new Account(n, c);
//     this->accounts[this->accountsCount] = newObject;
//     this->accountsCount += 1;
//     return newObject;
// }
// Account* Bank::createAccount(int n, Client *c, double ir) {
//     Account *newObject = new Account(n, c, ir);
//     this->accounts[this->accountsCount] = newObject;
//     this->accountsCount += 1;
//     return newObject;
// }
// Account* Bank::createAccount(int n, Client *c, Client *p) {
//     Account *newObject = new Account(n, c, p);
//     this->accounts[this->accountsCount] = newObject;
//     this->accountsCount += 1;
//     return newObject;
// }
// Account* Bank::createAccount(int n, Client *c, Client *p, double ir) {
//     Account *newObject = new Account(n, c, p, ir);
//     this->accounts[this->accountsCount] = newObject;
//     this->accountsCount += 1;
//     return newObject;
// }
// void Bank::addInterest() {
//     for (int i = 0; i < accountsCount; i++) accounts[i]->AddInterest();
// }

// int Bank::getClientsCount() {
//     return clientsCount;
// }

int main() {

    // Cviceni 6: dedicnost - prekryti
    Client *o = new Client(0, "Tomas");
    CreditAccount *ca = new CreditAccount(1, o, 1000);
    cout << ca->canWithdraw(1000) << endl;

    Account *a = ca;                    // polymorfne prirazeni
    cout << a->canWithdraw(1000) << endl;

    cout << ca -> canWithdraw(1000) << endl;

    a=nullptr;
    delete ca;

    getchar();

    // delete bank;

    return 0;
}
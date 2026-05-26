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
        double balance;
        double interestRate;

        static double defaultIR;

        Client* owner;
        Client* partner;
    public:
        Account(int n, Client *c);
        Account(int n, Client *c, double ir);
        Account(int n, Client *c, Client *p);
        Account(int n, Client *c, Client *p, double ir);

        static void setDefaultIR(double defaultIR);
        static double getDefaultIR();

        int getNumber();
        double getBalance();
        double getInterestRate();
        Client *getOwner();
        Client *getPartner();
        bool canWithdraw(double a);

        void Deposit(double a);
        bool Withdraw(double a);
        void AddInterest();
};

Account::Account(int n, Client *c) {
    this->number = n;
    this->owner = c;
    this->partner = nullptr;
    this->balance = 0;
    this->interestRate = 0.01;
}
Account::Account(int n, Client *c, double ir) {
    this->number = n;
    this->owner = c;
    this->partner = nullptr;
    this->balance = 0;
    this->interestRate = ir;
}
Account::Account(int n, Client *c, Client *p) {
    this->number = n;
    this->owner = c;
    this->partner = p;
    this->balance = 0;
    this->interestRate = 0.01;
}
Account::Account(int n, Client *c, Client *p, double ir) {
    this->number = n;
    this->owner = c;
    this->partner = p;
    this->balance = 0;
    this->interestRate = ir;
}
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

class Bank {
    private:
        Client** clients;
        int clientsCount;
        Account** accounts;
        int accountsCount;
    public:
        Bank(int c, int a);
        ~Bank();

        Client* getClient(int c);
        Account* getAccount(int a);
        
        Client* createClient(int c, string n);
        Account* createAccount(int n, Client* c);
        Account* createAccount(int n, Client *c, double ir);
        Account* createAccount(int n, Client *c, Client *p);
        Account* createAccount(int n, Client *c, Client *p, double ir);
        int getClientsCount();
        
        void addInterest();
};

Bank::Bank(int c, int a) {
    clients = new Client*[c];
    accounts = new Account*[a];
    clientsCount = 0;
    accountsCount = 0;
}
Bank::~Bank() {
    for (int i = 0; i < clientsCount; i++) delete clients[i];
    delete[] clients;

    for (int i = 0; i < accountsCount; i++) delete accounts[i];
    delete[] accounts;
}
Client* Bank::getClient(int c) {
    return this->clients[c];
}
Account* Bank::getAccount(int a) {
    return this->accounts[a];
}
Client* Bank::createClient(int c, string n) {
    Client *newObject = new Client(c, n);
    this->clients[this->clientsCount] = newObject;
    this->clientsCount += 1;
    this
    return newObject;
}
Account* Bank::createAccount(int n, Client *c) {
    Account *newObject = new Account(n, c);
    this->accounts[this->accountsCount] = newObject;
    this->accountsCount += 1;
    return newObject;
}
Account* Bank::createAccount(int n, Client *c, double ir) {
    Account *newObject = new Account(n, c, ir);
    this->accounts[this->accountsCount] = newObject;
    this->accountsCount += 1;
    return newObject;
}
Account* Bank::createAccount(int n, Client *c, Client *p) {
    Account *newObject = new Account(n, c, p);
    this->accounts[this->accountsCount] = newObject;
    this->accountsCount += 1;
    return newObject;
}
Account* Bank::createAccount(int n, Client *c, Client *p, double ir) {
    Account *newObject = new Account(n, c, p, ir);
    this->accounts[this->accountsCount] = newObject;
    this->accountsCount += 1;
    return newObject;
}
void Bank::addInterest() {
    for (int i = 0; i < accountsCount; i++) accounts[i]->AddInterest();
}

int Bank::getClientsCount() {
    return clientsCount;
}

int main() {
    Bank *bank = new Bank(10, 10);
    Client *client1 = bank->createClient(1, "Tomas");
    Account *account1 = bank->createAccount(1, client1, 0.05);
    account1->Deposit(1000);
    bank->addInterest();
    cout << account1->getBalance() << endl;
    cout << bank->getClientsCount() << endl;

    Client *client2 = bank->createClient(2, "Jana");
    Account *account2 = bank->createAccount(2, client2, client1, 0.03);
    account2->Deposit(2000);

    cout << account1->getBalance() << endl;
    cout << account2->getBalance() << endl;

    cout << bank->getClientsCount() << endl;

    delete bank;

    return 0;
}
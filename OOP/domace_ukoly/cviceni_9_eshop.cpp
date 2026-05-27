#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

// "Interface" pro textový výstup
class IStringOutput {
public:
    virtual ~IStringOutput() {};
    virtual std::string ToString() const = 0;
};

// -------------------- PRODUKTY --------------------

class AbstractProduct : public IStringOutput {
protected:
    std::string name;
    double price;
public:
    AbstractProduct(const std::string& n, double p) {name = n; price = p;}
    virtual ~AbstractProduct() = default;
    double GetPrice() const { return price; }
    const std::string& GetName() const { return name; }
};

class MobilePhone : public AbstractProduct {
    std::string os;
public:
    MobilePhone(const std::string& n, double p, const std::string& os_) : AbstractProduct(n, p) {os = os_;}
    std::string ToString() const override {
        std::ostringstream oss;
        oss << "Mobil: " << name << " (" << os << "), cena: " << price;
        return oss.str();
    }
};

class Notebook : public AbstractProduct {
    double screenSize;
public:
    Notebook(const std::string& n, double p, double screen) : AbstractProduct(n, p), screenSize(screen) {}

    std::string ToString() const override {
        std::ostringstream oss;
        oss << "Notebook: " << name << " (" << screenSize << "\"), cena: " << price;
        return oss.str();
    }
};

class Monitor : public AbstractProduct {
    double size;
public:
    Monitor(const std::string& n, double p, double s) : AbstractProduct(n, p) {size = s;}

    std::string ToString() const override {
        std::ostringstream oss;
        oss << "Monitor: " << name
            << ", Size " << size << " inch"
            << ", cena: " << price;
        return oss.str();
    }
};

// -------------------- ZÁKAZNÍCI --------------------

class AbstractCustomer : public IStringOutput {
protected:
    std::string id;
public:
    AbstractCustomer(const std::string& id_) : id(id_) {}
    virtual ~AbstractCustomer() = default;
};

class AbstractRegisteredCustomer : public AbstractCustomer {
protected:
    std::string email;
public:
    AbstractRegisteredCustomer(const std::string& id_, const std::string& e) : AbstractCustomer(id_) {
        email = e;
    }
};

class RegisteredUser : public AbstractRegisteredCustomer {
    std::string fullName;
public:
    RegisteredUser(const std::string& id_,
                   const std::string& email_,
                   const std::string& name_)
        : AbstractRegisteredCustomer(id_, email_), fullName(name_) {}

    std::string ToString() const override {
        std::ostringstream oss;
        oss << "Registrovaný uživatel: " << fullName
            << " (ID: " << id << ", email: " << email << ")";
        return oss.str();
    }
};

class CompanyUser : public AbstractRegisteredCustomer {
    std::string companyName;
    std::string ico;
public:
    CompanyUser(const std::string& id_,
                const std::string& email_,
                const std::string& companyName_,
                const std::string& ico_)
        : AbstractRegisteredCustomer(id_, email_),
          companyName(companyName_), ico(ico_) {}

    std::string ToString() const override {
        std::ostringstream oss;
        oss << "Firemní zákazník: " << companyName
            << " (IČO: " << ico
            << ", ID: " << id
            << ", email: " << email << ")";
        return oss.str();
    }
};

class UnregisteredUser : public AbstractCustomer {
    std::string contactName;
public:
    UnregisteredUser(const std::string& id_,
                     const std::string& contactName_)
        : AbstractCustomer(id_), contactName(contactName_) {}

    std::string ToString() const override {
        std::ostringstream oss;
        oss << "Neregistrovaný zákazník: " << contactName
            << " (ID: " << id << ")";
        return oss.str();
    }
};

// -------------------- POLOŽKA OBJEDNÁVKY --------------------

class OrderItem : public IStringOutput {
    std::shared_ptr<AbstractProduct> product;
    int quantity;

public:
    OrderItem(std::shared_ptr<AbstractProduct> p, int q)
        : product(std::move(p)), quantity(q) {}

    double GetTotalPrice() const {
        return product->GetPrice() * quantity;
    }

    std::string ToString() const override {
        std::ostringstream oss;
        oss << quantity << "x " << product->ToString()
            << " = " << GetTotalPrice();
        return oss.str();
    }
};

// -------------------- OBJEDNÁVKA --------------------

class Order : public IStringOutput {
    std::shared_ptr<AbstractCustomer> customer;
    std::vector<OrderItem> items;

public:
    Order(std::shared_ptr<AbstractCustomer> c)
        : customer(std::move(c)) {}

    void AddItem(const OrderItem& item) {
        items.push_back(item);
    }

    double GetTotal() const {
        double sum = 0.0;
        for (const auto& it : items) {
            sum += it.GetTotalPrice();
        }
        return sum;
    }

    std::string ToString() const override {
        std::ostringstream oss;
        oss << "===== Objednávka =====\n";
        oss << "Zákazník:\n" << customer->ToString() << "\n\n";
        oss << "Položky:\n";
        for (const auto& it : items) {
            oss << "  - " << it.ToString() << "\n";
        }
        oss << "Celkem: " << GetTotal() << "\n";
        oss << "======================\n";
        return oss.str();
    }
};

// -------------------- DEMO PROGRAM --------------------

int main() {
    // Produkty
    auto phone = std::make_shared<MobilePhone>("Pixel 9", 18990, "Android");
    auto notebook = std::make_shared<Notebook>("Lenovo Legion", 42990, 15.0);
    auto monitor = std::make_shared<Monitor>("Dell", 6550, 23);

    std::vector<std::shared_ptr<AbstractProduct>>  catalogue;
    catalogue.push_back(phone);
    catalogue.push_back(notebook);
    catalogue.push_back(monitor);

    std::cout << "Katalóg produktov" << std::endl;
    for (auto &c : catalogue) {
        std::cout << c->ToString() << std::endl;
    }


    // Zákazníci
    auto regUser = std::make_shared<RegisteredUser>(
        "U123", "user@example.com", "Jan Novák");
    auto company = std::make_shared<CompanyUser>(
        "C456", "firma@example.com", "onsemi s.r.o.", "12345678");
    auto unreg = std::make_shared<UnregisteredUser>(
        "N789", "Petr BezRegistrace");

    // Objednávka 1 – registrovaný uživatel
    Order order1(regUser);
    order1.AddItem(OrderItem(phone, 1));
    order1.AddItem(OrderItem(notebook, 2));

    // Objednávka 2 – firma
    Order order2(company);
    order2.AddItem(OrderItem(monitor, 3));

    // Objednávka 3 – neregistrovaný
    Order order3(unreg);
    order3.AddItem(OrderItem(phone, 1));
    order3.AddItem(OrderItem(monitor, 1));

    // Výpis
    std::cout << order1.ToString() << "\n";
    std::cout << order2.ToString() << "\n";
    std::cout << order3.ToString() << "\n";

    std::cout << phone->ToString() << "\n";
    return 0;
}

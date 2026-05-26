#include <string>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Figure {
    public:
        virtual double Obsah() const = 0;
        virtual double Obvod() const = 0;
        virtual ~Figure() {}
};

class Rectangle : public Figure {
    protected:
        double a, b;
    public:
        Rectangle(double a, double b) : a(a), b(b) {}
        double Obsah() const override {return a * b;}
        double Obvod() const override {return 2 * (a + b);}
};

class Square : public Rectangle {
    public:
        Square(double side) : Rectangle(side, side) {}
};

class Circle : public Figure {
    private:
        double r;
    public:
        Circle(double r) : r(r) {}
        double Obsah() const override {return M_PI * r * r;}
        double Obvod() const override {return 2 * M_PI * r;}
};


int main() {
    std::vector<Figure*> fig;           
    Figure* f1 = new Rectangle(3, 4);
    Figure* f2 = new Square(5);
    Figure* f3 = new Circle(2);

    fig.push_back(f1);
    fig.push_back(f2);
    fig.push_back(f3);

    // Demonstrace substitučního principu – Každý potomek musí být použitelný všude tam, 
    // kde očekáváme předka, aniž by se změnilo chování programu.
    for (int i = 0; i < fig.size(); i++) {
        cout << "Obsah: " << fig[i]->Obsah();
        cout << "  Obvod: " << fig[i]->Obvod() << endl;
    }
    
    for (int i = 0; i < fig.size(); i++) {
        delete fig[i];
    }

    return 0;
}

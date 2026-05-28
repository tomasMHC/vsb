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
    Figure* f1 = new Rectangle(3, 4);
    Figure* f2 = new Square(5);
    Figure* f3 = new Circle(2);

    cout << "Obsah: " << f1->Obsah();
    cout << "  Obvod: " << f1->Obvod() << endl;
    
    cout << "Obsah: " << f2->Obsah();
    cout << "  Obvod: " << f2->Obvod() << endl;

    cout << "Obsah: " << f3->Obsah();
    cout << "  Obvod: " << f3->Obvod() << endl;

    delete f1; delete f2; delete f3;

    return 0;
}

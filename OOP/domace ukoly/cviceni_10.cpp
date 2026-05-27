#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

class A {
public:
    virtual ~A() {}
    virtual void Print() const {
        std::cout << "A" << std::endl;
    }
};

class B : public A {
public:
    void Print() const override {
        std::cout << "B" << std::endl;
    }
};

template<class T>
class Box {
private:
    T* instance;
public:
    Box(T* i) : instance(i) {}
    T* Get() { return instance; }
};

template<typename T>
class Stack {
private:
    std::vector<T> data;
public:
    void Push(const T& value) {
        data.push_back(value);
    }

    void Pop() {
        if (!data.empty()) data.pop_back();
    }

    T& Top() {
        return data.back();
    }

    bool Empty() const {
        return data.empty();
    }
};



// -------------------- DEMO PROGRAM --------------------

int main() {
    A* a = new A();
    B* b = new B();

    Box<A> boxA(a);
    Box<A> boxB(b);   // polymorfismus – B je A

    boxA.Get()->Print();  // A
    boxB.Get()->Print();  // B

    delete a;
    delete b;

    Stack<int> s;
    s.Push(10);
    s.Push(20);
    std::cout << "Top: " << s.Top() << std::endl;

    std::cout << "Empty? : " << s.Empty() << std::endl;

    std::cout << "Pop.." <<std::endl;
    s.Pop();
    std::cout << "Top: " << s.Top() << std::endl;

    return 0;
}

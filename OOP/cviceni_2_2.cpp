#include <iostream>
#include <string>
using namespace std;

class Node {
private:
    string key;
    string value;
    Node *left;
    Node *right;

public:
    Node(string k, string v);
    ~Node();

    string getKey();
    string getValue();

    Node* getLeft();
    Node* getRight();

    Node* createLeft(string k, string v);
    Node* createRight(string k, string v);
};

Node::Node(string k, string v) {
    key = k;
    value = v;
    left = nullptr;
    right = nullptr;
}

Node::~Node() {
    delete left;
    delete right;
}

string Node::getKey() { return key; }
string Node::getValue() { return value; }

Node* Node::getLeft() { return left; }
Node* Node::getRight() { return right; }

Node* Node::createLeft(string k, string v) {
    left = new Node(k, v);
    return left;
}

Node* Node::createRight(string k, string v) {
    right = new Node(k, v);
    return right;
}

int main() {
    Node *root = new Node("root", "A");

    Node *left = root->createLeft("left", "B");
    Node *right = root->createRight("right", "C");

    left->createLeft("left-left", "D");
    left->createRight("left-right", "E");

    right->createLeft("right-left", "F");
    right->createRight("right-right", "G");

    // príklad výpisu
    cout << root->getKey() << endl;
    cout << root->getLeft()->getKey() << endl;
    cout << root->getLeft()->getValue() << endl;
    cout << root->getRight()->getKey() << endl;
    cout << root->getRight()->getValue() << endl;

    delete root; // zmaže celý strom rekurzívne

    return 0;
}
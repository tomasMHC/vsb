#include <iostream>
#include <string>
using namespace std;

class DecisionNode {
private:
    string key;      // rozhodovacie kritérium
    string value;    // výsledok (zviera, rastlina...)
    DecisionNode *left;
    DecisionNode *right;

public:
    DecisionNode(string k, string v);
    ~DecisionNode();

    string getKey();
    string getValue();

    DecisionNode* getLeft();
    DecisionNode* getRight();

    DecisionNode* createLeft(string k, string v);
    DecisionNode* createRight(string k, string v);
};

DecisionNode::DecisionNode(string k, string v) {
    key = k;
    value = v;
    left = nullptr;
    right = nullptr;
}

DecisionNode::~DecisionNode() {
    delete left;
    delete right;
}

string DecisionNode::getKey() { return key; }
string DecisionNode::getValue() { return value; }

DecisionNode* DecisionNode::getLeft() { return left; }
DecisionNode* DecisionNode::getRight() { return right; }

DecisionNode* DecisionNode::createLeft(string k, string v) {
    left = new DecisionNode(k, v);
    return left;
}

DecisionNode* DecisionNode::createRight(string k, string v) {
    right = new DecisionNode(k, v);
    return right;
}

void printTree(DecisionNode *node, int depth = 0) {
    if (node == nullptr) return;

    // odsadenie podľa hĺbky
    for (int i = 0; i < depth; i++) cout << "  ";

    cout << "- " << node->getKey() << " : " << node->getValue() << endl;

    printTree(node->getLeft(), depth + 1);
    printTree(node->getRight(), depth + 1);
}
void printPretty(DecisionNode* node, string prefix = "", bool isLeft = false) {
    if (node == nullptr) return;

    // Print right subtree first (so the tree grows downward)
    printPretty(node->getRight(), prefix + (isLeft ? "│   " : "    "), false);

    // Print current node
    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << node->getKey();

    if (!node->getValue().empty())
        cout << " (" << node->getValue() << ")";

    cout << endl;

    // Print left subtree
    printPretty(node->getLeft(), prefix + (isLeft ? "    " : "│   "), true);
}
int main() {
    DecisionNode *root = new DecisionNode("Má srsť?", "");  

    DecisionNode *yes = root->createLeft("Je to domestikované?", "");
    DecisionNode *no  = root->createRight("Má perie?", "");

    yes->createLeft("Pes", "Canis lupus familiaris");
    yes->createRight("Mačka", "Felis catus");

    DecisionNode *bird = no->createRight("Vie lietať?", "");
    DecisionNode *reptile = no->createLeft("Má šupiny?", "");

    bird->createLeft("Sliepka", "Gallus gallus domesticus");
    bird->createRight("Orol", "Aquila chrysaetos");

    reptile->createLeft("Jašterica", "Lacertilia");
    reptile->createRight("Had", "Serpentes");

    // vypíšeme celý strom
    printPretty(root);

    delete root; // zmaže celý strom rekurzívne
    return 0;
}
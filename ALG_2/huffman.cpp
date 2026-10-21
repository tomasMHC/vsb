//vytvori huffmanovo kodovanie na zaklade nacitaneho txt suboru s pocetnostami jednotlivych znakov.

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

class Node {
public:
    char symbol;
    int freq;
    Node* left;
    Node* right;

    Node(char s, int f) {
    symbol = s;
    freq = f;
    left = nullptr;
    right = nullptr;
    }
};

class Compare {
public:
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;   // min-heap
    }
};

void generateCodes(Node* node, string code,
                   map<char, string>& kody)
{
    if (!node) return;
    if (!node->left && !node->right) {
        kody[node->symbol] = code;
        return;
    }

    generateCodes(node->left, code + "0", kody );
    generateCodes(node->right, code + "1", kody );
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Pouzitie: " << argv[0] << " <nazov_suboru>\n";
        return 1;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;
    std::string filename = argv[1];
    ifstream file(filename);

    char c;
    int f;

    while (file >> c >> f) {
        pq.push(new Node(c, f));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* parent = new Node('\0', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    Node* root = pq.top();

    map<char, string> kody;
    generateCodes(root, "", kody);

    for (auto& [symbol, code] : kody) {
        cout << symbol << " : " << code << '\n';
    }

    return 0;
}

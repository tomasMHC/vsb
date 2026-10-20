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

    Node(char s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
};

class Compare {
public:
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;   // min-heap
    }
};

void generateCodes(Node* node, string code,
                   map<char, string>& codes)
{
    if (!node) return;

    if (!node->left && !node->right) {
        codes[node->symbol] = code;
        return;
    }

    generateCodes(node->left, code + "0", codes);
    generateCodes(node->right, code + "1", codes);
}

int main()
{
    priority_queue<Node*, vector<Node*>, Compare> pq;

    ifstream file("huff.txt");

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

    map<char, string> codes;
    generateCodes(root, "", codes);

    for (auto& [symbol, code] : codes) {
        cout << symbol << " : " << code << '\n';
    }

    return 0;
}

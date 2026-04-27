#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>

std::vector<std::vector<int>> read_lines(const std::string& filename) {
    std::ifstream file(filename);
    int N;
    file >> N;
    std::vector<std::vector<int>> data(N, std::vector<int>(N, 0));
    int a, b;
    while (file >> a >> b) {
        data[a][b] = 1;
    }
    return data;
}

void print_matrix( std::vector<std::vector<int>>& matrix ) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool find_celebrity(const std::vector<std::vector<int>>& knows, int& celebrity, std::string& result) {                  // O(N^2) algoritmus, prejde vsetkych N ludi a porovna ich s ostatnymi N-1 ludmi, ci su celebrity alebo nie.
    int N = knows.size();
    for (int i = 0; i < N; i++) {
        bool is_celebrity = true;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                if (knows[i][j] == 1 || knows[j][i] == 0) {
                    is_celebrity = false;
                    break;
                }
            }
        }
        if (is_celebrity) {
            celebrity = i;
            result = "Celebrity found: " + std::to_string(i);
            return true;
        }
    }
    result = "No celebrity found.";
    return false;
}

bool find_celebrity_ON(const std::vector<std::vector<int>>& knows, int& celebrity, std::string& result) {           // O(N) algoritmus, prejde vsetkych N ludi len raz, a porovna ich s ostatnymi N-1 ludmi, ci su celebrity alebo nie. Najprv sa najde kandidat na celebrity, a potom sa overi ci je to celebrity alebo nie.
    int N = knows.size();
    int candidate = 0;
    for (int i =0; i < N; i++) {
        if (knows[candidate][i] == 1) {
            candidate = i;
        }
    }
    for (int i = 0; i < N; i++) {
        if (i != candidate) {
            if (knows[candidate][i] == 1) {
                result = "No celebrity found.";
                return false;
            }
        
            if (knows[i][candidate] == 0) {
                result = "No celebrity found.";
                return false;
            }
        }
    }
    celebrity = candidate;
    result = "Celebrity found: " + std::to_string(candidate);
    return true;
}

int main() {

    std::vector<std::vector<int>> knows = read_lines("party.txt");
    print_matrix(knows);
    int celebrity;
    std::string result;
    if (find_celebrity_ON(knows, celebrity, result)) {
        std::cout << result << std::endl;
    } else {
        std::cout << result << std::endl;
    }
    return 0;
}

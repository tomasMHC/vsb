#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

static bool is_number_token(const std::string& tok, double& out) {
    // Skús parse cez stod a skontroluj, že sa spotreboval celý token
    try {
        size_t pos = 0;
        out = std::stod(tok, &pos);
        return pos == tok.size(); // žiadny zvyšok
    } catch (...) {
        return false;
    }
}

bool evaluate_rpn(const std::string& line, double& result, std::string& err) {
    std::istringstream iss(line);
    std::stack<double> st;
    std::string tok;

    while (iss >> tok) {
        double val;
        if (is_number_token(tok, val)) {
            st.push(val);
            continue;
        }

        if (tok.size() == 1) {
            char op = tok[0];
            if (op == '+' || op == '-' || op == '*' || op == '/') {
                if (st.size() < 2) {
                    err = "Nedostatok operandov pre operator '" + tok + "'";
                    return false;
                }
                double b = st.top(); st.pop(); // pravý operand
                double a = st.top(); st.pop(); // ľavý operand

                double r = 0.0;
                switch (op) {
                    case '+': r = a + b; break;
                    case '-': r = a - b; break;
                    case '*': r = a * b; break;
                    case '/':
                        if (b == 0.0) {
                            err = "Delenie nulou";
                            return false;
                        }
                        r = a / b; break;
                }
                st.push(r);
                continue;
            }
        }

        err = "Neznamy alebo neplatny token: '" + tok + "'";
        return false;
    }

    if (st.size() != 1) {
        if (st.empty()) err = "Prazdny vyraz alebo chyba operandov/operatorov";
        else            err = "Prilis vela operandov (na zasobniku je " + std::to_string(st.size()) + ")";
        return false;
    }

    result = st.top();
    return true;
}

int main() {
    std::string line;
    while (true) {
        std::cout << "Zadaj post-fix vyraz (alebo 'quit'): ";
        if (!std::getline(std::cin, line)) break;
        if (line == "quit") break;

        double res = 0.0;
        std::string err;
        if (evaluate_rpn(line, res, err)) {
            std::cout << "Vysledok: " << res << "\n";
        } else {
            std::cout << "Chyba: " << err << "\n";
        }
    }
}
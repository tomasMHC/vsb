#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>

class State {
public:
    bool prevoznik;
    bool vlk;
    bool koza;
    bool zeli;

    State(bool p, bool v, bool k, bool z)
        : prevoznik(p), vlk(v), koza(k), zeli(z) {}

    bool isValid() const;
    bool isGoal() const;
    std::string toString() const;
};

bool State::isValid() const
{
    if (vlk == koza && prevoznik != vlk)
        return false;

    if (koza == zeli && prevoznik != koza)
        return false;

    return true;
}
bool State::isGoal() const
{
    return prevoznik &&
           vlk &&
           koza &&
           zeli;
}

#include <vector>

class Graph
{
private:
    std::vector<State> states;
    std::vector<std::vector<int>> adj;

public:
    Graph();
    void bfs(int start);
};

Graph::Graph()
{
    for(int p=0; p<2; ++p)
    for(int v=0; v<2; ++v)
    for(int k=0; k<2; ++k)
    for(int z=0; z<2; ++z) {
        State s(p,v,k,z);

        if(s.isValid())
            states.push_back(s);
    }

    adj.resize(states.size());

    for(size_t i=0;i<states.size();++i)
    {
        for(size_t j=0;j<states.size();++j)
        {
            if(i!=j)
            {
                // determine whether move i->j is legal
            }
        }
    }
}
#include <queue>

void Graph::bfs(int start)
{
    std::vector<bool> visited(states.size(), false);
    std::vector<int> parent(states.size(), -1);

    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        if(states[u].isGoal())
        {
            std::vector<int> path;

            for(int v=u; v!=-1; v=parent[v])
                path.push_back(v);

            std::reverse(path.begin(), path.end());

            std::cout << "Solution:\n";

            for(int idx : path)
                std::cout << states[idx].toString() << '\n';

            return;
        }

        for(int v : adj[u])
        {
            if(!visited[v])
            {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}


int main() {

    return 0;
}


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

class State {
public:
    bool farmer;
    bool wolf;
    bool goat;
    bool cabbage;

    State(bool f = 0, bool w = 0, bool g = 0, bool c = 0)
        : farmer(f), wolf(w), goat(g), cabbage(c) {}

    bool isValid() const {
        // Wolf eats goat
        if (wolf == goat && farmer != wolf)
            return false;

        // Goat eats cabbage
        if (goat == cabbage && farmer != goat)
            return false;

        return true;
    }

    bool isGoal() const {
        return farmer && wolf && goat && cabbage;
    }

    string toString() const {
        auto side = bool x {
            return x ? "R" : "L";
        };

        return "F:" + side(farmer) +
               " W:" + side(wolf) +
               " G:" + side(goat) +
               " C:" + side(cabbage);
    }

    bool operator==(const State& other) const {
        return farmer == other.farmer &&
               wolf == other.wolf &&
               goat == other.goat &&
               cabbage == other.cabbage;
    }
};

class Graph {
private:
    vector<State> states;
    vector<vector<int>> adj;

    bool isMove(const State& a, const State& b) {
        // Farmer must move
        if (a.farmer == b.farmer)
            return false;

        int diff = 0;

        if (a.wolf != b.wolf) diff++;
        if (a.goat != b.goat) diff++;
        if (a.cabbage != b.cabbage) diff++;

        // Farmer can take at most one item
        if (diff > 1)
            return false;

        // If wolf moved, it must be with farmer
        if (a.wolf != b.wolf && a.wolf != a.farmer)
            return false;

        // If goat moved, it must be with farmer
        if (a.goat != b.goat && a.goat != a.farmer)
            return false;

        // If cabbage moved, it must be with farmer
        if (a.cabbage != b.cabbage && a.cabbage != a.farmer)
            return false;

        return b.isValid();
    }

public:
    Graph() {
        // Generate all valid states
        for (int f = 0; f < 2; f++)
            for (int w = 0; w < 2; w++)
                for (int g = 0; g < 2; g++)
                    for (int c = 0; c < 2; c++) {
                        State s(f, w, g, c);

                        if (s.isValid())
                            states.push_back(s);
                    }

        adj.resize(states.size());

        // Create edges
        for (size_t i = 0; i < states.size(); i++) {
            for (size_t j = 0; j < states.size(); j++) {

                if (i == j)
                    continue;

                if (isMove(states[i], states[j]))
                    adj[i].push_back(j);
            }
        }
    }

    void printStates() const {
        cout << "Valid states:\n";
        for (size_t i = 0; i < states.size(); i++) {
            cout << i << ": "
                 << states[i].toString()
                 << '\n';
        }
    }

    void solve() {
        int start = -1;

        for (size_t i = 0; i < states.size(); i++) {
            if (states[i] == State(0, 0, 0, 0)) {
                start = static_cast<int>(i);
                break;
            }
        }

        if (start == -1) {
            cout << "Start state not found.\n";
            return;
        }

        vector<bool> visited(states.size(), false);
        vector<int> parent(states.size(), -1);

        queue<int> q;

        visited[start] = true;
        q.push(start);

        int goal = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (states[u].isGoal()) {
                goal = u;
                break;
            }

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        if (goal == -1) {
            cout << "No solution found.\n";
            return;
        }

        vector<int> path;

        for (int v = goal; v != -1; v = parent[v])
            path.push_back(v);

        reverse(path.begin(), path.end());

        cout << "\nSolution:\n\n";

        for (size_t i = 0; i < path.size(); i++) {
            cout << "Step " << i << ": "
                 << states[path[i]].toString()
                 << '\n';
        }
    }
};

int main() {
    Graph graph;

    graph.solve();

    return 0;
}
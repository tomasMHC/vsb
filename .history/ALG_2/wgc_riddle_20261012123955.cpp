#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

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

std::string State::toString() const
{
    return "Prevoznik: " + std::to_string(prevoznik) +
           ", Vlk: " + std::to_string(vlk) +
           ", Koza: " + std::to_string(koza) +
           ", Zeli: " + std::to_string(zeli);
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
    Graph graph;
    

    return 0;
}



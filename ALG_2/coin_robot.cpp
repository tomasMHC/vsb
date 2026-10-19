#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> robotCoinCollection(const vector<vector<int>>& C)
{
    int n = C.size();
    int m = C[0].size();

    // F[i][j] = maximum number of coins
    // that can be collected when reaching cell (i,j)
    vector<vector<int>> F(n, vector<int>(m, 0));

    // Starting cell
    F[0][0] = C[0][0];

    // First row - robot can only come from the left
    for (int j = 1; j < m; ++j)
    {
        F[0][j] = F[0][j - 1] + C[0][j];
    }

    // Remaining rows
    for (int i = 1; i < n; ++i)
    {
        // First column - robot can only come from above
        F[i][0] = F[i - 1][0] + C[i][0];

        for (int j = 1; j < m; ++j)
        {
            F[i][j] =
                max(F[i - 1][j], F[i][j - 1]) + C[i][j];
        }
    }

    return F;
}

void printPath(const vector<vector<int>>& C, const vector<vector<int>>& F)
{
    int n = C.size();
    int m = C[0].size();
    int i = n - 1;
    int j = m - 1;

    vector<pair<int, int>> path;

    while (i > 0 || j > 0)
    {
        path.push_back({i, j});

        if (i == 0)
            --j;
        else if (j == 0)
            --i;
        else if (F[i - 1][j] > F[i][j - 1])
            --i;
        else
            --j;
    }

    path.push_back({0, 0});
    reverse(path.begin(), path.end());

    std::cout << "Path taken by the robot:\n";
    for (const auto& p : path)
    {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }
}

int main()
{
    vector<vector<int>> C = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 1, 1}
    };
    vector<vector<int>> F = robotCoinCollection(C);
    // cout << "Maximum number of coins: "
    //      << robotCoinCollection(C)
    //      << endl;
    //Maximum number of coins collected
    std::cout << "Maximum number of coins collected: " << F[C.size() - 1][C[0].size() - 1] << std::endl;
    // Print the path taken by the robot
    printPath(C, F);
    return 0;
}

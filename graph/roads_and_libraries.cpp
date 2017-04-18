#include <vector>
#include <iostream>

using namespace std;

/* 2
 * 3 3 2 1
 * 1 2
 * 3 1
 * 2 3
 * 6 6 2 5
 * 1 3
 * 3 4
 * 2 4
 * 1 2
 * 2 3
 * 5 6 */

int DFS(vector<int>& city, vector<bool>& visited) {
    int count = 0;
    for (int i = 0; i < city.size(); i++) {
        if(visited[i] == false) {
            visited[i] = true;
            count++;
        }
    }

    return count;
}

int DFSAll(vector<vector<int>>& cities, vector<bool>& visited, int library_cost, int road_cost) {
    int cost = 0;
    for (int i = 1; i < cities.size(); i++) {
        if (visited[i] == false) {
            visited[i] = true;
            cost += library_cost;
            cost += DFS(cities[i], visited)*road_cost;
        }
    }
}

int main() {
    int q;
    cin >> q;

    int n, e, lc, rc;
    cin >> n >> e >> lc >> rc;

    vector<vector<int>> cities(n+1, vector<int>());

    for (int i = 0; i < e; i++) {
        int n1, n2;
        cin >> n1 >> n2;

        cities[n1].push_back(n2);
        cities[n2].push_back(n1);
    }

    vector<bool> visited(n+1, false);

    int cost = DFSAll(cities, visited, lc, rc);
    int max_cost = min(cost, n*lc);

    cout << max_cost;
}

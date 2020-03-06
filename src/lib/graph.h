#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph {
public:
    Graph(map<int, set<int>> &vertices) : v_(vertices){};

    map<int, set<int>> v_;
    
    vector<int> dfs(int root);
    vector<int> dfs_all();

    void FloydWarshall(unordered_map<int, unordered_map<int, int>> &map, int n);
    unordered_map<int, int> BFS_Distance(int root, unordered_map<int, unordered_set<int>> &map);
    unordered_map<int, vector<int>> BFS_Path(int root, unordered_map<int, unordered_set<int>> &map);

    vector<int> TopologicalSort();
    vector<bool> shortestPathPassThrough(unordered_map<int, unordered_set<int>> &graph, int n);

private:
    void printMatrix(vector<vector<int>> &vec);
};

#endif
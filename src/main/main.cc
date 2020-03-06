#include <iostream>
#include "src/lib/solution.h"
#include "src/lib/graph.h"
#include <unordered_map>
#include <map>
#include <set>

using namespace std;

int main()
{
    Solution solution ;
    std::cout << solution.PrintHelloWorld() << std::endl;

    //Q2*************************************************************************************************************************
    map<int, set<int>> map3;
    Graph g(map3);
    unordered_map<int, unordered_map<int, int>> map0{
        {1, {{2, 10}, {5, 100}}},
        {2, {{3, 50}}},
        {3, {{5, 10}}},
        {4, {{3, 20}, {5, 60}}}
    };
    g.FloydWarshall(map0, 6);

    //Q3*************************************************************************************************************************
    unordered_map<int, unordered_set<int>> map1{
        {0, {1,2,5}},
        {1, {0,2,3}},
        {2, {0,1,3}},
        {3, {1,2,4,6}},
        {4, {3}},
        {5, {0}},
        {6, {3}}
    };

    unordered_map<int, int> res = g.BFS_Distance(0, map1);
    cout << "Shortest Distances: {";
    for (auto u : res) cout << "(" << u.first << "," << u.second << ")" << ", ";
    cout << "}" << endl;

    unordered_map<int, vector<int>> res1 = g.BFS_Path(0, map1);
    cout << "Shortest Paths: {";
    for (auto u : res1) {
        cout << "(" << u.first << ", [";
        for (auto num : u.second) {
            cout << num;
            if (num != u.first) cout << ",";
        }
        cout << "]) ";
    }
    cout << "}" << endl;

    //Q4*************************************************************************************************************************
    map<int, set<int>> map2 {
        {7, {5, 6}},
        {1, {0}},
        {2, {1}},
        {3, {1}},
        {5, {2,4}},
        {6, {3,4}}
    };
    Graph graph(map2);
    vector<int> topores = graph.TopologicalSort();
    for (int i : topores) {
        cout << i << " ";
    }
    cout << endl;

    //Q5*************************************************************************************************************************
    unordered_map<int, unordered_set<int>> map4 {
        {0, {1,4,5}},
        {1, {0,2,3}},
        {2, {1,3,8}},
        {3, {1,2}},
        {4, {0}},
        {5, {0,6}},
        {6, {5,7,8}},
        {7, {6,8}},
        {8, {2,6,7}},
    };
    vector<bool> vecBool = graph.shortestPathPassThrough(map4, 9);
    for (bool b : vecBool) cout << b << " ";
    cout << endl;
    return EXIT_SUCCESS;
}
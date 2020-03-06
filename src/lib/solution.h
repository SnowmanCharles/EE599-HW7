#ifndef TEMPLATE_SOLUTION_H
#define TEMPLATE_SOLUTION_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
  string PrintHelloWorld();
  void FloydWarshall(unordered_map<int, unordered_map<int, int>> &map, int n);
  unordered_map<int, int> BFS_Distance(int root, unordered_map<int, unordered_set<int>> &map);
  unordered_map<int, vector<int>> BFS_Path(int root, unordered_map<int, unordered_set<int>> &map);

private:
  void printMatrix(vector<vector<int>> &vec);

};

#endif
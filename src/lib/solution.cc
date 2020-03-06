#include "solution.h"
#include <unordered_map>
#include <unordered_set>
#include "iostream"
#include <queue>

using namespace std;

string Solution::PrintHelloWorld() { 
  return "**** Hello World ****"; 
}

void Solution::FloydWarshall(unordered_map<int, unordered_map<int, int>> &map, int n) {//O(n ^ 3)
  vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (i == j) dp[i][j] = 0;
        else dp[i][j] = -1;
    }
  }
  for (auto p1 : map) {
    for (auto p2 : p1.second) {
      dp[p1.first][p2.first] = p2.second;
    }
  }

  for (int k = 0; k < n; k++) {
    cout << endl;
    //for (int i = 0; i < n; i++) cout << i << "  ";
    //cout << endl;
    for (int i = 0; i < n; i++) {
      //cout << i << " ";
      for (int j = 0; j < n; j++) {
        if (dp[i][k] == -1 || dp[k][j] == -1) {
          cout << dp[i][j] << "  ";
          continue;
        }
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
        cout << dp[i][j] << "  ";
      }
      cout << endl;
    }
  }
}

unordered_map<int, int> Solution::BFS_Distance(int root, unordered_map<int, unordered_set<int>> &map) {//O(m + n)
  unordered_map<int, int> mark;
  unordered_map<int, int> res;
  queue<int> q;
  q.push(root);
  mark[root] = 1;
  int dis = 0;
  while (!q.empty()) {
    int size = q.size();
    while (size-- > 0) {
      int cur = q.front();
      q.pop();
      res[cur] = dis;
      for (auto &next : map[cur]) {
        if (!mark[next]) {
          mark[next] = 1;
          q.push(next);
        }
      }
    }
    dis++;
  }
  return res;
}

unordered_map<int, vector<int>> Solution::BFS_Path(int root, unordered_map<int, unordered_set<int>> &map) {//O(n^2 + m)
  unordered_map<int, int> mark;
  unordered_map<int, vector<int>> res;
  unordered_map<int, int> pre;
  queue<int> q;
  q.push(root);
  mark[root] = 1;
  pre[root] = root;
  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (auto &next : map[cur]) {
      if (!mark[next]) {
        mark[next] = 1;
        pre[next] = cur;
        q.push(next);
      }
    }
  }
  for (auto p : mark) {
    vector<int> temp;
    res[p.first] = temp;
    int cur = p.first;
    res[p.first].push_back(cur);
    while (pre[cur] != cur) {
      cur = pre[cur];
      res[p.first].push_back(cur);
    }
    reverse(res[p.first].begin(), res[p.first].end());
  }
  return res;
}

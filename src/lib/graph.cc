#include "graph.h"
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "iostream"

using namespace std;

vector<int> Graph::dfs(int root) {  //O(n + m)
    vector<int> res;
    stack<int> s;
    unordered_set<int> visited;
    s.push(root);
    while (!s.empty()) {
        root = s.top();
        s.pop();
        if (visited.count(root) < 1) {
            res.push_back(root);
            visited.insert(root);
        }
        for (auto i = v_[root].begin(); i != v_[root].end(); i++) {
            if (visited.count(*i) < 1) {
                s.push(*i);
            }
        }
    }
    return res;
}

vector<int> Graph::dfs_all() {  //O(m + n)
    unordered_set<int> set;
    for (auto pair : v_) {
        set.insert(pair.first);
        for (int i : pair.second) {
            set.insert(i);
        }
    }
    vector<int> res;
    stack<int> s;
    unordered_set<int> visited;
    for (int cur : set) {
        if (visited.count(cur) >= 1) continue;
        s.push(cur);
        while (!s.empty()) {
            int next = s.top();
            s.pop();
            if (visited.count(next) < 1) {
                res.push_back(next);
                visited.insert(next);
            }
            for (auto i = v_[next].begin(); i != v_[next].end(); i++) {
                if (visited.count(*i) < 1) {
                    s.push(*i);
                }
            }
        }
    }
    return res;
}


//Q2*************************************************************************************************************************
void Graph::FloydWarshall(unordered_map<int, unordered_map<int, int>> &map, int n) {  //O(n ^ 3)
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

//Q3*************************************************************************************************************************
unordered_map<int, int> Graph::BFS_Distance(int root, unordered_map<int, unordered_set<int>> &map) {//O(m + n)
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

unordered_map<int, vector<int>> Graph::BFS_Path(int root, unordered_map<int, unordered_set<int>> &map) {//O(n^2 + m)
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

//Q4*************************************************************************************************************************
vector<int> Graph::TopologicalSort() {//O(nlog(n) + m)
    unordered_map<int, int> indegree;
    for (auto p : v_) {
        if (indegree.count(p.first) == 0) indegree[p.first] = 0;
        for (int num : p.second) {
            if (indegree.count(num) == 0) {
                indegree[num] = 0;
            }
            indegree[num]++;
        }
    }

    unordered_map<int, int> visited;
    queue<int> q;
    for (auto p : indegree) {
        if (p.second == 0) {
            q.push(p.first);
            visited[p.first] = 1;
        }
    }

    vector<int> res;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        res.push_back(cur);
        for (int next : v_[cur]) {
            indegree[next]--;
            if (!visited[next] && indegree[next] == 0) {
                visited[next] = 1;
                q.push(next);
            }
        }
    }
    return res;
}


//Q5*************************************************************************************************************************
vector<bool> Graph::shortestPathPassThrough(unordered_map<int, unordered_set<int>> &graph, int n) {//O(n)
    vector<bool> res(n, false);
    unordered_map<int, int> dis1 = BFS_Distance(0, graph);
    unordered_map<int, int> dis2 = BFS_Distance(n-1, graph);
    if (dis1.count(n - 1) == 0) return res;
    int d = dis1[n-1];
    for (int i = 0; i < n; i++) {
        if (dis1.count(i) == 0 || dis2.count(i) == 0) continue;
        if (dis1[i] + dis2[i] == d) res[i] = true;
    }
    return res;
}
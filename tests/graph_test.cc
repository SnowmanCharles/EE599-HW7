#include "src/lib/graph.h"
#include "gtest/gtest.h"
#include <vector>

using namespace std;

TEST(GraphDFS, GraphDFS) {
  map<int, set<int>> v{
      {1, {2, 3}},
      {2, {1, 3, 4, 5}},
      {3, {1, 2, 4}},
      {4, {2, 3, 4}}
  };
  Graph g(v);
  vector<int> res = {1, 3, 4, 2, 5};
  vector<int> actual = g.dfs(1);
  for (int i = 0; i < actual.size(); i++) {
      EXPECT_EQ(res[i], actual[i]);
  }
}

TEST(GraphDFS_ALL, GraphDFS_ALL) {
  map<int, set<int>> v{
      {1, {2, 3}},
      {2, {1, 3, 4, 5}},
      {3, {1, 2, 4}},
      {4, {2, 3, 4}},
      {6, {5, 4}}
  };
  Graph g(v);
  vector<int> res = {6, 5, 4, 3, 2, 1};
  vector<int> actual = g.dfs_all();
  for (int i = 0; i < actual.size(); i++) {
      EXPECT_EQ(res[i], actual[i]);
  }
}
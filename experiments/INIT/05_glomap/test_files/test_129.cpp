// File: tree_test_129.cc

#include <gtest/gtest.h>

#include <utility>
#include <vector>

namespace glomap {

// Forward declaration of the function under test.
// In the real project, this would typically come from a header file.
int BFS(const std::vector<std::vector<int>>& graph,
        int root,
        std::vector<int>& parents,
        std::vector<std::pair<int, int>> banned_edges);

}  // namespace glomap

// -------------------------
// Test cases for glomap::BFS
// -------------------------

// Normal operation: connected graph with no banned edges.
TEST(BFSTest_129, FullTraversalWithoutBannedEdges_129) {
  // Graph:
  // 0 -- 1
  // |    |
  // 2 -- 3
  //
  // adjacency list (undirected):
  // 0: 1,2
  // 1: 0,3
  // 2: 0,3
  // 3: 1,2
  std::vector<std::vector<int>> graph = {
      {1, 2},  // 0
      {0, 3},  // 1
      {0, 3},  // 2
      {1, 2}   // 3
  };

  std::vector<int> parents(10, 42);  // pre-filled junk to verify clear/resize
  std::vector<std::pair<int, int>> banned_edges;  // empty

  int root = 0;
  int counter = glomap::BFS(graph, root, parents, banned_edges);

  // All 4 vertices reachable from root, so counter should be 3.
  EXPECT_EQ(counter, 3);

  ASSERT_EQ(parents.size(), 4u);
  EXPECT_EQ(parents[0], 0);  // root is parent of itself
  EXPECT_EQ(parents[1], 0);
  EXPECT_EQ(parents[2], 0);
  EXPECT_EQ(parents[3], 1);  // discovered from vertex 1 in this BFS order
}

// Boundary condition: single-vertex graph.
TEST(BFSTest_129, SingleVertexGraph_129) {
  std::vector<std::vector<int>> graph = {
      {}  // vertex 0 with no neighbors
  };

  std::vector<int> parents;
  std::vector<std::pair<int, int>> banned_edges;

  int root = 0;
  int counter = glomap::BFS(graph, root, parents, banned_edges);

  // Only the root exists and is already "visited"; BFS does not discover
  // any new vertex, so counter should be 0.
  EXPECT_EQ(counter, 0);

  ASSERT_EQ(parents.size(), 1u);
  EXPECT_EQ(parents[0], 0);
}

// Disconnected graph: BFS should only visit the root's component.
TEST(BFSTest_129, DisconnectedGraph_VisitsOnlyComponent_129) {
  // Graph:
  // Component 1: 0 -- 1
  // Component 2: 2 -- 3
  std::vector<std::vector<int>> graph = {
      {1},     // 0
      {0},     // 1
      {3},     // 2
      {2}      // 3
  };

  std::vector<int> parents;
  std::vector<std::pair<int, int>> banned_edges;

  int root = 2;  // start in second component
  int counter = glomap::BFS(graph, root, parents, banned_edges);

  // From root 2, we can discover only vertex 3.
  EXPECT_EQ(counter, 1);

  ASSERT_EQ(parents.size(), 4u);
  EXPECT_EQ(parents[2], 2);   // root
  EXPECT_EQ(parents[3], 2);   // reached from 2
  EXPECT_EQ(parents[0], -1);  // unreachable from root
  EXPECT_EQ(parents[1], -1);  // unreachable from root
}

// Banned edge (u, v) must prevent traversal along that edge.
TEST(BFSTest_129, BannedEdgeBlocksTraversal_129) {
  // Graph: 0 -- 1 -- 2 (line)
  std::vector<std::vector<int>> graph = {
      {1},     // 0
      {0, 2},  // 1
      {1}      // 2
  };

  std::vector<int> parents;
  std::vector<std::pair<int, int>> banned_edges = {
      {1, 2}  // ban edge (1,2)
  };

  int root = 0;
  int counter = glomap::BFS(graph, root, parents, banned_edges);

  // Without bans, BFS from 0 would discover vertices 1 and 2 => counter 2.
  // With edge (1,2) banned, vertex 2 should be unreachable => counter 1.
  EXPECT_EQ(counter, 1);

  ASSERT_EQ(parents.size(), 3u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
  EXPECT_EQ(parents[2], -1);  // not reached due to banned edge
}

// Banned edge in reversed order (v, u) must also be treated as banned.
TEST(BFSTest_129, BannedEdgeIsUndirected_129) {
  // Same graph: 0 -- 1 -- 2
  std::vector<std::vector<int>> graph = {
      {1},     // 0
      {0, 2},  // 1
      {1}      // 2
  };

  std::vector<int> parents;
  // Only (2,1) is listed, but the BFS should treat this as an undirected ban.
  std::vector<std::pair<int, int>> banned_edges = {
      {2, 1}
  };

  int root = 0;
  int counter = glomap::BFS(graph, root, parents, banned_edges);

  // Same behavior as banning (1,2).
  EXPECT_EQ(counter, 1);

  ASSERT_EQ(parents.size(), 3u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
  EXPECT_EQ(parents[2], -1);
}

// Banned edge not present in the graph should have no effect.
TEST(BFSTest_129, BannedEdgeNotInGraphHasNoEffect_129) {
  // Graph: 0 -- 1
  std::vector<std::vector<int>> graph = {
      {1},  // 0
      {0}   // 1
  };

  std::vector<int> parents;
  // Ban an edge that doesn't exist in the adjacency list.
  std::vector<std::pair<int, int>> banned_edges = {
      {1, 2}  // vertex 2 is not even in the graph
  };

  int root = 0;
  int counter = glomap::BFS(graph, root, parents, banned_edges);

  // BFS should behave as if there were no ban: discover vertex 1.
  EXPECT_EQ(counter, 1);

  ASSERT_EQ(parents.size(), 2u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
}

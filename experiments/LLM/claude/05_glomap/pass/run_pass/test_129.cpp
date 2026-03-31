#include <gtest/gtest.h>
#include <vector>
#include <utility>

// Forward declaration of the BFS function from glomap namespace
namespace glomap {
int BFS(const std::vector<std::vector<int>>& graph,
        int root,
        std::vector<int>& parents,
        std::vector<std::pair<int, int>> banned_edges = {});
}

class BFSTest_129 : public ::testing::Test {
 protected:
  std::vector<int> parents;
};

// Test BFS on a single node graph
TEST_F(BFSTest_129, SingleNodeGraph_129) {
  std::vector<std::vector<int>> graph = {{}};
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 0);
  ASSERT_EQ(parents.size(), 1u);
  EXPECT_EQ(parents[0], 0);  // root's parent is itself
}

// Test BFS on a simple two-node graph
TEST_F(BFSTest_129, TwoNodeGraph_129) {
  std::vector<std::vector<int>> graph = {{1}, {0}};
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 1);
  ASSERT_EQ(parents.size(), 2u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
}

// Test BFS on a linear chain graph: 0 - 1 - 2 - 3
TEST_F(BFSTest_129, LinearChainGraph_129) {
  std::vector<std::vector<int>> graph = {{1}, {0, 2}, {1, 3}, {2}};
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 3);
  ASSERT_EQ(parents.size(), 4u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
  EXPECT_EQ(parents[2], 1);
  EXPECT_EQ(parents[3], 2);
}

// Test BFS from a non-zero root
TEST_F(BFSTest_129, NonZeroRoot_129) {
  std::vector<std::vector<int>> graph = {{1}, {0, 2}, {1, 3}, {2}};
  int count = glomap::BFS(graph, 2, parents, {});
  EXPECT_EQ(count, 3);
  ASSERT_EQ(parents.size(), 4u);
  EXPECT_EQ(parents[2], 2);  // root
  EXPECT_EQ(parents[1], 2);
  EXPECT_EQ(parents[3], 2);
  EXPECT_EQ(parents[0], 1);
}

// Test BFS on a disconnected graph
TEST_F(BFSTest_129, DisconnectedGraph_129) {
  // Two components: {0,1} and {2,3}
  std::vector<std::vector<int>> graph = {{1}, {0}, {3}, {2}};
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 1);
  ASSERT_EQ(parents.size(), 4u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
  EXPECT_EQ(parents[2], -1);  // unreachable
  EXPECT_EQ(parents[3], -1);  // unreachable
}

// Test BFS with banned edges - banning the only connection
TEST_F(BFSTest_129, BannedEdgeBlocksTraversal_129) {
  std::vector<std::vector<int>> graph = {{1}, {0}};
  std::vector<std::pair<int, int>> banned = {{0, 1}};
  int count = glomap::BFS(graph, 0, parents, banned);
  EXPECT_EQ(count, 0);
  ASSERT_EQ(parents.size(), 2u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], -1);  // unreachable due to ban
}

// Test BFS with banned edges in reverse direction
TEST_F(BFSTest_129, BannedEdgeReverseDirection_129) {
  std::vector<std::vector<int>> graph = {{1}, {0}};
  std::vector<std::pair<int, int>> banned = {{1, 0}};
  int count = glomap::BFS(graph, 0, parents, banned);
  EXPECT_EQ(count, 0);
  ASSERT_EQ(parents.size(), 2u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], -1);  // unreachable due to ban (reverse also checked)
}

// Test BFS with banned edge that doesn't affect connectivity
TEST_F(BFSTest_129, BannedEdgeAlternatePathExists_129) {
  // Triangle graph: 0-1, 1-2, 0-2
  std::vector<std::vector<int>> graph = {{1, 2}, {0, 2}, {0, 1}};
  std::vector<std::pair<int, int>> banned = {{0, 1}};
  int count = glomap::BFS(graph, 0, parents, banned);
  EXPECT_EQ(count, 2);
  ASSERT_EQ(parents.size(), 3u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[2], 0);
  // Node 1 should be reached via node 2
  EXPECT_EQ(parents[1], 2);
}

// Test BFS with multiple banned edges
TEST_F(BFSTest_129, MultipleBannedEdges_129) {
  // Complete graph on 4 vertices
  std::vector<std::vector<int>> graph = {
      {1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
  std::vector<std::pair<int, int>> banned = {{0, 1}, {0, 2}, {0, 3}};
  int count = glomap::BFS(graph, 0, parents, banned);
  EXPECT_EQ(count, 0);
  ASSERT_EQ(parents.size(), 4u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], -1);
  EXPECT_EQ(parents[2], -1);
  EXPECT_EQ(parents[3], -1);
}

// Test BFS on a tree structure (star graph)
TEST_F(BFSTest_129, StarGraph_129) {
  // 0 is center, connected to 1, 2, 3, 4
  std::vector<std::vector<int>> graph = {{1, 2, 3, 4}, {0}, {0}, {0}, {0}};
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 4);
  ASSERT_EQ(parents.size(), 5u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
  EXPECT_EQ(parents[2], 0);
  EXPECT_EQ(parents[3], 0);
  EXPECT_EQ(parents[4], 0);
}

// Test BFS overwrites previously populated parents vector
TEST_F(BFSTest_129, ParentsVectorIsCleared_129) {
  parents = {99, 88, 77};  // pre-populate with garbage
  std::vector<std::vector<int>> graph = {{1}, {0}};
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 1);
  ASSERT_EQ(parents.size(), 2u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
}

// Test BFS on a cycle graph
TEST_F(BFSTest_129, CycleGraph_129) {
  // 0-1-2-3-0
  std::vector<std::vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {2, 0}};
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 3);
  ASSERT_EQ(parents.size(), 4u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
  EXPECT_EQ(parents[3], 0);
  // Node 2 could be reached from either 1 or 3, both at distance 2
  EXPECT_TRUE(parents[2] == 1 || parents[2] == 3);
}

// Test BFS with empty banned edges vector
TEST_F(BFSTest_129, EmptyBannedEdges_129) {
  std::vector<std::vector<int>> graph = {{1, 2}, {0}, {0}};
  std::vector<std::pair<int, int>> banned;
  int count = glomap::BFS(graph, 0, parents, banned);
  EXPECT_EQ(count, 2);
  ASSERT_EQ(parents.size(), 3u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
  EXPECT_EQ(parents[2], 0);
}

// Test BFS on a larger binary tree structure
TEST_F(BFSTest_129, BinaryTreeGraph_129) {
  //        0
  //       / \
  //      1   2
  //     / \ / \
  //    3  4 5  6
  std::vector<std::vector<int>> graph = {
      {1, 2},     // 0
      {0, 3, 4},  // 1
      {0, 5, 6},  // 2
      {1},        // 3
      {1},        // 4
      {2},        // 5
      {2}         // 6
  };
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 6);
  ASSERT_EQ(parents.size(), 7u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
  EXPECT_EQ(parents[2], 0);
  EXPECT_EQ(parents[3], 1);
  EXPECT_EQ(parents[4], 1);
  EXPECT_EQ(parents[5], 2);
  EXPECT_EQ(parents[6], 2);
}

// Test BFS return value equals number of nodes visited (excluding root)
TEST_F(BFSTest_129, ReturnValueIsVisitedCountMinusRoot_129) {
  std::vector<std::vector<int>> graph = {{1}, {0, 2}, {1}};
  int count = glomap::BFS(graph, 1, parents, {});
  // Root is 1, visits 0 and 2 => count = 2
  EXPECT_EQ(count, 2);
}

// Test BFS with self-loop in the graph (node connected to itself)
TEST_F(BFSTest_129, SelfLoopGraph_129) {
  std::vector<std::vector<int>> graph = {{0, 1}, {0}};
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 1);
  ASSERT_EQ(parents.size(), 2u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
}

// Test BFS banning an edge that is a self-loop
TEST_F(BFSTest_129, BannedSelfLoop_129) {
  std::vector<std::vector<int>> graph = {{0, 1}, {0}};
  std::vector<std::pair<int, int>> banned = {{0, 0}};
  int count = glomap::BFS(graph, 0, parents, banned);
  EXPECT_EQ(count, 1);
  ASSERT_EQ(parents.size(), 2u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], 0);
}

// Test BFS with isolated node as root
TEST_F(BFSTest_129, IsolatedNodeRoot_129) {
  std::vector<std::vector<int>> graph = {{}, {2}, {1}};
  int count = glomap::BFS(graph, 0, parents, {});
  EXPECT_EQ(count, 0);
  ASSERT_EQ(parents.size(), 3u);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[1], -1);
  EXPECT_EQ(parents[2], -1);
}

// Test BFS banning partial edges still allows other paths
TEST_F(BFSTest_129, PartialBanStillConnected_129) {
  // Graph: 0-1, 0-2, 1-2
  std::vector<std::vector<int>> graph = {{1, 2}, {0, 2}, {0, 1}};
  // Ban edge 0-1, node 1 should still be reachable via 2
  std::vector<std::pair<int, int>> banned = {{0, 1}};
  int count = glomap::BFS(graph, 0, parents, banned);
  EXPECT_EQ(count, 2);
  EXPECT_EQ(parents[0], 0);
  EXPECT_EQ(parents[2], 0);
  EXPECT_EQ(parents[1], 2);
}

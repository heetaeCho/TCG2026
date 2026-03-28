// File: tree_test_60.cc

#include <gtest/gtest.h>

#include <utility>
#include <vector>

// Adjust this include if the actual header path is different.
#include "glomap/math/tree.h"

class BFSTest_60 : public ::testing::Test {
protected:
  using Graph = std::vector<std::vector<int>>;

  static void ExpectParentsEqual(const std::vector<int>& parents,
                                 const std::vector<int>& expected) {
    ASSERT_EQ(parents.size(), expected.size())
        << "Parent vector size mismatch";
    for (size_t i = 0; i < expected.size(); ++i) {
      EXPECT_EQ(parents[i], expected[i]) << "Mismatch at index " << i;
    }
  }
};

// Normal operation: single-vertex graph, no edges.
TEST_F(BFSTest_60, SingleVertexGraph_60) {
  Graph graph(1);  // vertex 0, no neighbors
  std::vector<int> parents;
  std::vector<std::pair<int, int>> banned_edges;

  int counter = glomap::BFS(graph, /*root=*/0, parents, banned_edges);

  EXPECT_EQ(counter, 0);                // No new vertices discovered
  ASSERT_EQ(parents.size(), 1u);
  EXPECT_EQ(parents[0], 0);             // Root is its own parent
}

// Normal operation: simple chain with no banned edges.
TEST_F(BFSTest_60, SimpleChainNoBannedEdges_60) {
  // 0 -- 1 -- 2 -- 3
  Graph graph(4);
  graph[0] = {1};
  graph[1] = {0, 2};
  graph[2] = {1, 3};
  graph[3] = {2};

  std::vector<int> parents(10, 123);  // pre-filled to check it gets cleared
  std::vector<std::pair<int, int>> banned_edges;

  int counter = glomap::BFS(graph, /*root=*/0, parents, banned_edges);

  // All vertices should be reachable from 0: 3 discoveries (1,2,3)
  EXPECT_EQ(counter, 3);

  std::vector<int> expected_parents = {
      0,  // parent of 0 is itself
      0,  // discovered from 0
      1,  // discovered from 1
      2   // discovered from 2
  };
  ExpectParentsEqual(parents, expected_parents);
}

// Boundary: graph with multiple components; unreachable vertices remain -1.
TEST_F(BFSTest_60, DisconnectedComponents_60) {
  // Component A: 0 -- 1
  // Component B: 2 -- 3 -- 4
  Graph graph(5);
  graph[0] = {1};
  graph[1] = {0};
  graph[2] = {3};
  graph[3] = {2, 4};
  graph[4] = {3};

  std::vector<int> parents;
  std::vector<std::pair<int, int>> banned_edges;

  int counter = glomap::BFS(graph, /*root=*/2, parents, banned_edges);

  // From root 2 we can discover 3 and 4: 2 new vertices
  EXPECT_EQ(counter, 2);

  // Vertices in other component (0,1) should remain -1.
  std::vector<int> expected_parents = {
      -1, // 0 unreachable
      -1, // 1 unreachable
      2,  // root is its own parent
      2,  // discovered from 2
      3   // discovered from 3
  };
  ExpectParentsEqual(parents, expected_parents);
}

// Banned edges prevent traversal: banning (1,2) blocks reaching vertex 2.
TEST_F(BFSTest_60, BannedEdgesPreventTraversal_60) {
  // 0 -- 1 -- 2
  Graph graph(3);
  graph[0] = {1};
  graph[1] = {0, 2};
  graph[2] = {1};

  std::vector<int> parents;
  std::vector<std::pair<int, int>> banned_edges = { {1, 2} };

  int counter = glomap::BFS(graph, /*root=*/0, parents, banned_edges);

  // We can discover 1 from 0, but edge (1,2) is banned, so 2 is unreachable.
  EXPECT_EQ(counter, 1);

  std::vector<int> expected_parents = {
      0,   // root
      0,   // discovered from 0
      -1   // unreachable due to banned edge
  };
  ExpectParentsEqual(parents, expected_parents);
}

// Banned edges are treated as undirected: (2,1) blocks traversal 1 -> 2.
TEST_F(BFSTest_60, BannedEdgesAreUndirected_60) {
  // 0 -- 1 -- 2
  Graph graph(3);
  graph[0] = {1};
  graph[1] = {0, 2};
  graph[2] = {1};

  std::vector<int> parents;
  // Only store (2,1); implementation should also block (1,2).
  std::vector<std::pair<int, int>> banned_edges = { {2, 1} };

  int counter = glomap::BFS(graph, /*root=*/0, parents, banned_edges);

  EXPECT_EQ(counter, 1);  // Only vertex 1 discovered

  std::vector<int> expected_parents = {
      0,   // root
      0,   // discovered from 0
      -1   // blocked due to banned edge (treated as undirected)
  };
  ExpectParentsEqual(parents, expected_parents);
}

// Boundary: ensure parents vector is cleared and resized, and unreachable
// vertices (except root) remain -1.
TEST_F(BFSTest_60, ParentsClearedAndResizedWithUnreachableVertices_60) {
  // 3 vertices, no edges. Root is in the middle.
  Graph graph(3);
  graph[0] = {};
  graph[1] = {};
  graph[2] = {};

  // Pre-fill parents with different size and "junk" values.
  std::vector<int> parents(5, 42);
  std::vector<std::pair<int, int>> banned_edges;

  int counter = glomap::BFS(graph, /*root=*/1, parents, banned_edges);

  // No neighbors from 1, so no additional vertices discovered.
  EXPECT_EQ(counter, 0);

  // parents should be resized to 3 and all non-root entries should be -1.
  ASSERT_EQ(parents.size(), 3u);
  EXPECT_EQ(parents[1], 1);   // root is its own parent
  EXPECT_EQ(parents[0], -1);  // unreachable
  EXPECT_EQ(parents[2], -1);  // unreachable
}

// Exceptional/edge condition: banned edges that do not exist should have no effect.
TEST_F(BFSTest_60, NonExistingBannedEdgesHaveNoEffect_60) {
  // 0 -- 1
  Graph graph(2);
  graph[0] = {1};
  graph[1] = {0};

  std::vector<int> parents;
  // Ban an edge that doesn't exist in the graph (1, 3) for example.
  std::vector<std::pair<int, int>> banned_edges = { {1, 3}, {3, 1} };

  int counter = glomap::BFS(graph, /*root=*/0, parents, banned_edges);

  // Graph is unchanged, we can still discover vertex 1.
  EXPECT_EQ(counter, 1);

  std::vector<int> expected_parents = {
      0,  // root
      0   // discovered from 0
  };
  ExpectParentsEqual(parents, expected_parents);
}

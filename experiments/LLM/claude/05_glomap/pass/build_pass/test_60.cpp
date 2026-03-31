#include <gtest/gtest.h>
#include <vector>
#include <utility>

namespace glomap {
int BFS(const std::vector<std::vector<int>>& graph,
        int root,
        std::vector<int>& parents,
        std::vector<std::pair<int, int>> banned_edges = {});
}

// Test BFS on a single-node graph
TEST(BFSTest_60, SingleNodeGraph_60) {
    std::vector<std::vector<int>> graph = {{}};
    std::vector<int> parents;
    int count = glomap::BFS(graph, 0, parents, {});
    EXPECT_EQ(count, 0);
    ASSERT_EQ(parents.size(), 1u);
    EXPECT_EQ(parents[0], 0);
}

// Test BFS on a simple linear graph: 0-1-2
TEST(BFSTest_60, LinearGraph_60) {
    std::vector<std::vector<int>> graph = {
        {1},    // 0 -> 1
        {0, 2}, // 1 -> 0, 2
        {1}     // 2 -> 1
    };
    std::vector<int> parents;
    int count = glomap::BFS(graph, 0, parents, {});
    EXPECT_EQ(count, 2);
    ASSERT_EQ(parents.size(), 3u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], 0);
    EXPECT_EQ(parents[2], 1);
}

// Test BFS from a middle node in a linear graph
TEST(BFSTest_60, LinearGraphMiddleRoot_60) {
    std::vector<std::vector<int>> graph = {
        {1},
        {0, 2},
        {1}
    };
    std::vector<int> parents;
    int count = glomap::BFS(graph, 1, parents, {});
    EXPECT_EQ(count, 2);
    ASSERT_EQ(parents.size(), 3u);
    EXPECT_EQ(parents[1], 1);
    EXPECT_EQ(parents[0], 1);
    EXPECT_EQ(parents[2], 1);
}

// Test BFS on a disconnected graph (two components)
TEST(BFSTest_60, DisconnectedGraph_60) {
    std::vector<std::vector<int>> graph = {
        {1},    // 0 -> 1
        {0},    // 1 -> 0
        {3},    // 2 -> 3
        {2}     // 3 -> 2
    };
    std::vector<int> parents;
    int count = glomap::BFS(graph, 0, parents, {});
    EXPECT_EQ(count, 1);
    ASSERT_EQ(parents.size(), 4u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], 0);
    EXPECT_EQ(parents[2], -1); // Not reachable
    EXPECT_EQ(parents[3], -1); // Not reachable
}

// Test BFS with a banned edge that disconnects part of the graph
TEST(BFSTest_60, BannedEdgeDisconnects_60) {
    // Graph: 0-1-2
    std::vector<std::vector<int>> graph = {
        {1},
        {0, 2},
        {1}
    };
    std::vector<int> parents;
    std::vector<std::pair<int, int>> banned = {{0, 1}};
    int count = glomap::BFS(graph, 0, parents, banned);
    EXPECT_EQ(count, 0);
    ASSERT_EQ(parents.size(), 3u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], -1);
    EXPECT_EQ(parents[2], -1);
}

// Test BFS with a banned edge in reverse direction
TEST(BFSTest_60, BannedEdgeReverseDirection_60) {
    // Graph: 0-1-2
    std::vector<std::vector<int>> graph = {
        {1},
        {0, 2},
        {1}
    };
    std::vector<int> parents;
    // Banning (1, 0) should also block the edge 0->1
    std::vector<std::pair<int, int>> banned = {{1, 0}};
    int count = glomap::BFS(graph, 0, parents, banned);
    EXPECT_EQ(count, 0);
    ASSERT_EQ(parents.size(), 3u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], -1);
    EXPECT_EQ(parents[2], -1);
}

// Test BFS with banned edge that doesn't affect traversal (alternative path exists)
TEST(BFSTest_60, BannedEdgeAlternativePath_60) {
    // Triangle: 0-1, 1-2, 0-2
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {0, 2},
        {0, 1}
    };
    std::vector<int> parents;
    std::vector<std::pair<int, int>> banned = {{0, 1}};
    int count = glomap::BFS(graph, 0, parents, banned);
    EXPECT_EQ(count, 2);
    ASSERT_EQ(parents.size(), 3u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[2], 0);
    EXPECT_EQ(parents[1], 2);
}

// Test BFS on a tree-structured graph
TEST(BFSTest_60, TreeGraph_60) {
    //       0
    //      / \
    //     1   2
    //    / \
    //   3   4
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0},
        {1},
        {1}
    };
    std::vector<int> parents;
    int count = glomap::BFS(graph, 0, parents, {});
    EXPECT_EQ(count, 4);
    ASSERT_EQ(parents.size(), 5u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], 0);
    EXPECT_EQ(parents[2], 0);
    EXPECT_EQ(parents[3], 1);
    EXPECT_EQ(parents[4], 1);
}

// Test BFS with multiple banned edges
TEST(BFSTest_60, MultipleBannedEdges_60) {
    //       0
    //      / \
    //     1   2
    //    / \
    //   3   4
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0},
        {1},
        {1}
    };
    std::vector<int> parents;
    std::vector<std::pair<int, int>> banned = {{0, 1}, {0, 2}};
    int count = glomap::BFS(graph, 0, parents, banned);
    EXPECT_EQ(count, 0);
    ASSERT_EQ(parents.size(), 5u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], -1);
    EXPECT_EQ(parents[2], -1);
    EXPECT_EQ(parents[3], -1);
    EXPECT_EQ(parents[4], -1);
}

// Test BFS parents vector is properly cleared before use
TEST(BFSTest_60, ParentsVectorCleared_60) {
    std::vector<std::vector<int>> graph = {{1}, {0}};
    std::vector<int> parents = {99, 99, 99, 99, 99}; // Pre-filled with junk
    int count = glomap::BFS(graph, 0, parents, {});
    EXPECT_EQ(count, 1);
    ASSERT_EQ(parents.size(), 2u); // Should be resized to graph size
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], 0);
}

// Test BFS on a complete graph of 4 nodes
TEST(BFSTest_60, CompleteGraph_60) {
    std::vector<std::vector<int>> graph = {
        {1, 2, 3},
        {0, 2, 3},
        {0, 1, 3},
        {0, 1, 2}
    };
    std::vector<int> parents;
    int count = glomap::BFS(graph, 0, parents, {});
    EXPECT_EQ(count, 3);
    ASSERT_EQ(parents.size(), 4u);
    EXPECT_EQ(parents[0], 0);
    // All other nodes should have parent 0 since they're all direct neighbors
    EXPECT_EQ(parents[1], 0);
    EXPECT_EQ(parents[2], 0);
    EXPECT_EQ(parents[3], 0);
}

// Test BFS from last node in graph
TEST(BFSTest_60, RootIsLastNode_60) {
    std::vector<std::vector<int>> graph = {
        {1},
        {0, 2},
        {1}
    };
    std::vector<int> parents;
    int count = glomap::BFS(graph, 2, parents, {});
    EXPECT_EQ(count, 2);
    ASSERT_EQ(parents.size(), 3u);
    EXPECT_EQ(parents[2], 2);
    EXPECT_EQ(parents[1], 2);
    EXPECT_EQ(parents[0], 1);
}

// Test BFS with empty banned edges vector
TEST(BFSTest_60, EmptyBannedEdges_60) {
    std::vector<std::vector<int>> graph = {
        {1},
        {0}
    };
    std::vector<int> parents;
    std::vector<std::pair<int, int>> banned;
    int count = glomap::BFS(graph, 0, parents, banned);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], 0);
}

// Test BFS with banned edge that doesn't exist in graph
TEST(BFSTest_60, BannedEdgeNotInGraph_60) {
    std::vector<std::vector<int>> graph = {
        {1},
        {0, 2},
        {1}
    };
    std::vector<int> parents;
    // Ban an edge that doesn't exist: (0, 2)
    std::vector<std::pair<int, int>> banned = {{0, 2}};
    int count = glomap::BFS(graph, 0, parents, banned);
    EXPECT_EQ(count, 2);
    ASSERT_EQ(parents.size(), 3u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], 0);
    EXPECT_EQ(parents[2], 1);
}

// Test BFS on a graph with self-loops (should handle gracefully)
TEST(BFSTest_60, GraphWithSelfLoop_60) {
    std::vector<std::vector<int>> graph = {
        {0, 1}, // node 0 has self-loop
        {0}
    };
    std::vector<int> parents;
    int count = glomap::BFS(graph, 0, parents, {});
    EXPECT_EQ(count, 1);
    ASSERT_EQ(parents.size(), 2u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], 0);
}

// Test BFS on a cycle graph
TEST(BFSTest_60, CycleGraph_60) {
    // 0-1-2-3-0
    std::vector<std::vector<int>> graph = {
        {1, 3},
        {0, 2},
        {1, 3},
        {2, 0}
    };
    std::vector<int> parents;
    int count = glomap::BFS(graph, 0, parents, {});
    EXPECT_EQ(count, 3);
    ASSERT_EQ(parents.size(), 4u);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], 0);
    EXPECT_EQ(parents[3], 0);
    // Node 2 should be reached from either 1 or 3
    EXPECT_TRUE(parents[2] == 1 || parents[2] == 3);
}

// Test that counter returns correct value (number of newly visited nodes, excluding root)
TEST(BFSTest_60, CounterValueIsCorrect_60) {
    // Star graph: 0 connected to 1,2,3,4
    std::vector<std::vector<int>> graph = {
        {1, 2, 3, 4},
        {0},
        {0},
        {0},
        {0}
    };
    std::vector<int> parents;
    int count = glomap::BFS(graph, 0, parents, {});
    EXPECT_EQ(count, 4); // 4 nodes visited besides root
}

// Test BFS with all edges banned from root (root is isolated)
TEST(BFSTest_60, AllEdgesFromRootBanned_60) {
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {0, 2},
        {0, 1}
    };
    std::vector<int> parents;
    std::vector<std::pair<int, int>> banned = {{0, 1}, {0, 2}};
    int count = glomap::BFS(graph, 0, parents, banned);
    EXPECT_EQ(count, 0);
    EXPECT_EQ(parents[0], 0);
    EXPECT_EQ(parents[1], -1);
    EXPECT_EQ(parents[2], -1);
}

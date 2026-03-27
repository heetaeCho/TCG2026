#include <gtest/gtest.h>

#include <boost/adjacency_list.hpp>

#include <vector>

#include <queue>

#include <utility>



namespace glomap {

    int BFS(const std::vector<std::vector<int>>& graph, int root, std::vector<int>& parents, std::vector<std::pair<int, int>> banned_edges);

}



using namespace glomap;



TEST_F(BFSTest_129, SingleNodeGraph_129) {

    std::vector<std::vector<int>> graph = {{}};

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    

    int result = BFS(graph, 0, parents, banned_edges);

    

    EXPECT_EQ(result, 0);

    EXPECT_EQ(parents.size(), 1);

    EXPECT_EQ(parents[0], 0);

}



TEST_F(BFSTest_129, TwoNodesConnected_129) {

    std::vector<std::vector<int>> graph = {{1}, {0}};

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    

    int result = BFS(graph, 0, parents, banned_edges);

    

    EXPECT_EQ(result, 1);

    EXPECT_EQ(parents.size(), 2);

    EXPECT_EQ(parents[0], 0);

    EXPECT_EQ(parents[1], 0);

}



TEST_F(BFSTest_129, TwoNodesDisconnected_129) {

    std::vector<std::vector<int>> graph = {{}, {}};

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    

    int result = BFS(graph, 0, parents, banned_edges);

    

    EXPECT_EQ(result, 0);

    EXPECT_EQ(parents.size(), 2);

    EXPECT_EQ(parents[0], 0);

    EXPECT_EQ(parents[1], -1);

}



TEST_F(BFSTest_129, ThreeNodesConnectedLinearly_129) {

    std::vector<std::vector<int>> graph = {{1}, {0, 2}, {1}};

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    

    int result = BFS(graph, 0, parents, banned_edges);

    

    EXPECT_EQ(result, 2);

    EXPECT_EQ(parents.size(), 3);

    EXPECT_EQ(parents[0], 0);

    EXPECT_EQ(parents[1], 0);

    EXPECT_EQ(parents[2], 1);

}



TEST_F(BFSTest_129, ThreeNodesDisconnectedTriangle_129) {

    std::vector<std::vector<int>> graph = {{1}, {2}, {0}};

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    

    int result = BFS(graph, 0, parents, banned_edges);

    

    EXPECT_EQ(result, 2);

    EXPECT_EQ(parents.size(), 3);

    EXPECT_EQ(parents[0], 0);

    EXPECT_EQ(parents[1], 0);

    EXPECT_EQ(parents[2], 1);

}



TEST_F(BFSTest_129, BannedEdgesInGraph_129) {

    std::vector<std::vector<int>> graph = {{1, 2}, {0, 3}, {0, 3}, {1, 2}};

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges = {{0, 1}, {1, 0}};

    

    int result = BFS(graph, 0, parents, banned_edges);

    

    EXPECT_EQ(result, 1);

    EXPECT_EQ(parents.size(), 4);

    EXPECT_EQ(parents[0], 0);

    EXPECT_EQ(parents[1], -1);

    EXPECT_EQ(parents[2], 0);

    EXPECT_EQ(parents[3], 2);

}



TEST_F(BFSTest_129, BannedEdgesPreventTraversal_129) {

    std::vector<std::vector<int>> graph = {{1}, {0}};

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges = {{0, 1}, {1, 0}};

    

    int result = BFS(graph, 0, parents, banned_edges);

    

    EXPECT_EQ(result, 0);

    EXPECT_EQ(parents.size(), 2);

    EXPECT_EQ(parents[0], 0);

    EXPECT_EQ(parents[1], -1);

}



TEST_F(BFSTest_129, RootIsNotInGraph_129) {

    std::vector<std::vector<int>> graph = {{1}, {0}};

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    

    EXPECT_THROW(BFS(graph, 2, parents, banned_edges), std::exception);

}



TEST_F(BFSTest_129, LargeGraphTest_129) {

    const int numVertices = 1000;

    std::vector<std::vector<int>> graph(numVertices);

    

    for (int i = 0; i < numVertices - 1; ++i) {

        graph[i].push_back(i + 1);

        graph[i + 1].push_back(i);

    }

    

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    

    int result = BFS(graph, 0, parents, banned_edges);

    

    EXPECT_EQ(result, numVertices - 1);

    EXPECT_EQ(parents.size(), numVertices);

    for (int i = 0; i < numVertices; ++i) {

        if (i == 0) {

            EXPECT_EQ(parents[i], 0);

        } else {

            EXPECT_EQ(parents[i], i - 1);

        }

    }

}

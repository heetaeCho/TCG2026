#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/glomap/glomap/math/tree.cc"



namespace {



TEST(BFS_Test_60, NormalOperation_60) {

    std::vector<std::vector<int>> graph = {{1}, {0, 2, 3}, {1, 3}, {1, 2}};

    int root = 0;

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    int result = glomap::BFS(graph, root, parents, banned_edges);

    EXPECT_EQ(result, 3);

    EXPECT_THAT(parents, ::testing::ElementsAre(0, 0, 1, 1));

}



TEST(BFS_Test_60, BoundaryCondition_EmptyGraph_60) {

    std::vector<std::vector<int>> graph = {};

    int root = 0;

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    int result = glomap::BFS(graph, root, parents, banned_edges);

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(parents.empty());

}



TEST(BFS_Test_60, BoundaryCondition_SingleNode_60) {

    std::vector<std::vector<int>> graph = {{}};

    int root = 0;

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    int result = glomap::BFS(graph, root, parents, banned_edges);

    EXPECT_EQ(result, 0);

    EXPECT_THAT(parents, ::testing::ElementsAre(0));

}



TEST(BFS_Test_60, BoundaryCondition_NoEdges_60) {

    std::vector<std::vector<int>> graph = {{}, {}, {}};

    int root = 0;

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    int result = glomap::BFS(graph, root, parents, banned_edges);

    EXPECT_EQ(result, 0);

    EXPECT_THAT(parents, ::testing::ElementsAre(0, -1, -1));

}



TEST(BFS_Test_60, BoundaryCondition_RootNodeIsNotConnected_60) {

    std::vector<std::vector<int>> graph = {{}, {2, 3}, {1, 3}, {1, 2}};

    int root = 0;

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges;

    int result = glomap::BFS(graph, root, parents, banned_edges);

    EXPECT_EQ(result, 0);

    EXPECT_THAT(parents, ::testing::ElementsAre(0, -1, -1, -1));

}



TEST(BFS_Test_60, ExceptionalCase_BannedEdgesBlockAllPaths_60) {

    std::vector<std::vector<int>> graph = {{1}, {0, 2, 3}, {1, 3}, {1, 2}};

    int root = 0;

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges = {{0, 1}, {1, 0}};

    int result = glomap::BFS(graph, root, parents, banned_edges);

    EXPECT_EQ(result, 0);

    EXPECT_THAT(parents, ::testing::ElementsAre(0, -1, -1, -1));

}



TEST(BFS_Test_60, ExceptionalCase_BannedEdgesBlockSomePaths_60) {

    std::vector<std::vector<int>> graph = {{1}, {0, 2, 3}, {1, 3}, {1, 2}};

    int root = 0;

    std::vector<int> parents;

    std::vector<std::pair<int, int>> banned_edges = {{1, 2}, {2, 1}};

    int result = glomap::BFS(graph, root, parents, banned_edges);

    EXPECT_EQ(result, 1);

    EXPECT_THAT(parents, ::testing::ElementsAre(0, 0, -1, 1));

}



}  // namespace

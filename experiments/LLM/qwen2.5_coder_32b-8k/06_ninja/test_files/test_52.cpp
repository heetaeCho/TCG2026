#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "graph.h"



using ::testing::StrictMock;

using ::testing::_;



class MockEdge : public Edge {

public:

    MOCK_METHOD(void, SomeMethod, (), (const));

};



class NodeTest_52 : public ::testing::Test {

protected:

    Node node_;

    std::unique_ptr<Edge> edge1_;

    std::unique_ptr<Edge> edge2_;



    NodeTest_52() : node_("test_path", 0) {

        edge1_ = std::make_unique<MockEdge>();

        edge2_ = std::make_unique<MockEdge>();

    }

};



TEST_F(NodeTest_52, AddOutEdge_IncreasesCount_52) {

    size_t initial_count = node_.out_edges().size();

    node_.AddOutEdge(edge1_.get());

    EXPECT_EQ(node_.out_edges().size(), initial_count + 1);

}



TEST_F(NodeTest_52, AddMultipleOutEdges_IncreasesCountCorrectly_52) {

    size_t initial_count = node_.out_edges().size();

    node_.AddOutEdge(edge1_.get());

    node_.AddOutEdge(edge2_.get());

    EXPECT_EQ(node_.out_edges().size(), initial_count + 2);

}



TEST_F(NodeTest_52, AddOutEdge_CorrectlyAddsEdge_52) {

    node_.AddOutEdge(edge1_.get());

    EXPECT_EQ(node_.out_edges()[0], edge1_.get());

}



TEST_F(NodeTest_52, AddOutEdge_IdempotentForSameEdge_52) {

    node_.AddOutEdge(edge1_.get());

    size_t count_after_first_add = node_.out_edges().size();

    node_.AddOutEdge(edge1_.get());

    EXPECT_EQ(node_.out_edges().size(), count_after_first_add);

}



TEST_F(NodeTest_52, AddOutEdge_HandlesNullPointerGracefully_52) {

    size_t initial_count = node_.out_edges().size();

    node_.AddOutEdge(nullptr);

    EXPECT_EQ(node_.out_edges().size(), initial_count);

}

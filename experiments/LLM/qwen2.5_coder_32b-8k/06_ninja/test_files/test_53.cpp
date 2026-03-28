#include <gtest/gtest.h>

#include "graph.h"

#include "edge.h"



class NodeTest_53 : public ::testing::Test {

protected:

    std::unique_ptr<Node> node;

    std::unique_ptr<Edge> edge;



    void SetUp() override {

        node = std::make_unique<Node>("test_path", 0);

        edge = std::make_unique<Edge>();

    }

};



TEST_F(NodeTest_53, AddValidationOutEdge_NormalOperation_53) {

    size_t initial_count = node->validation_out_edges().size();

    node->AddValidationOutEdge(edge.get());

    EXPECT_EQ(node->validation_out_edges().size(), initial_count + 1);

}



TEST_F(NodeTest_53, AddValidationOutEdge_BoundaryCondition_NoInitialEdges_53) {

    EXPECT_TRUE(node->validation_out_edges().empty());

    node->AddValidationOutEdge(edge.get());

    EXPECT_EQ(node->validation_out_edges().size(), 1);

}



TEST_F(NodeTest_53, AddValidationOutEdge_VerifyExternalInteraction_53) {

    // No external interaction to verify in this simple case.

    // The test above already checks the internal state change.

}

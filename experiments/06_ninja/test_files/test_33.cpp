#include <gtest/gtest.h>

#include "graph.h"

#include <string>



class NodeTest_33 : public ::testing::Test {

protected:

    Node node;



    NodeTest_33() : node("test_path", 0) {}

};



TEST_F(NodeTest_33, ExistsReturnsFalseInitially_33) {

    EXPECT_FALSE(node.exists());

}



TEST_F(NodeTest_33, PathMatchesConstructorArgument_33) {

    EXPECT_EQ(node.path(), "test_path");

}



TEST_F(NodeTest_33, SlashBitsMatchesConstructorArgument_33) {

    EXPECT_EQ(node.slash_bits(), 0);

}



TEST_F(NodeTest_33, MtimeIsInitializedToNegativeOne_33) {

    EXPECT_EQ(node.mtime(), -1);

}



TEST_F(NodeTest_33, DirtyReturnsFalseInitially_33) {

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_33, DyndepPendingReturnsFalseInitially_33) {

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_33, InEdgeIsNullptrInitially_33) {

    EXPECT_EQ(node.in_edge(), nullptr);

}



TEST_F(NodeTest_33, OutEdgesIsEmptyInitially_33) {

    EXPECT_TRUE(node.out_edges().empty());

}



TEST_F(NodeTest_33, ValidationOutEdgesIsEmptyInitially_33) {

    EXPECT_TRUE(node.validation_out_edges().empty());

}



TEST_F(NodeTest_33, IdIsInitializedToNegativeOne_33) {

    EXPECT_EQ(node.id(), -1);

}



TEST_F(NodeTest_33, GeneratedByDepLoaderReturnsTrueInitially_33) {

    EXPECT_TRUE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_33, StatusKnownReturnsFalseInitially_33) {

    EXPECT_FALSE(node.status_known());

}



TEST_F(NodeTest_33, MarkMissingSetsExistsToFalseAndStatusKnownToTrue_33) {

    node.MarkMissing();

    EXPECT_FALSE(node.exists());

    EXPECT_TRUE(node.status_known());

}



TEST_F(NodeTest_33, SetDirtyUpdatesDirtyFlag_33) {

    node.set_dirty(true);

    EXPECT_TRUE(node.dirty());

    node.set_dirty(false);

    EXPECT_FALSE(node.dirty());

}



TEST_F(NodeTest_33, MarkDirtySetsDirtyFlag_33) {

    node.MarkDirty();

    EXPECT_TRUE(node.dirty());

}



TEST_F(NodeTest_33, SetDyndepPendingUpdatesFlag_33) {

    node.set_dyndep_pending(true);

    EXPECT_TRUE(node.dyndep_pending());

    node.set_dyndep_pending(false);

    EXPECT_FALSE(node.dyndep_pending());

}



TEST_F(NodeTest_33, SetInEdgeUpdatesInEdgePointer_33) {

    Edge mock_edge;

    node.set_in_edge(&mock_edge);

    EXPECT_EQ(node.in_edge(), &mock_edge);

}



TEST_F(NodeTest_33, AddOutEdgeAddsEdgeToOutEdges_33) {

    Edge mock_edge;

    node.AddOutEdge(&mock_edge);

    EXPECT_EQ(node.out_edges().size(), 1);

    EXPECT_EQ(node.out_edges()[0], &mock_edge);

}



TEST_F(NodeTest_33, AddValidationOutEdgeAddsEdgeToValidationOutEdges_33) {

    Edge mock_edge;

    node.AddValidationOutEdge(&mock_edge);

    EXPECT_EQ(node.validation_out_edges().size(), 1);

    EXPECT_EQ(node.validation_out_edges()[0], &mock_edge);

}



TEST_F(NodeTest_33, SetGeneratedByDepLoaderUpdatesFlag_33) {

    node.set_generated_by_dep_loader(false);

    EXPECT_FALSE(node.generated_by_dep_loader());

    node.set_generated_by_dep_loader(true);

    EXPECT_TRUE(node.generated_by_dep_loader());

}



TEST_F(NodeTest_33, SetIdUpdatesId_33) {

    node.set_id(42);

    EXPECT_EQ(node.id(), 42);

}

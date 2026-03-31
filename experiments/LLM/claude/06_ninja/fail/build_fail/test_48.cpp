#include "gtest/gtest.h"
#include "graph.h"

// Test fixture for Node class
class NodeTest_48 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test default id value
TEST_F(NodeTest_48, DefaultIdIsNegativeOne_48) {
    Node node("test_path", 0);
    EXPECT_EQ(-1, node.id());
}

// Test set_id and id
TEST_F(NodeTest_48, SetIdAndGetId_48) {
    Node node("test_path", 0);
    node.set_id(42);
    EXPECT_EQ(42, node.id());
}

// Test set_id with zero
TEST_F(NodeTest_48, SetIdToZero_48) {
    Node node("test_path", 0);
    node.set_id(0);
    EXPECT_EQ(0, node.id());
}

// Test set_id with negative value
TEST_F(NodeTest_48, SetIdToNegativeValue_48) {
    Node node("test_path", 0);
    node.set_id(-5);
    EXPECT_EQ(-5, node.id());
}

// Test set_id with large value
TEST_F(NodeTest_48, SetIdToLargeValue_48) {
    Node node("test_path", 0);
    node.set_id(INT_MAX);
    EXPECT_EQ(INT_MAX, node.id());
}

// Test set_id with INT_MIN
TEST_F(NodeTest_48, SetIdToIntMin_48) {
    Node node("test_path", 0);
    node.set_id(INT_MIN);
    EXPECT_EQ(INT_MIN, node.id());
}

// Test overwriting id
TEST_F(NodeTest_48, OverwriteId_48) {
    Node node("test_path", 0);
    node.set_id(10);
    EXPECT_EQ(10, node.id());
    node.set_id(20);
    EXPECT_EQ(20, node.id());
}

// Test path
TEST_F(NodeTest_48, PathReturnsConstructorPath_48) {
    Node node("my/test/path", 0);
    EXPECT_EQ("my/test/path", node.path());
}

// Test empty path
TEST_F(NodeTest_48, EmptyPath_48) {
    Node node("", 0);
    EXPECT_EQ("", node.path());
}

// Test slash_bits
TEST_F(NodeTest_48, SlashBitsReturnsConstructorValue_48) {
    Node node("test_path", 0x1234);
    EXPECT_EQ(0x1234u, node.slash_bits());
}

// Test slash_bits zero
TEST_F(NodeTest_48, SlashBitsZero_48) {
    Node node("test_path", 0);
    EXPECT_EQ(0u, node.slash_bits());
}

// Test default dirty state
TEST_F(NodeTest_48, DefaultDirtyIsFalse_48) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.dirty());
}

// Test set_dirty to true
TEST_F(NodeTest_48, SetDirtyTrue_48) {
    Node node("test_path", 0);
    node.set_dirty(true);
    EXPECT_TRUE(node.dirty());
}

// Test set_dirty to false
TEST_F(NodeTest_48, SetDirtyFalse_48) {
    Node node("test_path", 0);
    node.set_dirty(true);
    node.set_dirty(false);
    EXPECT_FALSE(node.dirty());
}

// Test MarkDirty
TEST_F(NodeTest_48, MarkDirtySetsDirtyTrue_48) {
    Node node("test_path", 0);
    node.MarkDirty();
    EXPECT_TRUE(node.dirty());
}

// Test default dyndep_pending
TEST_F(NodeTest_48, DefaultDyndepPendingIsFalse_48) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.dyndep_pending());
}

// Test set_dyndep_pending
TEST_F(NodeTest_48, SetDyndepPendingTrue_48) {
    Node node("test_path", 0);
    node.set_dyndep_pending(true);
    EXPECT_TRUE(node.dyndep_pending());
}

// Test set_dyndep_pending false
TEST_F(NodeTest_48, SetDyndepPendingFalse_48) {
    Node node("test_path", 0);
    node.set_dyndep_pending(true);
    node.set_dyndep_pending(false);
    EXPECT_FALSE(node.dyndep_pending());
}

// Test default in_edge
TEST_F(NodeTest_48, DefaultInEdgeIsNull_48) {
    Node node("test_path", 0);
    EXPECT_EQ(nullptr, node.in_edge());
}

// Test set_in_edge
TEST_F(NodeTest_48, SetInEdge_48) {
    Node node("test_path", 0);
    Edge edge;
    node.set_in_edge(&edge);
    EXPECT_EQ(&edge, node.in_edge());
}

// Test set_in_edge to null
TEST_F(NodeTest_48, SetInEdgeToNull_48) {
    Node node("test_path", 0);
    Edge edge;
    node.set_in_edge(&edge);
    node.set_in_edge(nullptr);
    EXPECT_EQ(nullptr, node.in_edge());
}

// Test default generated_by_dep_loader
TEST_F(NodeTest_48, DefaultGeneratedByDepLoaderIsTrue_48) {
    Node node("test_path", 0);
    EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test set_generated_by_dep_loader false
TEST_F(NodeTest_48, SetGeneratedByDepLoaderFalse_48) {
    Node node("test_path", 0);
    node.set_generated_by_dep_loader(false);
    EXPECT_FALSE(node.generated_by_dep_loader());
}

// Test set_generated_by_dep_loader true
TEST_F(NodeTest_48, SetGeneratedByDepLoaderTrue_48) {
    Node node("test_path", 0);
    node.set_generated_by_dep_loader(false);
    node.set_generated_by_dep_loader(true);
    EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test default out_edges is empty
TEST_F(NodeTest_48, DefaultOutEdgesEmpty_48) {
    Node node("test_path", 0);
    EXPECT_TRUE(node.out_edges().empty());
}

// Test AddOutEdge
TEST_F(NodeTest_48, AddOutEdge_48) {
    Node node("test_path", 0);
    Edge edge;
    node.AddOutEdge(&edge);
    ASSERT_EQ(1u, node.out_edges().size());
    EXPECT_EQ(&edge, node.out_edges()[0]);
}

// Test AddOutEdge multiple
TEST_F(NodeTest_48, AddMultipleOutEdges_48) {
    Node node("test_path", 0);
    Edge edge1, edge2, edge3;
    node.AddOutEdge(&edge1);
    node.AddOutEdge(&edge2);
    node.AddOutEdge(&edge3);
    ASSERT_EQ(3u, node.out_edges().size());
    EXPECT_EQ(&edge1, node.out_edges()[0]);
    EXPECT_EQ(&edge2, node.out_edges()[1]);
    EXPECT_EQ(&edge3, node.out_edges()[2]);
}

// Test default validation_out_edges is empty
TEST_F(NodeTest_48, DefaultValidationOutEdgesEmpty_48) {
    Node node("test_path", 0);
    EXPECT_TRUE(node.validation_out_edges().empty());
}

// Test AddValidationOutEdge
TEST_F(NodeTest_48, AddValidationOutEdge_48) {
    Node node("test_path", 0);
    Edge edge;
    node.AddValidationOutEdge(&edge);
    ASSERT_EQ(1u, node.validation_out_edges().size());
    EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

// Test AddValidationOutEdge multiple
TEST_F(NodeTest_48, AddMultipleValidationOutEdges_48) {
    Node node("test_path", 0);
    Edge edge1, edge2;
    node.AddValidationOutEdge(&edge1);
    node.AddValidationOutEdge(&edge2);
    ASSERT_EQ(2u, node.validation_out_edges().size());
    EXPECT_EQ(&edge1, node.validation_out_edges()[0]);
    EXPECT_EQ(&edge2, node.validation_out_edges()[1]);
}

// Test status_known initially false
TEST_F(NodeTest_48, DefaultStatusKnownFalse_48) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.status_known());
}

// Test MarkMissing sets exists to false and status known
TEST_F(NodeTest_48, MarkMissingSetsExistsFalseAndStatusKnown_48) {
    Node node("test_path", 0);
    node.MarkMissing();
    EXPECT_FALSE(node.exists());
    EXPECT_TRUE(node.status_known());
}

// Test ResetState resets id and other state
TEST_F(NodeTest_48, ResetStateClearsState_48) {
    Node node("test_path", 0);
    node.set_id(5);
    node.set_dirty(true);
    node.MarkMissing();
    node.ResetState();
    // After reset, status should be unknown again
    EXPECT_FALSE(node.status_known());
    EXPECT_FALSE(node.dirty());
}

// Test PathDecanonicalized static method
TEST_F(NodeTest_48, PathDecanonicalizedStatic_48) {
    std::string result = Node::PathDecanonicalized("test/path", 0);
    EXPECT_EQ("test/path", result);
}

// Test PathDecanonicalized instance method
TEST_F(NodeTest_48, PathDecanonicalizedInstance_48) {
    Node node("test/path", 0);
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("test/path", result);
}

// Test mtime default
TEST_F(NodeTest_48, DefaultMtimeIsNegativeOne_48) {
    Node node("test_path", 0);
    EXPECT_EQ(-1, node.mtime());
}

#include "gtest/gtest.h"
#include "graph.h"

// Forward declarations / minimal stubs needed for compilation
// Edge is used as a pointer, so we need at least a forward declaration
// which should already be in graph.h

class NodeInEdgeTest_44 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that a newly constructed Node has nullptr as in_edge
TEST_F(NodeInEdgeTest_44, DefaultInEdgeIsNull_44) {
    Node node("test_path", 0);
    EXPECT_EQ(nullptr, node.in_edge());
}

// Test that setting in_edge and then retrieving it returns the same pointer
TEST_F(NodeInEdgeTest_44, SetAndGetInEdge_44) {
    Node node("test_path", 0);
    Edge edge;
    node.set_in_edge(&edge);
    EXPECT_EQ(&edge, node.in_edge());
}

// Test that setting in_edge to nullptr works
TEST_F(NodeInEdgeTest_44, SetInEdgeToNull_44) {
    Node node("test_path", 0);
    Edge edge;
    node.set_in_edge(&edge);
    EXPECT_EQ(&edge, node.in_edge());
    node.set_in_edge(nullptr);
    EXPECT_EQ(nullptr, node.in_edge());
}

// Test that setting in_edge to different edges updates correctly
TEST_F(NodeInEdgeTest_44, SetInEdgeToMultipleEdges_44) {
    Node node("test_path", 0);
    Edge edge1;
    Edge edge2;
    node.set_in_edge(&edge1);
    EXPECT_EQ(&edge1, node.in_edge());
    node.set_in_edge(&edge2);
    EXPECT_EQ(&edge2, node.in_edge());
}

// Test in_edge is const-correct (can be called on const reference)
TEST_F(NodeInEdgeTest_44, InEdgeOnConstNode_44) {
    Node node("test_path", 0);
    Edge edge;
    node.set_in_edge(&edge);
    const Node& const_node = node;
    EXPECT_EQ(&edge, const_node.in_edge());
}

// Test path accessor
TEST_F(NodeInEdgeTest_44, PathReturnsCorrectPath_44) {
    Node node("my/path", 0);
    EXPECT_EQ("my/path", node.path());
}

// Test slash_bits accessor
TEST_F(NodeInEdgeTest_44, SlashBitsReturnsCorrectValue_44) {
    Node node("test_path", 42);
    EXPECT_EQ(42u, node.slash_bits());
}

// Test dirty default and setter
TEST_F(NodeInEdgeTest_44, DirtyDefaultAndSet_44) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.dirty());
    node.set_dirty(true);
    EXPECT_TRUE(node.dirty());
    node.set_dirty(false);
    EXPECT_FALSE(node.dirty());
}

// Test MarkDirty sets dirty to true
TEST_F(NodeInEdgeTest_44, MarkDirtySetsTrue_44) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.dirty());
    node.MarkDirty();
    EXPECT_TRUE(node.dirty());
}

// Test dyndep_pending default and setter
TEST_F(NodeInEdgeTest_44, DyndepPendingDefaultAndSet_44) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.dyndep_pending());
    node.set_dyndep_pending(true);
    EXPECT_TRUE(node.dyndep_pending());
    node.set_dyndep_pending(false);
    EXPECT_FALSE(node.dyndep_pending());
}

// Test generated_by_dep_loader default and setter
TEST_F(NodeInEdgeTest_44, GeneratedByDepLoaderDefaultAndSet_44) {
    Node node("test_path", 0);
    // Default is true
    EXPECT_TRUE(node.generated_by_dep_loader());
    node.set_generated_by_dep_loader(false);
    EXPECT_FALSE(node.generated_by_dep_loader());
    node.set_generated_by_dep_loader(true);
    EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test id default and setter
TEST_F(NodeInEdgeTest_44, IdDefaultAndSet_44) {
    Node node("test_path", 0);
    EXPECT_EQ(-1, node.id());
    node.set_id(5);
    EXPECT_EQ(5, node.id());
    node.set_id(0);
    EXPECT_EQ(0, node.id());
}

// Test out_edges starts empty and AddOutEdge adds edges
TEST_F(NodeInEdgeTest_44, OutEdgesDefaultEmpty_44) {
    Node node("test_path", 0);
    EXPECT_TRUE(node.out_edges().empty());
}

TEST_F(NodeInEdgeTest_44, AddOutEdgeAddsEdge_44) {
    Node node("test_path", 0);
    Edge edge1;
    Edge edge2;
    node.AddOutEdge(&edge1);
    ASSERT_EQ(1u, node.out_edges().size());
    EXPECT_EQ(&edge1, node.out_edges()[0]);
    node.AddOutEdge(&edge2);
    ASSERT_EQ(2u, node.out_edges().size());
    EXPECT_EQ(&edge2, node.out_edges()[1]);
}

// Test validation_out_edges starts empty and AddValidationOutEdge adds edges
TEST_F(NodeInEdgeTest_44, ValidationOutEdgesDefaultEmpty_44) {
    Node node("test_path", 0);
    EXPECT_TRUE(node.validation_out_edges().empty());
}

TEST_F(NodeInEdgeTest_44, AddValidationOutEdgeAddsEdge_44) {
    Node node("test_path", 0);
    Edge edge1;
    node.AddValidationOutEdge(&edge1);
    ASSERT_EQ(1u, node.validation_out_edges().size());
    EXPECT_EQ(&edge1, node.validation_out_edges()[0]);
}

// Test MarkMissing makes exists() return false and status_known() return true
TEST_F(NodeInEdgeTest_44, MarkMissingSetsState_44) {
    Node node("test_path", 0);
    // Before marking missing, status may not be known
    node.MarkMissing();
    EXPECT_FALSE(node.exists());
    EXPECT_TRUE(node.status_known());
}

// Test ResetState resets the node state
TEST_F(NodeInEdgeTest_44, ResetStateClearsState_44) {
    Node node("test_path", 0);
    node.set_dirty(true);
    node.MarkMissing();
    node.ResetState();
    // After reset, dirty should be false and status should be unknown
    EXPECT_FALSE(node.dirty());
    EXPECT_FALSE(node.status_known());
}

// Test PathDecanonicalized with slash_bits
TEST_F(NodeInEdgeTest_44, PathDecanonicalizedInstance_44) {
    Node node("test/path", 0);
    // With slash_bits = 0, path should remain unchanged
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("test/path", result);
}

// Test static PathDecanonicalized
TEST_F(NodeInEdgeTest_44, PathDecanonicalizedStatic_44) {
    std::string result = Node::PathDecanonicalized("test/path", 0);
    EXPECT_EQ("test/path", result);
}

// Test with empty path
TEST_F(NodeInEdgeTest_44, EmptyPathNode_44) {
    Node node("", 0);
    EXPECT_EQ("", node.path());
    EXPECT_EQ(nullptr, node.in_edge());
}

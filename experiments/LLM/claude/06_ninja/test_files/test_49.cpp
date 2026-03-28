#include "gtest/gtest.h"
#include "graph.h"

// Test fixture for Node class
class NodeTest_49 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test set_id and id
TEST_F(NodeTest_49, SetIdAndGetId_49) {
  Node node("test_path", 0);
  EXPECT_EQ(-1, node.id());  // default id should be -1
  node.set_id(42);
  EXPECT_EQ(42, node.id());
}

TEST_F(NodeTest_49, SetIdZero_49) {
  Node node("path", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

TEST_F(NodeTest_49, SetIdNegative_49) {
  Node node("path", 0);
  node.set_id(-100);
  EXPECT_EQ(-100, node.id());
}

TEST_F(NodeTest_49, SetIdLargeValue_49) {
  Node node("path", 0);
  node.set_id(999999);
  EXPECT_EQ(999999, node.id());
}

TEST_F(NodeTest_49, SetIdMultipleTimes_49) {
  Node node("path", 0);
  node.set_id(1);
  EXPECT_EQ(1, node.id());
  node.set_id(2);
  EXPECT_EQ(2, node.id());
  node.set_id(3);
  EXPECT_EQ(3, node.id());
}

// Test path
TEST_F(NodeTest_49, PathReturnsConstructorPath_49) {
  Node node("my/test/path", 0);
  EXPECT_EQ("my/test/path", node.path());
}

TEST_F(NodeTest_49, PathEmptyString_49) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

// Test slash_bits
TEST_F(NodeTest_49, SlashBitsReturnsConstructorValue_49) {
  Node node("path", 0x1234);
  EXPECT_EQ(0x1234u, node.slash_bits());
}

TEST_F(NodeTest_49, SlashBitsZero_49) {
  Node node("path", 0);
  EXPECT_EQ(0u, node.slash_bits());
}

// Test dirty
TEST_F(NodeTest_49, DefaultDirtyIsFalse_49) {
  Node node("path", 0);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_49, SetDirtyTrue_49) {
  Node node("path", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_49, SetDirtyFalse_49) {
  Node node("path", 0);
  node.set_dirty(true);
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_49, MarkDirty_49) {
  Node node("path", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

// Test dyndep_pending
TEST_F(NodeTest_49, DefaultDyndepPendingIsFalse_49) {
  Node node("path", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_49, SetDyndepPendingTrue_49) {
  Node node("path", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
}

TEST_F(NodeTest_49, SetDyndepPendingFalse_49) {
  Node node("path", 0);
  node.set_dyndep_pending(true);
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test in_edge
TEST_F(NodeTest_49, DefaultInEdgeIsNull_49) {
  Node node("path", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_49, SetInEdge_49) {
  Node node("path", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

TEST_F(NodeTest_49, SetInEdgeNull_49) {
  Node node("path", 0);
  Edge edge;
  node.set_in_edge(&edge);
  node.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node.in_edge());
}

// Test generated_by_dep_loader
TEST_F(NodeTest_49, DefaultGeneratedByDepLoaderIsTrue_49) {
  Node node("path", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_49, SetGeneratedByDepLoaderFalse_49) {
  Node node("path", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_49, SetGeneratedByDepLoaderTrue_49) {
  Node node("path", 0);
  node.set_generated_by_dep_loader(false);
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test out_edges
TEST_F(NodeTest_49, DefaultOutEdgesEmpty_49) {
  Node node("path", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

TEST_F(NodeTest_49, AddOutEdge_49) {
  Node node("path", 0);
  Edge edge;
  node.AddOutEdge(&edge);
  ASSERT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge, node.out_edges()[0]);
}

TEST_F(NodeTest_49, AddMultipleOutEdges_49) {
  Node node("path", 0);
  Edge edge1, edge2, edge3;
  node.AddOutEdge(&edge1);
  node.AddOutEdge(&edge2);
  node.AddOutEdge(&edge3);
  ASSERT_EQ(3u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  EXPECT_EQ(&edge2, node.out_edges()[1]);
  EXPECT_EQ(&edge3, node.out_edges()[2]);
}

// Test validation_out_edges
TEST_F(NodeTest_49, DefaultValidationOutEdgesEmpty_49) {
  Node node("path", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

TEST_F(NodeTest_49, AddValidationOutEdge_49) {
  Node node("path", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  ASSERT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

TEST_F(NodeTest_49, AddMultipleValidationOutEdges_49) {
  Node node("path", 0);
  Edge edge1, edge2;
  node.AddValidationOutEdge(&edge1);
  node.AddValidationOutEdge(&edge2);
  ASSERT_EQ(2u, node.validation_out_edges().size());
  EXPECT_EQ(&edge1, node.validation_out_edges()[0]);
  EXPECT_EQ(&edge2, node.validation_out_edges()[1]);
}

// Test mtime
TEST_F(NodeTest_49, DefaultMtimeIsNegativeOne_49) {
  Node node("path", 0);
  EXPECT_EQ(-1, node.mtime());
}

// Test status_known
TEST_F(NodeTest_49, DefaultStatusNotKnown_49) {
  Node node("path", 0);
  EXPECT_FALSE(node.status_known());
}

// Test MarkMissing
TEST_F(NodeTest_49, MarkMissingSetsStatusKnown_49) {
  Node node("path", 0);
  EXPECT_FALSE(node.status_known());
  node.MarkMissing();
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
}

// Test exists
TEST_F(NodeTest_49, MarkMissingMeansNotExists_49) {
  Node node("path", 0);
  node.MarkMissing();
  EXPECT_FALSE(node.exists());
}

// Test ResetState
TEST_F(NodeTest_49, ResetStateResetsToDefault_49) {
  Node node("path", 0);
  node.set_dirty(true);
  node.MarkMissing();
  node.ResetState();
  EXPECT_FALSE(node.dirty());
  EXPECT_FALSE(node.status_known());
  EXPECT_EQ(-1, node.mtime());
}

// Test PathDecanonicalized
TEST_F(NodeTest_49, PathDecanonicalizedInstance_49) {
  Node node("test/path", 0);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("test/path", result);
}

TEST_F(NodeTest_49, PathDecanonicalizedStatic_49) {
  std::string result = Node::PathDecanonicalized("test/path", 0);
  EXPECT_EQ("test/path", result);
}

// Test id default value
TEST_F(NodeTest_49, DefaultIdIsNegativeOne_49) {
  Node node("path", 0);
  EXPECT_EQ(-1, node.id());
}

// Boundary: set_id with INT_MAX and INT_MIN
TEST_F(NodeTest_49, SetIdIntMax_49) {
  Node node("path", 0);
  node.set_id(INT_MAX);
  EXPECT_EQ(INT_MAX, node.id());
}

TEST_F(NodeTest_49, SetIdIntMin_49) {
  Node node("path", 0);
  node.set_id(INT_MIN);
  EXPECT_EQ(INT_MIN, node.id());
}

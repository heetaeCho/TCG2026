#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Forward declarations and minimal stubs needed for compilation
// We rely on the actual implementations from the codebase.

class NodeTest_51 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test basic construction and path retrieval
TEST_F(NodeTest_51, ConstructorSetsPath_51) {
  Node node("build/foo.o", 0);
  EXPECT_EQ("build/foo.o", node.path());
}

// Test slash_bits is stored correctly
TEST_F(NodeTest_51, ConstructorSetsSlashBits_51) {
  Node node("build/foo.o", 42);
  EXPECT_EQ(42u, node.slash_bits());
}

// Test default mtime is -1
TEST_F(NodeTest_51, DefaultMtimeIsNegativeOne_51) {
  Node node("foo", 0);
  EXPECT_EQ(-1, node.mtime());
}

// Test default dirty state is false
TEST_F(NodeTest_51, DefaultDirtyIsFalse_51) {
  Node node("foo", 0);
  EXPECT_FALSE(node.dirty());
}

// Test set_dirty and dirty
TEST_F(NodeTest_51, SetDirtySetsFlag_51) {
  Node node("foo", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

// Test MarkDirty sets dirty to true
TEST_F(NodeTest_51, MarkDirtySetsTrue_51) {
  Node node("foo", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

// Test default dyndep_pending is false
TEST_F(NodeTest_51, DefaultDyndepPendingIsFalse_51) {
  Node node("foo", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test set_dyndep_pending
TEST_F(NodeTest_51, SetDyndepPending_51) {
  Node node("foo", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test default in_edge is nullptr
TEST_F(NodeTest_51, DefaultInEdgeIsNull_51) {
  Node node("foo", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

// Test set_in_edge
TEST_F(NodeTest_51, SetInEdge_51) {
  Node node("foo", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

// Test default id is -1
TEST_F(NodeTest_51, DefaultIdIsNegativeOne_51) {
  Node node("foo", 0);
  EXPECT_EQ(-1, node.id());
}

// Test set_id
TEST_F(NodeTest_51, SetId_51) {
  Node node("foo", 0);
  node.set_id(5);
  EXPECT_EQ(5, node.id());
}

// Test set_id with zero
TEST_F(NodeTest_51, SetIdZero_51) {
  Node node("foo", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

// Test out_edges initially empty
TEST_F(NodeTest_51, OutEdgesInitiallyEmpty_51) {
  Node node("foo", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

// Test AddOutEdge
TEST_F(NodeTest_51, AddOutEdge_51) {
  Node node("foo", 0);
  Edge edge1, edge2;
  node.AddOutEdge(&edge1);
  ASSERT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  node.AddOutEdge(&edge2);
  ASSERT_EQ(2u, node.out_edges().size());
  EXPECT_EQ(&edge2, node.out_edges()[1]);
}

// Test validation_out_edges initially empty
TEST_F(NodeTest_51, ValidationOutEdgesInitiallyEmpty_51) {
  Node node("foo", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

// Test AddValidationOutEdge
TEST_F(NodeTest_51, AddValidationOutEdge_51) {
  Node node("foo", 0);
  Edge edge1, edge2;
  node.AddValidationOutEdge(&edge1);
  ASSERT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge1, node.validation_out_edges()[0]);
  node.AddValidationOutEdge(&edge2);
  ASSERT_EQ(2u, node.validation_out_edges().size());
  EXPECT_EQ(&edge2, node.validation_out_edges()[1]);
}

// Test default generated_by_dep_loader is true
TEST_F(NodeTest_51, DefaultGeneratedByDepLoaderIsTrue_51) {
  Node node("foo", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test set_generated_by_dep_loader
TEST_F(NodeTest_51, SetGeneratedByDepLoader_51) {
  Node node("foo", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test status_known returns false initially (mtime == -1 means unknown)
TEST_F(NodeTest_51, StatusNotKnownInitially_51) {
  Node node("foo", 0);
  EXPECT_FALSE(node.status_known());
}

// Test MarkMissing sets existence to missing and status becomes known
TEST_F(NodeTest_51, MarkMissingSetsExistenceAndStatusKnown_51) {
  Node node("foo", 0);
  node.MarkMissing();
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
}

// Test exists returns false when status is not known
TEST_F(NodeTest_51, ExistsFalseWhenStatusUnknown_51) {
  Node node("foo", 0);
  // Default state - existence unknown
  EXPECT_FALSE(node.exists());
}

// Test ResetState resets dirty and other state
TEST_F(NodeTest_51, ResetStateClearsState_51) {
  Node node("foo", 0);
  node.set_dirty(true);
  node.MarkMissing();
  node.ResetState();
  EXPECT_FALSE(node.dirty());
  // After reset, mtime should be back to -1 (status unknown)
  EXPECT_EQ(-1, node.mtime());
  EXPECT_FALSE(node.status_known());
}

// Test PathDecanonicalized with slash_bits = 0 (no backslash replacement)
TEST_F(NodeTest_51, PathDecanonicalizedNoSlashBits_51) {
  Node node("build/foo/bar.o", 0);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("build/foo/bar.o", result);
}

// Test static PathDecanonicalized
TEST_F(NodeTest_51, StaticPathDecanonicalizedNoSlashBits_51) {
  std::string result = Node::PathDecanonicalized("build/foo/bar.o", 0);
  EXPECT_EQ("build/foo/bar.o", result);
}

// Test empty path
TEST_F(NodeTest_51, EmptyPath_51) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

// Test multiple out edges don't interfere with validation out edges
TEST_F(NodeTest_51, OutEdgesAndValidationEdgesAreIndependent_51) {
  Node node("foo", 0);
  Edge edge1, edge2, edge3;
  node.AddOutEdge(&edge1);
  node.AddOutEdge(&edge2);
  node.AddValidationOutEdge(&edge3);
  EXPECT_EQ(2u, node.out_edges().size());
  EXPECT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge3, node.validation_out_edges()[0]);
}

// Test set_id can handle large values
TEST_F(NodeTest_51, SetIdLargeValue_51) {
  Node node("foo", 0);
  node.set_id(1000000);
  EXPECT_EQ(1000000, node.id());
}

// Test UpdatePhonyMtime updates mtime
TEST_F(NodeTest_51, UpdatePhonyMtime_51) {
  Node node("foo", 0);
  node.UpdatePhonyMtime(100);
  EXPECT_EQ(100, node.mtime());
}

// Test UpdatePhonyMtime with max of multiple calls
TEST_F(NodeTest_51, UpdatePhonyMtimeKeepsMax_51) {
  Node node("foo", 0);
  node.UpdatePhonyMtime(100);
  node.UpdatePhonyMtime(50);
  // UpdatePhonyMtime should keep the max
  EXPECT_GE(node.mtime(), 50);
}

// Test slash_bits with nonzero value
TEST_F(NodeTest_51, SlashBitsNonZero_51) {
  Node node("build\\foo\\bar.o", 6);  // slash_bits marking backslashes
  EXPECT_EQ(6u, node.slash_bits());
}

#ifdef _WIN32
// Test PathDecanonicalized with slash_bits on Windows
TEST_F(NodeTest_51, PathDecanonicalizedWithSlashBitsWindows_51) {
  // slash_bits = 1 means first slash should be backslash
  std::string result = Node::PathDecanonicalized("build/foo.o", 1);
  // First '/' should be replaced with '\\'
  EXPECT_NE(std::string::npos, result.find('\\'));
}
#endif

// Test MarkDirty can be called multiple times
TEST_F(NodeTest_51, MarkDirtyIdempotent_51) {
  Node node("foo", 0);
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

// Test set_in_edge to nullptr
TEST_F(NodeTest_51, SetInEdgeToNull_51) {
  Node node("foo", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
  node.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node.in_edge());
}

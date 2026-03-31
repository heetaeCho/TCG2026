#include "gtest/gtest.h"
#include "graph.h"

// Forward declarations and minimal setup needed
// We need to include enough to construct Node and Edge objects

class NodeTest_50 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

TEST_F(NodeTest_50, ConstructorSetsPath_50) {
  Node node("foo/bar.cc", 0);
  EXPECT_EQ("foo/bar.cc", node.path());
}

TEST_F(NodeTest_50, ConstructorSetsSlashBits_50) {
  Node node("foo/bar.cc", 5);
  EXPECT_EQ(5u, node.slash_bits());
}

TEST_F(NodeTest_50, InitialMtimeIsNegativeOne_50) {
  Node node("test.cc", 0);
  EXPECT_EQ(-1, node.mtime());
}

TEST_F(NodeTest_50, InitialDirtyIsFalse_50) {
  Node node("test.cc", 0);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_50, SetDirtyTrue_50) {
  Node node("test.cc", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_50, SetDirtyFalse_50) {
  Node node("test.cc", 0);
  node.set_dirty(true);
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_50, MarkDirtySetsNodeDirty_50) {
  Node node("test.cc", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_50, InitialIdIsNegativeOne_50) {
  Node node("test.cc", 0);
  EXPECT_EQ(-1, node.id());
}

TEST_F(NodeTest_50, SetId_50) {
  Node node("test.cc", 0);
  node.set_id(42);
  EXPECT_EQ(42, node.id());
}

TEST_F(NodeTest_50, SetIdZero_50) {
  Node node("test.cc", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

TEST_F(NodeTest_50, InitialInEdgeIsNull_50) {
  Node node("test.cc", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_50, SetInEdge_50) {
  Node node("test.cc", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

TEST_F(NodeTest_50, InitialOutEdgesEmpty_50) {
  Node node("test.cc", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

TEST_F(NodeTest_50, AddOutEdge_50) {
  Node node("test.cc", 0);
  Edge edge;
  node.AddOutEdge(&edge);
  ASSERT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge, node.out_edges()[0]);
}

TEST_F(NodeTest_50, AddMultipleOutEdges_50) {
  Node node("test.cc", 0);
  Edge edge1, edge2, edge3;
  node.AddOutEdge(&edge1);
  node.AddOutEdge(&edge2);
  node.AddOutEdge(&edge3);
  ASSERT_EQ(3u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  EXPECT_EQ(&edge2, node.out_edges()[1]);
  EXPECT_EQ(&edge3, node.out_edges()[2]);
}

TEST_F(NodeTest_50, InitialValidationOutEdgesEmpty_50) {
  Node node("test.cc", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

TEST_F(NodeTest_50, AddValidationOutEdge_50) {
  Node node("test.cc", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  ASSERT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

TEST_F(NodeTest_50, AddMultipleValidationOutEdges_50) {
  Node node("test.cc", 0);
  Edge edge1, edge2;
  node.AddValidationOutEdge(&edge1);
  node.AddValidationOutEdge(&edge2);
  ASSERT_EQ(2u, node.validation_out_edges().size());
  EXPECT_EQ(&edge1, node.validation_out_edges()[0]);
  EXPECT_EQ(&edge2, node.validation_out_edges()[1]);
}

TEST_F(NodeTest_50, InitialDyndepPendingIsFalse_50) {
  Node node("test.cc", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_50, SetDyndepPending_50) {
  Node node("test.cc", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_50, InitialGeneratedByDepLoaderIsTrue_50) {
  Node node("test.cc", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_50, SetGeneratedByDepLoader_50) {
  Node node("test.cc", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_50, InitialStatusNotKnown_50) {
  Node node("test.cc", 0);
  EXPECT_FALSE(node.status_known());
}

TEST_F(NodeTest_50, MarkMissing_50) {
  Node node("test.cc", 0);
  node.MarkMissing();
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
}

TEST_F(NodeTest_50, ExistsAfterMarkMissingIsFalse_50) {
  Node node("test.cc", 0);
  node.MarkMissing();
  EXPECT_FALSE(node.exists());
}

TEST_F(NodeTest_50, ResetStateClearsDirtyAndStatus_50) {
  Node node("test.cc", 0);
  node.set_dirty(true);
  node.MarkMissing();
  EXPECT_TRUE(node.dirty());
  EXPECT_TRUE(node.status_known());

  node.ResetState();
  EXPECT_FALSE(node.dirty());
  EXPECT_FALSE(node.status_known());
}

TEST_F(NodeTest_50, PathDecanonicalizedInstance_50) {
  Node node("foo/bar", 0);
  std::string result = node.PathDecanonicalized();
  // With slash_bits = 0, no slash replacement should occur
  EXPECT_EQ("foo/bar", result);
}

TEST_F(NodeTest_50, PathDecanonicalizedStatic_50) {
  std::string result = Node::PathDecanonicalized("foo/bar", 0);
  EXPECT_EQ("foo/bar", result);
}

#ifdef _WIN32
TEST_F(NodeTest_50, PathDecanonicalizedWithSlashBits_50) {
  // On Windows, slash_bits indicates which slashes should be backslashes
  // Bit 0 corresponds to the first slash
  Node node("foo/bar", 1);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("foo\\bar", result);
}

TEST_F(NodeTest_50, PathDecanonicalizedStaticWithSlashBits_50) {
  std::string result = Node::PathDecanonicalized("foo/bar", 1);
  EXPECT_EQ("foo\\bar", result);
}
#endif

TEST_F(NodeTest_50, EmptyPath_50) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

TEST_F(NodeTest_50, OutEdgesReturnsByConstRef_50) {
  Node node("test.cc", 0);
  Edge edge;
  node.AddOutEdge(&edge);
  const std::vector<Edge*>& edges = node.out_edges();
  ASSERT_EQ(1u, edges.size());
  EXPECT_EQ(&edge, edges[0]);
}

TEST_F(NodeTest_50, ValidationOutEdgesReturnsByConstRef_50) {
  Node node("test.cc", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  const std::vector<Edge*>& edges = node.validation_out_edges();
  ASSERT_EQ(1u, edges.size());
  EXPECT_EQ(&edge, edges[0]);
}

TEST_F(NodeTest_50, UpdatePhonyMtime_50) {
  Node node("test.cc", 0);
  node.UpdatePhonyMtime(100);
  EXPECT_EQ(100, node.mtime());
}

TEST_F(NodeTest_50, UpdatePhonyMtimeKeepsMaximum_50) {
  Node node("test.cc", 0);
  node.UpdatePhonyMtime(100);
  node.UpdatePhonyMtime(50);
  // Phony mtime should track the maximum
  EXPECT_GE(node.mtime(), 50);
}

TEST_F(NodeTest_50, SetInEdgeToNull_50) {
  Node node("test.cc", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
  node.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_50, SlashBitsZero_50) {
  Node node("a/b/c", 0);
  EXPECT_EQ(0u, node.slash_bits());
}

TEST_F(NodeTest_50, LargeSlashBits_50) {
  Node node("test", 0xFFFFFFFF);
  EXPECT_EQ(0xFFFFFFFFu, node.slash_bits());
}

TEST_F(NodeTest_50, SetIdNegative_50) {
  Node node("test.cc", 0);
  node.set_id(-5);
  EXPECT_EQ(-5, node.id());
}

TEST_F(NodeTest_50, PathReturnsConstRef_50) {
  Node node("hello.cc", 0);
  const std::string& p = node.path();
  EXPECT_EQ("hello.cc", p);
}

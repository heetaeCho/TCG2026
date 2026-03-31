#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Minimal mock for DiskInterface if needed
struct MockDiskInterface : public DiskInterface {
  virtual TimeStamp Stat(const std::string& path, std::string* err) const override {
    return 0;
  }
  virtual bool WriteFile(const std::string& path, const std::string& contents) override {
    return true;
  }
  virtual bool MakeDir(const std::string& path) override {
    return true;
  }
  virtual std::string ReadFile(const std::string& path, std::string* err) override {
    return "";
  }
  virtual int RemoveFile(const std::string& path) override {
    return 0;
  }
};

class NodeTest_41 : public ::testing::Test {
 protected:
  void SetUp() override {
    node_ = new Node("test/path", 0);
  }
  void TearDown() override {
    delete node_;
  }
  Node* node_;
};

// Test that MarkDirty sets dirty to true
TEST_F(NodeTest_41, MarkDirtySetsNodeDirty_41) {
  EXPECT_FALSE(node_->dirty());
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
}

// Test that dirty() returns false by default
TEST_F(NodeTest_41, DirtyDefaultFalse_41) {
  EXPECT_FALSE(node_->dirty());
}

// Test set_dirty with true
TEST_F(NodeTest_41, SetDirtyTrue_41) {
  node_->set_dirty(true);
  EXPECT_TRUE(node_->dirty());
}

// Test set_dirty with false after MarkDirty
TEST_F(NodeTest_41, SetDirtyFalseAfterMarkDirty_41) {
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
  node_->set_dirty(false);
  EXPECT_FALSE(node_->dirty());
}

// Test calling MarkDirty multiple times is idempotent
TEST_F(NodeTest_41, MarkDirtyMultipleTimes_41) {
  node_->MarkDirty();
  node_->MarkDirty();
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
}

// Test path() returns the correct path
TEST_F(NodeTest_41, PathReturnsCorrectPath_41) {
  EXPECT_EQ("test/path", node_->path());
}

// Test slash_bits() returns the correct value
TEST_F(NodeTest_41, SlashBitsReturnsCorrectValue_41) {
  EXPECT_EQ(0u, node_->slash_bits());
}

// Test slash_bits with non-zero value
TEST(NodeSlashBitsTest_41, NonZeroSlashBits_41) {
  Node node("foo\\bar", 1);
  EXPECT_EQ(1u, node.slash_bits());
}

// Test mtime() default value
TEST_F(NodeTest_41, MtimeDefaultValue_41) {
  EXPECT_EQ(-1, node_->mtime());
}

// Test id() default value
TEST_F(NodeTest_41, IdDefaultValue_41) {
  EXPECT_EQ(-1, node_->id());
}

// Test set_id and id()
TEST_F(NodeTest_41, SetIdAndGetId_41) {
  node_->set_id(42);
  EXPECT_EQ(42, node_->id());
}

// Test in_edge() default is nullptr
TEST_F(NodeTest_41, InEdgeDefaultNull_41) {
  EXPECT_EQ(nullptr, node_->in_edge());
}

// Test set_in_edge
TEST_F(NodeTest_41, SetInEdge_41) {
  Edge edge;
  node_->set_in_edge(&edge);
  EXPECT_EQ(&edge, node_->in_edge());
}

// Test out_edges() default is empty
TEST_F(NodeTest_41, OutEdgesDefaultEmpty_41) {
  EXPECT_TRUE(node_->out_edges().empty());
}

// Test AddOutEdge
TEST_F(NodeTest_41, AddOutEdge_41) {
  Edge edge;
  node_->AddOutEdge(&edge);
  ASSERT_EQ(1u, node_->out_edges().size());
  EXPECT_EQ(&edge, node_->out_edges()[0]);
}

// Test AddOutEdge multiple edges
TEST_F(NodeTest_41, AddMultipleOutEdges_41) {
  Edge edge1, edge2, edge3;
  node_->AddOutEdge(&edge1);
  node_->AddOutEdge(&edge2);
  node_->AddOutEdge(&edge3);
  ASSERT_EQ(3u, node_->out_edges().size());
  EXPECT_EQ(&edge1, node_->out_edges()[0]);
  EXPECT_EQ(&edge2, node_->out_edges()[1]);
  EXPECT_EQ(&edge3, node_->out_edges()[2]);
}

// Test validation_out_edges() default is empty
TEST_F(NodeTest_41, ValidationOutEdgesDefaultEmpty_41) {
  EXPECT_TRUE(node_->validation_out_edges().empty());
}

// Test AddValidationOutEdge
TEST_F(NodeTest_41, AddValidationOutEdge_41) {
  Edge edge;
  node_->AddValidationOutEdge(&edge);
  ASSERT_EQ(1u, node_->validation_out_edges().size());
  EXPECT_EQ(&edge, node_->validation_out_edges()[0]);
}

// Test dyndep_pending() default
TEST_F(NodeTest_41, DyndepPendingDefault_41) {
  EXPECT_FALSE(node_->dyndep_pending());
}

// Test set_dyndep_pending
TEST_F(NodeTest_41, SetDyndepPending_41) {
  node_->set_dyndep_pending(true);
  EXPECT_TRUE(node_->dyndep_pending());
  node_->set_dyndep_pending(false);
  EXPECT_FALSE(node_->dyndep_pending());
}

// Test generated_by_dep_loader() default
TEST_F(NodeTest_41, GeneratedByDepLoaderDefault_41) {
  EXPECT_TRUE(node_->generated_by_dep_loader());
}

// Test set_generated_by_dep_loader
TEST_F(NodeTest_41, SetGeneratedByDepLoader_41) {
  node_->set_generated_by_dep_loader(false);
  EXPECT_FALSE(node_->generated_by_dep_loader());
  node_->set_generated_by_dep_loader(true);
  EXPECT_TRUE(node_->generated_by_dep_loader());
}

// Test exists() and status_known() defaults
TEST_F(NodeTest_41, ExistsAndStatusKnownDefaults_41) {
  // By default, existence status is unknown
  EXPECT_FALSE(node_->status_known());
}

// Test MarkMissing sets status
TEST_F(NodeTest_41, MarkMissingSetsStatus_41) {
  node_->MarkMissing();
  EXPECT_TRUE(node_->status_known());
  EXPECT_FALSE(node_->exists());
}

// Test ResetState resets dirty and other state
TEST_F(NodeTest_41, ResetStateClearsDirty_41) {
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
  node_->ResetState();
  EXPECT_FALSE(node_->dirty());
}

// Test ResetState resets mtime
TEST_F(NodeTest_41, ResetStateResetsMtime_41) {
  node_->ResetState();
  EXPECT_EQ(-1, node_->mtime());
}

// Test ResetState resets existence status
TEST_F(NodeTest_41, ResetStateResetsExistenceStatus_41) {
  node_->MarkMissing();
  EXPECT_TRUE(node_->status_known());
  node_->ResetState();
  EXPECT_FALSE(node_->status_known());
}

// Test PathDecanonicalized
TEST_F(NodeTest_41, PathDecanonicalized_41) {
  std::string result = node_->PathDecanonicalized();
  EXPECT_EQ("test/path", result);
}

// Test PathDecanonicalized with slash_bits
TEST(NodePathDecanonicalizedTest_41, WithSlashBits_41) {
  // When slash_bits has bit set, corresponding '/' should become '\\'
  Node node("a/b", 1);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("a\\b", result);
}

// Test static PathDecanonicalized
TEST(NodeStaticPathDecanonicalizedTest_41, Basic_41) {
  std::string result = Node::PathDecanonicalized("a/b/c", 0);
  EXPECT_EQ("a/b/c", result);
}

// Test Stat via DiskInterface
TEST_F(NodeTest_41, StatWithDiskInterface_41) {
  MockDiskInterface disk;
  std::string err;
  bool result = node_->Stat(&disk, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  EXPECT_TRUE(node_->status_known());
}

// Test StatIfNecessary only stats once
TEST_F(NodeTest_41, StatIfNecessaryOnlyStatsOnce_41) {
  MockDiskInterface disk;
  std::string err;
  // First call should stat
  bool result1 = node_->StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(node_->status_known());
  // Second call should not re-stat (already known)
  bool result2 = node_->StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result2);
}

// Test empty path node
TEST(NodeEmptyPathTest_41, EmptyPath_41) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

// Test set_id with zero
TEST_F(NodeTest_41, SetIdZero_41) {
  node_->set_id(0);
  EXPECT_EQ(0, node_->id());
}

// Test set_id with negative value
TEST_F(NodeTest_41, SetIdNegative_41) {
  node_->set_id(-5);
  EXPECT_EQ(-5, node_->id());
}

// Test UpdatePhonyMtime
TEST_F(NodeTest_41, UpdatePhonyMtime_41) {
  node_->UpdatePhonyMtime(100);
  // After updating phony mtime, we should be able to observe it
  // The exact behavior depends on implementation, but mtime should reflect the update
  // if the node doesn't have a real mtime
}

// Test MarkDirty followed by set_dirty(false) then MarkDirty again
TEST_F(NodeTest_41, MarkDirtyResetMarkDirtyAgain_41) {
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
  node_->set_dirty(false);
  EXPECT_FALSE(node_->dirty());
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
}

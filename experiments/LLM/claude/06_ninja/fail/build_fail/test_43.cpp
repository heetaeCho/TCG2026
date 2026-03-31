#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Minimal DiskInterface mock if needed
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

class NodeTest_43 : public ::testing::Test {
 protected:
  void SetUp() override {
    node_ = new Node("test/path", 0);
  }
  void TearDown() override {
    delete node_;
  }
  Node* node_;
};

// Test set_dyndep_pending sets pending to true
TEST_F(NodeTest_43, SetDyndepPendingTrue_43) {
  node_->set_dyndep_pending(true);
  EXPECT_TRUE(node_->dyndep_pending());
}

// Test set_dyndep_pending sets pending to false
TEST_F(NodeTest_43, SetDyndepPendingFalse_43) {
  node_->set_dyndep_pending(true);
  node_->set_dyndep_pending(false);
  EXPECT_FALSE(node_->dyndep_pending());
}

// Test default dyndep_pending is false
TEST_F(NodeTest_43, DefaultDyndepPendingIsFalse_43) {
  EXPECT_FALSE(node_->dyndep_pending());
}

// Test toggling dyndep_pending multiple times
TEST_F(NodeTest_43, ToggleDyndepPendingMultipleTimes_43) {
  node_->set_dyndep_pending(true);
  EXPECT_TRUE(node_->dyndep_pending());
  node_->set_dyndep_pending(false);
  EXPECT_FALSE(node_->dyndep_pending());
  node_->set_dyndep_pending(true);
  EXPECT_TRUE(node_->dyndep_pending());
}

// Test path returns the correct path
TEST_F(NodeTest_43, PathReturnsCorrectPath_43) {
  EXPECT_EQ("test/path", node_->path());
}

// Test slash_bits returns correctly
TEST_F(NodeTest_43, SlashBitsReturnsCorrectValue_43) {
  EXPECT_EQ(0u, node_->slash_bits());
}

// Test Node with non-zero slash_bits
TEST_F(NodeTest_43, SlashBitsNonZero_43) {
  Node node("foo\\bar", 1);
  EXPECT_EQ(1u, node.slash_bits());
}

// Test set_dirty and dirty
TEST_F(NodeTest_43, SetDirtyTrue_43) {
  node_->set_dirty(true);
  EXPECT_TRUE(node_->dirty());
}

TEST_F(NodeTest_43, SetDirtyFalse_43) {
  node_->set_dirty(true);
  node_->set_dirty(false);
  EXPECT_FALSE(node_->dirty());
}

// Test default dirty is false
TEST_F(NodeTest_43, DefaultDirtyIsFalse_43) {
  EXPECT_FALSE(node_->dirty());
}

// Test MarkDirty
TEST_F(NodeTest_43, MarkDirtySetsNodeDirty_43) {
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
}

// Test in_edge default is nullptr
TEST_F(NodeTest_43, DefaultInEdgeIsNull_43) {
  EXPECT_EQ(nullptr, node_->in_edge());
}

// Test set_in_edge
TEST_F(NodeTest_43, SetInEdge_43) {
  Edge edge;
  node_->set_in_edge(&edge);
  EXPECT_EQ(&edge, node_->in_edge());
}

// Test set_in_edge to nullptr
TEST_F(NodeTest_43, SetInEdgeToNull_43) {
  Edge edge;
  node_->set_in_edge(&edge);
  node_->set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node_->in_edge());
}

// Test id default is -1
TEST_F(NodeTest_43, DefaultIdIsNegativeOne_43) {
  EXPECT_EQ(-1, node_->id());
}

// Test set_id
TEST_F(NodeTest_43, SetId_43) {
  node_->set_id(42);
  EXPECT_EQ(42, node_->id());
}

// Test set_id to zero
TEST_F(NodeTest_43, SetIdToZero_43) {
  node_->set_id(0);
  EXPECT_EQ(0, node_->id());
}

// Test out_edges is initially empty
TEST_F(NodeTest_43, OutEdgesInitiallyEmpty_43) {
  EXPECT_TRUE(node_->out_edges().empty());
}

// Test AddOutEdge
TEST_F(NodeTest_43, AddOutEdge_43) {
  Edge edge;
  node_->AddOutEdge(&edge);
  ASSERT_EQ(1u, node_->out_edges().size());
  EXPECT_EQ(&edge, node_->out_edges()[0]);
}

// Test AddOutEdge multiple times
TEST_F(NodeTest_43, AddMultipleOutEdges_43) {
  Edge edge1, edge2, edge3;
  node_->AddOutEdge(&edge1);
  node_->AddOutEdge(&edge2);
  node_->AddOutEdge(&edge3);
  ASSERT_EQ(3u, node_->out_edges().size());
  EXPECT_EQ(&edge1, node_->out_edges()[0]);
  EXPECT_EQ(&edge2, node_->out_edges()[1]);
  EXPECT_EQ(&edge3, node_->out_edges()[2]);
}

// Test validation_out_edges is initially empty
TEST_F(NodeTest_43, ValidationOutEdgesInitiallyEmpty_43) {
  EXPECT_TRUE(node_->validation_out_edges().empty());
}

// Test AddValidationOutEdge
TEST_F(NodeTest_43, AddValidationOutEdge_43) {
  Edge edge;
  node_->AddValidationOutEdge(&edge);
  ASSERT_EQ(1u, node_->validation_out_edges().size());
  EXPECT_EQ(&edge, node_->validation_out_edges()[0]);
}

// Test generated_by_dep_loader default is true
TEST_F(NodeTest_43, DefaultGeneratedByDepLoaderIsTrue_43) {
  EXPECT_TRUE(node_->generated_by_dep_loader());
}

// Test set_generated_by_dep_loader
TEST_F(NodeTest_43, SetGeneratedByDepLoaderFalse_43) {
  node_->set_generated_by_dep_loader(false);
  EXPECT_FALSE(node_->generated_by_dep_loader());
}

TEST_F(NodeTest_43, SetGeneratedByDepLoaderTrue_43) {
  node_->set_generated_by_dep_loader(false);
  node_->set_generated_by_dep_loader(true);
  EXPECT_TRUE(node_->generated_by_dep_loader());
}

// Test status_known initially returns false (mtime is -1 initially)
TEST_F(NodeTest_43, StatusKnownInitiallyFalse_43) {
  EXPECT_FALSE(node_->status_known());
}

// Test MarkMissing
TEST_F(NodeTest_43, MarkMissingSetsStatusKnown_43) {
  node_->MarkMissing();
  EXPECT_TRUE(node_->status_known());
  EXPECT_FALSE(node_->exists());
}

// Test exists after MarkMissing
TEST_F(NodeTest_43, ExistsReturnsFalseAfterMarkMissing_43) {
  node_->MarkMissing();
  EXPECT_FALSE(node_->exists());
}

// Test Stat with MockDiskInterface
TEST_F(NodeTest_43, StatWithDiskInterface_43) {
  MockDiskInterface disk;
  std::string err;
  bool result = node_->Stat(&disk, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(err.empty());
  EXPECT_TRUE(node_->status_known());
}

// Test StatIfNecessary only stats when necessary
TEST_F(NodeTest_43, StatIfNecessaryStatsOnlyOnce_43) {
  MockDiskInterface disk;
  std::string err;
  bool result1 = node_->StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(node_->status_known());
  // Second call should still succeed (already stat'd)
  bool result2 = node_->StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result2);
}

// Test ResetState clears status
TEST_F(NodeTest_43, ResetStateClearsStatus_43) {
  MockDiskInterface disk;
  std::string err;
  node_->Stat(&disk, &err);
  EXPECT_TRUE(node_->status_known());
  node_->ResetState();
  EXPECT_FALSE(node_->status_known());
  EXPECT_FALSE(node_->dirty());
}

// Test mtime default is -1
TEST_F(NodeTest_43, DefaultMtimeIsNegativeOne_43) {
  EXPECT_EQ(-1, node_->mtime());
}

// Test PathDecanonicalized
TEST_F(NodeTest_43, PathDecanonicalized_43) {
  Node node("foo/bar", 0);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("foo/bar", result);
}

// Test PathDecanonicalized static version
TEST_F(NodeTest_43, PathDecanonicalizedStatic_43) {
  std::string result = Node::PathDecanonicalized("foo/bar", 0);
  EXPECT_EQ("foo/bar", result);
}

// Test UpdatePhonyMtime
TEST_F(NodeTest_43, UpdatePhonyMtime_43) {
  node_->UpdatePhonyMtime(100);
  EXPECT_EQ(100, node_->mtime());
}

// Test Node with empty path
TEST_F(NodeTest_43, EmptyPath_43) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

// Test ResetState also resets dirty
TEST_F(NodeTest_43, ResetStateClearsDirty_43) {
  node_->set_dirty(true);
  EXPECT_TRUE(node_->dirty());
  node_->ResetState();
  EXPECT_FALSE(node_->dirty());
}

// Test set_dyndep_pending idempotent setting to same value
TEST_F(NodeTest_43, SetDyndepPendingIdempotent_43) {
  node_->set_dyndep_pending(true);
  node_->set_dyndep_pending(true);
  EXPECT_TRUE(node_->dyndep_pending());
  node_->set_dyndep_pending(false);
  node_->set_dyndep_pending(false);
  EXPECT_FALSE(node_->dyndep_pending());
}

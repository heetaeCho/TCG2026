#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Mock DiskInterface for testing
struct MockDiskInterface : public DiskInterface {
  TimeStamp Stat(const std::string& path, std::string* err) const override {
    return stat_result_;
  }
  bool WriteFile(const std::string& path, const std::string& contents) override {
    return true;
  }
  bool MakeDir(const std::string& path) override {
    return true;
  }
  Status ReadFile(const std::string& path, std::string* contents, std::string* err) override {
    return Okay;
  }
  int RemoveFile(const std::string& path) override {
    return 0;
  }

  TimeStamp stat_result_ = 0;
};

class NodeTest_32 : public ::testing::Test {
protected:
  void SetUp() override {
    node_ = new Node("test_path", 0);
  }
  void TearDown() override {
    delete node_;
  }
  Node* node_;
};

// Test MarkMissing when mtime_ is default (-1)
TEST_F(NodeTest_32, MarkMissing_DefaultState_SetsMtimeToZero_32) {
  // Default mtime_ is -1, so MarkMissing should set it to 0
  node_->MarkMissing();
  EXPECT_EQ(0, node_->mtime());
}

// Test MarkMissing sets exists to ExistenceStatusMissing
TEST_F(NodeTest_32, MarkMissing_SetsExistenceStatusMissing_32) {
  node_->MarkMissing();
  EXPECT_FALSE(node_->exists());
  EXPECT_TRUE(node_->status_known());
}

// Test MarkMissing when mtime_ is not -1 (already statted)
TEST_F(NodeTest_32, MarkMissing_AfterStat_MtimeNotChanged_32) {
  // First stat the node to set mtime to something other than -1
  MockDiskInterface disk;
  disk.stat_result_ = 100;
  std::string err;
  node_->Stat(&disk, &err);
  
  // Now mtime_ should be 100, not -1
  EXPECT_EQ(100, node_->mtime());
  
  // MarkMissing should NOT change mtime since it's not -1
  node_->MarkMissing();
  EXPECT_EQ(100, node_->mtime());
}

// Test exists() returns false after MarkMissing
TEST_F(NodeTest_32, MarkMissing_ExistsReturnsFalse_32) {
  node_->MarkMissing();
  EXPECT_FALSE(node_->exists());
}

// Test status_known() returns true after MarkMissing
TEST_F(NodeTest_32, MarkMissing_StatusKnownReturnsTrue_32) {
  node_->MarkMissing();
  EXPECT_TRUE(node_->status_known());
}

// Test default state before MarkMissing
TEST_F(NodeTest_32, DefaultState_StatusUnknown_32) {
  EXPECT_FALSE(node_->status_known());
}

// Test default mtime is -1
TEST_F(NodeTest_32, DefaultState_MtimeIsNegativeOne_32) {
  EXPECT_EQ(-1, node_->mtime());
}

// Test path() accessor
TEST_F(NodeTest_32, Path_ReturnsConstructedPath_32) {
  EXPECT_EQ("test_path", node_->path());
}

// Test slash_bits() accessor
TEST_F(NodeTest_32, SlashBits_ReturnsConstructedValue_32) {
  EXPECT_EQ(0u, node_->slash_bits());
}

// Test with non-zero slash_bits
TEST_F(NodeTest_32, SlashBits_NonZero_32) {
  Node node_with_slashes("foo\\bar", 1);
  EXPECT_EQ(1u, node_with_slashes.slash_bits());
}

// Test dirty default state
TEST_F(NodeTest_32, DefaultState_DirtyIsFalse_32) {
  EXPECT_FALSE(node_->dirty());
}

// Test set_dirty
TEST_F(NodeTest_32, SetDirty_True_32) {
  node_->set_dirty(true);
  EXPECT_TRUE(node_->dirty());
}

// Test set_dirty false
TEST_F(NodeTest_32, SetDirty_False_32) {
  node_->set_dirty(true);
  node_->set_dirty(false);
  EXPECT_FALSE(node_->dirty());
}

// Test MarkDirty
TEST_F(NodeTest_32, MarkDirty_SetsDirtyTrue_32) {
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
}

// Test dyndep_pending default
TEST_F(NodeTest_32, DefaultState_DyndepPendingIsFalse_32) {
  EXPECT_FALSE(node_->dyndep_pending());
}

// Test set_dyndep_pending
TEST_F(NodeTest_32, SetDyndepPending_True_32) {
  node_->set_dyndep_pending(true);
  EXPECT_TRUE(node_->dyndep_pending());
}

// Test in_edge default
TEST_F(NodeTest_32, DefaultState_InEdgeIsNull_32) {
  EXPECT_EQ(nullptr, node_->in_edge());
}

// Test set_in_edge
TEST_F(NodeTest_32, SetInEdge_32) {
  Edge edge;
  node_->set_in_edge(&edge);
  EXPECT_EQ(&edge, node_->in_edge());
}

// Test id default
TEST_F(NodeTest_32, DefaultState_IdIsNegativeOne_32) {
  EXPECT_EQ(-1, node_->id());
}

// Test set_id
TEST_F(NodeTest_32, SetId_32) {
  node_->set_id(42);
  EXPECT_EQ(42, node_->id());
}

// Test out_edges default is empty
TEST_F(NodeTest_32, DefaultState_OutEdgesEmpty_32) {
  EXPECT_TRUE(node_->out_edges().empty());
}

// Test AddOutEdge
TEST_F(NodeTest_32, AddOutEdge_AddsEdge_32) {
  Edge edge;
  node_->AddOutEdge(&edge);
  EXPECT_EQ(1u, node_->out_edges().size());
  EXPECT_EQ(&edge, node_->out_edges()[0]);
}

// Test AddOutEdge multiple edges
TEST_F(NodeTest_32, AddOutEdge_MultipleEdges_32) {
  Edge edge1, edge2, edge3;
  node_->AddOutEdge(&edge1);
  node_->AddOutEdge(&edge2);
  node_->AddOutEdge(&edge3);
  EXPECT_EQ(3u, node_->out_edges().size());
}

// Test validation_out_edges default is empty
TEST_F(NodeTest_32, DefaultState_ValidationOutEdgesEmpty_32) {
  EXPECT_TRUE(node_->validation_out_edges().empty());
}

// Test AddValidationOutEdge
TEST_F(NodeTest_32, AddValidationOutEdge_AddsEdge_32) {
  Edge edge;
  node_->AddValidationOutEdge(&edge);
  EXPECT_EQ(1u, node_->validation_out_edges().size());
  EXPECT_EQ(&edge, node_->validation_out_edges()[0]);
}

// Test generated_by_dep_loader default
TEST_F(NodeTest_32, DefaultState_GeneratedByDepLoaderIsTrue_32) {
  EXPECT_TRUE(node_->generated_by_dep_loader());
}

// Test set_generated_by_dep_loader
TEST_F(NodeTest_32, SetGeneratedByDepLoader_False_32) {
  node_->set_generated_by_dep_loader(false);
  EXPECT_FALSE(node_->generated_by_dep_loader());
}

// Test ResetState resets mtime back to -1
TEST_F(NodeTest_32, ResetState_ResetsMtime_32) {
  MockDiskInterface disk;
  disk.stat_result_ = 100;
  std::string err;
  node_->Stat(&disk, &err);
  EXPECT_EQ(100, node_->mtime());
  
  node_->ResetState();
  EXPECT_EQ(-1, node_->mtime());
}

// Test ResetState resets existence status
TEST_F(NodeTest_32, ResetState_ResetsExistenceStatus_32) {
  node_->MarkMissing();
  EXPECT_TRUE(node_->status_known());
  
  node_->ResetState();
  EXPECT_FALSE(node_->status_known());
}

// Test Stat with existing file
TEST_F(NodeTest_32, Stat_ExistingFile_32) {
  MockDiskInterface disk;
  disk.stat_result_ = 12345;
  std::string err;
  
  EXPECT_TRUE(node_->Stat(&disk, &err));
  EXPECT_EQ(12345, node_->mtime());
  EXPECT_TRUE(node_->exists());
  EXPECT_TRUE(node_->status_known());
}

// Test Stat with non-existing file (stat returns 0)
TEST_F(NodeTest_32, Stat_NonExistingFile_32) {
  MockDiskInterface disk;
  disk.stat_result_ = 0;
  std::string err;
  
  EXPECT_TRUE(node_->Stat(&disk, &err));
  EXPECT_EQ(0, node_->mtime());
  EXPECT_FALSE(node_->exists());
  EXPECT_TRUE(node_->status_known());
}

// Test StatIfNecessary only stats once
TEST_F(NodeTest_32, StatIfNecessary_OnlyStatsWhenNeeded_32) {
  MockDiskInterface disk;
  disk.stat_result_ = 100;
  std::string err;
  
  // First call should stat
  EXPECT_TRUE(node_->StatIfNecessary(&disk, &err));
  EXPECT_EQ(100, node_->mtime());
  
  // Change the stat result
  disk.stat_result_ = 200;
  
  // Second call should not re-stat since status is already known
  EXPECT_TRUE(node_->StatIfNecessary(&disk, &err));
  EXPECT_EQ(100, node_->mtime()); // Should still be 100
}

// Test MarkMissing called twice
TEST_F(NodeTest_32, MarkMissing_CalledTwice_32) {
  node_->MarkMissing();
  EXPECT_EQ(0, node_->mtime());
  EXPECT_FALSE(node_->exists());
  
  // Second call - mtime is now 0, not -1, so the if condition is false
  node_->MarkMissing();
  EXPECT_EQ(0, node_->mtime());
  EXPECT_FALSE(node_->exists());
}

// Test MarkMissing after ResetState
TEST_F(NodeTest_32, MarkMissing_AfterResetState_32) {
  node_->MarkMissing();
  node_->ResetState();
  
  // After reset, mtime should be -1 again
  EXPECT_EQ(-1, node_->mtime());
  
  // MarkMissing should work again
  node_->MarkMissing();
  EXPECT_EQ(0, node_->mtime());
  EXPECT_FALSE(node_->exists());
}

// Test PathDecanonicalized
TEST_F(NodeTest_32, PathDecanonicalized_NoSlashBits_32) {
  std::string result = node_->PathDecanonicalized();
  EXPECT_EQ("test_path", result);
}

// Test empty path
TEST_F(NodeTest_32, EmptyPath_32) {
  Node empty_node("", 0);
  EXPECT_EQ("", empty_node.path());
}

// Test UpdatePhonyMtime
TEST_F(NodeTest_32, UpdatePhonyMtime_32) {
  node_->MarkMissing();
  EXPECT_EQ(0, node_->mtime());
  
  node_->UpdatePhonyMtime(500);
  EXPECT_EQ(500, node_->mtime());
}

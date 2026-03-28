#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Minimal mock for DiskInterface if needed
struct MockDiskInterface : public DiskInterface {
  virtual TimeStamp Stat(const std::string& path, std::string* err) const override {
    if (path == "existing_file") return 100;
    if (path == "missing_file") return 0;
    return 0;
  }
  virtual bool WriteFile(const std::string& path, const std::string& contents) override {
    return true;
  }
  virtual bool MakeDir(const std::string& path) override {
    return true;
  }
  virtual Status ReadFile(const std::string& path, std::string* contents, std::string* err) override {
    return NotFound;
  }
  virtual int RemoveFile(const std::string& path) override {
    return 0;
  }
};

class NodeTest_47 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(NodeTest_47, Constructor_InitializesPathAndSlashBits_47) {
  Node node("some/path", 0x1);
  EXPECT_EQ("some/path", node.path());
  EXPECT_EQ(0x1u, node.slash_bits());
}

TEST_F(NodeTest_47, DefaultId_IsNegativeOne_47) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.id());
}

TEST_F(NodeTest_47, SetId_ReturnsSetValue_47) {
  Node node("test", 0);
  node.set_id(42);
  EXPECT_EQ(42, node.id());
}

TEST_F(NodeTest_47, SetId_Zero_47) {
  Node node("test", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

TEST_F(NodeTest_47, DefaultDirty_IsFalse_47) {
  Node node("test", 0);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_47, SetDirty_True_47) {
  Node node("test", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_47, SetDirty_FalseAfterTrue_47) {
  Node node("test", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_47, MarkDirty_SetsDirtyTrue_47) {
  Node node("test", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_47, DefaultDyndepPending_IsFalse_47) {
  Node node("test", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_47, SetDyndepPending_True_47) {
  Node node("test", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
}

TEST_F(NodeTest_47, SetDyndepPending_FalseAfterTrue_47) {
  Node node("test", 0);
  node.set_dyndep_pending(true);
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_47, DefaultInEdge_IsNull_47) {
  Node node("test", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_47, SetInEdge_47) {
  Node node("test", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

TEST_F(NodeTest_47, SetInEdge_Null_47) {
  Node node("test", 0);
  Edge edge;
  node.set_in_edge(&edge);
  node.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_47, DefaultGeneratedByDepLoader_IsTrue_47) {
  Node node("test", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_47, SetGeneratedByDepLoader_False_47) {
  Node node("test", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_47, SetGeneratedByDepLoader_TrueAfterFalse_47) {
  Node node("test", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_47, DefaultOutEdges_IsEmpty_47) {
  Node node("test", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

TEST_F(NodeTest_47, AddOutEdge_IncreasesOutEdgesSize_47) {
  Node node("test", 0);
  Edge edge1, edge2;
  node.AddOutEdge(&edge1);
  EXPECT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  node.AddOutEdge(&edge2);
  EXPECT_EQ(2u, node.out_edges().size());
  EXPECT_EQ(&edge2, node.out_edges()[1]);
}

TEST_F(NodeTest_47, DefaultValidationOutEdges_IsEmpty_47) {
  Node node("test", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

TEST_F(NodeTest_47, AddValidationOutEdge_IncreasesSize_47) {
  Node node("test", 0);
  Edge edge1;
  node.AddValidationOutEdge(&edge1);
  EXPECT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge1, node.validation_out_edges()[0]);
}

TEST_F(NodeTest_47, DefaultStatusKnown_IsFalse_47) {
  Node node("test", 0);
  // mtime_ is -1 by default, status_known checks if mtime != -1
  EXPECT_FALSE(node.status_known());
}

TEST_F(NodeTest_47, MarkMissing_MakesStatusKnown_47) {
  Node node("test", 0);
  EXPECT_FALSE(node.status_known());
  node.MarkMissing();
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
}

TEST_F(NodeTest_47, MarkMissing_ExistsReturnsFalse_47) {
  Node node("test", 0);
  node.MarkMissing();
  EXPECT_FALSE(node.exists());
}

TEST_F(NodeTest_47, Stat_ExistingFile_47) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_TRUE(err.empty());
  EXPECT_TRUE(node.status_known());
  EXPECT_TRUE(node.exists());
  EXPECT_EQ(100, node.mtime());
}

TEST_F(NodeTest_47, Stat_MissingFile_47) {
  Node node("missing_file", 0);
  MockDiskInterface disk;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_TRUE(err.empty());
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
  EXPECT_EQ(0, node.mtime());
}

TEST_F(NodeTest_47, StatIfNecessary_OnlyStatsOnce_47) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  // First call should stat
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_EQ(100, node.mtime());
  // Second call should not re-stat (status already known)
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_EQ(100, node.mtime());
}

TEST_F(NodeTest_47, ResetState_ResetsToUnknown_47) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_TRUE(node.status_known());

  node.set_dirty(true);
  node.ResetState();
  EXPECT_FALSE(node.status_known());
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_47, PathDecanonicalized_Static_47) {
  // Test with slash_bits = 0 (no backslash conversion)
  std::string result = Node::PathDecanonicalized("a/b/c", 0);
  EXPECT_EQ("a/b/c", result);
}

TEST_F(NodeTest_47, PathDecanonicalized_WithSlashBits_47) {
  // slash_bits with bit 0 set means first slash should be backslash
  std::string result = Node::PathDecanonicalized("a/b/c", 0x1);
  EXPECT_EQ("a\\b/c", result);
}

TEST_F(NodeTest_47, PathDecanonicalized_InstanceMethod_47) {
  Node node("a/b", 0);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("a/b", result);
}

TEST_F(NodeTest_47, PathDecanonicalized_InstanceWithSlashBits_47) {
  Node node("a/b", 0x1);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("a\\b", result);
}

TEST_F(NodeTest_47, UpdatePhonyMtime_UpdatesIfGreater_47) {
  Node node("phony", 0);
  node.MarkMissing();  // Set mtime to 0
  node.UpdatePhonyMtime(50);
  EXPECT_EQ(50, node.mtime());
}

TEST_F(NodeTest_47, EmptyPath_47) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
  EXPECT_EQ(0u, node.slash_bits());
}

TEST_F(NodeTest_47, SlashBitsZero_47) {
  Node node("test/path", 0);
  EXPECT_EQ(0u, node.slash_bits());
}

TEST_F(NodeTest_47, MultipleOutEdgesOrdering_47) {
  Node node("test", 0);
  Edge e1, e2, e3;
  node.AddOutEdge(&e1);
  node.AddOutEdge(&e2);
  node.AddOutEdge(&e3);
  ASSERT_EQ(3u, node.out_edges().size());
  EXPECT_EQ(&e1, node.out_edges()[0]);
  EXPECT_EQ(&e2, node.out_edges()[1]);
  EXPECT_EQ(&e3, node.out_edges()[2]);
}

TEST_F(NodeTest_47, MultipleValidationOutEdgesOrdering_47) {
  Node node("test", 0);
  Edge e1, e2;
  node.AddValidationOutEdge(&e1);
  node.AddValidationOutEdge(&e2);
  ASSERT_EQ(2u, node.validation_out_edges().size());
  EXPECT_EQ(&e1, node.validation_out_edges()[0]);
  EXPECT_EQ(&e2, node.validation_out_edges()[1]);
}

TEST_F(NodeTest_47, DefaultMtime_IsNegativeOne_47) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.mtime());
}

TEST_F(NodeTest_47, PathDecanonicalized_AllSlashes_47) {
  // All slashes converted: "a/b/c" with slash_bits = 0x3 => bits 0 and 1 set
  std::string result = Node::PathDecanonicalized("a/b/c", 0x3);
  EXPECT_EQ("a\\b\\c", result);
}

TEST_F(NodeTest_47, ResetState_AfterMarkDirty_47) {
  Node node("test", 0);
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
  node.ResetState();
  EXPECT_FALSE(node.dirty());
}

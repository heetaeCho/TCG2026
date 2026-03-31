#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Minimal DiskInterface mock for Stat tests
struct MockDiskInterface : public DiskInterface {
  TimeStamp stat_result = 1;
  std::string read_result;
  bool make_dir_result = true;
  bool write_result = true;
  bool remove_result = true;

  TimeStamp Stat(const std::string& path, std::string* err) const override {
    return stat_result;
  }
  bool MakeDir(const std::string& path) override { return make_dir_result; }
  bool WriteFile(const std::string& path, const std::string& contents) override { return write_result; }
  std::string ReadFile(const std::string& path, std::string* err, bool* not_found = nullptr) override { return read_result; }
  int RemoveFile(const std::string& path) override { return remove_result ? 0 : -1; }
};

class NodeTest_46 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(NodeTest_46, Constructor_InitializesPath_46) {
  Node node("foo/bar.cc", 0);
  EXPECT_EQ("foo/bar.cc", node.path());
}

TEST_F(NodeTest_46, Constructor_InitializesSlashBits_46) {
  Node node("foo/bar.cc", 5);
  EXPECT_EQ(5u, node.slash_bits());
}

TEST_F(NodeTest_46, GeneratedByDepLoader_DefaultTrue_46) {
  Node node("test.cc", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_46, SetGeneratedByDepLoader_False_46) {
  Node node("test.cc", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_46, SetGeneratedByDepLoader_TrueAfterFalse_46) {
  Node node("test.cc", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_46, Dirty_DefaultFalse_46) {
  Node node("test.cc", 0);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_46, SetDirty_True_46) {
  Node node("test.cc", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_46, SetDirty_FalseAfterTrue_46) {
  Node node("test.cc", 0);
  node.set_dirty(true);
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_46, MarkDirty_SetsDirtyTrue_46) {
  Node node("test.cc", 0);
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_46, DyndepPending_DefaultFalse_46) {
  Node node("test.cc", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_46, SetDyndepPending_True_46) {
  Node node("test.cc", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
}

TEST_F(NodeTest_46, SetDyndepPending_False_46) {
  Node node("test.cc", 0);
  node.set_dyndep_pending(true);
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_46, InEdge_DefaultNull_46) {
  Node node("test.cc", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_46, SetInEdge_46) {
  Node node("test.cc", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

TEST_F(NodeTest_46, Id_DefaultNegativeOne_46) {
  Node node("test.cc", 0);
  EXPECT_EQ(-1, node.id());
}

TEST_F(NodeTest_46, SetId_46) {
  Node node("test.cc", 0);
  node.set_id(42);
  EXPECT_EQ(42, node.id());
}

TEST_F(NodeTest_46, SetId_Zero_46) {
  Node node("test.cc", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

TEST_F(NodeTest_46, OutEdges_InitiallyEmpty_46) {
  Node node("test.cc", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

TEST_F(NodeTest_46, AddOutEdge_46) {
  Node node("test.cc", 0);
  Edge edge;
  node.AddOutEdge(&edge);
  ASSERT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge, node.out_edges()[0]);
}

TEST_F(NodeTest_46, AddMultipleOutEdges_46) {
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

TEST_F(NodeTest_46, ValidationOutEdges_InitiallyEmpty_46) {
  Node node("test.cc", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

TEST_F(NodeTest_46, AddValidationOutEdge_46) {
  Node node("test.cc", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  ASSERT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

TEST_F(NodeTest_46, StatusKnown_InitiallyFalse_46) {
  Node node("test.cc", 0);
  // Before stat, status should not be known
  EXPECT_FALSE(node.status_known());
}

TEST_F(NodeTest_46, MarkMissing_46) {
  Node node("test.cc", 0);
  node.MarkMissing();
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
}

TEST_F(NodeTest_46, Stat_SetsStatusKnown_46) {
  Node node("test.cc", 0);
  MockDiskInterface disk;
  disk.stat_result = 1;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_TRUE(node.status_known());
  EXPECT_TRUE(node.exists());
  EXPECT_EQ(1, node.mtime());
}

TEST_F(NodeTest_46, Stat_MissingFile_46) {
  Node node("nonexistent.cc", 0);
  MockDiskInterface disk;
  disk.stat_result = 0;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
  EXPECT_EQ(0, node.mtime());
}

TEST_F(NodeTest_46, StatIfNecessary_OnlyStatsOnce_46) {
  Node node("test.cc", 0);
  MockDiskInterface disk;
  disk.stat_result = 100;
  std::string err;
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_EQ(100, node.mtime());
  
  // Second call should not re-stat
  disk.stat_result = 200;
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_EQ(100, node.mtime()); // should still be 100
}

TEST_F(NodeTest_46, ResetState_ClearsStatusAndDirty_46) {
  Node node("test.cc", 0);
  MockDiskInterface disk;
  disk.stat_result = 100;
  std::string err;
  node.Stat(&disk, &err);
  node.set_dirty(true);
  
  node.ResetState();
  
  EXPECT_FALSE(node.status_known());
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_46, PathDecanonicalized_Instance_46) {
  Node node("foo/bar.cc", 0);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("foo/bar.cc", result);
}

TEST_F(NodeTest_46, PathDecanonicalized_Static_46) {
  std::string result = Node::PathDecanonicalized("foo/bar.cc", 0);
  EXPECT_EQ("foo/bar.cc", result);
}

TEST_F(NodeTest_46, PathDecanonicalized_WithSlashBits_46) {
  // slash_bits indicate which slashes should be backslashes
  // Bit 0 corresponds to the first slash, etc.
  std::string result = Node::PathDecanonicalized("foo/bar.cc", 1);
  EXPECT_EQ("foo\\bar.cc", result);
}

TEST_F(NodeTest_46, EmptyPath_46) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

TEST_F(NodeTest_46, UpdatePhonyMtime_46) {
  Node node("phony", 0);
  node.UpdatePhonyMtime(42);
  // We can't easily verify mtime without stat, but let's try after marking
  // The behavior depends on implementation
}

TEST_F(NodeTest_46, Exists_AfterStat_Exists_46) {
  Node node("test.cc", 0);
  MockDiskInterface disk;
  disk.stat_result = 5;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_TRUE(node.exists());
}

TEST_F(NodeTest_46, Exists_AfterStat_Missing_46) {
  Node node("test.cc", 0);
  MockDiskInterface disk;
  disk.stat_result = 0;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_FALSE(node.exists());
}

TEST_F(NodeTest_46, Mtime_DefaultNegativeOne_46) {
  Node node("test.cc", 0);
  EXPECT_EQ(-1, node.mtime());
}

TEST_F(NodeTest_46, SetInEdge_Nullptr_46) {
  Node node("test.cc", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
  node.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_46, Stat_Error_46) {
  Node node("test.cc", 0);
  MockDiskInterface disk;
  disk.stat_result = -1;
  std::string err;
  // When stat returns -1 it typically indicates error
  node.Stat(&disk, &err);
  // The exact behavior depends on implementation
}

TEST_F(NodeTest_46, ResetState_AllowsRestat_46) {
  Node node("test.cc", 0);
  MockDiskInterface disk;
  disk.stat_result = 100;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_EQ(100, node.mtime());
  
  node.ResetState();
  EXPECT_FALSE(node.status_known());
  
  disk.stat_result = 200;
  node.Stat(&disk, &err);
  EXPECT_EQ(200, node.mtime());
}

TEST_F(NodeTest_46, StatIfNecessary_AfterReset_46) {
  Node node("test.cc", 0);
  MockDiskInterface disk;
  disk.stat_result = 100;
  std::string err;
  node.StatIfNecessary(&disk, &err);
  EXPECT_EQ(100, node.mtime());
  
  node.ResetState();
  disk.stat_result = 300;
  node.StatIfNecessary(&disk, &err);
  EXPECT_EQ(300, node.mtime());
}

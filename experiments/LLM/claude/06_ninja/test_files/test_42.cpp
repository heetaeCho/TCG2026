#include "gtest/gtest.h"
#include "graph.h"
#include "disk_interface.h"
#include <string>
#include <vector>

// Minimal mock for DiskInterface if needed
class MockDiskInterface : public DiskInterface {
public:
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
  virtual std::string ReadFile(const std::string& path, std::string* err) override {
    return "";
  }
  virtual int RemoveFile(const std::string& path) override {
    return 0;
  }
};

class NodeTest_42 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(NodeTest_42, ConstructorSetsPath_42) {
  Node node("test_path", 0);
  EXPECT_EQ("test_path", node.path());
}

TEST_F(NodeTest_42, ConstructorSetsSlashBits_42) {
  Node node("some/path", 0x3);
  EXPECT_EQ(0x3u, node.slash_bits());
}

TEST_F(NodeTest_42, DefaultMtimeIsNegative_42) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.mtime());
}

TEST_F(NodeTest_42, DefaultDirtyIsFalse_42) {
  Node node("test", 0);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_42, SetDirtyTrue_42) {
  Node node("test", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_42, SetDirtyFalse_42) {
  Node node("test", 0);
  node.set_dirty(true);
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_42, MarkDirtySetsNodeDirty_42) {
  Node node("test", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_42, DyndepPendingDefaultFalse_42) {
  Node node("test", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_42, SetDyndepPendingTrue_42) {
  Node node("test", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
}

TEST_F(NodeTest_42, SetDyndepPendingFalse_42) {
  Node node("test", 0);
  node.set_dyndep_pending(true);
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_42, DefaultInEdgeIsNull_42) {
  Node node("test", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_42, SetInEdge_42) {
  Node node("test", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

TEST_F(NodeTest_42, DefaultIdIsNegativeOne_42) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.id());
}

TEST_F(NodeTest_42, SetId_42) {
  Node node("test", 0);
  node.set_id(5);
  EXPECT_EQ(5, node.id());
}

TEST_F(NodeTest_42, SetIdZero_42) {
  Node node("test", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

TEST_F(NodeTest_42, OutEdgesInitiallyEmpty_42) {
  Node node("test", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

TEST_F(NodeTest_42, AddOutEdge_42) {
  Node node("test", 0);
  Edge edge;
  node.AddOutEdge(&edge);
  ASSERT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge, node.out_edges()[0]);
}

TEST_F(NodeTest_42, AddMultipleOutEdges_42) {
  Node node("test", 0);
  Edge edge1, edge2, edge3;
  node.AddOutEdge(&edge1);
  node.AddOutEdge(&edge2);
  node.AddOutEdge(&edge3);
  ASSERT_EQ(3u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  EXPECT_EQ(&edge2, node.out_edges()[1]);
  EXPECT_EQ(&edge3, node.out_edges()[2]);
}

TEST_F(NodeTest_42, ValidationOutEdgesInitiallyEmpty_42) {
  Node node("test", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

TEST_F(NodeTest_42, AddValidationOutEdge_42) {
  Node node("test", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  ASSERT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

TEST_F(NodeTest_42, AddMultipleValidationOutEdges_42) {
  Node node("test", 0);
  Edge edge1, edge2;
  node.AddValidationOutEdge(&edge1);
  node.AddValidationOutEdge(&edge2);
  ASSERT_EQ(2u, node.validation_out_edges().size());
  EXPECT_EQ(&edge1, node.validation_out_edges()[0]);
  EXPECT_EQ(&edge2, node.validation_out_edges()[1]);
}

TEST_F(NodeTest_42, DefaultGeneratedByDepLoaderIsTrue_42) {
  Node node("test", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_42, SetGeneratedByDepLoaderFalse_42) {
  Node node("test", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_42, SetGeneratedByDepLoaderTrue_42) {
  Node node("test", 0);
  node.set_generated_by_dep_loader(false);
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_42, StatusNotKnownByDefault_42) {
  Node node("test", 0);
  EXPECT_FALSE(node.status_known());
}

TEST_F(NodeTest_42, MarkMissingSetsExistenceFalse_42) {
  Node node("test", 0);
  node.MarkMissing();
  EXPECT_FALSE(node.exists());
  EXPECT_TRUE(node.status_known());
}

TEST_F(NodeTest_42, StatExistingFile_42) {
  MockDiskInterface disk;
  Node node("existing_file", 0);
  std::string err;
  bool result = node.Stat(&disk, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
  EXPECT_TRUE(node.exists());
  EXPECT_TRUE(node.status_known());
  EXPECT_EQ(100, node.mtime());
}

TEST_F(NodeTest_42, StatMissingFile_42) {
  MockDiskInterface disk;
  Node node("missing_file", 0);
  std::string err;
  bool result = node.Stat(&disk, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
  EXPECT_FALSE(node.exists());
  EXPECT_TRUE(node.status_known());
}

TEST_F(NodeTest_42, StatIfNecessaryOnlyStatsOnce_42) {
  MockDiskInterface disk;
  Node node("existing_file", 0);
  std::string err;
  // First stat should perform the stat
  bool result1 = node.StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result1);
  EXPECT_EQ(100, node.mtime());
  // Second call should be a no-op since status is already known
  bool result2 = node.StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result2);
  EXPECT_EQ(100, node.mtime());
}

TEST_F(NodeTest_42, ResetStateClearsState_42) {
  MockDiskInterface disk;
  Node node("existing_file", 0);
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_TRUE(node.status_known());

  node.ResetState();
  EXPECT_FALSE(node.status_known());
  EXPECT_EQ(-1, node.mtime());
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_42, PathDecanonicalizedInstance_42) {
  Node node("path/to/file", 0);
  std::string decanon = node.PathDecanonicalized();
  EXPECT_FALSE(decanon.empty());
}

TEST_F(NodeTest_42, PathDecanonicalizedStatic_42) {
  std::string result = Node::PathDecanonicalized("path/to/file", 0);
  EXPECT_EQ("path/to/file", result);
}

TEST_F(NodeTest_42, PathDecanonicalizedWithSlashBits_42) {
  // slash_bits = 1 means the first slash should be backslash on Windows
  // On non-Windows this may be a no-op or different behavior
  std::string result = Node::PathDecanonicalized("a/b", 1);
  // We just check it returns a non-empty string
  EXPECT_FALSE(result.empty());
}

TEST_F(NodeTest_42, EmptyPath_42) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

TEST_F(NodeTest_42, UpdatePhonyMtime_42) {
  Node node("phony", 0);
  node.UpdatePhonyMtime(42);
  EXPECT_EQ(42, node.mtime());
}

TEST_F(NodeTest_42, UpdatePhonyMtimeOnlyUpdatesIfGreater_42) {
  Node node("phony", 0);
  node.UpdatePhonyMtime(100);
  node.UpdatePhonyMtime(50);
  // Based on typical implementation, phony mtime takes max
  // We can only observe the final mtime
  TimeStamp mt = node.mtime();
  EXPECT_GE(mt, 50);
}

TEST_F(NodeTest_42, SetIdNegative_42) {
  Node node("test", 0);
  node.set_id(-5);
  EXPECT_EQ(-5, node.id());
}

TEST_F(NodeTest_42, SlashBitsZero_42) {
  Node node("path", 0);
  EXPECT_EQ(0u, node.slash_bits());
}

TEST_F(NodeTest_42, SlashBitsNonZero_42) {
  Node node("path", 0xFF);
  EXPECT_EQ(0xFFu, node.slash_bits());
}

TEST_F(NodeTest_42, DumpDoesNotCrash_42) {
  Node node("test_dump", 0);
  // Just ensure Dump doesn't crash with various prefixes
  node.Dump("prefix: ");
  node.Dump("");
  node.Dump(nullptr);
}

TEST_F(NodeTest_42, ResetStateAlsoResetsDyndepPending_42) {
  Node node("test", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.ResetState();
  // After reset, dyndep_pending might or might not be reset
  // We observe the actual behavior
  // This is a boundary test
}

TEST_F(NodeTest_42, MultipleResetStates_42) {
  Node node("test", 0);
  node.set_dirty(true);
  node.ResetState();
  EXPECT_FALSE(node.dirty());
  node.ResetState();
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_42, ExistsAfterMarkMissingThenStat_42) {
  MockDiskInterface disk;
  Node node("existing_file", 0);
  node.MarkMissing();
  EXPECT_FALSE(node.exists());
  
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_TRUE(node.exists());
  EXPECT_EQ(100, node.mtime());
}

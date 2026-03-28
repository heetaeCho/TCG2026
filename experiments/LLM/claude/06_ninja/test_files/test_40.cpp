#include "gtest/gtest.h"
#include "graph.h"
#include "state.h"
#include "disk_interface.h"
#include <string>
#include <vector>

// A simple mock DiskInterface for testing Stat-related methods
struct TestDiskInterface : public DiskInterface {
  virtual TimeStamp Stat(const std::string& path, std::string* err) const override {
    if (path == "existing_file") return 100;
    if (path == "missing_file") return 0;
    if (path == "error_file") {
      *err = "stat error";
      return -1;
    }
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

class NodeTest_40 : public ::testing::Test {
protected:
  void SetUp() override {
    disk_interface_ = new TestDiskInterface();
  }
  void TearDown() override {
    delete disk_interface_;
  }
  TestDiskInterface* disk_interface_;
};

TEST_F(NodeTest_40, Constructor_PathAndSlashBits_40) {
  Node node("some/path", 0x1);
  EXPECT_EQ("some/path", node.path());
  EXPECT_EQ(0x1u, node.slash_bits());
}

TEST_F(NodeTest_40, DefaultDirtyIsFalse_40) {
  Node node("test", 0);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_40, SetDirtyTrue_40) {
  Node node("test", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_40, SetDirtyFalse_40) {
  Node node("test", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_40, SetDirtyToggle_40) {
  Node node("test", 0);
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_40, MarkDirty_40) {
  Node node("test", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_40, DefaultMtime_40) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.mtime());
}

TEST_F(NodeTest_40, DefaultId_40) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.id());
}

TEST_F(NodeTest_40, SetId_40) {
  Node node("test", 0);
  node.set_id(42);
  EXPECT_EQ(42, node.id());
}

TEST_F(NodeTest_40, SetIdZero_40) {
  Node node("test", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

TEST_F(NodeTest_40, DefaultInEdgeIsNull_40) {
  Node node("test", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_40, SetInEdge_40) {
  Node node("test", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

TEST_F(NodeTest_40, DefaultOutEdgesEmpty_40) {
  Node node("test", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

TEST_F(NodeTest_40, AddOutEdge_40) {
  Node node("test", 0);
  Edge edge;
  node.AddOutEdge(&edge);
  ASSERT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge, node.out_edges()[0]);
}

TEST_F(NodeTest_40, AddMultipleOutEdges_40) {
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

TEST_F(NodeTest_40, DefaultValidationOutEdgesEmpty_40) {
  Node node("test", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

TEST_F(NodeTest_40, AddValidationOutEdge_40) {
  Node node("test", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  ASSERT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

TEST_F(NodeTest_40, DefaultDyndepPendingIsFalse_40) {
  Node node("test", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_40, SetDyndepPending_40) {
  Node node("test", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_40, DefaultGeneratedByDepLoader_40) {
  Node node("test", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_40, SetGeneratedByDepLoader_40) {
  Node node("test", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_40, StatusNotKnownInitially_40) {
  Node node("test", 0);
  EXPECT_FALSE(node.status_known());
}

TEST_F(NodeTest_40, StatExistingFile_40) {
  Node node("existing_file", 0);
  std::string err;
  EXPECT_TRUE(node.Stat(disk_interface_, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(node.status_known());
  EXPECT_TRUE(node.exists());
  EXPECT_EQ(100, node.mtime());
}

TEST_F(NodeTest_40, StatMissingFile_40) {
  Node node("missing_file", 0);
  std::string err;
  EXPECT_TRUE(node.Stat(disk_interface_, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
}

TEST_F(NodeTest_40, MarkMissing_40) {
  Node node("test", 0);
  node.MarkMissing();
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
  EXPECT_EQ(0, node.mtime());
}

TEST_F(NodeTest_40, ResetState_40) {
  Node node("existing_file", 0);
  std::string err;
  node.Stat(disk_interface_, &err);
  EXPECT_TRUE(node.status_known());

  node.set_dirty(true);
  node.set_id(5);

  node.ResetState();

  // After reset, state should go back to unknown
  EXPECT_FALSE(node.status_known());
  EXPECT_EQ(-1, node.mtime());
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_40, StatIfNecessary_AlreadyStatted_40) {
  Node node("existing_file", 0);
  std::string err;
  // First stat
  EXPECT_TRUE(node.Stat(disk_interface_, &err));
  EXPECT_TRUE(node.status_known());

  // StatIfNecessary should not re-stat since status is already known
  EXPECT_TRUE(node.StatIfNecessary(disk_interface_, &err));
  EXPECT_EQ("", err);
}

TEST_F(NodeTest_40, StatIfNecessary_NotYetStatted_40) {
  Node node("existing_file", 0);
  std::string err;
  EXPECT_FALSE(node.status_known());

  EXPECT_TRUE(node.StatIfNecessary(disk_interface_, &err));
  EXPECT_TRUE(node.status_known());
  EXPECT_EQ(100, node.mtime());
}

TEST_F(NodeTest_40, PathDecanonicalized_40) {
  Node node("some/path", 0);
  std::string result = node.PathDecanonicalized();
  // With slash_bits == 0, no backslash replacement expected
  EXPECT_EQ("some/path", result);
}

TEST_F(NodeTest_40, PathDecanonicalized_WithSlashBits_40) {
  // slash_bits with bit 0 set means first slash becomes backslash
  Node node("a/b", 0x1);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("a\\b", result);
}

TEST_F(NodeTest_40, StaticPathDecanonicalized_40) {
  std::string result = Node::PathDecanonicalized("a/b/c", 0);
  EXPECT_EQ("a/b/c", result);
}

TEST_F(NodeTest_40, StaticPathDecanonicalized_WithSlashBits_40) {
  // bit 0 -> first slash, bit 1 -> second slash
  std::string result = Node::PathDecanonicalized("a/b/c", 0x3);
  EXPECT_EQ("a\\b\\c", result);
}

TEST_F(NodeTest_40, UpdatePhonyMtime_40) {
  Node node("phony", 0);
  node.UpdatePhonyMtime(500);
  EXPECT_EQ(500, node.mtime());
}

TEST_F(NodeTest_40, UpdatePhonyMtime_KeepsLarger_40) {
  Node node("phony", 0);
  node.UpdatePhonyMtime(500);
  node.UpdatePhonyMtime(300);
  // Should keep the larger mtime
  EXPECT_GE(node.mtime(), 300);
}

TEST_F(NodeTest_40, EmptyPath_40) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
  EXPECT_EQ(0u, node.slash_bits());
}

TEST_F(NodeTest_40, SetDirtyMultipleTimes_40) {
  Node node("test", 0);
  for (int i = 0; i < 100; ++i) {
    node.set_dirty(true);
    EXPECT_TRUE(node.dirty());
    node.set_dirty(false);
    EXPECT_FALSE(node.dirty());
  }
}

TEST_F(NodeTest_40, SetInEdgeToNull_40) {
  Node node("test", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
  node.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_40, StatErrorFile_40) {
  Node node("error_file", 0);
  std::string err;
  EXPECT_FALSE(node.Stat(disk_interface_, &err));
  EXPECT_NE("", err);
}

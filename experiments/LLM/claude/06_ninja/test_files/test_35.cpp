#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Minimal DiskInterface mock for Stat-related tests
struct MockDiskInterface : public DiskInterface {
  virtual TimeStamp Stat(const std::string& path, std::string* err) const override {
    if (path == "existing_file") return 12345;
    if (path == "error_file") { *err = "stat error"; return -1; }
    return 0; // file not found
  }
  virtual bool WriteFile(const std::string& path, const std::string& contents) override {
    return true;
  }
  virtual bool MakeDir(const std::string& path) override {
    return true;
  }
  virtual std::string ReadFile(const std::string& path, std::string* err, bool* not_found = nullptr) override {
    return "";
  }
  virtual int RemoveFile(const std::string& path) override {
    return 0;
  }
};

class NodeTest_35 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(NodeTest_35, ConstructorSetsPath_35) {
  Node node("foo/bar.cc", 0);
  EXPECT_EQ("foo/bar.cc", node.path());
}

TEST_F(NodeTest_35, ConstructorSetsSlashBits_35) {
  Node node("foo/bar.cc", 0x3);
  EXPECT_EQ(0x3u, node.slash_bits());
}

TEST_F(NodeTest_35, DefaultMtimeIsNegative_35) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.mtime());
}

TEST_F(NodeTest_35, DefaultDirtyIsFalse_35) {
  Node node("test", 0);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_35, SetDirty_35) {
  Node node("test", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_35, MarkDirty_35) {
  Node node("test", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_35, DefaultIdIsNegativeOne_35) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.id());
}

TEST_F(NodeTest_35, SetId_35) {
  Node node("test", 0);
  node.set_id(42);
  EXPECT_EQ(42, node.id());
}

TEST_F(NodeTest_35, DefaultInEdgeIsNull_35) {
  Node node("test", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_35, SetInEdge_35) {
  Node node("test", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

TEST_F(NodeTest_35, DefaultOutEdgesEmpty_35) {
  Node node("test", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

TEST_F(NodeTest_35, AddOutEdge_35) {
  Node node("test", 0);
  Edge edge1, edge2;
  node.AddOutEdge(&edge1);
  EXPECT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  node.AddOutEdge(&edge2);
  EXPECT_EQ(2u, node.out_edges().size());
  EXPECT_EQ(&edge2, node.out_edges()[1]);
}

TEST_F(NodeTest_35, DefaultValidationOutEdgesEmpty_35) {
  Node node("test", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

TEST_F(NodeTest_35, AddValidationOutEdge_35) {
  Node node("test", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  EXPECT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

TEST_F(NodeTest_35, DefaultDyndepPendingIsFalse_35) {
  Node node("test", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_35, SetDyndepPending_35) {
  Node node("test", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_35, DefaultGeneratedByDepLoader_35) {
  Node node("test", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_35, SetGeneratedByDepLoader_35) {
  Node node("test", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_35, StatusKnownInitiallyFalse_35) {
  Node node("test", 0);
  EXPECT_FALSE(node.status_known());
}

TEST_F(NodeTest_35, MarkMissing_35) {
  Node node("test", 0);
  node.MarkMissing();
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
}

TEST_F(NodeTest_35, StatExistingFile_35) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  bool result = node.Stat(&disk, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
  EXPECT_TRUE(node.status_known());
  EXPECT_TRUE(node.exists());
  EXPECT_EQ(12345, node.mtime());
}

TEST_F(NodeTest_35, StatNonExistingFile_35) {
  Node node("nonexistent", 0);
  MockDiskInterface disk;
  std::string err;
  bool result = node.Stat(&disk, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
  EXPECT_EQ(0, node.mtime());
}

TEST_F(NodeTest_35, StatIfNecessaryOnlyStatsOnce_35) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  // First call should stat
  bool result1 = node.StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result1);
  TimeStamp mtime1 = node.mtime();
  // Second call should not re-stat (already known)
  bool result2 = node.StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result2);
  EXPECT_EQ(mtime1, node.mtime());
}

TEST_F(NodeTest_35, ResetState_35) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_TRUE(node.status_known());
  node.set_dirty(true);

  node.ResetState();

  EXPECT_FALSE(node.status_known());
  EXPECT_FALSE(node.dirty());
  EXPECT_EQ(-1, node.mtime());
}

TEST_F(NodeTest_35, EmptyPath_35) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

TEST_F(NodeTest_35, PathDecanonicalized_35) {
  // With slash_bits = 0, should return the path as-is (forward slashes)
  Node node("foo/bar/baz", 0);
  std::string decanon = node.PathDecanonicalized();
  // The result should be a valid path string
  EXPECT_FALSE(decanon.empty());
}

TEST_F(NodeTest_35, PathDecanonicalizedWithSlashBits_35) {
  // With slash_bits indicating backslashes at certain positions
  Node node("foo/bar/baz", 0x3);
  std::string decanon = node.PathDecanonicalized();
  EXPECT_FALSE(decanon.empty());
}

TEST_F(NodeTest_35, StaticPathDecanonicalized_35) {
  std::string result = Node::PathDecanonicalized("foo/bar", 0);
  EXPECT_EQ("foo/bar", result);
}

TEST_F(NodeTest_35, UpdatePhonyMtime_35) {
  Node node("phony", 0);
  node.UpdatePhonyMtime(999);
  // For a phony node, mtime should be updated if greater
  // We can check the mtime was set
  EXPECT_GE(node.mtime(), 0);
}

TEST_F(NodeTest_35, MultipleOutEdges_35) {
  Node node("test", 0);
  Edge edges[5];
  for (int i = 0; i < 5; ++i) {
    node.AddOutEdge(&edges[i]);
  }
  EXPECT_EQ(5u, node.out_edges().size());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(&edges[i], node.out_edges()[i]);
  }
}

TEST_F(NodeTest_35, MultipleValidationOutEdges_35) {
  Node node("test", 0);
  Edge edges[3];
  for (int i = 0; i < 3; ++i) {
    node.AddValidationOutEdge(&edges[i]);
  }
  EXPECT_EQ(3u, node.validation_out_edges().size());
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(&edges[i], node.validation_out_edges()[i]);
  }
}

TEST_F(NodeTest_35, SetIdMultipleTimes_35) {
  Node node("test", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
  node.set_id(100);
  EXPECT_EQ(100, node.id());
  node.set_id(-5);
  EXPECT_EQ(-5, node.id());
}

TEST_F(NodeTest_35, PathConstReference_35) {
  Node node("my/path", 0);
  const std::string& ref1 = node.path();
  const std::string& ref2 = node.path();
  // Should return the same reference each time
  EXPECT_EQ(&ref1, &ref2);
}

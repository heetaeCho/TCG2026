#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Mock DiskInterface for testing
struct MockDiskInterface : public DiskInterface {
  virtual TimeStamp Stat(const std::string& path, std::string* err) const override {
    if (path == "existing_file") return 1;
    if (path == "missing_file") return 0;
    if (path == "error_file") { *err = "stat error"; return -1; }
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

class NodeTest_33 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a newly constructed Node does not report as existing (ExistenceStatusUnknown)
TEST_F(NodeTest_33, NewNodeDoesNotExist_33) {
  Node node("test_path", 0);
  EXPECT_FALSE(node.exists());
}

// Test that after MarkMissing, exists() returns false
TEST_F(NodeTest_33, MarkMissingSetsExistsFalse_33) {
  Node node("test_path", 0);
  node.MarkMissing();
  EXPECT_FALSE(node.exists());
}

// Test that after Stat on an existing file, exists() returns true
TEST_F(NodeTest_33, StatExistingFileReturnsExists_33) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_TRUE(node.exists());
  EXPECT_TRUE(err.empty());
}

// Test that after Stat on a missing file, exists() returns false
TEST_F(NodeTest_33, StatMissingFileReturnsNotExists_33) {
  Node node("missing_file", 0);
  MockDiskInterface disk;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_FALSE(node.exists());
}

// Test status_known after construction (should be false/unknown)
TEST_F(NodeTest_33, StatusUnknownAfterConstruction_33) {
  Node node("test_path", 0);
  EXPECT_FALSE(node.status_known());
}

// Test status_known after Stat
TEST_F(NodeTest_33, StatusKnownAfterStat_33) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_TRUE(node.status_known());
}

// Test status_known after MarkMissing
TEST_F(NodeTest_33, StatusKnownAfterMarkMissing_33) {
  Node node("test_path", 0);
  node.MarkMissing();
  EXPECT_TRUE(node.status_known());
}

// Test path() returns the correct path
TEST_F(NodeTest_33, PathReturnsCorrectPath_33) {
  Node node("my/test/path", 0);
  EXPECT_EQ("my/test/path", node.path());
}

// Test slash_bits() returns the correct value
TEST_F(NodeTest_33, SlashBitsReturnsCorrectValue_33) {
  Node node("test_path", 42);
  EXPECT_EQ(42u, node.slash_bits());
}

// Test mtime() default value
TEST_F(NodeTest_33, MtimeDefaultValue_33) {
  Node node("test_path", 0);
  EXPECT_EQ(-1, node.mtime());
}

// Test mtime() after Stat on existing file
TEST_F(NodeTest_33, MtimeAfterStatExisting_33) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_EQ(1, node.mtime());
}

// Test dirty() default value
TEST_F(NodeTest_33, DirtyDefaultIsFalse_33) {
  Node node("test_path", 0);
  EXPECT_FALSE(node.dirty());
}

// Test set_dirty and dirty
TEST_F(NodeTest_33, SetDirtyTrue_33) {
  Node node("test_path", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
}

// Test set_dirty false
TEST_F(NodeTest_33, SetDirtyFalse_33) {
  Node node("test_path", 0);
  node.set_dirty(true);
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

// Test MarkDirty
TEST_F(NodeTest_33, MarkDirty_33) {
  Node node("test_path", 0);
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

// Test dyndep_pending default
TEST_F(NodeTest_33, DyndepPendingDefaultFalse_33) {
  Node node("test_path", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test set_dyndep_pending
TEST_F(NodeTest_33, SetDyndepPending_33) {
  Node node("test_path", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test in_edge default is nullptr
TEST_F(NodeTest_33, InEdgeDefaultNull_33) {
  Node node("test_path", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

// Test set_in_edge
TEST_F(NodeTest_33, SetInEdge_33) {
  Node node("test_path", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

// Test id default
TEST_F(NodeTest_33, IdDefault_33) {
  Node node("test_path", 0);
  EXPECT_EQ(-1, node.id());
}

// Test set_id
TEST_F(NodeTest_33, SetId_33) {
  Node node("test_path", 0);
  node.set_id(5);
  EXPECT_EQ(5, node.id());
}

// Test generated_by_dep_loader default
TEST_F(NodeTest_33, GeneratedByDepLoaderDefault_33) {
  Node node("test_path", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test set_generated_by_dep_loader
TEST_F(NodeTest_33, SetGeneratedByDepLoader_33) {
  Node node("test_path", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test out_edges initially empty
TEST_F(NodeTest_33, OutEdgesInitiallyEmpty_33) {
  Node node("test_path", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

// Test AddOutEdge
TEST_F(NodeTest_33, AddOutEdge_33) {
  Node node("test_path", 0);
  Edge edge1, edge2;
  node.AddOutEdge(&edge1);
  ASSERT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  node.AddOutEdge(&edge2);
  ASSERT_EQ(2u, node.out_edges().size());
  EXPECT_EQ(&edge2, node.out_edges()[1]);
}

// Test validation_out_edges initially empty
TEST_F(NodeTest_33, ValidationOutEdgesInitiallyEmpty_33) {
  Node node("test_path", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

// Test AddValidationOutEdge
TEST_F(NodeTest_33, AddValidationOutEdge_33) {
  Node node("test_path", 0);
  Edge edge1;
  node.AddValidationOutEdge(&edge1);
  ASSERT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge1, node.validation_out_edges()[0]);
}

// Test ResetState resets mtime and existence status
TEST_F(NodeTest_33, ResetStateClearsState_33) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_TRUE(node.exists());
  EXPECT_TRUE(node.status_known());

  node.ResetState();
  EXPECT_FALSE(node.exists());
  EXPECT_FALSE(node.status_known());
  EXPECT_EQ(-1, node.mtime());
}

// Test ResetState also resets dirty
TEST_F(NodeTest_33, ResetStateClearsDirty_33) {
  Node node("test_path", 0);
  node.set_dirty(true);
  node.ResetState();
  EXPECT_FALSE(node.dirty());
}

// Test StatIfNecessary only stats when needed
TEST_F(NodeTest_33, StatIfNecessaryOnlyStatsOnce_33) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;

  // First call should stat
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_TRUE(node.exists());
  TimeStamp first_mtime = node.mtime();

  // Second call should not re-stat (already known)
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_EQ(first_mtime, node.mtime());
}

// Test StatIfNecessary stats again after ResetState
TEST_F(NodeTest_33, StatIfNecessaryAfterReset_33) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;

  node.StatIfNecessary(&disk, &err);
  EXPECT_TRUE(node.exists());

  node.ResetState();
  EXPECT_FALSE(node.status_known());

  node.StatIfNecessary(&disk, &err);
  EXPECT_TRUE(node.exists());
}

// Test empty path node
TEST_F(NodeTest_33, EmptyPathNode_33) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

// Test UpdatePhonyMtime
TEST_F(NodeTest_33, UpdatePhonyMtime_33) {
  Node node("phony_target", 0);
  node.UpdatePhonyMtime(100);
  EXPECT_EQ(100, node.mtime());
}

// Test PathDecanonicalized with zero slash_bits
TEST_F(NodeTest_33, PathDecanonicalizedZeroSlashBits_33) {
  Node node("path/to/file", 0);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("path/to/file", result);
}

// Test static PathDecanonicalized
TEST_F(NodeTest_33, StaticPathDecanonicalized_33) {
  std::string result = Node::PathDecanonicalized("path/to/file", 0);
  EXPECT_EQ("path/to/file", result);
}

// Test that exists() is false when status is ExistenceStatusMissing
TEST_F(NodeTest_33, ExistsReturnsFalseWhenMissing_33) {
  Node node("missing_file", 0);
  MockDiskInterface disk;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_FALSE(node.exists());
}

// Test that exists() is false when status is ExistenceStatusUnknown (default)
TEST_F(NodeTest_33, ExistsReturnsFalseWhenUnknown_33) {
  Node node("test_path", 0);
  EXPECT_FALSE(node.exists());
}

// Test multiple out edges and validation out edges
TEST_F(NodeTest_33, MultipleEdges_33) {
  Node node("test_path", 0);
  Edge edges[5];
  for (int i = 0; i < 5; ++i) {
    node.AddOutEdge(&edges[i]);
    node.AddValidationOutEdge(&edges[i]);
  }
  EXPECT_EQ(5u, node.out_edges().size());
  EXPECT_EQ(5u, node.validation_out_edges().size());
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(&edges[i], node.out_edges()[i]);
    EXPECT_EQ(&edges[i], node.validation_out_edges()[i]);
  }
}

// Test set_id with boundary values
TEST_F(NodeTest_33, SetIdBoundaryValues_33) {
  Node node("test_path", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
  node.set_id(INT_MAX);
  EXPECT_EQ(INT_MAX, node.id());
  node.set_id(-1);
  EXPECT_EQ(-1, node.id());
}

// Test slash_bits with max value
TEST_F(NodeTest_33, SlashBitsMaxValue_33) {
  Node node("test_path", UINT64_MAX);
  EXPECT_EQ(UINT64_MAX, node.slash_bits());
}

#include "gtest/gtest.h"
#include "graph.h"
#include "state.h"
#include "disk_interface.h"
#include <string>
#include <vector>

// A minimal disk interface for testing
class TestDiskInterface : public DiskInterface {
public:
  TimeStamp Stat(const std::string& path, std::string* err) const override {
    if (path == "existing_file") return 100;
    if (path == "missing_file") return 0;
    return 0;
  }
  bool WriteFile(const std::string& path, const std::string& contents) override {
    return true;
  }
  bool MakeDir(const std::string& path) override {
    return true;
  }
  Status ReadFile(const std::string& path, std::string* contents, std::string* err) override {
    return NotFound;
  }
  int RemoveFile(const std::string& path) override {
    return 0;
  }
};

class NodeTest_39 : public ::testing::Test {
protected:
  void SetUp() override {
    disk_interface_ = new TestDiskInterface();
  }
  void TearDown() override {
    delete disk_interface_;
  }
  TestDiskInterface* disk_interface_;
};

// Test that a newly created Node has dirty_ == false by default
TEST_F(NodeTest_39, DefaultDirtyIsFalse_39) {
  Node node("test_path", 0);
  EXPECT_FALSE(node.dirty());
}

// Test set_dirty(true) makes dirty() return true
TEST_F(NodeTest_39, SetDirtyTrue_39) {
  Node node("test_path", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
}

// Test set_dirty(false) makes dirty() return false
TEST_F(NodeTest_39, SetDirtyFalse_39) {
  Node node("test_path", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

// Test MarkDirty sets dirty to true
TEST_F(NodeTest_39, MarkDirtySetsTrue_39) {
  Node node("test_path", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

// Test path() returns the path given at construction
TEST_F(NodeTest_39, PathReturnsConstructedPath_39) {
  Node node("my/test/path", 0);
  EXPECT_EQ("my/test/path", node.path());
}

// Test slash_bits() returns the value given at construction
TEST_F(NodeTest_39, SlashBitsReturnsConstructedValue_39) {
  Node node("some/path", 42);
  EXPECT_EQ(42u, node.slash_bits());
}

// Test default mtime is -1
TEST_F(NodeTest_39, DefaultMtimeIsNegativeOne_39) {
  Node node("test_path", 0);
  EXPECT_EQ(-1, node.mtime());
}

// Test default id is -1
TEST_F(NodeTest_39, DefaultIdIsNegativeOne_39) {
  Node node("test_path", 0);
  EXPECT_EQ(-1, node.id());
}

// Test set_id and id
TEST_F(NodeTest_39, SetIdAndGetId_39) {
  Node node("test_path", 0);
  node.set_id(5);
  EXPECT_EQ(5, node.id());
}

// Test set_id with zero
TEST_F(NodeTest_39, SetIdZero_39) {
  Node node("test_path", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

// Test default in_edge is nullptr
TEST_F(NodeTest_39, DefaultInEdgeIsNull_39) {
  Node node("test_path", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

// Test set_in_edge and in_edge
TEST_F(NodeTest_39, SetInEdge_39) {
  Node node("test_path", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

// Test out_edges is initially empty
TEST_F(NodeTest_39, OutEdgesInitiallyEmpty_39) {
  Node node("test_path", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

// Test AddOutEdge adds to out_edges
TEST_F(NodeTest_39, AddOutEdge_39) {
  Node node("test_path", 0);
  Edge edge;
  node.AddOutEdge(&edge);
  ASSERT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge, node.out_edges()[0]);
}

// Test AddOutEdge multiple edges
TEST_F(NodeTest_39, AddMultipleOutEdges_39) {
  Node node("test_path", 0);
  Edge edge1, edge2, edge3;
  node.AddOutEdge(&edge1);
  node.AddOutEdge(&edge2);
  node.AddOutEdge(&edge3);
  ASSERT_EQ(3u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  EXPECT_EQ(&edge2, node.out_edges()[1]);
  EXPECT_EQ(&edge3, node.out_edges()[2]);
}

// Test validation_out_edges is initially empty
TEST_F(NodeTest_39, ValidationOutEdgesInitiallyEmpty_39) {
  Node node("test_path", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

// Test AddValidationOutEdge
TEST_F(NodeTest_39, AddValidationOutEdge_39) {
  Node node("test_path", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  ASSERT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

// Test dyndep_pending default is false
TEST_F(NodeTest_39, DyndepPendingDefaultFalse_39) {
  Node node("test_path", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test set_dyndep_pending
TEST_F(NodeTest_39, SetDyndepPending_39) {
  Node node("test_path", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test generated_by_dep_loader default is true
TEST_F(NodeTest_39, GeneratedByDepLoaderDefaultTrue_39) {
  Node node("test_path", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test set_generated_by_dep_loader
TEST_F(NodeTest_39, SetGeneratedByDepLoader_39) {
  Node node("test_path", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test status_known initially returns false (mtime == -1)
TEST_F(NodeTest_39, StatusKnownInitiallyFalse_39) {
  Node node("test_path", 0);
  EXPECT_FALSE(node.status_known());
}

// Test Stat on an existing file sets mtime and status_known
TEST_F(NodeTest_39, StatExistingFile_39) {
  Node node("existing_file", 0);
  std::string err;
  EXPECT_TRUE(node.Stat(disk_interface_, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(node.status_known());
  EXPECT_EQ(100, node.mtime());
  EXPECT_TRUE(node.exists());
}

// Test Stat on a missing file
TEST_F(NodeTest_39, StatMissingFile_39) {
  Node node("missing_file", 0);
  std::string err;
  EXPECT_TRUE(node.Stat(disk_interface_, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(node.status_known());
  EXPECT_EQ(0, node.mtime());
  EXPECT_FALSE(node.exists());
}

// Test MarkMissing sets exists to false and status to known
TEST_F(NodeTest_39, MarkMissing_39) {
  Node node("test_path", 0);
  node.MarkMissing();
  EXPECT_TRUE(node.status_known());
  EXPECT_FALSE(node.exists());
  EXPECT_EQ(0, node.mtime());
}

// Test ResetState resets mtime and dirty
TEST_F(NodeTest_39, ResetState_39) {
  Node node("existing_file", 0);
  std::string err;
  node.Stat(disk_interface_, &err);
  node.set_dirty(true);
  node.set_id(10);

  node.ResetState();

  EXPECT_EQ(-1, node.mtime());
  EXPECT_FALSE(node.dirty());
  EXPECT_FALSE(node.status_known());
}

// Test StatIfNecessary only stats if status not known
TEST_F(NodeTest_39, StatIfNecessaryOnlyStatsOnce_39) {
  Node node("existing_file", 0);
  std::string err;
  
  // First call should stat
  EXPECT_TRUE(node.StatIfNecessary(disk_interface_, &err));
  EXPECT_EQ(100, node.mtime());
  
  // Second call should not re-stat (status already known)
  EXPECT_TRUE(node.StatIfNecessary(disk_interface_, &err));
  EXPECT_EQ(100, node.mtime());
}

// Test UpdatePhonyMtime
TEST_F(NodeTest_39, UpdatePhonyMtime_39) {
  Node node("test_path", 0);
  node.UpdatePhonyMtime(200);
  EXPECT_EQ(200, node.mtime());
}

// Test PathDecanonicalized (instance method)
TEST_F(NodeTest_39, PathDecanonicalized_39) {
  Node node("test/path", 0);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("test/path", result);
}

// Test PathDecanonicalized with slash_bits set (static)
TEST_F(NodeTest_39, PathDecanonicalizedStatic_39) {
  std::string result = Node::PathDecanonicalized("test/path", 0);
  EXPECT_EQ("test/path", result);
}

// Test empty path construction
TEST_F(NodeTest_39, EmptyPathConstruction_39) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

// Test toggling dirty multiple times
TEST_F(NodeTest_39, ToggleDirtyMultipleTimes_39) {
  Node node("test_path", 0);
  for (int i = 0; i < 10; i++) {
    node.set_dirty(true);
    EXPECT_TRUE(node.dirty());
    node.set_dirty(false);
    EXPECT_FALSE(node.dirty());
  }
}

// Test that set_in_edge to nullptr works
TEST_F(NodeTest_39, SetInEdgeToNull_39) {
  Node node("test_path", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
  node.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node.in_edge());
}

// Test exists() initially when status is unknown
TEST_F(NodeTest_39, ExistsWhenStatusUnknown_39) {
  Node node("test_path", 0);
  // When status is unknown, exists should return false
  EXPECT_FALSE(node.exists());
}

// Test large slash_bits value
TEST_F(NodeTest_39, LargeSlashBits_39) {
  uint64_t large_bits = 0xFFFFFFFFFFFFFFFFULL;
  Node node("test/path", large_bits);
  EXPECT_EQ(large_bits, node.slash_bits());
}

// Test set_id with negative value
TEST_F(NodeTest_39, SetIdNegative_39) {
  Node node("test_path", 0);
  node.set_id(-100);
  EXPECT_EQ(-100, node.id());
}

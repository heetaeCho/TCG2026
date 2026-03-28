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

class NodeTest_38 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default mtime value
TEST_F(NodeTest_38, DefaultMtimeIsNegativeOne_38) {
  Node node("test_path", 0);
  EXPECT_EQ(-1, node.mtime());
}

// Test: Path is stored correctly
TEST_F(NodeTest_38, PathReturnsConstructorValue_38) {
  Node node("my/path/file.cc", 0);
  EXPECT_EQ("my/path/file.cc", node.path());
}

// Test: Slash bits stored correctly
TEST_F(NodeTest_38, SlashBitsReturnsConstructorValue_38) {
  Node node("some/path", 0x5);
  EXPECT_EQ(0x5u, node.slash_bits());
}

// Test: Default dirty is false
TEST_F(NodeTest_38, DefaultDirtyIsFalse_38) {
  Node node("path", 0);
  EXPECT_FALSE(node.dirty());
}

// Test: set_dirty changes dirty state
TEST_F(NodeTest_38, SetDirtyChangesState_38) {
  Node node("path", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

// Test: MarkDirty sets dirty to true
TEST_F(NodeTest_38, MarkDirtySetsTrue_38) {
  Node node("path", 0);
  EXPECT_FALSE(node.dirty());
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

// Test: Default id is -1
TEST_F(NodeTest_38, DefaultIdIsNegativeOne_38) {
  Node node("path", 0);
  EXPECT_EQ(-1, node.id());
}

// Test: set_id and id
TEST_F(NodeTest_38, SetIdAndGetId_38) {
  Node node("path", 0);
  node.set_id(42);
  EXPECT_EQ(42, node.id());
}

// Test: Default in_edge is nullptr
TEST_F(NodeTest_38, DefaultInEdgeIsNull_38) {
  Node node("path", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

// Test: set_in_edge
TEST_F(NodeTest_38, SetInEdge_38) {
  Node node("path", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

// Test: Default out_edges is empty
TEST_F(NodeTest_38, DefaultOutEdgesEmpty_38) {
  Node node("path", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

// Test: AddOutEdge adds to out_edges
TEST_F(NodeTest_38, AddOutEdgeAddsEdge_38) {
  Node node("path", 0);
  Edge edge1, edge2;
  node.AddOutEdge(&edge1);
  EXPECT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  node.AddOutEdge(&edge2);
  EXPECT_EQ(2u, node.out_edges().size());
  EXPECT_EQ(&edge2, node.out_edges()[1]);
}

// Test: Default validation_out_edges is empty
TEST_F(NodeTest_38, DefaultValidationOutEdgesEmpty_38) {
  Node node("path", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

// Test: AddValidationOutEdge adds to validation_out_edges
TEST_F(NodeTest_38, AddValidationOutEdgeAddsEdge_38) {
  Node node("path", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  EXPECT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

// Test: Default dyndep_pending is false
TEST_F(NodeTest_38, DefaultDyndepPendingIsFalse_38) {
  Node node("path", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test: set_dyndep_pending
TEST_F(NodeTest_38, SetDyndepPending_38) {
  Node node("path", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test: Default generated_by_dep_loader is true
TEST_F(NodeTest_38, DefaultGeneratedByDepLoaderIsTrue_38) {
  Node node("path", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test: set_generated_by_dep_loader
TEST_F(NodeTest_38, SetGeneratedByDepLoader_38) {
  Node node("path", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test: status_known is false initially
TEST_F(NodeTest_38, StatusNotKnownInitially_38) {
  Node node("path", 0);
  EXPECT_FALSE(node.status_known());
}

// Test: MarkMissing makes exists return false and status_known return true
TEST_F(NodeTest_38, MarkMissingSetsExistsFalse_38) {
  Node node("path", 0);
  node.MarkMissing();
  EXPECT_FALSE(node.exists());
  EXPECT_TRUE(node.status_known());
}

// Test: Stat on existing file sets mtime
TEST_F(NodeTest_38, StatExistingFileSetsPositiveMtime_38) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ(100, node.mtime());
  EXPECT_TRUE(node.exists());
  EXPECT_TRUE(node.status_known());
}

// Test: Stat on missing file sets mtime to 0
TEST_F(NodeTest_38, StatMissingFileSetsZeroMtime_38) {
  Node node("missing_file", 0);
  MockDiskInterface disk;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_EQ(0, node.mtime());
  EXPECT_FALSE(node.exists());
  EXPECT_TRUE(node.status_known());
}

// Test: ResetState restores initial state
TEST_F(NodeTest_38, ResetStateClearsState_38) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  node.Stat(&disk, &err);
  node.set_dirty(true);
  node.ResetState();
  EXPECT_EQ(-1, node.mtime());
  EXPECT_FALSE(node.dirty());
  EXPECT_FALSE(node.status_known());
}

// Test: StatIfNecessary only stats if not already known
TEST_F(NodeTest_38, StatIfNecessarySkipsIfAlreadyStatted_38) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  // First stat
  EXPECT_TRUE(node.Stat(&disk, &err));
  TimeStamp first_mtime = node.mtime();
  // StatIfNecessary should not re-stat
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_EQ(first_mtime, node.mtime());
}

// Test: StatIfNecessary does stat when status not known
TEST_F(NodeTest_38, StatIfNecessaryStatsWhenNeeded_38) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  EXPECT_FALSE(node.status_known());
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_TRUE(node.status_known());
  EXPECT_EQ(100, node.mtime());
}

// Test: UpdatePhonyMtime updates mtime if larger
TEST_F(NodeTest_38, UpdatePhonyMtimeUpdatesWhenLarger_38) {
  Node node("phony", 0);
  node.MarkMissing();
  EXPECT_EQ(0, node.mtime());
  node.UpdatePhonyMtime(50);
  EXPECT_EQ(50, node.mtime());
  // Updating with a smaller value should not decrease
  node.UpdatePhonyMtime(30);
  EXPECT_GE(node.mtime(), 30);
}

// Test: PathDecanonicalized (static version)
TEST_F(NodeTest_38, PathDecanonicalizedStatic_38) {
  std::string result = Node::PathDecanonicalized("some/path", 0);
  EXPECT_EQ("some/path", result);
}

// Test: PathDecanonicalized (member version)
TEST_F(NodeTest_38, PathDecanonicalizedMember_38) {
  Node node("some/path", 0);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("some/path", result);
}

// Test: PathDecanonicalized with slash bits set
TEST_F(NodeTest_38, PathDecanonicalizedWithSlashBits_38) {
  // slash_bits = 1 means the first slash should be backslash
  Node node("a/b", 1);
  std::string result = node.PathDecanonicalized();
  EXPECT_EQ("a\\b", result);
}

// Test: Empty path node
TEST_F(NodeTest_38, EmptyPathNode_38) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
  EXPECT_EQ("", node.PathDecanonicalized());
}

// Test: Multiple out edges
TEST_F(NodeTest_38, MultipleOutEdges_38) {
  Node node("path", 0);
  Edge e1, e2, e3;
  node.AddOutEdge(&e1);
  node.AddOutEdge(&e2);
  node.AddOutEdge(&e3);
  EXPECT_EQ(3u, node.out_edges().size());
}

// Test: Multiple validation out edges
TEST_F(NodeTest_38, MultipleValidationOutEdges_38) {
  Node node("path", 0);
  Edge e1, e2;
  node.AddValidationOutEdge(&e1);
  node.AddValidationOutEdge(&e2);
  EXPECT_EQ(2u, node.validation_out_edges().size());
}

// Test: set_id with zero
TEST_F(NodeTest_38, SetIdToZero_38) {
  Node node("path", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

// Test: set_id with large value
TEST_F(NodeTest_38, SetIdLargeValue_38) {
  Node node("path", 0);
  node.set_id(999999);
  EXPECT_EQ(999999, node.id());
}

// Test: set_in_edge to nullptr
TEST_F(NodeTest_38, SetInEdgeToNull_38) {
  Node node("path", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
  node.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node.in_edge());
}

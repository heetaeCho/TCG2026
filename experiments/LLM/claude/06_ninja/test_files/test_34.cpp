#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "graph.h"

// Mock DiskInterface for testing Stat-related methods
struct MockDiskInterface : public DiskInterface {
  MOCK_METHOD(TimeStamp, Stat, (const std::string& path, std::string* err), (const, override));
  MOCK_METHOD(bool, WriteFile, (const std::string& path, const std::string& contents), (override));
  MOCK_METHOD(bool, MakeDir, (const std::string& path), (override));
  MOCK_METHOD(Status, ReadFile, (const std::string& path, std::string* contents, std::string* err), (override));
  MOCK_METHOD(int, RemoveFile, (const std::string& path), (override));
};

class NodeTest_34 : public ::testing::Test {
 protected:
  void SetUp() override {
    node_ = new Node("test/path", 0);
  }

  void TearDown() override {
    delete node_;
  }

  Node* node_;
};

// Test: status_known returns false for a freshly constructed node
TEST_F(NodeTest_34, StatusUnknownInitially_34) {
  EXPECT_FALSE(node_->status_known());
}

// Test: After MarkMissing, status_known returns true
TEST_F(NodeTest_34, StatusKnownAfterMarkMissing_34) {
  node_->MarkMissing();
  EXPECT_TRUE(node_->status_known());
}

// Test: After MarkMissing, exists returns false
TEST_F(NodeTest_34, ExistsReturnsFalseAfterMarkMissing_34) {
  node_->MarkMissing();
  EXPECT_FALSE(node_->exists());
}

// Test: After Stat with existing file, status_known returns true
TEST_F(NodeTest_34, StatusKnownAfterStat_34) {
  MockDiskInterface disk;
  std::string err;
  EXPECT_CALL(disk, Stat("test/path", &err))
      .WillOnce(::testing::Return(1));
  node_->Stat(&disk, &err);
  EXPECT_TRUE(node_->status_known());
}

// Test: After Stat with existing file, exists returns true
TEST_F(NodeTest_34, ExistsAfterStatWithExistingFile_34) {
  MockDiskInterface disk;
  std::string err;
  EXPECT_CALL(disk, Stat("test/path", &err))
      .WillOnce(::testing::Return(100));
  node_->Stat(&disk, &err);
  EXPECT_TRUE(node_->exists());
}

// Test: After Stat with non-existing file (mtime==0), exists returns false
TEST_F(NodeTest_34, NotExistsAfterStatWithMissingFile_34) {
  MockDiskInterface disk;
  std::string err;
  EXPECT_CALL(disk, Stat("test/path", &err))
      .WillOnce(::testing::Return(0));
  node_->Stat(&disk, &err);
  EXPECT_FALSE(node_->exists());
  EXPECT_TRUE(node_->status_known());
}

// Test: After ResetState, status_known returns false again
TEST_F(NodeTest_34, StatusUnknownAfterReset_34) {
  node_->MarkMissing();
  EXPECT_TRUE(node_->status_known());
  node_->ResetState();
  EXPECT_FALSE(node_->status_known());
}

// Test: path returns the path passed to constructor
TEST_F(NodeTest_34, PathReturnsConstructedPath_34) {
  EXPECT_EQ("test/path", node_->path());
}

// Test: slash_bits returns the slash_bits passed to constructor
TEST_F(NodeTest_34, SlashBitsReturnsConstructedValue_34) {
  Node n("foo\\bar", 3);
  EXPECT_EQ(3u, n.slash_bits());
}

// Test: mtime returns -1 initially (not yet statted)
TEST_F(NodeTest_34, MtimeInitiallyNegative_34) {
  EXPECT_EQ(-1, node_->mtime());
}

// Test: mtime after Stat returns the value from DiskInterface
TEST_F(NodeTest_34, MtimeAfterStat_34) {
  MockDiskInterface disk;
  std::string err;
  EXPECT_CALL(disk, Stat("test/path", &err))
      .WillOnce(::testing::Return(42));
  node_->Stat(&disk, &err);
  EXPECT_EQ(42, node_->mtime());
}

// Test: dirty is false initially
TEST_F(NodeTest_34, DirtyInitiallyFalse_34) {
  EXPECT_FALSE(node_->dirty());
}

// Test: set_dirty changes dirty state
TEST_F(NodeTest_34, SetDirtyChangesState_34) {
  node_->set_dirty(true);
  EXPECT_TRUE(node_->dirty());
  node_->set_dirty(false);
  EXPECT_FALSE(node_->dirty());
}

// Test: MarkDirty sets dirty to true
TEST_F(NodeTest_34, MarkDirtySetsTrue_34) {
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
}

// Test: dyndep_pending is false initially
TEST_F(NodeTest_34, DyndepPendingInitiallyFalse_34) {
  EXPECT_FALSE(node_->dyndep_pending());
}

// Test: set_dyndep_pending changes state
TEST_F(NodeTest_34, SetDyndepPending_34) {
  node_->set_dyndep_pending(true);
  EXPECT_TRUE(node_->dyndep_pending());
  node_->set_dyndep_pending(false);
  EXPECT_FALSE(node_->dyndep_pending());
}

// Test: in_edge is null initially
TEST_F(NodeTest_34, InEdgeInitiallyNull_34) {
  EXPECT_EQ(nullptr, node_->in_edge());
}

// Test: set_in_edge changes in_edge
TEST_F(NodeTest_34, SetInEdge_34) {
  Edge edge;
  node_->set_in_edge(&edge);
  EXPECT_EQ(&edge, node_->in_edge());
}

// Test: generated_by_dep_loader is true initially
TEST_F(NodeTest_34, GeneratedByDepLoaderInitiallyTrue_34) {
  EXPECT_TRUE(node_->generated_by_dep_loader());
}

// Test: set_generated_by_dep_loader changes value
TEST_F(NodeTest_34, SetGeneratedByDepLoader_34) {
  node_->set_generated_by_dep_loader(false);
  EXPECT_FALSE(node_->generated_by_dep_loader());
  node_->set_generated_by_dep_loader(true);
  EXPECT_TRUE(node_->generated_by_dep_loader());
}

// Test: id is -1 initially
TEST_F(NodeTest_34, IdInitiallyNegativeOne_34) {
  EXPECT_EQ(-1, node_->id());
}

// Test: set_id changes id
TEST_F(NodeTest_34, SetId_34) {
  node_->set_id(42);
  EXPECT_EQ(42, node_->id());
}

// Test: out_edges is empty initially
TEST_F(NodeTest_34, OutEdgesInitiallyEmpty_34) {
  EXPECT_TRUE(node_->out_edges().empty());
}

// Test: AddOutEdge adds to out_edges
TEST_F(NodeTest_34, AddOutEdge_34) {
  Edge edge1, edge2;
  node_->AddOutEdge(&edge1);
  ASSERT_EQ(1u, node_->out_edges().size());
  EXPECT_EQ(&edge1, node_->out_edges()[0]);
  node_->AddOutEdge(&edge2);
  ASSERT_EQ(2u, node_->out_edges().size());
  EXPECT_EQ(&edge2, node_->out_edges()[1]);
}

// Test: validation_out_edges is empty initially
TEST_F(NodeTest_34, ValidationOutEdgesInitiallyEmpty_34) {
  EXPECT_TRUE(node_->validation_out_edges().empty());
}

// Test: AddValidationOutEdge adds to validation_out_edges
TEST_F(NodeTest_34, AddValidationOutEdge_34) {
  Edge edge1;
  node_->AddValidationOutEdge(&edge1);
  ASSERT_EQ(1u, node_->validation_out_edges().size());
  EXPECT_EQ(&edge1, node_->validation_out_edges()[0]);
}

// Test: StatIfNecessary only stats when status is unknown
TEST_F(NodeTest_34, StatIfNecessaryOnlyStatsWhenUnknown_34) {
  MockDiskInterface disk;
  std::string err;
  EXPECT_CALL(disk, Stat("test/path", &err))
      .WillOnce(::testing::Return(10));
  // First call should stat
  EXPECT_TRUE(node_->StatIfNecessary(&disk, &err));
  EXPECT_TRUE(node_->status_known());
  // Second call should not stat again (no additional EXPECT_CALL)
  EXPECT_TRUE(node_->StatIfNecessary(&disk, &err));
}

// Test: ResetState resets dirty flag as well
TEST_F(NodeTest_34, ResetStateResetsDirty_34) {
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
  node_->ResetState();
  EXPECT_FALSE(node_->dirty());
}

// Test: ResetState resets mtime
TEST_F(NodeTest_34, ResetStateResetsMtime_34) {
  MockDiskInterface disk;
  std::string err;
  EXPECT_CALL(disk, Stat("test/path", &err))
      .WillOnce(::testing::Return(99));
  node_->Stat(&disk, &err);
  EXPECT_EQ(99, node_->mtime());
  node_->ResetState();
  EXPECT_EQ(-1, node_->mtime());
}

// Test: UpdatePhonyMtime updates mtime
TEST_F(NodeTest_34, UpdatePhonyMtime_34) {
  node_->UpdatePhonyMtime(123);
  EXPECT_EQ(123, node_->mtime());
}

// Test: PathDecanonicalized static method with slash_bits
TEST_F(NodeTest_34, PathDecanonicalizedStatic_34) {
  // With slash_bits = 0, no back-slash replacement expected
  std::string result = Node::PathDecanonicalized("foo/bar", 0);
  EXPECT_EQ("foo/bar", result);
}

// Test: PathDecanonicalized instance method
TEST_F(NodeTest_34, PathDecanonicalizedInstance_34) {
  Node n("foo/bar", 0);
  std::string result = n.PathDecanonicalized();
  EXPECT_EQ("foo/bar", result);
}

// Test: Node with empty path
TEST_F(NodeTest_34, EmptyPath_34) {
  Node n("", 0);
  EXPECT_EQ("", n.path());
  EXPECT_FALSE(n.status_known());
}

// Test: Stat returns false on error (negative mtime)
TEST_F(NodeTest_34, StatFailure_34) {
  MockDiskInterface disk;
  std::string err;
  EXPECT_CALL(disk, Stat("test/path", &err))
      .WillOnce(::testing::DoAll(
          ::testing::SetArgPointee<1>("stat error"),
          ::testing::Return(-1)));
  bool result = node_->Stat(&disk, &err);
  EXPECT_FALSE(result);
}

// Test: Multiple out edges
TEST_F(NodeTest_34, MultipleOutEdges_34) {
  Edge e1, e2, e3;
  node_->AddOutEdge(&e1);
  node_->AddOutEdge(&e2);
  node_->AddOutEdge(&e3);
  EXPECT_EQ(3u, node_->out_edges().size());
}

// Test: set_id to zero (boundary)
TEST_F(NodeTest_34, SetIdToZero_34) {
  node_->set_id(0);
  EXPECT_EQ(0, node_->id());
}

// Test: set_id to large value
TEST_F(NodeTest_34, SetIdToLargeValue_34) {
  node_->set_id(999999);
  EXPECT_EQ(999999, node_->id());
}

#include "gtest/gtest.h"
#include "graph.h"
#include "state.h"
#include "disk_interface.h"
#include <string>
#include <vector>

// A minimal mock DiskInterface for testing Stat-related behavior
class MockDiskInterface : public DiskInterface {
public:
  virtual TimeStamp Stat(const std::string& path, std::string* err) const override {
    if (path == "existing_file") return 12345;
    if (path == "error_file") {
      *err = "stat error";
      return -1;
    }
    return 0; // File does not exist
  }
  virtual bool WriteFile(const std::string& path, const std::string& contents) override {
    return true;
  }
  virtual bool MakeDir(const std::string& path) override {
    return true;
  }
  virtual Status ReadFile(const std::string& path, std::string* contents,
                          std::string* err) override {
    return NotFound;
  }
  virtual int RemoveFile(const std::string& path) override {
    return 0;
  }
};

class NodeTest_37 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test constructor sets path correctly
TEST_F(NodeTest_37, ConstructorSetsPath_37) {
  Node node("foo/bar.cc", 0);
  EXPECT_EQ("foo/bar.cc", node.path());
}

// Test constructor sets slash_bits correctly
TEST_F(NodeTest_37, ConstructorSetsSlashBits_37) {
  Node node("foo\\bar.cc", 0x1);
  EXPECT_EQ(0x1u, node.slash_bits());
}

// Test slash_bits returns zero when constructed with zero
TEST_F(NodeTest_37, SlashBitsZero_37) {
  Node node("foo/bar.cc", 0);
  EXPECT_EQ(0u, node.slash_bits());
}

// Test slash_bits returns large value
TEST_F(NodeTest_37, SlashBitsLargeValue_37) {
  uint64_t large_val = 0xFFFFFFFFFFFFFFFFULL;
  Node node("path", large_val);
  EXPECT_EQ(large_val, node.slash_bits());
}

// Test initial mtime is -1 (unknown)
TEST_F(NodeTest_37, InitialMtimeIsNegativeOne_37) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.mtime());
}

// Test initial dirty is false
TEST_F(NodeTest_37, InitialDirtyIsFalse_37) {
  Node node("test", 0);
  EXPECT_FALSE(node.dirty());
}

// Test set_dirty and dirty
TEST_F(NodeTest_37, SetDirtyTrue_37) {
  Node node("test", 0);
  node.set_dirty(true);
  EXPECT_TRUE(node.dirty());
}

// Test set_dirty to false
TEST_F(NodeTest_37, SetDirtyFalse_37) {
  Node node("test", 0);
  node.set_dirty(true);
  node.set_dirty(false);
  EXPECT_FALSE(node.dirty());
}

// Test MarkDirty sets dirty to true
TEST_F(NodeTest_37, MarkDirtySetsTrue_37) {
  Node node("test", 0);
  node.MarkDirty();
  EXPECT_TRUE(node.dirty());
}

// Test initial dyndep_pending is false
TEST_F(NodeTest_37, InitialDyndepPendingIsFalse_37) {
  Node node("test", 0);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test set_dyndep_pending
TEST_F(NodeTest_37, SetDyndepPending_37) {
  Node node("test", 0);
  node.set_dyndep_pending(true);
  EXPECT_TRUE(node.dyndep_pending());
  node.set_dyndep_pending(false);
  EXPECT_FALSE(node.dyndep_pending());
}

// Test initial in_edge is nullptr
TEST_F(NodeTest_37, InitialInEdgeIsNull_37) {
  Node node("test", 0);
  EXPECT_EQ(nullptr, node.in_edge());
}

// Test set_in_edge
TEST_F(NodeTest_37, SetInEdge_37) {
  Node node("test", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
}

// Test initial id is -1
TEST_F(NodeTest_37, InitialIdIsNegativeOne_37) {
  Node node("test", 0);
  EXPECT_EQ(-1, node.id());
}

// Test set_id
TEST_F(NodeTest_37, SetId_37) {
  Node node("test", 0);
  node.set_id(42);
  EXPECT_EQ(42, node.id());
}

// Test set_id to zero
TEST_F(NodeTest_37, SetIdZero_37) {
  Node node("test", 0);
  node.set_id(0);
  EXPECT_EQ(0, node.id());
}

// Test initial out_edges is empty
TEST_F(NodeTest_37, InitialOutEdgesEmpty_37) {
  Node node("test", 0);
  EXPECT_TRUE(node.out_edges().empty());
}

// Test AddOutEdge
TEST_F(NodeTest_37, AddOutEdge_37) {
  Node node("test", 0);
  Edge edge1, edge2;
  node.AddOutEdge(&edge1);
  EXPECT_EQ(1u, node.out_edges().size());
  EXPECT_EQ(&edge1, node.out_edges()[0]);
  node.AddOutEdge(&edge2);
  EXPECT_EQ(2u, node.out_edges().size());
  EXPECT_EQ(&edge2, node.out_edges()[1]);
}

// Test initial validation_out_edges is empty
TEST_F(NodeTest_37, InitialValidationOutEdgesEmpty_37) {
  Node node("test", 0);
  EXPECT_TRUE(node.validation_out_edges().empty());
}

// Test AddValidationOutEdge
TEST_F(NodeTest_37, AddValidationOutEdge_37) {
  Node node("test", 0);
  Edge edge;
  node.AddValidationOutEdge(&edge);
  EXPECT_EQ(1u, node.validation_out_edges().size());
  EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

// Test initial generated_by_dep_loader is true
TEST_F(NodeTest_37, InitialGeneratedByDepLoaderIsTrue_37) {
  Node node("test", 0);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test set_generated_by_dep_loader
TEST_F(NodeTest_37, SetGeneratedByDepLoader_37) {
  Node node("test", 0);
  node.set_generated_by_dep_loader(false);
  EXPECT_FALSE(node.generated_by_dep_loader());
  node.set_generated_by_dep_loader(true);
  EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test status_known initially false (mtime is -1)
TEST_F(NodeTest_37, InitialStatusNotKnown_37) {
  Node node("test", 0);
  EXPECT_FALSE(node.status_known());
}

// Test Stat on existing file sets mtime and status_known
TEST_F(NodeTest_37, StatExistingFile_37) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(node.status_known());
  EXPECT_EQ(12345, node.mtime());
  EXPECT_TRUE(node.exists());
}

// Test Stat on non-existing file
TEST_F(NodeTest_37, StatNonExistingFile_37) {
  Node node("nonexistent", 0);
  MockDiskInterface disk;
  std::string err;
  EXPECT_TRUE(node.Stat(&disk, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(node.status_known());
  EXPECT_EQ(0, node.mtime());
  EXPECT_FALSE(node.exists());
}

// Test MarkMissing sets existence to not exist
TEST_F(NodeTest_37, MarkMissing_37) {
  Node node("test", 0);
  node.MarkMissing();
  EXPECT_FALSE(node.exists());
  EXPECT_TRUE(node.status_known());
}

// Test ResetState resets mtime and status
TEST_F(NodeTest_37, ResetState_37) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;
  node.Stat(&disk, &err);
  EXPECT_TRUE(node.status_known());

  node.ResetState();
  EXPECT_FALSE(node.status_known());
  EXPECT_EQ(-1, node.mtime());
  EXPECT_FALSE(node.dirty());
}

// Test StatIfNecessary only stats when status is unknown
TEST_F(NodeTest_37, StatIfNecessary_37) {
  Node node("existing_file", 0);
  MockDiskInterface disk;
  std::string err;

  // First call should stat
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_EQ(12345, node.mtime());

  // Second call should not re-stat (status already known)
  EXPECT_TRUE(node.StatIfNecessary(&disk, &err));
  EXPECT_EQ(12345, node.mtime());
}

// Test UpdatePhonyMtime updates mtime if greater
TEST_F(NodeTest_37, UpdatePhonyMtime_37) {
  Node node("test", 0);
  node.MarkMissing(); // sets mtime to 0
  node.UpdatePhonyMtime(100);
  EXPECT_EQ(100, node.mtime());
}

// Test PathDecanonicalized with slash_bits
TEST_F(NodeTest_37, PathDecanonicalized_37) {
  // slash_bits = 1 means first slash should be backslash
  Node node("foo/bar", 1);
  std::string result = node.PathDecanonicalized();
  // With slash_bits=1, the first '/' should be converted to '\\'
  EXPECT_NE(std::string::npos, result.find('\\'));
}

// Test static PathDecanonicalized
TEST_F(NodeTest_37, StaticPathDecanonicalized_37) {
  std::string result = Node::PathDecanonicalized("a/b/c", 0);
  EXPECT_EQ("a/b/c", result);
}

// Test path returns reference to stored path
TEST_F(NodeTest_37, PathReturnsCorrectValue_37) {
  Node node("some/path/to/file.cc", 0);
  EXPECT_EQ("some/path/to/file.cc", node.path());
}

// Test empty path
TEST_F(NodeTest_37, EmptyPath_37) {
  Node node("", 0);
  EXPECT_EQ("", node.path());
}

// Test exists initially returns false (status unknown behaves as not existing)
TEST_F(NodeTest_37, ExistsInitiallyFalse_37) {
  Node node("test", 0);
  EXPECT_FALSE(node.exists());
}

// Test multiple AddOutEdge calls
TEST_F(NodeTest_37, MultipleAddOutEdges_37) {
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

// Test multiple AddValidationOutEdge calls
TEST_F(NodeTest_37, MultipleAddValidationOutEdges_37) {
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

// Test set_in_edge to nullptr
TEST_F(NodeTest_37, SetInEdgeToNull_37) {
  Node node("test", 0);
  Edge edge;
  node.set_in_edge(&edge);
  EXPECT_EQ(&edge, node.in_edge());
  node.set_in_edge(nullptr);
  EXPECT_EQ(nullptr, node.in_edge());
}

// Test Stat error case
TEST_F(NodeTest_37, StatError_37) {
  Node node("error_file", 0);
  MockDiskInterface disk;
  std::string err;
  bool result = node.Stat(&disk, &err);
  EXPECT_FALSE(result);
  EXPECT_NE("", err);
}

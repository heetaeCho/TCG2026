#include "gtest/gtest.h"
#include "graph.h"
#include <string>
#include <vector>

// Minimal DiskInterface mock for Stat calls if needed
struct MockDiskInterface : public DiskInterface {
  virtual TimeStamp Stat(const std::string& path, std::string* err) const override {
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

class NodeTest_52 : public ::testing::Test {
 protected:
  void SetUp() override {
    node_ = new Node("test/path", 0);
  }
  void TearDown() override {
    delete node_;
  }
  Node* node_;
};

// Test that AddOutEdge adds an edge to the out_edges vector
TEST_F(NodeTest_52, AddOutEdge_AddsOneEdge_52) {
  Edge edge;
  EXPECT_EQ(node_->out_edges().size(), 0u);
  node_->AddOutEdge(&edge);
  EXPECT_EQ(node_->out_edges().size(), 1u);
  EXPECT_EQ(node_->out_edges()[0], &edge);
}

// Test that AddOutEdge can add multiple edges
TEST_F(NodeTest_52, AddOutEdge_AddsMultipleEdges_52) {
  Edge edge1, edge2, edge3;
  node_->AddOutEdge(&edge1);
  node_->AddOutEdge(&edge2);
  node_->AddOutEdge(&edge3);
  ASSERT_EQ(node_->out_edges().size(), 3u);
  EXPECT_EQ(node_->out_edges()[0], &edge1);
  EXPECT_EQ(node_->out_edges()[1], &edge2);
  EXPECT_EQ(node_->out_edges()[2], &edge3);
}

// Test that AddOutEdge preserves insertion order
TEST_F(NodeTest_52, AddOutEdge_PreservesOrder_52) {
  const int kNumEdges = 10;
  std::vector<Edge> edges(kNumEdges);
  for (int i = 0; i < kNumEdges; ++i) {
    node_->AddOutEdge(&edges[i]);
  }
  ASSERT_EQ(node_->out_edges().size(), static_cast<size_t>(kNumEdges));
  for (int i = 0; i < kNumEdges; ++i) {
    EXPECT_EQ(node_->out_edges()[i], &edges[i]);
  }
}

// Test that out_edges is initially empty
TEST_F(NodeTest_52, OutEdges_InitiallyEmpty_52) {
  EXPECT_TRUE(node_->out_edges().empty());
}

// Test that AddOutEdge allows adding the same edge pointer multiple times
TEST_F(NodeTest_52, AddOutEdge_DuplicateEdge_52) {
  Edge edge;
  node_->AddOutEdge(&edge);
  node_->AddOutEdge(&edge);
  EXPECT_EQ(node_->out_edges().size(), 2u);
  EXPECT_EQ(node_->out_edges()[0], &edge);
  EXPECT_EQ(node_->out_edges()[1], &edge);
}

// Test Node path
TEST_F(NodeTest_52, Path_ReturnsConstructorPath_52) {
  EXPECT_EQ(node_->path(), "test/path");
}

// Test Node slash_bits
TEST_F(NodeTest_52, SlashBits_ReturnsConstructorValue_52) {
  EXPECT_EQ(node_->slash_bits(), 0u);
}

// Test Node with non-zero slash_bits
TEST_F(NodeTest_52, SlashBits_NonZero_52) {
  Node node("foo\\bar", 1);
  EXPECT_EQ(node.slash_bits(), 1u);
  EXPECT_EQ(node.path(), "foo\\bar");
}

// Test set_dirty and dirty
TEST_F(NodeTest_52, SetDirty_52) {
  EXPECT_FALSE(node_->dirty());
  node_->set_dirty(true);
  EXPECT_TRUE(node_->dirty());
  node_->set_dirty(false);
  EXPECT_FALSE(node_->dirty());
}

// Test MarkDirty
TEST_F(NodeTest_52, MarkDirty_52) {
  EXPECT_FALSE(node_->dirty());
  node_->MarkDirty();
  EXPECT_TRUE(node_->dirty());
}

// Test set_in_edge and in_edge
TEST_F(NodeTest_52, SetInEdge_52) {
  EXPECT_EQ(node_->in_edge(), nullptr);
  Edge edge;
  node_->set_in_edge(&edge);
  EXPECT_EQ(node_->in_edge(), &edge);
}

// Test set_id and id
TEST_F(NodeTest_52, SetId_52) {
  EXPECT_EQ(node_->id(), -1);
  node_->set_id(42);
  EXPECT_EQ(node_->id(), 42);
}

// Test set_dyndep_pending and dyndep_pending
TEST_F(NodeTest_52, SetDyndepPending_52) {
  EXPECT_FALSE(node_->dyndep_pending());
  node_->set_dyndep_pending(true);
  EXPECT_TRUE(node_->dyndep_pending());
  node_->set_dyndep_pending(false);
  EXPECT_FALSE(node_->dyndep_pending());
}

// Test set_generated_by_dep_loader and generated_by_dep_loader
TEST_F(NodeTest_52, SetGeneratedByDepLoader_52) {
  // Default is true
  EXPECT_TRUE(node_->generated_by_dep_loader());
  node_->set_generated_by_dep_loader(false);
  EXPECT_FALSE(node_->generated_by_dep_loader());
  node_->set_generated_by_dep_loader(true);
  EXPECT_TRUE(node_->generated_by_dep_loader());
}

// Test AddValidationOutEdge
TEST_F(NodeTest_52, AddValidationOutEdge_52) {
  EXPECT_TRUE(node_->validation_out_edges().empty());
  Edge edge;
  node_->AddValidationOutEdge(&edge);
  ASSERT_EQ(node_->validation_out_edges().size(), 1u);
  EXPECT_EQ(node_->validation_out_edges()[0], &edge);
}

// Test AddValidationOutEdge multiple
TEST_F(NodeTest_52, AddValidationOutEdge_Multiple_52) {
  Edge e1, e2;
  node_->AddValidationOutEdge(&e1);
  node_->AddValidationOutEdge(&e2);
  ASSERT_EQ(node_->validation_out_edges().size(), 2u);
  EXPECT_EQ(node_->validation_out_edges()[0], &e1);
  EXPECT_EQ(node_->validation_out_edges()[1], &e2);
}

// Test status_known initially
TEST_F(NodeTest_52, StatusKnown_InitiallyFalse_52) {
  EXPECT_FALSE(node_->status_known());
}

// Test MarkMissing
TEST_F(NodeTest_52, MarkMissing_52) {
  node_->MarkMissing();
  EXPECT_TRUE(node_->status_known());
  EXPECT_FALSE(node_->exists());
}

// Test exists after MarkMissing
TEST_F(NodeTest_52, Exists_AfterMarkMissing_52) {
  node_->MarkMissing();
  EXPECT_FALSE(node_->exists());
}

// Test ResetState
TEST_F(NodeTest_52, ResetState_52) {
  node_->set_dirty(true);
  node_->set_id(10);
  node_->MarkMissing();
  node_->ResetState();
  // After reset, mtime should be back to default, status unknown
  EXPECT_FALSE(node_->status_known());
  EXPECT_FALSE(node_->dirty());
}

// Test mtime default value
TEST_F(NodeTest_52, Mtime_DefaultValue_52) {
  EXPECT_EQ(node_->mtime(), -1);
}

// Test Stat with mock disk interface
TEST_F(NodeTest_52, Stat_WithMockDiskInterface_52) {
  MockDiskInterface disk;
  std::string err;
  bool result = node_->Stat(&disk, &err);
  EXPECT_TRUE(result);
  EXPECT_TRUE(node_->status_known());
}

// Test StatIfNecessary only stats once
TEST_F(NodeTest_52, StatIfNecessary_OnlyStatsOnce_52) {
  MockDiskInterface disk;
  std::string err;
  // First call should stat
  bool result1 = node_->StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result1);
  EXPECT_TRUE(node_->status_known());
  // Second call should not need to stat again (already known)
  bool result2 = node_->StatIfNecessary(&disk, &err);
  EXPECT_TRUE(result2);
}

// Test that AddOutEdge and AddValidationOutEdge are independent
TEST_F(NodeTest_52, AddOutEdge_IndependentOfValidation_52) {
  Edge e1, e2;
  node_->AddOutEdge(&e1);
  node_->AddValidationOutEdge(&e2);
  EXPECT_EQ(node_->out_edges().size(), 1u);
  EXPECT_EQ(node_->validation_out_edges().size(), 1u);
  EXPECT_EQ(node_->out_edges()[0], &e1);
  EXPECT_EQ(node_->validation_out_edges()[0], &e2);
}

// Test empty path node
TEST_F(NodeTest_52, EmptyPath_52) {
  Node emptyNode("", 0);
  EXPECT_EQ(emptyNode.path(), "");
  EXPECT_EQ(emptyNode.slash_bits(), 0u);
}

// Test large number of out edges
TEST_F(NodeTest_52, AddOutEdge_LargeNumber_52) {
  const int kNumEdges = 1000;
  std::vector<Edge> edges(kNumEdges);
  for (int i = 0; i < kNumEdges; ++i) {
    node_->AddOutEdge(&edges[i]);
  }
  EXPECT_EQ(node_->out_edges().size(), static_cast<size_t>(kNumEdges));
  for (int i = 0; i < kNumEdges; ++i) {
    EXPECT_EQ(node_->out_edges()[i], &edges[i]);
  }
}

// Test set_id boundary values
TEST_F(NodeTest_52, SetId_BoundaryValues_52) {
  node_->set_id(0);
  EXPECT_EQ(node_->id(), 0);
  node_->set_id(INT_MAX);
  EXPECT_EQ(node_->id(), INT_MAX);
  node_->set_id(INT_MIN);
  EXPECT_EQ(node_->id(), INT_MIN);
}

// Test PathDecanonicalized instance method
TEST_F(NodeTest_52, PathDecanonicalized_Instance_52) {
  Node node("foo/bar", 0);
  std::string result = node.PathDecanonicalized();
  EXPECT_FALSE(result.empty());
}

// Test PathDecanonicalized static method
TEST_F(NodeTest_52, PathDecanonicalized_Static_52) {
  std::string result = Node::PathDecanonicalized("foo/bar", 0);
  EXPECT_EQ(result, "foo/bar");
}

// Test PathDecanonicalized static with slash_bits
TEST_F(NodeTest_52, PathDecanonicalized_StaticWithSlashBits_52) {
  // With slash_bits = 1, first slash should be backslash on Windows-like behavior
  std::string result = Node::PathDecanonicalized("foo/bar", 1);
  // The exact output depends on implementation, but we test it doesn't crash
  EXPECT_FALSE(result.empty());
}

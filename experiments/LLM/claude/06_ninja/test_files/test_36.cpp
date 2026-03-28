#include "gtest/gtest.h"
#include "graph.h"

// Test fixture for Node tests
class NodeTest_36 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test PathDecanonicalized with no slash bits (all forward slashes)
TEST_F(NodeTest_36, PathDecanonicalizedNoSlashBits_36) {
    Node node("path/to/file", 0);
    std::string result = node.PathDecanonicalized();
    // With slash_bits_ = 0, no slashes should be converted to backslashes
    EXPECT_EQ("path/to/file", result);
}

// Test PathDecanonicalized with slash bits set
TEST_F(NodeTest_36, PathDecanonicalizedWithSlashBits_36) {
    // slash_bits_ = 1 means the first slash should be a backslash
    Node node("path/to/file", 1);
    std::string result = node.PathDecanonicalized();
    // The first slash (at position 4) should become a backslash
    EXPECT_EQ("path\\to/file", result);
}

// Test PathDecanonicalized with all slash bits set
TEST_F(NodeTest_36, PathDecanonicalizedAllSlashBits_36) {
    // slash_bits_ = 3 (binary 11) means first two slashes become backslashes
    Node node("path/to/file", 3);
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("path\\to\\file", result);
}

// Test PathDecanonicalized with empty path
TEST_F(NodeTest_36, PathDecanonicalizedEmptyPath_36) {
    Node node("", 0);
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("", result);
}

// Test PathDecanonicalized with no slashes in path
TEST_F(NodeTest_36, PathDecanonicalizedNoSlashesInPath_36) {
    Node node("filename", 0);
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("filename", result);
}

// Test PathDecanonicalized with single slash
TEST_F(NodeTest_36, PathDecanonicalizedSingleSlash_36) {
    Node node("dir/file", 1);
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("dir\\file", result);
}

// Test PathDecanonicalized with single slash but no bits set
TEST_F(NodeTest_36, PathDecanonicalizedSingleSlashNoBits_36) {
    Node node("dir/file", 0);
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("dir/file", result);
}

// Test static PathDecanonicalized method
TEST_F(NodeTest_36, StaticPathDecanonicalizedNoSlashBits_36) {
    std::string result = Node::PathDecanonicalized("a/b/c", 0);
    EXPECT_EQ("a/b/c", result);
}

TEST_F(NodeTest_36, StaticPathDecanonicalizedWithSlashBits_36) {
    std::string result = Node::PathDecanonicalized("a/b/c", 0x7);
    EXPECT_EQ("a\\b\\c", result);
}

// Test that path() returns the original canonicalized path
TEST_F(NodeTest_36, PathReturnsOriginal_36) {
    Node node("path/to/file", 3);
    EXPECT_EQ("path/to/file", node.path());
}

// Test slash_bits accessor
TEST_F(NodeTest_36, SlashBitsAccessor_36) {
    Node node("path/to/file", 42);
    EXPECT_EQ(42u, node.slash_bits());
}

// Test dirty state
TEST_F(NodeTest_36, DirtyDefaultFalse_36) {
    Node node("file", 0);
    EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_36, SetDirtyTrue_36) {
    Node node("file", 0);
    node.set_dirty(true);
    EXPECT_TRUE(node.dirty());
}

TEST_F(NodeTest_36, SetDirtyFalse_36) {
    Node node("file", 0);
    node.set_dirty(true);
    node.set_dirty(false);
    EXPECT_FALSE(node.dirty());
}

TEST_F(NodeTest_36, MarkDirty_36) {
    Node node("file", 0);
    node.MarkDirty();
    EXPECT_TRUE(node.dirty());
}

// Test dyndep_pending
TEST_F(NodeTest_36, DyndepPendingDefault_36) {
    Node node("file", 0);
    EXPECT_FALSE(node.dyndep_pending());
}

TEST_F(NodeTest_36, SetDyndepPending_36) {
    Node node("file", 0);
    node.set_dyndep_pending(true);
    EXPECT_TRUE(node.dyndep_pending());
}

// Test in_edge
TEST_F(NodeTest_36, InEdgeDefaultNull_36) {
    Node node("file", 0);
    EXPECT_EQ(nullptr, node.in_edge());
}

TEST_F(NodeTest_36, SetInEdge_36) {
    Node node("file", 0);
    Edge edge;
    node.set_in_edge(&edge);
    EXPECT_EQ(&edge, node.in_edge());
}

// Test generated_by_dep_loader
TEST_F(NodeTest_36, GeneratedByDepLoaderDefault_36) {
    Node node("file", 0);
    EXPECT_TRUE(node.generated_by_dep_loader());
}

TEST_F(NodeTest_36, SetGeneratedByDepLoader_36) {
    Node node("file", 0);
    node.set_generated_by_dep_loader(false);
    EXPECT_FALSE(node.generated_by_dep_loader());
}

// Test id
TEST_F(NodeTest_36, IdDefault_36) {
    Node node("file", 0);
    EXPECT_EQ(-1, node.id());
}

TEST_F(NodeTest_36, SetId_36) {
    Node node("file", 0);
    node.set_id(42);
    EXPECT_EQ(42, node.id());
}

// Test out_edges
TEST_F(NodeTest_36, OutEdgesInitiallyEmpty_36) {
    Node node("file", 0);
    EXPECT_TRUE(node.out_edges().empty());
}

TEST_F(NodeTest_36, AddOutEdge_36) {
    Node node("file", 0);
    Edge edge;
    node.AddOutEdge(&edge);
    ASSERT_EQ(1u, node.out_edges().size());
    EXPECT_EQ(&edge, node.out_edges()[0]);
}

TEST_F(NodeTest_36, AddMultipleOutEdges_36) {
    Node node("file", 0);
    Edge edge1, edge2, edge3;
    node.AddOutEdge(&edge1);
    node.AddOutEdge(&edge2);
    node.AddOutEdge(&edge3);
    ASSERT_EQ(3u, node.out_edges().size());
    EXPECT_EQ(&edge1, node.out_edges()[0]);
    EXPECT_EQ(&edge2, node.out_edges()[1]);
    EXPECT_EQ(&edge3, node.out_edges()[2]);
}

// Test validation_out_edges
TEST_F(NodeTest_36, ValidationOutEdgesInitiallyEmpty_36) {
    Node node("file", 0);
    EXPECT_TRUE(node.validation_out_edges().empty());
}

TEST_F(NodeTest_36, AddValidationOutEdge_36) {
    Node node("file", 0);
    Edge edge;
    node.AddValidationOutEdge(&edge);
    ASSERT_EQ(1u, node.validation_out_edges().size());
    EXPECT_EQ(&edge, node.validation_out_edges()[0]);
}

// Test mtime
TEST_F(NodeTest_36, MtimeDefault_36) {
    Node node("file", 0);
    EXPECT_EQ(-1, node.mtime());
}

// Test status_known
TEST_F(NodeTest_36, StatusKnownDefault_36) {
    Node node("file", 0);
    // Default existence status is Unknown, so status_known should be false
    EXPECT_FALSE(node.status_known());
}

// Test MarkMissing
TEST_F(NodeTest_36, MarkMissing_36) {
    Node node("file", 0);
    node.MarkMissing();
    EXPECT_TRUE(node.status_known());
    EXPECT_FALSE(node.exists());
}

// Test exists after MarkMissing
TEST_F(NodeTest_36, ExistsAfterMarkMissing_36) {
    Node node("file", 0);
    node.MarkMissing();
    EXPECT_FALSE(node.exists());
}

// Test ResetState
TEST_F(NodeTest_36, ResetState_36) {
    Node node("file", 0);
    node.set_dirty(true);
    node.MarkMissing();
    node.ResetState();
    EXPECT_FALSE(node.dirty());
    EXPECT_FALSE(node.status_known());
}

// Test PathDecanonicalized with many slashes
TEST_F(NodeTest_36, PathDecanonicalizedManySlashes_36) {
    // Path with 4 slashes, set bits for alternating ones
    // slash_bits = 0b0101 = 5 -> 1st and 3rd slashes become backslashes
    Node node("a/b/c/d/e", 5);
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("a\\b/c\\d/e", result);
}

// Test PathDecanonicalized with second bit set
TEST_F(NodeTest_36, PathDecanonicalizedSecondBit_36) {
    // slash_bits = 2 (binary 10) means second slash becomes backslash
    Node node("a/b/c", 2);
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("a/b\\c", result);
}

// Test consistency between instance and static method
TEST_F(NodeTest_36, InstanceAndStaticConsistency_36) {
    std::string path = "x/y/z";
    uint64_t slash_bits = 5;
    Node node(path, slash_bits);
    EXPECT_EQ(Node::PathDecanonicalized(path, slash_bits), node.PathDecanonicalized());
}

// Test PathDecanonicalized path with no slashes and non-zero slash_bits
TEST_F(NodeTest_36, PathDecanonicalizedNoSlashesNonZeroBits_36) {
    // No slashes to convert, slash_bits should have no effect
    Node node("filename", 7);
    std::string result = node.PathDecanonicalized();
    EXPECT_EQ("filename", result);
}

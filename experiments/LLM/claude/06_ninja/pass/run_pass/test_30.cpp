#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "graph.h"
#include "disk_interface.h"

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgPointee;

class MockDiskInterface : public DiskInterface {
public:
    MOCK_METHOD(TimeStamp, Stat, (const std::string& path, std::string* err), (const, override));
    MOCK_METHOD(bool, MakeDir, (const std::string& path), (override));
    MOCK_METHOD(bool, WriteFile, (const std::string& path, const std::string& contents, bool crlf_on_windows), (override));
    MOCK_METHOD(int, RemoveFile, (const std::string& path), (override));
    MOCK_METHOD(Status, ReadFile, (const std::string& path, std::string* contents, std::string* err), (override));
};

class NodeTest_30 : public ::testing::Test {
protected:
    void SetUp() override {
        disk_interface_ = new MockDiskInterface();
    }

    void TearDown() override {
        delete disk_interface_;
    }

    MockDiskInterface* disk_interface_;
};

// Test that a newly constructed Node has expected default values
TEST_F(NodeTest_30, DefaultConstruction_30) {
    Node node("test_path", 0);
    EXPECT_EQ(node.path(), "test_path");
    EXPECT_EQ(node.slash_bits(), 0u);
    EXPECT_EQ(node.mtime(), -1);
    EXPECT_FALSE(node.dirty());
    EXPECT_FALSE(node.dyndep_pending());
    EXPECT_TRUE(node.generated_by_dep_loader());
    EXPECT_EQ(node.in_edge(), nullptr);
    EXPECT_TRUE(node.out_edges().empty());
    EXPECT_TRUE(node.validation_out_edges().empty());
    EXPECT_EQ(node.id(), -1);
}

// Test status_known returns false for a fresh node
TEST_F(NodeTest_30, StatusUnknownInitially_30) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.status_known());
}

// Test StatIfNecessary calls Stat when status is not known
TEST_F(NodeTest_30, StatIfNecessaryCallsStatWhenStatusUnknown_30) {
    Node node("test_path", 0);
    std::string err;

    EXPECT_CALL(*disk_interface_, Stat("test_path", _))
        .WillOnce(Return(100));

    EXPECT_TRUE(node.StatIfNecessary(disk_interface_, &err));
    EXPECT_TRUE(err.empty());
    EXPECT_TRUE(node.status_known());
    EXPECT_EQ(node.mtime(), 100);
}

// Test StatIfNecessary does NOT call Stat when status is already known
TEST_F(NodeTest_30, StatIfNecessarySkipsStatWhenStatusKnown_30) {
    Node node("test_path", 0);
    std::string err;

    EXPECT_CALL(*disk_interface_, Stat("test_path", _))
        .WillOnce(Return(100));

    // First call should invoke Stat
    EXPECT_TRUE(node.StatIfNecessary(disk_interface_, &err));
    EXPECT_TRUE(node.status_known());

    // Second call should NOT invoke Stat again
    EXPECT_CALL(*disk_interface_, Stat(_, _)).Times(0);
    EXPECT_TRUE(node.StatIfNecessary(disk_interface_, &err));
}

// Test Stat is called and returns file timestamp
TEST_F(NodeTest_30, StatReturnsFileTimestamp_30) {
    Node node("existing_file", 0);
    std::string err;

    EXPECT_CALL(*disk_interface_, Stat("existing_file", _))
        .WillOnce(Return(42));

    EXPECT_TRUE(node.Stat(disk_interface_, &err));
    EXPECT_EQ(node.mtime(), 42);
    EXPECT_TRUE(node.exists());
    EXPECT_TRUE(node.status_known());
}

// Test Stat for a non-existent file (mtime = 0)
TEST_F(NodeTest_30, StatNonExistentFile_30) {
    Node node("nonexistent", 0);
    std::string err;

    EXPECT_CALL(*disk_interface_, Stat("nonexistent", _))
        .WillOnce(Return(0));

    EXPECT_TRUE(node.Stat(disk_interface_, &err));
    EXPECT_EQ(node.mtime(), 0);
    EXPECT_FALSE(node.exists());
    EXPECT_TRUE(node.status_known());
}

// Test Stat error case (returns -1)
TEST_F(NodeTest_30, StatError_30) {
    Node node("error_file", 0);
    std::string err;

    EXPECT_CALL(*disk_interface_, Stat("error_file", _))
        .WillOnce(DoAll(SetArgPointee<1>("stat error"), Return(-1)));

    EXPECT_FALSE(node.Stat(disk_interface_, &err));
    EXPECT_EQ(err, "stat error");
}

// Test ResetState brings the node back to unknown state
TEST_F(NodeTest_30, ResetState_30) {
    Node node("test_path", 0);
    std::string err;

    EXPECT_CALL(*disk_interface_, Stat("test_path", _))
        .WillOnce(Return(100));

    node.Stat(disk_interface_, &err);
    EXPECT_TRUE(node.status_known());

    node.ResetState();
    EXPECT_FALSE(node.status_known());
    EXPECT_EQ(node.mtime(), -1);
}

// Test MarkMissing sets the node to non-existent
TEST_F(NodeTest_30, MarkMissing_30) {
    Node node("test_path", 0);
    node.MarkMissing();
    EXPECT_FALSE(node.exists());
    EXPECT_TRUE(node.status_known());
    EXPECT_EQ(node.mtime(), 0);
}

// Test exists() returns true when mtime > 0
TEST_F(NodeTest_30, ExistsWhenMtimePositive_30) {
    Node node("test_path", 0);
    std::string err;

    EXPECT_CALL(*disk_interface_, Stat("test_path", _))
        .WillOnce(Return(1));

    node.Stat(disk_interface_, &err);
    EXPECT_TRUE(node.exists());
}

// Test dirty flag get/set
TEST_F(NodeTest_30, DirtyFlag_30) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.dirty());
    node.set_dirty(true);
    EXPECT_TRUE(node.dirty());
    node.set_dirty(false);
    EXPECT_FALSE(node.dirty());
}

// Test MarkDirty
TEST_F(NodeTest_30, MarkDirty_30) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.dirty());
    node.MarkDirty();
    EXPECT_TRUE(node.dirty());
}

// Test dyndep_pending get/set
TEST_F(NodeTest_30, DyndepPending_30) {
    Node node("test_path", 0);
    EXPECT_FALSE(node.dyndep_pending());
    node.set_dyndep_pending(true);
    EXPECT_TRUE(node.dyndep_pending());
    node.set_dyndep_pending(false);
    EXPECT_FALSE(node.dyndep_pending());
}

// Test in_edge get/set
TEST_F(NodeTest_30, InEdge_30) {
    Node node("test_path", 0);
    EXPECT_EQ(node.in_edge(), nullptr);
    Edge edge;
    node.set_in_edge(&edge);
    EXPECT_EQ(node.in_edge(), &edge);
}

// Test generated_by_dep_loader get/set
TEST_F(NodeTest_30, GeneratedByDepLoader_30) {
    Node node("test_path", 0);
    EXPECT_TRUE(node.generated_by_dep_loader());
    node.set_generated_by_dep_loader(false);
    EXPECT_FALSE(node.generated_by_dep_loader());
    node.set_generated_by_dep_loader(true);
    EXPECT_TRUE(node.generated_by_dep_loader());
}

// Test id get/set
TEST_F(NodeTest_30, Id_30) {
    Node node("test_path", 0);
    EXPECT_EQ(node.id(), -1);
    node.set_id(42);
    EXPECT_EQ(node.id(), 42);
    node.set_id(0);
    EXPECT_EQ(node.id(), 0);
}

// Test AddOutEdge
TEST_F(NodeTest_30, AddOutEdge_30) {
    Node node("test_path", 0);
    EXPECT_TRUE(node.out_edges().empty());

    Edge edge1, edge2;
    node.AddOutEdge(&edge1);
    EXPECT_EQ(node.out_edges().size(), 1u);
    EXPECT_EQ(node.out_edges()[0], &edge1);

    node.AddOutEdge(&edge2);
    EXPECT_EQ(node.out_edges().size(), 2u);
    EXPECT_EQ(node.out_edges()[1], &edge2);
}

// Test AddValidationOutEdge
TEST_F(NodeTest_30, AddValidationOutEdge_30) {
    Node node("test_path", 0);
    EXPECT_TRUE(node.validation_out_edges().empty());

    Edge edge1, edge2;
    node.AddValidationOutEdge(&edge1);
    EXPECT_EQ(node.validation_out_edges().size(), 1u);
    EXPECT_EQ(node.validation_out_edges()[0], &edge1);

    node.AddValidationOutEdge(&edge2);
    EXPECT_EQ(node.validation_out_edges().size(), 2u);
    EXPECT_EQ(node.validation_out_edges()[1], &edge2);
}

// Test slash_bits stored correctly
TEST_F(NodeTest_30, SlashBits_30) {
    Node node("path\\to\\file", 3);
    EXPECT_EQ(node.slash_bits(), 3u);
}

// Test PathDecanonicalized (instance method)
TEST_F(NodeTest_30, PathDecanonicalized_30) {
    Node node("path/to/file", 0);
    // With slash_bits = 0, path should remain with forward slashes
    std::string decanon = node.PathDecanonicalized();
    EXPECT_FALSE(decanon.empty());
}

// Test PathDecanonicalized with slash_bits converting slashes
TEST_F(NodeTest_30, PathDecanonicalizedWithSlashBits_30) {
    // slash_bits=3 means bits 0 and 1 are set, converting first two slashes to backslashes
    Node node("a/b/c", 3);
    std::string decanon = node.PathDecanonicalized();
    // The first two slashes should be replaced with backslashes
    EXPECT_EQ(decanon, "a\\b\\c");
}

// Test static PathDecanonicalized
TEST_F(NodeTest_30, StaticPathDecanonicalized_30) {
    std::string result = Node::PathDecanonicalized("a/b/c", 0);
    EXPECT_EQ(result, "a/b/c");
}

// Test StatIfNecessary after MarkMissing - should not call Stat since status is known
TEST_F(NodeTest_30, StatIfNecessaryAfterMarkMissing_30) {
    Node node("test_path", 0);
    node.MarkMissing();
    EXPECT_TRUE(node.status_known());

    EXPECT_CALL(*disk_interface_, Stat(_, _)).Times(0);

    std::string err;
    EXPECT_TRUE(node.StatIfNecessary(disk_interface_, &err));
}

// Test StatIfNecessary after ResetState calls Stat again
TEST_F(NodeTest_30, StatIfNecessaryAfterResetState_30) {
    Node node("test_path", 0);
    std::string err;

    EXPECT_CALL(*disk_interface_, Stat("test_path", _))
        .WillOnce(Return(100))
        .WillOnce(Return(200));

    node.Stat(disk_interface_, &err);
    EXPECT_EQ(node.mtime(), 100);

    node.ResetState();
    EXPECT_FALSE(node.status_known());

    EXPECT_TRUE(node.StatIfNecessary(disk_interface_, &err));
    EXPECT_EQ(node.mtime(), 200);
}

// Test UpdatePhonyMtime
TEST_F(NodeTest_30, UpdatePhonyMtime_30) {
    Node node("phony", 0);
    node.MarkMissing();
    EXPECT_EQ(node.mtime(), 0);

    node.UpdatePhonyMtime(500);
    EXPECT_EQ(node.mtime(), 500);
}

// Test path() returns correct path
TEST_F(NodeTest_30, Path_30) {
    Node node("some/path/to/file.cc", 0);
    EXPECT_EQ(node.path(), "some/path/to/file.cc");
}

// Test empty path
TEST_F(NodeTest_30, EmptyPath_30) {
    Node node("", 0);
    EXPECT_EQ(node.path(), "");
}

// Test multiple out edges and validation edges don't interfere
TEST_F(NodeTest_30, OutEdgesAndValidationEdgesIndependent_30) {
    Node node("test", 0);
    Edge e1, e2, e3;

    node.AddOutEdge(&e1);
    node.AddValidationOutEdge(&e2);
    node.AddOutEdge(&e3);

    EXPECT_EQ(node.out_edges().size(), 2u);
    EXPECT_EQ(node.validation_out_edges().size(), 1u);
    EXPECT_EQ(node.out_edges()[0], &e1);
    EXPECT_EQ(node.out_edges()[1], &e3);
    EXPECT_EQ(node.validation_out_edges()[0], &e2);
}

// Test StatIfNecessary with Stat error propagation
TEST_F(NodeTest_30, StatIfNecessaryErrorPropagation_30) {
    Node node("error_file", 0);
    std::string err;

    EXPECT_CALL(*disk_interface_, Stat("error_file", _))
        .WillOnce(DoAll(SetArgPointee<1>("disk error"), Return(-1)));

    EXPECT_FALSE(node.StatIfNecessary(disk_interface_, &err));
    EXPECT_EQ(err, "disk error");
}

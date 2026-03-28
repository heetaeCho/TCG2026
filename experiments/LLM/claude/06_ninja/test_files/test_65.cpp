#include "gtest/gtest.h"
#include "graph.h"
#include "state.h"
#include "build_log.h"
#include "deps_log.h"
#include "disk_interface.h"
#include "test.h"

class DependencyScanTest_65 : public testing::Test {
 protected:
  void SetUp() override {
    state_.Reset();
  }

  State state_;
  BuildLog build_log_;
  DepsLog deps_log_;
  RealDiskInterface disk_interface_;
  DepfileParserOptions depfile_parser_options_;
};

TEST_F(DependencyScanTest_65, BuildLogReturnsCorrectPointer_65) {
  DependencyScan scan(&state_, &build_log_, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  EXPECT_EQ(&build_log_, scan.build_log());
}

TEST_F(DependencyScanTest_65, BuildLogReturnsNullWhenConstructedWithNull_65) {
  DependencyScan scan(&state_, nullptr, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  EXPECT_EQ(nullptr, scan.build_log());
}

TEST_F(DependencyScanTest_65, SetBuildLogChangesReturnedPointer_65) {
  DependencyScan scan(&state_, nullptr, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  EXPECT_EQ(nullptr, scan.build_log());

  scan.set_build_log(&build_log_);
  EXPECT_EQ(&build_log_, scan.build_log());
}

TEST_F(DependencyScanTest_65, SetBuildLogToNullAfterNonNull_65) {
  DependencyScan scan(&state_, &build_log_, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  EXPECT_EQ(&build_log_, scan.build_log());

  scan.set_build_log(nullptr);
  EXPECT_EQ(nullptr, scan.build_log());
}

TEST_F(DependencyScanTest_65, DepsLogReturnsCorrectPointer_65) {
  DependencyScan scan(&state_, &build_log_, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  EXPECT_EQ(&deps_log_, scan.deps_log());
}

TEST_F(DependencyScanTest_65, SetBuildLogMultipleTimes_65) {
  DependencyScan scan(&state_, nullptr, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);

  BuildLog log1, log2, log3;
  scan.set_build_log(&log1);
  EXPECT_EQ(&log1, scan.build_log());

  scan.set_build_log(&log2);
  EXPECT_EQ(&log2, scan.build_log());

  scan.set_build_log(&log3);
  EXPECT_EQ(&log3, scan.build_log());
}

TEST_F(DependencyScanTest_65, BuildLogConsistencyAfterConstruction_65) {
  BuildLog specific_log;
  DependencyScan scan(&state_, &specific_log, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  // Call build_log() multiple times to ensure consistency
  EXPECT_EQ(&specific_log, scan.build_log());
  EXPECT_EQ(&specific_log, scan.build_log());
  EXPECT_EQ(scan.build_log(), scan.build_log());
}

// Test RecomputeDirty with a simple node that has no edges
TEST_F(DependencyScanTest_65, RecomputeDirtyOnNodeWithNoInEdge_65) {
  // A node with no in_edge should be handled without error
  Node* node = state_.GetNode("nonexistent_file", 0);
  std::vector<Node*> validation_nodes;
  std::string err;
  
  bool result = false;
  DependencyScan scan(&state_, &build_log_, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  result = scan.RecomputeDirty(node, &validation_nodes, &err);
  // A node with no in_edge and no file on disk should succeed
  EXPECT_TRUE(result);
}

// Test with VirtualFileSystem for more controlled testing
class DependencyScanVFSTest_65 : public testing::Test {
 protected:
  void SetUp() override {
    state_.Reset();
  }

  State state_;
  BuildLog build_log_;
  DepsLog deps_log_;
  VirtualFileSystem fs_;
  DepfileParserOptions depfile_parser_options_;
};

TEST_F(DependencyScanVFSTest_65, RecomputeDirtyExistingFile_65) {
  fs_.Create("existing_file", "content");
  Node* node = state_.GetNode("existing_file", 0);
  std::vector<Node*> validation_nodes;
  std::string err;

  DependencyScan scan(&state_, &build_log_, &deps_log_, &fs_,
                      &depfile_parser_options_, nullptr);
  bool result = scan.RecomputeDirty(node, &validation_nodes, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
}

TEST_F(DependencyScanVFSTest_65, RecomputeDirtyMissingFile_65) {
  Node* node = state_.GetNode("missing_file", 0);
  std::vector<Node*> validation_nodes;
  std::string err;

  DependencyScan scan(&state_, &build_log_, &deps_log_, &fs_,
                      &depfile_parser_options_, nullptr);
  bool result = scan.RecomputeDirty(node, &validation_nodes, &err);
  EXPECT_TRUE(result);
}

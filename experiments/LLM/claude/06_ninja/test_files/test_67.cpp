#include "gtest/gtest.h"
#include "graph.h"
#include "state.h"
#include "build_log.h"
#include "deps_log.h"
#include "disk_interface.h"
#include "test.h"

// Test fixture for DependencyScan
class DependencyScanTest_67 : public testing::Test {
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

// Test that deps_log() returns the DepsLog pointer passed during construction
TEST_F(DependencyScanTest_67, DepsLogReturnsCorrectPointer_67) {
  DependencyScan scan(&state_, &build_log_, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  EXPECT_EQ(&deps_log_, scan.deps_log());
}

// Test that build_log() returns the BuildLog pointer passed during construction
TEST_F(DependencyScanTest_67, BuildLogReturnsCorrectPointer_67) {
  DependencyScan scan(&state_, &build_log_, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  EXPECT_EQ(&build_log_, scan.build_log());
}

// Test that set_build_log changes the returned build log
TEST_F(DependencyScanTest_67, SetBuildLogChangesPointer_67) {
  DependencyScan scan(&state_, &build_log_, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  BuildLog new_log;
  scan.set_build_log(&new_log);
  EXPECT_EQ(&new_log, scan.build_log());
}

// Test that set_build_log to nullptr works
TEST_F(DependencyScanTest_67, SetBuildLogToNullptr_67) {
  DependencyScan scan(&state_, &build_log_, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  scan.set_build_log(nullptr);
  EXPECT_EQ(nullptr, scan.build_log());
}

// Test that deps_log returns correct value when constructed with nullptr DepsLog
TEST_F(DependencyScanTest_67, DepsLogWithNullptr_67) {
  DependencyScan scan(&state_, &build_log_, nullptr, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  EXPECT_EQ(nullptr, scan.deps_log());
}

// Test that build_log returns correct value when constructed with nullptr BuildLog
TEST_F(DependencyScanTest_67, BuildLogWithNullptr_67) {
  DependencyScan scan(&state_, nullptr, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  EXPECT_EQ(nullptr, scan.build_log());
}

// Test fixture using VirtualFileSystem for more complex scenarios
class DependencyScanIntegrationTest_67 : public testing::Test {
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

// Test RecomputeDirty on a node with no edges (a source file that doesn't exist)
TEST_F(DependencyScanIntegrationTest_67, RecomputeDirtySourceNodeNotExist_67) {
  DependencyScan scan(&state_, &build_log_, &deps_log_, &fs_,
                      &depfile_parser_options_, nullptr);
  
  Node* node = state_.GetNode("nonexistent.cc", 0);
  std::vector<Node*> validation_nodes;
  std::string err;
  
  // A source node with no in_edge should succeed in RecomputeDirty
  bool result = scan.RecomputeDirty(node, &validation_nodes, &err);
  EXPECT_TRUE(result);
}

// Test RecomputeDirty on a node that is a source file which exists
TEST_F(DependencyScanIntegrationTest_67, RecomputeDirtySourceNodeExists_67) {
  fs_.Create("existing.cc", "content");
  
  DependencyScan scan(&state_, &build_log_, &deps_log_, &fs_,
                      &depfile_parser_options_, nullptr);
  
  Node* node = state_.GetNode("existing.cc", 0);
  std::vector<Node*> validation_nodes;
  std::string err;
  
  bool result = scan.RecomputeDirty(node, &validation_nodes, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
}

// Test with a simple edge: input -> output
TEST_F(DependencyScanIntegrationTest_67, RecomputeDirtyWithEdge_67) {
  // Add a rule and edge
  AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in > $out\n"
    "build out.o: cc in.cc\n");
  
  fs_.Create("in.cc", "");
  
  DependencyScan scan(&state_, &build_log_, &deps_log_, &fs_,
                      &depfile_parser_options_, nullptr);
  
  Node* node = state_.GetNode("out.o", 0);
  std::vector<Node*> validation_nodes;
  std::string err;
  
  bool result = scan.RecomputeDirty(node, &validation_nodes, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
  // Output doesn't exist, so it should be dirty
  EXPECT_TRUE(node->dirty());
}

// Test that output is not dirty when it's up-to-date
TEST_F(DependencyScanIntegrationTest_67, RecomputeDirtyUpToDate_67) {
  AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in > $out\n"
    "build out.o: cc in.cc\n");
  
  fs_.Create("in.cc", "");
  fs_.Create("out.o", "");
  
  // Make output newer than input
  fs_.files_["in.cc"].mtime = 1;
  fs_.files_["out.o"].mtime = 2;
  
  // Record the command in the build log so it matches
  BuildLog::LogEntry* entry = new BuildLog::LogEntry;
  entry->output = "out.o";
  entry->command = "cc in.cc > out.o";
  entry->start_time = 0;
  entry->end_time = 1;
  entry->mtime = 2;
  build_log_.entries_["out.o"] = entry;
  
  DependencyScan scan(&state_, &build_log_, &deps_log_, &fs_,
                      &depfile_parser_options_, nullptr);
  
  Node* node = state_.GetNode("out.o", 0);
  std::vector<Node*> validation_nodes;
  std::string err;
  
  bool result = scan.RecomputeDirty(node, &validation_nodes, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
}

// Test RecomputeDirty with a cycle should fail
TEST_F(DependencyScanIntegrationTest_67, RecomputeDirtyDetectsCycle_67) {
  AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in > $out\n"
    "build a: cc b\n"
    "build b: cc a\n");
  
  DependencyScan scan(&state_, &build_log_, &deps_log_, &fs_,
                      &depfile_parser_options_, nullptr);
  
  Node* node = state_.GetNode("a", 0);
  std::vector<Node*> validation_nodes;
  std::string err;
  
  bool result = scan.RecomputeDirty(node, &validation_nodes, &err);
  EXPECT_FALSE(result);
  EXPECT_NE("", err);
}

// Test that output is dirty when input is newer
TEST_F(DependencyScanIntegrationTest_67, RecomputeDirtyInputNewer_67) {
  AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in > $out\n"
    "build out.o: cc in.cc\n");
  
  fs_.Create("in.cc", "");
  fs_.Create("out.o", "");
  
  // Make input newer than output
  fs_.files_["in.cc"].mtime = 2;
  fs_.files_["out.o"].mtime = 1;
  
  DependencyScan scan(&state_, &build_log_, &deps_log_, &fs_,
                      &depfile_parser_options_, nullptr);
  
  Node* node = state_.GetNode("out.o", 0);
  std::vector<Node*> validation_nodes;
  std::string err;
  
  bool result = scan.RecomputeDirty(node, &validation_nodes, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
  EXPECT_TRUE(node->dirty());
}

// Test RecomputeOutputsDirty
TEST_F(DependencyScanIntegrationTest_67, RecomputeOutputsDirty_67) {
  AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in > $out\n"
    "build out.o: cc in.cc\n");
  
  fs_.Create("in.cc", "");
  
  DependencyScan scan(&state_, &build_log_, &deps_log_, &fs_,
                      &depfile_parser_options_, nullptr);
  
  Edge* edge = state_.GetNode("out.o", 0)->in_edge();
  ASSERT_NE(nullptr, edge);
  
  Node* input = state_.GetNode("in.cc", 0);
  input->Stat(&fs_, nullptr);
  
  bool dirty = false;
  std::string err;
  bool result = scan.RecomputeOutputsDirty(edge, input, &dirty, &err);
  EXPECT_TRUE(result);
}

// Test multiple set_build_log calls
TEST_F(DependencyScanTest_67, SetBuildLogMultipleTimes_67) {
  DependencyScan scan(&state_, &build_log_, &deps_log_, &disk_interface_,
                      &depfile_parser_options_, nullptr);
  
  BuildLog log1, log2, log3;
  
  scan.set_build_log(&log1);
  EXPECT_EQ(&log1, scan.build_log());
  
  scan.set_build_log(&log2);
  EXPECT_EQ(&log2, scan.build_log());
  
  scan.set_build_log(&log3);
  EXPECT_EQ(&log3, scan.build_log());
}

// Test construction with different DepsLog instances
TEST_F(DependencyScanTest_67, DepsLogDifferentInstances_67) {
  DepsLog deps_log1, deps_log2;
  
  DependencyScan scan1(&state_, &build_log_, &deps_log1, &disk_interface_,
                       &depfile_parser_options_, nullptr);
  DependencyScan scan2(&state_, &build_log_, &deps_log2, &disk_interface_,
                       &depfile_parser_options_, nullptr);
  
  EXPECT_EQ(&deps_log1, scan1.deps_log());
  EXPECT_EQ(&deps_log2, scan2.deps_log());
  EXPECT_NE(scan1.deps_log(), scan2.deps_log());
}

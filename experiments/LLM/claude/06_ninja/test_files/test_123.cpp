#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "missing_deps.h"
#include "deps_log.h"
#include "state.h"
#include "disk_interface.h"
#include "graph.h"

// Mock for MissingDependencyScannerDelegate
struct MockMissingDependencyScannerDelegate : public MissingDependencyScannerDelegate {
  MOCK_METHOD(void, OnMissingDep, (Node* node, const std::string& path, const std::string& generator), (override));
};

// Mock for DiskInterface
struct MockDiskInterface : public DiskInterface {
  MOCK_METHOD(TimeStamp, Stat, (const std::string& path, std::string* err), (const, override));
  MOCK_METHOD(bool, WriteFile, (const std::string& path, const std::string& contents), (override));
  MOCK_METHOD(bool, MakeDir, (const std::string& path), (override));
  MOCK_METHOD(Status, ReadFile, (const std::string& path, std::string* contents, std::string* err), (override));
  MOCK_METHOD(int, RemoveFile, (const std::string& path), (override));
};

class MissingDependencyScannerTest_123 : public ::testing::Test {
 protected:
  void SetUp() override {
    delegate_ = new MockMissingDependencyScannerDelegate();
    deps_log_ = new DepsLog();
    state_ = new State();
    disk_interface_ = new MockDiskInterface();
    scanner_ = new MissingDependencyScanner(delegate_, deps_log_, state_, disk_interface_);
  }

  void TearDown() override {
    delete scanner_;
    delete disk_interface_;
    delete state_;
    delete deps_log_;
    delete delegate_;
  }

  MockMissingDependencyScannerDelegate* delegate_;
  DepsLog* deps_log_;
  State* state_;
  MockDiskInterface* disk_interface_;
  MissingDependencyScanner* scanner_;
};

// Test that a freshly constructed scanner has no missing deps
TEST_F(MissingDependencyScannerTest_123, InitiallyNoMissingDeps_123) {
  EXPECT_FALSE(scanner_->HadMissingDeps());
}

// Test that nodes_missing_deps_ being empty means HadMissingDeps returns false
TEST_F(MissingDependencyScannerTest_123, HadMissingDepsReturnsFalseWhenEmpty_123) {
  EXPECT_TRUE(scanner_->nodes_missing_deps_.empty());
  EXPECT_FALSE(scanner_->HadMissingDeps());
}

// Test that HadMissingDeps returns true when nodes_missing_deps_ is non-empty
TEST_F(MissingDependencyScannerTest_123, HadMissingDepsReturnsTrueWhenNonEmpty_123) {
  // Create a node through state to insert into nodes_missing_deps_
  Node* node = state_->GetNode("test_node", 0);
  scanner_->nodes_missing_deps_.insert(node);
  EXPECT_TRUE(scanner_->HadMissingDeps());
}

// Test that missing_dep_path_count_ starts at zero
TEST_F(MissingDependencyScannerTest_123, InitialMissingDepPathCountIsZero_123) {
  EXPECT_EQ(0, scanner_->missing_dep_path_count_);
}

// Test that seen_ set is initially empty
TEST_F(MissingDependencyScannerTest_123, InitiallySeenIsEmpty_123) {
  EXPECT_TRUE(scanner_->seen_.empty());
}

// Test that generated_nodes_ set is initially empty
TEST_F(MissingDependencyScannerTest_123, InitiallyGeneratedNodesIsEmpty_123) {
  EXPECT_TRUE(scanner_->generated_nodes_.empty());
}

// Test that generator_rules_ set is initially empty
TEST_F(MissingDependencyScannerTest_123, InitiallyGeneratorRulesIsEmpty_123) {
  EXPECT_TRUE(scanner_->generator_rules_.empty());
}

// Test that delegate is properly stored
TEST_F(MissingDependencyScannerTest_123, DelegateIsStored_123) {
  EXPECT_EQ(delegate_, scanner_->delegate_);
}

// Test HadMissingDeps after inserting and removing from nodes_missing_deps_
TEST_F(MissingDependencyScannerTest_123, HadMissingDepsAfterInsertAndRemove_123) {
  Node* node = state_->GetNode("some_node", 0);
  scanner_->nodes_missing_deps_.insert(node);
  EXPECT_TRUE(scanner_->HadMissingDeps());

  scanner_->nodes_missing_deps_.erase(node);
  EXPECT_FALSE(scanner_->HadMissingDeps());
}

// Test HadMissingDeps with multiple nodes
TEST_F(MissingDependencyScannerTest_123, HadMissingDepsWithMultipleNodes_123) {
  Node* node1 = state_->GetNode("node1", 0);
  Node* node2 = state_->GetNode("node2", 0);
  scanner_->nodes_missing_deps_.insert(node1);
  scanner_->nodes_missing_deps_.insert(node2);
  EXPECT_TRUE(scanner_->HadMissingDeps());

  scanner_->nodes_missing_deps_.erase(node1);
  EXPECT_TRUE(scanner_->HadMissingDeps());

  scanner_->nodes_missing_deps_.erase(node2);
  EXPECT_FALSE(scanner_->HadMissingDeps());
}

// Test ProcessNode with a node that has no edge (should not crash)
TEST_F(MissingDependencyScannerTest_123, ProcessNodeWithNoEdge_123) {
  Node* node = state_->GetNode("no_edge_node", 0);
  // ProcessNode on a node with no in_edge should be safe
  scanner_->ProcessNode(node);
  // After processing a node with no edge, it shouldn't produce missing deps
  // (the node has no build rule, so nothing to analyze)
}

// Test ProcessNodeDeps with zero deps
TEST_F(MissingDependencyScannerTest_123, ProcessNodeDepsWithZeroDeps_123) {
  Node* node = state_->GetNode("zero_deps_node", 0);
  scanner_->ProcessNodeDeps(node, nullptr, 0);
  // No missing deps should be reported for zero deps
  EXPECT_FALSE(scanner_->HadMissingDeps());
}

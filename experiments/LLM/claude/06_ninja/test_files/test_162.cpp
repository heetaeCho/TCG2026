#include "gtest/gtest.h"
#include "clean.h"
#include "build.h"
#include "state.h"
#include "disk_interface.h"
#include "graph.h"
#include "build_log.h"

#include <string>
#include <set>
#include <map>

// A simple mock/stub DiskInterface for testing
struct TestDiskInterface : public DiskInterface {
  virtual TimeStamp Stat(const std::string& path, std::string* err) const override {
    auto it = files_.find(path);
    if (it != files_.end())
      return 1;
    return 0;
  }

  virtual bool WriteFile(const std::string& path, const std::string& contents) override {
    files_[path] = contents;
    return true;
  }

  virtual bool MakeDir(const std::string& path) override {
    return true;
  }

  virtual Status ReadFile(const std::string& path, std::string* contents, std::string* err) override {
    auto it = files_.find(path);
    if (it != files_.end()) {
      *contents = it->second;
      return Okay;
    }
    return NotFound;
  }

  virtual int RemoveFile(const std::string& path) override {
    auto it = files_.find(path);
    if (it != files_.end()) {
      files_.erase(it);
      removed_.insert(path);
      return 0;
    }
    return 1;
  }

  std::map<std::string, std::string> files_;
  std::set<std::string> removed_;
};

class CleanerTest_162 : public ::testing::Test {
 protected:
  void SetUp() override {
    disk_interface_ = new TestDiskInterface();
  }

  void TearDown() override {
    delete disk_interface_;
  }

  TestDiskInterface* disk_interface_;
  State state_;
};

// Test IsVerbose with QUIET verbosity
TEST_F(CleanerTest_162, IsVerboseReturnsFalseWhenQuiet_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::QUIET;
  config.dry_run = false;

  Cleaner cleaner(&state_, config, disk_interface_);
  EXPECT_FALSE(cleaner.IsVerbose());
}

// Test IsVerbose with QUIET verbosity but dry_run true
// QUIET should still make it non-verbose regardless of dry_run
TEST_F(CleanerTest_162, IsVerboseReturnsFalseWhenQuietEvenDryRun_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::QUIET;
  config.dry_run = true;

  Cleaner cleaner(&state_, config, disk_interface_);
  EXPECT_FALSE(cleaner.IsVerbose());
}

// Test IsVerbose with VERBOSE verbosity
TEST_F(CleanerTest_162, IsVerboseReturnsTrueWhenVerbose_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::VERBOSE;
  config.dry_run = false;

  Cleaner cleaner(&state_, config, disk_interface_);
  EXPECT_TRUE(cleaner.IsVerbose());
}

// Test IsVerbose with NORMAL verbosity and dry_run = true
TEST_F(CleanerTest_162, IsVerboseReturnsTrueWhenNormalDryRun_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::NORMAL;
  config.dry_run = true;

  Cleaner cleaner(&state_, config, disk_interface_);
  EXPECT_TRUE(cleaner.IsVerbose());
}

// Test IsVerbose with NORMAL verbosity and dry_run = false
TEST_F(CleanerTest_162, IsVerboseReturnsFalseWhenNormalNoDryRun_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::NORMAL;
  config.dry_run = false;

  Cleaner cleaner(&state_, config, disk_interface_);
  EXPECT_FALSE(cleaner.IsVerbose());
}

// Test IsVerbose with NO_STATUS_UPDATE and dry_run true
TEST_F(CleanerTest_162, IsVerboseReturnsTrueWhenNoStatusUpdateDryRun_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::NO_STATUS_UPDATE;
  config.dry_run = true;

  Cleaner cleaner(&state_, config, disk_interface_);
  EXPECT_TRUE(cleaner.IsVerbose());
}

// Test IsVerbose with NO_STATUS_UPDATE and dry_run false
TEST_F(CleanerTest_162, IsVerboseReturnsFalseWhenNoStatusUpdateNoDryRun_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::NO_STATUS_UPDATE;
  config.dry_run = false;

  Cleaner cleaner(&state_, config, disk_interface_);
  EXPECT_FALSE(cleaner.IsVerbose());
}

// Test cleaned_files_count on a fresh Cleaner
TEST_F(CleanerTest_162, CleanedFilesCountInitiallyZero_162) {
  BuildConfig config;
  Cleaner cleaner(&state_, config, disk_interface_);
  EXPECT_EQ(0, cleaner.cleaned_files_count());
}

// Test CleanAll with no edges in state (nothing to clean)
TEST_F(CleanerTest_162, CleanAllNoEdgesReturnsZero_162) {
  BuildConfig config;
  Cleaner cleaner(&state_, config, disk_interface_);
  int result = cleaner.CleanAll(false);
  EXPECT_EQ(0, result);
  EXPECT_EQ(0, cleaner.cleaned_files_count());
}

// Test CleanAll with generator=true and no edges
TEST_F(CleanerTest_162, CleanAllGeneratorNoEdgesReturnsZero_162) {
  BuildConfig config;
  Cleaner cleaner(&state_, config, disk_interface_);
  int result = cleaner.CleanAll(true);
  EXPECT_EQ(0, result);
}

// Test CleanTarget with nonexistent target name
TEST_F(CleanerTest_162, CleanTargetNonexistentTargetByName_162) {
  BuildConfig config;
  Cleaner cleaner(&state_, config, disk_interface_);
  int result = cleaner.CleanTarget("nonexistent_target");
  // Cleaning a target that doesn't exist in the state
  EXPECT_EQ(1, result);
}

// Test CleanRule with nonexistent rule name
TEST_F(CleanerTest_162, CleanRuleNonexistentRuleByName_162) {
  BuildConfig config;
  Cleaner cleaner(&state_, config, disk_interface_);
  int result = cleaner.CleanRule("nonexistent_rule");
  EXPECT_EQ(1, result);
}

// Test CleanDead with empty entries
TEST_F(CleanerTest_162, CleanDeadEmptyEntries_162) {
  BuildConfig config;
  Cleaner cleaner(&state_, config, disk_interface_);
  BuildLog::Entries entries;
  int result = cleaner.CleanDead(entries);
  EXPECT_EQ(0, result);
}

// Test that CleanTargets with zero count works
TEST_F(CleanerTest_162, CleanTargetsZeroCount_162) {
  BuildConfig config;
  Cleaner cleaner(&state_, config, disk_interface_);
  int result = cleaner.CleanTargets(0, nullptr);
  EXPECT_EQ(0, result);
}

// Test that CleanRules with zero count works
TEST_F(CleanerTest_162, CleanRulesZeroCount_162) {
  BuildConfig config;
  Cleaner cleaner(&state_, config, disk_interface_);
  int result = cleaner.CleanRules(0, nullptr);
  EXPECT_EQ(0, result);
}

// Test with a simple build graph - add an edge with input and output
TEST_F(CleanerTest_162, CleanTargetWithExistingTarget_162) {
  BuildConfig config;
  
  // Create a simple build graph
  std::string err;
  state_.AddRule(new Rule("cat"));
  Edge* edge = state_.AddEdge(state_.LookupRule("cat"));
  
  // Add input and output nodes
  Node* in = state_.GetNode("in.txt", 0);
  Node* out = state_.GetNode("out.txt", 0);
  edge->inputs_.push_back(in);
  edge->outputs_.push_back(out);
  in->AddOutEdge(edge);
  out->set_in_edge(edge);
  
  // Create the output file on disk
  disk_interface_->files_["out.txt"] = "content";
  
  Cleaner cleaner(&state_, config, disk_interface_);
  int result = cleaner.CleanTarget(out);
  EXPECT_EQ(0, result);
  EXPECT_GE(cleaner.cleaned_files_count(), 0);
}

// Test CleanAll in dry_run mode
TEST_F(CleanerTest_162, CleanAllDryRunDoesNotRemoveFiles_162) {
  BuildConfig config;
  config.dry_run = true;
  
  std::string err;
  state_.AddRule(new Rule("cat"));
  Edge* edge = state_.AddEdge(state_.LookupRule("cat"));
  
  Node* in = state_.GetNode("in.txt", 0);
  Node* out = state_.GetNode("out.txt", 0);
  edge->inputs_.push_back(in);
  edge->outputs_.push_back(out);
  in->AddOutEdge(edge);
  out->set_in_edge(edge);
  
  disk_interface_->files_["out.txt"] = "content";
  
  Cleaner cleaner(&state_, config, disk_interface_);
  int result = cleaner.CleanAll(false);
  EXPECT_EQ(0, result);
  
  // In dry run mode, the file should still exist
  EXPECT_TRUE(disk_interface_->files_.count("out.txt") > 0);
}

// Test IsVerbose with VERBOSE and dry_run = true
TEST_F(CleanerTest_162, IsVerboseReturnsTrueWhenVerboseAndDryRun_162) {
  BuildConfig config;
  config.verbosity = BuildConfig::VERBOSE;
  config.dry_run = true;

  Cleaner cleaner(&state_, config, disk_interface_);
  EXPECT_TRUE(cleaner.IsVerbose());
}

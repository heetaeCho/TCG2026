#include "gtest/gtest.h"
#include "clean.h"
#include "state.h"
#include "build.h"
#include "graph.h"
#include "disk_interface.h"
#include "build_log.h"
#include "util.h"

#include <string>
#include <set>
#include <cstring>

// A virtual filesystem for testing purposes
struct VirtualFileSystem : public DiskInterface {
  std::set<std::string> files_;
  std::set<std::string> directories_;

  void Create(const std::string& path) {
    files_.insert(path);
  }

  virtual TimeStamp Stat(const std::string& path, std::string* err) const override {
    if (files_.count(path) > 0)
      return 1;
    return 0;
  }

  virtual bool WriteFile(const std::string& path, const std::string& contents) override {
    files_.insert(path);
    return true;
  }

  virtual bool MakeDir(const std::string& path) override {
    directories_.insert(path);
    return true;
  }

  virtual Status ReadFile(const std::string& path, std::string* contents, std::string* err) override {
    if (files_.count(path) > 0) {
      *contents = "";
      return Okay;
    }
    *err = "file not found";
    return NotFound;
  }

  virtual int RemoveFile(const std::string& path) override {
    if (files_.count(path) > 0) {
      files_.erase(path);
      return 0;
    }
    return 1;
  }
};

class CleanerTest_161 : public ::testing::Test {
 protected:
  virtual void SetUp() override {
    config_.verbosity = BuildConfig::NORMAL;
  }

  void AssertParse(State* state, const char* input, ManifestParserOptions opts = ManifestParserOptions()) {
    ManifestParser parser(state, &fs_, opts);
    std::string err;
    ASSERT_TRUE(parser.ParseTest(input, &err)) << err;
  }

  State state_;
  BuildConfig config_;
  VirtualFileSystem fs_;
};

TEST_F(CleanerTest_161, CleanAllNoFiles_161) {
  // No build rules, cleaning all should succeed and clean 0 files.
  Cleaner cleaner(&state_, config_, &fs_);
  EXPECT_EQ(0, cleaner.CleanAll(false));
  EXPECT_EQ(0, cleaner.cleaned_files_count());
}

TEST_F(CleanerTest_161, CleanAllWithFiles_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"
    "build out2: cc in2\n"));

  fs_.Create("in1");
  fs_.Create("in2");
  fs_.Create("out1");
  fs_.Create("out2");

  Cleaner cleaner(&state_, config_, &fs_);
  EXPECT_EQ(0, cleaner.CleanAll(false));
  EXPECT_EQ(2, cleaner.cleaned_files_count());
  EXPECT_EQ(0u, fs_.files_.count("out1"));
  EXPECT_EQ(0u, fs_.files_.count("out2"));
}

TEST_F(CleanerTest_161, CleanTargetByNode_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"
    "build out2: cc in2\n"));

  fs_.Create("in1");
  fs_.Create("in2");
  fs_.Create("out1");
  fs_.Create("out2");

  Cleaner cleaner(&state_, config_, &fs_);
  Node* target = state_.LookupNode("out1");
  ASSERT_NE(nullptr, target);
  EXPECT_EQ(0, cleaner.CleanTarget(target));
  EXPECT_EQ(1, cleaner.cleaned_files_count());
  EXPECT_EQ(0u, fs_.files_.count("out1"));
  // out2 should remain
  EXPECT_EQ(1u, fs_.files_.count("out2"));
}

TEST_F(CleanerTest_161, CleanTargetByName_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"));

  fs_.Create("in1");
  fs_.Create("out1");

  Cleaner cleaner(&state_, config_, &fs_);
  EXPECT_EQ(0, cleaner.CleanTarget("out1"));
  EXPECT_EQ(1, cleaner.cleaned_files_count());
  EXPECT_EQ(0u, fs_.files_.count("out1"));
}

TEST_F(CleanerTest_161, CleanTargetNonExistent_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"));

  Cleaner cleaner(&state_, config_, &fs_);
  // Target doesn't exist in the graph
  EXPECT_NE(0, cleaner.CleanTarget("nonexistent"));
}

TEST_F(CleanerTest_161, CleanRuleByPointer_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "rule link\n"
    "  command = link $in -o $out\n"
    "build out1.o: cc in1.cc\n"
    "build out2.o: cc in2.cc\n"
    "build out3: link out1.o out2.o\n"));

  fs_.Create("in1.cc");
  fs_.Create("in2.cc");
  fs_.Create("out1.o");
  fs_.Create("out2.o");
  fs_.Create("out3");

  Cleaner cleaner(&state_, config_, &fs_);
  const Rule* rule = state_.bindings_.LookupRule("cc");
  ASSERT_NE(nullptr, rule);
  EXPECT_EQ(0, cleaner.CleanRule(rule));
  EXPECT_EQ(2, cleaner.cleaned_files_count());
  EXPECT_EQ(0u, fs_.files_.count("out1.o"));
  EXPECT_EQ(0u, fs_.files_.count("out2.o"));
  // out3 is from link rule, should remain
  EXPECT_EQ(1u, fs_.files_.count("out3"));
}

TEST_F(CleanerTest_161, CleanRuleByName_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1.o: cc in1.cc\n"));

  fs_.Create("in1.cc");
  fs_.Create("out1.o");

  Cleaner cleaner(&state_, config_, &fs_);
  EXPECT_EQ(0, cleaner.CleanRule("cc"));
  EXPECT_EQ(1, cleaner.cleaned_files_count());
  EXPECT_EQ(0u, fs_.files_.count("out1.o"));
}

TEST_F(CleanerTest_161, CleanRuleNonExistent_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1.o: cc in1.cc\n"));

  Cleaner cleaner(&state_, config_, &fs_);
  EXPECT_NE(0, cleaner.CleanRule("nonexistent_rule"));
}

TEST_F(CleanerTest_161, CleanTargets_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"
    "build out2: cc in2\n"));

  fs_.Create("in1");
  fs_.Create("in2");
  fs_.Create("out1");
  fs_.Create("out2");

  Cleaner cleaner(&state_, config_, &fs_);
  char target1[] = "out1";
  char target2[] = "out2";
  char* targets[] = { target1, target2 };
  EXPECT_EQ(0, cleaner.CleanTargets(2, targets));
  EXPECT_EQ(2, cleaner.cleaned_files_count());
}

TEST_F(CleanerTest_161, CleanRules_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "rule link\n"
    "  command = link $in -o $out\n"
    "build out1.o: cc in1.cc\n"
    "build out2: link out1.o\n"));

  fs_.Create("in1.cc");
  fs_.Create("out1.o");
  fs_.Create("out2");

  Cleaner cleaner(&state_, config_, &fs_);
  char rule1[] = "cc";
  char rule2[] = "link";
  char* rules[] = { rule1, rule2 };
  EXPECT_EQ(0, cleaner.CleanRules(2, rules));
  EXPECT_EQ(2, cleaner.cleaned_files_count());
}

TEST_F(CleanerTest_161, CleanDead_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"));

  fs_.Create("in1");
  fs_.Create("out1");
  fs_.Create("out_dead");

  BuildLog log;
  BuildLog::Entries entries;
  // Add a "dead" entry that is not in the current build graph
  BuildLog::LogEntry* entry = new BuildLog::LogEntry("out_dead");
  entry->start_time = 0;
  entry->end_time = 1;
  entry->mtime = 1;
  entries["out_dead"] = entry;
  // Also add a live entry
  BuildLog::LogEntry* live_entry = new BuildLog::LogEntry("out1");
  live_entry->start_time = 0;
  live_entry->end_time = 1;
  live_entry->mtime = 1;
  entries["out1"] = live_entry;

  Cleaner cleaner(&state_, config_, &fs_);
  cleaner.CleanDead(entries);
  // out_dead should be cleaned (it's not in the build graph)
  EXPECT_EQ(1, cleaner.cleaned_files_count());
  EXPECT_EQ(0u, fs_.files_.count("out_dead"));
  // out1 should remain (it's a valid target)
  EXPECT_EQ(1u, fs_.files_.count("out1"));

  delete entry;
  delete live_entry;
}

TEST_F(CleanerTest_161, CleanAllGeneratorFlag_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule gen\n"
    "  command = gen $in -o $out\n"
    "  generator = 1\n"
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build gen_out: gen in1\n"
    "build out1: cc in2\n"));

  fs_.Create("in1");
  fs_.Create("in2");
  fs_.Create("gen_out");
  fs_.Create("out1");

  // CleanAll with generator=false should NOT clean generator outputs
  {
    Cleaner cleaner(&state_, config_, &fs_);
    EXPECT_EQ(0, cleaner.CleanAll(false));
    EXPECT_EQ(1, cleaner.cleaned_files_count());
    EXPECT_EQ(1u, fs_.files_.count("gen_out"));
    EXPECT_EQ(0u, fs_.files_.count("out1"));
  }

  // Restore out1
  fs_.Create("out1");

  // CleanAll with generator=true should also clean generator outputs
  {
    Cleaner cleaner(&state_, config_, &fs_);
    EXPECT_EQ(0, cleaner.CleanAll(true));
    EXPECT_EQ(2, cleaner.cleaned_files_count());
    EXPECT_EQ(0u, fs_.files_.count("gen_out"));
    EXPECT_EQ(0u, fs_.files_.count("out1"));
  }
}

TEST_F(CleanerTest_161, CleanedFilesCountInitiallyZero_161) {
  Cleaner cleaner(&state_, config_, &fs_);
  EXPECT_EQ(0, cleaner.cleaned_files_count());
}

TEST_F(CleanerTest_161, CleanTargetWithDeps_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "rule link\n"
    "  command = link $in -o $out\n"
    "build mid.o: cc in1\n"
    "build out: link mid.o\n"));

  fs_.Create("in1");
  fs_.Create("mid.o");
  fs_.Create("out");

  Cleaner cleaner(&state_, config_, &fs_);
  Node* target = state_.LookupNode("out");
  ASSERT_NE(nullptr, target);
  EXPECT_EQ(0, cleaner.CleanTarget(target));
  // Should clean out and its dependency mid.o
  EXPECT_EQ(2, cleaner.cleaned_files_count());
  EXPECT_EQ(0u, fs_.files_.count("out"));
  EXPECT_EQ(0u, fs_.files_.count("mid.o"));
}

TEST_F(CleanerTest_161, CleanFileAlreadyMissing_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"));

  fs_.Create("in1");
  // Don't create out1 - it doesn't exist on disk

  Cleaner cleaner(&state_, config_, &fs_);
  EXPECT_EQ(0, cleaner.CleanTarget("out1"));
  EXPECT_EQ(0, cleaner.cleaned_files_count());
}

TEST_F(CleanerTest_161, VerboseMode_161) {
  config_.verbosity = BuildConfig::NORMAL;
  {
    Cleaner cleaner(&state_, config_, &fs_);
    // In normal mode, IsVerbose should return false
    EXPECT_FALSE(cleaner.IsVerbose());
  }

  config_.verbosity = BuildConfig::VERBOSE;
  {
    Cleaner cleaner(&state_, config_, &fs_);
    EXPECT_TRUE(cleaner.IsVerbose());
  }
}

TEST_F(CleanerTest_161, CleanTargetsWithInvalidTarget_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"));

  Cleaner cleaner(&state_, config_, &fs_);
  char target1[] = "nonexistent";
  char* targets[] = { target1 };
  EXPECT_NE(0, cleaner.CleanTargets(1, targets));
}

TEST_F(CleanerTest_161, CleanRulesWithInvalidRule_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"));

  Cleaner cleaner(&state_, config_, &fs_);
  char rule1[] = "nonexistent_rule";
  char* rules[] = { rule1 };
  EXPECT_NE(0, cleaner.CleanRules(1, rules));
}

TEST_F(CleanerTest_161, CleanAllEmptyBuildGraph_161) {
  // No rules or edges at all
  Cleaner cleaner(&state_, config_, &fs_);
  EXPECT_EQ(0, cleaner.CleanAll(false));
  EXPECT_EQ(0, cleaner.cleaned_files_count());
}

TEST_F(CleanerTest_161, CleanDeadEmptyEntries_161) {
  ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
    "rule cc\n"
    "  command = cc $in -o $out\n"
    "build out1: cc in1\n"));

  BuildLog::Entries entries;
  Cleaner cleaner(&state_, config_, &fs_);
  cleaner.CleanDead(entries);
  EXPECT_EQ(0, cleaner.cleaned_files_count());
}

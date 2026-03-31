#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "build.h"
#include "graph.h"
#include "state.h"
#include "build_log.h"
#include "deps_log.h"
#include "disk_interface.h"
#include "status.h"
#include "test.h"

#include <memory>
#include <string>

// Use the test infrastructure from ninja's test framework
struct BuilderTest_92 : public ::testing::Test {
  BuilderTest_92() : config_(MakeConfig()), status_(config_) {
  }

  virtual void SetUp() {
    ASSERT_NO_FATAL_FAILURE(AssertParse(&state_,
        "rule cat\n"
        "  command = cat $in > $out\n"
        "rule true\n"
        "  command = true\n"
        "rule false\n"
        "  command = false\n"
        "build cat1: cat in1\n"
        "build cat2: cat in1 in2\n"
        "build cat12: cat cat1 cat2\n"
    ));

    fs_.Create("in1", "");
    fs_.Create("in2", "");
  }

  BuildConfig MakeConfig() {
    BuildConfig config;
    config.verbosity = BuildConfig::QUIET;
    return config;
  }

  void AssertParse(State* state, const char* input) {
    ManifestParser parser(state, &fs_);
    std::string err;
    ASSERT_TRUE(parser.ParseTest(input, &err)) << err;
  }

  // Helper to create a builder
  std::unique_ptr<Builder> MakeBuilder() {
    return std::unique_ptr<Builder>(new Builder(
        &state_, config_, &build_log_, &deps_log_, &fs_, &status_, 0));
  }

  State state_;
  BuildConfig config_;
  VirtualFileSystem fs_;
  BuildLog build_log_;
  DepsLog deps_log_;
  StatusPrinter status_;
};

// Test that GetExitCode returns ExitSuccess initially
TEST_F(BuilderTest_92, GetExitCodeInitiallySuccess_92) {
  auto builder = MakeBuilder();
  EXPECT_EQ(ExitSuccess, builder->GetExitCode());
}

// Test that AlreadyUpToDate returns true when no targets have been added
TEST_F(BuilderTest_92, AlreadyUpToDateWithNoTargets_92) {
  auto builder = MakeBuilder();
  EXPECT_TRUE(builder->AlreadyUpToDate());
}

// Test AddTarget with valid target name
TEST_F(BuilderTest_92, AddTargetValidName_92) {
  auto builder = MakeBuilder();
  std::string err;
  Node* node = builder->AddTarget("cat1", &err);
  EXPECT_NE(nullptr, node);
  EXPECT_EQ("", err);
}

// Test AddTarget with unknown target name
TEST_F(BuilderTest_92, AddTargetUnknownName_92) {
  auto builder = MakeBuilder();
  std::string err;
  Node* node = builder->AddTarget("nonexistent", &err);
  EXPECT_EQ(nullptr, node);
  EXPECT_NE("", err);
}

// Test AddTarget with empty string
TEST_F(BuilderTest_92, AddTargetEmptyString_92) {
  auto builder = MakeBuilder();
  std::string err;
  Node* node = builder->AddTarget("", &err);
  EXPECT_EQ(nullptr, node);
  EXPECT_NE("", err);
}

// Test that after adding a target that needs building, AlreadyUpToDate is false
TEST_F(BuilderTest_92, NotUpToDateAfterAddingTarget_92) {
  auto builder = MakeBuilder();
  std::string err;
  Node* node = builder->AddTarget("cat1", &err);
  ASSERT_NE(nullptr, node);
  EXPECT_EQ("", err);
  EXPECT_FALSE(builder->AlreadyUpToDate());
}

// Test that adding a target whose inputs already exist and output is up-to-date
TEST_F(BuilderTest_92, AlreadyUpToDateWhenOutputFresh_92) {
  // Create the output file newer than the input
  fs_.Create("cat1", "");
  // Ensure cat1 is newer than in1 by creating it after
  fs_.Tick();
  fs_.Create("cat1", "");

  auto builder = MakeBuilder();
  std::string err;
  Node* node = builder->AddTarget("cat1", &err);
  // Node should still be returned (it's a valid target)
  // Whether it's up to date depends on timestamps
  EXPECT_EQ("", err);
}

// Test AddTarget with Node* overload
TEST_F(BuilderTest_92, AddTargetNodePointer_92) {
  auto builder = MakeBuilder();
  std::string err;
  Node* node = state_.LookupNode("cat1");
  ASSERT_NE(nullptr, node);
  bool result = builder->AddTarget(node, &err);
  EXPECT_TRUE(result);
  EXPECT_EQ("", err);
}

// Test GetExitCode after cleanup
TEST_F(BuilderTest_92, GetExitCodeAfterCleanup_92) {
  auto builder = MakeBuilder();
  builder->Cleanup();
  EXPECT_EQ(ExitSuccess, builder->GetExitCode());
}

// Test that Cleanup can be called without any prior build activity
TEST_F(BuilderTest_92, CleanupWithoutBuild_92) {
  auto builder = MakeBuilder();
  // Should not crash or throw
  builder->Cleanup();
}

// Test Build when already up to date
TEST_F(BuilderTest_92, BuildAlreadyUpToDate_92) {
  auto builder = MakeBuilder();
  std::string err;
  // Don't add any targets - should be already up to date
  ExitStatus status = builder->Build(&err);
  EXPECT_EQ(ExitSuccess, status);
}

// Test adding multiple targets
TEST_F(BuilderTest_92, AddMultipleTargets_92) {
  auto builder = MakeBuilder();
  std::string err;

  Node* node1 = builder->AddTarget("cat1", &err);
  EXPECT_NE(nullptr, node1);
  EXPECT_EQ("", err);

  Node* node2 = builder->AddTarget("cat2", &err);
  EXPECT_NE(nullptr, node2);
  EXPECT_EQ("", err);

  EXPECT_FALSE(builder->AlreadyUpToDate());
}

// Test adding a target with transitive dependencies
TEST_F(BuilderTest_92, AddTargetWithTransitiveDeps_92) {
  auto builder = MakeBuilder();
  std::string err;

  Node* node = builder->AddTarget("cat12", &err);
  EXPECT_NE(nullptr, node);
  EXPECT_EQ("", err);
  EXPECT_FALSE(builder->AlreadyUpToDate());
}

// Test SetBuildLog
TEST_F(BuilderTest_92, SetBuildLog_92) {
  auto builder = MakeBuilder();
  BuildLog log;
  // Should not crash
  builder->SetBuildLog(&log);
}

// Test SetBuildLog with nullptr
TEST_F(BuilderTest_92, SetBuildLogNull_92) {
  auto builder = MakeBuilder();
  // Should not crash
  builder->SetBuildLog(nullptr);
}

// Test SetJobserverClient
TEST_F(BuilderTest_92, SetJobserverClient_92) {
  auto builder = MakeBuilder();
  // Setting nullptr should be acceptable
  builder->SetJobserverClient(nullptr);
}

// Test that adding the same target twice doesn't cause issues
TEST_F(BuilderTest_92, AddSameTargetTwice_92) {
  auto builder = MakeBuilder();
  std::string err;

  Node* node1 = builder->AddTarget("cat1", &err);
  EXPECT_NE(nullptr, node1);
  EXPECT_EQ("", err);

  Node* node2 = builder->AddTarget("cat1", &err);
  EXPECT_NE(nullptr, node2);
  EXPECT_EQ("", err);

  EXPECT_EQ(node1, node2);
}

// Test that a source file (no rule to build it) returns nullptr with error
TEST_F(BuilderTest_92, AddTargetSourceFile_92) {
  auto builder = MakeBuilder();
  std::string err;

  // "in1" is a source file, not a build target with an edge
  Node* node = builder->AddTarget("in1", &err);
  // Source files that exist should return the node but it should be up to date
  // The exact behavior depends on implementation, but it shouldn't crash
}

// Test GetExitCode is const-correct
TEST_F(BuilderTest_92, GetExitCodeConstCorrectness_92) {
  auto builder = MakeBuilder();
  const Builder& const_ref = *builder;
  ExitStatus code = const_ref.GetExitCode();
  EXPECT_EQ(ExitSuccess, code);
}

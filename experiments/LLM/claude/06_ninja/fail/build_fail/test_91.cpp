#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "build.h"
#include "build_log.h"
#include "graph.h"
#include "state.h"
#include "disk_interface.h"
#include "status.h"
#include "deps_log.h"

#include <memory>
#include <string>

// A minimal mock/fake for StatusPrinter or Status interface
// We need a Status implementation for the Builder constructor.
struct MockStatus : public Status {
  void PlanHasTotalEdges(int total) override {}
  void BuildEdgeStarted(const Edge* edge, int start_time, int end_time) override {}
  void BuildEdgeFinished(Edge* edge, int end_time, bool success,
                         const std::string& output) override {}
  void BuildLoadDyndeps() override {}
  void BuildStarted() override {}
  void BuildFinished() override {}
  void Info(const char* msg, ...) override {}
  void Warning(const char* msg, ...) override {}
  void Error(const char* msg, ...) override {}
};

class BuilderSetBuildLogTest_91 : public ::testing::Test {
 protected:
  void SetUp() override {
    status_ = std::make_unique<MockStatus>();
    disk_interface_ = std::make_unique<RealDiskInterface>();
    
    config_.verbosity = BuildConfig::NORMAL;
    
    builder_ = std::make_unique<Builder>(
        &state_, config_, &build_log_, &deps_log_,
        disk_interface_.get(), status_.get(), 0);
  }

  State state_;
  BuildConfig config_;
  BuildLog build_log_;
  DepsLog deps_log_;
  std::unique_ptr<RealDiskInterface> disk_interface_;
  std::unique_ptr<MockStatus> status_;
  std::unique_ptr<Builder> builder_;
};

// Test that SetBuildLog can be called with a valid BuildLog pointer
TEST_F(BuilderSetBuildLogTest_91, SetBuildLogWithValidPointer_91) {
  BuildLog new_log;
  // Should not crash or throw
  builder_->SetBuildLog(&new_log);
}

// Test that SetBuildLog can be called with nullptr
TEST_F(BuilderSetBuildLogTest_91, SetBuildLogWithNullptr_91) {
  // Should not crash or throw when setting nullptr
  builder_->SetBuildLog(nullptr);
}

// Test that SetBuildLog can be called multiple times
TEST_F(BuilderSetBuildLogTest_91, SetBuildLogMultipleTimes_91) {
  BuildLog log1;
  BuildLog log2;
  BuildLog log3;
  
  builder_->SetBuildLog(&log1);
  builder_->SetBuildLog(&log2);
  builder_->SetBuildLog(&log3);
  // No crash expected
}

// Test that SetBuildLog can switch from a valid log to nullptr and back
TEST_F(BuilderSetBuildLogTest_91, SetBuildLogSwitchBetweenValidAndNull_91) {
  BuildLog new_log;
  
  builder_->SetBuildLog(&new_log);
  builder_->SetBuildLog(nullptr);
  builder_->SetBuildLog(&new_log);
  // No crash expected
}

// Test that after construction, AlreadyUpToDate returns true when no targets added
TEST_F(BuilderSetBuildLogTest_91, AlreadyUpToDateWithNoTargets_91) {
  EXPECT_TRUE(builder_->AlreadyUpToDate());
}

// Test that SetBuildLog can be called with the same log that was passed at construction
TEST_F(BuilderSetBuildLogTest_91, SetBuildLogWithSameLogAsConstructor_91) {
  builder_->SetBuildLog(&build_log_);
  // Should not crash; effectively a no-op replacement with same pointer
}

// Test that AddTarget with non-existent target returns nullptr and sets error
TEST_F(BuilderSetBuildLogTest_91, AddTargetNonExistent_91) {
  std::string err;
  Node* node = builder_->AddTarget("nonexistent_target", &err);
  EXPECT_EQ(nullptr, node);
  EXPECT_FALSE(err.empty());
}

// Test GetExitCode returns success initially
TEST_F(BuilderSetBuildLogTest_91, GetExitCodeInitiallySuccess_91) {
  EXPECT_EQ(ExitSuccess, builder_->GetExitCode());
}

// Test that SetBuildLog followed by AlreadyUpToDate still works
TEST_F(BuilderSetBuildLogTest_91, SetBuildLogThenAlreadyUpToDate_91) {
  BuildLog new_log;
  builder_->SetBuildLog(&new_log);
  EXPECT_TRUE(builder_->AlreadyUpToDate());
}

// Test Cleanup can be called without issues after SetBuildLog
TEST_F(BuilderSetBuildLogTest_91, CleanupAfterSetBuildLog_91) {
  BuildLog new_log;
  builder_->SetBuildLog(&new_log);
  builder_->Cleanup();
  // No crash expected
}

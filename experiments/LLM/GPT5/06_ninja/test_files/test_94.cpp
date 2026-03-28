// File: real_command_runner_clear_job_tokens_test.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "build.h"               // For BuildConfig
#include "real_command_runner.h" // For RealCommandRunner
#include "jobserver.h"           // For Jobserver::Client, Jobserver::Slot
#include "graph.h"               // For Edge

using ::testing::_;
using ::testing::Times;

// Mock for Jobserver::Client
class MockJobserverClient_94 : public Jobserver::Client {
public:
  MOCK_METHOD(Jobserver::Slot, TryAcquire, (), (override));
  MOCK_METHOD(void, Release, (Jobserver::Slot slot), (override));
};

// Testable subclass that lets us control GetActiveEdges()
class TestableRealCommandRunner_94 : public RealCommandRunner {
public:
  TestableRealCommandRunner_94(const BuildConfig& config,
                               Jobserver::Client* jobserver)
      : RealCommandRunner(config, jobserver) {}

  void SetActiveEdges(const std::vector<Edge*>& edges) {
    active_edges_ = edges;
  }

  std::vector<Edge*> GetActiveEdges() override {
    return active_edges_;
  }

private:
  std::vector<Edge*> active_edges_;
};

// Subclass used to verify that GetActiveEdges is *not* called
// when jobserver_ is nullptr.
class NoActiveEdgesCallRunner_94 : public RealCommandRunner {
public:
  NoActiveEdgesCallRunner_94(const BuildConfig& config)
      : RealCommandRunner(config, /*jobserver=*/nullptr) {}

  std::vector<Edge*> GetActiveEdges() override {
    ADD_FAILURE() << "GetActiveEdges should not be called when jobserver_ is null.";
    return {};
  }
};

class RealCommandRunnerTest_94 : public ::testing::Test {
protected:
  BuildConfig config_; // Default configuration; details are irrelevant for ClearJobTokens
};

// Normal operation: jobserver_ is set and there are multiple active edges.
// Expect: Release is called once for each active edge.
TEST_F(RealCommandRunnerTest_94, ReleasesTokensForAllActiveEdges_94) {
  MockJobserverClient_94 jobserver;

  TestableRealCommandRunner_94 runner(config_, &jobserver);

  Edge edge1;
  Edge edge2;

  // We don't rely on specific Slot values; just ensure Release is called.
  Jobserver::Slot slot1{};
  Jobserver::Slot slot2{};
  edge1.job_slot_ = slot1;
  edge2.job_slot_ = slot2;

  std::vector<Edge*> active_edges{&edge1, &edge2};
  runner.SetActiveEdges(active_edges);

  EXPECT_CALL(jobserver, Release(_)).Times(2);

  runner.ClearJobTokens();
}

// Boundary condition: jobserver_ is set, but there are no active edges.
// Expect: Release is never called.
TEST_F(RealCommandRunnerTest_94, NoActiveEdgesDoesNotCallRelease_94) {
  MockJobserverClient_94 jobserver;

  TestableRealCommandRunner_94 runner(config_, &jobserver);

  std::vector<Edge*> empty_edges;
  runner.SetActiveEdges(empty_edges);

  EXPECT_CALL(jobserver, Release(_)).Times(0);

  runner.ClearJobTokens();
}

// Error/edge case: jobserver_ is nullptr.
// Observable behavior: ClearJobTokens should not attempt to access active edges
// or call Release, and must not crash.
TEST_F(RealCommandRunnerTest_94, NullJobserverSkipsClearingTokens_94) {
  NoActiveEdgesCallRunner_94 runner(config_);

  // If ClearJobTokens incorrectly calls GetActiveEdges(),
  // NoActiveEdgesCallRunner_94::GetActiveEdges will ADD_FAILURE().
  // If it behaves correctly, this test will simply pass.
  EXPECT_NO_FATAL_FAILURE(runner.ClearJobTokens());
}

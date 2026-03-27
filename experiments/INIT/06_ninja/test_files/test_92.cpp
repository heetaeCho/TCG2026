// File: build_get_exit_code_test_92.cc

#include "build.h"

#include "build_log.h"
#include "deps_log.h"
#include "exit_status.h"
#include "graph.h"
#include "test.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

/// Simple fake CommandRunner used only for testing Builder's interaction.
/// It simulates a single in-flight command and lets the test control the
/// resulting ExitStatus.
struct FakeCommandRunner_92 : public CommandRunner {
  explicit FakeCommandRunner_92(VirtualFileSystem* fs)
      : last_edge_(nullptr), fs_(fs), next_status_(ExitSuccess) {}

  void SetNextStatus(ExitStatus status) { next_status_ = status; }

  size_t commands_started() const { return started_edges_.size(); }

  // CommandRunner interface
  bool CanRunMore() override {
    // Allow only one active command at a time.
    return last_edge_ == nullptr;
  }

  bool StartCommand(Edge* edge) override {
    last_edge_ = edge;
    started_edges_.push_back(edge);

    // Simulate that outputs are created on disk.
    for (vector<Node*>::iterator it = edge->outputs_.begin();
         it != edge->outputs_.end(); ++it) {
      fs_->Create((*it)->path(), "");
    }

    return true;
  }

  bool WaitForCommand(Result* result) override {
    if (!last_edge_)
      return false;

    result->edge = last_edge_;
    result->status = next_status_;
    last_edge_ = nullptr;
    return true;
  }

  vector<Edge*> GetActiveEdges() override {
    vector<Edge*> edges;
    if (last_edge_)
      edges.push_back(last_edge_);
    return edges;
  }

  void Abort() override { last_edge_ = nullptr; }

 private:
  Edge* last_edge_;
  VirtualFileSystem* fs_;
  ExitStatus next_status_;
  vector<Edge*> started_edges_;
};

/// Fixture for testing Builder::GetExitCode with a minimal build graph.
struct BuilderGetExitCodeTest_92 : public StateTestWithBuiltinRules {
  BuilderGetExitCodeTest_92()
      : config_(MakeConfig()),
        fs_(),
        fake_runner_(&fs_),
        status_(config_),
        builder_(&state_,
                 config_,
                 /*build_log=*/nullptr,
                 /*deps_log=*/nullptr,
                 &fs_,
                 &status_,
                 /*start_time_millis=*/0) {}

  ~BuilderGetExitCodeTest_92() override {
    // command_runner_ owns a pointer we gave it from the stack; release it
    // so it is not deleted.
    builder_.command_runner_.release();
  }

  void SetUp() override {
    StateTestWithBuiltinRules::SetUp();

    // Use our fake command runner for all commands started by Builder.
    builder_.command_runner_.reset(&fake_runner_);

    // Simple one-edge manifest: build "out" from "in" using builtin "cat" rule.
    AssertParse(&state_, "build out: cat in\n");

    // Ensure input exists and target is dirty so there is work to do.
    fs_.Create("in", "");
    GetNode("out")->MarkDirty();
  }

  BuildConfig MakeConfig() {
    BuildConfig c;
    c.verbosity = BuildConfig::QUIET;
    return c;
  }

  BuildConfig config_;
  VirtualFileSystem fs_;
  FakeCommandRunner_92 fake_runner_;
  BuildStatus status_;
  Builder builder_;
};

// Normal operation: immediately after construction / setup, exit code should
// indicate success.
TEST_F(BuilderGetExitCodeTest_92, DefaultExitCodeIsSuccess_92) {
  EXPECT_EQ(ExitSuccess, builder_.GetExitCode());
}

// Normal operation: a successful build should return ExitSuccess and
// GetExitCode() should reflect the same value.
TEST_F(BuilderGetExitCodeTest_92, BuildSuccessReflectsExitCode_92) {
  string err;
  fake_runner_.SetNextStatus(ExitSuccess);

  // Add the single target and build it.
  EXPECT_TRUE(builder_.AddTarget("out", &err));
  ASSERT_EQ("", err);

  ExitStatus build_status = builder_.Build(&err);

  EXPECT_EQ(ExitSuccess, build_status);
  EXPECT_EQ("", err);
  EXPECT_EQ(ExitSuccess, builder_.GetExitCode());
}

// Error case: when a command fails (ExitFailure), Build should return
// ExitFailure and GetExitCode() should match it.
TEST_F(BuilderGetExitCodeTest_92, BuildFailureSetsExitCodeFailure_92) {
  string err;
  fake_runner_.SetNextStatus(ExitFailure);

  EXPECT_TRUE(builder_.AddTarget("out", &err));
  ASSERT_EQ("", err);

  ExitStatus build_status = builder_.Build(&err);

  EXPECT_EQ(ExitFailure, build_status);
  // We don't assume a specific error message, only that the exit code is set.
  EXPECT_EQ(build_status, builder_.GetExitCode());
}

// Error/boundary case: an interrupted build should set the exit code to
// ExitInterrupted and keep it observable via GetExitCode().
TEST_F(BuilderGetExitCodeTest_92, InterruptedBuildSetsExitCodeInterrupted_92) {
  string err;
  fake_runner_.SetNextStatus(ExitInterrupted);

  EXPECT_TRUE(builder_.AddTarget("out", &err));
  ASSERT_EQ("", err);

  ExitStatus build_status = builder_.Build(&err);

  EXPECT_EQ(ExitInterrupted, build_status);
  EXPECT_EQ(build_status, builder_.GetExitCode());
}

// Boundary/consistency: GetExitCode() should be stable across multiple calls
// and should not change observable state.
TEST_F(BuilderGetExitCodeTest_92, GetExitCodeIsIdempotent_92) {
  // Force a failure once to move Builder into a non-default state.
  string err;
  fake_runner_.SetNextStatus(ExitFailure);

  EXPECT_TRUE(builder_.AddTarget("out", &err));
  ASSERT_EQ("", err);

  ExitStatus build_status = builder_.Build(&err);
  ASSERT_EQ(ExitFailure, build_status);

  ExitStatus first = builder_.GetExitCode();
  ExitStatus second = builder_.GetExitCode();

  EXPECT_EQ(first, second);
  EXPECT_EQ(build_status, first);
}

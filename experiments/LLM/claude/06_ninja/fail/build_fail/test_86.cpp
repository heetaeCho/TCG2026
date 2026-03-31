#include "gtest/gtest.h"
#include "build.h"
#include "graph.h"
#include "state.h"
#include "build_log.h"
#include "deps_log.h"
#include "disk_interface.h"
#include "status.h"
#include "util.h"

#include <string>

// Minimal status handler for Builder
struct TestStatus : public Status {
  void PlanHasTotalEdges(int total) override {}
  void BuildEdgeStarted(const Edge* edge, int start_time_millis) override {}
  void BuildEdgeFinished(Edge* edge, int end_time_millis, bool success,
                         const std::string& output) override {}
  void BuildLoadDyndeps() override {}
  void BuildStarted() override {}
  void BuildFinished() override {}
  void Info(const char* msg, ...) override {}
  void Warning(const char* msg, ...) override {}
  void Error(const char* msg, ...) override {}
};

struct VirtualFileSystem : public DiskInterface {
  TimeStamp Stat(const std::string& path, std::string* err) const override {
    auto it = files_.find(path);
    if (it != files_.end())
      return it->second;
    return 0;
  }
  bool WriteFile(const std::string& path, const std::string& contents) override {
    return true;
  }
  bool MakeDir(const std::string& path) override { return true; }
  Status ReadFile(const std::string& path, std::string* contents,
                  std::string* err) override {
    return NotFound;
  }
  int RemoveFile(const std::string& path) override { return 0; }
  
  void Create(const std::string& path, TimeStamp mtime) {
    files_[path] = mtime;
  }
  
  std::map<std::string, TimeStamp> files_;
};

class PlanTest_86 : public ::testing::Test {
protected:
  void SetUp() override {
    status_.reset(new TestStatus);
  }
  
  // Helper to build a simple graph: input -> edge -> output
  void AddSimpleRule() {
    // Add a rule
    rule_ = new Rule("cat");
    rule_->AddBinding("command", "cat $in > $out");
    state_.bindings_.AddRule(rule_);
  }
  
  Edge* AddEdge(const std::string& rule_name) {
    return state_.AddEdge(state_.bindings_.LookupRule(rule_name));
  }

  State state_;
  VirtualFileSystem fs_;
  std::unique_ptr<TestStatus> status_;
  Rule* rule_ = nullptr;
};

TEST_F(PlanTest_86, InitialState_MoreToDoIsFalse_86) {
  // A fresh Plan with no targets should have nothing to do
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  EXPECT_FALSE(plan.more_to_do());
}

TEST_F(PlanTest_86, MoreToDoAfterAddTarget_86) {
  AddSimpleRule();
  
  // Create edge: in.txt -> out.txt
  Node* in = state_.GetNode("in.txt", 0);
  Node* out = state_.GetNode("out.txt", 0);
  Edge* edge = AddEdge("cat");
  edge->inputs_.push_back(in);
  edge->outputs_.push_back(out);
  in->AddOutEdge(edge);
  out->set_in_edge(edge);
  
  // Make input exist but output doesn't, so edge is dirty
  fs_.Create("in.txt", 2);
  // out.txt doesn't exist => mtime 0 => dirty
  
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  
  std::string err;
  EXPECT_TRUE(plan.AddTarget(out, &err));
  EXPECT_EQ("", err);
  
  // After adding a target that needs building, more_to_do should be true
  EXPECT_TRUE(plan.more_to_do());
}

TEST_F(PlanTest_86, CommandEdgeCountInitiallyZero_86) {
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  EXPECT_EQ(0, plan.command_edge_count());
}

TEST_F(PlanTest_86, MoreToDoFalseAfterReset_86) {
  AddSimpleRule();
  
  Node* in = state_.GetNode("in.txt", 0);
  Node* out = state_.GetNode("out.txt", 0);
  Edge* edge = AddEdge("cat");
  edge->inputs_.push_back(in);
  edge->outputs_.push_back(out);
  in->AddOutEdge(edge);
  out->set_in_edge(edge);
  
  fs_.Create("in.txt", 2);
  
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  
  std::string err;
  EXPECT_TRUE(plan.AddTarget(out, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(plan.more_to_do());
  
  plan.Reset();
  EXPECT_FALSE(plan.more_to_do());
}

TEST_F(PlanTest_86, FindWorkReturnsEdgeWhenReady_86) {
  AddSimpleRule();
  
  Node* in = state_.GetNode("in.txt", 0);
  Node* out = state_.GetNode("out.txt", 0);
  Edge* edge = AddEdge("cat");
  edge->inputs_.push_back(in);
  edge->outputs_.push_back(out);
  in->AddOutEdge(edge);
  out->set_in_edge(edge);
  
  fs_.Create("in.txt", 2);
  
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  
  std::string err;
  EXPECT_TRUE(plan.AddTarget(out, &err));
  EXPECT_EQ("", err);
  
  plan.PrepareQueue();
  
  Edge* found = plan.FindWork();
  EXPECT_NE(nullptr, found);
  EXPECT_EQ(edge, found);
  
  // After finding the work but before finishing, more_to_do should still be true
  EXPECT_TRUE(plan.more_to_do());
}

TEST_F(PlanTest_86, MoreToDoFalseAfterEdgeFinished_86) {
  AddSimpleRule();
  
  Node* in = state_.GetNode("in.txt", 0);
  Node* out = state_.GetNode("out.txt", 0);
  Edge* edge = AddEdge("cat");
  edge->inputs_.push_back(in);
  edge->outputs_.push_back(out);
  in->AddOutEdge(edge);
  out->set_in_edge(edge);
  
  fs_.Create("in.txt", 2);
  
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  
  std::string err;
  EXPECT_TRUE(plan.AddTarget(out, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(plan.more_to_do());
  
  plan.PrepareQueue();
  
  Edge* found = plan.FindWork();
  ASSERT_NE(nullptr, found);
  
  // Finish the edge successfully
  EXPECT_TRUE(plan.EdgeFinished(found, Plan::kEdgeSucceeded, &err));
  EXPECT_EQ("", err);
  
  // After finishing all edges, more_to_do should be false
  EXPECT_FALSE(plan.more_to_do());
}

TEST_F(PlanTest_86, NoWorkWhenTargetUpToDate_86) {
  AddSimpleRule();
  
  Node* in = state_.GetNode("in.txt", 0);
  Node* out = state_.GetNode("out.txt", 0);
  Edge* edge = AddEdge("cat");
  edge->inputs_.push_back(in);
  edge->outputs_.push_back(out);
  in->AddOutEdge(edge);
  out->set_in_edge(edge);
  
  // Both exist, output newer than input => up to date
  fs_.Create("in.txt", 1);
  fs_.Create("out.txt", 2);
  
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  
  std::string err;
  EXPECT_TRUE(plan.AddTarget(out, &err));
  
  // When target is up to date, no work needed
  EXPECT_FALSE(plan.more_to_do());
}

TEST_F(PlanTest_86, EdgeFinishedWithFailure_86) {
  AddSimpleRule();
  
  Node* in = state_.GetNode("in.txt", 0);
  Node* out = state_.GetNode("out.txt", 0);
  Edge* edge = AddEdge("cat");
  edge->inputs_.push_back(in);
  edge->outputs_.push_back(out);
  in->AddOutEdge(edge);
  out->set_in_edge(edge);
  
  fs_.Create("in.txt", 2);
  
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  
  std::string err;
  EXPECT_TRUE(plan.AddTarget(out, &err));
  EXPECT_TRUE(plan.more_to_do());
  
  plan.PrepareQueue();
  
  Edge* found = plan.FindWork();
  ASSERT_NE(nullptr, found);
  
  // Finish the edge with failure
  EXPECT_TRUE(plan.EdgeFinished(found, Plan::kEdgeFailed, &err));
  
  // After failure, should no longer have more to do
  EXPECT_FALSE(plan.more_to_do());
}

TEST_F(PlanTest_86, FindWorkReturnsNullWhenNothingReady_86) {
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  
  Edge* found = plan.FindWork();
  EXPECT_EQ(nullptr, found);
}

TEST_F(PlanTest_86, MultipleEdgesChained_86) {
  AddSimpleRule();
  
  // Chain: in.txt -> mid.txt -> out.txt
  Node* in = state_.GetNode("in.txt", 0);
  Node* mid = state_.GetNode("mid.txt", 0);
  Node* out = state_.GetNode("out.txt", 0);
  
  Edge* edge1 = AddEdge("cat");
  edge1->inputs_.push_back(in);
  edge1->outputs_.push_back(mid);
  in->AddOutEdge(edge1);
  mid->set_in_edge(edge1);
  
  Edge* edge2 = AddEdge("cat");
  edge2->inputs_.push_back(mid);
  edge2->outputs_.push_back(out);
  mid->AddOutEdge(edge2);
  out->set_in_edge(edge2);
  
  fs_.Create("in.txt", 2);
  
  BuildConfig config;
  Builder builder(&state_, config, nullptr, nullptr, &fs_, status_.get(), 0);
  Plan plan(&builder);
  
  std::string err;
  EXPECT_TRUE(plan.AddTarget(out, &err));
  EXPECT_EQ("", err);
  EXPECT_TRUE(plan.more_to_do());
  
  // Should have 2 command edges
  EXPECT_EQ(2, plan.command_edge_count());
  
  plan.PrepareQueue();
  
  // First, only edge1 should be ready (its input exists)
  Edge* work1 = plan.FindWork();
  ASSERT_NE(nullptr, work1);
  EXPECT_EQ(edge1, work1);
  
  // Still more to do
  EXPECT_TRUE(plan.more_to_do());
  
  // Finish edge1
  EXPECT_TRUE(plan.EdgeFinished(work1, Plan::kEdgeSucceeded, &err));
  EXPECT_TRUE(plan.more_to_do());
  
  // Now edge2 should be ready
  Edge* work2 = plan.FindWork();
  ASSERT_NE(nullptr, work2);
  EXPECT_EQ(edge2, work2);
  
  // Finish edge2
  EXPECT_TRUE(plan.EdgeFinished(work2, Plan::kEdgeSucceeded, &err));
  EXPECT_FALSE(plan.more_to_do());
}

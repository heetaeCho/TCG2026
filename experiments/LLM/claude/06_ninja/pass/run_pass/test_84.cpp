#include "gtest/gtest.h"

#include "deps_log.h"
#include "graph.h"
#include "state.h"
#include "util.h"

#include <string>
#include <vector>
#include <cstdio>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

namespace {

const char kTestFilename[] = "DepsLogTest_tempfile_84";

class DepsLogTest_84 : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Clean up any leftover files from previous test runs.
    unlink(kTestFilename);
  }

  virtual void TearDown() {
    unlink(kTestFilename);
  }

  State state_;
};

TEST_F(DepsLogTest_84, WriteAndReadBack_84) {
  // Write some deps entries, close, then read them back.
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));
    ASSERT_EQ("", err);

    Node* out = state_.GetNode("out.o", 0);
    std::vector<Node*> deps;
    deps.push_back(state_.GetNode("foo.h", 0));
    deps.push_back(state_.GetNode("bar.h", 0));
    ASSERT_TRUE(log.RecordDeps(out, 1, deps));

    log.Close();
  }

  {
    DepsLog log;
    std::string err;
    State state;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state, &err));
    ASSERT_EQ("", err);

    Node* out = state.GetNode("out.o", 0);
    DepsLog::Deps* loaded_deps = log.GetDeps(out);
    ASSERT_TRUE(loaded_deps != NULL);
    EXPECT_EQ(1, loaded_deps->mtime);
    EXPECT_EQ(2, loaded_deps->node_count);
    EXPECT_EQ("foo.h", loaded_deps->nodes[0]->path());
    EXPECT_EQ("bar.h", loaded_deps->nodes[1]->path());

    log.Close();
  }
}

TEST_F(DepsLogTest_84, EmptyNodesInitially_84) {
  DepsLog log;
  EXPECT_TRUE(log.nodes().empty());
}

TEST_F(DepsLogTest_84, EmptyDepsInitially_84) {
  DepsLog log;
  EXPECT_TRUE(log.deps().empty());
}

TEST_F(DepsLogTest_84, GetDepsReturnsNullForUnknownNode_84) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));
  ASSERT_EQ("", err);

  Node* node = state_.GetNode("nonexistent.o", 0);
  EXPECT_TRUE(log.GetDeps(node) == NULL);

  log.Close();
}

TEST_F(DepsLogTest_84, RecordMultipleDepsEntries_84) {
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out1 = state_.GetNode("out1.o", 0);
    std::vector<Node*> deps1;
    deps1.push_back(state_.GetNode("a.h", 0));
    ASSERT_TRUE(log.RecordDeps(out1, 10, deps1));

    Node* out2 = state_.GetNode("out2.o", 0);
    std::vector<Node*> deps2;
    deps2.push_back(state_.GetNode("b.h", 0));
    deps2.push_back(state_.GetNode("c.h", 0));
    ASSERT_TRUE(log.RecordDeps(out2, 20, deps2));

    // Verify nodes were recorded
    EXPECT_FALSE(log.nodes().empty());

    log.Close();
  }

  {
    DepsLog log;
    std::string err;
    State state;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state, &err));
    ASSERT_EQ("", err);

    DepsLog::Deps* d1 = log.GetDeps(state.GetNode("out1.o", 0));
    ASSERT_TRUE(d1 != NULL);
    EXPECT_EQ(10, d1->mtime);
    EXPECT_EQ(1, d1->node_count);
    EXPECT_EQ("a.h", d1->nodes[0]->path());

    DepsLog::Deps* d2 = log.GetDeps(state.GetNode("out2.o", 0));
    ASSERT_TRUE(d2 != NULL);
    EXPECT_EQ(20, d2->mtime);
    EXPECT_EQ(2, d2->node_count);
    EXPECT_EQ("b.h", d2->nodes[0]->path());
    EXPECT_EQ("c.h", d2->nodes[1]->path());

    log.Close();
  }
}

TEST_F(DepsLogTest_84, UpdateExistingDeps_84) {
  // Record deps, then update them for the same output.
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    std::vector<Node*> deps;
    deps.push_back(state_.GetNode("foo.h", 0));
    ASSERT_TRUE(log.RecordDeps(out, 1, deps));

    // Update deps for same output.
    std::vector<Node*> deps2;
    deps2.push_back(state_.GetNode("bar.h", 0));
    deps2.push_back(state_.GetNode("baz.h", 0));
    ASSERT_TRUE(log.RecordDeps(out, 2, deps2));

    // Should see updated deps.
    DepsLog::Deps* d = log.GetDeps(out);
    ASSERT_TRUE(d != NULL);
    EXPECT_EQ(2, d->mtime);
    EXPECT_EQ(2, d->node_count);

    log.Close();
  }
}

TEST_F(DepsLogTest_84, LoadFromNonexistentFileReturnsNotFound_84) {
  DepsLog log;
  std::string err;
  State state;
  EXPECT_EQ(LOAD_NOT_FOUND, log.Load("nonexistent_file_84", &state, &err));
}

TEST_F(DepsLogTest_84, Recompact_84) {
  // Write multiple updates and then recompact.
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    std::vector<Node*> deps;
    deps.push_back(state_.GetNode("foo.h", 0));
    ASSERT_TRUE(log.RecordDeps(out, 1, deps));

    // Update to cause potential recompaction need.
    std::vector<Node*> deps2;
    deps2.push_back(state_.GetNode("bar.h", 0));
    ASSERT_TRUE(log.RecordDeps(out, 2, deps2));

    log.Close();
  }

  // Recompact.
  {
    DepsLog log;
    std::string err;
    State state;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state, &err));
    ASSERT_TRUE(log.Recompact(kTestFilename, &err));
    ASSERT_EQ("", err);
    log.Close();
  }

  // Verify after recompaction.
  {
    DepsLog log;
    std::string err;
    State state;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state, &err));
    ASSERT_EQ("", err);

    DepsLog::Deps* d = log.GetDeps(state.GetNode("out.o", 0));
    ASSERT_TRUE(d != NULL);
    EXPECT_EQ(2, d->mtime);
    EXPECT_EQ(1, d->node_count);
    EXPECT_EQ("bar.h", d->nodes[0]->path());

    log.Close();
  }
}

TEST_F(DepsLogTest_84, RecordDepsWithNodePointerArray_84) {
  // Test the overload that takes (Node*, TimeStamp, int, Node*const*).
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    Node* dep_nodes[2];
    dep_nodes[0] = state_.GetNode("x.h", 0);
    dep_nodes[1] = state_.GetNode("y.h", 0);
    ASSERT_TRUE(log.RecordDeps(out, 5, 2, dep_nodes));

    DepsLog::Deps* d = log.GetDeps(out);
    ASSERT_TRUE(d != NULL);
    EXPECT_EQ(5, d->mtime);
    EXPECT_EQ(2, d->node_count);

    log.Close();
  }
}

TEST_F(DepsLogTest_84, NodesVectorPopulatedAfterRecord_84) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  EXPECT_TRUE(log.nodes().empty());

  Node* out = state_.GetNode("out.o", 0);
  std::vector<Node*> deps;
  deps.push_back(state_.GetNode("dep.h", 0));
  ASSERT_TRUE(log.RecordDeps(out, 1, deps));

  // After recording, nodes vector should have entries.
  EXPECT_FALSE(log.nodes().empty());

  log.Close();
}

TEST_F(DepsLogTest_84, DepsVectorPopulatedAfterRecord_84) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  EXPECT_TRUE(log.deps().empty());

  Node* out = state_.GetNode("out.o", 0);
  std::vector<Node*> deps;
  deps.push_back(state_.GetNode("dep.h", 0));
  ASSERT_TRUE(log.RecordDeps(out, 1, deps));

  // After recording, deps vector should have at least one entry.
  EXPECT_FALSE(log.deps().empty());

  log.Close();
}

TEST_F(DepsLogTest_84, IsDepsEntryLiveFor_84) {
  // A node with no edge should not have live deps.
  Node* node = state_.GetNode("lonely.o", 0);
  EXPECT_FALSE(DepsLog::IsDepsEntryLiveFor(node));
}

TEST_F(DepsLogTest_84, GetFirstReverseDepsNode_84) {
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    Node* dep = state_.GetNode("common.h", 0);
    std::vector<Node*> deps;
    deps.push_back(dep);
    ASSERT_TRUE(log.RecordDeps(out, 1, deps));

    // common.h is a dependency of out.o, so reverse deps should find out.o.
    Node* reverse = log.GetFirstReverseDepsNode(dep);
    ASSERT_TRUE(reverse != NULL);
    EXPECT_EQ("out.o", reverse->path());

    log.Close();
  }
}

TEST_F(DepsLogTest_84, GetFirstReverseDepsNodeReturnsNullForUnknown_84) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  Node* node = state_.GetNode("unknown.h", 0);
  Node* reverse = log.GetFirstReverseDepsNode(node);
  EXPECT_TRUE(reverse == NULL);

  log.Close();
}

TEST_F(DepsLogTest_84, EmptyDepsVector_84) {
  // Record deps with an empty deps vector.
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    std::vector<Node*> deps;
    ASSERT_TRUE(log.RecordDeps(out, 3, deps));

    DepsLog::Deps* d = log.GetDeps(out);
    ASSERT_TRUE(d != NULL);
    EXPECT_EQ(3, d->mtime);
    EXPECT_EQ(0, d->node_count);

    log.Close();
  }

  // Verify on reload.
  {
    DepsLog log;
    std::string err;
    State state;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state, &err));

    DepsLog::Deps* d = log.GetDeps(state.GetNode("out.o", 0));
    ASSERT_TRUE(d != NULL);
    EXPECT_EQ(0, d->node_count);

    log.Close();
  }
}

TEST_F(DepsLogTest_84, CloseWithoutOpen_84) {
  // Closing without opening should not crash.
  DepsLog log;
  log.Close();
}

TEST_F(DepsLogTest_84, DoubleClose_84) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));
  log.Close();
  // Second close should be safe.
  log.Close();
}

TEST_F(DepsLogTest_84, LoadPopulatesNodesAndDeps_84) {
  // Write data.
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    std::vector<Node*> deps;
    deps.push_back(state_.GetNode("header.h", 0));
    ASSERT_TRUE(log.RecordDeps(out, 7, deps));

    log.Close();
  }

  // Load and check nodes()/deps().
  {
    DepsLog log;
    std::string err;
    State state;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state, &err));

    EXPECT_FALSE(log.nodes().empty());
    EXPECT_FALSE(log.deps().empty());

    log.Close();
  }
}

}  // namespace

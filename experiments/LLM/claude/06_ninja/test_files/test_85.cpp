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

const char kTestFilename[] = "DepsLogTest_tempfile_85";

void RemoveTestFile() {
  unlink(kTestFilename);
}

class DepsLogTest_85 : public ::testing::Test {
 protected:
  void SetUp() override {
    RemoveTestFile();
  }
  void TearDown() override {
    RemoveTestFile();
  }

  State state_;
};

TEST_F(DepsLogTest_85, OpenForWriteCreatesFile_85) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));
  EXPECT_EQ("", err);
  log.Close();
}

TEST_F(DepsLogTest_85, EmptyDepsInitially_85) {
  DepsLog log;
  const std::vector<DepsLog::Deps*>& deps = log.deps();
  EXPECT_TRUE(deps.empty());
}

TEST_F(DepsLogTest_85, EmptyNodesInitially_85) {
  DepsLog log;
  const std::vector<Node*>& nodes = log.nodes();
  EXPECT_TRUE(nodes.empty());
}

TEST_F(DepsLogTest_85, RecordAndGetDeps_85) {
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    Node* dep1 = state_.GetNode("dep1.h", 0);
    Node* dep2 = state_.GetNode("dep2.h", 0);

    std::vector<Node*> dep_nodes;
    dep_nodes.push_back(dep1);
    dep_nodes.push_back(dep2);

    ASSERT_TRUE(log.RecordDeps(out, 100, dep_nodes));

    DepsLog::Deps* deps = log.GetDeps(out);
    ASSERT_NE(nullptr, deps);
    EXPECT_EQ(100, deps->mtime);
    EXPECT_EQ(2, deps->node_count);
    EXPECT_EQ(dep1, deps->nodes[0]);
    EXPECT_EQ(dep2, deps->nodes[1]);

    log.Close();
  }
}

TEST_F(DepsLogTest_85, GetDepsReturnsNullForUnknownNode_85) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  Node* unknown = state_.GetNode("unknown.o", 0);
  EXPECT_EQ(nullptr, log.GetDeps(unknown));

  log.Close();
}

TEST_F(DepsLogTest_85, LoadFromDisk_85) {
  // Write some deps
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    Node* dep1 = state_.GetNode("dep1.h", 0);

    std::vector<Node*> dep_nodes;
    dep_nodes.push_back(dep1);
    ASSERT_TRUE(log.RecordDeps(out, 50, dep_nodes));
    log.Close();
  }

  // Load them in a new log with a fresh state
  {
    State state2;
    DepsLog log;
    std::string err;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state2, &err));
    EXPECT_EQ("", err);

    Node* out = state2.GetNode("out.o", 0);
    ASSERT_NE(nullptr, out);
    DepsLog::Deps* deps = log.GetDeps(out);
    ASSERT_NE(nullptr, deps);
    EXPECT_EQ(50, deps->mtime);
    EXPECT_EQ(1, deps->node_count);

    log.Close();
  }
}

TEST_F(DepsLogTest_85, LoadNonExistentFile_85) {
  DepsLog log;
  std::string err;
  LoadStatus status = log.Load("nonexistent_file_85", &state_, &err);
  EXPECT_EQ(LOAD_NOT_FOUND, status);
}

TEST_F(DepsLogTest_85, DepsVectorGrowsWithRecords_85) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  Node* out1 = state_.GetNode("out1.o", 0);
  Node* out2 = state_.GetNode("out2.o", 0);
  Node* dep1 = state_.GetNode("dep1.h", 0);

  std::vector<Node*> dep_nodes;
  dep_nodes.push_back(dep1);

  ASSERT_TRUE(log.RecordDeps(out1, 10, dep_nodes));
  ASSERT_TRUE(log.RecordDeps(out2, 20, dep_nodes));

  // deps() should have entries; exact indexing depends on node IDs
  const std::vector<DepsLog::Deps*>& deps = log.deps();
  EXPECT_FALSE(deps.empty());

  log.Close();
}

TEST_F(DepsLogTest_85, NodesVectorGrowsWithRecords_85) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  Node* out = state_.GetNode("out.o", 0);
  Node* dep1 = state_.GetNode("dep1.h", 0);
  Node* dep2 = state_.GetNode("dep2.h", 0);

  std::vector<Node*> dep_nodes;
  dep_nodes.push_back(dep1);
  dep_nodes.push_back(dep2);

  ASSERT_TRUE(log.RecordDeps(out, 10, dep_nodes));

  const std::vector<Node*>& nodes = log.nodes();
  EXPECT_GE(nodes.size(), 3u);  // at least out, dep1, dep2

  log.Close();
}

TEST_F(DepsLogTest_85, RecordDepsOverwritesPrevious_85) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  Node* out = state_.GetNode("out.o", 0);
  Node* dep1 = state_.GetNode("dep1.h", 0);
  Node* dep2 = state_.GetNode("dep2.h", 0);

  std::vector<Node*> dep_nodes1;
  dep_nodes1.push_back(dep1);
  ASSERT_TRUE(log.RecordDeps(out, 10, dep_nodes1));

  // Overwrite with different deps
  std::vector<Node*> dep_nodes2;
  dep_nodes2.push_back(dep2);
  ASSERT_TRUE(log.RecordDeps(out, 20, dep_nodes2));

  DepsLog::Deps* deps = log.GetDeps(out);
  ASSERT_NE(nullptr, deps);
  EXPECT_EQ(20, deps->mtime);
  EXPECT_EQ(1, deps->node_count);
  EXPECT_EQ(dep2, deps->nodes[0]);

  log.Close();
}

TEST_F(DepsLogTest_85, RecordDepsWithNodeArray_85) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  Node* out = state_.GetNode("out.o", 0);
  Node* dep1 = state_.GetNode("dep1.h", 0);
  Node* dep2 = state_.GetNode("dep2.h", 0);

  Node* dep_array[] = { dep1, dep2 };
  ASSERT_TRUE(log.RecordDeps(out, 77, 2, dep_array));

  DepsLog::Deps* deps = log.GetDeps(out);
  ASSERT_NE(nullptr, deps);
  EXPECT_EQ(77, deps->mtime);
  EXPECT_EQ(2, deps->node_count);
  EXPECT_EQ(dep1, deps->nodes[0]);
  EXPECT_EQ(dep2, deps->nodes[1]);

  log.Close();
}

TEST_F(DepsLogTest_85, RecordDepsWithNoDeps_85) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  Node* out = state_.GetNode("out.o", 0);
  std::vector<Node*> empty;
  ASSERT_TRUE(log.RecordDeps(out, 5, empty));

  DepsLog::Deps* deps = log.GetDeps(out);
  ASSERT_NE(nullptr, deps);
  EXPECT_EQ(5, deps->mtime);
  EXPECT_EQ(0, deps->node_count);

  log.Close();
}

TEST_F(DepsLogTest_85, Recompact_85) {
  // Create a log with some overwrites to trigger recompaction need
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    Node* dep1 = state_.GetNode("dep1.h", 0);
    Node* dep2 = state_.GetNode("dep2.h", 0);

    std::vector<Node*> deps1;
    deps1.push_back(dep1);
    ASSERT_TRUE(log.RecordDeps(out, 10, deps1));

    std::vector<Node*> deps2;
    deps2.push_back(dep2);
    ASSERT_TRUE(log.RecordDeps(out, 20, deps2));

    log.Close();
  }

  // Recompact
  {
    DepsLog log;
    std::string err;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state_, &err));
    EXPECT_TRUE(log.Recompact(kTestFilename, &err));
    EXPECT_EQ("", err);
  }

  // Verify after recompaction
  {
    State state2;
    DepsLog log;
    std::string err;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state2, &err));

    Node* out = state2.GetNode("out.o", 0);
    ASSERT_NE(nullptr, out);
    DepsLog::Deps* deps = log.GetDeps(out);
    ASSERT_NE(nullptr, deps);
    EXPECT_EQ(20, deps->mtime);
    EXPECT_EQ(1, deps->node_count);

    log.Close();
  }
}

TEST_F(DepsLogTest_85, IsDepsEntryLiveFor_85) {
  // A node with no in_edge should not be considered live for deps purposes
  // (or it might be live - we test the static function is callable)
  Node* node = state_.GetNode("test.o", 0);
  // Just verify it's callable - we can't know the exact logic
  bool result = DepsLog::IsDepsEntryLiveFor(node);
  // Without an edge, typically false
  (void)result;  // We just test it doesn't crash
}

TEST_F(DepsLogTest_85, CloseWithoutOpen_85) {
  // Closing without opening should not crash
  DepsLog log;
  log.Close();
}

TEST_F(DepsLogTest_85, GetFirstReverseDepsNode_85) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  Node* out = state_.GetNode("out.o", 0);
  Node* dep1 = state_.GetNode("dep1.h", 0);

  std::vector<Node*> dep_nodes;
  dep_nodes.push_back(dep1);
  ASSERT_TRUE(log.RecordDeps(out, 10, dep_nodes));

  // dep1 is a dependency of out, so GetFirstReverseDepsNode(dep1)
  // should return out (or some node that depends on dep1)
  Node* reverse = log.GetFirstReverseDepsNode(dep1);
  EXPECT_EQ(out, reverse);

  // For a node that nothing depends on
  Node* orphan = state_.GetNode("orphan.h", 0);
  // We need to record something so orphan gets an ID, but it won't be a dep of anything
  // Actually, orphan might not be in the log at all, so this could return null
  Node* reverse_orphan = log.GetFirstReverseDepsNode(orphan);
  EXPECT_EQ(nullptr, reverse_orphan);

  log.Close();
}

TEST_F(DepsLogTest_85, PersistenceAcrossOpenClose_85) {
  {
    DepsLog log;
    std::string err;
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out = state_.GetNode("out.o", 0);
    Node* dep = state_.GetNode("dep.h", 0);
    std::vector<Node*> deps;
    deps.push_back(dep);
    ASSERT_TRUE(log.RecordDeps(out, 42, deps));
    log.Close();
  }

  // Reopen and append
  {
    State state2;
    DepsLog log;
    std::string err;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state2, &err));
    ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

    Node* out2 = state2.GetNode("out2.o", 0);
    Node* dep2 = state2.GetNode("dep2.h", 0);
    std::vector<Node*> deps;
    deps.push_back(dep2);
    ASSERT_TRUE(log.RecordDeps(out2, 99, deps));

    // Verify both entries
    Node* out = state2.GetNode("out.o", 0);
    DepsLog::Deps* d1 = log.GetDeps(out);
    ASSERT_NE(nullptr, d1);
    EXPECT_EQ(42, d1->mtime);

    DepsLog::Deps* d2 = log.GetDeps(out2);
    ASSERT_NE(nullptr, d2);
    EXPECT_EQ(99, d2->mtime);

    log.Close();
  }

  // Verify full persistence
  {
    State state3;
    DepsLog log;
    std::string err;
    ASSERT_EQ(LOAD_SUCCESS, log.Load(kTestFilename, &state3, &err));

    Node* out = state3.GetNode("out.o", 0);
    Node* out2 = state3.GetNode("out2.o", 0);

    DepsLog::Deps* d1 = log.GetDeps(out);
    ASSERT_NE(nullptr, d1);
    EXPECT_EQ(42, d1->mtime);

    DepsLog::Deps* d2 = log.GetDeps(out2);
    ASSERT_NE(nullptr, d2);
    EXPECT_EQ(99, d2->mtime);

    log.Close();
  }
}

TEST_F(DepsLogTest_85, MultipleDependencies_85) {
  DepsLog log;
  std::string err;
  ASSERT_TRUE(log.OpenForWrite(kTestFilename, &err));

  Node* out = state_.GetNode("out.o", 0);
  std::vector<Node*> dep_nodes;
  for (int i = 0; i < 10; ++i) {
    char name[32];
    snprintf(name, sizeof(name), "dep%d.h", i);
    dep_nodes.push_back(state_.GetNode(name, 0));
  }

  ASSERT_TRUE(log.RecordDeps(out, 200, dep_nodes));

  DepsLog::Deps* deps = log.GetDeps(out);
  ASSERT_NE(nullptr, deps);
  EXPECT_EQ(200, deps->mtime);
  EXPECT_EQ(10, deps->node_count);

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(dep_nodes[i], deps->nodes[i]);
  }

  log.Close();
}

}  // namespace

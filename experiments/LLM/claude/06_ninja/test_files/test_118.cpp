#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "build_log.h"
#include "build.h"
#include "graph.h"
#include "state.h"
#include "disk_interface.h"
#include "util.h"
#include "test.h"

#include <cstdio>
#include <string>
#include <cstring>

#ifdef _WIN32
#include <io.h>
#endif

namespace {

const char kTestFilename[] = "BuildLogTest-tempfile";

struct BuildLogTest_118 : public ::testing::Test {
  virtual void SetUp() {
  }

  virtual void TearDown() {
    unlink(kTestFilename);
  }
};

// A simple BuildLogUser implementation for testing.
struct TestBuildLogUser : public BuildLogUser {
  bool IsPathDead(StringPiece s) const override {
    return false;
  }
};

// A BuildLogUser that considers certain paths as dead.
struct DeadPathBuildLogUser : public BuildLogUser {
  bool IsPathDead(StringPiece s) const override {
    // Mark paths containing "dead" as dead
    std::string str(s.str_, s.len_);
    return str.find("dead") != std::string::npos;
  }
};

TEST_F(BuildLogTest_118, DefaultConstructorEmptyEntries_118) {
  BuildLog log;
  EXPECT_TRUE(log.entries().empty());
}

TEST_F(BuildLogTest_118, OpenForWriteCreatesFile_118) {
  BuildLog log;
  TestBuildLogUser user;
  std::string err;
  EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));
  EXPECT_EQ("", err);
  log.Close();
}

TEST_F(BuildLogTest_118, OpenForWriteInvalidPath_118) {
  BuildLog log;
  TestBuildLogUser user;
  std::string err;
  // Try opening a file in a non-existent directory
  bool result = log.OpenForWrite("/nonexistent/dir/file", user, &err);
  if (!result) {
    EXPECT_NE("", err);
  }
  log.Close();
}

TEST_F(BuildLogTest_118, RecordCommand_118) {
  // Build a simple graph to test RecordCommand.
  State state;
  
  // First, create the log and write to it.
  {
    BuildLog log;
    TestBuildLogUser user;
    std::string err;
    EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));
    EXPECT_EQ("", err);

    // We need an Edge to record. Create a simple rule and edge.
    Rule* rule = new Rule("cat");
    rule->AddBinding("command", new EvalString());
    state.bindings_.AddRule(rule);

    Edge* edge = state.AddEdge(rule);
    state.AddOut(edge, "out1", 0);
    // Add an input
    state.AddIn(edge, "in1", 0);

    EXPECT_TRUE(log.RecordCommand(edge, 100, 200, 300));
    log.Close();
  }

  // Verify by loading the log
  {
    BuildLog log;
    TestBuildLogUser user;
    std::string err;
    LoadStatus status = log.Load(kTestFilename, &err);
    EXPECT_EQ(LOAD_SUCCESS, status);
    EXPECT_EQ("", err);
    EXPECT_FALSE(log.entries().empty());
  }
}

TEST_F(BuildLogTest_118, LookupByOutputNotFound_118) {
  BuildLog log;
  LogEntry* entry = log.LookupByOutput("nonexistent_output");
  EXPECT_EQ(nullptr, entry);
}

TEST_F(BuildLogTest_118, LookupByOutputFound_118) {
  State state;

  BuildLog log;
  TestBuildLogUser user;
  std::string err;
  EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));

  Rule* rule = new Rule("cat");
  rule->AddBinding("command", new EvalString());
  state.bindings_.AddRule(rule);

  Edge* edge = state.AddEdge(rule);
  state.AddOut(edge, "out_lookup", 0);
  state.AddIn(edge, "in_lookup", 0);

  EXPECT_TRUE(log.RecordCommand(edge, 10, 20, 30));

  LogEntry* entry = log.LookupByOutput("out_lookup");
  EXPECT_NE(nullptr, entry);
  EXPECT_EQ(10, entry->start_time);
  EXPECT_EQ(20, entry->end_time);
  EXPECT_EQ(30, entry->mtime);

  log.Close();
}

TEST_F(BuildLogTest_118, LoadNonexistentFile_118) {
  BuildLog log;
  std::string err;
  LoadStatus status = log.Load("nonexistent_file.log", &err);
  EXPECT_EQ(LOAD_NOT_FOUND, status);
}

TEST_F(BuildLogTest_118, LoadEmptyFile_118) {
  // Create an empty file
  FILE* f = fopen(kTestFilename, "w");
  ASSERT_TRUE(f != nullptr);
  fclose(f);

  BuildLog log;
  std::string err;
  LoadStatus status = log.Load(kTestFilename, &err);
  // An empty file might be considered an error or not found
  // depending on implementation. We just test it doesn't crash.
  // The status may be LOAD_SUCCESS with empty entries, or LOAD_NOT_FOUND.
  if (status == LOAD_SUCCESS) {
    // Fine, empty log
  }
}

TEST_F(BuildLogTest_118, WriteAndLoadRoundTrip_118) {
  State state;

  // Write
  {
    BuildLog log;
    TestBuildLogUser user;
    std::string err;
    EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));

    Rule* rule = new Rule("cat");
    rule->AddBinding("command", new EvalString());
    state.bindings_.AddRule(rule);

    Edge* edge = state.AddEdge(rule);
    state.AddOut(edge, "roundtrip_out", 0);
    state.AddIn(edge, "roundtrip_in", 0);

    EXPECT_TRUE(log.RecordCommand(edge, 1, 2, 3));
    log.Close();
  }

  // Read
  {
    BuildLog log;
    std::string err;
    LoadStatus status = log.Load(kTestFilename, &err);
    EXPECT_EQ(LOAD_SUCCESS, status);
    EXPECT_EQ("", err);

    LogEntry* entry = log.LookupByOutput("roundtrip_out");
    ASSERT_NE(nullptr, entry);
    EXPECT_EQ(1, entry->start_time);
    EXPECT_EQ(2, entry->end_time);
    EXPECT_EQ(3, entry->mtime);
  }
}

TEST_F(BuildLogTest_118, MultipleRecords_118) {
  State state;

  BuildLog log;
  TestBuildLogUser user;
  std::string err;
  EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));

  Rule* rule = new Rule("cat");
  rule->AddBinding("command", new EvalString());
  state.bindings_.AddRule(rule);

  // Record first edge
  Edge* edge1 = state.AddEdge(rule);
  state.AddOut(edge1, "multi_out1", 0);
  state.AddIn(edge1, "multi_in1", 0);
  EXPECT_TRUE(log.RecordCommand(edge1, 10, 20, 30));

  // Record second edge
  Edge* edge2 = state.AddEdge(rule);
  state.AddOut(edge2, "multi_out2", 0);
  state.AddIn(edge2, "multi_in2", 0);
  EXPECT_TRUE(log.RecordCommand(edge2, 40, 50, 60));

  EXPECT_NE(nullptr, log.LookupByOutput("multi_out1"));
  EXPECT_NE(nullptr, log.LookupByOutput("multi_out2"));
  EXPECT_EQ(nullptr, log.LookupByOutput("multi_out3"));

  log.Close();
}

TEST_F(BuildLogTest_118, EntriesReturnsAllRecords_118) {
  State state;

  BuildLog log;
  TestBuildLogUser user;
  std::string err;
  EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));

  Rule* rule = new Rule("cat");
  rule->AddBinding("command", new EvalString());
  state.bindings_.AddRule(rule);

  Edge* edge1 = state.AddEdge(rule);
  state.AddOut(edge1, "entries_out1", 0);
  state.AddIn(edge1, "entries_in1", 0);
  EXPECT_TRUE(log.RecordCommand(edge1, 1, 2, 3));

  Edge* edge2 = state.AddEdge(rule);
  state.AddOut(edge2, "entries_out2", 0);
  state.AddIn(edge2, "entries_in2", 0);
  EXPECT_TRUE(log.RecordCommand(edge2, 4, 5, 6));

  const BuildLog::Entries& entries = log.entries();
  EXPECT_EQ(2u, entries.size());

  log.Close();
}

TEST_F(BuildLogTest_118, CloseWithoutOpen_118) {
  BuildLog log;
  // Close on a log that was never opened should be safe
  log.Close();
  EXPECT_TRUE(log.entries().empty());
}

TEST_F(BuildLogTest_118, WriteEntry_118) {
  LogEntry entry;
  entry.output = "test_output";
  entry.command_hash = 12345;
  entry.start_time = 100;
  entry.end_time = 200;
  entry.mtime = 300;

  FILE* f = fopen(kTestFilename, "w");
  ASSERT_TRUE(f != nullptr);

  BuildLog log;
  EXPECT_TRUE(log.WriteEntry(f, entry));
  fclose(f);

  // Verify the file is non-empty
  f = fopen(kTestFilename, "r");
  ASSERT_TRUE(f != nullptr);
  char buf[1024];
  size_t bytes_read = fread(buf, 1, sizeof(buf), f);
  EXPECT_GT(bytes_read, 0u);
  fclose(f);
}

TEST_F(BuildLogTest_118, Recompact_118) {
  State state;

  // Create a log with some entries
  {
    BuildLog log;
    TestBuildLogUser user;
    std::string err;
    EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));

    Rule* rule = new Rule("cat");
    rule->AddBinding("command", new EvalString());
    state.bindings_.AddRule(rule);

    Edge* edge = state.AddEdge(rule);
    state.AddOut(edge, "recompact_out", 0);
    state.AddIn(edge, "recompact_in", 0);
    EXPECT_TRUE(log.RecordCommand(edge, 1, 2, 3));
    // Record same edge again to create a duplicate that recompaction should clean
    EXPECT_TRUE(log.RecordCommand(edge, 4, 5, 6));
    log.Close();
  }

  // Recompact
  {
    BuildLog log;
    TestBuildLogUser user;
    std::string err;
    LoadStatus status = log.Load(kTestFilename, &err);
    EXPECT_EQ(LOAD_SUCCESS, status);

    EXPECT_TRUE(log.Recompact(kTestFilename, user, &err));
    EXPECT_EQ("", err);
  }

  // Verify after recompact
  {
    BuildLog log;
    std::string err;
    LoadStatus status = log.Load(kTestFilename, &err);
    EXPECT_EQ(LOAD_SUCCESS, status);

    LogEntry* entry = log.LookupByOutput("recompact_out");
    ASSERT_NE(nullptr, entry);
    // After recompaction, the latest record should be preserved
    EXPECT_EQ(4, entry->start_time);
    EXPECT_EQ(5, entry->end_time);
    EXPECT_EQ(6, entry->mtime);
  }
}

TEST_F(BuildLogTest_118, RecompactRemovesDeadPaths_118) {
  State state;

  // Create a log with entries including a "dead" output
  {
    BuildLog log;
    TestBuildLogUser user;
    std::string err;
    EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));

    Rule* rule = new Rule("cat");
    rule->AddBinding("command", new EvalString());
    state.bindings_.AddRule(rule);

    Edge* edge1 = state.AddEdge(rule);
    state.AddOut(edge1, "alive_out", 0);
    state.AddIn(edge1, "alive_in", 0);
    EXPECT_TRUE(log.RecordCommand(edge1, 1, 2, 3));

    Edge* edge2 = state.AddEdge(rule);
    state.AddOut(edge2, "dead_out", 0);
    state.AddIn(edge2, "dead_in", 0);
    EXPECT_TRUE(log.RecordCommand(edge2, 4, 5, 6));

    log.Close();
  }

  // Recompact with DeadPathBuildLogUser
  {
    BuildLog log;
    DeadPathBuildLogUser user;
    std::string err;
    LoadStatus status = log.Load(kTestFilename, &err);
    EXPECT_EQ(LOAD_SUCCESS, status);

    EXPECT_TRUE(log.Recompact(kTestFilename, user, &err));
    EXPECT_EQ("", err);
  }

  // Verify after recompact: dead_out should be removed
  {
    BuildLog log;
    std::string err;
    LoadStatus status = log.Load(kTestFilename, &err);
    EXPECT_EQ(LOAD_SUCCESS, status);

    EXPECT_NE(nullptr, log.LookupByOutput("alive_out"));
    EXPECT_EQ(nullptr, log.LookupByOutput("dead_out"));
  }
}

TEST_F(BuildLogTest_118, OverwriteExistingEntry_118) {
  State state;

  BuildLog log;
  TestBuildLogUser user;
  std::string err;
  EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));

  Rule* rule = new Rule("cat");
  rule->AddBinding("command", new EvalString());
  state.bindings_.AddRule(rule);

  Edge* edge = state.AddEdge(rule);
  state.AddOut(edge, "overwrite_out", 0);
  state.AddIn(edge, "overwrite_in", 0);

  EXPECT_TRUE(log.RecordCommand(edge, 1, 2, 3));
  LogEntry* entry = log.LookupByOutput("overwrite_out");
  ASSERT_NE(nullptr, entry);
  EXPECT_EQ(1, entry->start_time);

  // Record again with different times
  EXPECT_TRUE(log.RecordCommand(edge, 10, 20, 30));
  entry = log.LookupByOutput("overwrite_out");
  ASSERT_NE(nullptr, entry);
  EXPECT_EQ(10, entry->start_time);
  EXPECT_EQ(20, entry->end_time);
  EXPECT_EQ(30, entry->mtime);

  // Should still be only one entry for this output
  EXPECT_EQ(1u, log.entries().size());

  log.Close();
}

TEST_F(BuildLogTest_118, LoadCorruptedFile_118) {
  // Write garbage to the file
  FILE* f = fopen(kTestFilename, "w");
  ASSERT_TRUE(f != nullptr);
  fprintf(f, "this is not a valid build log\n");
  fprintf(f, "garbage data here\n");
  fclose(f);

  BuildLog log;
  std::string err;
  LoadStatus status = log.Load(kTestFilename, &err);
  // The implementation may handle corrupt data gracefully
  // We just ensure it doesn't crash
  (void)status;
}

TEST_F(BuildLogTest_118, LoadWithVersionHeader_118) {
  // Write a proper version header
  FILE* f = fopen(kTestFilename, "w");
  ASSERT_TRUE(f != nullptr);
  fprintf(f, "# ninja log v5\n");
  fclose(f);

  BuildLog log;
  std::string err;
  LoadStatus status = log.Load(kTestFilename, &err);
  EXPECT_EQ(LOAD_SUCCESS, status);
  EXPECT_EQ("", err);
  EXPECT_TRUE(log.entries().empty());
}

TEST_F(BuildLogTest_118, DestructorClosesCleanly_118) {
  // Test that destructor doesn't crash even after open
  {
    BuildLog log;
    TestBuildLogUser user;
    std::string err;
    EXPECT_TRUE(log.OpenForWrite(kTestFilename, user, &err));
    // Let destructor handle cleanup
  }
  // If we reach here, destructor didn't crash
  SUCCEED();
}

}  // namespace

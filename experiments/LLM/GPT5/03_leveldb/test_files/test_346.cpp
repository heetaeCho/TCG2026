// File: db/leveldbutil_main_test.cc

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <cstring>

// ---- Minimal surface from the dependency header ----
#include "leveldb/env.h"

// ---------- Test doubles & plumbing ----------

// Recorders for verifying observable interactions
static int g_usage_call_count = 0;
static int g_handle_call_count = 0;
static bool g_handle_result = false;
static leveldb::Env* g_last_env = nullptr;
static std::vector<std::string> g_last_args;

// Global function used by the SUT; we provide a test double to observe calls.
void Usage() { ++g_usage_call_count; }

// Provide a trivial Env singleton so leveldbutil can call Env::Default().
namespace leveldb {

class TestEnv : public Env {
  // No behavior needed for these tests; main() only passes the pointer along.
};

static TestEnv& GetTestEnv() {
  static TestEnv env;
  return env;
}

Env* Env::Default() {
  // Return a stable singleton pointer we can compare in assertions.
  return &GetTestEnv();
}

// Namespaced function called by the SUT for the "dump" command.
// We capture args and return a controllable boolean.
bool HandleDumpCommand(Env* env, char** argv, int n) {
  ++g_handle_call_count;
  g_last_env = env;
  g_last_args.clear();
  for (int i = 0; i < n; ++i) {
    g_last_args.emplace_back(argv[i] ? argv[i] : "");
  }
  return g_handle_result;
}

}  // namespace leveldb

// ---------- Include the SUT with a renamed entry point ----------
// We avoid symbol clash with gtest's main() by renaming the program's main()
// before including the .cc under test. This keeps the implementation intact.
#define main leveldbutil_main
#include "db/leveldbutil.cc"
#undef main

// ---------- Test fixture ----------
class LeveldbUtilMainTest_346 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_usage_call_count = 0;
    g_handle_call_count = 0;
    g_handle_result = false;
    g_last_env = nullptr;
    g_last_args.clear();
  }

  // Helper to build argv easily
  static std::vector<char*> MakeArgv(const std::vector<std::string>& args) {
    std::vector<char*> out;
    out.reserve(args.size());
    for (const auto& s : args) {
      // Store in a local buffer so c_str() lifetime is safe during call.
      // We copy into a mutable buffer to satisfy char** signature.
      char* buf = new char[s.size() + 1];
      std::memcpy(buf, s.c_str(), s.size() + 1);
      out.push_back(buf);
    }
    return out;
  }

  static void FreeArgv(std::vector<char*>* argv) {
    for (char* p : *argv) delete[] p;
    argv->clear();
  }
};

// ---------- Tests ----------

TEST_F(LeveldbUtilMainTest_346, ReturnsErrorAndCallsUsageWhenNoArgs_346) {
  // argc < 2 → should call Usage() and exit with 1
  auto argv = MakeArgv({"prog"});
  int rc = leveldbutil_main(static_cast<int>(argv.size()), argv.data());
  FreeArgv(&argv);

  EXPECT_EQ(rc, 1);
  EXPECT_EQ(g_usage_call_count, 1) << "Usage() should be called when argc < 2";
  EXPECT_EQ(g_handle_call_count, 0) << "Dump handler must not be called";
}

TEST_F(LeveldbUtilMainTest_346, UnknownCommandCallsUsageAndFails_346) {
  // Non-"dump" command → Usage() called, nonzero exit
  auto argv = MakeArgv({"prog", "list", "foo"});
  int rc = leveldbutil_main(static_cast<int>(argv.size()), argv.data());
  FreeArgv(&argv);

  EXPECT_EQ(rc, 1);
  EXPECT_EQ(g_usage_call_count, 1);
  EXPECT_EQ(g_handle_call_count, 0) << "Dump handler should not be invoked";
}

TEST_F(LeveldbUtilMainTest_346, DumpCommandPassesArgsAndSucceedsOnTrue_346) {
  // "dump" should forward (argv + 2, argc - 2) to HandleDumpCommand
  g_handle_result = true;  // Make handler report success

  auto argv = MakeArgv({"prog", "dump", "a", "b", "c"});
  int rc = leveldbutil_main(static_cast<int>(argv.size()), argv.data());
  FreeArgv(&argv);

  EXPECT_EQ(rc, 0) << "Return 0 when handler returns true";
  EXPECT_EQ(g_usage_call_count, 0) << "Usage() should not be called";
  ASSERT_EQ(g_handle_call_count, 1) << "Handler must be called exactly once";

  // Verify env pointer is the one from Env::Default()
  EXPECT_EQ(g_last_env, leveldb::Env::Default());

  // Verify argv slicing (skip first two tokens: program & command)
  std::vector<std::string> expected = {"a", "b", "c"};
  EXPECT_EQ(g_last_args, expected);
}

TEST_F(LeveldbUtilMainTest_346, DumpCommandFailsWhenHandlerReturnsFalse_346) {
  g_handle_result = false;  // Simulate handler failure

  auto argv = MakeArgv({"prog", "dump", "only_one_arg"});
  int rc = leveldbutil_main(static_cast<int>(argv.size()), argv.data());
  FreeArgv(&argv);

  EXPECT_EQ(rc, 1) << "Nonzero when handler returns false";
  EXPECT_EQ(g_usage_call_count, 0);
  ASSERT_EQ(g_handle_call_count, 1);
  std::vector<std::string> expected = {"only_one_arg"};
  EXPECT_EQ(g_last_args, expected);
}

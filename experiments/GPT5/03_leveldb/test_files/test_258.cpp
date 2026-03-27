// File: db/c_options_set_env_test_258.cc

#include <gtest/gtest.h>

// Assume these real headers are available in your build.
// If your project exposes different paths, adjust accordingly.
#include "leveldb/options.h"

// Minimal forward declarations to match your provided interface.
// If your build already exposes these from a public C header, include that instead.
struct leveldb_env_t {
  leveldb::Env* rep;
  bool is_default;
};

struct leveldb_options_t {
  leveldb::Options rep;
};

// Function under test (declared; implementation is linked from production code).
extern "C" void leveldb_options_set_env(leveldb_options_t* opt, leveldb_env_t* env);

// ---------- Test Suite ----------

class LevelDBOptionsSetEnvTest_258 : public ::testing::Test {
protected:
  // Helper to create a wrapper env with a specific (opaque) pointer value.
  static leveldb_env_t MakeEnvWithPtr(leveldb::Env* p) {
    leveldb_env_t e{};
    e.rep = p;
    e.is_default = false;
    return e;
  }
};

// Normal operation: sets a non-null Env pointer onto options.
TEST_F(LevelDBOptionsSetEnvTest_258, SetsNonNullEnv_258) {
  leveldb_options_t opt{};
  // Ensure a known baseline for an unrelated field to detect unintended changes.
  opt.rep.max_open_files = 7;

  // Use an opaque, non-dereferenced pointer value.
  auto* env_ptr = reinterpret_cast<leveldb::Env*>(0x1234);
  leveldb_env_t env = LevelDBOptionsSetEnvTest_258::MakeEnvWithPtr(env_ptr);

  leveldb_options_set_env(&opt, &env);

  EXPECT_EQ(opt.rep.env, env_ptr);
  // Verify unrelated fields remain unchanged (black-box side-effect guard).
  EXPECT_EQ(opt.rep.max_open_files, 7);
}

// Boundary: passing nullptr for env should set options.env to nullptr.
TEST_F(LevelDBOptionsSetEnvTest_258, SetsNullEnvWhenArgIsNull_258) {
  leveldb_options_t opt{};
  // Pre-populate with a non-null value to ensure it actually becomes null.
  opt.rep.env = reinterpret_cast<leveldb::Env*>(0xDEADBEEF);

  leveldb_options_set_env(&opt, nullptr);

  EXPECT_EQ(opt.rep.env, nullptr);
}

// Boundary: env wrapper exists but its internal rep is nullptr.
TEST_F(LevelDBOptionsSetEnvTest_258, SetsNullWhenEnvRepIsNull_258) {
  leveldb_options_t opt{};
  opt.rep.env = reinterpret_cast<leveldb::Env*>(0xFEEDBEEF);  // pre-set non-null

  leveldb_env_t env_with_null_rep = LevelDBOptionsSetEnvTest_258::MakeEnvWithPtr(nullptr);

  leveldb_options_set_env(&opt, &env_with_null_rep);

  EXPECT_EQ(opt.rep.env, nullptr);
}

// Normal operation: calling again overwrites any existing env pointer.
TEST_F(LevelDBOptionsSetEnvTest_258, OverwritesExistingEnv_258) {
  leveldb_options_t opt{};
  // Start with some existing pointer.
  opt.rep.env = reinterpret_cast<leveldb::Env*>(0xAAAA);

  auto* new_env_ptr = reinterpret_cast<leveldb::Env*>(0xBBBB);
  leveldb_env_t new_env = LevelDBOptionsSetEnvTest_258::MakeEnvWithPtr(new_env_ptr);

  leveldb_options_set_env(&opt, &new_env);

  EXPECT_EQ(opt.rep.env, new_env_ptr);
}

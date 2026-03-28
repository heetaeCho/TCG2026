// File: db/c_create_default_env_test_282.cc

#include <gtest/gtest.h>
#include "leveldb/env.h"

// Forward declarations based on the provided partial code.
struct leveldb_env_t {
  leveldb::Env* rep;
  bool is_default;
};

// Function under test (from db/c.cc).
leveldb_env_t* leveldb_create_default_env();

using leveldb::Env;

class CreateDefaultEnvTest_282 : public ::testing::Test {};

// [Normal] Returns a non-null wrapper pointer.
TEST_F(CreateDefaultEnvTest_282, CreatesNonNullWrapper_282) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  delete env;  // `rep` is owned by Env::Default(), do not delete it here.
}

// [Normal] The wrapper's rep points to Env::Default().
TEST_F(CreateDefaultEnvTest_282, SetsRepToEnvDefault_282) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  // Observable check: rep is not null and equals Env::Default()
  EXPECT_NE(env->rep, nullptr);
  EXPECT_EQ(env->rep, Env::Default());
  delete env;
}

// [Normal] The wrapper marks itself as default.
TEST_F(CreateDefaultEnvTest_282, SetsIsDefaultTrue_282) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  EXPECT_TRUE(env->is_default);
  delete env;
}

// [Boundary] Multiple calls return distinct wrapper objects (separate allocations).
TEST_F(CreateDefaultEnvTest_282, MultipleCallsReturnDistinctWrappers_282) {
  leveldb_env_t* env1 = leveldb_create_default_env();
  leveldb_env_t* env2 = leveldb_create_default_env();
  ASSERT_NE(env1, nullptr);
  ASSERT_NE(env2, nullptr);
  EXPECT_NE(env1, env2);           // distinct wrapper allocations
  EXPECT_NE(env1->rep, nullptr);
  EXPECT_NE(env2->rep, nullptr);
  // Each wrapper exposes Env::Default() as its rep (observable behavior)
  EXPECT_EQ(env1->rep, Env::Default());
  EXPECT_EQ(env2->rep, Env::Default());
  delete env1;
  delete env2;
}

// [Smoke / Interaction] The exposed Env pointer is usable for basic calls.
TEST_F(CreateDefaultEnvTest_282, RepIsUsableForBasicCall_282) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  ASSERT_NE(env->rep, nullptr);

  // Call a non-destructive method to confirm usability through the public API.
  // We do not assert specific timing semantics; just that a call succeeds and returns a value.
  const uint64_t now = env->rep->NowMicros();
  (void)now;  // Suppress unused variable warning.

  // Non-blocking sleep (0) to ensure the pointer can be used safely.
  env->rep->SleepForMicroseconds(0);

  delete env;
}

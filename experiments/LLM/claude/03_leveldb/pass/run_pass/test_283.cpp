#include "gtest/gtest.h"
#include "leveldb/c.h"
#include "leveldb/env.h"

// We need access to the internal struct definition for testing
// Based on the known dependency:
struct leveldb_env_t {
  leveldb::Env* rep;
  bool is_default;
};

// Helper to create a non-default env (custom env)
// We use a simple wrapper around the default env to simulate a custom env
class TestEnv : public leveldb::EnvWrapper {
 public:
  TestEnv() : EnvWrapper(leveldb::Env::Default()) {}
};

TEST(LevelDBEnvDestroy_283, DestroyDefaultEnv_DoesNotDeleteRep_283) {
  // When is_default is true, the rep should NOT be deleted.
  // We pass the default env as rep, which must not be deleted.
  leveldb_env_t* env = new leveldb_env_t;
  env->rep = leveldb::Env::Default();
  env->is_default = true;

  // This should not crash or delete the default env
  leveldb_env_destroy(env);

  // If we get here without crashing, the default env was not deleted
  // Verify the default env is still usable
  ASSERT_NE(leveldb::Env::Default(), nullptr);
}

TEST(LevelDBEnvDestroy_283, DestroyNonDefaultEnv_DeletesRep_283) {
  // When is_default is false, rep should be deleted along with the struct
  leveldb_env_t* env = new leveldb_env_t;
  env->rep = new TestEnv();
  env->is_default = false;

  // This should delete both rep and env without crashing
  leveldb_env_destroy(env);

  // If we reach here, the function successfully cleaned up both allocations
  SUCCEED();
}

TEST(LevelDBEnvDestroy_283, DestroyNonDefaultEnvWithIsDefaultFalse_283) {
  // Explicitly test that a non-default env with is_default=false gets its rep deleted
  auto* custom_env = new TestEnv();
  leveldb_env_t* env = new leveldb_env_t;
  env->rep = custom_env;
  env->is_default = false;

  // Should not leak or crash
  leveldb_env_destroy(env);
  SUCCEED();
}

TEST(LevelDBEnvDestroy_283, DefaultEnvFlagTrue_RepNotDeleted_283) {
  // Create an env struct pointing to default env with is_default = true
  // Ensure destruction only frees the wrapper struct, not the env itself
  leveldb_env_t* env = new leveldb_env_t;
  env->rep = leveldb::Env::Default();
  env->is_default = true;

  leveldb_env_destroy(env);

  // Default env should still be functional after destroy
  leveldb::Env* default_env = leveldb::Env::Default();
  ASSERT_NE(default_env, nullptr);

  // Try using the default env to ensure it's still valid
  std::string test_dir;
  leveldb::Status s = default_env->GetTestDirectory(&test_dir);
  EXPECT_TRUE(s.ok());
}

TEST(LevelDBEnvDestroy_283, MultipleNonDefaultEnvsCanBeDestroyed_283) {
  // Test that multiple non-default envs can be created and destroyed
  for (int i = 0; i < 5; i++) {
    leveldb_env_t* env = new leveldb_env_t;
    env->rep = new TestEnv();
    env->is_default = false;
    leveldb_env_destroy(env);
  }
  SUCCEED();
}

TEST(LevelDBEnvDestroy_283, MultipleDefaultEnvsCanBeDestroyed_283) {
  // Test that multiple default env wrappers can be destroyed without issue
  for (int i = 0; i < 5; i++) {
    leveldb_env_t* env = new leveldb_env_t;
    env->rep = leveldb::Env::Default();
    env->is_default = true;
    leveldb_env_destroy(env);
  }
  // Default env should still be valid
  ASSERT_NE(leveldb::Env::Default(), nullptr);
}

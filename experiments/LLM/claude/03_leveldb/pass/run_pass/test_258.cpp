#include "gtest/gtest.h"
#include "leveldb/c.h"
#include "leveldb/env.h"
#include "leveldb/options.h"

// We need access to the internal structs for testing
// These are defined in db/c.cc
extern "C" {
// Forward declarations of C API functions we need
leveldb_options_t* leveldb_options_create();
void leveldb_options_destroy(leveldb_options_t* opt);
void leveldb_options_set_env(leveldb_options_t* opt, leveldb_env_t* env);
leveldb_env_t* leveldb_create_default_env();
void leveldb_env_destroy(leveldb_env_t* env);
}

class LevelDBOptionsSetEnvTest_258 : public ::testing::Test {
 protected:
  void SetUp() override {
    options_ = leveldb_options_create();
    ASSERT_NE(options_, nullptr);
  }

  void TearDown() override {
    if (options_) {
      leveldb_options_destroy(options_);
    }
  }

  leveldb_options_t* options_ = nullptr;
};

// Test that setting a valid env through the default env works correctly
TEST_F(LevelDBOptionsSetEnvTest_258, SetDefaultEnv_258) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);

  leveldb_options_set_env(options_, env);

  // The env should have been set (we can't directly inspect, but it shouldn't crash)
  // Clean up
  leveldb_env_destroy(env);
}

// Test that setting env to nullptr results in nullptr env in options
TEST_F(LevelDBOptionsSetEnvTest_258, SetNullEnv_258) {
  // First set a valid env
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  leveldb_options_set_env(options_, env);

  // Now set to nullptr
  leveldb_options_set_env(options_, nullptr);

  // Should not crash; the env in options should now be nullptr
  leveldb_env_destroy(env);
}

// Test setting env multiple times (overwriting)
TEST_F(LevelDBOptionsSetEnvTest_258, SetEnvMultipleTimes_258) {
  leveldb_env_t* env1 = leveldb_create_default_env();
  ASSERT_NE(env1, nullptr);

  leveldb_env_t* env2 = leveldb_create_default_env();
  ASSERT_NE(env2, nullptr);

  leveldb_options_set_env(options_, env1);
  leveldb_options_set_env(options_, env2);

  // Should not crash; the last env set should be active
  leveldb_env_destroy(env1);
  leveldb_env_destroy(env2);
}

// Test setting env then nullptr then env again
TEST_F(LevelDBOptionsSetEnvTest_258, SetEnvThenNullThenEnvAgain_258) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);

  leveldb_options_set_env(options_, env);
  leveldb_options_set_env(options_, nullptr);
  leveldb_options_set_env(options_, env);

  // Should not crash
  leveldb_env_destroy(env);
}

// Test that setting the same env twice doesn't cause issues
TEST_F(LevelDBOptionsSetEnvTest_258, SetSameEnvTwice_258) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);

  leveldb_options_set_env(options_, env);
  leveldb_options_set_env(options_, env);

  // Should not crash or cause double-set issues
  leveldb_env_destroy(env);
}

// Test with freshly created options (env should have a default value initially)
TEST_F(LevelDBOptionsSetEnvTest_258, FreshOptionsDefaultEnv_258) {
  // A freshly created options object should have the default env
  // Setting a new env should override it
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);

  leveldb_options_set_env(options_, env);
  // No crash expected

  leveldb_env_destroy(env);
}

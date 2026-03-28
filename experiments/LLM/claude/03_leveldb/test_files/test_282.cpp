#include "gtest/gtest.h"

extern "C" {
#include "leveldb/c.h"
}

#include "leveldb/env.h"

// The struct definition from c.cc
struct leveldb_env_t {
  leveldb::Env* rep;
  bool is_default;
};

TEST(LevelDBCreateDefaultEnvTest_282, ReturnsNonNull_282) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  leveldb_env_destroy(env);
}

TEST(LevelDBCreateDefaultEnvTest_282, RepIsDefaultEnv_282) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  EXPECT_EQ(env->rep, leveldb::Env::Default());
  leveldb_env_destroy(env);
}

TEST(LevelDBCreateDefaultEnvTest_282, IsDefaultIsTrue_282) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  EXPECT_TRUE(env->is_default);
  leveldb_env_destroy(env);
}

TEST(LevelDBCreateDefaultEnvTest_282, MultipleCallsReturnDifferentObjects_282) {
  leveldb_env_t* env1 = leveldb_create_default_env();
  leveldb_env_t* env2 = leveldb_create_default_env();
  ASSERT_NE(env1, nullptr);
  ASSERT_NE(env2, nullptr);
  // Different wrapper objects
  EXPECT_NE(env1, env2);
  // But same underlying default env
  EXPECT_EQ(env1->rep, env2->rep);
  leveldb_env_destroy(env1);
  leveldb_env_destroy(env2);
}

TEST(LevelDBCreateDefaultEnvTest_282, RepIsNotNull_282) {
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  EXPECT_NE(env->rep, nullptr);
  leveldb_env_destroy(env);
}

TEST(LevelDBCreateDefaultEnvTest_282, DefaultEnvIsSingleton_282) {
  leveldb::Env* default_env = leveldb::Env::Default();
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);
  EXPECT_EQ(env->rep, default_env);
  leveldb_env_destroy(env);
}

TEST(LevelDBCreateDefaultEnvTest_282, CanBeUsedWithLevelDBOpen_282) {
  // Verify the created env can be set in options (basic integration sanity)
  leveldb_env_t* env = leveldb_create_default_env();
  ASSERT_NE(env, nullptr);

  leveldb_options_t* options = leveldb_options_create();
  ASSERT_NE(options, nullptr);

  // This should not crash
  leveldb_options_set_env(options, env);

  leveldb_options_destroy(options);
  leveldb_env_destroy(env);
}

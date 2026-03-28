// File: db/c_env_destroy_test.cc

#include <gtest/gtest.h>

// Minimal stand-ins to compile tests without inferring internals
struct Env { virtual ~Env() = default; };

// Match the production signatures exactly (no implementation here)
extern "C" {

// Mirror of the known struct layout (public fields as provided)
struct leveldb_env_t {
  Env* rep;
  bool is_default;
};

// Function under test (implemented in the production code)
void leveldb_env_destroy(leveldb_env_t* env);

}  // extern "C"

// Helper Env whose ctor/dtor effects are observable in tests
class TrackedEnv : public Env {
 public:
  TrackedEnv() { ++live_count; }
  ~TrackedEnv() override { ++destruct_count; --live_count; }

  static void ResetCounters() {
    live_count = 0;
    destruct_count = 0;
  }

  static int live_count;
  static int destruct_count;
};

int TrackedEnv::live_count = 0;
int TrackedEnv::destruct_count = 0;

// ---------- Tests ----------

TEST(LevelDBEnvDestroyTest_283, DeletesRepWhenNotDefault_283) {
  TrackedEnv::ResetCounters();

  // Arrange: env with a dynamically allocated rep and is_default == false
  auto* rep = new TrackedEnv();
  ASSERT_EQ(TrackedEnv::live_count, 1);
  ASSERT_EQ(TrackedEnv::destruct_count, 0);

  auto* env = new leveldb_env_t{rep, /*is_default=*/false};

  // Act
  leveldb_env_destroy(env);

  // Assert: rep must be deleted exactly once by the function
  EXPECT_EQ(TrackedEnv::live_count, 0);
  EXPECT_EQ(TrackedEnv::destruct_count, 1);

  // No further cleanup possible: env was deleted by the function.
  // If the function failed to delete rep, we'd observe live_count == 1 here.
}

TEST(LevelDBEnvDestroyTest_283, DoesNotDeleteRepWhenDefault_283) {
  TrackedEnv::ResetCounters();

  // Arrange: env with rep and is_default == true (rep is "owned" externally)
  auto* rep = new TrackedEnv();
  ASSERT_EQ(TrackedEnv::live_count, 1);
  ASSERT_EQ(TrackedEnv::destruct_count, 0);

  auto* env = new leveldb_env_t{rep, /*is_default=*/true};

  // Act
  leveldb_env_destroy(env);

  // Assert: rep must NOT be deleted by the function
  EXPECT_EQ(TrackedEnv::live_count, 1);
  EXPECT_EQ(TrackedEnv::destruct_count, 0);

  // Cleanup: since the function didn't delete rep, we remain responsible
  delete rep;
  EXPECT_EQ(TrackedEnv::live_count, 0);
  EXPECT_EQ(TrackedEnv::destruct_count, 1);
}

TEST(LevelDBEnvDestroyTest_283, HandlesNullRepPointerWhenNotDefault_283) {
  TrackedEnv::ResetCounters();

  // Arrange: env with null rep and is_default == false
  // Deleting a null pointer is a no-op in C++, so this should not crash.
  auto* env = new leveldb_env_t{/*rep=*/nullptr, /*is_default=*/false};

  // Act & Assert: should not crash; just delete env
  leveldb_env_destroy(env);

  // No destructor should have run for TrackedEnv
  EXPECT_EQ(TrackedEnv::live_count, 0);
  EXPECT_EQ(TrackedEnv::destruct_count, 0);
}

#if GTEST_HAS_DEATH_TEST
TEST(LevelDBEnvDestroyTest_283, NullEnvPointerCrashes_283) {
  // The implementation dereferences env without null-check.
  // Passing nullptr should cause a crash (undefined behavior / death).
  EXPECT_DEATH(
      {
        // Avoid optimizer removing the call
        auto* p = static_cast<leveldb_env_t*>(nullptr);
        leveldb_env_destroy(p);
      },
      ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

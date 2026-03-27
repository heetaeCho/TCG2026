// File: leveldb_cache_destroy_test_281.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// ---- Interface surfaced by the prompt (black-box to us) ----

// Minimal stand-in for the external collaborator type.
// We only rely on its existence and a virtual destructor so deletion
// through base pointer is observable. No internal behavior is assumed.
class Cache {
public:
  virtual ~Cache() = default;
};

// From the prompt:
struct leveldb_cache_t { Cache* rep; };

// Function under test (implemented elsewhere; we just declare it)
extern "C" void leveldb_cache_destroy(leveldb_cache_t* cache);

// ---- Test doubles & fixtures ----

class LeveldbCacheDestroyTest_281 : public ::testing::Test {};

// A simple test double that flips a flag when destroyed.
// This verifies that `delete cache->rep;` is actually invoked.
class DummyCache_281 : public Cache {
public:
  explicit DummyCache_281(bool* destroyed_flag) : flag_(destroyed_flag) {}
  ~DummyCache_281() override {
    if (flag_) *flag_ = true;
  }
private:
  bool* flag_;
};

// ---- Tests ----

// Normal operation: destroys the pointed-to Cache (via its destructor)
// and does not crash while also deleting the wrapper object.
TEST_F(LeveldbCacheDestroyTest_281, DestroysRepAndWrapper_281) {
  bool rep_destroyed = false;

  auto* wrapper = new leveldb_cache_t;
  wrapper->rep = new DummyCache_281(&rep_destroyed);

  // Act
  leveldb_cache_destroy(wrapper);

  // Assert: observable side-effect is that the rep's destructor ran.
  EXPECT_TRUE(rep_destroyed);
  // We cannot (and should not) access `wrapper` after destroy since it
  // should have been deleted as well.
}

// Boundary: safe when rep is nullptr. `delete nullptr;` is a no-op.
// We only assert it doesn't crash.
TEST_F(LeveldbCacheDestroyTest_281, NullRep_DoesNotCrash_281) {
  auto* wrapper = new leveldb_cache_t;
  wrapper->rep = nullptr;

  // Should not crash.
  leveldb_cache_destroy(wrapper);

  SUCCEED();  // Reached here without a crash is success.
}

// Exceptional/error case (observable): passing nullptr for `cache`
// dereferences a null pointer per the provided implementation.
// Verify this is a death condition.
TEST_F(LeveldbCacheDestroyTest_281, NullCachePointer_Death_281) {
#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH(
      {
        // NOLINTNEXTLINE(clang-analyzer-core.NullDereference)
        leveldb_cache_destroy(nullptr);
      },
      ".*");
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

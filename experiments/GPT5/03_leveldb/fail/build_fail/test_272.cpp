// tests/readoptions_create_test_272.cc
#include "gtest/gtest.h"
#include "leveldb/c.h"

// Test suite for leveldb_readoptions_create()
//
// Notes:
// - We only assert properties visible via the public C API.
// - We avoid any assumptions about internal structure or defaults.

TEST(ReadOptionsCreateTest_272, ReturnsNonNull_272) {
  leveldb_readoptions_t* opts = leveldb_readoptions_create();
  ASSERT_NE(opts, nullptr) << "leveldb_readoptions_create() must return a valid pointer";
  // Clean up via the public API if available.
#if defined(__has_include)
#  if __has_include("leveldb/c.h")
  // leveldb_readoptions_destroy is part of the standard C API; call it if present at link time.
#  endif
#endif
  leveldb_readoptions_destroy(opts);
}

TEST(ReadOptionsCreateTest_272, MultipleCallsReturnDistinctObjects_272) {
  leveldb_readoptions_t* a = leveldb_readoptions_create();
  leveldb_readoptions_t* b = leveldb_readoptions_create();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a, b) << "Each call to leveldb_readoptions_create() should allocate a distinct object";

  leveldb_readoptions_destroy(a);
  leveldb_readoptions_destroy(b);
}

TEST(ReadOptionsCreateTest_272, CreateThenDestroyDoesNotCrash_272) {
  // This validates the basic lifecycle: create -> destroy.
  // We cannot (and do not) assert on internal state; we only ensure no crash/UB is observable.
  leveldb_readoptions_t* opts = leveldb_readoptions_create();
  ASSERT_NE(opts, nullptr);
  EXPECT_NO_THROW({
    leveldb_readoptions_destroy(opts);
  });
}

// db/c_writeoptions_create_test_277.cc
#include <gtest/gtest.h>

// Only declare what's in the provided interface.
extern "C" {
  struct leveldb_writeoptions_t;
  leveldb_writeoptions_t* leveldb_writeoptions_create();
}

// NOTE: We intentionally do NOT delete/free the returned pointer because
// the prompt provides only the create() function and no corresponding
// destroy/free API. Per constraints, we avoid inferring internals.

TEST(LevelDB_WriteOptionsCreate_277, CreateReturnsNonNull_277) {
  leveldb_writeoptions_t* opts = leveldb_writeoptions_create();
  // Observable behavior: function should return a valid pointer.
  ASSERT_NE(opts, nullptr);
  // Intentionally no delete/free due to lack of a destroy API in the interface.
}

TEST(LevelDB_WriteOptionsCreate_277, CreateReturnsDistinctInstances_277) {
  leveldb_writeoptions_t* a = leveldb_writeoptions_create();
  leveldb_writeoptions_t* b = leveldb_writeoptions_create();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  // Observable behavior: separate calls yield distinct instances.
  EXPECT_NE(a, b);
  // No deletion, as explained above.
}

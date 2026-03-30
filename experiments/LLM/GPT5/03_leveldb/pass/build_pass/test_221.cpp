// File: db/c_close_test_221.cc

#include <gtest/gtest.h>

// We only need a forward declaration of DB to define leveldb_t.
class DB;

// Define the C API struct so we can allocate it in tests.
// This mirrors the public layout used by the implementation.
struct leveldb_t {
 public:
  DB* rep;
};

// Declare the function under test. In the real codebase this is provided
// by the C wrapper translation unit (db/c.cc).
extern "C" void leveldb_close(leveldb_t* db);

// -------------------- Tests --------------------

// [Boundary / Error] Passing a nullptr for `db` should crash since the function
// dereferences `db` (observable via a death test, without asserting any
// particular internal logic).
TEST(LeveldbCloseTest_221, NullDBPointer_Death_221) {
#if GTEST_HAS_DEATH_TEST
  EXPECT_DEATH(
      {
        // Intentionally pass nullptr to verify the program terminates.
        leveldb_close(nullptr);
      },
      ".*");
#else
  GTEST_SKIP() << "Death tests are not supported on this platform.";
#endif
}

// [Normal operation] Passing a valid `leveldb_t*` whose `rep` is null should
// complete without crashing (deleting a null pointer is safe). We allocate
// `leveldb_t` with `new` so that deleting it inside `leveldb_close` is valid.
TEST(LeveldbCloseTest_221, ValidStructWithNullRep_NoCrash_221) {
  // Allocate a valid wrapper object.
  leveldb_t* db = new leveldb_t();
  db->rep = nullptr;  // Observable setup: rep is null

  // If leveldb_close performs the expected deletes, this should not crash.
  // No assertions needed—crash-free completion is the observable behavior.
  leveldb_close(db);
}

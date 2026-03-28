// File: db/c_writebatch_destroy_test.cc

#include <gtest/gtest.h>

// Forward declarations only; we treat the implementation as opaque.
// Use C linkage to match typical LevelDB C API headers.
extern "C" {
  struct leveldb_writebatch_t;
  void leveldb_writebatch_destroy(leveldb_writebatch_t* b);
}

// Test suite focuses solely on observable behavior of the destroy function.
// We never construct a real leveldb_writebatch_t instance (that would require
// internal details). Safe, well-defined calls we can verify here are those
// involving nullptr.

// Verifies that destroying a null pointer is a no-op (no crash/exception).
TEST(WriteBatchDestroyTest_245, DestroyNullptr_NoCrash_245) {
  leveldb_writebatch_t* ptr = nullptr;
  // Expect: no crash, no exception; function returns void.
  leveldb_writebatch_destroy(ptr);
  SUCCEED();
}

// Verifies idempotent safety of calling destroy on nullptr multiple times.
TEST(WriteBatchDestroyTest_245, DestroyNullptrTwice_NoCrash_245) {
  leveldb_writebatch_t* ptr = nullptr;
  leveldb_writebatch_destroy(ptr);
  leveldb_writebatch_destroy(ptr);  // still nullptr
  SUCCEED();
}

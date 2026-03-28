// File: leveldb_options_destroy_test_252.cc

#include <gtest/gtest.h>

// We only need a forward declaration to pass (possibly null) pointers.
// Do not include or rely on any private/internal definitions.
extern "C" {
  struct leveldb_options_t;
  void leveldb_options_destroy(leveldb_options_t* options);
}

// ----------------------------------------------------------------------------
// NOTE ON SCOPE OF TESTS (black-box):
// Without a publicly provided creation API (e.g., leveldb_options_create())
// or a complete, constructible public definition of leveldb_options_t,
// we cannot safely produce a valid non-null instance to destroy.
// Therefore, we restrict tests to observable, spec-safe behavior available
// via the provided interface: handling of nullptr inputs.
// ----------------------------------------------------------------------------

TEST(LevelDBOptionsDestroy_252, DestroyNullptrIsNoop_252) {
  // Boundary case: nullptr should be safely handled.
  leveldb_options_t* ptr = nullptr;

  // Should not crash or throw.
  leveldb_options_destroy(ptr);

  SUCCEED();  // If we got here, behavior is as expected.
}

TEST(LevelDBOptionsDestroy_252, DestroyNullptrMultipleTimesIsNoop_252) {
  // Repeatedly destroying nullptr should remain a no-op.
  leveldb_options_t* ptr = nullptr;

  leveldb_options_destroy(ptr);
  leveldb_options_destroy(ptr);
  leveldb_options_destroy(ptr);

  SUCCEED();  // No crashes or exceptions == pass.
}

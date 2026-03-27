// File: block_iter_value_test_410.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/slice.h"
#include "leveldb/comparator.h"
#include "table/iterator.h"
#include "table/block.h"   // Assumes this header declares leveldb::Block::Iter

using ::testing::Test;

namespace leveldb {

class BlockIterValueTest_410 : public ::testing::Test {
protected:
  // Helper to construct an iterator in a minimal/empty configuration without
  // relying on internal encoding details. We never assume validity.
  Block::Iter MakeEmptyIter() {
    const Comparator* cmp = nullptr;      // Not used by value() precondition
    const char* data = nullptr;           // No data -> iterator remains invalid
    const uint32_t restarts = 0;
    const uint32_t num_restarts = 0;
    return Block::Iter(cmp, data, restarts, num_restarts);
  }
};

// value() must assert if called when !Valid().
// The iterator is freshly constructed and, by interface contract enforced via
// assert(Valid()), calling value() in an invalid state must die.
TEST_F(BlockIterValueTest_410, ValueOnFreshInvalidIterator_410) {
#if GTEST_HAS_DEATH_TEST
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  Block::Iter it = MakeEmptyIter();

  // We can check Valid() without assuming internal encoding behavior.
  // Regardless of its value, value() must assert if not valid.
  if (!it.Valid()) {
    ASSERT_DEATH_IF_SUPPORTED({ (void)it.value(); }, "");  // assert failure
  } else {
    GTEST_SKIP() << "Iterator unexpectedly valid in empty configuration; "
                    "test only targets invalid-precondition behavior.";
  }
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

// After SeekToFirst() on an empty/minimal iterator, value() must still assert
// if the iterator is not valid.
TEST_F(BlockIterValueTest_410, ValueAfterSeekToFirstWhenInvalid_410) {
#if GTEST_HAS_DEATH_TEST
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  Block::Iter it = MakeEmptyIter();
  it.SeekToFirst();

  if (!it.Valid()) {
    ASSERT_DEATH_IF_SUPPORTED({ (void)it.value(); }, "");
  } else {
    GTEST_SKIP() << "Iterator became valid; this test only covers invalid case.";
  }
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

// After Seek(target) on an empty/minimal iterator, value() must assert if the
// iterator remains invalid.
TEST_F(BlockIterValueTest_410, ValueAfterSeekTargetWhenInvalid_410) {
#if GTEST_HAS_DEATH_TEST
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  Block::Iter it = MakeEmptyIter();
  it.Seek(Slice("any-target"));

  if (!it.Valid()) {
    ASSERT_DEATH_IF_SUPPORTED({ (void)it.value(); }, "");
  } else {
    GTEST_SKIP() << "Iterator became valid; this test only covers invalid case.";
  }
#else
  GTEST_SKIP() << "Death tests not supported on this platform.";
#endif
}

}  // namespace leveldb

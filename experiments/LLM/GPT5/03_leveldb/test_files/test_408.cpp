// File: block_iter_status_test_408.cc

#include "gtest/gtest.h"

// Pull in the partial implementation so we can name leveldb::Block::Iter.
// (We do NOT rely on or re-implement internal logic; we only call public APIs.)
#include "table/block.cc"

namespace {

using leveldb::Block;

// A minimal fixture (not strictly necessary, but keeps naming consistent).
class BlockIterStatusTest_408 : public ::testing::Test {};

// --- Tests ---

// [Normal] Immediately after construction, status() should be callable and
// should report an OK status for a fresh iterator.
TEST_F(BlockIterStatusTest_408, DefaultStatusIsOk_408) {
  // Construct with minimal, safe inputs.
  const leveldb::Comparator* cmp = nullptr;  // Not used by status()
  const char* data = nullptr;                // No data needed to query status()
  const uint32_t restarts = 0;
  const uint32_t num_restarts = 0;

  Block::Iter it(cmp, data, restarts, num_restarts);

  // Observable behavior: status() returns a Status.
  // For a fresh iterator, LevelDB iterators typically start OK.
  EXPECT_TRUE(it.status().ok());
}

// [Stability] Calling status() multiple times should be stable (no mutation).
TEST_F(BlockIterStatusTest_408, StatusStableAcrossCalls_408) {
  const leveldb::Comparator* cmp = nullptr;
  const char* data = nullptr;
  Block::Iter it(cmp, data, /*restarts=*/0, /*num_restarts=*/0);

  auto s1 = it.status();
  auto s2 = it.status();

  // We compare string forms to avoid relying on internal fields.
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

// [Boundary] status() should be available and OK even when the iterator is not
// positioned on a valid entry (e.g., empty construction parameters).
TEST_F(BlockIterStatusTest_408, StatusOkWhenIteratorIsInvalid_408) {
  const leveldb::Comparator* cmp = nullptr;
  const char* data = nullptr;
  Block::Iter it(cmp, data, /*restarts=*/0, /*num_restarts=*/0);

  // Valid() is an observable property exposed by the interface.
  // The iterator may be invalid before any positioning.
  EXPECT_FALSE(it.Valid());

  // Regardless of validity, status() should be callable and (for this case) OK.
  EXPECT_TRUE(it.status().ok());
}

// [Boundary/Robustness] Construct with non-null data pointer but zero sizes.
// status() should still be callable and stable.
TEST_F(BlockIterStatusTest_408, StatusCallableWithUnusedDataPointer_408) {
  const leveldb::Comparator* cmp = nullptr;
  static const char dummy[4] = {0, 0, 0, 0};
  Block::Iter it(cmp, dummy, /*restarts=*/0, /*num_restarts=*/0);

  // Call status() multiple times; it should neither crash nor change.
  auto s1 = it.status();
  auto s2 = it.status();
  EXPECT_EQ(s1.ToString(), s2.ToString());
  EXPECT_TRUE(s1.ok());
}

}  // namespace

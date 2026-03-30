// File: block_iter_valid_test.cc

#include <cstdint>
#include "gtest/gtest.h"

// Use the real LevelDB headers from your codebase.
// If your project layout differs, adjust these includes accordingly.
#include "table/block.h"           // declares leveldb::Block and Block::Iter
#include "leveldb/comparator.h"    // declares leveldb::Comparator

namespace leveldb {

class BlockIterValidTest_407 : public ::testing::Test {
protected:
  // Helper to construct an iterator with given restart metadata.
  // Per the visible interface, the constructor requires a Comparator*,
  // a data pointer, and the restart metadata. We pass nullptrs for
  // comparator and data since Valid() does not expose any use of them.
  static Block::Iter MakeIter(uint32_t restarts, uint32_t num_restarts) {
    const Comparator* cmp = nullptr;
    const char* data = nullptr;
    return Block::Iter(cmp, data, restarts, num_restarts);
  }
};

// Verifies that a freshly constructed iterator reports invalid via Valid().
// (Normal operation: default/initial state)
TEST_F(BlockIterValidTest_407, ConstructedIter_IsInvalidInitially_407) {
  auto it = MakeIter(/*restarts=*/3, /*num_restarts=*/3);
  EXPECT_FALSE(it.Valid());
}

// Boundary: restarts == 0 should still yield a consistent, observable result for Valid().
TEST_F(BlockIterValidTest_407, ValidWithZeroRestarts_407) {
  auto it = MakeIter(/*restarts=*/0, /*num_restarts=*/0);
  EXPECT_FALSE(it.Valid());
}

// Boundary: very large restarts value should not change the initial invalid state.
TEST_F(BlockIterValidTest_407, ValidWithLargeRestarts_407) {
  auto it = MakeIter(/*restarts=*/std::numeric_limits<uint32_t>::max(),
                     /*num_restarts=*/std::numeric_limits<uint32_t>::max());
  EXPECT_FALSE(it.Valid());
}

// Idempotence/consistency: multiple calls to Valid() should not change its observable result.
TEST_F(BlockIterValidTest_407, ValidIsIdempotent_407) {
  auto it = MakeIter(/*restarts=*/5, /*num_restarts=*/2);
  EXPECT_FALSE(it.Valid());
  EXPECT_FALSE(it.Valid());  // repeat to ensure no side effects from calling Valid()
}

}  // namespace leveldb

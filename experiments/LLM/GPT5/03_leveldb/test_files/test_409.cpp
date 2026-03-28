// File: block_iter_key_test_409.cc

#include <gtest/gtest.h>
#include "leveldb/iterator.h"   // Iterator/Slice declarations (from your codebase)
#include "table/block.h"        // Or the header that exposes leveldb::Block::Iter

using leveldb::Block;

// A small test fixture to keep naming consistent.
class BlockIterKeyTest_409 : public ::testing::Test {
protected:
  // Helper to make an Iter in a clearly invalid state (no data).
  // We pass nullptr comparator and data, with zero restarts.
  static Block::Iter MakeInvalidIter() {
    const leveldb::Comparator* cmp = nullptr;
    const char* data = nullptr;
    uint32_t restarts = 0;
    uint32_t num_restarts = 0;
    return Block::Iter(cmp, data, restarts, num_restarts);
  }
};

// Death tests need this on some platforms.
#if GTEST_HAS_DEATH_TEST
TEST_F(BlockIterKeyTest_409, KeyOnInvalidIterator_TriggersAssert_409) {
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";

  auto it = MakeInvalidIter();
  ASSERT_FALSE(it.Valid()) << "Precondition: iterator should start invalid with empty inputs";

  // Contract: key() asserts if !Valid()
  EXPECT_DEATH({ (void)it.key(); }, "");  // empty regex: accept any assert/abort message
}
#endif  // GTEST_HAS_DEATH_TEST

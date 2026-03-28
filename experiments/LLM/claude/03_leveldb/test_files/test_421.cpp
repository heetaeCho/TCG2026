#include "gtest/gtest.h"
#include "leveldb/slice.h"
#include "table/block.h"

// We need to access the DeleteCachedBlock function.
// Since it's a static function in table.cc, we need to either:
// 1. Include the source file directly, or
// 2. Declare it as accessible somehow.
// For testing purposes, we'll work with what we can observe.

// Since DeleteCachedBlock is a static (file-local) function in table.cc,
// it's not directly accessible from outside. However, we can test it
// indirectly through the Table interface, or we can include the .cc file
// to access it for unit testing purposes.

// For this test, we include the implementation file to access the static function.
// In practice, this is a common technique for testing static/file-local functions.

namespace leveldb {

// Forward declare the static function by including the source or re-declaring
// We'll use a workaround: define a test helper that calls into the function
// through the cache mechanism, or directly test observable behavior.

// Since DeleteCachedBlock is static in table.cc, we test it by including
// the translation unit. We declare it here for test access.
// Note: In a real build system, you might need to expose this differently.

static void DeleteCachedBlock(const Slice& key, void* value);

}  // namespace leveldb

// Include the actual implementation to get access to the static function
#include "table/table.cc"

namespace leveldb {

class DeleteCachedBlockTest_421 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that DeleteCachedBlock correctly deletes a dynamically allocated Block
// without crashing (normal operation).
TEST_F(DeleteCachedBlockTest_421, DeletesValidBlock_421) {
  // Create block contents for a valid Block
  BlockContents contents;
  contents.data = Slice("test_data", 9);
  contents.cachable = false;
  contents.heap_allocated = false;

  // Allocate a Block on the heap
  Block* block = new Block(contents);
  ASSERT_NE(block, nullptr);

  Slice key("test_key");

  // Call DeleteCachedBlock - should delete the block without crashing
  // If it doesn't properly delete, we'd get a memory leak (detectable by sanitizers)
  EXPECT_NO_FATAL_FAILURE(DeleteCachedBlock(key, reinterpret_cast<void*>(block)));
}

// Test with an empty key slice
TEST_F(DeleteCachedBlockTest_421, DeletesBlockWithEmptyKey_421) {
  BlockContents contents;
  contents.data = Slice("some_block_data", 15);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block* block = new Block(contents);
  ASSERT_NE(block, nullptr);

  Slice empty_key;

  // Should still delete the block without issues - key is not used for deletion logic
  EXPECT_NO_FATAL_FAILURE(DeleteCachedBlock(empty_key, reinterpret_cast<void*>(block)));
}

// Test with a nullptr value - this would be a boundary/error case
// Note: Passing nullptr will cause delete on nullptr which is safe in C++
TEST_F(DeleteCachedBlockTest_421, HandlesNullValue_421) {
  Slice key("some_key");

  // Deleting nullptr is well-defined in C++ (no-op)
  EXPECT_NO_FATAL_FAILURE(DeleteCachedBlock(key, nullptr));
}

// Test with a large key to ensure key parameter doesn't affect deletion
TEST_F(DeleteCachedBlockTest_421, DeletesBlockWithLargeKey_421) {
  BlockContents contents;
  contents.data = Slice("data", 4);
  contents.cachable = false;
  contents.heap_allocated = false;

  Block* block = new Block(contents);

  std::string large_key(10000, 'x');
  Slice key(large_key);

  EXPECT_NO_FATAL_FAILURE(DeleteCachedBlock(key, reinterpret_cast<void*>(block)));
}

// Test that multiple sequential deletions work fine
TEST_F(DeleteCachedBlockTest_421, MultipleSequentialDeletions_421) {
  for (int i = 0; i < 10; i++) {
    BlockContents contents;
    std::string data = "block_data_" + std::to_string(i);
    contents.data = Slice(data);
    contents.cachable = false;
    contents.heap_allocated = false;

    Block* block = new Block(contents);
    Slice key("key_" + std::to_string(i));

    EXPECT_NO_FATAL_FAILURE(DeleteCachedBlock(key, reinterpret_cast<void*>(block)));
  }
}

}  // namespace leveldb

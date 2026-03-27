// File: block_destructor_ownership_test_405.cc

#include <gtest/gtest.h>
#include <type_traits>

// Pull in the real interfaces (treat the class as a black box).
#include "table/block.h"
#include "leveldb/slice.h"

namespace {

using leveldb::Block;
using leveldb::BlockContents;
using leveldb::Slice;

// --- Compile-time interface checks (no internal logic inferred) ---

// Copying and assignment must be deleted per the provided interface.
static_assert(!std::is_copy_constructible<Block>::value,
              "Block should not be copy-constructible");
static_assert(!std::is_copy_assignable<Block>::value,
              "Block should not be copy-assignable");

class BlockTest_405 : public ::testing::Test {};

// --- Runtime observable-behavior tests ---

// Normal operation: size() should equal the byte length provided via contents.data.size().
TEST_F(BlockTest_405, SizeReflectsInputDataLength_405) {
  // Arrange: prepare an external buffer and wrap it in a Slice.
  const char kData[] = "abcdef";  // 6 bytes before the null terminator.
  BlockContents contents{Slice(kData, 6), /*cachable=*/false, /*heap_allocated=*/false};

  // Act: construct the block.
  Block block(contents);

  // Assert: size() reports the same length given in contents.data.size().
  EXPECT_EQ(block.size(), static_cast<size_t>(6));
}

// Boundary / ownership behavior: when heap_allocated == true, Block owns the memory
// and must delete[] it on destruction. We verify by *not* deleting the buffer ourselves
// and asserting that the test process does not crash/leak observably during destruction.
TEST_F(BlockTest_405, DestructorDeletesWhenOwned_405) {
  // Arrange: allocate a raw buffer the Block is allowed to delete[].
  const size_t n = 3;
  char* buf = new char[n];
  buf[0] = 'x'; buf[1] = 'y'; buf[2] = 'z';

  // Important: Slice points to our raw buffer; BlockContents marks ownership true.
  BlockContents contents{Slice(buf, n), /*cachable=*/false, /*heap_allocated=*/true};

  // Act & Assert: construct and destroy without freeing buf ourselves.
  // If Block fails to delete[] when owned, you'll leak; if it double-frees, you'd crash.
  // Either would be observable under sanitizers; here we only assert that destruction is safe.
  Block* blk = new Block(contents);
  ASSERT_NE(blk, nullptr);
  delete blk;

  // No explicit EXPECT here: success == no crash.
}

// Boundary / ownership behavior: when heap_allocated == false, Block must NOT delete the memory.
// We verify by deleting the buffer ourselves after the Block is destroyed; if Block incorrectly
// deleted it, this would be a double free and crash the test process.
TEST_F(BlockTest_405, DestructorDoesNotDeleteWhenNotOwned_405) {
  // Arrange: allocate a raw buffer that we will retain ownership of.
  const size_t n = 4;
  char* buf = new char[n];
  buf[0] = 'a'; buf[1] = 'b'; buf[2] = 'c'; buf[3] = 'd';

  BlockContents contents{Slice(buf, n), /*cachable=*/false, /*heap_allocated=*/false};

  // Act: construct the block with non-owned memory, then destroy it.
  {
    Block block(contents);
    EXPECT_EQ(block.size(), static_cast<size_t>(n));  // sanity check: observable behavior
  }  // block destroyed here; must NOT have deleted buf

  // Assert: now we delete the buffer; if Block had deleted it, this would double-free and crash.
  delete[] buf;

  SUCCEED();  // Reaching here indicates no double free occurred.
}

// (Optional sanity) Creating a very small block (including zero-length) should not crash.
// This tests a boundary for size reporting without inferring internals.
TEST_F(BlockTest_405, ZeroLengthDataIsHandled_Gracefully_405) {
  const char* p = nullptr;  // pointer value should be irrelevant for zero length
  BlockContents contents{Slice(p, 0), /*cachable=*/false, /*heap_allocated=*/false};

  Block block(contents);
  EXPECT_EQ(block.size(), static_cast<size_t>(0));
}

}  // namespace

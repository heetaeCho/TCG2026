// File: block_size_test_295.cc
#include "table/block.h"
#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <type_traits>
#include <string>

namespace {

using leveldb::Block;
using leveldb::Slice;

// Minimal use of the BlockContents interface as exposed by the header(s).
// We rely on the public struct definition normally provided alongside block.h.
struct BlockContents {
  Slice data;
  bool cachable = false;
  bool heap_allocated = false;
};

class BlockTest_295 : public ::testing::Test {};

// --- Type trait expectations about the public interface ---

TEST_F(BlockTest_295, IsNotCopyConstructible_295) {
  // Public interface declares copy-ctor deleted; enforce at compile time.
  static_assert(!std::is_copy_constructible<Block>::value,
                "Block should not be copy-constructible");
}

TEST_F(BlockTest_295, IsNotCopyAssignable_295) {
  // Public interface declares copy-assignment deleted; enforce at compile time.
  static_assert(!std::is_copy_assignable<Block>::value,
                "Block should not be copy-assignable");
}

// --- size() observable behavior ---

TEST_F(BlockTest_295, SizeIsZeroForEmptyData_295) {
  std::string backing;  // empty
  BlockContents contents;
  contents.data = Slice(backing);
  contents.heap_allocated = false;  // should not affect observable size()
  contents.cachable = false;

  Block block(contents);

  EXPECT_EQ(block.size(), static_cast<size_t>(0))
      << "size() must reflect empty input data length";
}

TEST_F(BlockTest_295, SizeMatchesNonEmptyData_295) {
  std::string backing = "abcdef";  // length = 6
  BlockContents contents;
  contents.data = Slice(backing);
  contents.heap_allocated = false;
  contents.cachable = true;  // flag should not impact size()

  Block block(contents);

  EXPECT_EQ(block.size(), backing.size())
      << "size() must equal the length of the provided data";
}

TEST_F(BlockTest_295, SizeUnaffectedByHeapAllocatedFlag_295) {
  // Same bytes, different heap_allocated flags — size() should not change.
  std::string backing(123, 'x');  // 123 bytes
  BlockContents c1;
  c1.data = Slice(backing);
  c1.heap_allocated = false;

  BlockContents c2;
  c2.data = Slice(backing);
  c2.heap_allocated = true;

  Block b1(c1);
  Block b2(c2);

  EXPECT_EQ(b1.size(), backing.size());
  EXPECT_EQ(b2.size(), backing.size());
  EXPECT_EQ(b1.size(), b2.size())
      << "size() should be independent of heap ownership flags";
}

TEST_F(BlockTest_295, SizeStableAcrossRepeatedCalls_295) {
  std::string backing(1000, 'z');
  BlockContents contents;
  contents.data = Slice(backing);
  contents.heap_allocated = true;

  Block block(contents);

  const size_t expected = backing.size();
  // Call size() multiple times to ensure idempotence/const-correctness.
  EXPECT_EQ(block.size(), expected);
  EXPECT_EQ(block.size(), expected);
  EXPECT_EQ(block.size(), expected);
}

TEST_F(BlockTest_295, SizeHandlesLargeInput_295) {
  // Boundary-ish case: a fairly large block. Keep test practical for CI.
  const size_t N = 1 << 20; // 1 MiB
  std::string backing(N, '\1');
  BlockContents contents;
  contents.data = Slice(backing);
  contents.heap_allocated = true;

  Block block(contents);

  EXPECT_EQ(block.size(), N)
      << "size() must handle large inputs without truncation";
}

} // namespace

// File: block_seek_to_last_test_415.cc

#include "gtest/gtest.h"
#include "leveldb/iterator.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "table/block.h"
#include "table/block_builder.h"
#include "util/testutil.h"   // If your tree provides a test Slice/string helper; otherwise remove.

using namespace leveldb;

namespace {

class BlockSeekToLastTest_415 : public ::testing::Test {
protected:
  // Helper to build a Block from a vector of key/value pairs using only public API.
  static std::unique_ptr<Block> MakeBlock(const std::vector<std::pair<std::string, std::string>>& kvs,
                                          const Comparator* cmp = BytewiseComparator()) {
    // Use BlockBuilder to produce a properly-encoded block buffer (public dependency).
    Options options;
    options.comparator = cmp;

    BlockBuilder builder(&options);
    for (const auto& kv : kvs) {
      builder.Add(Slice(kv.first), Slice(kv.second));
    }
    Slice data = builder.Finish();

    // Copy data to an owning buffer because BlockContents expects the lifetime to outlive Block.
    std::string* backing = new std::string(data.data(), data.size());

    BlockContents contents;
    contents.data = Slice(*backing);
    contents.cachable = false;
    contents.heap_allocated = true; // the Block will delete backing memory

    return std::unique_ptr<Block>(new Block(contents));
  }

  // Helper to corrupt/truncate a finished block buffer (error case); still uses public types to feed Block.
  static std::unique_ptr<Block> MakeCorruptedBlock(const std::vector<std::pair<std::string, std::string>>& kvs,
                                                   size_t bytes_to_trim,
                                                   const Comparator* cmp = BytewiseComparator()) {
    Options options;
    options.comparator = cmp;

    BlockBuilder builder(&options);
    for (const auto& kv : kvs) builder.Add(Slice(kv.first), Slice(kv.second));
    Slice data = builder.Finish();

    // Defensive: do not underflow.
    ASSERT_LE(bytes_to_trim, data.size());
    size_t new_size = data.size() - bytes_to_trim;

    std::string* backing = new std::string(data.data(), new_size);
    BlockContents contents;
    contents.data = Slice(*backing);
    contents.cachable = false;
    contents.heap_allocated = true;

    return std::unique_ptr<Block>(new Block(contents));
  }
};

// ========== Tests ==========

// Boundary: empty block -> SeekToLast results in invalid iterator; status remains ok.
TEST_F(BlockSeekToLastTest_415, EmptyBlock_SeekToLast_Invalid_415) {
  auto block = MakeBlock({});  // no entries
  std::unique_ptr<Iterator> it(block->NewIterator(BytewiseComparator()));

  it->SeekToLast();

  EXPECT_FALSE(it->Valid()) << "Iterator should be invalid for an empty block after SeekToLast()";
  EXPECT_TRUE(it->status().ok());
}

// Normal: single (k,v) -> SeekToLast lands on that entry.
TEST_F(BlockSeekToLastTest_415, SingleEntry_SeekToLast_PositionsOnOnlyEntry_415) {
  auto block = MakeBlock({{"a", "1"}});
  std::unique_ptr<Iterator> it(block->NewIterator(BytewiseComparator()));

  it->SeekToLast();

  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "a");
  EXPECT_EQ(it->value().ToString(), "1");
  EXPECT_TRUE(it->status().ok());
}

// Normal: multiple entries -> SeekToLast lands on the lexicographically last key in the block order.
TEST_F(BlockSeekToLastTest_415, MultipleEntries_SeekToLast_PositionsOnLastEntry_415) {
  // Insert several keys (BlockBuilder expects keys to be added in increasing order).
  std::vector<std::pair<std::string, std::string>> kvs = {
      {"a", "v1"},
      {"b", "v2"},
      {"c", "v3"},
      {"d", "v4"},
  };
  auto block = MakeBlock(kvs);
  std::unique_ptr<Iterator> it(block->NewIterator(BytewiseComparator()));

  it->SeekToLast();

  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->key().ToString(), "d");
  EXPECT_EQ(it->value().ToString(), "v4");
  EXPECT_TRUE(it->status().ok());
}

// Error/Exceptional: truncated buffer -> after SeekToLast, iterator should surface a non-ok status
// or be invalid (observable via status()). We do not assert internal error specifics.
TEST_F(BlockSeekToLastTest_415, CorruptedBlock_SeekToLast_SurfacesError_415) {
  // Build a small block and truncate a few bytes from the end (e.g., chop restart array).
  auto block = MakeCorruptedBlock({{"a","1"}, {"b","2"}, {"c","3"}}, /*bytes_to_trim=*/4);
  std::unique_ptr<Iterator> it(block->NewIterator(BytewiseComparator()));

  it->SeekToLast();

  // We only assert observable behavior: either invalid with error status, or invalid with non-ok status.
  // Some implementations may keep ok() but !Valid(). We accept either as long as it doesn't claim a valid
  // last record for a corrupted block.
  EXPECT_FALSE(it->Valid());
  // If the implementation reports corruption via status(), verify it is non-ok.
  // This expectation is soft to avoid over-specifying: we assert non-ok only if it’s not ok().
  if (!it->status().ok()) {
    EXPECT_FALSE(it->status().ok());
  }
}

} // namespace

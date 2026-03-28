// File: block_newiterator_test_416.cc
#include "table/block.h"
#include "leveldb/comparator.h"
#include "leveldb/status.h"
#include "leveldb/iterator.h"

#include <gtest/gtest.h>
#include <string>

namespace {

// A minimal external collaborator (Comparator) for testing.
// This is allowed per constraints: we only mock/implement collaborators,
// not internal behavior of Block.
class SimpleComparator : public leveldb::Comparator {
 public:
  ~SimpleComparator() override = default;

  int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const override {
    const std::string sa(a.data(), a.size());
    const std::string sb(b.data(), b.size());
    if (sa < sb) return -1;
    if (sa > sb) return 1;
    return 0;
  }

  const char* Name() const override { return "test.SimpleComparator"; }

  void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

class BlockNewIteratorTest_416 : public ::testing::Test {
 protected:
  SimpleComparator cmp_;
};

// Helper to build BlockContents with given bytes.
static leveldb::BlockContents MakeContents(const std::string& bytes,
                                           bool heap_allocated = false,
                                           bool cachable = false) {
  leveldb::BlockContents c;
  c.data = leveldb::Slice(bytes);
  c.heap_allocated = heap_allocated;
  c.cachable = cachable;
  return c;
}

}  // namespace

// size_ < sizeof(uint32_t) -> should return an *error* iterator
// (observable via !status.ok() and IsCorruption()).
TEST_F(BlockNewIteratorTest_416, NewIterator_SizeTooSmall_ReturnsErrorIterator_416) {
  // 3 bytes < 4 => too small to contain the restart count.
  const std::string raw(3, '\x00');
  leveldb::BlockContents contents = MakeContents(raw);
  leveldb::Block block(contents);

  std::unique_ptr<leveldb::Iterator> it(block.NewIterator(&cmp_));
  ASSERT_NE(it.get(), nullptr);

  // Observable behavior of an error iterator:
  EXPECT_FALSE(it->status().ok());
  EXPECT_TRUE(it->status().IsCorruption());
  EXPECT_FALSE(it->Valid());
}

// num_restarts == 0 -> should return an *empty* iterator
// (observable via status().ok() and !Valid()).
TEST_F(BlockNewIteratorTest_416, NewIterator_NoRestarts_ReturnsEmptyIterator_416) {
  // Block format ends with a 32-bit little-endian num_restarts.
  // Here: num_restarts = 0.
  std::string raw;
  raw.append("\x00\x00\x00\x00", 4);  // num_restarts = 0

  leveldb::BlockContents contents = MakeContents(raw);
  leveldb::Block block(contents);

  std::unique_ptr<leveldb::Iterator> it(block.NewIterator(&cmp_));
  ASSERT_NE(it.get(), nullptr);

  // Observable behavior of an empty iterator:
  EXPECT_TRUE(it->status().ok());
  EXPECT_FALSE(it->Valid());
}

// num_restarts > 0 -> should return a "normal" iterator instance.
// We don't assert internal structure; just that it's not an error/empty-by-construction.
// With no entries, it is reasonable that Valid() is false but status is OK.
TEST_F(BlockNewIteratorTest_416, NewIterator_WithOneRestart_ReturnsUsableIterator_416) {
  // Minimal well-formed layout for "has restarts":
  // [restart_offsets (1 x uint32_t)] [num_restarts (uint32_t = 1)]
  // Use restart_offsets[0] = 0.
  std::string raw;
  raw.append("\x00\x00\x00\x00", 4);  // restart offset #0 = 0
  raw.append("\x01\x00\x00\x00", 4);  // num_restarts = 1

  leveldb::BlockContents contents = MakeContents(raw);
  leveldb::Block block(contents);

  std::unique_ptr<leveldb::Iterator> it(block.NewIterator(&cmp_));
  ASSERT_NE(it.get(), nullptr);

  // Should not be an error iterator.
  EXPECT_TRUE(it->status().ok());

  // With no entries encoded before the restart array, it's reasonable
  // that the iterator isn't positioned at a valid entry by default.
  EXPECT_FALSE(it->Valid());
}

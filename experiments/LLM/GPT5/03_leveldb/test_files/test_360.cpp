// File: db/memtable_iterator_seek_to_last_test.cc

#include "db/memtable.h"
#include "db/dbformat.h"
#include "include/leveldb/comparator.h"
#include "include/leveldb/iterator.h"
#include "gtest/gtest.h"

namespace leveldb {

class MemTableIteratorTest_360 : public ::testing::Test {
protected:
  InternalKeyComparator icmp_{BytewiseComparator()};
  // Fresh MemTable per test (black-box usage through public API).
  MemTable mem_{icmp_};

  // Helper: materialize an iterator for current memtable state.
  std::unique_ptr<Iterator> NewIt() {
    return std::unique_ptr<Iterator>(mem_.NewIterator());
  }

  // Helper: insert KV as a regular value with increasing sequence.
  void Put(uint64_t seq, const Slice& key, const Slice& value) {
    mem_.Add(seq, kTypeValue, key, value);
  }
};

// Normal operation: multiple entries → SeekToLast lands on last user key.
TEST_F(MemTableIteratorTest_360, SeekToLast_MultipleEntries_360) {
  Put(1, "a", "A");
  Put(2, "b", "B");
  Put(3, "c", "C");  // lexicographically last user key

  auto it = NewIt();
  it->SeekToLast();

  ASSERT_TRUE(it->Valid()) << "Iterator should be valid after SeekToLast()";
  // We assert on value (observable via public API) rather than decoding internal key.
  EXPECT_EQ(it->value().ToString(), "C");
}

// Boundary: single entry → SeekToLast should land on that entry.
TEST_F(MemTableIteratorTest_360, SeekToLast_SingleEntry_360) {
  Put(42, "only", "ONE");

  auto it = NewIt();
  it->SeekToLast();

  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->value().ToString(), "ONE");
}

// Exceptional/edge case: empty memtable → SeekToLast yields invalid iterator.
TEST_F(MemTableIteratorTest_360, SeekToLast_EmptyTable_IsInvalid_360) {
  auto it = NewIt();
  it->SeekToLast();
  EXPECT_FALSE(it->Valid());
}

// Postcondition behavior: after SeekToLast, Next() should move past end.
TEST_F(MemTableIteratorTest_360, SeekToLast_FollowedByNext_GoesInvalid_360) {
  Put(10, "k1", "v1");
  Put(11, "k2", "v2");

  auto it = NewIt();
  it->SeekToLast();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(it->value().ToString(), "v2");  // last key's value

  it->Next();
  EXPECT_FALSE(it->Valid()) << "Advancing from last should invalidate the iterator";
}

}  // namespace leveldb

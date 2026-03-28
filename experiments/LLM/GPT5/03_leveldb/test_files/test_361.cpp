// File: memtable_iterator_next_test.cc

#include "db/memtable.h"
#include "db/dbformat.h"
#include "util/coding.h"
#include "util/testutil.h"
#include "gtest/gtest.h"

using namespace leveldb;

class MemTableIteratorNextTest_361 : public ::testing::Test {
protected:
  // Typical LevelDB setup: InternalKeyComparator using the default BytewiseComparator
  InternalKeyComparator icmp_{BytewiseComparator()};
  // Arena-owned memtable
  MemTable mem_{icmp_};

  void SetUp() override {
    mem_.Ref();  // MemTable requires manual ref management in tests
  }

  void TearDown() override {
    mem_.Unref();
  }

  // Helper to add a simple user-key/value pair as a kTypeValue at a given seq
  void Put(uint64_t seq, const std::string& ukey, const std::string& value) {
    InternalKey ikey(ukey, seq, kTypeValue);
    mem_.Add(seq, kTypeValue, Slice(ukey), Slice(value));
  }

  // Extract user key from an internal key Slice returned by iterator->key()
  static std::string UserKeyFromInternal(const Slice& internal_key) {
    ParsedInternalKey pik;
    // Parsing is part of the public interface in dbformat and does not assume memtable internals
    bool ok = ParseInternalKey(internal_key, &pik);
    EXPECT_TRUE(ok);  // If this fails, the test environment is misconfigured
    return pik.user_key.ToString();
  }
};

// Normal iteration from first to end
TEST_F(MemTableIteratorNextTest_361, NextWalksForward_361) {
  // Arrange
  Put(3, "a", "1");
  Put(2, "b", "2");
  Put(1, "c", "3");

  std::unique_ptr<Iterator> it(mem_.NewIterator());
  it->SeekToFirst();

  // Assert initial position
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("a", UserKeyFromInternal(it->key()));
  EXPECT_EQ("1", it->value().ToString());

  // Act + Assert step 1
  it->Next();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("b", UserKeyFromInternal(it->key()));
  EXPECT_EQ("2", it->value().ToString());

  // Act + Assert step 2
  it->Next();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("c", UserKeyFromInternal(it->key()));
  EXPECT_EQ("3", it->value().ToString());

  // Act + Assert step 3 (past last)
  it->Next();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

// Boundary: Next() on the last element yields invalid, and repeated Next() stays invalid
TEST_F(MemTableIteratorNextTest_361, NextPastEndRemainsInvalid_361) {
  Put(1, "k", "v");

  std::unique_ptr<Iterator> it(mem_.NewIterator());
  it->SeekToLast();

  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("k", UserKeyFromInternal(it->key()));
  EXPECT_EQ("v", it->value().ToString());

  // Move to invalid by stepping past the end
  it->Next();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());

  // Repeated Next() should keep iterator invalid and not crash
  it->Next();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

// Edge: Next() on an empty table should be a no-op (remain invalid) and keep status OK
TEST_F(MemTableIteratorNextTest_361, NextOnEmptyTableKeepsInvalid_361) {
  std::unique_ptr<Iterator> it(mem_.NewIterator());

  // No seek yet; iterator is typically invalid until positioned.
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());

  // Calling Next() on an invalid iterator should not crash and should remain invalid.
  it->Next();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());

  // SeekToFirst() still leaves it invalid because the table is empty
  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

// Seek + Next: advancing from a middle key reaches the immediate successor
TEST_F(MemTableIteratorNextTest_361, NextAfterSeekMovesToImmediateSuccessor_361) {
  Put(5, "apple",  "x");
  Put(4, "banana", "y");
  Put(3, "cherry", "z");
  Put(2, "date",   "w");

  std::unique_ptr<Iterator> it(mem_.NewIterator());

  // Position at "banana"
  it->Seek(InternalKey("banana", /*seq=*/9, kTypeValue).Encode());
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("banana", UserKeyFromInternal(it->key()));
  EXPECT_EQ("y", it->value().ToString());

  // Next -> "cherry"
  it->Next();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("cherry", UserKeyFromInternal(it->key()));
  EXPECT_EQ("z", it->value().ToString());

  // Next -> "date"
  it->Next();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("date", UserKeyFromInternal(it->key()));
  EXPECT_EQ("w", it->value().ToString());

  // Next -> invalid
  it->Next();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

// Robustness: Calling Next() immediately after SeekToLast() on a single-item table becomes invalid
TEST_F(MemTableIteratorNextTest_361, NextFromSingleLastBecomesInvalid_361) {
  Put(7, "only", "val");

  std::unique_ptr<Iterator> it(mem_.NewIterator());
  it->SeekToLast();

  ASSERT_TRUE(it->Valid());
  EXPECT_EQ("only", UserKeyFromInternal(it->key()));
  EXPECT_EQ("val", it->value().ToString());

  it->Next();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());
}

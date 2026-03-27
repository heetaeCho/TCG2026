// db/memtable_seektofirst_test.cc
#include "db/memtable.h"
#include "db/dbformat.h"          // For ParseInternalKey / ParsedInternalKey
#include "util/coding.h"
#include "gtest/gtest.h"

namespace leveldb {

class MemTableIteratorTest_359 : public ::testing::Test {
protected:
  // Common helpers to create a MemTable with the standard comparator.
  MemTableIteratorTest_359()
      : icmp_(BytewiseComparator()), mem_(icmp_) {}

  void AddKV(uint64_t seq, ValueType type, const std::string& key, const std::string& value) {
    mem_.Add(seq, type, key, value);
  }

  // Extract user key from an internal key returned by Iterator::key()
  static std::string UserKeyFromInternal(const Slice& internal_key) {
    ParsedInternalKey pik;
    bool ok = ParseInternalKey(internal_key, &pik);
    // In black-box fashion, only rely on the documented parser to interpret internal keys.
    // If parsing fails, return a marker to make it visible in assertions.
    return ok ? pik.user_key.ToString() : std::string("<parse-failed>");
  }

  InternalKeyComparator icmp_;
  MemTable mem_;
};

// Normal operation: non-empty table -> SeekToFirst lands on smallest key
TEST_F(MemTableIteratorTest_359, SeekToFirst_OnNonEmptyMovesToSmallest_359) {
  AddKV(/*seq=*/1, kTypeValue, "b", "vb");
  AddKV(/*seq=*/2, kTypeValue, "a", "va");
  AddKV(/*seq=*/3, kTypeValue, "c", "vc");

  std::unique_ptr<Iterator> it(mem_.NewIterator());
  it->SeekToFirst();

  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(UserKeyFromInternal(it->key()), "a");
  EXPECT_EQ(it->value().ToString(), "va");
  EXPECT_TRUE(it->status().ok());
}

// Boundary condition: empty table -> SeekToFirst yields invalid iterator
TEST_F(MemTableIteratorTest_359, SeekToFirst_OnEmptyMakesInvalid_359) {
  std::unique_ptr<Iterator> it(mem_.NewIterator());
  it->SeekToFirst();
  EXPECT_FALSE(it->Valid());
  EXPECT_TRUE(it->status().ok());  // No error just because it's empty
}

// Interaction correctness: after moving elsewhere, SeekToFirst resets to the first entry
TEST_F(MemTableIteratorTest_359, SeekToFirst_AfterAdvancingResetsToFirst_359) {
  AddKV(/*seq=*/10, kTypeValue, "a", "va");
  AddKV(/*seq=*/11, kTypeValue, "b", "vb");
  AddKV(/*seq=*/12, kTypeValue, "c", "vc");

  std::unique_ptr<Iterator> it(mem_.NewIterator());

  // Move away from the first entry
  it->Seek(Slice("b"));
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(UserKeyFromInternal(it->key()), "b");
  EXPECT_EQ(it->value().ToString(), "vb");

  // Now reset to the first entry
  it->SeekToFirst();
  ASSERT_TRUE(it->Valid());
  EXPECT_EQ(UserKeyFromInternal(it->key()), "a");
  EXPECT_EQ(it->value().ToString(), "va");
  EXPECT_TRUE(it->status().ok());
}

}  // namespace leveldb

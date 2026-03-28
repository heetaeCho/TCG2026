#include "gtest/gtest.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/iterator.h"
#include "leveldb/status.h"
#include "util/logging.h"

namespace leveldb {

class MemTableTest_103 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Use a default BytewiseComparator for InternalKeyComparator
    cmp_ = new InternalKeyComparator(BytewiseComparator());
    memtable_ = new MemTable(*cmp_);
    memtable_->Ref();
  }

  void TearDown() override {
    memtable_->Unref();
    delete cmp_;
  }

  InternalKeyComparator* cmp_;
  MemTable* memtable_;
};

// Test that a newly created MemTable has minimal memory usage
TEST_F(MemTableTest_103, InitialApproximateMemoryUsage_103) {
  size_t usage = memtable_->ApproximateMemoryUsage();
  // A freshly created memtable should have some small baseline memory usage
  EXPECT_GT(usage, 0u);
}

// Test that Add increases memory usage
TEST_F(MemTableTest_103, AddIncreasesMemoryUsage_103) {
  size_t before = memtable_->ApproximateMemoryUsage();
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  size_t after = memtable_->ApproximateMemoryUsage();
  EXPECT_GT(after, before);
}

// Test that we can Get a value that was previously Added
TEST_F(MemTableTest_103, AddAndGetValue_103) {
  memtable_->Add(100, kTypeValue, Slice("testkey"), Slice("testvalue"));

  std::string value;
  Status s;
  LookupKey lkey("testkey", 100);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("testvalue", value);
}

// Test that Get returns false for a key that doesn't exist
TEST_F(MemTableTest_103, GetNonExistentKey_103) {
  memtable_->Add(100, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  LookupKey lkey("nonexistent", 100);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_FALSE(found);
}

// Test that a deletion entry makes Get return NotFound status
TEST_F(MemTableTest_103, AddDeletionAndGet_103) {
  memtable_->Add(100, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(200, kTypeDeletion, Slice("key1"), Slice(""));

  std::string value;
  Status s;
  LookupKey lkey("key1", 200);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.IsNotFound());
}

// Test that Get with a lower sequence number doesn't see newer entries
TEST_F(MemTableTest_103, GetWithOlderSequenceNumber_103) {
  memtable_->Add(100, kTypeValue, Slice("key1"), Slice("value1"));

  std::string value;
  Status s;
  // Lookup with sequence number smaller than the add's sequence
  LookupKey lkey("key1", 50);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_FALSE(found);
}

// Test that the latest value is returned when multiple values exist for same key
TEST_F(MemTableTest_103, GetReturnsLatestValue_103) {
  memtable_->Add(100, kTypeValue, Slice("key1"), Slice("value_old"));
  memtable_->Add(200, kTypeValue, Slice("key1"), Slice("value_new"));

  std::string value;
  Status s;
  LookupKey lkey("key1", 300);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value_new", value);
}

// Test that older value is returned when sequence number is between two adds
TEST_F(MemTableTest_103, GetReturnsCorrectVersionBySequence_103) {
  memtable_->Add(100, kTypeValue, Slice("key1"), Slice("value_old"));
  memtable_->Add(200, kTypeValue, Slice("key1"), Slice("value_new"));

  std::string value;
  Status s;
  LookupKey lkey("key1", 150);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value_old", value);
}

// Test NewIterator returns a valid iterator
TEST_F(MemTableTest_103, NewIteratorIsValid_103) {
  memtable_->Add(1, kTypeValue, Slice("a"), Slice("va"));
  memtable_->Add(2, kTypeValue, Slice("b"), Slice("vb"));
  memtable_->Add(3, kTypeValue, Slice("c"), Slice("vc"));

  Iterator* iter = memtable_->NewIterator();
  ASSERT_NE(iter, nullptr);

  // Check that iterator can traverse entries
  int count = 0;
  for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
    count++;
  }
  EXPECT_EQ(3, count);

  delete iter;
}

// Test NewIterator on empty memtable
TEST_F(MemTableTest_103, NewIteratorOnEmptyMemTable_103) {
  Iterator* iter = memtable_->NewIterator();
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());

  iter->SeekToLast();
  EXPECT_FALSE(iter->Valid());

  delete iter;
}

// Test Ref/Unref doesn't crash (basic reference counting)
TEST_F(MemTableTest_103, RefUnrefDoesNotCrash_103) {
  // memtable_ already has Ref() called in SetUp
  // Call Ref() again, then Unref() to balance
  memtable_->Ref();
  memtable_->Unref();
  // TearDown will call the final Unref()
}

// Test adding multiple different keys and retrieving them
TEST_F(MemTableTest_103, AddMultipleKeysAndGet_103) {
  memtable_->Add(1, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(2, kTypeValue, Slice("key2"), Slice("value2"));
  memtable_->Add(3, kTypeValue, Slice("key3"), Slice("value3"));

  for (int i = 1; i <= 3; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_value = "value" + std::to_string(i);
    std::string value;
    Status s;
    LookupKey lkey(key, 10);
    bool found = memtable_->Get(lkey, &value, &s);
    EXPECT_TRUE(found) << "Failed to find " << key;
    EXPECT_TRUE(s.ok());
    EXPECT_EQ(expected_value, value);
  }
}

// Test with empty key and value
TEST_F(MemTableTest_103, EmptyKeyAndValue_103) {
  memtable_->Add(1, kTypeValue, Slice(""), Slice(""));

  std::string value;
  Status s;
  LookupKey lkey("", 1);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("", value);
}

// Test with large key and value
TEST_F(MemTableTest_103, LargeKeyAndValue_103) {
  std::string large_key(1000, 'k');
  std::string large_value(10000, 'v');

  memtable_->Add(1, kTypeValue, Slice(large_key), Slice(large_value));

  std::string value;
  Status s;
  LookupKey lkey(large_key, 1);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(large_value, value);
}

// Test that deletion after value makes it not found, but earlier seq still finds value
TEST_F(MemTableTest_103, DeletionDoesNotAffectOlderSequence_103) {
  memtable_->Add(100, kTypeValue, Slice("key1"), Slice("value1"));
  memtable_->Add(200, kTypeDeletion, Slice("key1"), Slice(""));

  // With sequence 150, we should still see the value
  std::string value;
  Status s;
  LookupKey lkey("key1", 150);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);
}

// Test iterator SeekToFirst and SeekToLast
TEST_F(MemTableTest_103, IteratorSeekToFirstAndLast_103) {
  memtable_->Add(1, kTypeValue, Slice("b"), Slice("vb"));
  memtable_->Add(2, kTypeValue, Slice("a"), Slice("va"));
  memtable_->Add(3, kTypeValue, Slice("c"), Slice("vc"));

  Iterator* iter = memtable_->NewIterator();
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());

  iter->SeekToLast();
  EXPECT_TRUE(iter->Valid());

  delete iter;
}

// Test that memory usage grows with more additions
TEST_F(MemTableTest_103, MemoryUsageGrowsWithAdditions_103) {
  size_t prev_usage = memtable_->ApproximateMemoryUsage();
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string value = "value" + std::to_string(i);
    memtable_->Add(i + 1, kTypeValue, Slice(key), Slice(value));
    size_t current_usage = memtable_->ApproximateMemoryUsage();
    EXPECT_GE(current_usage, prev_usage);
    prev_usage = current_usage;
  }
}

// Test that a value added and then re-added updates correctly
TEST_F(MemTableTest_103, OverwriteValueWithHigherSequence_103) {
  memtable_->Add(1, kTypeValue, Slice("key"), Slice("first"));
  memtable_->Add(2, kTypeValue, Slice("key"), Slice("second"));
  memtable_->Add(3, kTypeValue, Slice("key"), Slice("third"));

  std::string value;
  Status s;
  LookupKey lkey("key", 3);
  bool found = memtable_->Get(lkey, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("third", value);
}

}  // namespace leveldb

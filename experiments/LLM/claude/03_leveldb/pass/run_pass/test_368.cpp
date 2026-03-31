#include "gtest/gtest.h"
#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/status.h"
#include "util/coding.h"

namespace leveldb {

class MemTableTest_368 : public ::testing::Test {
 protected:
  MemTable* memtable_;
  InternalKeyComparator cmp_;

  MemTableTest_368() : cmp_(BytewiseComparator()) {
    memtable_ = new MemTable(cmp_);
    memtable_->Ref();
  }

  ~MemTableTest_368() override {
    memtable_->Unref();
  }

  void Add(const std::string& key, const std::string& value,
           SequenceNumber seq, ValueType type = kTypeValue) {
    memtable_->Add(seq, type, key, value);
  }

  bool Get(const std::string& key, SequenceNumber seq, std::string* value,
           Status* s) {
    LookupKey lk(key, seq);
    return memtable_->Get(lk, value, s);
  }
};

// Test: Get returns false when memtable is empty
TEST_F(MemTableTest_368, GetFromEmptyMemTable_368) {
  std::string value;
  Status s;
  bool found = Get("key1", 100, &value, &s);
  EXPECT_FALSE(found);
}

// Test: Get retrieves a value that was previously added
TEST_F(MemTableTest_368, GetExistingKey_368) {
  Add("key1", "value1", 1);

  std::string value;
  Status s;
  bool found = Get("key1", 1, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ("value1", value);
}

// Test: Get returns false for a key that doesn't exist
TEST_F(MemTableTest_368, GetNonExistingKey_368) {
  Add("key1", "value1", 1);

  std::string value;
  Status s;
  bool found = Get("key2", 1, &value, &s);
  EXPECT_FALSE(found);
}

// Test: Get with a deleted key returns NotFound status
TEST_F(MemTableTest_368, GetDeletedKey_368) {
  Add("key1", "", 1, kTypeDeletion);

  std::string value;
  Status s = Status::OK();
  bool found = Get("key1", 1, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Get returns the latest value when key is updated
TEST_F(MemTableTest_368, GetLatestValueForKey_368) {
  Add("key1", "value1", 1);
  Add("key1", "value2", 2);

  std::string value;
  Status s;
  bool found = Get("key1", 2, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ("value2", value);
}

// Test: Get with a higher sequence number sees the latest value
TEST_F(MemTableTest_368, GetWithHigherSequenceNumber_368) {
  Add("key1", "value1", 1);
  Add("key1", "value2", 2);

  std::string value;
  Status s;
  bool found = Get("key1", 10, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ("value2", value);
}

// Test: Get with a sequence number that is lower than the add doesn't find the key
TEST_F(MemTableTest_368, GetWithLowerSequenceNumberDoesNotFind_368) {
  Add("key1", "value1", 5);

  std::string value;
  Status s;
  // Lookup with sequence 3, which is before the key was added at seq 5
  bool found = Get("key1", 3, &value, &s);
  EXPECT_FALSE(found);
}

// Test: Get retrieves correct value when multiple keys exist
TEST_F(MemTableTest_368, GetCorrectValueAmongMultipleKeys_368) {
  Add("aaa", "val_a", 1);
  Add("bbb", "val_b", 2);
  Add("ccc", "val_c", 3);

  std::string value;
  Status s;

  bool found = Get("bbb", 10, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ("val_b", value);
}

// Test: Delete after insert makes Get return NotFound
TEST_F(MemTableTest_368, DeleteAfterInsert_368) {
  Add("key1", "value1", 1, kTypeValue);
  Add("key1", "", 2, kTypeDeletion);

  std::string value;
  Status s = Status::OK();
  bool found = Get("key1", 2, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.IsNotFound());
}

// Test: Insert after delete makes Get return the new value
TEST_F(MemTableTest_368, InsertAfterDelete_368) {
  Add("key1", "value1", 1, kTypeValue);
  Add("key1", "", 2, kTypeDeletion);
  Add("key1", "value3", 3, kTypeValue);

  std::string value;
  Status s;
  bool found = Get("key1", 3, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ("value3", value);
}

// Test: Get with exact sequence number of insertion
TEST_F(MemTableTest_368, GetWithExactSequenceNumber_368) {
  Add("key1", "value1", 5);

  std::string value;
  Status s;
  bool found = Get("key1", 5, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ("value1", value);
}

// Test: Get with sequence number between two versions returns the older one
TEST_F(MemTableTest_368, GetWithSequenceBetweenVersions_368) {
  Add("key1", "old_value", 1);
  Add("key1", "new_value", 10);

  std::string value;
  Status s;
  bool found = Get("key1", 5, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ("old_value", value);
}

// Test: Empty key
TEST_F(MemTableTest_368, EmptyKey_368) {
  Add("", "empty_key_value", 1);

  std::string value;
  Status s;
  bool found = Get("", 1, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ("empty_key_value", value);
}

// Test: Empty value
TEST_F(MemTableTest_368, EmptyValue_368) {
  Add("key1", "", 1, kTypeValue);

  std::string value;
  Status s;
  bool found = Get("key1", 1, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ("", value);
}

// Test: Large value
TEST_F(MemTableTest_368, LargeValue_368) {
  std::string large_value(10000, 'x');
  Add("key1", large_value, 1);

  std::string value;
  Status s;
  bool found = Get("key1", 1, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_EQ(large_value, value);
}

// Test: Multiple different keys all retrievable
TEST_F(MemTableTest_368, MultipleKeysAllRetrievable_368) {
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    Add(key, val, i + 1);
  }

  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string expected_val = "val" + std::to_string(i);
    std::string value;
    Status s;
    bool found = Get(key, 200, &value, &s);
    EXPECT_TRUE(found) << "Key not found: " << key;
    EXPECT_EQ(expected_val, value) << "Wrong value for key: " << key;
  }
}

// Test: ApproximateMemoryUsage increases after adding entries
TEST_F(MemTableTest_368, ApproximateMemoryUsageIncreases_368) {
  size_t initial = memtable_->ApproximateMemoryUsage();
  Add("key1", "value1", 1);
  size_t after_one = memtable_->ApproximateMemoryUsage();
  EXPECT_GT(after_one, initial);

  Add("key2", "value2", 2);
  size_t after_two = memtable_->ApproximateMemoryUsage();
  EXPECT_GT(after_two, after_one);
}

// Test: NewIterator returns a valid iterator
TEST_F(MemTableTest_368, NewIteratorValid_368) {
  Add("key1", "value1", 1);
  Add("key2", "value2", 2);

  Iterator* iter = memtable_->NewIterator();
  ASSERT_NE(iter, nullptr);

  iter->SeekToFirst();
  EXPECT_TRUE(iter->Valid());

  int count = 0;
  while (iter->Valid()) {
    count++;
    iter->Next();
  }
  EXPECT_EQ(2, count);

  delete iter;
}

// Test: NewIterator on empty memtable
TEST_F(MemTableTest_368, NewIteratorOnEmpty_368) {
  Iterator* iter = memtable_->NewIterator();
  ASSERT_NE(iter, nullptr);
  iter->SeekToFirst();
  EXPECT_FALSE(iter->Valid());
  delete iter;
}

// Test: Deletion entry is visible through Get with sequence at deletion
TEST_F(MemTableTest_368, DeletionVisibleAtCorrectSequence_368) {
  Add("key1", "value1", 1, kTypeValue);
  Add("key1", "", 5, kTypeDeletion);

  // At sequence 3, should see the value
  std::string value;
  Status s;
  bool found = Get("key1", 3, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("value1", value);

  // At sequence 5, should see the deletion
  value.clear();
  s = Status::OK();
  found = Get("key1", 5, &value, &s);
  EXPECT_TRUE(found);
  EXPECT_TRUE(s.IsNotFound());
}

}  // namespace leveldb

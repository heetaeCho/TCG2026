#include "db/memtable.h"
#include "db/dbformat.h"
#include "gtest/gtest.h"

namespace leveldb {

// Helper to create an InternalKey
static std::string MakeInternalKey(const std::string& user_key,
                                   SequenceNumber seq,
                                   ValueType type) {
  InternalKey internal_key(user_key, seq, type);
  return internal_key.Encode().ToString();
}

class MemTableTest_367 : public ::testing::Test {
 protected:
  InternalKeyComparator icmp{BytewiseComparator()};
  MemTable memtable{icmp};
};

// Normal insertion and retrieval
TEST_F(MemTableTest_367, AddAndGetNormalKey_367) {
  std::string user_key = "test";
  std::string value = "value";
  SequenceNumber seq = 1;

  memtable.Add(seq, kTypeValue, Slice(user_key), Slice(value));

  std::string result;
  Status s;
  LookupKey lookup(user_key, seq);
  ASSERT_TRUE(memtable.Get(lookup, &result, &s));
  EXPECT_EQ(result, value);
  EXPECT_TRUE(s.ok());
}

// Insertion of multiple keys
TEST_F(MemTableTest_367, AddMultipleKeysAndRetrieve_367) {
  memtable.Add(1, kTypeValue, Slice("key1"), Slice("val1"));
  memtable.Add(2, kTypeValue, Slice("key2"), Slice("val2"));

  std::string result;
  Status s1, s2;
  LookupKey lookup1("key1", 1);
  LookupKey lookup2("key2", 2);

  EXPECT_TRUE(memtable.Get(lookup1, &result, &s1));
  EXPECT_EQ(result, "val1");

  EXPECT_TRUE(memtable.Get(lookup2, &result, &s2));
  EXPECT_EQ(result, "val2");
}

// Boundary condition: empty key and value
TEST_F(MemTableTest_367, AddEmptyKeyAndValue_367) {
  memtable.Add(1, kTypeValue, Slice(""), Slice(""));

  std::string result;
  Status s;
  LookupKey lookup("", 1);
  EXPECT_TRUE(memtable.Get(lookup, &result, &s));
  EXPECT_EQ(result, "");
}

// Overwriting existing key with higher sequence number
TEST_F(MemTableTest_367, OverwriteKeyWithHigherSeq_367) {
  std::string key = "dupkey";
  memtable.Add(1, kTypeValue, Slice(key), Slice("old"));
  memtable.Add(2, kTypeValue, Slice(key), Slice("new"));

  std::string result;
  Status s;
  LookupKey lookup(key, 2);
  EXPECT_TRUE(memtable.Get(lookup, &result, &s));
  EXPECT_EQ(result, "new");
}

// Deletion marker: value should not be found
TEST_F(MemTableTest_367, AddDeletionType_367) {
  std::string key = "delkey";
  memtable.Add(1, kTypeValue, Slice(key), Slice("exists"));
  memtable.Add(2, kTypeDeletion, Slice(key), Slice("irrelevant"));

  std::string result;
  Status s;
  LookupKey lookup(key, 2);
  EXPECT_FALSE(memtable.Get(lookup, &result, &s));
  EXPECT_TRUE(s.IsNotFound());
}

}  // namespace leveldb

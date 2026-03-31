#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

class LookupKeyTest_57 : public ::testing::Test {
 protected:
};

// Test that constructing a LookupKey with an empty user key does not crash
// and that memtable_key returns a non-empty slice (due to internal encoding overhead)
TEST_F(LookupKeyTest_57, EmptyUserKey_57) {
  LookupKey key(Slice("", 0), 0);
  Slice memtable = key.memtable_key();
  // Even with empty user key, memtable_key should have length encoding + tag
  EXPECT_GT(memtable.size(), 0u);
}

// Test memtable_key with a normal user key and sequence number
TEST_F(LookupKeyTest_57, NormalUserKey_MemtableKey_57) {
  std::string user_key = "hello";
  SequenceNumber seq = 100;
  LookupKey key(Slice(user_key), seq);
  Slice memtable = key.memtable_key();
  // memtable_key should contain the full encoding: length prefix + user_key + tag
  // The tag is 8 bytes, so minimum size is varint(user_key.size() + 8) + user_key.size() + 8
  EXPECT_GE(memtable.size(), user_key.size() + 8 + 1);
}

// Test internal_key with a normal user key
TEST_F(LookupKeyTest_57, NormalUserKey_InternalKey_57) {
  std::string user_key = "hello";
  SequenceNumber seq = 100;
  LookupKey key(Slice(user_key), seq);
  Slice internal = key.internal_key();
  // internal_key should be user_key + 8 byte tag
  EXPECT_EQ(internal.size(), user_key.size() + 8);
  // The first part of internal_key should contain the user_key
  EXPECT_EQ(Slice(internal.data(), user_key.size()).ToString(), user_key);
}

// Test user_key with a normal user key
TEST_F(LookupKeyTest_57, NormalUserKey_UserKey_57) {
  std::string user_key = "hello";
  SequenceNumber seq = 100;
  LookupKey key(Slice(user_key), seq);
  Slice extracted = key.user_key();
  EXPECT_EQ(extracted.ToString(), user_key);
}

// Test with sequence number 0
TEST_F(LookupKeyTest_57, SequenceNumberZero_57) {
  std::string user_key = "testkey";
  LookupKey key(Slice(user_key), 0);
  Slice extracted = key.user_key();
  EXPECT_EQ(extracted.ToString(), user_key);
  Slice internal = key.internal_key();
  EXPECT_EQ(internal.size(), user_key.size() + 8);
}

// Test with maximum sequence number
TEST_F(LookupKeyTest_57, MaxSequenceNumber_57) {
  std::string user_key = "testkey";
  // Max sequence number is (1 << 56) - 1 based on leveldb format
  SequenceNumber max_seq = (static_cast<uint64_t>(1) << 56) - 1;
  LookupKey key(Slice(user_key), max_seq);
  Slice extracted = key.user_key();
  EXPECT_EQ(extracted.ToString(), user_key);
}

// Test with a single character user key
TEST_F(LookupKeyTest_57, SingleCharUserKey_57) {
  std::string user_key = "a";
  LookupKey key(Slice(user_key), 42);
  Slice extracted = key.user_key();
  EXPECT_EQ(extracted.ToString(), user_key);
  Slice internal = key.internal_key();
  EXPECT_EQ(internal.size(), 1 + 8);
}

// Test with a longer user key that exceeds the internal space_ buffer (200 bytes)
TEST_F(LookupKeyTest_57, LongUserKey_57) {
  std::string user_key(300, 'x');
  LookupKey key(Slice(user_key), 12345);
  Slice extracted = key.user_key();
  EXPECT_EQ(extracted.ToString(), user_key);
  Slice internal = key.internal_key();
  EXPECT_EQ(internal.size(), user_key.size() + 8);
  Slice memtable = key.memtable_key();
  EXPECT_GT(memtable.size(), internal.size());
}

// Test that memtable_key size > internal_key size (memtable_key has a varint prefix)
TEST_F(LookupKeyTest_57, MemtableKeyLargerThanInternalKey_57) {
  std::string user_key = "somekey";
  LookupKey key(Slice(user_key), 500);
  Slice memtable = key.memtable_key();
  Slice internal = key.internal_key();
  EXPECT_GT(memtable.size(), internal.size());
}

// Test that internal_key starts at an offset within memtable_key
TEST_F(LookupKeyTest_57, InternalKeyIsSubmemtableKey_57) {
  std::string user_key = "mykey";
  LookupKey key(Slice(user_key), 99);
  Slice memtable = key.memtable_key();
  Slice internal = key.internal_key();
  // internal_key should be the tail of memtable_key
  const char* internal_end = internal.data() + internal.size();
  const char* memtable_end = memtable.data() + memtable.size();
  EXPECT_EQ(internal_end, memtable_end);
}

// Test that user_key is a prefix of internal_key
TEST_F(LookupKeyTest_57, UserKeyIsPrefixOfInternalKey_57) {
  std::string user_key = "prefix_test";
  LookupKey key(Slice(user_key), 777);
  Slice internal = key.internal_key();
  Slice extracted = key.user_key();
  EXPECT_EQ(internal.data(), extracted.data());
  EXPECT_EQ(extracted.size() + 8, internal.size());
}

// Test with binary data in user key
TEST_F(LookupKeyTest_57, BinaryUserKey_57) {
  std::string user_key;
  user_key.push_back('\0');
  user_key.push_back('\x01');
  user_key.push_back('\xff');
  user_key.push_back('\x80');
  LookupKey key(Slice(user_key), 1);
  Slice extracted = key.user_key();
  EXPECT_EQ(extracted.size(), user_key.size());
  EXPECT_EQ(extracted.ToString(), user_key);
}

// Test key at exactly the boundary of internal space_ (200 bytes)
// space_ is 200 bytes; key encoding = varint_len + user_key.size() + 8
// For user_key of ~190 bytes: varint(190+8=198) = 2 bytes, total = 2 + 198 = 200
TEST_F(LookupKeyTest_57, BoundarySpaceBuffer_57) {
  // Try key size that should fit exactly in space_[200]
  // varint(size+8) where size = 190: 198 -> 2-byte varint, total = 2 + 190 + 8 = 200
  std::string user_key(190, 'b');
  LookupKey key(Slice(user_key), 50);
  Slice extracted = key.user_key();
  EXPECT_EQ(extracted.ToString(), user_key);
}

// Test key just over the boundary of internal space_ buffer
TEST_F(LookupKeyTest_57, JustOverBoundarySpaceBuffer_57) {
  std::string user_key(191, 'c');
  LookupKey key(Slice(user_key), 50);
  Slice extracted = key.user_key();
  EXPECT_EQ(extracted.ToString(), user_key);
}

// Test consistency: multiple calls to the same method return the same result
TEST_F(LookupKeyTest_57, ConsistentResults_57) {
  std::string user_key = "consistent";
  LookupKey key(Slice(user_key), 999);
  
  Slice m1 = key.memtable_key();
  Slice m2 = key.memtable_key();
  EXPECT_EQ(m1.data(), m2.data());
  EXPECT_EQ(m1.size(), m2.size());
  
  Slice i1 = key.internal_key();
  Slice i2 = key.internal_key();
  EXPECT_EQ(i1.data(), i2.data());
  EXPECT_EQ(i1.size(), i2.size());
  
  Slice u1 = key.user_key();
  Slice u2 = key.user_key();
  EXPECT_EQ(u1.data(), u2.data());
  EXPECT_EQ(u1.size(), u2.size());
}

}  // namespace leveldb

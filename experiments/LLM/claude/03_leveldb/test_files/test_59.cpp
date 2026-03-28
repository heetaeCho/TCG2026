#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

class LookupKeyTest_59 : public ::testing::Test {
 protected:
};

// Test that user_key() returns the correct user key for a simple key
TEST_F(LookupKeyTest_59, UserKeyReturnsCorrectKey_59) {
  LookupKey key(Slice("hello"), 100);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "hello");
}

// Test that user_key() works with an empty user key
TEST_F(LookupKeyTest_59, UserKeyEmptyString_59) {
  LookupKey key(Slice(""), 0);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "");
}

// Test that user_key() works with a single character key
TEST_F(LookupKeyTest_59, UserKeySingleChar_59) {
  LookupKey key(Slice("a"), 1);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "a");
}

// Test that user_key() works with maximum sequence number
TEST_F(LookupKeyTest_59, UserKeyMaxSequenceNumber_59) {
  LookupKey key(Slice("test"), kMaxSequenceNumber);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "test");
}

// Test that user_key() works with sequence number 0
TEST_F(LookupKeyTest_59, UserKeySequenceZero_59) {
  LookupKey key(Slice("test"), 0);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), "test");
}

// Test that internal_key() contains user key plus 8 bytes tag
TEST_F(LookupKeyTest_59, InternalKeyContainsUserKeyPlusTag_59) {
  LookupKey key(Slice("hello"), 100);
  Slice internal_key = key.internal_key();
  // Internal key = user_key + 8 bytes (sequence number + type packed)
  EXPECT_EQ(internal_key.size(), 5 + 8);
  // First 5 bytes should be "hello"
  EXPECT_EQ(Slice(internal_key.data(), 5).ToString(), "hello");
}

// Test that memtable_key() has the length prefix before internal key
TEST_F(LookupKeyTest_59, MemtableKeyHasLengthPrefix_59) {
  LookupKey key(Slice("hello"), 100);
  Slice memtable_key = key.memtable_key();
  // memtable_key should be longer than internal_key due to varint length prefix
  Slice internal_key = key.internal_key();
  EXPECT_GT(memtable_key.size(), internal_key.size());
}

// Test with a longer key that might exceed the inline space_ buffer (200 bytes)
TEST_F(LookupKeyTest_59, UserKeyLongKey_59) {
  std::string long_key(300, 'x');
  LookupKey key(Slice(long_key), 42);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), long_key);
}

// Test with a key exactly at the boundary of the space_ buffer
TEST_F(LookupKeyTest_59, UserKeyBoundaryLength_59) {
  // space_ is 200 bytes. The lookup key stores varint32(len) + user_key + 8 bytes tag
  // For a key of size ~190, total would be around 1 + 190 + 8 = 199
  std::string boundary_key(190, 'b');
  LookupKey key(Slice(boundary_key), 55);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.ToString(), boundary_key);
}

// Test that user_key preserves binary data including null bytes
TEST_F(LookupKeyTest_59, UserKeyWithNullBytes_59) {
  std::string key_with_nulls("ab\0cd", 5);
  LookupKey key(Slice(key_with_nulls), 10);
  Slice user_key = key.user_key();
  EXPECT_EQ(user_key.size(), 5);
  EXPECT_EQ(user_key.ToString(), key_with_nulls);
}

// Test that different sequence numbers don't affect user_key
TEST_F(LookupKeyTest_59, DifferentSequencesSameUserKey_59) {
  LookupKey key1(Slice("same"), 1);
  LookupKey key2(Slice("same"), 999999);
  EXPECT_EQ(key1.user_key().ToString(), key2.user_key().ToString());
}

// Test that different sequence numbers produce different internal keys
TEST_F(LookupKeyTest_59, DifferentSequencesDifferentInternalKey_59) {
  LookupKey key1(Slice("same"), 1);
  LookupKey key2(Slice("same"), 2);
  EXPECT_NE(key1.internal_key().ToString(), key2.internal_key().ToString());
}

// Test consistency: user_key extracted from internal_key matches user_key()
TEST_F(LookupKeyTest_59, UserKeyConsistentWithInternalKey_59) {
  LookupKey key(Slice("consistent"), 500);
  Slice user_key = key.user_key();
  Slice internal_key = key.internal_key();
  // The user key portion of internal key (first internal_key.size() - 8 bytes) should match
  EXPECT_EQ(Slice(internal_key.data(), internal_key.size() - 8).ToString(),
            user_key.ToString());
}

}  // namespace leveldb

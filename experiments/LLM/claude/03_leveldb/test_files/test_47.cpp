#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test normal operation with a typical user key
TEST(InternalKeyEncodingLengthTest_47, NormalKey_47) {
  ParsedInternalKey key("hello", 100, kTypeValue);
  EXPECT_EQ(InternalKeyEncodingLength(key), 5 + 8);
}

// Test with an empty user key
TEST(InternalKeyEncodingLengthTest_47, EmptyUserKey_47) {
  ParsedInternalKey key("", 0, kTypeDeletion);
  EXPECT_EQ(InternalKeyEncodingLength(key), 0 + 8);
}

// Test with a single character user key
TEST(InternalKeyEncodingLengthTest_47, SingleCharUserKey_47) {
  ParsedInternalKey key("a", 1, kTypeValue);
  EXPECT_EQ(InternalKeyEncodingLength(key), 1 + 8);
}

// Test with a longer user key
TEST(InternalKeyEncodingLengthTest_47, LongUserKey_47) {
  std::string long_key(1000, 'x');
  ParsedInternalKey key(long_key, 999999, kTypeValue);
  EXPECT_EQ(InternalKeyEncodingLength(key), 1000 + 8);
}

// Test with max sequence number
TEST(InternalKeyEncodingLengthTest_47, MaxSequenceNumber_47) {
  ParsedInternalKey key("test", kMaxSequenceNumber, kTypeValue);
  EXPECT_EQ(InternalKeyEncodingLength(key), 4 + 8);
}

// Test with zero sequence number
TEST(InternalKeyEncodingLengthTest_47, ZeroSequenceNumber_47) {
  ParsedInternalKey key("test", 0, kTypeValue);
  EXPECT_EQ(InternalKeyEncodingLength(key), 4 + 8);
}

// Test with kTypeDeletion type
TEST(InternalKeyEncodingLengthTest_47, DeletionType_47) {
  ParsedInternalKey key("mykey", 50, kTypeDeletion);
  EXPECT_EQ(InternalKeyEncodingLength(key), 5 + 8);
}

// Test with kTypeValue type
TEST(InternalKeyEncodingLengthTest_47, ValueType_47) {
  ParsedInternalKey key("mykey", 50, kTypeValue);
  EXPECT_EQ(InternalKeyEncodingLength(key), 5 + 8);
}

// Test that the result is always user_key.size() + 8 regardless of sequence/type
TEST(InternalKeyEncodingLengthTest_47, ConsistentOverhead_47) {
  ParsedInternalKey key1("abc", 1, kTypeValue);
  ParsedInternalKey key2("abc", 999, kTypeDeletion);
  EXPECT_EQ(InternalKeyEncodingLength(key1), InternalKeyEncodingLength(key2));
}

// Test with a very large user key
TEST(InternalKeyEncodingLengthTest_47, VeryLargeUserKey_47) {
  std::string large_key(100000, 'z');
  ParsedInternalKey key(large_key, 42, kTypeValue);
  EXPECT_EQ(InternalKeyEncodingLength(key), 100000 + 8);
}

// Test with user key containing null bytes
TEST(InternalKeyEncodingLengthTest_47, UserKeyWithNullBytes_47) {
  std::string key_with_nulls("ab\0cd", 5);
  ParsedInternalKey key(Slice(key_with_nulls.data(), key_with_nulls.size()), 10, kTypeValue);
  EXPECT_EQ(InternalKeyEncodingLength(key), 5 + 8);
}

// Test with user key constructed from Slice with explicit size
TEST(InternalKeyEncodingLengthTest_47, SliceWithExplicitSize_47) {
  const char* data = "hello world";
  Slice s(data, 5);  // Only "hello"
  ParsedInternalKey key(s, 77, kTypeValue);
  EXPECT_EQ(InternalKeyEncodingLength(key), 5 + 8);
}

// Test default constructed ParsedInternalKey
TEST(InternalKeyEncodingLengthTest_47, DefaultConstructedKey_47) {
  ParsedInternalKey key;
  // Default Slice is empty
  EXPECT_EQ(InternalKeyEncodingLength(key), 0 + 8);
}

}  // namespace leveldb

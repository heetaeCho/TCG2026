#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "util/coding.h"
#include <string>

namespace leveldb {

// Helper to decode the fixed64 from the end of the result
static uint64_t DecodeFixed64FromEnd(const std::string& result) {
  EXPECT_GE(result.size(), 8u);
  return DecodeFixed64(result.data() + result.size() - 8);
}

static uint64_t PackSequenceAndType(SequenceNumber seq, ValueType t) {
  return (seq << 8) | static_cast<uint64_t>(t);
}

// Test normal operation with a typical key
TEST(AppendInternalKeyTest_185, NormalKey_185) {
  std::string result;
  ParsedInternalKey key("hello", 100, kTypeValue);
  AppendInternalKey(&result, key);

  // Result should be user_key + 8 bytes for packed sequence and type
  EXPECT_EQ(result.size(), 5 + 8);

  // Check that the user key is at the beginning
  EXPECT_EQ(result.substr(0, 5), "hello");

  // Check the packed sequence and type
  uint64_t packed = DecodeFixed64FromEnd(result);
  EXPECT_EQ(packed, PackSequenceAndType(100, kTypeValue));
}

// Test with kTypeDeletion
TEST(AppendInternalKeyTest_185, DeletionType_185) {
  std::string result;
  ParsedInternalKey key("mykey", 200, kTypeDeletion);
  AppendInternalKey(&result, key);

  EXPECT_EQ(result.size(), 5 + 8);
  EXPECT_EQ(result.substr(0, 5), "mykey");

  uint64_t packed = DecodeFixed64FromEnd(result);
  EXPECT_EQ(packed, PackSequenceAndType(200, kTypeDeletion));
}

// Test with empty user key
TEST(AppendInternalKeyTest_185, EmptyUserKey_185) {
  std::string result;
  ParsedInternalKey key("", 0, kTypeValue);
  AppendInternalKey(&result, key);

  // Result should only have the 8-byte trailer
  EXPECT_EQ(result.size(), 8u);

  uint64_t packed = DecodeFixed64FromEnd(result);
  EXPECT_EQ(packed, PackSequenceAndType(0, kTypeValue));
}

// Test with sequence number 0
TEST(AppendInternalKeyTest_185, ZeroSequenceNumber_185) {
  std::string result;
  ParsedInternalKey key("key", 0, kTypeValue);
  AppendInternalKey(&result, key);

  EXPECT_EQ(result.size(), 3 + 8);
  EXPECT_EQ(result.substr(0, 3), "key");

  uint64_t packed = DecodeFixed64FromEnd(result);
  EXPECT_EQ(packed, PackSequenceAndType(0, kTypeValue));
}

// Test with a large sequence number
TEST(AppendInternalKeyTest_185, LargeSequenceNumber_185) {
  std::string result;
  SequenceNumber large_seq = (1ULL << 56) - 1;  // Max valid sequence number
  ParsedInternalKey key("bigseq", large_seq, kTypeValue);
  AppendInternalKey(&result, key);

  EXPECT_EQ(result.size(), 6 + 8);
  EXPECT_EQ(result.substr(0, 6), "bigseq");

  uint64_t packed = DecodeFixed64FromEnd(result);
  EXPECT_EQ(packed, PackSequenceAndType(large_seq, kTypeValue));
}

// Test that AppendInternalKey appends (does not overwrite) to an existing string
TEST(AppendInternalKeyTest_185, AppendsToExistingString_185) {
  std::string result = "prefix";
  ParsedInternalKey key("abc", 42, kTypeValue);
  AppendInternalKey(&result, key);

  // Should have prefix + user_key + 8 bytes
  EXPECT_EQ(result.size(), 6 + 3 + 8);
  EXPECT_EQ(result.substr(0, 6), "prefix");
  EXPECT_EQ(result.substr(6, 3), "abc");

  uint64_t packed = DecodeFixed64(result.data() + 9);
  EXPECT_EQ(packed, PackSequenceAndType(42, kTypeValue));
}

// Test with user key containing null bytes
TEST(AppendInternalKeyTest_185, UserKeyWithNullBytes_185) {
  std::string user_key_str("ke\0y", 4);
  std::string result;
  ParsedInternalKey key(Slice(user_key_str), 10, kTypeValue);
  AppendInternalKey(&result, key);

  EXPECT_EQ(result.size(), 4 + 8);
  EXPECT_EQ(result.substr(0, 4), user_key_str);

  uint64_t packed = DecodeFixed64FromEnd(result);
  EXPECT_EQ(packed, PackSequenceAndType(10, kTypeValue));
}

// Test multiple appends to the same string
TEST(AppendInternalKeyTest_185, MultipleAppends_185) {
  std::string result;
  ParsedInternalKey key1("aaa", 1, kTypeValue);
  ParsedInternalKey key2("bbb", 2, kTypeDeletion);

  AppendInternalKey(&result, key1);
  size_t first_size = result.size();
  EXPECT_EQ(first_size, 3 + 8);

  AppendInternalKey(&result, key2);
  EXPECT_EQ(result.size(), first_size + 3 + 8);

  // Verify second key's packed value
  uint64_t packed2 = DecodeFixed64(result.data() + first_size + 3);
  EXPECT_EQ(packed2, PackSequenceAndType(2, kTypeDeletion));
}

// Test with sequence number 1
TEST(AppendInternalKeyTest_185, SequenceNumberOne_185) {
  std::string result;
  ParsedInternalKey key("x", 1, kTypeDeletion);
  AppendInternalKey(&result, key);

  EXPECT_EQ(result.size(), 1 + 8);
  EXPECT_EQ(result[0], 'x');

  uint64_t packed = DecodeFixed64FromEnd(result);
  EXPECT_EQ(packed, PackSequenceAndType(1, kTypeDeletion));
}

// Test with a longer user key
TEST(AppendInternalKeyTest_185, LongUserKey_185) {
  std::string long_key(1000, 'z');
  std::string result;
  ParsedInternalKey key(long_key, 999, kTypeValue);
  AppendInternalKey(&result, key);

  EXPECT_EQ(result.size(), 1000 + 8);
  EXPECT_EQ(result.substr(0, 1000), long_key);

  uint64_t packed = DecodeFixed64FromEnd(result);
  EXPECT_EQ(packed, PackSequenceAndType(999, kTypeValue));
}

}  // namespace leveldb

#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "util/coding.h"

#include <string>
#include <cstring>

namespace leveldb {

// Helper function to build an internal key from user_key, sequence, and type
static std::string BuildInternalKey(const Slice& user_key,
                                     SequenceNumber seq,
                                     ValueType type) {
  std::string result(user_key.data(), user_key.size());
  uint64_t packed = (seq << 8) | static_cast<uint8_t>(type);
  char buf[8];
  EncodeFixed64(buf, packed);
  result.append(buf, 8);
  return result;
}

class ParseInternalKeyTest_56 : public ::testing::Test {};

// Test parsing a valid internal key with kTypeValue
TEST_F(ParseInternalKeyTest_56, ParseValidKeyWithTypeValue_56) {
  std::string user_key = "hello";
  SequenceNumber seq = 12345;
  ValueType type = kTypeValue;

  std::string internal = BuildInternalKey(user_key, seq, type);
  Slice internal_slice(internal);

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "hello");
  EXPECT_EQ(parsed.sequence, 12345);
  EXPECT_EQ(parsed.type, kTypeValue);
}

// Test parsing a valid internal key with kTypeDeletion
TEST_F(ParseInternalKeyTest_56, ParseValidKeyWithTypeDeletion_56) {
  std::string user_key = "world";
  SequenceNumber seq = 99999;
  ValueType type = kTypeDeletion;

  std::string internal = BuildInternalKey(user_key, seq, type);
  Slice internal_slice(internal);

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "world");
  EXPECT_EQ(parsed.sequence, 99999);
  EXPECT_EQ(parsed.type, kTypeDeletion);
}

// Test that keys shorter than 8 bytes are rejected
TEST_F(ParseInternalKeyTest_56, TooShortKeyReturnsFlase_56) {
  std::string short_key = "1234567"; // 7 bytes, less than 8
  Slice internal_slice(short_key);

  ParsedInternalKey parsed;
  EXPECT_FALSE(ParseInternalKey(internal_slice, &parsed));
}

// Test that an empty key is rejected
TEST_F(ParseInternalKeyTest_56, EmptyKeyReturnsFalse_56) {
  Slice internal_slice("", 0);

  ParsedInternalKey parsed;
  EXPECT_FALSE(ParseInternalKey(internal_slice, &parsed));
}

// Test exactly 8 bytes (empty user key)
TEST_F(ParseInternalKeyTest_56, ExactlyEightBytesEmptyUserKey_56) {
  std::string user_key = "";
  SequenceNumber seq = 1;
  ValueType type = kTypeValue;

  std::string internal = BuildInternalKey(user_key, seq, type);
  ASSERT_EQ(internal.size(), 8u);
  Slice internal_slice(internal);

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "");
  EXPECT_EQ(parsed.sequence, 1);
  EXPECT_EQ(parsed.type, kTypeValue);
}

// Test that an invalid type value (> kTypeValue) causes failure
TEST_F(ParseInternalKeyTest_56, InvalidTypeReturnsFalse_56) {
  std::string user_key = "test";
  // Manually build with an invalid type byte (e.g., 2)
  std::string result(user_key.data(), user_key.size());
  uint64_t packed = (100ULL << 8) | 2; // type = 2, which is > kTypeValue(1)
  char buf[8];
  EncodeFixed64(buf, packed);
  result.append(buf, 8);

  Slice internal_slice(result);
  ParsedInternalKey parsed;
  EXPECT_FALSE(ParseInternalKey(internal_slice, &parsed));
}

// Test with sequence number 0
TEST_F(ParseInternalKeyTest_56, ZeroSequenceNumber_56) {
  std::string user_key = "key";
  SequenceNumber seq = 0;
  ValueType type = kTypeValue;

  std::string internal = BuildInternalKey(user_key, seq, type);
  Slice internal_slice(internal);

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "key");
  EXPECT_EQ(parsed.sequence, 0);
  EXPECT_EQ(parsed.type, kTypeValue);
}

// Test with a large sequence number
TEST_F(ParseInternalKeyTest_56, LargeSequenceNumber_56) {
  std::string user_key = "bigseq";
  // Max sequence number fits in 56 bits (since lower 8 bits are type)
  SequenceNumber seq = (1ULL << 56) - 1;
  ValueType type = kTypeDeletion;

  std::string internal = BuildInternalKey(user_key, seq, type);
  Slice internal_slice(internal);

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "bigseq");
  EXPECT_EQ(parsed.sequence, seq);
  EXPECT_EQ(parsed.type, kTypeDeletion);
}

// Test with a single character user key
TEST_F(ParseInternalKeyTest_56, SingleCharUserKey_56) {
  std::string user_key = "a";
  SequenceNumber seq = 42;
  ValueType type = kTypeValue;

  std::string internal = BuildInternalKey(user_key, seq, type);
  Slice internal_slice(internal);

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.user_key.ToString(), "a");
  EXPECT_EQ(parsed.sequence, 42);
  EXPECT_EQ(parsed.type, kTypeValue);
}

// Test that type byte 0xFF (255) is invalid
TEST_F(ParseInternalKeyTest_56, TypeByte255IsInvalid_56) {
  std::string user_key = "test";
  std::string result(user_key.data(), user_key.size());
  uint64_t packed = (50ULL << 8) | 0xFF;
  char buf[8];
  EncodeFixed64(buf, packed);
  result.append(buf, 8);

  Slice internal_slice(result);
  ParsedInternalKey parsed;
  EXPECT_FALSE(ParseInternalKey(internal_slice, &parsed));
}

// Test with 7 bytes (boundary: just below minimum)
TEST_F(ParseInternalKeyTest_56, SevenBytesReturnsFalse_56) {
  std::string data(7, 'x');
  Slice internal_slice(data);

  ParsedInternalKey parsed;
  EXPECT_FALSE(ParseInternalKey(internal_slice, &parsed));
}

// Test with user key containing null bytes
TEST_F(ParseInternalKeyTest_56, UserKeyWithNullBytes_56) {
  std::string user_key("ke\0y", 4);
  SequenceNumber seq = 10;
  ValueType type = kTypeValue;

  std::string internal = BuildInternalKey(user_key, seq, type);
  Slice internal_slice(internal);

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.user_key.size(), 4u);
  EXPECT_EQ(parsed.user_key.ToString(), user_key);
  EXPECT_EQ(parsed.sequence, 10);
  EXPECT_EQ(parsed.type, kTypeValue);
}

// Test that type byte exactly equal to kTypeValue (1) is accepted
TEST_F(ParseInternalKeyTest_56, TypeExactlyKTypeValue_56) {
  std::string user_key = "exact";
  std::string result(user_key.data(), user_key.size());
  uint64_t packed = (77ULL << 8) | static_cast<uint8_t>(kTypeValue);
  char buf[8];
  EncodeFixed64(buf, packed);
  result.append(buf, 8);

  Slice internal_slice(result);
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.type, kTypeValue);
  EXPECT_EQ(parsed.sequence, 77);
}

// Test that type byte exactly equal to kTypeDeletion (0) is accepted
TEST_F(ParseInternalKeyTest_56, TypeExactlyKTypeDeletion_56) {
  std::string user_key = "del";
  std::string result(user_key.data(), user_key.size());
  uint64_t packed = (88ULL << 8) | static_cast<uint8_t>(kTypeDeletion);
  char buf[8];
  EncodeFixed64(buf, packed);
  result.append(buf, 8);

  Slice internal_slice(result);
  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.type, kTypeDeletion);
  EXPECT_EQ(parsed.sequence, 88);
}

// Test long user key
TEST_F(ParseInternalKeyTest_56, LongUserKey_56) {
  std::string user_key(10000, 'z');
  SequenceNumber seq = 500;
  ValueType type = kTypeValue;

  std::string internal = BuildInternalKey(user_key, seq, type);
  Slice internal_slice(internal);

  ParsedInternalKey parsed;
  ASSERT_TRUE(ParseInternalKey(internal_slice, &parsed));
  EXPECT_EQ(parsed.user_key.size(), 10000u);
  EXPECT_EQ(parsed.user_key.ToString(), user_key);
  EXPECT_EQ(parsed.sequence, 500);
  EXPECT_EQ(parsed.type, kTypeValue);
}

}  // namespace leveldb

#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include <string>
#include <cstdint>

namespace leveldb {

// Test normal operation with a simple key
TEST(ParsedInternalKeyTest_186, DebugStringNormalKey_186) {
  ParsedInternalKey key(Slice("hello"), 100, kTypeValue);
  std::string result = key.DebugString();
  // Should contain the user key
  EXPECT_NE(result.find("hello"), std::string::npos);
  // Should contain the sequence number
  EXPECT_NE(result.find("100"), std::string::npos);
  // Should contain the type as an integer (kTypeValue = 1)
  EXPECT_NE(result.find("1"), std::string::npos);
  // Should contain the @ separator
  EXPECT_NE(result.find("@"), std::string::npos);
  // Should contain the : separator
  EXPECT_NE(result.find(":"), std::string::npos);
}

// Test with deletion type
TEST(ParsedInternalKeyTest_186, DebugStringDeletionType_186) {
  ParsedInternalKey key(Slice("mykey"), 42, kTypeDeletion);
  std::string result = key.DebugString();
  EXPECT_NE(result.find("mykey"), std::string::npos);
  EXPECT_NE(result.find("42"), std::string::npos);
  // kTypeDeletion = 0
  EXPECT_NE(result.find("0"), std::string::npos);
}

// Test with empty user key
TEST(ParsedInternalKeyTest_186, DebugStringEmptyKey_186) {
  ParsedInternalKey key(Slice(""), 0, kTypeDeletion);
  std::string result = key.DebugString();
  // Should still have the format with @ and :
  EXPECT_NE(result.find("@"), std::string::npos);
  EXPECT_NE(result.find(":"), std::string::npos);
  EXPECT_NE(result.find("0"), std::string::npos);
}

// Test with zero sequence number
TEST(ParsedInternalKeyTest_186, DebugStringZeroSequence_186) {
  ParsedInternalKey key(Slice("key"), 0, kTypeValue);
  std::string result = key.DebugString();
  EXPECT_NE(result.find("key"), std::string::npos);
  EXPECT_NE(result.find("0"), std::string::npos);
}

// Test with large sequence number
TEST(ParsedInternalKeyTest_186, DebugStringLargeSequence_186) {
  ParsedInternalKey key(Slice("bigseq"), 9999999999ULL, kTypeValue);
  std::string result = key.DebugString();
  EXPECT_NE(result.find("bigseq"), std::string::npos);
  EXPECT_NE(result.find("9999999999"), std::string::npos);
}

// Test with max sequence number
TEST(ParsedInternalKeyTest_186, DebugStringMaxSequence_186) {
  // kMaxSequenceNumber is (1ull << 56) - 1
  SequenceNumber maxSeq = (1ULL << 56) - 1;
  ParsedInternalKey key(Slice("maxkey"), maxSeq, kTypeValue);
  std::string result = key.DebugString();
  EXPECT_NE(result.find("maxkey"), std::string::npos);
  EXPECT_NE(result.find("@"), std::string::npos);
}

// Test with special characters in user key
TEST(ParsedInternalKeyTest_186, DebugStringSpecialCharsInKey_186) {
  std::string specialKey = "key\x01\x02\xff";
  ParsedInternalKey key(Slice(specialKey), 5, kTypeValue);
  std::string result = key.DebugString();
  // The result should be non-empty and properly formatted
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("@"), std::string::npos);
  EXPECT_NE(result.find(":"), std::string::npos);
  EXPECT_NE(result.find("5"), std::string::npos);
}

// Test that the string starts with a single quote
TEST(ParsedInternalKeyTest_186, DebugStringStartsWithQuote_186) {
  ParsedInternalKey key(Slice("test"), 1, kTypeValue);
  std::string result = key.DebugString();
  EXPECT_EQ(result[0], '\'');
}

// Test with string constructed user key
TEST(ParsedInternalKeyTest_186, DebugStringFromStdString_186) {
  std::string userKey = "fromstring";
  ParsedInternalKey key(Slice(userKey), 77, kTypeDeletion);
  std::string result = key.DebugString();
  EXPECT_NE(result.find("fromstring"), std::string::npos);
  EXPECT_NE(result.find("77"), std::string::npos);
}

// Test default constructor
TEST(ParsedInternalKeyTest_186, DefaultConstructor_186) {
  ParsedInternalKey key;
  // Should still be able to call DebugString without crashing
  std::string result = key.DebugString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("@"), std::string::npos);
  EXPECT_NE(result.find(":"), std::string::npos);
}

// Test with binary data in key
TEST(ParsedInternalKeyTest_186, DebugStringBinaryData_186) {
  std::string binaryKey(4, '\0');
  binaryKey[1] = 'a';
  binaryKey[2] = 'b';
  ParsedInternalKey key(Slice(binaryKey.data(), binaryKey.size()), 10, kTypeValue);
  std::string result = key.DebugString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("@"), std::string::npos);
  EXPECT_NE(result.find("10"), std::string::npos);
}

// Test that kTypeValue produces expected integer representation
TEST(ParsedInternalKeyTest_186, DebugStringValueTypeInteger_186) {
  ParsedInternalKey key(Slice("x"), 1, kTypeValue);
  std::string result = key.DebugString();
  // kTypeValue is 1, format is "... : <int>"
  // Check that it ends with ": 1"
  EXPECT_NE(result.find(": 1"), std::string::npos);
}

// Test that kTypeDeletion produces expected integer representation
TEST(ParsedInternalKeyTest_186, DebugStringDeletionTypeInteger_186) {
  ParsedInternalKey key(Slice("x"), 1, kTypeDeletion);
  std::string result = key.DebugString();
  // kTypeDeletion is 0, format is "... : <int>"
  EXPECT_NE(result.find(": 0"), std::string::npos);
}

}  // namespace leveldb

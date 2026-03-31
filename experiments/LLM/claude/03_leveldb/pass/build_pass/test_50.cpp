#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

class InternalKeyTest_50 : public ::testing::Test {
 protected:
  InternalKey key_;
};

// Test that DecodeFrom with a non-empty slice returns true
TEST_F(InternalKeyTest_50, DecodeFromNonEmptySliceReturnsTrue_50) {
  Slice s("hello");
  EXPECT_TRUE(key_.DecodeFrom(s));
}

// Test that DecodeFrom with an empty slice returns false
TEST_F(InternalKeyTest_50, DecodeFromEmptySliceReturnsFalse_50) {
  Slice s("");
  EXPECT_FALSE(key_.DecodeFrom(s));
}

// Test that DecodeFrom with a single character returns true
TEST_F(InternalKeyTest_50, DecodeFromSingleCharReturnsTrue_50) {
  Slice s("x");
  EXPECT_TRUE(key_.DecodeFrom(s));
}

// Test that after DecodeFrom, Encode returns the same data
TEST_F(InternalKeyTest_50, EncodeAfterDecodeReturnsSameData_50) {
  std::string data = "testkey\x01\x00\x00\x00\x00\x00\x00\x01";
  Slice s(data);
  EXPECT_TRUE(key_.DecodeFrom(s));
  Slice encoded = key_.Encode();
  EXPECT_EQ(encoded.size(), data.size());
  EXPECT_EQ(encoded.ToString(), data);
}

// Test that DecodeFrom with binary data containing null bytes works
TEST_F(InternalKeyTest_50, DecodeFromBinaryDataWithNulls_50) {
  std::string data("ab\x00cd", 5);
  Slice s(data);
  EXPECT_TRUE(key_.DecodeFrom(s));
  Slice encoded = key_.Encode();
  EXPECT_EQ(encoded.size(), 5u);
  EXPECT_EQ(encoded.ToString(), data);
}

// Test that Clear makes the internal representation empty
TEST_F(InternalKeyTest_50, ClearMakesKeyEmpty_50) {
  Slice s("somedata");
  key_.DecodeFrom(s);
  key_.Clear();
  Slice encoded = key_.Encode();
  EXPECT_TRUE(encoded.empty());
}

// Test that DecodeFrom can be called multiple times (overwrite)
TEST_F(InternalKeyTest_50, DecodeFromOverwritesPreviousValue_50) {
  Slice s1("first");
  EXPECT_TRUE(key_.DecodeFrom(s1));
  Slice encoded1 = key_.Encode();
  EXPECT_EQ(encoded1.ToString(), "first");

  Slice s2("second");
  EXPECT_TRUE(key_.DecodeFrom(s2));
  Slice encoded2 = key_.Encode();
  EXPECT_EQ(encoded2.ToString(), "second");
}

// Test default constructor results in empty Encode
TEST_F(InternalKeyTest_50, DefaultConstructorEncodesEmpty_50) {
  InternalKey defaultKey;
  Slice encoded = defaultKey.Encode();
  EXPECT_TRUE(encoded.empty());
}

// Test that DecodeFrom with a large slice works
TEST_F(InternalKeyTest_50, DecodeFromLargeSlice_50) {
  std::string largeData(10000, 'A');
  Slice s(largeData);
  EXPECT_TRUE(key_.DecodeFrom(s));
  Slice encoded = key_.Encode();
  EXPECT_EQ(encoded.size(), 10000u);
  EXPECT_EQ(encoded.ToString(), largeData);
}

// Test constructing InternalKey with user_key, sequence, and type
TEST_F(InternalKeyTest_50, ConstructWithUserKeySequenceAndType_50) {
  InternalKey ikey(Slice("mykey"), 100, kTypeValue);
  Slice encoded = ikey.Encode();
  EXPECT_FALSE(encoded.empty());
  // The user_key should be extractable
  Slice ukey = ikey.user_key();
  EXPECT_EQ(ukey.ToString(), "mykey");
}

// Test user_key extraction after construction
TEST_F(InternalKeyTest_50, UserKeyExtraction_50) {
  InternalKey ikey(Slice("userkey"), 42, kTypeDeletion);
  Slice ukey = ikey.user_key();
  EXPECT_EQ(ukey.ToString(), "userkey");
}

// Test SetFrom with a ParsedInternalKey
TEST_F(InternalKeyTest_50, SetFromParsedInternalKey_50) {
  ParsedInternalKey parsed;
  parsed.user_key = Slice("setfromkey");
  parsed.sequence = 200;
  parsed.type = kTypeValue;

  key_.SetFrom(parsed);
  Slice ukey = key_.user_key();
  EXPECT_EQ(ukey.ToString(), "setfromkey");
}

// Test DebugString returns non-empty for a valid key
TEST_F(InternalKeyTest_50, DebugStringNonEmpty_50) {
  InternalKey ikey(Slice("debugkey"), 1, kTypeValue);
  std::string debug = ikey.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test that DecodeFrom with Slice of size 0 constructed from data pointer returns false
TEST_F(InternalKeyTest_50, DecodeFromZeroSizeSliceReturnsFalse_50) {
  const char* data = "notempty";
  Slice s(data, 0);
  EXPECT_FALSE(key_.DecodeFrom(s));
}

// Test Encode after Clear returns empty
TEST_F(InternalKeyTest_50, EncodeAfterClearIsEmpty_50) {
  InternalKey ikey(Slice("test"), 50, kTypeValue);
  EXPECT_FALSE(ikey.Encode().empty());
  ikey.Clear();
  EXPECT_TRUE(ikey.Encode().empty());
}

// Test that DecodeFrom preserves exact byte content
TEST_F(InternalKeyTest_50, DecodeFromPreservesExactBytes_50) {
  std::string original;
  original.push_back('\xff');
  original.push_back('\x00');
  original.push_back('\x80');
  original.push_back('\x7f');
  Slice s(original);
  EXPECT_TRUE(key_.DecodeFrom(s));
  Slice encoded = key_.Encode();
  EXPECT_EQ(encoded.size(), 4u);
  EXPECT_EQ(encoded.ToString(), original);
}

}  // namespace leveldb
